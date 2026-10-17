#include <stdio.h>
struct Node {
    char ch;
    int freq, left, right;
};
struct Node a[20];
int active[20], total = 0;
void printCodes(int root, int code[], int top) {
    if (a[root].left == -1 && a[root].right == -1) {
        printf("%c : ", a[root].ch);

        for (int i = 0; i < top; i++)
            printf("%d", code[i]);
            printf("\n");
        total += a[root].freq * top;
        return;
    }
    code[top] = 0;
    printCodes(a[root].left, code, top + 1);
    code[top] = 1;
    printCodes(a[root].right, code, top + 1);
}
int main() {
    char ch[] = {'a','c','d','e','o','m','s','t','u'};
    int f[] = {20,11,2,10,15,8,10,22,2};
    int n = 9, k = 9;
 for (int i = 0; i < n; i++) {
        a[i].ch = ch[i];
        a[i].freq = f[i];
        a[i].left = a[i].right = -1;
        active[i] = 1;
    }
    while (k < 2 * n - 1) {
        int x = -1, y = -1;
    for (int i = 0; i < k; i++) {
            if (active[i]) {
                if (x == -1 || a[i].freq < a[x].freq) {
                    y = x;
                    x = i;
                } else if (y == -1 || a[i].freq < a[y].freq) {
                    y = i;
                }
            }
        }

        a[k].ch = '$';
        a[k].freq = a[x].freq + a[y].freq;
        a[k].left = x;
        a[k].right = y;

        active[x] = active[y] = 0;
        active[k] = 1;
        k++;
    }
    int code[20];
    printf("Huffman Codes:\n");
    printCodes(k - 1, code, 0);
    printf("\nTotal bits = %d\n", total * 100);
    printf("Memory = %d bytes\n", total * 100 / 8);
    return 0;
}
