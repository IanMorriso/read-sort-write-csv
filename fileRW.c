#include "fileRW.h"


int char_tracker = 0;   // Global Variable to track location in current file line
char *header_line;      // Tracks the header of our input file

void read_file(char* fileName, char* mode, struct game *games[]) {

    // File to read from
    FILE* fp = fopen(fileName, mode);
    if (!fp) {
        printf("Failed to open %s with mode '%s'\n", fileName, mode);
        exit(0);
    }

    // This block allocates memory for our file_line string, which will hold each line in our input file, one at a time
    char *file_line = calloc(256, 1);  
    if (file_line == NULL) {
        printf("Failed to allocate file_line buffer.\n");
        exit(0);
    }


    int row = -1;   // Starts at -1 so we do not read the first line of the file
    while (fgets(file_line, 256, fp) != NULL) {
        if ((row == -1)) {

            header_line = (char *)calloc(strlen(file_line) + 1, 1);
            strcpy(header_line, file_line);
            row++;
            continue;
        }


        struct game *new_game = (struct game *)malloc(sizeof(struct game)); // Creates a pointer to a game struct, so we can initialize it with a new game from out input file
        //new_game->rank = 0;
        //new_game->year = 0;
        // This block initializes each property of our new_game based on the corresponding data types
        game_initializer_int(&(new_game->rank), file_line);

        game_initializer_str(&(new_game->name), file_line);
        game_initializer_str(&(new_game->platform), file_line);

        game_initializer_int(&(new_game->year), file_line);

        game_initializer_str(&(new_game->genre), file_line);
        game_initializer_str(&(new_game->publisher), file_line);

        game_initializer_float(&(new_game->NA_sales), file_line);
        game_initializer_float(&(new_game->EU_sales), file_line);
        game_initializer_float(&(new_game->JP_sales), file_line);
        game_initializer_float(&(new_game->other_sales), file_line);
        game_initializer_float(&(new_game->global_sales), file_line);


        // This block checks for empty values from the input file, and calculates any missing values
        if (new_game->NA_sales < 0) {
            new_game->NA_sales = (new_game->global_sales - (new_game->EU_sales + new_game->JP_sales + new_game->other_sales));
        }
        else if (new_game->EU_sales < 0) {
            new_game->EU_sales = (new_game->global_sales - (new_game->NA_sales + new_game->JP_sales + new_game->other_sales));
        }
        else if (new_game->JP_sales < 0) {
            new_game->JP_sales = (new_game->global_sales - (new_game->EU_sales + new_game->NA_sales + new_game->other_sales));
        }
        else if (new_game->other_sales < 0) {
            new_game->other_sales = (new_game->global_sales - (new_game->EU_sales + new_game->JP_sales + new_game->NA_sales));
        }

        // Resets our character tracker for our file_line, adds the new_game to our array of game pointers, and proceeds to the next row (line) of our input file
        char_tracker = 0;
        games[row] = new_game;
        row++;
    }
    free(file_line);
    fclose(fp);
    return;
}


void write_file(char* fileName, char* mode, struct game *games[]) {

    // Opens/creates output file to write to
    FILE* fq = fopen(fileName, mode);
    if (!fq) {
        printf("Failed to open %s with mode '%s'\n", fileName, mode);
        exit(0);
    }
    // If u_sort == tre, write the header for our new .csv file
    if (u_sort == true) {
        fprintf(fq, "%s", header_line);

    }
    // This loop writes each game's properties into our output file, on a new line for each game
    for (int i = 0; i < MAX_GAMES; i++) {
        fprintf(fq, "%d,%s,%s,%d,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                                                                games[i]->rank,
                                                                games[i]->name,
                                                                games[i]->platform,
                                                                games[i]->year,
                                                                games[i]->genre,
                                                                games[i]->publisher,
                                                                games[i]->NA_sales,
                                                                games[i]->EU_sales,
                                                                games[i]->JP_sales,
                                                                games[i]->other_sales,
                                                                games[i]->global_sales);
    }
    free(header_line);
    fclose(fq);
    return;
}

// Initializes integer values (rank or year) for our new_game
void game_initializer_int(int *game_int, char *file_line) { 
    
    char temp[128] = {'\0'};
    int count = 0;

    // Steps through the file_line and adds each character to temp[] while it is not ',' or '\0'
    while ((file_line[char_tracker] != ',') && (file_line[char_tracker] != '\n')) {
        temp[count] = file_line[char_tracker];
        count++;
        char_tracker++;
    }
    char_tracker++;
    count ++;

    temp[count] = '\0';
    *game_int = atoi(temp);     // Sets a integer value of new_game
    return;
}

// Initializes strings (name, genre, platform, publisher) for our new_game
void game_initializer_str(char **game_str, char *file_line) {
    
    char temp[128] = {'\0'};
    int count = 0;

    // Steps through the file_line and adds each character to temp[] while it is not ',' or '\0'
    while ((file_line[char_tracker] != ',') && (file_line[char_tracker] != '\n')) {
        temp[count] = file_line[char_tracker];
        count++;
        char_tracker++;
    }
    char_tracker++;
    count ++;

    temp[count] = '\0';
    *game_str = (char *)calloc(strlen(temp) + 1, 1);    // Allocates length of string + 1 for NULL
    strcpy(*game_str, temp);                            // Copies temp into our new_game string
    return;
}

// Initialiezes floats (NA_sales, EU_sales, JP_sales, other_sales, global_sales) for our new_game
void game_initializer_float(float *game_float, char *file_line) {

    char temp[128] = {'\0'};
    int count = 0;

    // Steps through the file_line and adds each character to temp[] while it is not ',' or '\0'
    while ((file_line[char_tracker] != ',') && (file_line[char_tracker] != '\n')) {

        temp[count] = file_line[char_tracker];
        count++;
        char_tracker++;
    }
    char_tracker++;
    count ++;

    temp[count] = '\0';

    // This checks for missing values, and sets our float to -1 as a flag if found
    if (!(strcmp(temp, " ")) || !(strcmp(temp, ""))) {
        *game_float = -1;
        return;
    }

    *game_float = atof(temp);       // Sets float value for our new_game
    return;
}