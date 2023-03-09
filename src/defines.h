#include <stdio.h>
#include <stdlib.h>

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

#ifdef MRN_DEBUG
#define LOG_DEBUG(...) printf("[DEBUG]: "); printf(__VA_ARGS__); printf("\n")
#else
#define LOG_DEBUG(...)
#endif

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

#define mrn_malloc(var_name, size)                                                                                              \
    malloc(size);                                                                                                               \
    LOG_DEBUG("Allocated %li bytes to block '%s'", size, #var_name);                                                            \

#define mrn_free(block) {                                                                                                       \
    free(block);                                                                                                                \
    LOG_DEBUG("Freed block '%s' (%li bytes)", #block, sizeof(block));                                                           \
}

#define assign_ptr(dst, ptr) {                                                                                                  \
    ASSERT(dst != NULL, "Tried to assign block '%s' to unallotaced block '%s'.", #ptr, #dst);                                   \
    dst = ptr;                                                                                                                  \
    LOG_DEBUG("Assigned block '%s'%s to block '%s'", #ptr, (ptr == NULL) ? "(which is NULL)" : "", (#dst));                     \
}
