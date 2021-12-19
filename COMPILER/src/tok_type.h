#ifndef TOK_TYPE_H
#define TOK_TYPE_H

typedef enum tok_type
{
    EOF_T,
    SEMICOLON_T,
    COMMA_T,
    BLANKID_T,
    ASSIGN_T,
    STAR_T,
    DIV_T,
    MINUS_T,
    PLUS_T,
    EQ_T,
    GE_T,
    GT_T,
    LBRACE_T,
    LE_T,
    LPAR_T,
    LSQ_T,
    LT_T,
    MOD_T,
    NE_T,
    NOT_T,
    AND_T,
    OR_T,
    RBRACE_T,
    RPAR_T,
    RSQ_T,
    PACKAGE_T,
    RETURN_T,
    ELSE_T,
    FOR_T,
    IF_T,
    VAR_T,
    INT_T,
    FLOAT32_T,
    BOOL_T,
    STRING_T,
    PRINT_T,
    PARSEINT_T,
    FUNC_T,
    CMDARGS_T,
    RESERVED_T,
    ID_T,
    INTLIT_T,
    REALLIT_T,
    STRLIT_T
} tok_type;

const char *tok_names[] = {
    "EOF",
    "SEMICOLON",
    "COMMA",
    "BLANKID",
    "ASSIGN",
    "STAR",
    "DIV",
    "MINUS",
    "PLUS",
    "EQ",
    "GE",
    "GT",
    "LBRACE",
    "LE",
    "LPAR",
    "LSQ",
    "LT",
    "MOD",
    "NE",
    "NOT",
    "AND",
    "OR",
    "RBRACE",
    "RPAR",
    "RSQ",
    "PACKAGE",
    "RETURN",
    "ELSE",
    "FOR",
    "IF",
    "VAR",
    "INT",
    "FLOAT32",
    "BOOL",
    "STRING",
    "PRINT",
    "PARSEINT",
    "FUNC",
    "CMDARGS",
    "RESERVED",
    "ID",
    "INTLIT",
    "REALLIT",
    "STRLIT",
};

#endif
