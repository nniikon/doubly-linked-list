#include "../include/DLL_htmlDump.h"

#define log(...) fprintf(list->logFile, __VA_ARGS__)

static void logNodeName(List* list, int i)
{
    if (i == -1)
        log("NODE_F");
    else
        log("NODE_%d", i);
}


void genGraphDump(List* list)
{
    if (list == NULL || list->logFile == NULL)
        return;
    log("digraph G{\n");
    log("rankdir = LR;\n");
    log("bgcolor = \"%s\"\n;", BG_CLR);
    log("subgraph cluster_list {\n");

    for (int i = -1; i < (int) list->listInfo.capacity; i++)
    {
        logNodeName(list, i);
        log(" [shape = Mrecord, style = filled, fillcolor = \"#ffe4c4\", ");
        log("color = \"%s\", label = \" INDX: %d | DATA: %d | NEXT: %d | PREV: %d \"];\n", 
            ARR_CLR, i, list->data[i], list->next[i], list->prev[i]);
    }

    for (int i = -1; i < (int) list->listInfo.capacity; i++)
    {
        logNodeName(list, i);
        if (i != (int) list->listInfo.capacity - 1)
            log(" -> ");
    }
    log("[color = \"%s\", weight = 0]\n", BG_CLR);

    for (int i = -1; i < (int) list->listInfo.capacity; i++)
    {
        logNodeName(list, i);
        log(" -> ");
        logNodeName(list, list->next[i]);
        const char* clr = NXT_CLR;
        if (list->prev[i] == DLL_PREV_POISON)
            clr = FRE_CLR;
        log(" [color = \"%s\", weight = 0]\n", clr);
    }
    log("\n");

    for (int i = -1; i < (int)  list->listInfo.capacity; i++)
    {
        if (list->prev[i] != DLL_PREV_POISON)
        {
            logNodeName(list, i);
            log(" -> ");
            logNodeName(list, list->prev[i]);
            log(" [color = \"%s\", weight = 0]\n", PRV_CLR);
        }
    }
    log("}\n");

    log("}");

}