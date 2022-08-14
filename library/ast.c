#include "main/php.h"
#include "zend_types.h"
#include "ast.h"

#if defined(DEBUG)
#define AST_DEBUG(s, c, i) printf(s, c, i);
#else
#define AST_DEBUG(s, c, i)
#endif

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

static const char *ast_attr_to_string(int attr)
{
    switch (attr)
    {
    case ZEND_NOP:
        return "ZEND_NOP";
    case ZEND_ADD:
        return "ZEND_ADD";
    case ZEND_SUB:
        return "ZEND_SUB";
    case ZEND_MUL:
        return "ZEND_MUL";
    case ZEND_DIV:
        return "ZEND_DIV";
    case ZEND_MOD:
        return "ZEND_MOD";
    case ZEND_SL:
        return "ZEND_SL";
    case ZEND_SR:
        return "ZEND_SR";
    case ZEND_CONCAT:
        return "ZEND_CONCAT";
    case ZEND_BW_OR:
        return "ZEND_BW_OR";
    case ZEND_BW_AND:
        return "ZEND_BW_AND";
    case ZEND_BW_XOR:
        return "ZEND_BW_XOR";
    case ZEND_POW:
        return "ZEND_POW";
    case ZEND_BW_NOT:
        return "ZEND_BW_NOT";
    case ZEND_BOOL_NOT:
        return "ZEND_BOOL_NOT";
    case ZEND_BOOL_XOR:
        return "ZEND_BOOL_XOR";
    case ZEND_IS_IDENTICAL:
        return "ZEND_IS_IDENTICAL";
    case ZEND_IS_NOT_IDENTICAL:
        return "ZEND_IS_NOT_IDENTICAL";
    case ZEND_IS_EQUAL:
        return "ZEND_IS_EQUAL";
    case ZEND_IS_NOT_EQUAL:
        return "ZEND_IS_NOT_EQUAL";
    case ZEND_IS_SMALLER:
        return "ZEND_IS_SMALLER";
    case ZEND_IS_SMALLER_OR_EQUAL:
        return "ZEND_IS_SMALLER_OR_EQUAL";
    case ZEND_ASSIGN:
        return "ZEND_ASSIGN";
    case ZEND_ASSIGN_DIM:
        return "ZEND_ASSIGN_DIM";
    case ZEND_ASSIGN_OBJ:
        return "ZEND_ASSIGN_OBJ";
    case ZEND_ASSIGN_STATIC_PROP:
        return "ZEND_ASSIGN_STATIC_PROP";
    case ZEND_ASSIGN_OP:
        return "ZEND_ASSIGN_OP";
    case ZEND_ASSIGN_DIM_OP:
        return "ZEND_ASSIGN_DIM_OP";
    case ZEND_ASSIGN_OBJ_OP:
        return "ZEND_ASSIGN_OBJ_OP";
    case ZEND_ASSIGN_STATIC_PROP_OP:
        return "ZEND_ASSIGN_STATIC_PROP_OP";
    case ZEND_ASSIGN_REF:
        return "ZEND_ASSIGN_REF";
    case ZEND_QM_ASSIGN:
        return "ZEND_QM_ASSIGN";
    case ZEND_ASSIGN_OBJ_REF:
        return "ZEND_ASSIGN_OBJ_REF";
    case ZEND_ASSIGN_STATIC_PROP_REF:
        return "ZEND_ASSIGN_STATIC_PROP_REF";
    case ZEND_PRE_INC:
        return "ZEND_PRE_INC";
    case ZEND_PRE_DEC:
        return "ZEND_PRE_DEC";
    case ZEND_POST_INC:
        return "ZEND_POST_INC";
    case ZEND_POST_DEC:
        return "ZEND_POST_DEC";
    case ZEND_PRE_INC_STATIC_PROP:
        return "ZEND_PRE_INC_STATIC_PROP";
    case ZEND_PRE_DEC_STATIC_PROP:
        return "ZEND_PRE_DEC_STATIC_PROP";
    case ZEND_POST_INC_STATIC_PROP:
        return "ZEND_POST_INC_STATIC_PROP";
    case ZEND_POST_DEC_STATIC_PROP:
        return "ZEND_POST_DEC_STATIC_PROP";
    case ZEND_JMP:
        return "ZEND_JMP";
    case ZEND_JMPZ:
        return "ZEND_JMPZ";
    case ZEND_JMPNZ:
        return "ZEND_JMPNZ";
    case ZEND_JMPZNZ:
        return "ZEND_JMPZNZ";
    case ZEND_JMPZ_EX:
        return "ZEND_JMPZ_EX";
    case ZEND_JMPNZ_EX:
        return "ZEND_JMPNZ_EX";
    case ZEND_CASE:
        return "ZEND_CASE";
    case ZEND_CHECK_VAR:
        return "ZEND_CHECK_VAR";
    case ZEND_SEND_VAR_NO_REF_EX:
        return "ZEND_SEND_VAR_NO_REF_EX";
    case ZEND_CAST:
        return "ZEND_CAST";
    case ZEND_BOOL:
        return "ZEND_BOOL";
    case ZEND_FAST_CONCAT:
        return "ZEND_FAST_CONCAT";
    case ZEND_ROPE_INIT:
        return "ZEND_ROPE_INIT";
    case ZEND_ROPE_ADD:
        return "ZEND_ROPE_ADD";
    case ZEND_ROPE_END:
        return "ZEND_ROPE_END";
    case ZEND_BEGIN_SILENCE:
        return "ZEND_BEGIN_SILENCE";
    case ZEND_END_SILENCE:
        return "ZEND_END_SILENCE";
    case ZEND_INIT_FCALL_BY_NAME:
        return "ZEND_INIT_FCALL_BY_NAME";
    case ZEND_DO_FCALL:
        return "ZEND_DO_FCALL";
    case ZEND_INIT_FCALL:
        return "ZEND_INIT_FCALL";
    case ZEND_RETURN:
        return "ZEND_RETURN";
    case ZEND_RECV:
        return "ZEND_RECV";
    case ZEND_RECV_INIT:
        return "ZEND_RECV_INIT";
    case ZEND_SEND_VAL:
        return "ZEND_SEND_VAL";
    case ZEND_SEND_VAR_EX:
        return "ZEND_SEND_VAR_EX";
    case ZEND_SEND_REF:
        return "ZEND_SEND_REF";
    case ZEND_NEW:
        return "ZEND_NEW";
    case ZEND_INIT_NS_FCALL_BY_NAME:
        return "ZEND_INIT_NS_FCALL_BY_NAME";
    case ZEND_FREE:
        return "ZEND_FREE";
    case ZEND_INIT_ARRAY:
        return "ZEND_INIT_ARRAY";
    case ZEND_ADD_ARRAY_ELEMENT:
        return "ZEND_ADD_ARRAY_ELEMENT";
    case ZEND_INCLUDE_OR_EVAL:
        return "ZEND_INCLUDE_OR_EVAL";
    case ZEND_UNSET_VAR:
        return "ZEND_UNSET_VAR";
    case ZEND_UNSET_DIM:
        return "ZEND_UNSET_DIM";
    case ZEND_UNSET_OBJ:
        return "ZEND_UNSET_OBJ";
    case ZEND_FE_RESET_R:
        return "ZEND_FE_RESET_R";
    case ZEND_FE_FETCH_R:
        return "ZEND_FE_FETCH_R";
    case ZEND_EXIT:
        return "ZEND_EXIT";
    case ZEND_FETCH_R:
        return "ZEND_FETCH_R";
    case ZEND_FETCH_DIM_R:
        return "ZEND_FETCH_DIM_R";
    case ZEND_FETCH_OBJ_R:
        return "ZEND_FETCH_OBJ_R";
    case ZEND_FETCH_W:
        return "ZEND_FETCH_W";
    case ZEND_FETCH_DIM_W:
        return "ZEND_FETCH_DIM_W";
    case ZEND_FETCH_OBJ_W:
        return "ZEND_FETCH_OBJ_W";
    case ZEND_FETCH_RW:
        return "ZEND_FETCH_RW";
    case ZEND_FETCH_DIM_RW:
        return "ZEND_FETCH_DIM_RW";
    case ZEND_FETCH_OBJ_RW:
        return "ZEND_FETCH_OBJ_RW";
    case ZEND_FETCH_IS:
        return "ZEND_FETCH_IS";
    case ZEND_FETCH_DIM_IS:
        return "ZEND_FETCH_DIM_IS";
    case ZEND_FETCH_OBJ_IS:
        return "ZEND_FETCH_OBJ_IS";
    case ZEND_FETCH_FUNC_ARG:
        return "ZEND_FETCH_FUNC_ARG";
    case ZEND_FETCH_DIM_FUNC_ARG:
        return "ZEND_FETCH_DIM_FUNC_ARG";
    case ZEND_FETCH_OBJ_FUNC_ARG:
        return "ZEND_FETCH_OBJ_FUNC_ARG";
    case ZEND_FETCH_UNSET:
        return "ZEND_FETCH_UNSET";
    case ZEND_FETCH_DIM_UNSET:
        return "ZEND_FETCH_DIM_UNSET";
    case ZEND_FETCH_OBJ_UNSET:
        return "ZEND_FETCH_OBJ_UNSET";
    case ZEND_FETCH_LIST_R:
        return "ZEND_FETCH_LIST_R";
    case ZEND_FETCH_CONSTANT:
        return "ZEND_FETCH_CONSTANT";
    case ZEND_CHECK_FUNC_ARG:
        return "ZEND_CHECK_FUNC_ARG";
    case ZEND_EXT_STMT:
        return "ZEND_EXT_STMT";
    case ZEND_EXT_FCALL_BEGIN:
        return "ZEND_EXT_FCALL_BEGIN";
    case ZEND_EXT_FCALL_END:
        return "ZEND_EXT_FCALL_END";
    case ZEND_EXT_NOP:
        return "ZEND_EXT_NOP";
    case ZEND_TICKS:
        return "ZEND_TICKS";
    case ZEND_SEND_VAR_NO_REF:
        return "ZEND_SEND_VAR_NO_REF";
    case ZEND_CATCH:
        return "ZEND_CATCH";
    case ZEND_THROW:
        return "ZEND_THROW";
    case ZEND_FETCH_CLASS:
        return "ZEND_FETCH_CLASS";
    case ZEND_CLONE:
        return "ZEND_CLONE";
    case ZEND_RETURN_BY_REF:
        return "ZEND_RETURN_BY_REF";
    case ZEND_INIT_METHOD_CALL:
        return "ZEND_INIT_METHOD_CALL";
    case ZEND_INIT_STATIC_METHOD_CALL:
        return "ZEND_INIT_STATIC_METHOD_CALL";
    case ZEND_ISSET_ISEMPTY_VAR:
        return "ZEND_ISSET_ISEMPTY_VAR";
    case ZEND_ISSET_ISEMPTY_DIM_OBJ:
        return "ZEND_ISSET_ISEMPTY_DIM_OBJ";
    case ZEND_SEND_VAL_EX:
        return "ZEND_SEND_VAL_EX";
    case ZEND_SEND_VAR:
        return "ZEND_SEND_VAR";
    case ZEND_INIT_USER_CALL:
        return "ZEND_INIT_USER_CALL";
    case ZEND_SEND_ARRAY:
        return "ZEND_SEND_ARRAY";
    case ZEND_SEND_USER:
        return "ZEND_SEND_USER";
    case ZEND_STRLEN:
        return "ZEND_STRLEN";
    case ZEND_DEFINED:
        return "ZEND_DEFINED";
    case ZEND_TYPE_CHECK:
        return "ZEND_TYPE_CHECK";
    case ZEND_VERIFY_RETURN_TYPE:
        return "ZEND_VERIFY_RETURN_TYPE";
    case ZEND_FE_RESET_RW:
        return "ZEND_FE_RESET_RW";
    case ZEND_FE_FETCH_RW:
        return "ZEND_FE_FETCH_RW";
    case ZEND_FE_FREE:
        return "ZEND_FE_FREE";
    case ZEND_INIT_DYNAMIC_CALL:
        return "ZEND_INIT_DYNAMIC_CALL";
    case ZEND_DO_ICALL:
        return "ZEND_DO_ICALL";
    case ZEND_DO_UCALL:
        return "ZEND_DO_UCALL";
    case ZEND_DO_FCALL_BY_NAME:
        return "ZEND_DO_FCALL_BY_NAME";
    case ZEND_PRE_INC_OBJ:
        return "ZEND_PRE_INC_OBJ";
    case ZEND_PRE_DEC_OBJ:
        return "ZEND_PRE_DEC_OBJ";
    case ZEND_POST_INC_OBJ:
        return "ZEND_POST_INC_OBJ";
    case ZEND_POST_DEC_OBJ:
        return "ZEND_POST_DEC_OBJ";
    case ZEND_ECHO:
        return "ZEND_ECHO";
    case ZEND_OP_DATA:
        return "ZEND_OP_DATA";
    case ZEND_INSTANCEOF:
        return "ZEND_INSTANCEOF";
    case ZEND_GENERATOR_CREATE:
        return "ZEND_GENERATOR_CREATE";
    case ZEND_MAKE_REF:
        return "ZEND_MAKE_REF";
    case ZEND_DECLARE_FUNCTION:
        return "ZEND_DECLARE_FUNCTION";
    case ZEND_DECLARE_LAMBDA_FUNCTION:
        return "ZEND_DECLARE_LAMBDA_FUNCTION";
    case ZEND_DECLARE_CONST:
        return "ZEND_DECLARE_CONST";
    case ZEND_DECLARE_CLASS:
        return "ZEND_DECLARE_CLASS";
    case ZEND_DECLARE_CLASS_DELAYED:
        return "ZEND_DECLARE_CLASS_DELAYED";
    case ZEND_DECLARE_ANON_CLASS:
        return "ZEND_DECLARE_ANON_CLASS";
    case ZEND_ADD_ARRAY_UNPACK:
        return "ZEND_ADD_ARRAY_UNPACK";
    case ZEND_ISSET_ISEMPTY_PROP_OBJ:
        return "ZEND_ISSET_ISEMPTY_PROP_OBJ";
    case ZEND_HANDLE_EXCEPTION:
        return "ZEND_HANDLE_EXCEPTION";
    case ZEND_USER_OPCODE:
        return "ZEND_USER_OPCODE";
    case ZEND_ASSERT_CHECK:
        return "ZEND_ASSERT_CHECK";
    case ZEND_JMP_SET:
        return "ZEND_JMP_SET";
    case ZEND_UNSET_CV:
        return "ZEND_UNSET_CV";
    case ZEND_ISSET_ISEMPTY_CV:
        return "ZEND_ISSET_ISEMPTY_CV";
    case ZEND_FETCH_LIST_W:
        return "ZEND_FETCH_LIST_W";
    case ZEND_SEPARATE:
        return "ZEND_SEPARATE";
    case ZEND_FETCH_CLASS_NAME:
        return "ZEND_FETCH_CLASS_NAME";
    case ZEND_CALL_TRAMPOLINE:
        return "ZEND_CALL_TRAMPOLINE";
    case ZEND_DISCARD_EXCEPTION:
        return "ZEND_DISCARD_EXCEPTION";
    case ZEND_YIELD:
        return "ZEND_YIELD";
    case ZEND_GENERATOR_RETURN:
        return "ZEND_GENERATOR_RETURN";
    case ZEND_FAST_CALL:
        return "ZEND_FAST_CALL";
    case ZEND_FAST_RET:
        return "ZEND_FAST_RET";
    case ZEND_RECV_VARIADIC:
        return "ZEND_RECV_VARIADIC";
    case ZEND_SEND_UNPACK:
        return "ZEND_SEND_UNPACK";
    case ZEND_YIELD_FROM:
        return "ZEND_YIELD_FROM";
    case ZEND_COPY_TMP:
        return "ZEND_COPY_TMP";
    case ZEND_BIND_GLOBAL:
        return "ZEND_BIND_GLOBAL";
    case ZEND_COALESCE:
        return "ZEND_COALESCE";
    case ZEND_SPACESHIP:
        return "ZEND_SPACESHIP";
    case ZEND_FUNC_NUM_ARGS:
        return "ZEND_FUNC_NUM_ARGS";
    case ZEND_FUNC_GET_ARGS:
        return "ZEND_FUNC_GET_ARGS";
    case ZEND_FETCH_STATIC_PROP_R:
        return "ZEND_FETCH_STATIC_PROP_R";
    case ZEND_FETCH_STATIC_PROP_W:
        return "ZEND_FETCH_STATIC_PROP_W";
    case ZEND_FETCH_STATIC_PROP_RW:
        return "ZEND_FETCH_STATIC_PROP_RW";
    case ZEND_FETCH_STATIC_PROP_IS:
        return "ZEND_FETCH_STATIC_PROP_IS";
    case ZEND_FETCH_STATIC_PROP_FUNC_ARG:
        return "ZEND_FETCH_STATIC_PROP_FUNC_ARG";
    case ZEND_FETCH_STATIC_PROP_UNSET:
        return "ZEND_FETCH_STATIC_PROP_UNSET";
    case ZEND_UNSET_STATIC_PROP:
        return "ZEND_UNSET_STATIC_PROP";
    case ZEND_ISSET_ISEMPTY_STATIC_PROP:
        return "ZEND_ISSET_ISEMPTY_STATIC_PROP";
    case ZEND_FETCH_CLASS_CONSTANT:
        return "ZEND_FETCH_CLASS_CONSTANT";
    case ZEND_BIND_LEXICAL:
        return "ZEND_BIND_LEXICAL";
    case ZEND_BIND_STATIC:
        return "ZEND_BIND_STATIC";
    case ZEND_FETCH_THIS:
        return "ZEND_FETCH_THIS";
    case ZEND_SEND_FUNC_ARG:
        return "ZEND_SEND_FUNC_ARG";
    case ZEND_ISSET_ISEMPTY_THIS:
        return "ZEND_ISSET_ISEMPTY_THIS";
    case ZEND_SWITCH_LONG:
        return "ZEND_SWITCH_LONG";
    case ZEND_SWITCH_STRING:
        return "ZEND_SWITCH_STRING";
    case ZEND_IN_ARRAY:
        return "ZEND_IN_ARRAY";
    case ZEND_COUNT:
        return "ZEND_COUNT";
    case ZEND_GET_CLASS:
        return "ZEND_GET_CLASS";
    case ZEND_GET_CALLED_CLASS:
        return "ZEND_GET_CALLED_CLASS";
    case ZEND_GET_TYPE:
        return "ZEND_GET_TYPE";
    case ZEND_ARRAY_KEY_EXISTS:
        return "ZEND_ARRAY_KEY_EXISTS";
    case ZEND_MATCH:
        return "ZEND_MATCH";
    case ZEND_CASE_STRICT:
        return "ZEND_CASE_STRICT";
    case ZEND_MATCH_ERROR:
        return "ZEND_MATCH_ERROR";
    case ZEND_JMP_NULL:
        return "ZEND_JMP_NULL";
    case ZEND_CHECK_UNDEF_ARGS:
        return "ZEND_CHECK_UNDEF_ARGS";
    case ZEND_FETCH_GLOBALS:
        return "ZEND_FETCH_GLOBALS";
    case ZEND_VERIFY_NEVER_TYPE:
        return "ZEND_VERIFY_NEVER_TYPE";
    case ZEND_CALLABLE_CONVERT:
        return "ZEND_CALLABLE_CONVERT";
    default:
    {
        char *str = (char *)malloc(40);
        sprintf(str, "UNKNOWN: %d", attr);
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
    nast->attr = "";
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
            AST_DEBUG("list %s [%d]\n", nast->kind, i);
            nast->child[nast->children] = create_node_ast();
            parse(ast_list->child[i], nast->child[nast->children]);
            nast->children++;
        }
        else
        {
            AST_DEBUG("list %s [%d] not found\n", nast->kind, i);
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
            AST_DEBUG("as_list %s [%d]\n", nast->kind, i);
            nast->child[nast->children] = create_node_ast();
            parse(ast->child[i], nast->child[nast->children]);
            nast->children++;
        }
        else
        {
            AST_DEBUG("as_list %s [%d] not found\n", nast->kind, i);
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
            AST_DEBUG("decl %s [%d]\n", nast->kind, i);
            nast->child[nast->children] = create_node_ast();
            parse(ast->child[i], nast->child[nast->children]);
            nast->children++;
        }
        else
        {
            AST_DEBUG("decl %s [%d] not found\n", nast->kind, i);
        }
    }
}

void parse(zend_ast *ast, node_ast *nast)
{
    if (ast->kind == ZEND_AST_ZVAL)
    {
        nast->kind = ast_kind_to_string(ast->kind);
        nast->attr = ast_attr_to_string(ast->attr);
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
                sprintf(str, "%.2f", Z_DVAL_P(zv));
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
        nast->attr = ast_attr_to_string(ast->attr);
        nast->lineno = zend_ast_get_lineno(ast);
        parse_list(ast, nast);
        return;
    }

    nast->kind = ast_kind_to_string(ast->kind);
    nast->attr = ast_attr_to_string(ast->attr);
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
