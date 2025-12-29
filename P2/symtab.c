#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

typedef struct SymNode {
    char *name;
    TokenValue *val;
    struct SymNode *next;
} SymNode;

SymNode *head = NULL;

int sym_lookup(char *name, TokenValue **val) {
    SymNode *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            *val = current->val;
            return SYMTAB_OK;
        }
        current = current->next;
    }
    return SYMTAB_NOT_FOUND;
}

int sym_add(char *name, TokenValue **val) {
    TokenValue *dummy;
    if (sym_lookup(name, &dummy) == SYMTAB_OK) {
        return SYMTAB_DUPLICATE;
    }
    SymNode *node = (SymNode*) malloc(sizeof(SymNode));
    node->name = strdup(name);
    node->val = *val;
    node->next = head;
    head = node;
    return SYMTAB_OK;
}