#include "../include/DLL.h"

#define DUMP_DEBUG
#include "../lib/dump.h"

const char *const DLL_ERROR_MSG[] =
{
    #define DEF_ERR(err, str) str,
    #include "../include/DLL_errors_codegen.h"
    #undef DEF_ERR
};


#define DUMP_AND_RETURN_ERROR(err)                                  \
    do                                                              \
    {                                                               \
        DUMP_ERROR("LIST ERROR: %s\n", DLL_ERROR_MSG[(int)err]);    \
        return err;                                                 \
    } while (0)                                                     \


#ifndef LIST_RELEASE
    #define VERIFY_DUMP_RETURN_ERROR(list)              \
    do                                                  \
    {                                                   \
        DLL_Error err = listVerify(list);               \
        if (err != DLL_ERR_OK)                          \
        {                                               \
            DUMP_AND_RETURN_ERROR(err);                 \
        }                                               \
    } while (0)
#else
    #define LIST_VERIFY_DUMP_RETURN_ERROR(list) do {} while(0)
#endif


DLL_Error listVerify(List* list)
{
    if (list == NULL)        DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_LIST_PASSED);
    if (list->data == NULL)  DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_DATA_ARRAY_PASSED);
    if (list->prev == NULL)  DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_PREV_ARRAY_PASSED);
    if (list->next == NULL)  DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_NEXT_ARRAY_PASSED);

    if (list->prev[-1] == INT32_MAX || list->prev[-1] >= list->listInfo.capacity)
        DUMP_AND_RETURN_ERROR(DLL_ERR_INVALID_HEAD_INDEX);

    if (list->next[-1] == INT32_MAX || list->next[-1] >= list->listInfo.capacity)
        DUMP_AND_RETURN_ERROR(DLL_ERR_INVALID_TAIL_INDEX);

    if (list->free == INT32_MAX || list->free >= list->listInfo.capacity)
        DUMP_AND_RETURN_ERROR(DLL_ERR_INVALID_FREE_INDEX);

    return DLL_ERR_OK;
}


DLL_Error listConstuctor_internal(List* list, FILE* logFile, DLL_InitInfo info)
{
    DUMP_PRINT("%s was initialized in %s function %s[%d]\n", 
                info.varName, info.fileName, info.funcName, info.lineNum);
    DUMP_PRINT("listConstuctor() started.\n");

    if (list == NULL)
        DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_LIST_PASSED);

    list->logFile = logFile;

    list->data = (elem_t*) calloc(sizeof(list->data[0]), DLL_DEFAULT_CAPACITY + 1);
    if (list->data == NULL)
    {
        DUMP_AND_RETURN_ERROR(DLL_ERR_MEMORY_ALLOCATION_FAILURE);
    }
    list->data++;

    list->prev = (int*) calloc(sizeof(list->prev[0]), DLL_DEFAULT_CAPACITY + 1);
    if (list->prev == NULL)
    {
        free(list->data);
        DUMP_AND_RETURN_ERROR(DLL_ERR_MEMORY_ALLOCATION_FAILURE);
    }
    list->prev++;

    list->next = (int*) calloc(sizeof(list->next[0]), DLL_DEFAULT_CAPACITY + 1);
    if (list->next == NULL)
    {
        free(list->data);
        free(list->prev);
        DUMP_AND_RETURN_ERROR(DLL_ERR_MEMORY_ALLOCATION_FAILURE);
    }
    list->next++;

    // Fill in arrays with info.
    for (unsigned int i = 0; i < DLL_DEFAULT_CAPACITY; i++)
    {
        list->prev[i] = DLL_PREV_POISON;
        list->next[i] = i + 1;
    }
    // Loop the next[] array.
    list->next[DLL_DEFAULT_CAPACITY - 1] = -1; 

    list->free = 0;
    list->data[-1] = -1;
    list->prev[-1] = -1;
    list->next[-1] = -1;
    list->listInfo.capacity = DLL_DEFAULT_CAPACITY;
    list->listInfo.size     = 0;
    list->listInfo.isSorted = true;

    DUMP_PRINT("listConstuctor() success.\n.");
    return DLL_ERR_OK;
}


DLL_Error listDestructor(List* list)
{
    DUMP_PRINT("listDestructor() started.\n");
    if (list == NULL) 
        DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_LIST_PASSED);

    if (list->next != NULL)
        free(list->next - 1);

    if (list->prev != NULL)
        free(list->prev - 1);

    if (list->data != NULL)
        free(list->data - 1);

    DUMP_PRINT("listDestructor() success.\n");

    return DLL_ERR_OK;
}


DLL_Error listInsertAfter(List* list, int index, elem_t value)
{
    DUMP_PRINT("listInsertAfter(%d, " ELEM_FORMAT ") started.\n", index, value);
    if (list == NULL)
        DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_LIST_PASSED);
    VERIFY_DUMP_RETURN_ERROR(list);

    int freeIndex = list->free;

    if (freeIndex >= list->listInfo.capacity - 2)
        listChangeCapacity(list, DLL_CAPACITY_MULTIPLIER);

    list->free = list->next[list->free];
    list->listInfo.size++;

    list->data[freeIndex] = value;
    list->prev[list->next[index]] = freeIndex;
    list->next[freeIndex] = list->next[index];
    list->prev[freeIndex] = index;

    list->next[index] = freeIndex;

    if (index == list->prev[-1])
    {
        list->prev[-1] = freeIndex;
        DUMP_VALUE("TAIL: %d\n", list->prev[-1]);
    }


    return DLL_ERR_OK;
}


DLL_Error listInsertBefore(List* list, int index, elem_t value)
{
    DUMP_PRINT("listInsertBefore(%d, " ELEM_FORMAT ") started.\n", index, value);
    if (list == NULL)
        DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_LIST_PASSED);
    VERIFY_DUMP_RETURN_ERROR(list);

    return listInsertAfter(list, list->prev[index], value);
}


DLL_Error listPushFront(List* list, elem_t value)
{
    DUMP_PRINT("listPushFront(" ELEM_FORMAT ") started.\n", value);
    if (list == NULL)
        DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_LIST_PASSED);
    VERIFY_DUMP_RETURN_ERROR(list);

    return listInsertAfter(list, -1, value);
}   


DLL_Error listPushBack(List* list, elem_t value)
{
    DUMP_PRINT("listPushFront(" ELEM_FORMAT ") started.\n", value);
    if (list == NULL)
        DUMP_AND_RETURN_ERROR(DLL_ERR_NULL_LIST_PASSED);
    VERIFY_DUMP_RETURN_ERROR(list);

    return listInsertBefore(list, -1, value);
}


/*static*/ DLL_Error listChangeCapacity(List* list, float multiplier)
{
    DUMP_PRINT("listChangeCapacity() started.\n");

    int newCapacity = (int)((float) list->listInfo.capacity * multiplier);

    elem_t* tempData = (elem_t*) calloc(sizeof(elem_t), newCapacity);
    if (tempData == NULL)
    {
        DUMP_AND_RETURN_ERROR(DLL_ERR_MEMORY_ALLOCATION_FAILURE);
    }

    int* tempNext = (int*) calloc(sizeof(int), newCapacity);
    if (tempData == NULL)
    {
        free(tempData);
        DUMP_AND_RETURN_ERROR(DLL_ERR_MEMORY_ALLOCATION_FAILURE);
    }

    int* tempPrev = (int*) calloc(sizeof(int), newCapacity);
    if (tempPrev == NULL)
    {
        free(tempData);
        free(tempNext);
        DUMP_AND_RETURN_ERROR(DLL_ERR_MEMORY_ALLOCATION_FAILURE);
    }

    list->data = tempData;
    list->next = tempNext;
    list->prev = tempPrev;

    // Fill in arrays with info.
    for (int i = list->free; i < newCapacity; i++)
    {
        list->prev[i] = DLL_PREV_POISON;
        list->next[i] = i + 1;
    }
    list->next[newCapacity - 1] = -1;

    list->listInfo.capacity = newCapacity;

    DUMP_PRINT("listChangeCapacity() success.\n");
    return DLL_ERR_OK;
}