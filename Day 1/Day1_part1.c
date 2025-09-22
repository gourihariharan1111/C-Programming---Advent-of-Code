#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main(){
    
    FILE *fp = fopen("Day1_part1_input.txt","r");
    if(fp == NULL){
        printf("input.txt file cannot be opened\n");
        return 1;
    }
    
    int list1[MAX], list2[MAX];
    int n = 0;
    
    //reate arrays from the input
    while(fscanf(fp,"%d %d", &list1[n], &list2[n]) == 2) {
        n++;
    }
    
    fclose(fp);
    
    //Sorting list1 and list2
    qsort(list1, n, sizeof(int), compare);
    qsort(list2, n, sizeof(int), compare);
    
    //Find total distance
    int total = 0;
    for(int i=0; i<n; i++){
        total += abs(list1[i]-list2[i]);
    }
    
    printf("Total distance: %d\n", total);
    return 0;
    
}