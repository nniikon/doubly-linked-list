#ifndef DUMP_H
#define DUMP_H

#include "colors.h"

#ifdef DUMP_DEBUG
    #define DUMP_PRINT(...)                                             \
    do                                                                  \
    {                                                                   \
        fprintf(stderr, "file: %s line: %d\t\t", __FILE__, __LINE__);   \
        fprintf(stderr, __VA_ARGS__);                                   \
        fprintf(stderr, RESET);                                         \
    } while (0)

    #define DUMP_VALUE(...)     \
    do                          \
    {                           \
        fprintf(stderr, CYAN);  \
        DUMP_PRINT(__VA_ARGS__);\
    } while (0)

    #define DUMP_ERROR(...)     \
    do                          \
    {                           \
        fprintf(stderr, RED);   \
        DUMP_PRINT(__VA_ARGS__);\
    } while (0)

    #define DUMP_SUCCESS(...)   \
    do                          \
    {                           \
        fprintf(stderr, GREEN); \
        DUMP_PRINT(__VA_ARGS__);\
    } while (0)

    #define IF_DUMP_DEBUG(...) __VA_ARGS__
#else
    #define DUMP_PRINT(...)         do {} while(0)
    #define DUMP_VALUE(...)         do {} while(0)
    #define DUMP_ERROR(...)         do {} while(0)
    #define DUMP_SUCCESS(...)       do {} while(0)
    #define IF_DUMP_DEBUG(...)      do {} while(0)
#endif

#endif