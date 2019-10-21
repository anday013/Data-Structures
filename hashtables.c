#include <stdio.h>
#include <stdlib.h>

struct LLNode
{
    char *fName;
    char *lName;
    int age;
    struct LLNode *pNext;
};

struct LLNode *LL_new(char *fName, char *lName, int age)
{
    struct LLNode *newNode = (struct LLNode *)
        malloc(sizeof(struct LLNode));
    newNode->fName = fName;
    newNode->lName = lName;
    newNode->age = age;
    newNode->pNext = NULL;
    return newNode;
}

void LL_add(struct LLNode **ppHead, char *name, char *surname, int age)
{
    struct LLNode *newNode = LL_new(name, surname, age);
    newNode->pNext = *ppHead;
    *ppHead = newNode;
}

void LL_print(struct LLNode *pHead)
{
    struct LLNode *temp = pHead;
    if(pHead == NULL)
    {
        puts("");
        return;
    }
    
    while(pHead != NULL)
    {
        printf("[%s, %s, %d]=> ",pHead->fName,pHead->lName,pHead->age);
        pHead = pHead->pNext;
    }
    pHead = temp;
}

void LL_print(struct LLNode *pHead)
{
    struct LLNode *temp = pHead;
    if(pHead == NULL)
    {
        puts("");
        return;
    }
    
    while(pHead != NULL)
    {
        printf("* ");
        pHead = pHead->pNext;
    }
    pHead = temp;
}

void main()
{
}