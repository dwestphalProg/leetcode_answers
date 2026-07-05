/**
 * My Solution to: https://leetcode.com/problems/longest-palindromic-substring/description/
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>


/**
 * @brief Implementation of Manacher's string pre-processing
 * 
 * @param sString 
 * @return char* 
 */
char* preProcessString(const char* sString) {
    //Standard way of getting string length
    int n = (int)strlen(sString);
    // result length = 2*n + 3: '@' + '#' + chars + '#'+ '$' (actually: '@' + (# and chars) + '$')
    char* t = (char*)malloc((2 * n + 3) * sizeof(char));
    if (!t) return NULL;

    int k = 0;
    t[k++] = '@';
    for (int i = 0; i < n; i++) {
        t[k++] = '#';
        t[k++] = sString[i];
    }
    t[k++] = '#';
    t[k++] = '$';
    t[k] = '\0';

    return t;
}


char* longestPalindrome(char* s) {
    if (!s) return NULL;

    char* t = preProcessString(s);
    if (!t) return NULL;

    int n = (int)strlen(t);
    int* radii = (int*)calloc(n, sizeof(int));
    if (!radii) { free(t); return NULL; }

    int center = 0, right_border = 0;
    int max_radius = 0;
    int largest_center = 0;

    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;

        if (i < right_border) {
            radii[i] = radii[mirror];
            int limit = right_border - i;
            if (radii[i] > limit) radii[i] = limit;
        }

        while (i - 1 - radii[i] >= 0 &&
               i + 1 + radii[i] < n &&
               t[i - 1 - radii[i]] == t[i + 1 + radii[i]]) {
            radii[i]++;
        }

        if (i + radii[i] > right_border) {
            center = i;
            right_border = i + radii[i];
        }

        if (radii[i] > max_radius) {
            max_radius = radii[i];
            largest_center = i;
        }
    }

    // Map back to original string s:
    // In t, palindrome at largest_center with radius max_radius covers:
    // indices [largest_center - max_radius, largest_center + max_radius]
    // The start index in original s is (largest_center - max_radius) / 2
    int start = (largest_center - max_radius) / 2;
    int len = max_radius;

    char* ans = (char*)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++) ans[i] = s[start + i];
    ans[len] = '\0';

    free(radii);
    free(t);
    return ans;
}

static void runTest(char* x) {
    char* ans = longestPalindrome(x);
    printf("longestPalindrome(%s) = %s\n", x, ans);
}


/*
    To run
        `gcc -std=c11 -O2 -Wall longest_palindromic_substring.c -o longest_palindromic_substring`
        `./longest_palindromic_substring`

*/
int main(void) {
    // LeetCode standard tests
    char* testString;
    testString = "babad";
    runTest(testString);

    return 0;
}