#include <stdio.h>
#include <stdlib.h>

typedef struct dinArr dinArr;

/*Dynamic array itself*/
typedef struct dinArr{
    int* arr; //temporary type
    int size; //number of filled cells
    int capacity; //number of cells available now
}dinArr;

/*The function calculates the required number of cells multiple of 2
to accommodate a specified number of elements.*/
//It is not clear yet whether this function is needed separately.
int dinArr_calcSizeMalloc (int quantity)
{
    int sizeMalloc = 1;
    while (sizeMalloc < quantity)
        sizeMalloc = sizeMalloc*2;

    return sizeMalloc;
}

/*The function creates an empty dynamic array. Returns a pointer on it.*/
dinArr* dinArr_CreateNew()
{
    dinArr* ptrOnNew = malloc(sizeof(dinArr));
    ptrOnNew->size = 0;
    ptrOnNew->capacity = 0;
    ptrOnNew->arr = NULL;

    return ptrOnNew;
}

dinArr* dinArr_add(dinArr* prevArr)
{
    int quantityAdd;
    printf("Enter the dimensions of the array: ");
    scanf("%d", &quantityAdd);

    if (prevArr->capacity < (prevArr->size + quantityAdd))
    {

    }

}

int main()
{
    int sizeOfArray;
    printf("Enter the dimensions of the array: ");
    scanf("%d", &sizeOfArray);

    int nesseraryMemory;
    nesseraryMemory = dinArr_calcSizeMalloc(sizeOfArray);

    printf("%d\n", nesseraryMemory);

    dinArr* curDinArr;
    curDinArr = dinArr_CreateNew();

    /*Makes the array longer.*/
    curDinArr->arr = (int*)malloc(dinArr_calcSizeMalloc(sizeOfArray) * sizeof(int));
    curDinArr->capacity = dinArr_calcSizeMalloc(sizeOfArray);
    /**/

    int i;
    for (i = 0; i<sizeOfArray; i++)
    {
        printf("arr[%d] = ", i);
        printf("Enter data: ");
        scanf("%d", &curDinArr->arr[i]);
    }
    curDinArr->size = sizeOfArray;

    for (i = 0; i<sizeOfArray; i++)
        printf("%d ", curDinArr->arr[i]);




    return 0;
}
