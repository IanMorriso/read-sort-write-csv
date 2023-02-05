# include "salesStats.h"

float mean_sales = 0;
float median_sales = 0;
float range_sales = 0;
float total_global = 0;

void display_percentages(struct game *target_game) {
    float na_percentage = (target_game->NA_sales / target_game->global_sales) * 100;
    float eu_percentage = (target_game->EU_sales / target_game->global_sales) * 100;
    float jp_percentage = (target_game->JP_sales / target_game->global_sales) * 100;
    float other_percentage = (target_game->other_sales / target_game->global_sales) * 100;

    printf("%s - NA %0.1f%%, EU %0.1f%%, JP: %0.1f%%, Other: %0.1f%%\n",target_game->name,
                                                                na_percentage,
                                                                eu_percentage,
                                                                jp_percentage,
                                                                other_percentage);

    total_global += target_game->global_sales;
    return;
}


void display_summary(float global_totals[]) {
    
    int middle = MAX_GAMES/2;
    float median = 0;
    if ((MAX_GAMES % 2) != 0) {
        median = global_totals[middle];
    }
    else {
        median = (global_totals[middle] + global_totals[middle - 1]) / 2;
    }

    float mean = total_global / MAX_GAMES;
    float range = (global_totals[0] - global_totals[MAX_GAMES - 1]);

    printf("\n############ Summary Statistics: ############\n");
    printf("Mean global sales: %.2f million\n", mean);
    printf("Median global sales: %.2f million\n", median);
    printf("Range of global sales: %.2f million\n\n", range);

}