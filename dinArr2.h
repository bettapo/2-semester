#ifndef DINARR2_H_INCLUDED
#define DINARR2_H_INCLUDED

/*Dynamic array itself*/
typedef struct{
    void* arr; //temporary type
    int size; //number of filled cells
    int capacity; //number of cells available now
    int sizeItem;
}dinArr;

#endif // DINARR2_H_INCLUDED
