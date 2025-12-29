#ifndef VALUE_H
#define VALUE_H

typedef enum { 
    TYPE_INT, 
    TYPE_FLOAT 
} Type;


typedef struct {
    Type type;      
    int size;       
    int offset;     
    char *name;     
} TokenValue;


struct TempValue {
    Type type;
    char *addr;
    int is_const;
    float val;
};

#endif