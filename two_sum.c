/**
 * My Solution to: https://leetcode.com/problems/two-sum/
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

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Number numbers[numsSize];

    for (int i = 0; i < numsSize; i++) {
        numbers[i].num = nums[i];
        numbers[i].index = i;
    }

    qsort(numbers, numsSize, sizeof(Number), compare);

    int left = 0, right = numsSize - 1;
    while (left < right) {
        int sum = numbers[left].num + numbers[right].num;

        if (sum == target) {
            *returnSize = 2;
            int* result = (int*)malloc(*returnSize * sizeof(int));
            result[0] = numbers[left].index;
            result[1] = numbers[right].index;
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    *returnSize = 0;
    return NULL;
}

static void run_test(int* nums, int numsSize, int target) {
    int returnSize = 0;
    int* ans = twoSum(nums, numsSize, target, &returnSize);

    printf("nums=[");
    for (int i = 0; i < numsSize; i++) {
        printf("%d%s", nums[i], (i + 1 < numsSize) ? "," : "");
    }
    printf("], target=%d -> ", target);

    if (ans == NULL || returnSize == 0) {
        printf("no pair\n");
    } else {
        printf("[%d, %d]\n", ans[0], ans[1]);
    }

    free(ans);
}

/*
    Main function to test two sums implementation
    `gcc -std=c11 -O2 -Wall two_sum.c -o two_sums.out`
    followed by `./two_sums.out`
*/
int main(void) {
    int nums1[] = {2, 7, 11, 15};
    run_test(nums1, 4, 9);  // expected indices: [0,1]

    int nums2[] = {3, 2, 4};
    run_test(nums2, 3, 6);  // expected indices: [1,2]

    int nums3[] = {3, 3};
    run_test(nums3, 2, 6);  // expected indices: [0,1]

    int nums4[] = {1, 2, 3};
    run_test(nums4, 3, 100); // expected: no pair

    return 0;
}