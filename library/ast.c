#include "main/php.h"
#include "zend_types.h"
#include "ast.h"

static void parse(zend_ast *ast, node_ast *nast);

static const char *ast_kind_to_string(int kind)
{
    switch (kind)
    {
    case ZEND_AST_ZVAL:
        return "ZEND_AST_ZVAL";
        break;
    case ZEND_AST_CONSTANT:
        return "ZEND_AST_CONSTANT";
        break;
    case ZEND_AST_ZNODE:
        return "ZEND_AST_ZNODE";
        break;
    case ZEND_AST_FUNC_DECL:
        return "ZEND_AST_FUNC_DECL";
        break;
    case ZEND_AST_CLOSURE:
        return "ZEND_AST_CLOSURE";
        break;
    case ZEND_AST_METHOD:
        return "ZEND_AST_METHOD";
        break;
    case ZEND_AST_CLASS:
        return "ZEND_AST_CLASS";
        break;
    case ZEND_AST_ARROW_FUNC:
        return "ZEND_AST_ARROW_FUNC";
        break;
    case ZEND_AST_ARG_LIST:
        return "ZEND_AST_ARG_LIST";
        break;
    case ZEND_AST_ARRAY:
        return "ZEND_AST_ARRAY";
        break;
    case ZEND_AST_ENCAPS_LIST:
        return "ZEND_AST_ENCAPS_LIST";
        break;
    case ZEND_AST_EXPR_LIST:
        return "ZEND_AST_EXPR_LIST";
        break;
    case ZEND_AST_STMT_LIST:
        return "ZEND_AST_STMT_LIST";
        break;
    case ZEND_AST_IF:
        return "ZEND_AST_IF";
        break;
    case ZEND_AST_SWITCH_LIST:
        return "ZEND_AST_SWITCH_LIST";
        break;
    case ZEND_AST_CATCH_LIST:
        return "ZEND_AST_CATCH_LIST";
        break;
    case ZEND_AST_PARAM_LIST:
        return "ZEND_AST_PARAM_LIST";
        break;
    case ZEND_AST_CLOSURE_USES:
        return "ZEND_AST_CLOSURE_USES";
        break;
    case ZEND_AST_PROP_DECL:
        return "ZEND_AST_PROP_DECL";
        break;
    case ZEND_AST_CONST_DECL:
        return "ZEND_AST_CONST_DECL";
        break;
    case ZEND_AST_CLASS_CONST_DECL:
        return "ZEND_AST_CLASS_CONST_DECL";
        break;
    case ZEND_AST_NAME_LIST:
        return "ZEND_AST_NAME_LIST";
        break;
    case ZEND_AST_TRAIT_ADAPTATIONS:
        return "ZEND_AST_TRAIT_ADAPTATIONS";
        break;
    case ZEND_AST_USE:
        return "ZEND_AST_USE";
        break;
    case ZEND_AST_TYPE_UNION:
        return "ZEND_AST_TYPE_UNION";
        break;
    case ZEND_AST_TYPE_INTERSECTION:
        return "ZEND_AST_TYPE_INTERSECTION";
        break;
    case ZEND_AST_ATTRIBUTE_LIST:
        return "ZEND_AST_ATTRIBUTE_LIST";
        break;
    case ZEND_AST_ATTRIBUTE_GROUP:
        return "ZEND_AST_ATTRIBUTE_GROUP";
        break;
    case ZEND_AST_MATCH_ARM_LIST:
        return "ZEND_AST_MATCH_ARM_LIST";
        break;
    case ZEND_AST_MAGIC_CONST:
        return "ZEND_AST_MAGIC_CONST";
        break;
    case ZEND_AST_TYPE:
        return "ZEND_AST_TYPE";
        break;
    case ZEND_AST_CONSTANT_CLASS:
        return "ZEND_AST_CONSTANT_CLASS";
        break;
    case ZEND_AST_CALLABLE_CONVERT:
        return "ZEND_AST_CALLABLE_CONVERT";
        break;
    case ZEND_AST_VAR:
        return "ZEND_AST_VAR";
        break;
    case ZEND_AST_CONST:
        return "ZEND_AST_CONST";
        break;
    case ZEND_AST_UNPACK:
        return "ZEND_AST_UNPACK";
        break;
    case ZEND_AST_UNARY_PLUS:
        return "ZEND_AST_UNARY_PLUS";
        break;
    case ZEND_AST_UNARY_MINUS:
        return "ZEND_AST_UNARY_MINUS";
        break;
    case ZEND_AST_CAST:
        return "ZEND_AST_CAST";
        break;
    case ZEND_AST_EMPTY:
        return "ZEND_AST_EMPTY";
        break;
    case ZEND_AST_ISSET:
        return "ZEND_AST_ISSET";
        break;
    case ZEND_AST_SILENCE:
        return "ZEND_AST_SILENCE";
        break;
    case ZEND_AST_SHELL_EXEC:
        return "ZEND_AST_SHELL_EXEC";
        break;
    case ZEND_AST_CLONE:
        return "ZEND_AST_CLONE";
        break;
    case ZEND_AST_EXIT:
        return "ZEND_AST_EXIT";
        break;
    case ZEND_AST_PRINT:
        return "ZEND_AST_PRINT";
        break;
    case ZEND_AST_INCLUDE_OR_EVAL:
        return "ZEND_AST_INCLUDE_OR_EVAL";
        break;
    case ZEND_AST_UNARY_OP:
        return "ZEND_AST_UNARY_OP";
        break;
    case ZEND_AST_PRE_INC:
        return "ZEND_AST_PRE_INC";
        break;
    case ZEND_AST_PRE_DEC:
        return "ZEND_AST_PRE_DEC";
        break;
    case ZEND_AST_POST_INC:
        return "ZEND_AST_POST_INC";
        break;
    case ZEND_AST_POST_DEC:
        return "ZEND_AST_POST_DEC";
        break;
    case ZEND_AST_YIELD_FROM:
        return "ZEND_AST_YIELD_FROM";
        break;
    case ZEND_AST_CLASS_NAME:
        return "ZEND_AST_CLASS_NAME";
        break;
    case ZEND_AST_GLOBAL:
        return "ZEND_AST_GLOBAL";
        break;
    case ZEND_AST_UNSET:
        return "ZEND_AST_UNSET";
        break;
    case ZEND_AST_RETURN:
        return "ZEND_AST_RETURN";
        break;
    case ZEND_AST_LABEL:
        return "ZEND_AST_LABEL";
        break;
    case ZEND_AST_REF:
        return "ZEND_AST_REF";
        break;
    case ZEND_AST_HALT_COMPILER:
        return "ZEND_AST_HALT_COMPILER";
        break;
    case ZEND_AST_ECHO:
        return "ZEND_AST_ECHO";
        break;
    case ZEND_AST_THROW:
        return "ZEND_AST_THROW";
        break;
    case ZEND_AST_GOTO:
        return "ZEND_AST_GOTO";
        break;
    case ZEND_AST_BREAK:
        return "ZEND_AST_BREAK";
        break;
    case ZEND_AST_CONTINUE:
        return "ZEND_AST_CONTINUE";
        break;
    case ZEND_AST_DIM:
        return "ZEND_AST_DIM";
        break;
    case ZEND_AST_PROP:
        return "ZEND_AST_PROP";
        break;
    case ZEND_AST_NULLSAFE_PROP:
        return "ZEND_AST_NULLSAFE_PROP";
        break;
    case ZEND_AST_STATIC_PROP:
        return "ZEND_AST_STATIC_PROP";
        break;
    case ZEND_AST_CALL:
        return "ZEND_AST_CALL";
        break;
    case ZEND_AST_CLASS_CONST:
        return "ZEND_AST_CLASS_CONST";
        break;
    case ZEND_AST_ASSIGN:
        return "ZEND_AST_ASSIGN";
        break;
    case ZEND_AST_ASSIGN_REF:
        return "ZEND_AST_ASSIGN_REF";
        break;
    case ZEND_AST_ASSIGN_OP:
        return "ZEND_AST_ASSIGN_OP";
        break;
    case ZEND_AST_BINARY_OP:
        return "ZEND_AST_BINARY_OP";
        break;
    case ZEND_AST_GREATER:
        return "ZEND_AST_GREATER";
        break;
    case ZEND_AST_GREATER_EQUAL:
        return "ZEND_AST_GREATER_EQUAL";
        break;
    case ZEND_AST_AND:
        return "ZEND_AST_AND";
        break;
    case ZEND_AST_OR:
        return "ZEND_AST_OR";
        break;
    case ZEND_AST_ARRAY_ELEM:
        return "ZEND_AST_ARRAY_ELEM";
        break;
    case ZEND_AST_NEW:
        return "ZEND_AST_NEW";
        break;
    case ZEND_AST_INSTANCEOF:
        return "ZEND_AST_INSTANCEOF";
        break;
    case ZEND_AST_YIELD:
        return "ZEND_AST_YIELD";
        break;
    case ZEND_AST_COALESCE:
        return "ZEND_AST_COALESCE";
        break;
    case ZEND_AST_ASSIGN_COALESCE:
        return "ZEND_AST_ASSIGN_COALESCE";
        break;
    case ZEND_AST_STATIC:
        return "ZEND_AST_STATIC";
        break;
    case ZEND_AST_WHILE:
        return "ZEND_AST_WHILE";
        break;
    case ZEND_AST_DO_WHILE:
        return "ZEND_AST_DO_WHILE";
        break;
    case ZEND_AST_IF_ELEM:
        return "ZEND_AST_IF_ELEM";
        break;
    case ZEND_AST_SWITCH:
        return "ZEND_AST_SWITCH";
        break;
    case ZEND_AST_SWITCH_CASE:
        return "ZEND_AST_SWITCH_CASE";
        break;
    case ZEND_AST_DECLARE:
        return "ZEND_AST_DECLARE";
        break;
    case ZEND_AST_USE_TRAIT:
        return "ZEND_AST_USE_TRAIT";
        break;
    case ZEND_AST_TRAIT_PRECEDENCE:
        return "ZEND_AST_TRAIT_PRECEDENCE";
        break;
    case ZEND_AST_METHOD_REFERENCE:
        return "ZEND_AST_METHOD_REFERENCE";
        break;
    case ZEND_AST_NAMESPACE:
        return "ZEND_AST_NAMESPACE";
        break;
    case ZEND_AST_USE_ELEM:
        return "ZEND_AST_USE_ELEM";
        break;
    case ZEND_AST_TRAIT_ALIAS:
        return "ZEND_AST_TRAIT_ALIAS";
        break;
    case ZEND_AST_GROUP_USE:
        return "ZEND_AST_GROUP_USE";
        break;
    case ZEND_AST_CLASS_CONST_GROUP:
        return "ZEND_AST_CLASS_CONST_GROUP";
        break;
    case ZEND_AST_ATTRIBUTE:
        return "ZEND_AST_ATTRIBUTE";
        break;
    case ZEND_AST_MATCH:
        return "ZEND_AST_MATCH";
        break;
    case ZEND_AST_MATCH_ARM:
        return "ZEND_AST_MATCH_ARM";
        break;
    case ZEND_AST_NAMED_ARG:
        return "ZEND_AST_NAMED_ARG";
        break;
    case ZEND_AST_METHOD_CALL:
        return "ZEND_AST_METHOD_CALL";
        break;
    case ZEND_AST_NULLSAFE_METHOD_CALL:
        return "ZEND_AST_NULLSAFE_METHOD_CALL";
        break;
    case ZEND_AST_STATIC_CALL:
        return "ZEND_AST_STATIC_CALL";
        break;
    case ZEND_AST_CONDITIONAL:
        return "ZEND_AST_CONDITIONAL";
        break;
    case ZEND_AST_TRY:
        return "ZEND_AST_TRY";
        break;
    case ZEND_AST_CATCH:
        return "ZEND_AST_CATCH";
        break;
    case ZEND_AST_PROP_GROUP:
        return "ZEND_AST_PROP_GROUP";
        break;
    case ZEND_AST_PROP_ELEM:
        return "ZEND_AST_PROP_ELEM";
        break;
    case ZEND_AST_CONST_ELEM:
        return "ZEND_AST_CONST_ELEM";
        break;
    case ZEND_AST_CONST_ENUM_INIT:
        return "ZEND_AST_CONST_ENUM_INIT";
        break;
    case ZEND_AST_FOR:
        return "ZEND_AST_FOR";
        break;
    case ZEND_AST_FOREACH:
        return "ZEND_AST_FOREACH";
        break;
    case ZEND_AST_ENUM_CASE:
        return "ZEND_AST_ENUM_CASE";
        break;
    case ZEND_AST_PARAM:
        return "ZEND_AST_PARAM";
        break;

    default:
    {
        char *str = (char *)malloc(40);
        sprintf(str, "UNKNOWN: %d", kind);
        return str;
    }
    }
}

static bool zend_ast_kind_is_decl(zend_ast_kind kind)
{
    return kind == ZEND_AST_FUNC_DECL || kind == ZEND_AST_CLOSURE || kind == ZEND_AST_ARROW_FUNC || kind == ZEND_AST_METHOD || kind == ZEND_AST_CLASS;
}

static node_ast *create_node_ast()
{
    node_ast *nast = (node_ast *)malloc(sizeof(node_ast) - sizeof(node_ast *) + sizeof(node_ast *) * 100);
    nast->kind = "UNINITIALIZED";
    nast->value = "";
    nast->lineno = 0;
    nast->children = 0;

    return nast;
}

static void parse_list(zend_ast *ast, node_ast *nast)
{
    zend_ast_list *ast_list = zend_ast_get_list(ast);
    nast->children = 0;
    for (uint32_t i = 0; i < ast_list->children; i++)
    {
        if (ast_list->child[i])
        {
#if defined(DEBUG)
            printf("list %s [%d]\n", nast->kind, i);
#endif
            nast->child[nast->children] = create_node_ast();
            parse(ast_list->child[i], nast->child[nast->children]);
            nast->children++;
        }
        else
        {
#if defined(DEBUG)
            printf("list %s [%d] not found\n", nast->kind, i);
#endif
        }
    }
}

static void parse_as_list(zend_ast *ast, node_ast *nast)
{
    nast->children = 0;
    for (uint32_t i = 0; i < zend_ast_get_num_children(ast); i++)
    {
        if (ast->child[i])
        {
#if defined(DEBUG)
            printf("as_list %s [%d]\n", nast->kind, i);
#endif
            nast->child[nast->children] = create_node_ast();
            parse(ast->child[i], nast->child[nast->children]);
            nast->children++;
        }
        else
        {
#if defined(DEBUG)
            printf("as_list %s [%d] not found\n", nast->kind, i);
#endif
        }
    }
}

void parse_decl(zend_ast_decl *ast, node_ast *nast)
{
    nast->children = 0;
    for (uint32_t i = 0; i < 5; i++)
    {
        if (ast->child[i])
        {
#if defined(DEBUG)
            printf("decl %s [%d]\n", nast->kind, i);
#endif
            nast->child[nast->children] = create_node_ast();
            parse(ast->child[i], nast->child[nast->children]);
            nast->children++;
        }
        else
        {
#if defined(DEBUG)
            printf("decl %s [%d] not found\n", nast->kind, i);
#endif
        }
    }
}

void parse(zend_ast *ast, node_ast *nast)
{

    if (ast->kind == ZEND_AST_ZVAL)
    {
        nast->kind = ast_kind_to_string(ast->kind);
        nast->lineno = zend_ast_get_lineno(ast);

        zval *zv = zend_ast_get_zval(ast);
        if (zv)
        {
            switch (Z_TYPE_P(zv))
            {
            case IS_LONG:
            {
                char *str = (char *)malloc(40);
                sprintf(str, "%d", (int)Z_LVAL_P(zv));
                nast->value = str;
            }
            break;
            case IS_DOUBLE:
            {
                char *str = (char *)malloc(40);
                sprintf(str, "%d", (int)Z_DVAL_P(zv));
                nast->value = str;
            }
            break;
            case IS_STRING:
                nast->value = ZSTR_VAL(Z_STR_P(zv));
                break;
            default:
                nast->value = "UNKNOWN"; //@todo
            }
        }

        return;
    }

    if (zend_ast_kind_is_decl(ast->kind))
    {
        zend_ast_decl *decl = (zend_ast_decl *)ast;

        nast->kind = ast_kind_to_string(ast->kind);
        nast->lineno = zend_ast_get_lineno(ast);
        nast->value = decl->name->val;
        parse_decl(decl, nast);
        return;
    }

    if (zend_ast_is_list(ast))
    {
        nast->kind = ast_kind_to_string(ast->kind);
        nast->lineno = zend_ast_get_lineno(ast);
        parse_list(ast, nast);
        return;
    }

    nast->kind = ast_kind_to_string(ast->kind);
    nast->lineno = zend_ast_get_lineno(ast);
    parse_as_list(ast, nast);
}

zval *get_zval_by_name(char *name)
{

    HashTable *symbol_table = zend_array_dup(zend_rebuild_symbol_table());

    zend_string *key_name = zend_string_init(name, strlen(name), 0);
    zval *data = zend_hash_find(symbol_table, key_name);

    zend_string_release(key_name);
    zend_array_destroy(symbol_table);

    return data;
}

node_ast *get_ast(char *input)
{

    node_ast *nast = create_node_ast();

    zval *inputVal = get_zval_by_name(input);
    if (inputVal == NULL)
    {
        return nast;
    }

    zend_arena *ast_arena;
    zend_ast *ast = zend_compile_string_to_ast(Z_STR(*inputVal), &ast_arena, ZSTR_EMPTY_ALLOC());

    if (!ast)
    {
        return nast;
    }

    parse(ast, nast);

    return nast;
}
