/**
 * My Solution to: https://leetcode.com/problems/3sum/
 */
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // malloc, free, qsort

typedef struct {
    int num;
    int index;
} Number;

int compare(const void* a, const void* b) {
    return ((Number*)a)->num - ((Number*)b)->num;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    //The memory allocation for this poblem in C is diffult to understand
    //The first thing to realize is that the return size just need to be 0 for the start
    //We increment the return size to count the number of triplets we find
    //Then at the end we allocate the memory
    *returnSize = 0;
    *returnColumnSizes = NULL;
    // This algorithm uses an iterative approach based on our two sum
    // We carry over the struct and comparison function
    // The key insight is that the target becomes the inverse of what ever number we have

    
    //First step is to convert numbs into our struct that way we can use that
     Number numbers[numsSize];

    for (int i = 0; i < numsSize; i++) {
        numbers[i].num = nums[i];
        numbers[i].index = i;
    }
    // sort values
    qsort(numbers, numsSize, sizeof(Number), compare);

    int capacity = 16;
    int count = 0;

    int **ret = malloc(capacity * sizeof(int*));
    int *colSizes = malloc(capacity * sizeof(int)); // store column size per row (will be 3)


    for (int i = 0; i < numsSize; i++) {
        if (i > 0 && numbers[i].num == numbers[i-1].num) continue;

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            int sum = numbers[i].num + numbers[left].num + numbers[right].num;

            if (sum == 0) {
                // grow if needed
                if (count == capacity) {
                    capacity *= 2;
                    ret = realloc(ret, capacity * sizeof(int*));
                    colSizes = realloc(colSizes, capacity * sizeof(int));
                }

                ret[count] = malloc(3 * sizeof(int));
                ret[count][0] = numbers[i].num;
                ret[count][1] = numbers[left].num;
                ret[count][2] = numbers[right].num;
                colSizes[count] = 3;
                count++;

                // skip duplicates for left/right so you don't generate duplicate triplets
                int leftVal = numbers[left].num;
                int rightVal = numbers[right].num;

                while (left < right && numbers[left].num == leftVal) left++;
                while (left < right && numbers[right].num == rightVal) right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }

    *returnSize = count;
    *returnColumnSizes = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) (*returnColumnSizes)[i] = colSizes[i];

    free(colSizes);
    // Optional: shrink ret to exact size
    // ret = realloc(ret, count * sizeof(int*));

    return ret;
}

static void run_test(int* nums, int numsSize) {
    int returnSize = 0;
    int* returnColumnSizes = NULL;

    int** ans = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);

    printf("nums=[");
    for (int i = 0; i < numsSize; i++) {
        printf("%d%s", nums[i], (i + 1 < numsSize) ? "," : "");
    }
    printf("] -> ");

    if (ans == NULL || returnSize == 0) {
        printf("[]\n");
    } else {
        printf("[");
        for (int i = 0; i < returnSize; i++) {
            // column size should be 3 for each triplet
            int col = returnColumnSizes ? returnColumnSizes[i] : 3;
            if (col < 3) col = 3;

            printf("[%d,%d,%d]%s",
                   ans[i][0], ans[i][1], ans[i][2],
                   (i + 1 < returnSize) ? "," : "");
        }
        printf("]\n");
    }

    // free returned structure
    for (int i = 0; ans != NULL && i < returnSize; i++) {
        free(ans[i]);
    }
    free(ans);
    free(returnColumnSizes);
}



/*
  Main function to test threeSum implementation

  gcc -std=c11 -O2 -Wall three_sum.c -o three_sums.out
  ./three_sums.out
*/
int main(void) {
    int nums1[] = {-1, 0, 1, 2, -1, -4};
    run_test(nums1, 6);

    int nums2[] = {0, 1, 1};
    run_test(nums2, 3);

    int nums3[] = {0, 0, 0};
    run_test(nums3, 3);

    int nums4[] = {1, 2, -2, -1};
    run_test(nums4, 4);

    return 0;
}