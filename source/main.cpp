#include "../include/DLL.h"
#include "../include/DLL_htmlDump.h"
#include "../lib/parseArgs/parseArgs.h"


int main(int argc, char** argv)
{
    const char* logFileName = NULL;

    StrArgument strArgs[] = 
    {
        {"-o", "log_file", "The file all logs will be written to", &logFileName, false},
    };
    ConsoleArgs args = {sizeof(strArgs) / sizeof(strArgs[0]), strArgs};

    if (!parseArgs(argc, argv, &args))
        return -1;

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
    // listPushBack(&list, 50);
    // listPushBack(&list, 60);
    // listPushBack(&list, 70);
    // listPushBack(&list, 80);
    // listPushBack(&list, 90);
    // listPushFront(&list, 40);
    for (int i = 0; i < 50; i++)
    {
        // listPushBack(&list, i);
    }
    listChangeCapacity(&list, 3.0f);
    listInsertBefore(&list, 1, 15);
    genGraphDump(&list);
    // listDestructor(&list);
}