#include <stdio.h>
#include <stdlib.h>



int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


long long teamChemistry(int* skill, int n) {
    if (n % 2 != 0) return -1; 
    
    qsort(skill, n, sizeof(int), compare); 


    int target = skill[0] + skill[n - 1]; 
    long long sum = 0; 


    for (int i = 0; i < n / 2; i++) {
        int pairSum = skill[i] + skill[n - 1 - i];
        if (pairSum != target) return -1; 
        
        sum += (long long)skill[i] * skill[n - 1 - i]; 
    }


    return sum;
}



int main() {
    int skill[] = {3, 2, 5, 7, 5, 8}; 
    int n = sizeof(skill) / sizeof(skill[0]);


    long long result = teamChemistry(skill, n);
    printf("%lld\n", result); 


    return 0;
}