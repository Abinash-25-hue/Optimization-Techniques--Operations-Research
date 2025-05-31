#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_SIZE 1024

void main()
{
    printf("\n\n                                   !!  Welcome to NWCM_1.0  !!\n\n");
    printf("       This code helps solving North-West Corner Method of Optimization Techniques in an easier way. !\n\n");

    int has_file = 0;
    printf("Will you enter your data manually or with a .csv file ? \nPress (1) for YES and (0) for NO : ");
    scanf("%d", &has_file);

    char file_name[100] ;
    char *line[LINE_SIZE];

    int index, jindex, demand, supply;
    int demand_limit = demand, supply_limit = supply;
    int demand_array[100], supply_array[100];

    int cost[100][100];
    for (index = 0; index < (supply + 1); index++)
    {
        for (jindex = 0; jindex < (demand + 1); jindex++)
        {
            cost[index][jindex] = 0;
        }
    }

    if (has_file == 1)
    {
        printf("\nEnter the file name : ");
        scanf(" %[^\n]", file_name);


        FILE* file = fopen(file_name, "r");
        if (file == NULL)
        {
            perror("Error, file not found. \n");   
        }

        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        supply = atoi(token);

        token = strtok(NULL, ",");
        demand = atoi(token);

        line[strcspn(line, "\n")] = 0;
        demand_limit = demand;
        supply_limit = supply;

        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = 0;
        token = strtok(line, ",");
        for (index = 0; index < supply_limit; index++)
        {
            supply_array[index] = atoi(token);
            token = strtok(NULL, ",");
        }

        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = 0;
        token = strtok(line, ",");
        for (index = 0; index < demand_limit; index++)
        {
            demand_array[index] = atoi(token);
            token = strtok(NULL, ",");
        }
        line[strcspn(line, "\n")] = 0;

        for (index = 0; index < supply_limit; index++)
        {
            fgets(line, sizeof(line), file);
            line[strcspn(line, "\n")] = 0;

            token = strtok(line, ",");
            for (jindex = 0; jindex < demand_limit; jindex++)
            {
                cost[index][jindex] = atoi(token);
                token = strtok(NULL, ",");
            }
        }

    }
    else if (has_file == 0)
    {
        printf("Enter the no of Supply : ");
        scanf("%d", &supply);
        printf("Enter the no of Demand : ");
        scanf("%d", &demand);
        
        supply_limit = supply;
        demand_limit = demand;

        //int supply_array[supply + 1], demand_array[demand + 1];
        
        printf("\n");
        array_entry(supply_array, (supply_limit), "Supply");
        array_entry(demand_array, (demand_limit), "Demand");

        for (index = 0; index < supply_limit; index++)
        {
            for (jindex = 0; jindex < demand_limit; jindex++)
            {
                printf("Enter the cost at (%d, %d) : ", index, jindex);
                scanf("%d", &cost[index][jindex]);
            }
        }
    }
    printf("\n");


    //Working Part

    if (array_sum(demand_array, demand_limit) > array_sum(supply_array, supply_limit))
    {
        supply_array[supply_limit] = (array_sum(demand_array, demand_limit) - array_sum(supply_array, supply_limit));
        supply_limit+=1;
    }
    else if (array_sum(demand_array, demand_limit) < array_sum(supply_array, supply_limit))
    {
        demand_array[demand_limit] = (array_sum(supply_array, supply_limit) - array_sum(demand_array, demand_limit));
        demand_limit+=1;
    }

    //printf("Supply_limit = %d, demand_limit = %d \n\n", supply_limit, demand_limit);
    //array_printer(supply_array, supply_limit, 0);
    //array_printer(demand_array, demand_limit, 0);

    int sum = 0, multiplier = 1, c_row = 0, c_column = 0;
    while ((c_row != supply_limit) && (c_column != demand_limit))
    {
        if (supply_array[c_row] <= demand_array[c_column])
        {
            multiplier = supply_array[c_row];
            demand_array[c_column] -= supply_array[c_row];
            sum+=((cost[c_row][c_column])*multiplier);
            supply_array[c_row] = 0;
           c_row++;
        }
        else if (supply_array[c_row] > demand_array[c_column])
        {
            multiplier = demand_array[c_column];
            supply_array[c_row] -= demand_array[c_column];
            sum+=((cost[c_row][c_column])*multiplier);
            demand_array[c_column] = 0;
            c_column++;
        }
        //printf("\n");

    }
    
    


    //Printing Part

    /*for (index = 0; index < supply_limit; index++)
    {
        for (jindex = 0; jindex < demand_limit; jindex++)
        {
            printf("%d, ", cost[index][jindex]);
        }
        printf(" | %d |", supply_array[index]);
        printf("\n");
    }
    printf("\n| ");
    for (index = 0; index < demand_limit; index++)
    {
        printf("%d| ", demand_array[index]);;
    }*/
    printf("The total Cost is %d. \n", sum);

}

void array_entry(int array[], int limit_1, char array_name[100])
{
    int index;
    for (index = 0; index < limit_1; index++)
    {
        printf("Enter element %d of %s : ", index, array_name);
        scanf("%d", &array[index], 0);
    }
    printf("\n");
}

void array_printer(int array[], int limit_1, int limit_2)
{
    int index;
    for (index = 0; index < limit_1; index++)
    {
        printf("%d, ", array[index]);
    }
    printf("\n");
}

int array_sum(int array[], int limit_1)
{
    int index, sum = 0;
    for (index = 0; index < limit_1; index++)
    {
        sum+=array[index];
    }
    return sum;
}
