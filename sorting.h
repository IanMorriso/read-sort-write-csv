#ifndef SORTING
#define SORTING

#include "lab13.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#endif

void getInput(char *input);
void userSort(struct game *games[], char *input);
int name_compare(const void *a, const void *b);
int publisher_compare(const void *a, const void *b);
int genre_compare(const void *a, const void *b);
int platform_compare(const void *a, const void *b);
int NA_compare(const void *a, const void *b);
int EU_compare(const void *a, const void *b);
int JP_compare(const void *a, const void *b);
int year_compare(const void *a, const void *b);
void rerank(struct game *games[]);