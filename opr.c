#include <stdio.h>

int predict(int page[], int fr[], int pn, int index, int fn) {
    int i, j;
    int res = -1, farthest = index;
    for (i = 0; i < fn; i++) {
        for (j = index; j < pn; j++) {
            if (fr[i] == page[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}

int search(int key, int fr[], int fn) {
    int i;
    for (i = 0; i < fn; i++)
        if (fr[i] == key)
            return 1;
    return 0;
}

void opr(int page[], int pn, int fn) {
    int fr[fn];
    int i, hit = 0, index = 0;
    for (i = 0; i < fn; i++)
        fr[i] = -1; 

    for (i = 0; i < pn; i++) {
        if (search(page[i], fr, fn)) {
            hit++;
        } else {
            if (index < fn) {
                fr[index] = page[i];
                index++;
            } else {
                int j = predict(page, fr, pn, i + 1, fn);
                fr[j] = page[i];
            }
        }
    }
    printf("Hits = %d\n", hit);
    printf("Misses = %d\n", pn - hit);
}

int main() {
    int page[] = {1, 7, 8, 3, 0, 2, 0, 3, 5, 4, 0, 6, 1};
    int pn = sizeof(page) / sizeof(page[0]);
    int fn = 3;
    opr(page, pn, fn);
    return 0;
}
