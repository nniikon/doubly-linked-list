#include "../include/DLL.h"
#include "../include/DLL_htmlDump.h"


int main(int argc, char** argv)
{
    const char* logFileName = NULL;

    List list = {};

    FILE* logFile = NULL;
    if (logFileName != NULL)
    {
        logFile = fopen(logFileName, "w");
        if (logFile == NULL)
        {
            fprintf(stderr, "Error opening file.\n");
            return -1;
        }
    }

    listConstuctor(&list, logFile);

    for (int i = 0; i < 15; i++)
    {
        listPushBack(&list, i);
    }
    for (int i = 0; i < 15; i++)
    {
        listPushFront(&list, i);
    }

    listDelete(&list, 5);
    listLinearize(&list);

    genGraphDump(&list);
    listDestructor(&list);
}
