#include <stdio.h>

//DOSAL RUIZ VICTOR MANUEL

int trap(int* height, int heightSize) {
    if (heightSize == 0) return 0;
    
    int left = 0, right = heightSize - 1;
    int left_max = 0, right_max = 0;
    int water = 0;
    
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= left_max) {
                left_max = height[left];
            } else {
                water += left_max - height[left];
            }
            left++;
        } else {
            if (height[right] >= right_max) {
                right_max = height[right];
            } else {
                water += right_max - height[right];
            }
            right--;
        }
    }
    
    return water;
}

int main() {
    
    int height1[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int size1 = sizeof(height1)/sizeof(height1[0]);
    printf("Example 1 Output: %d\n", trap(height1, size1)); 
    
    
    int height2[] = {4,2,0,3,2,5};
    int size2 = sizeof(height2)/sizeof(height2[0]);
    printf("Example 2 Output: %d\n", trap(height2, size2)); 
    
    return 0;
}
