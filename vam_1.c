#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LINE_SIZE 1024

void main()
{
    printf("\n                          !!  Welcome to vam_1.c  !! \n");
    printf("    A program that solves transportation problem with Vogel's Approximation Method \n\n");
    int index, jindex, warehouse, factory, has_file, degeneracy_checker,allocations = 0;
    double cost[100][100], w_array[100], f_array[100], sum = 0;
    char file_name[100];
    printf("\nDo you want to enter data manually or with a .csv file ? \n");
    printf("\nPress (0) for manual and (1) for .csv : ");
    scanf("%d", &has_file);


    //Initialisation

    if (has_file == 1)
    {
        printf("\nEnter the name of the file : ");
        scanf(" %[^\n]", file_name);

        FILE *file;
        file = fopen(file_name, "r");
        char *line[LINE_SIZE];

        if (file == NULL)
        {
            perror("Error, file not found.\n");
        }

        fgets(line, sizeof(line), file);
        char *token = strtok(line, ",");
        factory = atoi(token);
        token = strtok(NULL, ",");
        warehouse = atoi(token);

        line[strcspn(line, "\n")] = 0;

        degeneracy_checker = (factory + warehouse - 1);
        //printf("f = %d, w = %d \n", factory, warehouse);

        csv_array_entry(f_array, factory, file);
        csv_array_entry(w_array, warehouse, file);

        for (index = 0; index < factory; index++)
        {
            fgets(line, sizeof(line), file);
            token = strtok(line, ",");
            for (jindex = 0; jindex < warehouse; jindex++)
            {
                cost[index][jindex] = atof(token);
                token = strtok(NULL, ",");
            }
            line[strcspn(line, "\n")] = 0;
        }
    }
    else if (has_file == 0)
    {
        printf("Ënter the number of factories : ");
        scanf("%d", &factory);
        printf("Ënter the number of warehouses : ");
        scanf("%d", &warehouse);
        printf("\n");
        manual_array_entry(f_array, factory, "factories");
        printf("\n");
        manual_array_entry(w_array, warehouse, "warehouse");
        degeneracy_checker = (factory + warehouse - 1);

        printf("\n");
        for (index = 0; index < factory; index++)
        {
            for (jindex = 0; jindex < warehouse; jindex++)
            {
                printf("Enter cost at (%d, %d) : ", index, jindex);
                scanf("%lf", &cost[index][jindex]);
            }
        }
        printf("Answer : \n");
    }


    //Working Part

    if (array_sum(f_array, factory) > array_sum(w_array, warehouse))
    {
        w_array[warehouse] = (array_sum(f_array, factory) - array_sum(w_array, warehouse));
        warehouse++;
    }
    else if (array_sum(f_array, factory) < array_sum(w_array, warehouse))
    {
        f_array[factory] = (array_sum(w_array, warehouse) - (f_array, factory));
        factory++;
    }

    int max_l, is_factory = 1, row, column;
    double min_1 = 99999, min_2 = 99999, multiplier, least;
    double f_diff_array[factory], w_diff_array[warehouse], diff_array[factory + warehouse], max;

    while ((factory > 0) && (warehouse > 0))
    {

        min_1 = 99999, min_2 = 99999;
        for (index = 0; index < factory; index++)
        {
            if (warehouse > 1)
            {
            min_1 = cost[index][0];
            for (jindex = 0; jindex < warehouse; jindex++)
            {
                min_1 = (min_1 >= cost[index][jindex])? cost[index][jindex]: min_1;
                //min_1 = (jindex == 0 && (cost[index][jindex] != -1))? cost[index][jindex]: (((min_1 >= cost[index][jindex]) && (cost[index][jindex] != -1))? cost[index][jindex]: min_1);
            }
            min_2 = 99999;
            for (jindex = 0; jindex < warehouse; jindex++)
            {
                if ((min_2 >= cost[index][jindex]) && (cost[index][jindex] != min_1))
                {
                    min_2 = cost[index][jindex];
                }
            }
            f_diff_array[index] = (min_2 - min_1);
            }
            else 
            {
                f_diff_array[index] = 0;
            }
            //f_diff_array[index] = ((min_2 == 99999) || (f_array[index] <= 0))? 0: (min_2 - min_1);
            //printf("%.1lf - %.1lf = %.1lf f\n", min_2, min_1, f_diff_array[index]);
        }

        //printf("\n");
        min_1 = 99999, min_2 = 99999;

        for (index = 0; index < warehouse; index++)
        {
            if (factory > 1)
            {
                min_1 = cost[0][index];
                for (jindex = 0; jindex < factory; jindex++)
                {
                    min_1 = (cost[jindex][index] <= min_1)? cost[jindex][index]: min_1;
                    //min_1 = ((jindex == 0) && (cost[jindex][index] != -1))? cost[jindex][index]: (((min_1 >= cost[jindex][index]) && (cost[jindex][index] != -1))? cost[jindex][index]: min_1);
                }
                min_2 = 99999;
                for (jindex = 0; jindex < factory; jindex++)
                {
                    if ((min_2 >= cost[jindex][index]) && (cost[jindex][index] != min_1))
                    {
                        min_2 = cost[jindex][index];
                    }
                    //min_2 = ((jindex == 0) && (cost[jindex][index] != min_1) && (cost[jindex][index] != -1))? cost[jindex][index]: ((((min_2 >= cost[jindex][index]) && (cost[jindex][index] != -1)) && (cost[jindex][index] != min_1))? cost[jindex][index]: min_2);
                    //printf("c[j][i] = %.1lf, m1 = %.1lf, m2 = %.1lf, j = %d, i = %d \n", cost[jindex][index], min_1, min_2, jindex, index);
                }
                //printf("%.1lf - %.1lf = %.1lf w\n", min_2, min_1, (min_2 - min_1));
                w_diff_array[index] = ((min_2 == 99999) || (w_array[index] <= 0))? 0: (min_2 - min_1);
            }
            else
            {
                w_diff_array[index] = 0;
            }
            //diff_array[factory + index] = (min_2 - min_1);
        }

        
        //printf("\nSum = %.1lf \n", sum);
        //printf("f = %d, w = %d \n", factory, warehouse);

        max = f_diff_array[0];
        for (index = 0; index < factory; index++)
        {
            if (max <= f_diff_array[index])
            {
                max = f_diff_array[index];
                max_l = index;
                is_factory = 1 ;
            }
        }
        for (index = 0; index < warehouse; index++)
        {
            if (max <= w_diff_array[index])
            {
                max = w_diff_array[index];
                max_l = index;
                is_factory = 0;
            }
        }

        //max_l = max_finder(diff_array, (factory + warehouse));
        
        if (is_factory == 1)
        {
            least = cost[max_l][0];
            for (index = 0; index < warehouse; index++)
            {
                if (least >= cost[max_l][index])
                {
                    least = cost[max_l][index];
                    row = max_l;
                    column = index;
                }
            }
        }
        else
        {
            least = cost[0][max_l];
            for (index = 0; index < factory; index++)
            {
                if (least >= cost[index][max_l])
                {
                    least = cost[index][max_l];
                    row = index;
                    column = max_l;
                }
            }
        }

        //Printing Part
        printf("\n");
        for (index = 0; index < factory; index++)
        {
            for (jindex = 0; jindex < warehouse; jindex++)
            {
                printf("%.1lf, ", cost[index][jindex]);   
            }
            printf("    |%.1lf|  %.1lf", f_array[index], f_diff_array[index]);
            printf("\n");
        }
        printf("\n");
        for (index = 0; index < warehouse; index++)
        {
            printf("%.1lf, ", w_array[index]);
        }
        printf("\n");
        printf("-------------------------------\n");
        for (index = 0; index < warehouse; index++)
        {
            printf("%.1lf, ", w_diff_array[index]);
        }
        printf("\n");

        //printf("Max_l = %d, is_factory = %d, least = %.1lf, row = %d, column = %d ", max_l, is_factory, least, row, column);
        //Checkers
        /*printf("Max = %.1lf, ", max);
        printf("Max_l = %d, ", max_l);
        printf("is_factory = %d, ", is_factory);
        printf("least = %.1lf, ", least);
        printf("row = %d, ", row);
        printf("column = %d, \n", column);*/

        if (f_array[row] > w_array[column])
        {
            multiplier = w_array[column];
            f_array[row] -= w_array[column];
            w_array[column] = 0;
            is_factory = 0;
            //printf("1 ");
        }
        else if (f_array[row] < w_array[column])
        {
            multiplier = f_array[row];
            w_array[column] -= f_array[row];
            f_array[row] = 0;
            is_factory = 1;
            //printf("2 ");
        }
        else
        {
            multiplier = f_array[row];
            f_array[row] = 0;
            w_array[column] = 0;
            //printf("0 ");
        }

        printf("\nCost : %.1lf ", sum);
        sum += least*multiplier;
        printf("+ (%.1lf * %.1lf) = %.1lf \n\n", least, multiplier, sum);
        allocations++;

        if (is_factory == 1)
        {
            for (index = 0; index < warehouse; index++)
            {
                for (jindex = row; jindex < factory; jindex++)
                {
                    cost[jindex][index] = cost[jindex + 1][index];
                }
            }
            for (index = row; index < (factory - 1); index++)
            {
                f_array[index] = f_array[index + 1];
            }
            factory--;
        }
        else if (is_factory == 0)
        {
            for (index = 0; index < factory; index++)
            {
                for (jindex = column; jindex < warehouse; jindex++)
                {
                    cost[index][jindex] = cost[index][jindex + 1];
                }
            }
            for (index = column; index < (warehouse - 1); index++)
            {
                w_array[index] = w_array[index + 1];
            }
            warehouse--;
        }
        //printf("After : factory = %d, warehouse = %d \n", factory, warehouse);
       
        //element_is_present++;
    
    }

    


    //Printing Part

    /*printf("\n");
    for (index = 0; index < factory; index++)
    {
        for (jindex = 0; jindex < warehouse; jindex++)
        {
            printf("%.1lf, ", cost[index][jindex]);   
        }
        printf("    |%.1lf|  %.1lf", f_array[index], f_diff_array[index]);
        printf("\n");
    }
    printf("\n");
    for (index = 0; index < warehouse; index++)
    {
        printf("%.1lf, ", w_array[index]);
    }
    printf("\n");
    printf("-------------------------------\n");
    for (index = 0; index < warehouse; index++)
    {
        printf("%.1lf, ", w_diff_array[index]);
    }
    printf("\n");
    printf("\nSum = %.1lf \n", sum);*/

    printf("Total Cost is %.1lf. \nAllocations = %d \n\n", sum, allocations);
    if ((degeneracy_checker) == allocations)
    {
        printf("(m + n - 1) = Allocations, \n(%d = %d), so.... \nThe solution is a non-degenerate basic feasible solution. \n\n", degeneracy_checker, allocations);
    }
    else if ((degeneracy_checker) > allocations)
    {
        printf("(m + n - 1) > Allocations, \n(%d > %d), so.... \nThe solution is degenerate. \n\n", degeneracy_checker, allocations);
    }
    
}

void csv_array_entry(double array[], int limit, FILE *file)
{
    int index;
    char *line[LINE_SIZE], *token;
    file = fgets(line, sizeof(line), file);
    token = strtok(line, ",");
    for (index = 0; index < limit; index++)
    {
        array[index] = atof(token);
        token = strtok(NULL, ",");
    }
    line[strcspn(line, "\n")] = 0;

    /*for (index = 0; index < limit; index++)
    {
        printf("%.1lf, ", array[index]);
    }
    printf("\n");*/
}

void manual_array_entry(double array[], int limit, char *name[100])
{
    int index;
    for (index = 0; index < limit; index++)
    {
        printf("Enter element %d of %s : ", index, name);
        scanf(" %lf", &array[index]);
    }

    /*for (index = 0; index < limit; index++)
    {
        printf("%.1lf, ", array[index]);
    }
    printf("\n");*/

}

int array_sum(double array[], int length)
{
    int index;
    double sum = 0;
    for (index = 0; index < length; index++)
    {
        sum+=array[index];
    }
    //printf("Sum = %.1lf, ", sum);
    return sum;
}

int max_finder(double array[], int limit)
{
    int index, location = -2;
    double max = -1;
    for (index = 0; index < limit; index++)
    {
        if (max <= array[index])
        {
            //printf("max = %.1lf, array[index] = %.1lf, location = %d ", max, array[index], location);
            max = array[index];
            location = index;
            printf("location = %d \n", location);
        }
    }
    printf("\n");
    return location;
}

