#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *getStr() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

int getInt() {
    char *input = getStr();
    if (input == NULL) {
        free(input);
        return 0;
    }
    if (atoi(input) == 0){
        free(input);
        return 0;
    }
    int output = atoi(input);
    free(input);
    return output;
}
