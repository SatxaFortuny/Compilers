#ifndef VALUE_H
#define VALUE_H
#include <stdbool.h>

typedef enum {
    TYPE_UNDEFINED,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_STRUCT
} TypeData;

typedef struct Token {
    char *name;            
    TypeData type;         
    union {
        int   i_val;
        float f_val;
        char *s_val;
        int   b_val;
    } value;
    
    struct Token *next;    
} Token;

typedef struct TokenValue {
    TypeData type;
    bool inicialized;
    union {
        int   i_val;
        float f_val;
        char *s_val;
        bool   b_val;
        struct Token *tokens;
    } value;
} TokenValue;

typedef struct TempValue {
    TypeData type;
    union {
        int   i_val;
        float f_val;
        char *s_val;
        bool  b_val;
        struct Token *tokens;
    } value;
} TempValue;
#endif