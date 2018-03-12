#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dinArr2.h"

/*The function calculates the required number of cells multiple of 2
to accommodate a specified number of elements.*/
//It is not clear yet whether this function is needed separately.
int dinArr_calcSizeMalloc(int quantity)
{
    if(quantity == 1)
        return 2;
    else
    {
        int sizeMalloc = 1;
        while (sizeMalloc < quantity)
            sizeMalloc = sizeMalloc*2;

        return sizeMalloc;
    }
}

/*The function creates an empty dynamic array. Returns a pointer on it.*/
dinArr* dinArr_createNew()
{
    dinArr* ptrOnNew = malloc(sizeof(dinArr));
    ptrOnNew->size = 0;
    ptrOnNew->capacity = 0;
    ptrOnNew->arr = NULL;

    return ptrOnNew;
}

/*The function adds new elements in the end of dynamic array.*/
dinArr* dinArr_add(dinArr* prevArr)
{
    int quantityAdd;
    printf("How many items do you want to add to the array? ");
    scanf("%d", &quantityAdd);

    int requiredSize = prevArr->size + quantityAdd;
    printf("%d\n", requiredSize);

    if (prevArr->capacity < requiredSize)
    {
        dinArr* longerArr = dinArr_createNew();
        longerArr->arr = malloc(dinArr_calcSizeMalloc(requiredSize)*sizeof(longerArr->sizeItem));
        longerArr->capacity = dinArr_calcSizeMalloc(requiredSize);
        printf("Capacity: %d\n", longerArr->capacity);

        int i;
        for (i = 0; i < prevArr->size; i++)
        {
            void* elemPtr  = &prevArr->arr[i];
            //int tmp = (int*)prevArr->arr[i];
            printf("Before copying: %d\n", elemPtr);
            memcpy(&longerArr->arr[i], &prevArr->arr[i], prevArr->sizeItem);
            free(&prevArr->arr[i]);
            printf("Cell: %d, ", &longerArr->arr[i]);
            void* intPtr = &longerArr->arr[i];
            int *k;
            k = intPtr;
            printf("Cell contents: %d\n", *k);
            int j;
            for (j = 0; j < longerArr->size; j++)
            {
                printf("Cell: %d, ", &longerArr->arr[j]);
                void* intPtr = &longerArr->arr[j];
                int *k;
                k = intPtr;
                printf("Cell contents: %d\n", *k);
            }
        }

        longerArr->size = prevArr->size;
        for (i = prevArr->size; i < requiredSize; i++)
        {
            /*Stopgap measure. It is necessary to implement different input functions.*/
            int tmp;
            scanf("%d", &tmp);
            printf("Before copying: %d\n", tmp);
            /**/
            if (i>0)
            {
                void* itemPtr = &longerArr->arr[i-1];
                printf("previous item: %d\n", itemPtr);
            }


            memcpy(&longerArr->arr[i], &tmp, sizeof(tmp));
            free(&tmp);
            if (i>0)
            {
                void* itemPtr = &longerArr->arr[i-1];
                printf("previous item: %d\n", itemPtr);
            }


            longerArr->size++;
            int j;
            for (j = 0; j < longerArr->size; j++)
            {
                printf("Cell: %d, ", &longerArr->arr[j]);
                void* intPtr = &longerArr->arr[j];
                int *k;
                k = intPtr;
                printf("Cell contents: %d\n", *k);
            }
        }
        for (i = 0; i < longerArr->size; i++)
        {
            void* intPtr = &longerArr->arr[i];
            int *k;
            k = intPtr;
            printf("%d ", *k);
        }
        return longerArr;
    }
    else
    {
        int i;
        for (i = prevArr->size; i < requiredSize; i++)
        {
            /*Stopgap measure. It is necessary to implement different input functions.*/
            int tmp;
            scanf("%d", &tmp);
            /**/

            memcpy(&prevArr->arr[i], &tmp, sizeof(tmp));
            prevArr->size++;
        }
        for (i = 0; i < prevArr->size; i++)
        {
            void* intPtr = &prevArr->arr[i];
            int *k;
            k = intPtr;
            printf("%d ", *k);
        }
        return prevArr;
    }
}

/*Concatenation*/
dinArr* dinArr_concatenation (dinArr* arrA, dinArr* arrB)
{
    int requiredSize = arrA->size + arrB->size;
    printf("%d\n", requiredSize);

    if(arrA->capacity < requiredSize)
    {
        dinArr* newA = dinArr_createNew();
        newA->arr = malloc(dinArr_calcSizeMalloc(requiredSize)*sizeof(int));
        newA->capacity = dinArr_calcSizeMalloc(requiredSize);
        printf("%d\n", newA->capacity);

        int i;
        for (i = 0; i < arrA->size; i++)
            memcpy(&newA->arr[i], &arrA->arr[i], sizeof(arrA->arr[i]));
        newA->size = arrA->size;
        for (i = newA->size; i < requiredSize; i++)
            memcpy(&newA->arr[i], &arrB->arr[i-newA->size], sizeof(arrB->arr[i-newA->size]));
        newA->size = requiredSize;

        return newA;
    }
    else
    {
        int i;
        for(i = arrA->size; i < requiredSize; i++)
            memcpy(&arrA->arr[i], &arrB->arr[i-arrA->size], sizeof(arrB->arr[i-arrA->size]));
        arrA->size = requiredSize;

        return arrA;
    }
}


int main()
{
    int menu = -1;

    while(true)
    {
        printf("Press 1 to test the addition of elements to the array.\n");
        printf("Press 2 to test the concatenation of 2 arrays.\n");
        printf("Press 0 to exit the program.\n");

        scanf("%d", &menu);
        if (menu == 0)
            break;
        switch(menu)
        {
            case 1:
            {
                dinArr* curDinArr;
                curDinArr = dinArr_createNew();
                curDinArr->sizeItem = sizeof(int);


                curDinArr = dinArr_add(curDinArr);
                int i;
                int* A;
                A = (int*)curDinArr->arr;
                printf("Array elements: \n");
                for (i = 0; i < curDinArr->size; i++)
                    printf("%d ", A[i]);

                printf("my variant\n");
                for (i = 0; i < curDinArr->size; i++) {
                    void* intPtr = &curDinArr->arr[i];
                    int *k;
                    k = intPtr;
                    printf("%d ", *k);
                }

                printf("\n");
            }
            break;
            case 2:
            {
                dinArr* arrA;
                arrA = dinArr_createNew();
                arrA = dinArr_add(arrA);

                dinArr* arrB;
                arrB = dinArr_createNew();
                arrB = dinArr_add(arrB);

                arrA = dinArr_concatenation(arrA, arrB);
                free(arrB);

                int i;
                int* A;
                A = (int*)arrA->arr;
                for (i = 0; i < arrA->size; i++)
                    printf("%d", A[i]);

                printf("\n");
            }
            break;

            default:
                printf("ERROR: Not selected any of the text menu items.");
            break;
        }

    }
    return 0;
}
