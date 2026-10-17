#include <stdio.h>
#include <stdlib.h>
 
struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};
 
struct Node* createNode(char ch, int freq) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->ch = ch;
    temp->freq = freq;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
 
void printCodes(struct Node* root, int code[], int top) {
    if (root == NULL)
        return;
 
    if (root->left == NULL && root->right == NULL) {
        printf("%c : ", root->ch);
        for (int i = 0; i < top; i++)
            printf("%d", code[i]);
        printf("\n");
        return;
    }
 
    code[top] = 0;
    printCodes(root->left, code, top + 1);
 
    code[top] = 1;
    printCodes(root->right, code, top + 1);
}
 
int main() {
    int n, count;
    char ch[20];
    int freq[20];
    struct Node* nodes[40];
 
    printf("Enter number of characters: ");
    scanf("%d", &n);
 
    if (n < 2 || n > 20) {
        printf("Enter between 2 and 20 characters.\n");
        return 0;
    }
 
    for (int i = 0; i < n; i++) {
        printf("Enter character and frequency: ");
        scanf(" %c %d", &ch[i], &freq[i]);
 
        if (freq[i] <= 0) {
            printf("Frequency must be positive.\n");
            return 0;
        }
 
        nodes[i] = createNode(ch[i], freq[i]);
    }
 
    count = n;
 
    while (count > 1) {
        int min1 = -1, min2 = -1;
 
        for (int i = 0; i < count; i++) {
            if (min1 == -1 || nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (min2 == -1 ||
                       nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }
 
        struct Node* left = nodes[min1];
        struct Node* right = nodes[min2];
 
        struct Node* parent =
            createNode('$', left->freq + right->freq);
 
        parent->left = left;
        parent->right = right;
 
        if (min1 > min2) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }
 
        nodes[min1] = parent;
        nodes[min2] = nodes[count - 1];
        count--;
    }
 
    int code[20];
    printf("\nHuffman Codes:\n");
    printCodes(nodes[0], code, 0);
 
    return 0;
}
