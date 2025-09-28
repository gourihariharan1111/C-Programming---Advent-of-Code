#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_STRING_LENGTH 25
#define MAX_ROW_NUMBER_COUNT 10

int isReportSafe(int report[], int n){
    
    // if the report array has only 1 or 2 values
    
    if (n <= 2) {
        return 1; 
    }

    int isIncreasing = 0; // checks if the values are increasing
    // IsIncreasing = 0: unset, -1: decreasing order, 1: increasing order
    int diff;

    for (int i = 0; i < n-1; i++) {
        diff = report[i+1] - report[i];

        // The report is unsafe because diff is 0 or greater than 3
        if (abs(diff) > 3 || diff == 0) {
            printf("The report is unsafe as the values differ by 0 or >3\n");
            return 0; 
        }
        
        // Check if the report is increasing or decreasing
        if (diff > 0) {
            if (isIncreasing == -1) {
                printf("The report is unsafe as the values were gradually decreasing previously\n");
                return 0; 
            }
            isIncreasing = 1;
        } else {
            if (isIncreasing == 1) {
                printf("The report is unsafe as the values were gradually increasing previously\n");
                return 0; 
            }
            isIncreasing = -1;
        }
    }
    printf("The report is safe \n");
    return 1; 
}

int isReportSafeWithOneLevelDampened(int report[], int n){
    for (int i = 0; i < n; i++) {
        int tempReport[MAX_ROW_NUMBER_COUNT]; //Report after removing 1 level 
        int idx = 0;

        // Copy all elements except the one at index i
        for (int j = 0; j < n; j++) {
            if (j != i) {
                tempReport[idx++] = report[j];
            }
        }

        if (isReportSafe(tempReport, idx)) {
            printf("The report is safe after removal of one level");
            return 1; 
        }
    }
    return 0; // Still unsafe
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL){
        printf("input.txt file cannot be opened\n");
        return 1;
    }

    char row[MAX_ROW_STRING_LENGTH];
    int report[MAX_ROW_NUMBER_COUNT];
    int count = 0;

    while(fgets(row, sizeof(row), fp) != NULL){
        memset(report, 0, sizeof(report));

        int size = 0;
        char *token = strtok(row, " \n");
        while(token != NULL && size < MAX_ROW_NUMBER_COUNT){
            report[size++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        if (isReportSafe(report, size)) {
            count++;
        } else if (isReportSafeWithOneLevelDampened(report, size)) {
            count++;
        }
    }

    printf("The number of reports that are safe is %d\n", count);
    fclose(fp);
    return 0;
}
