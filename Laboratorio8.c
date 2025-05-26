#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_LEN 30


// Dosal Ruiz Victor Manuel
typedef struct {
    char s1[MAX_LEN + 1];
    char s2[MAX_LEN + 1];
    bool result;
} MemoEntry;


MemoEntry memo[1000];
int memoSize = 0;



bool areAnagrams(const char *s1, const char *s2, int len) {
    int count[26] = {0};
    for (int i = 0; i < len; i++) {
        count[s1[i] - 'a']++;
        count[s2[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) return false;
    }
    return true;
}



bool isScrambleHelper(const char *s1, const char *s2, int len) {
    
    for (int i = 0; i < memoSize; i++) {
        if (strncmp(memo[i].s1, s1, len) == 0 && 
            strncmp(memo[i].s2, s2, len) == 0) {
            return memo[i].result;
        }
    }
    
    
    if (strncmp(s1, s2, len) == 0) {
        return true;
    }
    
    
    if (!areAnagrams(s1, s2, len)) {
        return false;
    }
    
   
    for (int i = 1; i < len; i++) {
        
        if (isScrambleHelper(s1, s2, i) && 
            isScrambleHelper(s1 + i, s2 + i, len - i)) {
            
            strncpy(memo[memoSize].s1, s1, len);
            strncpy(memo[memoSize].s2, s2, len);
            memo[memoSize].result = true;
            memoSize++;
            return true;
        }
        
        
        if (isScrambleHelper(s1, s2 + len - i, i) && 
            isScrambleHelper(s1 + i, s2, len - i)) {
            
            strncpy(memo[memoSize].s1, s1, len);
            strncpy(memo[memoSize].s2, s2, len);
            memo[memoSize].result = true;
            memoSize++;
            return true;
        }
    }
    
    
    strncpy(memo[memoSize].s1, s1, len);
    strncpy(memo[memoSize].s2, s2, len);
    memo[memoSize].result = false;
    memoSize++;
    return false;
}


bool isScramble(char *s1, char *s2) {
    int len = strlen(s1);
    if (len != strlen(s2)) return false;
    memoSize = 0; 
    return isScrambleHelper(s1, s2, len);
}



int main() {
    printf("Example 1: %d\n", isScramble("great", "great")); 
    printf("Example 2: %d\n", isScramble("abcde", "caebd")); 
    printf("Example 3: %d\n", isScramble("a", "a")); 
    return 0;
}
