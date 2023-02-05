#include "sorting.h"

int sort_type = 0;


void getInput(char *input) {
    
    int max_choices = 8;   
    char *valid[8] = {"name", "year", "platform", "genre", "publisher", "NA_sales", "EU_sales", "JP_sales"};
    bool match = false;

    while (match == false) {        
        printf("Sort games by: ");
        scanf("%s", input);
        for (int i = 0; i < max_choices; i++) {
            if (!(strcmp(input, valid[i]))) {
                sort_type = i;
                return;
            }
        }
    }
    return;
}


void userSort(struct game *games[], char *input) {

    if (strcmp(input, "name") == 0) {
        qsort(games, MAX_GAMES, sizeof(struct game *), name_compare);
    }

    else if (strcmp(input, "year") == 0) {
        qsort(games, MAX_GAMES, sizeof(struct game *), year_compare);
    }

    else if (strcmp(input, "platform") == 0) {
        qsort(games, MAX_GAMES, sizeof(struct game *), platform_compare);
    }

    else if (strcmp(input, "genre") == 0) {
        qsort(games, MAX_GAMES, sizeof(struct game *), genre_compare);
    }

    else if (strcmp(input, "publisher") == 0) {
        qsort(games, MAX_GAMES, sizeof(struct game *), publisher_compare);
    }

    else if (strcmp(input, "NA_sales") == 0) {
        qsort(games, MAX_GAMES, sizeof(struct game *), NA_compare);
    }

    else if (strcmp(input, "EU_sales") == 0) {
        qsort(games, MAX_GAMES, sizeof(struct game *), EU_compare);
    }

    else if (strcmp(input, "JP_sales") == 0) {
        qsort(games, MAX_GAMES, sizeof(struct game *), JP_compare);
    }

    rerank(games);
    return;
}


int year_compare(const void *a, const void *b) {

    if ((*(struct game **)a)->year > (*(struct game **)b)->year) {
        return -1;
    }
    else if ((*(struct game **)a)->year == (*(struct game **)b)->year) {
        return strcmp((*(struct game **)a)->name, (*(struct game **)b)->name);
    }
    return 1;
}


int NA_compare(const void *a, const void *b) {

    if ((*(struct game **)a)->NA_sales > (*(struct game **)b)->NA_sales) {
        return -1;
    }
    else if ((*(struct game **)a)->NA_sales == (*(struct game **)b)->NA_sales) {
        return 0;
    }
    return 1;
}


int EU_compare(const void *a, const void *b) {

    if ((*(struct game **)a)->EU_sales > (*(struct game **)b)->EU_sales) {
        return -1;
    }
    else if ((*(struct game **)a)->EU_sales == (*(struct game **)b)->EU_sales) {
        return 0;
    }
    return 1;  
}


int JP_compare(const void *a, const void *b) {  

    if ((*(struct game **)a)->JP_sales > (*(struct game **)b)->JP_sales) {
        return -1;
    }
    else if ((*(struct game **)a)->JP_sales == (*(struct game **)b)->JP_sales) {
        return 0;
    }
    return 1;
}


int publisher_compare(const void *a, const void *b) {
    if ((strcmp((*(struct game **)a)->publisher, (*(struct game **)b)->publisher)) == 0) {
        return strcmp((*(struct game **)a)->name, (*(struct game **)b)->name);
    }
    return strcmp((*(struct game **)a)->publisher, (*(struct game **)b)->publisher);
}


int genre_compare(const void *a, const void *b) {
    if ((strcmp((*(struct game **)a)->genre, (*(struct game **)b)->genre)) == 0) {
        return strcmp((*(struct game **)a)->name, (*(struct game **)b)->name);
    }
    return strcmp((*(struct game **)a)->genre, (*(struct game **)b)->genre);
}


int platform_compare(const void *a, const void *b) {

    if ((strcmp((*(struct game **)a)->platform, (*(struct game **)b)->platform)) == 0) {
        return strcmp((*(struct game **)a)->name, (*(struct game **)b)->name);
    }

    return strcmp((*(struct game **)a)->platform, (*(struct game **)b)->platform);
}


int name_compare(const void *a, const void *b) {

    return strcmp((*(struct game **)a)->name, (*(struct game **)b)->name);
}

void rerank(struct game *games[]) {

    for (int i = 0; i < MAX_GAMES; i++) {
        games[i]->rank = i+1;
    }

}