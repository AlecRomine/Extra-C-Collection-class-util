//Alec Romine
//al411896
//KindredSpirits

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"


typedef struct Stack {
int *array;
int size;
int capacity;
} Stack;

int NodeCounter(node *a);
void Preorder(node *a, Stack *s);
void Postorder(node *a,Stack *s);
void push(Stack *s, int data);
node *createNode(int data);
Stack *createStack(int capacity);
Stack *destroyStack(Stack *s);


//Determines if trees are mirror images of each other
int isReflection(node *a, node *b)
{
    if(a == NULL && b == NULL)
        return 1;
    else if(a != NULL && b != NULL && a->data == b->data)
        return (isReflection(a->left,b->right) && isReflection(a->right,b->left));
    else
        return 0;
}
//Will produce a mirror image of a tree
node *makeReflection(node *root)
{
    node *mirror = NULL;

    if(root == NULL)
        return NULL;
    else
    {
        mirror = createNode(root->data);
        mirror->left = makeReflection(root->right);
        mirror->right = makeReflection(root->left);
        return mirror;
    }
}
//Find kindred spirits regardless of entry order
int kindredSpirits(node *a, node *b)
{
    int lenA, lenB ,i;
    Stack *s1,*s2,*s3,*s4;

    if(a == NULL && b == NULL)
        return 1;
    else if(a == NULL || b == NULL)
        return 0;

    lenA = NodeCounter(a);
    lenB = NodeCounter(b);

    if(lenA != lenB)
        return 0;

    s1 = createStack(lenA);
    s2 = createStack(lenB);
    s3 = createStack(lenA);
    s4 = createStack(lenB);


    //Transferring the preorder and postorder to stacks
    Preorder(a,s1);
    Postorder(b,s2);
    //Checking the other direction
    Preorder(b,s3);
    Postorder(a,s4);


    for(i=0;i<lenA;i++)
    {
        if(s1->array[i] != s2->array[i] && s3->array[i] != s4->array[i])
        {
           destroyStack(s1);
           destroyStack(s2);
           destroyStack(s3);
           destroyStack(s4);
            return 0;
        }
    }

    destroyStack(s1);
    destroyStack(s2);
    destroyStack(s3);
    destroyStack(s4);

return 1;
}
double difficultyRating(void)
{
   return 2;
}
double hoursSpent(void)
{
    return 10;
}
//Recursively counts nodes in trees
int NodeCounter(node *a)
{
   if(a == NULL)
        return 0;
   else
        return (1 + NodeCounter(a->left)+NodeCounter(a->right));

}
//Will push Preorder of BT to stack array
void Preorder(node *a, Stack *s)
{
    if(a != NULL)
    {
        push(s,a->data);
        Preorder(a->left,s);
        Preorder(a->right,s);
    }
    return;
}
//Will push Postorder of BT to stack array
void Postorder(node *a, Stack *s)
{
    if(a != NULL)
    {
        Postorder(a->left,s);
        Postorder(a->right,s);
        push(s,a->data);
    }
    return;
}
//Create Node Funct taken from notes
node *createNode(int data)
{
	node *n = malloc(sizeof(node));

	n->data = data;
	n->left = n->right = NULL;

	return n;
}
//Create stack Funct from notes
Stack *createStack(int capacity)
{
    Stack *s;
    if ((s = malloc(sizeof(Stack))) == NULL)
        return NULL;
    if ((s->array = malloc(sizeof(int) * capacity)) == NULL)
    {
            free(s);
            return NULL;
    }

    s->size = 0;
    s->capacity = capacity;
return s;
}
//Push Funct from notes
void push(Stack *s, int data)
{
s->array[ s->size++ ] = data;
return;
}
//Push funct from notes
Stack *destroyStack(Stack *s)
{
    if (s == NULL)
        return NULL;

    free(s->array);
    free(s);

return NULL;
}
