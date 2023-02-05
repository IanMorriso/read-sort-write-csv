#!/usr/bin/bash
# Check script given for lab 13
#
# Written in Fall 2022 for CMPUT 201 @ University of Alberta
# by Akemi Izuko <akemi.izuko@ualberta.ca>
umask 077
shopt -s lastpipe

declare -r TMP_DIR="$(mktemp -d --tmpdir=/dev/shm)"  # Shared mem is big enough?
declare -r REQUIRED_FILES=(\
  ex13q1.c
  lab13.h
  makefile
  gamesales.csv
  check.sh
)

print_help() {
  cat <<HELP
Check file for lab 13

USAGE:
    $0 submit.tar
    bash $0 submit.tar
HELP
}

# ===================================================================
# Helper functions
# ===================================================================
assert_lab_machine() {
  if [[ "$(hostname)" =~ ^ug[0-9]{2}$ || "$(hostname)" == ohaton ]]; then
    return 0
  else
    return 1
  fi
}

check_mem_leaks() {
  local -i valgrind_out=0
  local name="$1"
  local exe="${TMP_DIR}/${name}"
  local file="${TMP_DIR}/gamesales.csv"
  local input="$2"
  local out="${TMP_DIR}/valgrind_out"

  # Checks for heap memory leaks
  printf "\nChecking for memory leaks (this may appear to freeze for a second)\n"

  # Runs the program
  if [[ -z "$input" ]]; then
    valgrind "$exe" "$file" 2> "$out" >/dev/null
  else
    valgrind "$exe" "$file" <<<"$input" 2> "$out" >/dev/null
  fi

  # Parses out the "in use at exit" number
  awk 'match($0, /in use at exit/) {
    split($0, a, " ");
    printf "%d", a[6];
  }' "$out" | read -r valgrind_out

  if [[ "$valgrind_out" -ne 0 ]]; then
    echo "Memory leaks detected in ${name}!"
    return 1
  else
    printf "%s did not leak memory! Good stuff\n\n" "$name"
    return 0
  fi
}

# Returns true if a file is a valid csv file, false otherwise. Pretty much just
# checks the commas
validate_csv() {
  local file="$1"
  local is_csv="not_a_csv"

  awk '
    BEGIN { is_csv = is_first_line = 1 }

    {
        if (is_first_line) {
            is_first_line = 0
            comma_count = split($0, a, ",")
        } else {
            line_comma_count = split($0, b, ",")
            if (line_comma_count != comma_count) is_csv = 0
        }
    }

    END {
        if (is_csv) printf "is_csv"
        else printf "not_a_csv"
    }
  ' "$1" | read -r is_csv

  if [[ "$is_csv" == "is_csv" ]]; then
    return 0
  else
    return 1
  fi
}

# ===================================================================
# Main program starts here
# ===================================================================
if ! [[ -r "$1" ]]; then
  print_help
  exit 1
elif ! assert_lab_machine; then
    echo " \`$(hostname) \` is not a lab machine!"
    echo "Please scp your files to a lab machine and run this check script there"
    exit 1
else
  # Untar file
  if ! tar -C "$TMP_DIR" -xf "$1"; then
    echo "Something is wrong with the tar file \"${1}\""
    exit 1
  fi

  # Check to make sure all files are present
  for file in "${REQUIRED_FILES[@]}"; do
    if ! [[ -e "${TMP_DIR}/${file}" ]]; then
      echo "You're missing \"${file}\" in your submission"
      exit 1
    fi
  done

  echo "Opened $1 into \`${TMP_DIR}\`"

  # Run make command and check executables `process` and `sorting` exist ====
  if ! make -C "$TMP_DIR"; then
    echo "\`make\` exited with nonzero exit code: $?. An error likely occured"
    exit 1
  fi

  if ! [[ -x "${TMP_DIR}/processing" ]]; then
    echo "No \`processing\` executable was built by the makefile run with \`make\`"
    echo "Please make sure running \`make\` alone will build all executables"
    exit 1
  elif ! [[ -x "${TMP_DIR}/sorting" ]]; then
    echo "No \`sorting\` executable was built by the makefile run with \`make\`"
    echo "Please make sure running \`make\` alone will build all executables"
    exit 1
  else
    echo "Makefile successfully built both \`sorting\` and \`processing\`"
  fi

  # Run process ====
  cd "${TMP_DIR}"

  if ! "${TMP_DIR}/processing" "${TMP_DIR}/gamesales.csv" &>/dev/null; then
    echo "\`processing\` returned a nonzero code $? when run with gamesales.csv"
    exit 1
  fi

  # Re-run with valgrind
  if ! check_mem_leaks "processing"; then
    exit 1
  fi

  if ! validate_csv "${TMP_DIR}/processing.csv"; then
    echo "process.csv is not a proper csv file"
    exit 1
  fi

  # Run sorting ====
  if ! "${TMP_DIR}/sorting" "${TMP_DIR}/gamesales.csv" <<<$'year\n'; then
    echo "\`sorting\` returned a nonzero code $? when run with \"year\""
    exit 1
  elif ! "${TMP_DIR}/sorting" "${TMP_DIR}/gamesales.csv" <<<$'JP_sales\n'; then
    echo "\`sorting\` returned a nonzero code $? when run with \"JP_sales\""
    exit 1
  fi

  # Re-run with valgrind
  if ! check_mem_leaks "sorting" $'year\n'; then
    exit 1
  fi

  if ! validate_csv "${TMP_DIR}/gamesales_year.csv"; then
    echo "gamesales_year.csv is not a proper csv file"
    exit 1
  elif ! validate_csv "${TMP_DIR}/gamesales_JP_sales.csv"; then
    echo "gamesales_JP_sales.csv is not a proper csv file"
    exit 1
  fi

  # Check if all good ====
  echo "All checks passed!"
  echo "If you feel you've tested enough, you can submit. Good luck!"
fi
