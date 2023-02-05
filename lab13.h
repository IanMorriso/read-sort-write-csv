#ifndef EX13_H
#define EX13_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_GAMES 100



struct game {
    int rank;
    int year;
    char *name;
    char *platform;
    char *genre;
    char *publisher;
    
    // sales below represented in millions
    float NA_sales;
    float EU_sales;
    float JP_sales;
    float other_sales;
    float global_sales;
};

#endif // EX13_H

// Function declarations
//void read_file(char* fileName, char* mode, struct game *games[]);
//void write_file(char* fileName, char* mode, struct game *games[]);



//struct game **initialize(int n);
//struct game create(struct game **game_list, int n);



