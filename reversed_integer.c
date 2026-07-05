/**
 * My Solution to: https://leetcode.com/problems/reverse-integer/
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>


static void reverse_char_array(char* s) {
    int l = 0;
    int r = (int)strlen(s) - 1;
    while (l < r) {
        char t = s[l];
        s[l] = s[r];
        s[r] = t;
        l++;
        r--;
    }
}

static int32_t parse_int32_or_zero(const char s[]) {
    if (!s) return 0;

    errno = 0;
    char *end = NULL;

    // Optional: reject empty/whitespace-only strings early
    while (isspace((unsigned char)*s)) s++;
    if (*s == '\0') return 0;

    long v = strtol(s, &end, 10);

    // Must consume the whole string (except trailing whitespace)
    while (end && isspace((unsigned char)*end)) end++;
    if (end == NULL || *end != '\0') return 0;

    // Overflow/underflow or other range errors
    if (errno == ERANGE) return 0;

    // Also ensure it fits int32 explicitly
    if (v < INT32_MIN || v > INT32_MAX) return 0;

    return (int32_t)v;
}

int reverse(int x) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", x);

    if (x > 0) {
        reverse_char_array(buffer);
    } else {
        char storeNeg = buffer[0];       // '-'
        char *buffer_neg = buffer + 1;  // digits part
        reverse_char_array(buffer_neg);
        buffer[0] = storeNeg;
    }

    return parse_int32_or_zero(buffer);
}

static void runTest(int x) {
    int ans = reverse(x);
    printf("reverse(%d) = %d\n", x, ans);
}

/*
    To run
        `gcc -std=c11 -O2 -Wall reversed_integer.c -o reversed_integer`
        `./reversed_integer`

*/
int main(void) {
    // LeetCode standard tests
    runTest(123);      // 321
    runTest(-123);     // -321
    runTest(120);      // 21
    runTest(-120);     // -21
    runTest(0);        // 0

    // Overflow-ish boundary checks (LeetCode expects 0 when overflow occurs)
    runTest(1534236469);  // 0
    runTest(-2147483648); // 0

    return 0;
}