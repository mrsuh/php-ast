#ifndef MRSUH_AST_H
#define MRSUH_AST_H

typedef struct _node_ast node_ast;

struct _node_ast {
	const char *kind;
	const char *attr;
	const char *value;
	int lineno;
	int children;
    node_ast *child[100];
};

node_ast *get_ast(char *input);

#endif
