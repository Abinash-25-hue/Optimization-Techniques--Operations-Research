#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LINE_SIZE 1024
#define MAX_COLS 100

void main()
{
    int index, jindex, has_file, supply, demand, l_index, l_jindex;
    printf("\nDo you wanna enter data with a .csv file (Press 1) or manually (Press 0) ? : ");
    scanf("%d", &has_file);

    //Initialization

    char file_name[100];
    double supply_array[100], demand_array[100], cost[100][100], sum = 0,  least = 99999;

    for (index = 0; index < 100; index++)
    {
        for (jindex = 0; jindex < 100; jindex++)
        {
            cost[index][jindex] = 0;
        }
    }

    if (has_file == 1)
    {
        printf("\nEnter the .csv file name : ");
        scanf(" %[^\n]", file_name);
        
        FILE *file = fopen(file_name, "r");
        char *line[LINE_SIZE];

        if (file == NULL)
        {
            perror("Error, file not found, Try Again. \n");
        }
        
        fgets(line, sizeof(line), file);
        char *token = strtok(line, ",");
        supply = atoi(token);

        token = strtok(NULL, ",");
        demand = atoi(token);
        line[strcspn(line, "\n")] = 0;

        printf("supply = %d, demand = %d \n", supply, demand);

        csv_array_entry(supply_array, supply, 0, file);
        csv_array_entry(demand_array, demand, 0, file);

        array_sum(supply_array, supply);
        array_sum(demand_array, demand);

        token = strtok(line, ",");
        for (index = 0; index < supply; index++)
        {
            fgets(line, sizeof(line), file);
            token = strtok(line, ",");
            for (jindex = 0; jindex < demand; jindex++)
            {
                cost[index][jindex] = atof(token);
                token = strtok(NULL, ",");
            }
            line[strcspn(line, "\n")] = 0;
        }
        printf("\n");

    }
    else if (has_file == 0)
    {
        printf("Enter the number of supply : ");
        scanf("%d", &supply);
        printf("Enter the number of demand : ");
        scanf("%d", &demand);
        printf("\n");

        manual_array_entry(supply_array, supply, 0, "Supply");
        printf("\n");
        manual_array_entry(demand_array, demand, 0, "Demand");
        printf("\n");

        for (index = 0; index < supply; index++)
        {
            for (jindex = 0; jindex < demand; jindex++)
            {
                printf("Enter cost at (%d, %d) : ", (index + 1), (jindex + 1));
                scanf(" %lf", &cost[index][jindex]);
            }
        }
        array_sum(supply_array, supply);
        array_sum(demand_array, demand);

    }
    printf("\n");


    //Printing Part

    printf("Solver| ");
    for (index = 0; index < demand; index++)
    {
        printf("D%d,  ", (index + 1));
    }
    printf("  Supply");
    printf("\n----------------------------------------\n");
    for (index = 0; index < supply; index++)
    {
        printf("  S%d  | ", (index + 1));
        for (jindex = 0; jindex < demand; jindex++)
        {
            printf("%.1lf, ", cost[index][jindex]);
        }
        printf(" | %.1lf |", supply_array[index]);
        printf("\n");
    }
    printf("----------------------------------------\n");
    printf("Demand: ");
    for (index = 0; index < demand; index++)
    {
        printf("%.1lf, ", demand_array[index]);
    }
    array_sum(demand_array, demand);
    printf("\n\n");


    //Working Part

    if (array_sum(supply_array, supply) > array_sum(demand_array, demand))
    {
        demand++;
        demand_array[demand - 1] = array_sum(supply_array, supply) - array_sum(demand_array, demand);
    }
    else if (array_sum(supply_array, supply) < array_sum(demand_array, demand))
    {
        supply++;
        supply_array[supply - 1] = array_sum(demand_array, demand) - array_sum(supply_array, supply);
    }
    
    while ((array_non_zero_checker(supply_array, supply) != 0) && (array_non_zero_checker(demand_array, demand) != 0))
    {
        least = 99999;
        for (index = 0; index < supply; index++)
        {
            for (jindex = 0; jindex < demand; jindex++)
            {
                if ((least >= cost[index][jindex]) && (cost[index][jindex] >= 0))
                {
                    least = cost[index][jindex];
                    l_index = index;
                    l_jindex = jindex;
                }
            }
        }
        if (supply_array[l_index] < demand_array[l_jindex])
        {
            sum+=(least * supply_array[l_index]);
            demand_array[l_jindex] = demand_array[l_jindex] - supply_array[l_index];
            supply_array[l_index] = 0;
            for (jindex = 0; jindex < demand; jindex++)
            {
                cost[l_index][jindex] = -1;
            }
        }
        else if (supply_array[l_index] > demand_array[l_jindex])
        {
            sum+=(least * demand_array[l_jindex]);
            supply_array[l_index] = supply_array[l_index] - demand_array[l_jindex];
            demand_array[l_jindex] = 0;
            for (index = 0; index < supply; index++)
            {
                cost[index][l_jindex] = -1;
            }
        }
        else
        {
            sum+=(least * supply_array[l_index]);
            supply_array[l_index] = 0;
            demand_array[l_jindex] = 0;
            for (jindex = 0; jindex < demand; jindex++)
            {
                cost[l_index][jindex] = -1;
            }
            for (index = 0; index < supply; index++)
            {
                cost[index][l_jindex] = -1;
            }
        }
        
    }

    printf("Total Cost = %.1lf \n\n", sum);

}

void csv_array_entry(double array[], int limit_1, int limit_2, FILE *file)
{
    int index;
    char *line[LINE_SIZE];
    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = 0;
    char *token = strtok(line, ",");

    for (index = 0; index < limit_1; index++)
    {
        array[index] = atof(token);
        token = strtok(NULL, ",");
    }
}

void manual_array_entry(double array[], int limit_1, int limit_2, char *name[100])
{
    int index;
    for (index = 0; index < limit_1; index++)
    {
        printf("Enter element %d of %s : ", (index + 1), name);
        scanf(" %lf", &array[index]);
    }
}

int array_sum(double array[], int limit_1)
{
    int index;
    double sum = 0;
    for (index = 0; index < limit_1; index++)
    {
        sum+=array[index];
    }
    return sum;
}

int array_non_zero_checker(double array[], int limit_1)
{
    int index, is_zero = 0;
    for (index = 0; index < limit_1; index++)
    {
        if (array[index] != 0)
        {
            is_zero = 1;
        }
    }
    //printf("is_zero = %d \n", is_zero);
    return is_zero;
}



