#include <stdio.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned char bool;
#define false 0
#define true 1

#define LOG_TRACE(...) printf("[TRACE]: "); printf(__VA_ARGS__); printf("\n")

#define LOG_INFO(...)  printf("[INFO]: "); printf(__VA_ARGS__); printf("\n")

#define LOG_WARN(...) printf("[WARN]: "); printf(__VA_ARGS__); printf("\n")

#define LOG_ERROR(...)  printf("[ERROR]: "); printf(__VA_ARGS__); printf("\n")

#define LOG_CRITICAL(...) printf("[CRITICAL]: "); printf(__VA_ARGS__); printf("\n")

#define ASSERT(cond, ...) {                                                                                                     \
    if(cond) {                                                                                                                  \
    } else {                                                                                                                    \
        LOG_CRITICAL("Assertion failed: '%s' on line %i in file '%s'.", #cond, __LINE__, __FILE__); LOG_CRITICAL(__VA_ARGS__);  \
        __builtin_trap();                                                                                                       \
    }                                                                                                                           \
}                                                                                                                               
