/* Ben Miller
 * 2019/11/17
 * Madness of temperature averages
 * */

#include <stdio.h>


int main(){


    //Open input file (check for errors)
    FILE* input_file = fopen("input_data.txt", "r");
    if (!input_file){ //Could also use condition "input_file == NULL"
        printf("Unable to open input file.\n");
        return 1;
    }

    //Open output file (check for errors)
    FILE* output_file = fopen("daily_averages_summary.txt", "w");
    if (!output_file){ //Could also use condition "output_file == NULL"
        printf("Unable to open output file.\n");
        return 1;
    }
    //make sure to make both dividend calendar and divisor calendar all zeroes in case this is done many times.

    float dividend_calendar[13][32];
    float divisor_calendar[13][32];

    for(int zero_rows = 0; zero_rows < 13; zero_rows++){
        for(int zero_cols = 0; zero_cols < 32; zero_cols++){
            dividend_calendar[zero_rows][zero_cols] = 0;
            divisor_calendar[zero_rows][zero_cols] = 0;
        }
    }

    //Read data and write output
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int station_number = 0;
    float temperature;
    while( fscanf(input_file, "%d %d %d %d %d %f", &month, &day, &hour, &minute, &station_number, &temperature) == 6 ){
        dividend_calendar[month][day] += temperature;
        divisor_calendar[month][day] += 1;
    }

    int rows = 0;
    int cols = 0;
    for(rows = 0; rows < 13; rows++){
        for(cols = 0; cols < 32; cols++){
            if(divisor_calendar[rows][cols] != 0){
                fprintf(output_file, "%d %d %.2f\n", rows, cols, (dividend_calendar[rows][cols] / divisor_calendar[rows][cols]));
            }
        }
    }

    //Close output file
    fclose(output_file);

    //Close input file
    fclose(input_file);

    return 0;
}
