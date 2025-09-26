#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_STRING_LENGTH 25
#define MAX_ROW_NUMBER_COUNT 10

int isReportSafe(int report[], int n){
    
    // if the report array has only 1 or 2 values
    
    if (n <= 2) {
        printf("The report is safe \n");
        return 1;
    }
    
    int isIncreasing = 0; // checks if the values are increasing
    // IsIncreasing = 0: unset, -1: decreasing order, 1: increasing order
    int diff;

    for (int i = 0; i < n-1; i++){
        diff = report[i+1]-report[i];
        
        // The report is unsafe because diff is 0 or greater than 3
        if(abs(diff) > 3 || diff == 0){
            printf("The report is unsafe as the values differ by 0 or >3\n");
            return 0;
        }
        
        // Check if the report is increasing or decreasing
        if(diff > 0){
            if(isIncreasing == -1){
                printf("The report is unsafe as the values were gradually decreasing previously\n");
                return 0;
            }
            isIncreasing = 1;
        } else if(diff < 0){
            if(isIncreasing == 1){
                printf("The report is unsafe as the values were gradually increasing previously\n");
                return 0;
            }
            isIncreasing = -1;
        }
    }
    printf("The report is safe \n");
    return 1;
}

int main(){
  
  // Read the input
  FILE *fp = fopen("input.txt","r");
  if(fp == NULL){
    printf("input.txt file cannot be opened\n");
    return 1;
  }
  
  char row[MAX_ROW_STRING_LENGTH];
  int report[MAX_ROW_NUMBER_COUNT];
  int n = 0;
  int count = 0;
  
  // Read each row of input
  while(fgets(row, sizeof(row), fp) != NULL){
    
    // Reset report array to all zeroes
    memset(report, 0, sizeof(report));
    
    // Parse integers from row into report[]
    int size = 0;
    char *token = strtok(row, " \n");
    while(token != NULL && size < MAX_ROW_NUMBER_COUNT){
      report[size++] = atoi(token);
      token = strtok(NULL, " \n");
    }
    
    // Check if report is safe
    if(isReportSafe(report, size) == 1){
        count++;
    }
  }
  printf("The number of resports that are safe is %d", count);
  return 0;
  
}