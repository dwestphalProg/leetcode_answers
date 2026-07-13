/**
 * My Solution to: https://leetcode.com/problems/zigzag-conversion
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* convert(const char* s, int numRows) {
    int n = (int)strlen(s);
    if (numRows <= 1 || n <= 1) {
        char* out = (char*)malloc(n + 1);
        memcpy(out, s, n + 1);
        return out;
    }

    // Count how many chars go to each row
    int* counts = (int*)calloc(numRows, sizeof(int));
    int row = 0, dir = 1;
    for (int i = 0; i < n; i++) {
        counts[row]++;
        if (row == 0) dir = 1;
        else if (row == numRows - 1) dir = -1;
        row += dir;
    }

    // Allocate row buffers
    char** rows = (char**)malloc(numRows * sizeof(char*));
    for (int r = 0; r < numRows; r++) {
        rows[r] = (char*)malloc((size_t)counts[r] + 1);
        rows[r][0] = '\0';
    }

    // Fill row buffers
    int* idx = (int*)calloc(numRows, sizeof(int));
    row = 0; dir = 1;
    for (int i = 0; i < n; i++) {
        int k = idx[row]++;
        rows[row][k] = s[i];
        if (row == 0) dir = 1;
        else if (row == numRows - 1) dir = -1;
        row += dir;
    }

    for (int r = 0; r < numRows; r++) rows[r][counts[r]] = '\0';

    // Concatenate
    char* out = (char*)malloc((size_t)n + 1);
    int pos = 0;
    for (int r = 0; r < numRows; r++) {
        memcpy(out + pos, rows[r], (size_t)counts[r]);
        pos += counts[r];
        free(rows[r]);
    }
    out[pos] = '\0';

    free(rows);
    free(idx);
    free(counts);
    return out;
}



static void run_test(char* stringVal, int numRows) {
    char* ans = convert(stringVal, numRows);
    printf("%s\n", ans);
    free(ans);
}

/*
    Main function to test two sums implementation
    `gcc -std=c11 -O2 -Wall zig_zag_conversion.c -o zig_zag_conversion.out`
    followed by `./zig_zag_conversion.out`
*/
int main(void) {
    char* stringTest1 = "PAYPALISHIRING";
    int numRowsTest1 = 3;

    run_test(stringTest1, numRowsTest1);

    int numRowsTest2 = 4;
    run_test(stringTest1, numRowsTest2);

    return 0;
}