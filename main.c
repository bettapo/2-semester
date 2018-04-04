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
/*Only this function should allocate a new memory.*/
//Изменить функцию. Параметрически передавать в нее желаемый размер массива и размер 1 элемента.
dinArr* dinArr_createNew(int dimension, int sizeItem)
{
    dinArr* ptrOnNew = malloc(sizeof(dinArr));
    ptrOnNew->size = 0;
    ptrOnNew->capacity = dimension;
    ptrOnNew->arr = malloc(dimension*sizeItem);
    ptrOnNew->sizeItem = sizeItem;
    return ptrOnNew;
}
/*The function of adding an element to the end of the array.*/
dinArr* dinArr_pushBack(dinArr* prevArr, void* insertElement)
{
    if (prevArr->capacity < (prevArr->size+1))
    {
        dinArr* longerArr = dinArr_createNew(dinArr_calcSizeMalloc(prevArr->size+1), prevArr->sizeItem);//WARNING! Implicit allocation of memory.

        printf("Capacity: %d\n", longerArr->capacity);//Temporary line

        int i;
        for (i = 0; i < prevArr->size*prevArr->sizeItem; i+=prevArr->sizeItem)
            memcpy(&longerArr->arr[i], &prevArr->arr[i], prevArr->sizeItem);

        longerArr->size = prevArr->size;

        memcpy(&longerArr->arr[longerArr->size*longerArr->sizeItem], insertElement, longerArr->sizeItem);
        longerArr->size++;

        //free(prevArr); //We clear the memory, which we no longer need, because we identified a new one.
        //Здесь нельзя очищать память. Иначе нельзя делать вставку в тот же самый массив.
        return longerArr;
    }
    else
    {
        memcpy(&prevArr->arr[prevArr->size*prevArr->sizeItem], insertElement, prevArr->sizeItem);
        prevArr->size++;

        return prevArr;
    }
}
/*Concatenation*/
dinArr* dinArr_concatenation (dinArr* arrA, dinArr* arrB)
{
    int i;
    for(i = 0; i < arrB->size*arrB->sizeItem; i += arrB->sizeItem)
        arrA = dinArr_pushBack(arrA, &arrB->arr[i]);

    return arrA;
}
/*Map*/
void dinArr_map(dinArr* originalArr, dinArr* mapArr, int elemSize, void* (*ptrFunc)(void*, void*)) //Нужен ли int elemSize? или он заложен в mapArr
{
    int i;
    for(i = 0; i < originalArr->size; i++) //как правильно сделать этот цикл?
    {
        ptrFunc(dinArr_getAdressOfElementByIndex(originalArr, i), dinArr_getAdressOfElementByIndex(mapArr, i));
        mapArr->size++;
    }
}
/*Function of obtaining the address of a cell with a certain number i.*/
int dinArr_getAdressOfElementByIndex(dinArr* arr, int index)
{
    void* adress;
    adress = arr->arr;

    int i;
    if (index > 0)
        for (i = 1; i <= index; i++)
            adress += arr->sizeItem;
    return adress;
}
/*Where*/
void dinArr_where(dinArr* originalArr, dinArr* whereArr, int elemSize, bool* (*ptrFunc)(void*))
{
    printf("PONG\n");
    printf("First cell %d\n", originalArr->arr);
    int i;
    for (i = 0; i < originalArr->size; i++)
    {
        printf("Current cell: %d\n", dinArr_getAdressOfElementByIndex(originalArr, i));
        void* intPtr = dinArr_getAdressOfElementByIndex(originalArr, i);
        int *k;
        k = intPtr;
        printf("%d\n", *k);

        if (ptrFunc(dinArr_getAdressOfElementByIndex(originalArr, i)) == true)
        {
            whereArr = dinArr_pushBack(whereArr, intPtr);
            printf("Capacity changed: %d\n", whereArr->capacity);
            printf("Size changed: %d\n", whereArr->size);
        }
        for(i = 0; i < whereArr->size*whereArr->sizeItem; i+=whereArr->sizeItem )
        {
            void* intPtr = &whereArr->arr[i];
            int *k;
            k = intPtr;
            printf("%d ", *k);
        }

        printf("\n");
    }
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
        dinArr* longerArr = dinArr_createNew(dinArr_calcSizeMalloc(requiredSize), sizeof(int));

        printf("Capacity: %d\n", longerArr->capacity);

        int i;
        for (i = 0; i < prevArr->size; i++)
        {
            void* elemPtr  = &prevArr->arr[i];
            //int tmp = (int*)prevArr->arr[i];
            printf("Before copying: %d\n", elemPtr);
            memcpy(&longerArr->arr[i], &prevArr->arr[i], prevArr->sizeItem);
            //free(&prevArr->arr[i]);
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

        void* cp = longerArr->arr;
        int k;
        for (k = prevArr->size; k < requiredSize; k++)
        {
            int cin;
            printf("Enter data: ");
            scanf("%d", &cin);

            printf("Number of cell: %d\n", cp); //Проверка номера ячейки памяти
            memcpy(cp, &cin, longerArr->sizeItem);
            longerArr->size++;
            cp += longerArr->sizeItem;
            printf("Number of cell: %d\n", cp); //Проверка номера ячейки памяти

            int j;
            for (j = 0; j < longerArr->size*longerArr->sizeItem; j+=longerArr->sizeItem)
            {
                printf("Cell: %d, ", &longerArr->arr[j]);
                void* intPtr = &longerArr->arr[j];
                int *k;
                k = intPtr;
                printf("Cell contents: %d\n", *k);
            }
            printf("\n");
        }

        int j;
        for (j = 0; j < longerArr->size*longerArr->sizeItem; j+=longerArr->sizeItem)
        {
            printf("Cell: %d, ", &longerArr->arr[j]);
            void* intPtr = &longerArr->arr[j];
            int *k;
            k = intPtr;
            printf("Cell contents: %d\n", *k);
        }
        printf("\n");

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

void test_squaring(int* before, int* after)
{
    printf("Before: %d\n", before);
    printf("After: %d\n", after);
    int square;
    *after = (*before)*(*before);
}

bool test_divisibility(int* elem)
{
    bool result = false;
    if (*elem%3 == 0)
        result = true;
    return result;
}

int main()
{
    int menu = -1;

    while(true)
    {
        printf("Press 1 to test the addition of elements to the array.\n");
        printf("Press 2 to test the concatenation of 2 arrays.\n");
        printf("Press 3 to test the map function.\n");
        printf("Press 4 to test push back function.\n");
        printf("Press 0 to exit the program.\n");

        scanf("%d", &menu);
        if (menu == 0)
            break;
        switch(menu)
        {
            case 1:
            {
                dinArr* curDinArr;
                curDinArr = dinArr_createNew(0, sizeof(int));

                curDinArr = dinArr_add(curDinArr);

                printf("\n");
                printf("Temporary test\n");
                int i;
                for(i = 0; i < curDinArr->size*curDinArr->sizeItem; i+=curDinArr->sizeItem )
                    {
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
                arrA = dinArr_createNew(0, 0);
                arrA = dinArr_add(arrA);

                dinArr* arrB;
                arrB = dinArr_createNew(0,0);
                arrB = dinArr_add(arrB);

                arrA = dinArr_concatenation(arrA, arrB);
                free(arrB);

                int i;
                int* A;
                A = (int*)arrA->arr;
                for (i = 0; i < arrA->size; i++)
                    printf("%d ", A[i]);

                printf("\n");
            }
            break;
            case 3:
            {
                dinArr* curDinArr;
                curDinArr = dinArr_createNew(0, sizeof(int));
                //curDinArr->sizeItem = sizeof(int);


                curDinArr = dinArr_add(curDinArr);

                printf("\n");
                printf("Original array\n");
                int i;
                for(i = 0; i < curDinArr->size*curDinArr->sizeItem; i+=curDinArr->sizeItem )
                    {
                    void* intPtr = &curDinArr->arr[i];
                    int *k;
                    k = intPtr;
                    printf("%d ", *k);
                }

                dinArr* mappedArr;
                mappedArr = dinArr_createNew(curDinArr->capacity, sizeof(int));
                printf("PING\n");
                dinArr_map(curDinArr, mappedArr, sizeof(int), test_squaring);

                printf("\n");
                printf("Changed array\n");
                printf("Size of changed array: %d\n", mappedArr->size);
                printf("Capacity of changed array: %d\n", mappedArr->capacity);

                for(i = 0; i < mappedArr->size*mappedArr->sizeItem; i+=mappedArr->sizeItem )
                    {
                    void* intPtr = &mappedArr->arr[i];
                    int *k;
                    k = intPtr;
                    printf("%d ", *k);
                }

                printf("\n");
            }
            break;
            case 4:
            {
                dinArr* curDinArr;
                curDinArr = dinArr_createNew(0, sizeof(int));

                curDinArr = dinArr_add(curDinArr);

                printf("\n");
                printf("Temporary test\n");
                int i;
                for(i = 0; i < curDinArr->size*curDinArr->sizeItem; i+=curDinArr->sizeItem )
                    {
                    void* intPtr = &curDinArr->arr[i];
                    int *k;
                    k = intPtr;
                    printf("%d ", *k);
                }

                printf("\n");

                int elem = 1111;
                curDinArr = dinArr_pushBack(curDinArr, &elem);

                for(i = 0; i < curDinArr->size*curDinArr->sizeItem; i+=curDinArr->sizeItem )
                    {
                    void* intPtr = &curDinArr->arr[i];
                    int *k;
                    k = intPtr;
                    printf("%d ", *k);
                }

                printf("\n");
            }
            break;
            case 5:
            {
                dinArr* curDinArr;
                curDinArr = dinArr_createNew(0, sizeof(int));

                curDinArr = dinArr_add(curDinArr);

                printf("\n");
                printf("Original array\n");
                int i;
                for(i = 0; i < curDinArr->size*curDinArr->sizeItem; i+=curDinArr->sizeItem )
                {
                    void* intPtr = &curDinArr->arr[i];
                    int *k;
                    k = intPtr;
                    printf("%d ", *k);
                }

                dinArr* whereArr;
                whereArr = dinArr_createNew(0, sizeof(int));
                printf("\n");
                printf("Size of where array: %d\n", whereArr->size);
                printf("Capacity of where array: %d\n", whereArr->capacity);

                printf("PING\n");
                dinArr_where(curDinArr, whereArr, sizeof(int), test_divisibility);

                printf("\n");
                printf("Changed array\n");
                printf("Size of changed array: %d\n", whereArr->size);
                printf("Capacity of changed array: %d\n", whereArr->capacity);

                for(i = 0; i < whereArr->size*whereArr->sizeItem; i+=whereArr->sizeItem )
                    {
                    void* intPtr = &whereArr->arr[i];
                    int *k;
                    k = intPtr;
                    printf("%d ", *k);
                }

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
