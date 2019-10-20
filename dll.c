#include <stdio.h>
#include <stdlib.h>
//printReverse, AddBefore, recursion, DLL_Size, is_polindrom, reverse of the DLL
struct node
{
    int data;
    struct node *next;
    struct node *previous;
};
void DLL_pushStart(struct node **ppHead, int n);
void DLL_pushAfter(struct node **ppNode, int n);
void DLL_pushBefore(struct node **ppNode, int n);
void DLL_reverseDll(struct node **ppHead);
int DLL_size(struct node *ppHead);
void DLL_pushEnd(struct node **ppHead, int n);
struct node *DLL_new(int n);
void DLL_Print(struct node *head);
void DLL_printReverse(struct node *head);
void DLL_printReverseRecursion(struct node *head);
int DLL_isPolindrom(struct node *head);
int main()
{
    //91019
    struct node *head = DLL_new(1);
    DLL_pushStart(&head, 9);
    DLL_pushAfter(&(head->next), 5);
    DLL_pushEnd(&head, 2);
    DLL_pushBefore(&(head->next->next->next), 23);
    // DLL_Print(head);
    // printf("\n");
    // DLL_pushStart(&head, 5);
    // DLL_pushEnd(&head, 333);
    // DLL_pushBefore(&(head->next), 1);
    DLL_Print(head);
    DLL_reverseDll(&head);
    DLL_Print(head);
    // printf("Size of DLL = %d\n", DLL_size(head));
    // DLL_printReverseRecursion(head);
    // DLL_printReverse(head);
    // if(DLL_isPolindrom(head) == 1) printf("true\n");
    // else printf("false\n");
    return 0;
}

struct node *DLL_new(int n)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = n;
    newNode->previous = newNode->next = NULL;
    return newNode;
}

void DLL_pushStart(struct node **ppHead, int n)
{
    struct node *newNode = DLL_new(n);
    if (*ppHead == NULL)
    {
        *ppHead = newNode;
        return;
    }
    newNode->next = *ppHead;
    (*ppHead)->previous = newNode;

    (*ppHead) = newNode;
}

void DLL_pushBefore(struct node **ppNode, int n)
{
    struct node *newNode = DLL_new(n);
    if ((*ppNode) == NULL)
    {
        (*ppNode) = newNode;
        return;
    }
    newNode->previous = (*ppNode)->previous;
    newNode->next = (*ppNode);
    (*ppNode)->previous = newNode;
    if (newNode->previous != NULL)
    {
        newNode->previous->next = newNode;
    }
    else
    {
        (*ppNode) = newNode;
    }
}

void DLL_pushAfter(struct node **ppNode, int n)
{
    struct node *newNode = DLL_new(n);
    if (*ppNode == NULL)
    {
        *ppNode = newNode;
        return;
    }

    newNode->previous = *ppNode;
    newNode->next = (*ppNode)->next;

    (*ppNode)->next = newNode;
    if (newNode->next != NULL)
    {
        newNode->next->previous = newNode;
    }
}

void DLL_pushEnd(struct node **ppHead, int n)
{
    struct node *newNode = DLL_new(n);
    if ((*ppHead) == NULL)
    {
        *ppHead = newNode;
        return;
    }
    struct node *temp = *ppHead;
    while ((*ppHead)->next != NULL)
    {
        (*ppHead) = (*ppHead)->next;
    }
    (*ppHead)->next = newNode;
    newNode->previous = (*ppHead);
    (*ppHead) = temp;
}

void DLL_Print(struct node *head)
{
    while (head != NULL)
    {
        printf("%d => ", head->data);
        head = head->next;
    }
    printf("\n");
}

void DLL_printReverse(struct node *head)
{
    while (head->next != NULL)
    {
        head = head->next;
    }
    while (head != NULL)
    {
        printf("%d => ", head->data);
        head = head->previous;
    }
    printf("\n");
}

int DLL_size(struct node *ppHead)
{
    int counter = 0;
    while (ppHead != NULL)
    {
        counter++;
        ppHead = ppHead->next;
    }
    return counter;
}

void DLL_printReverseRecursion(struct node *ppHead)
{
    if (ppHead == NULL)
    {
        printf("\n");
        return;
    }
    printf("%d => ", ppHead->data);
    DLL_printReverseRecursion(ppHead->next);
}

int DLL_isPolindrom(struct node *head)
{
    struct node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    while (temp != head)
    {
        if (head->data == temp->data)
        {
            head = head->next;
            temp = temp->previous;
        }
        else
        {
            return 0;
        }
        
    }
    return 1;
}


void DLL_reverseDll(struct node **ppHead)
{
    if((*ppHead) == NULL)
    {
        return;
    }
    
    struct node * copy = *ppHead;
    while(copy->next != NULL)
    {
        copy = copy->next;
    }
    struct node * temp = copy;

    while(copy != NULL)
    {
        (*ppHead)= copy;
        (*ppHead)->next = copy->previous;
        (*ppHead)->previous = copy->next;
        copy = copy->previous;
        (*ppHead) = (*ppHead)->next;
    }
    (*ppHead) = temp;
    
    
}