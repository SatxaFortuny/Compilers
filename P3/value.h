#ifndef VALUE_H
#define VALUE_H

typedef enum { 
    TYPE_INT, 
    TYPE_FLOAT,
    TYPE_BOOL
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

    struct ListInt *truelist;  
    struct ListInt *falselist; 
    struct ListInt *nextlist;  

    int instr;
};

struct ListInt {
    int instr;
    struct ListInt *next;
};

#endif