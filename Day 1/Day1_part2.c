#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main(){
    
    FILE *fp = fopen("input.txt","r");
    if(fp == NULL){
        printf("input.txt file cannot be opened\n");
        return 1;
    }
    
    int list1[MAX], list2[MAX];
    int n = 0;
    
    // Create arrays from the input
    while(fscanf(fp,"%d %d", &list1[n], &list2[n]) == 2) {
        n++;
    }
    
    fclose(fp);
    
    // Sorting list1 and list2
    qsort(list1, n, sizeof(int), compare);
    qsort(list2, n, sizeof(int), compare);
    
    
    // Finding similarity Score
    int already_seen_list1_num = 0;
    int list1_num = 0;
    int similarity_score = 0;
    int count = 0;
    int list2_start_index = 0;
    
    // Iterate through sorted list1
    for(int i = 0; i < n; i++){
        list1_num = list1[i];
        
        // If count of occurrences of num in list2 is already calculated, 
        // just add it to the similarity score.
        if(already_seen_list1_num == list1_num){
          similarity_score += count*list1_num;
          continue;
        }
        else {
          already_seen_list1_num = list1_num;
        }
        
        // Iterate through list2 to count the number of occurrences of num.
        count = 0;
        int j = list2_start_index;
        
        // Skip all elements in list2 that are smaller than num
        while (j < n && list2[j] < list1_num) {
            j++;
        }
        
         // Count matching elements
        while (j < n && list2[j] == list1_num) {
            count++;
            j++;
        }
        
        list2_start_index = j;
        
        // Add the num * count of its occurences in list2 to similarity score.
        similarity_score += count*list1_num;
    }
    
    printf("Similarity Score: %d\n", similarity_score);
    return 0;
    
}