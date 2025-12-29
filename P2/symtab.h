#ifndef SYMTAB_H
#define SYMTAB_H

#include "value.h"

#define SYMTAB_OK 0
#define SYMTAB_DUPLICATE 1
#define SYMTAB_NOT_FOUND 2

int sym_add(char *name, TokenValue **val);
int sym_lookup(char *name, TokenValue **val);

#endif