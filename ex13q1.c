/* Purpose: Reading, sorting, and writing .csv files
 * Author: Ian Morrison
 * Date: November 25/2022
 * References: 
 *      https://stackoverflow.com/questions/26703616/organizing-a-struct-in-alphabetical-order-with-qsort, Author : Jonathan Leffler
 *      https://www.algolist.net/Data_structures/Binary_search_tree/Removal, Lab11
 *      call1.c, Author: Guohui Lin
 *            
 */

#include "lab13.h"
#include "sorting.h"
#include "bsearch.h"
#include "bubbleSort.h"
#include "salesStats.h"
#include "fileRW.h"
bool u_sort = false;

int main (int argc, char *argv[]) {

    // Checks for input parameter
    if (argc != 2) {
        printf("ERROR: Insufficent parameters. Input .csv file needed.\n");
        exit(0);
    }

    // This block reads the given .csv file, and creates an array of game pointers
    char *fileName = argv[1];
    char *mode = "r";
    struct game *games[MAX_GAMES];
    read_file(fileName, mode, games);

    fileName = "processing.csv";

    // This block writes our missing sales values to our output file
    if (!strcmp(argv[0], "./sorting")) {   // If our first cmd line arg is sorting, redefine SORTING as true

        u_sort = true;
        char *input =  (char *)calloc(10, 1);   // 10 bits as "publisher" + '\0' is the longest string to accept as input
        fileName = (char *)calloc(25, 1);       // 25 bits for max output file name length + '\0'

        // Builds our output file name
        strcat(fileName, "gamesales_");
        getInput(input);
        strcat(fileName, input);
        strcat(fileName, ".csv");
  
        userSort(games, input);
        free(input);
    }

    // Calls write_file
    mode = "w+";
    write_file(fileName, mode, games);


    if (u_sort == false) {

        // This block creates binary search trees, sorted by publisher, and another sorted by repeated title count
        struct bst_node *publishers = create_BST(games[0]->publisher);
        for (int i = 1; i < (MAX_GAMES - 1); i++) {
            insert_node(games[i]->publisher, publishers);
        }

        struct bst_node *repeated_games = create_BST(games[0]->name);
        max_count = 0;  // Counts max number of times any game has appeared
        for (int i = 1; i < (MAX_GAMES - 1); i++) {
            insert_node(games[i]->name, repeated_games);
        }


        // This block displays our sorted data
        char *descriptor = (char*) calloc(6, 1); //{'\0'};
        printf("############ Common publishers: ############\n");
        in_order_print(publishers, strcpy(descriptor, "games"));
        free_btree(publishers);

        printf("\n############ Repeated games: ############\n");
        // Starting from our max name count, iterate down each value and display each sorted game with that value
        for (int i = max_count; i > 0; i--) {
            in_order_numerical(repeated_games, strcpy(descriptor, "times"), i);
        }
        free_btree(repeated_games);
        free(descriptor);


        // This block displays our percentages
        float global_totals[MAX_GAMES];
        for (int i = 0; i < MAX_GAMES; i++) {
            display_percentages(games[i]);
            global_totals[i] = games[i]->global_sales;
        }


        // Sorts and displays our summary stats
        bubble_sort(global_totals, MAX_GAMES);
        display_summary(global_totals);
    }


    // Frees remaining allocated data
    for (int i = 0; i < MAX_GAMES; i++) {
        free(games[i]->name);
        free(games[i]->publisher);
        free(games[i]->genre);
        free(games[i]->platform);
        free(games[i]);
    }

    return 0;
}