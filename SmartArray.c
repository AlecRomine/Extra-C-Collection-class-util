//al411896
//Alec Romine
#include <stdio.h>
#include "SmartArray.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Create struct with array size >= 10
SmartArray *createSmartArray(int length)
{
    SmartArray *a = malloc(sizeof(SmartArray));

    if (a == NULL)
        return NULL;

    a->size = 0;
    a->capacity = (length < DEFAULT_INIT_LEN) ? DEFAULT_INIT_LEN : length;
    a->array = calloc(a->capacity, sizeof(char *));

    if (a->array == NULL)
    {
        free(a);
        return NULL;
    }
    else
        printf("-> Created new SmartArray of size %d.\n", a->capacity);

    return a;
}

// Free's all memory in struct
SmartArray *destroySmartArray(SmartArray *smarty)
{
    int i;

    if(smarty == NULL)
        return NULL;
    else    if (getSize(smarty) == 0)
        free(smarty);
        return NULL;


    for (i=0;i<getSize(smarty);i++)
    {
        free(smarty->array[i]);
    }

    free(smarty->array);
    free(smarty);
    smarty = NULL;

    return smarty;
}

// Allocates additional memory of given array length
SmartArray *expandSmartArray(SmartArray *smarty, int length)
{
    int i;
    char **newarray = calloc(length, sizeof(char*));

    if(smarty == NULL || length <= smarty->capacity)
    {
        free(newarray);
        return smarty;
    }
    else
    {
        for (i=0;i<getSize(smarty);i++)
        {
            newarray[i] = calloc((strlen(smarty->array[i])+1), sizeof(char));
            newarray[i] = smarty->array[i];
        }
        printf("-> Expanded SmartArray to size %d.\n", length);
        free(smarty->array);
        smarty->array = newarray;
        smarty->size = getSize(smarty);
        smarty->capacity = length;
    }

    return smarty;
}

// Free's excess memory
SmartArray *trimSmartArray(SmartArray *smarty)
{
    char **newarray = calloc(getSize(smarty), sizeof(char*));
    int i;

    if(newarray ==  NULL ||  smarty ==  NULL)
    {
        free(newarray);
        return NULL;
    }
    else if (getSize(smarty) < smarty->capacity)
    {
        for(i=0;i<getSize(smarty);i++)
        {
            newarray[i] = calloc((strlen(smarty->array[i])+1), sizeof(char));
            newarray[i] = smarty->array[i];
        }
        free(smarty->array);
        smarty->array = newarray;
        smarty->capacity = getSize(smarty);
        printf("-> Trimmed SmartArray to size %d.\n", getSize(smarty));
    }

    return smarty;
}

// Places string in next available position
char *put(SmartArray *smarty, char *str)
{
    if(str == NULL  ||  smarty == NULL)
    {
        return NULL;
    }
    else if (getSize(smarty) == smarty->capacity)
    {
        smarty = expandSmartArray(smarty, (smarty->capacity*2+1));
        smarty->array[getSize(smarty)] = calloc((strlen(str)+1), sizeof(char));
        strcpy(smarty->array[getSize(smarty)], str);
        smarty->size++;
    }
    else
    {
        smarty->array[getSize(smarty)] = calloc((strlen(str)+1), sizeof(char));
        strcpy(smarty->array[getSize(smarty)], str);
        smarty->size++;
    }

    return smarty->array[getSize(smarty)-1];
}

// Retrieves string at index
char *get(SmartArray *smarty, int index)
{
    if(smarty == NULL   ||  index > smarty->capacity ||  index < 0)
        return NULL;
    else
        return smarty->array[index];
}

// Replace a string at valid index
char *set(SmartArray *smarty, int index, char *str)
{
    char *a;

    if (smarty->capacity < index   ||  str == NULL    ||  index < 0)
    {
        free(a);
        return NULL;
    }
    else if(smarty->array[index] != NULL)
    {
        a = malloc(sizeof(char)*(strlen(str)+1));
        smarty->array[index] = a;
        strcpy(smarty->array[index], str);
    }
    else
        return NULL;

    return smarty->array[index];
}

// Add a string at valid index. Strings >= index shift up
char *insertElement(SmartArray *smarty, int index, char *str)
{
    int i, tempsize;


    if (smarty == NULL  ||  str == NULL ||  index < 0)
        return NULL;
    else if(getSize(smarty) == smarty->capacity)
    {
        tempsize = getSize(smarty);
        smarty = expandSmartArray(smarty,(smarty->capacity*2+1));
        smarty->array[tempsize] = calloc((strlen(str)+1), sizeof(char));
        for(i=tempsize;i>index;i--)
        {
            smarty->array[i] = smarty->array[i-1];
        }
        smarty->array[index] = calloc((strlen(str)+1), sizeof(char));
        strcpy(smarty->array[index],str);
    }
    else if (index > getSize(smarty))
    {

        smarty->array[getSize(smarty)] = calloc((strlen(str)+1), sizeof(char));
        strcpy(smarty->array[getSize(smarty)], str);
    }
    else if (getSize(smarty) > index)
    {
        smarty->array[getSize(smarty)] = calloc((strlen(str)+1), sizeof(char));

            for(i=getSize(smarty);i>index-1;i--)
            {
                smarty->array[i+1] = smarty->array[i];
            }
        smarty->array[index] = calloc((strlen(str)+1), sizeof(char));
        strcpy(smarty->array[index], str);
        smarty->size++;
    }

    return smarty->array[index];
}

// Removes string at index and shift remains down
int removeElement(SmartArray *smarty, int index)
{
    int i;

    if(smarty == NULL || index > getSize(smarty) || index < 0)
        return 0;
    else
    {

        for(i=index;i<(getSize(smarty)-1);i++)
        {
            smarty->array[i] = smarty->array[i+1];
        }

        smarty->size--;
    }
    return 1;
}

// Returns number of strings in struct
int getSize(SmartArray *smarty)
{
    if(smarty == NULL || smarty->array == NULL)
        return -1;
    else
        return smarty->size;
}

void printSmartArray(SmartArray *smarty)
{
    int i;

    if(smarty == NULL   ||  getSize(smarty) == 0)
    {
        printf("(empty array)\n");
    }
    else
    {
        for (i=0;i<getSize(smarty);i++)
        {
            printf("%s\n", smarty->array[i]);
        }
    }
    return;
}

double difficultyRating(void)
{
    return 4.5555;
}

double hoursSpent(void)
{
    return 30;
}

