#ifndef DLL_HD5H3KR6V4_H
#define DLL_HD5H3KR6V4_H

#include <stdio.h>
#include "DLL_config.h"

enum DLL_Error 
{
    #define DEF_ERR(err, ...) DLL_ERR_ ## err,
    #include "DLL_errors_codegen.h"
    #undef DEF_ERR
};

struct DLL_ListInfo
{
    unsigned int capacity; 
    int size;
    bool isSorted;
};

struct DLL_InitInfo
{
    const char* fileName;
    const char* varName;
    const char* funcName;
    int lineNum;
};

struct List
{
    elem_t* data;
    int* prev;
    int* next;
    int free;
    DLL_ListInfo listInfo;
    DLL_InitInfo initInfo;
    FILE* logFile;
};

#define listConstuctor(list, file)\
    listConstuctor_internal(list, file, DLL_InitInfo{__FILE__, #list, __FUNCTION__, __LINE__})

DLL_Error listConstuctor_internal(List* list, FILE* logFile, DLL_InitInfo info);
DLL_Error listDestructor         (List* list);
DLL_Error listVerify             (List* list);
DLL_Error listDelete             (List* list, int index);
DLL_Error listInsertAfter        (List* list, int index, elem_t value);
DLL_Error listInsertBefore       (List* list, int index, elem_t value);
DLL_Error listPushFront          (List* list, elem_t value);
DLL_Error listPushBack           (List* list, elem_t value);
DLL_Error listChangeCapacity     (List* list, float multiplier);
DLL_Error listLinearize          (List* list);

#endif
