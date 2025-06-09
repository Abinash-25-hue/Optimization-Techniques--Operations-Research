#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LINE_SIZE 1024



void main()
{
    //printf("\nHello World \n\n");

    int index, jindex, has_file, variables = 1, constraints = 1, condition = 1, flag = 0, table_count = 1;

    //Initialisation

    printf("\nDo you want to enter the data manually (0) or with a .csv file (1) : ");
    scanf("%d", &has_file);

    double Cj[100];
    double solutions[100], table[100][100];
    double Zj[100];
    //Cj = (double*)calloc(variables, sizeof(double));
    //solutions = (double*)calloc(variables, sizeof(double));
    //table = (double*)calloc((variables * constraints), sizeof(double));


    if (has_file == 1)
    {
        //printf("has_file = %d \n", has_file);
        char file_name[100];
        printf("\nEnter the file name : ");
        scanf(" %[^\n]", file_name);

        char *line[LINE_SIZE];
        FILE *file = fopen(file_name, "r");

        if (file == NULL)
        {
            perror("Error, file not found\n Try Again");
        }
        
        fgets(line, sizeof(line), file);
        char *token = strtok(line, ",");
        variables = atoi(token);
        token = strtok(NULL, ",");
        constraints = atoi(token);
        line[strcspn(line, "\n")] = 0;

        //printf("v = %d, c = %d \n", variables, constraints);

        //Cj = (double*)realloc(Cj, (variables + constraints));
        //solutions = (double*)realloc(solutions, (variables));

        fgets(line, sizeof(line), file);
        token = strtok(line, ",");
        for (index = 0; index < variables; index++)
        {
            Cj[index] = atof(token);
            //printf("%.1lf, ", Cj[index]);
            token = strtok(NULL, ",");
        }
        printf("\n");
        line[strcspn(line, "\n")] = 0;

        //table = (double*)realloc(table, (constraints * (variables + constraints)));
        for (index = 0; index < constraints; index++)
        {
            fgets(line, sizeof(line), file);
            line[strcspn(line, "\n")] = 0;
            token = strtok(line, ",");
            for (jindex = 0; jindex < variables; jindex++)
            {
                table[index][jindex] = atof(token);
                token = strtok(NULL, ",");
                //printf("%.1lf ", table[index][jindex]);
            }
            solutions[index] = atof(token);
            //printf("<= %.1lf \n", solutions[index]);  
            line[strcspn(line, "\n")] = 0;
        }
        //printf("\n");

        /*for (index = 0; index < (variables + constraints); index++)
        {
            printf("%.1lfk ", Cj[index]);
        }*/
    }
    else if (has_file == 0)
    {
        //printf("has_file = %d \n", has_file);

        printf("\nEnter the number of variables : ");
        scanf("%d", &variables);
        printf("Enter the number of constraints : ");
        scanf("%d", &constraints);
        printf("\n");

        for (index = 0; index < variables; index++)
        {
            printf("Enter element %d of Cj : ", (index + 1));
            scanf("%lf", &Cj[index]);
        }
        printf("\n");
        for (index = 0; index < constraints; index++)
        {
            for (jindex = 0; jindex < variables; jindex++)
            {
                printf("Enter the X%d of constraint %d : ", (jindex + 1), (index + 1));
                scanf("%lf", &table[index][jindex]);
            }
            printf("Enter the solution of constraint %d : ", (index + 1));
            scanf("%lf", &solutions[index]);
            printf("\n");
        }
        printf("\n");
    }


    //Working Part

    
    for (index = variables; index < (variables + constraints + 1); index++)
    {
        Cj[index] = 0;
    }
    for (index = 0; index < constraints; index++)
    {
        for (jindex = variables; jindex < (variables + constraints); jindex++)
        {
            table[index][jindex] = ((variables + index) == jindex)? 1: 0;
        }
    }

    char c_array[constraints];
    int n_array[constraints];
    double v_array[constraints];
    for (index = 0; index < constraints; index++)
    {  
        c_array[index] = 'S';
        n_array[index] = (index + 1);
        v_array[index] = 0;
    }
    
    int key_row, key_column;
    key_row = leaster(solutions, constraints, 1);
    for (index = 0; index < (variables + constraints); index++)
    {
        Zj[index] = ((Cj[index]) / (table[key_row][index]));
    }

    double key_row_array[(variables + constraints + 1)], key_column_array[(constraints + 1)], key_element;
    while (condition_checker(solutions, constraints) != 1)
    {
        while (flag == 1)
        {
            /*key_row = leaster(solutions, constraints, 1);
            for (index = 0; index < (variables + constraints); index++)
            {
                Zj[index] = ((Cj[index]) / (table[key_row][index]));
            }*/
            c_array[key_row] = 'X';
            //v_array[key_row] = 1;
            key_column = leaster(Zj, (variables + constraints), 0);
            n_array[key_row] = (key_column + 1);
            //printf("k_row = %d, k_col = %d \n", key_row, key_column);

            key_element = table[key_row][key_column];

            for (index = 0; index < (variables + constraints); index++)
            {
                key_row_array[index] = table[key_row][index];
            }
            key_row_array[index] = solutions[key_row];

            key_column_array[0] = Cj[key_column];
            for (index = 0; index < (constraints); index++)
            {
                key_column_array[index + 1] = table[index][key_column];
            }

            //array_printer (key_row_array, (variables + constraints + 1));
            //array_printer (key_column_array, (constraints + 1));
            //printf("k = %.1lf \nProcess : \n", key_element);

            for (index = 0; index < (variables + constraints); index++)
            {
                table[key_row][index] /= (key_element);
            }
            solutions[key_row] = solutions[key_row]/key_element;
            
            Cj[key_column] = 0;
            for (index = 0; index < constraints; index++)
            {
                if (index != key_row)
                {
                    table[index][key_column] = 0;
                }
            }

            for (index = 0; index < (variables + constraints); index++)
            {
                if (index != key_column)
                {
                    Cj[index] = Cj[index] - ((key_column_array[0] * key_row_array[index])/key_element);
                }
            }
            Cj[(variables + constraints)] = Cj[(variables + constraints)] - ((key_column_array[0] * key_row_array[(variables + constraints)])/ key_element);
            
            for (index = 0; index < constraints; index++)
            {
                if (index != key_row)
                {
                    for (jindex = 0; jindex < (variables + constraints); jindex++)
                    {
                        if (jindex != key_column)
                        {
                            //printf("t[%d][%d] = %.1lf ", index, jindex, table[index][jindex]);
                            table[index][jindex] = table[index][jindex] - ((key_row_array[jindex] * key_column_array[index + 1])/key_element);
                            //printf("- (%.1lf * %.1lf)/ %.1lf \n", key_row_array[jindex], key_column_array[index], key_element);
                        }
                    }
                }
            }

            for (index = 1; index < (constraints + 1); index++)
            {
                if (index != (key_row + 1))
                {
                    solutions[index - 1] = solutions[index - 1] - ((key_row_array[(variables + constraints)] * key_column_array[index])/ key_element);
                }
            }

            key_row = leaster(solutions, constraints, 1);
            for (index = 0; index < (variables + constraints); index++)
            {
                Zj[index] = ((Cj[index]) / (table[key_row][index]));
            }

            condition++;
            flag = 0;
        }

        while (flag == 0)
        {
            printf("\n\nIteration Table : %d \n\n    |", table_count);
            table_count++;
            for (index = 0; index < (variables + constraints); index++)
            {
                printf("%.1lf  ", Cj[index]);
            }
            printf("| %.1lf  \n-----------------------------------------------\n", Cj[(variables + constraints)]);
            for (index = 0; index < constraints; index++)
            {
                printf(" %c%d |  ", c_array[index], n_array[index]);
                for (jindex = 0; jindex < (variables + constraints); jindex++)
                {
                    printf("%.1lf   ", table[index][jindex]);
                }
                printf("| %.1lf \n", solutions[index]);
            }
            printf("-----------------------------------------------\n    |  ");
            for (index = 0; index < (variables + constraints); index++)
            {
                printf("%.1lf   ", Zj[index]);
            }
            printf("| \n");
            condition_checker(solutions, constraints);
            flag = 1;
        }
        
    }

    for (index = 0; index < constraints; index++)
    {
        if (c_array[index] == 'X')
        {
            //printf("f = %d, ", index);
            v_array[(n_array[index]) - 1] = solutions[index];
        }
    }
    printf("\n");
    //array_printer_int(n_array, constraints);
    //array_printer(v_array, constraints);
    printf("The value of Xs are : \n");
    for (index = 0; index < constraints; index++)
    {
        printf("X%d = %.1lf \n", (index + 1), v_array[index]);
    }
    printf("\nand Z = %.1lf \n\n", Cj[(variables + constraints)]);
    
}


int condition_checker (double array[], int length)
{
    int condition = 1;
    for (int index = 0; index < length; index++)
    {
        if (array[index] < 0)
        {
            condition = 0;
            //printf("i = %d ", index);
            break;
        }
    }
    //printf("condition = %d \n", condition);
    return condition;
}

int leaster (double array[], int length, int condition)
{
    // condition == 1, when the least number (including negative numbers) is to be found
    // condition == 0, when the least non-negative number is to be found 
    int location;
    double least = (condition == 1)? array[0]: 9999999999999;
    for (int index = 0; index < length; index++)
    {
        if ((array[index] <= least) && (condition == 1))
        {
            least = array[index];
            location = index;
        }
        else if ((array[index] <= least) && (array[index] > 0) && (condition == 0))
        {
            least = array[index];
            location = index;
        }
    }
    //printf("least = %.1lf, ", least);
    return location;
}


void array_printer (double array[], int length)
{
    for (int index = 0; index < length; index++)
    {
        printf("%.1lf, ", array[index]);
    }
    printf("\n");
}

void array_printer_int (int array[], int length)
{
    for (int index = 0; index < length; index++)
    {
        printf("%d, ", array[index]);
    }
    printf("\n");
}



