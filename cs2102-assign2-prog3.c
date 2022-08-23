/*
Name: Debprasad Kundu
Roll No.: cs2102
Date:30th January, 2022
Programme Description: print maximum Z pattern of a tree and count the turn
*/
#include <stdio.h>
#include <stdlib.h>

#define Malloc(n, type) ((type *)malloc(n * sizeof(type)))

void merge(int *A, int b, int m, int e)
{
    int i, j, p = m - b + 1, q = e - m, k;
    /* allocate spaces for auxiliary array  */
    int L[p], R[q];
    for (i = 0; i < p; i++)
        L[i] = A[b + i];
    for (j = 0; j < p; j++)
        R[j] = A[m + 1 + j];
    i = 0, j = 0, k = b;
    while (i < p && j < q)
    {
        if (L[i] <= R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }
    while (i < p)
        A[k++] = L[i++];
    while (j < q)
        A[k++] = R[j++];
}

void msort(int *A, int beginning, int end)
{
    if (beginning < end)
    {
        int middle;
        middle = (beginning + end) / 2;
        msort(A, beginning, middle);
        msort(A, middle + 1, end);
        merge(A, beginning, middle, end);
    }
}

int max(int arr[], int strt, int end)
{
    int i, max = arr[strt], maxind = strt;
    for (i = strt + 1; i <= end; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            maxind = i;
        }
    }
    return maxind;
}

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} BTNODE;

struct node *NewNode(int x) // Creating node
{
    struct node *ptr;
    if (NULL == (ptr = Malloc(1, BTNODE)))
        printf("Out of memory");
    ptr->data = x;
    ptr->left = NULL;
    ptr->right = NULL;
    return ptr;
}

struct node *buildTree(int inorder[], int start, int end){
    if (start > end)
        return NULL;
    int i = start + (end - start + 1) / 2;
    struct node *root = NewNode(inorder[i]);
    if (start == end)
        return root;
    root->left = buildTree(inorder, start, i - 1);
    root->right = buildTree(inorder, i+1 , end);
    return root;
}

void zigzag(struct node *root){
    int count1 = 0;
    struct node *temp = root;
    temp = root;
    while (NULL != temp){
        count1++;
        printf("%d ", temp->data);
        temp = temp->right;
        if (NULL != temp){
            count1++;
            printf("%d ", temp->data);
            temp = temp->left;
        }       
    }
    printf("\n%d",count1 - 1);
}

int main()
{
    int i, n;
    printf("Enter n : ");
    scanf("%d", &n);
    int inorder[n];
    printf("Enter elements : ");
    for (i = 0; i < n; i++)
        scanf("%d", &inorder[i]);
    msort(inorder, 0, n - 1);
    struct node *root = buildTree(inorder, 0, n - 1);
    struct node *temp = root;
    if(NULL == temp->right)
        printf("NIL");
    else
        zigzag(root);
    return 0;
}