#ifndef FILERW_H
#define FILERW_H

#include "lab13.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
extern bool u_sort;
#endif //"FILERW_H"

// Function declarations
void read_file(char* fileName, char* mode, struct game *games[]);
void write_file(char* fileName, char* mode, struct game *games[]);
void game_initializer_int(int *game_int, char *file_line);
void game_initializer_float(float *game_float, char *file_line);
void game_initializer_str(char **game_str, char *file_line);

