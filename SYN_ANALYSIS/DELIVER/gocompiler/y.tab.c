/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "gocompiler.y"

    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    void *array;
    size_t size, capacity, el_size;
} vector;

typedef struct _node
{
    int node_type;
    char *str;
    vector children;
} ast_node;
typedef ast_node *ast_ptr;

vector new_vector(size_t size_elem)
{
    vector ans;
    ans.size = ans.capacity = 0;
    ans.el_size = size_elem;
    ans.array = NULL;
    return ans;
}

void push_back(vector *vec, void *elem)
{
    if (vec->size == 0)
    {
        // printf("Boopb1\n");
        void *new_vec = malloc(vec->el_size);
        vec->array = new_vec;
        memcpy(vec->array, elem, vec->el_size);
        // printf("Boopb2\n");
        vec->capacity = 1;
        vec->size++;
        // printf("Boopb3\n");
        return;
    }
    if (vec->size >= vec->capacity)
    {
        void *new_vec = realloc(vec->array, 2 * vec->capacity * vec->el_size);
        // memcpy(new_vec, vec->array, vec->el_size * vec->capacity);
        vec->capacity *= 2;
        // free(vec->array);
        vec->array = new_vec;
    }

    memcpy(vec->array + vec->size * vec->el_size, elem, vec->el_size);
    vec->size++;
    // free(elem); //! might be problematic if the thing is static
}

void *get(vector *vec, int pos)
{
    if (pos >= (int)vec->size)
    {
        printf("Vec with no children...\n");
        return NULL;
    }
    return (char *)vec->array + vec->el_size * pos;
}

void set(vector *vec, size_t pos, void *val)
{
    if (vec->size <= pos || pos < 0)
    {
        fprintf(stderr, "Invalid set in vector\n");
        exit(0);
    }
    memcpy(vec->array + vec->el_size * pos, val, vec->el_size);
}

void pop_back(vector *vec)
{
    if (vec->size == 0)
        return;
    vec->size--;
    if (vec->size < vec->capacity / 4)
    {
        vec->array /*void *r*/ = realloc(vec->array, vec->el_size * vec->capacity / 2);
        vec->capacity /= 2;
        /*void *new_array = malloc(vec->el_size * vec->capacity);
        memcpy(new_array, vec->array, vec->capacity * vec->el_size);
        free(vec->array);
        vec->array = new_array;*/
    }
}

void test_vector()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector v = new_vector(sizeof(int));

    for (int x = 0; x < (int)(sizeof(a) / sizeof(int)); x++)
        push_back(&v, &a[x]);

    for (int i = 0; i < (int)v.size; i++)
    {
        printf("v[%d] = %d\n", i, (*(int *)get(&v, i)));
    }
    printf("%ld\n", v.capacity);
    for (int i = 0; i < 6; i++)
        pop_back(&v);
    for (int i = 0; i < (int)v.size; i++)
    {
        printf("v[%d] = %d\n", i, (*(int *)get(&v, i)));
    }
    printf("%ld\n", v.capacity);
}

ast_node new_node(int node_type, char *name)
{
    ast_node ans;
    ans.node_type = node_type;
    int f = strlen(name) + 2;
    ans.str = malloc(f * sizeof(char));
    strcpy(ans.str, name);
    ans.children = new_vector(sizeof(ast_node *));
    return ans;
}

ast_node *new_node_ptr(int node_type, char *name)
{
    ast_node *ans = malloc(sizeof(ast_node));
    ans->node_type = node_type;
    int f = strlen(name) + 2;
    ans->str = malloc(f * sizeof(char));
    strcpy(ans->str, name);
    ans->children = new_vector(sizeof(ast_node *));
    return ans;
}

void add_child(ast_node *node, ast_node **child)
{
    push_back(&(node->children), /*(void *)(**/ child);
    // printf("Add Child1\n");
    // ast_node **ch = (ast_node **)node->children.array + node->children.size - 1; // get(&(node->children), node->children.size - 1);
    // printf("Add Child2\n");
    // printf("Child: %s\n", (*child)->str);
    // printf("Child: %s\n", (*ch)->str);
}

void remove_child(ast_node *node)
{
    pop_back(&(node->children));
}

void free_ast_ptr(ast_ptr node)
{
    free(node->children.array);
    free(node);
}

void print_ast_tree(ast_node *node, int depth)
{
    /*if (node == NULL || node->children.size == 0)
        return;*/
    //     if(depth>5) return;
    for (int i = 0; i < depth; i++)
        printf("..");
    printf("%s\n", node->str);
    for (size_t i = 0; i < node->children.size; i++)
    {
        print_ast_tree(*((ast_node **)get(&(node->children), i)), depth + 1);
    }
}

void ast_test()
{
    ast_ptr a = new_node_ptr(0, "Father"), b = new_node_ptr(0, "Child1"), c = new_node_ptr(0, "Child2");
    // ast_node *f = &a, *g = &b, *h = &c;
    add_child(a, &b);
    add_child(a, &c);
    print_ast_tree(a, 0);
    strcpy(b->str, "Heir?");
    print_ast_tree(a, 0);
}

/*
int main()
{
    test_vector();
    ast_test();
    return 0;
}
*/
    #define true 1
    #define false 0
    #define P_NODE(a,b) push_node(a, #a, b)
    int yylex(void);
    void yyerror (const char *s);
    void decl() {
        printf("Declarations\n");
    }
    extern char* yytext;
    extern int prev_line, prev_col, yyleng;
    int syn_error = 0;
    typedef enum {
        Program, VarDecl, Int, Float32, Bool, String, FuncDecl, FuncHeader, FuncParams, ParamDecl, FuncBody, Block, 
        If, For, Return, ParseArgs, Print, IntLit, RealLit, Id, StrLit,
        Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod,
        Not, Minus, Plus, Assign, Call,
        Rep_Statement_Semicolon, Rep_Comma_Id, Vars_Statements, Rep_Comma_Expr, VarSpec
    } ast_node_type;

    vector stack;

    void push_node(int node_type, char* format, char* val) {
        char*name;
        if(node_type == IntLit || node_type == RealLit || node_type == StrLit || node_type == Id) {
            name = malloc(strlen(format)+strlen(val)+2);
            sprintf(name, format, val);
        }
        else {
            name = malloc(strlen(format)+2);
            strcpy(name, format);
        }
        ast_ptr n = new_node_ptr(node_type, name);
        push_back(&stack, &n);
        // printf("Pushing node %s\n", name);
        //printf("Stack size: %ld\n", stack.size);
        free(name);
    }

    void push_with_children(int node_type, char* name, int no_children) {
        ast_ptr n = new_node_ptr(node_type, name);
        for(size_t i = stack.size-no_children; i<stack.size; i++) {
            ast_ptr ch = *(ast_ptr*) get(&stack, i);
            add_child(n, &ch);
        }
        for(int i = 0; i<no_children; i++) pop_back(&stack);

        push_back(&stack, &n);
    }

    ast_ptr pop_node() {
        ast_ptr* ans = get(&stack, stack.size-1);
        if(ans == NULL) {
            fprintf(stderr, "No values in stack!\n");
            exit(-1);
        }
        pop_back(&stack);
        return *ans;
    }

    void print_top() {
        printf("Top:");
        ast_ptr* ans = get(&stack, stack.size-1);
        print_ast_tree(*ans, 0);
    }

    void handle_rep(int node_type, char* name, int no_children, int reverse) {
        //printf("AWDHKAGDJ\n");
        //printf("%s\n", name);
        ast_ptr n = pop_node(), aid = n;
        vector nodes = new_vector(sizeof(ast_ptr));
        vector to_free = new_vector(sizeof(ast_ptr));
        push_back(&to_free, &aid);
        //printf("Handling node %s; no_children: %d\n", name, no_children);
        while((int)aid->children.size > no_children) {
            if(!reverse) {
                for(int j = 0; j<no_children; j++) {
                    // printf("Boo1.1.1\n");
                    ast_ptr st_node = (*(ast_ptr*) get(&(aid->children), j));
                    //printf("Pushing node %s\n", st_node->str);
                    push_back(&nodes, &st_node);
                }
            }
            else {
                for(int j = no_children-1; j>0; j--) {
                    // printf("Boo1.1.1\n");
                    ast_ptr st_node = (*(ast_ptr*) get(&(aid->children), j));
                    //printf("Pushing node %s\n", st_node->str);
                    push_back(&nodes, &st_node);
                }
            }
            // printf("Boo1.2\n");
            aid = (*(ast_ptr*) get(&(aid->children),no_children));
            push_back(&to_free, &aid);
            // printf("Boo1.3\n");
        }
        // printf("Boo2\n");
        if(nodes.size > 1/*no_children*/) {
            // printf("Boo2.1\n");
            ast_ptr block_node = new_node_ptr(node_type, name);
            for(size_t i = 0; i<nodes.size; i++) {
                push_back(&(block_node->children), get(&nodes, i));
            }
            // printf("Boo2.2\n");
            push_back(&stack, &block_node);
        }
        // printf("Boo3\n");
        if(nodes.size == 1) push_back(&stack, get(&nodes, 0));
        // printf("Boo4\n");
        for(size_t i = 0; i< to_free.size; i++) {
            free_ast_ptr((*(ast_ptr*)get(&to_free, i)));
        }
        // printf("Boo5\n");
        free(nodes.array);
        // printf("Boo6\n");
        free(to_free.array);
        // printf("Boo7\n");
    }

    vector flat_children(ast_ptr node, int children, int reverse) {
        vector ans = new_vector(sizeof(ast_ptr));
        vector to_free = new_vector(sizeof(ast_ptr));
        ast_ptr cur = node;
        push_back(&to_free,&cur);
        while(cur->children.size > (size_t) children) {
            if(!reverse){
                for(int i = 0; i < children; i++) {
                push_back(&ans, get(&(cur->children), i));
            }
            }
            else {
                for(int i = children-1; i >= 0; i--) {
                push_back(&ans, get(&(cur->children), i));
            }
            }
            cur = *(ast_ptr*) get(&(cur->children), children);
            /*    RS
                /\ \  -> children 2
                S T RS
                /\
                S RS*/
            push_back(&to_free,&cur);
        }
        for(size_t i = 0; i< to_free.size; i++) {
            free_ast_ptr(*(ast_ptr*)get(&to_free, i));
        }
        free(to_free.array);
        return ans;
    }

    void yyerror(const char* s)
    {
        printf("Line %d, column %d: %s: %s\n", prev_line, prev_col,s, yytext);
        syn_error=1;
        // yyerrok;
    }

    void handle_blocks(ast_ptr node) {
        int t = node->node_type;
        for(size_t i = 0; i<node->children.size; i++) {
            handle_blocks(*(ast_ptr*)get(&(node->children), i));
        }
        if(t != If && t != For) {
            vector to_eliminate = new_vector(sizeof(int));
            for(size_t i = 0; i<node->children.size; i++) {
                ast_ptr ch = *(ast_ptr*)get(&(node->children), i);
                if(ch->node_type == Block) {
                    if(ch->children.size==1) {
                        ast_ptr grandson = *(ast_ptr*)get(&(ch->children),0);
                        set(&(node->children), i, &grandson);
                        free_ast_ptr(ch);
                        ch = grandson;
                    }
                    else if(ch->children.size == 0) {
                        push_back(&to_eliminate, &i);
                    }
                    
                }
            }
            push_back(&to_eliminate, &(node->children.size));
            if(to_eliminate.size>0) {
                vector new_children = new_vector(sizeof(ast_ptr));
                int pos1 = *(int*)get(&to_eliminate, 0), pos_aid = 0;
                for(int i = 0; i<(int)node->children.size; i++) {
                    if(i==pos1) {
                        free_ast_ptr(*(ast_ptr*)get(&(node->children), i));
                        pos_aid++;
                        pos1 = *(int*)get(&to_eliminate, pos_aid);
                        continue;
                    }
                    else {
                        push_back(&new_children, get(&(node->children), i));
                    }
                }
                free(node->children.array);
                node->children = new_children;
            }
        }
    } 


#line 460 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AND = 258,
    ASSIGN = 259,
    BLANKID = 260,
    BOOL = 261,
    CMDARGS = 262,
    COMMA = 263,
    DIV = 264,
    ELSE = 265,
    EQ = 266,
    FLOAT32 = 267,
    FOR = 268,
    FUNC = 269,
    GE = 270,
    GT = 271,
    ID = 272,
    IF = 273,
    INT = 274,
    INTLIT = 275,
    LBRACE = 276,
    LE = 277,
    LPAR = 278,
    LSQ = 279,
    LT = 280,
    MINUS = 281,
    MOD = 282,
    NE = 283,
    NOT = 284,
    OR = 285,
    PACKAGE = 286,
    PARSEINT = 287,
    PLUS = 288,
    PRINT = 289,
    RBRACE = 290,
    REALLIT = 291,
    RESERVED = 292,
    RETURN = 293,
    RPAR = 294,
    RSQ = 295,
    SEMICOLON = 296,
    STAR = 297,
    STRING = 298,
    STRLIT = 299,
    VAR = 300
  };
#endif
/* Tokens.  */
#define AND 258
#define ASSIGN 259
#define BLANKID 260
#define BOOL 261
#define CMDARGS 262
#define COMMA 263
#define DIV 264
#define ELSE 265
#define EQ 266
#define FLOAT32 267
#define FOR 268
#define FUNC 269
#define GE 270
#define GT 271
#define ID 272
#define IF 273
#define INT 274
#define INTLIT 275
#define LBRACE 276
#define LE 277
#define LPAR 278
#define LSQ 279
#define LT 280
#define MINUS 281
#define MOD 282
#define NE 283
#define NOT 284
#define OR 285
#define PACKAGE 286
#define PARSEINT 287
#define PLUS 288
#define PRINT 289
#define RBRACE 290
#define REALLIT 291
#define RESERVED 292
#define RETURN 293
#define RPAR 294
#define RSQ 295
#define SEMICOLON 296
#define STAR 297
#define STRING 298
#define STRLIT 299
#define VAR 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   220

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

#define YYUNDEFTOK  2
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   393,   393,   426,   427,   428,   430,   431,   433,   477,
     477,   478,   482,   486,   490,   495,   508,   523,   537,   549,
     556,   557,   559,   592,   627,   628,   629,   630,   632,   640,
     641,   643,   644,   645,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   668,   669,   671,   702,
     703,   705,   709,   713,   714,   715,   716,   717,   718,   719,
     720,   721,   722,   723,   724,   725,   726,   727,   728,   729,
     730,   731,   732,   733,   734,   735,   736,   737,   739,   743,
     747
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "ASSIGN", "BLANKID", "BOOL",
  "CMDARGS", "COMMA", "DIV", "ELSE", "EQ", "FLOAT32", "FOR", "FUNC", "GE",
  "GT", "ID", "IF", "INT", "INTLIT", "LBRACE", "LE", "LPAR", "LSQ", "LT",
  "MINUS", "MOD", "NE", "NOT", "OR", "PACKAGE", "PARSEINT", "PLUS",
  "PRINT", "RBRACE", "REALLIT", "RESERVED", "RETURN", "RPAR", "RSQ",
  "SEMICOLON", "STAR", "STRING", "STRLIT", "VAR", "$accept", "Program",
  "Declarations", "VarDeclaration", "VarSpec", "REP_COMMA_ID", "Type",
  "FuncDeclaration", "FuncHeader", "FuncParams", "REP_COMMA_ID_TYPE",
  "Parameters", "FuncBody", "VarsAndStatements", "BLOCK",
  "REP_STATEMENT_SEMICOLON", "Statement", "ParseArgs", "REP_COMMA_EXPR",
  "FuncInvocation", "Pred5", "Pred4", "Pred3", "Pred2", "Pred1", "Expr",
  "ID_NTERM", "STRLIT_NTERM", "ERR_NTERM", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-31)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,    16,    47,    23,   -51,    -3,    49,    64,   -51,    35,
      43,    70,   -51,    62,    49,   -51,    88,    -3,    -3,    93,
     -51,    -5,    37,    52,    49,    37,   -51,   -51,   -51,   170,
     178,   134,    75,   178,    93,    59,    72,    74,   -51,   -51,
      12,   -51,   -51,    78,    37,   -51,   -51,   -51,   -51,   -51,
      79,    88,   -51,   -51,   134,   141,   178,   178,   178,   -51,
     -51,   -51,    17,    46,    67,   110,     2,    96,     6,    87,
     -51,    83,   156,    90,   -51,    93,   -51,    93,   178,   121,
     120,   -51,   117,   -51,   -51,    94,    31,    91,   -51,   -51,
     -51,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   178,   134,   178,   134,   -51,   134,   -51,    38,
      97,   -51,   -51,    90,   128,   -51,    11,   102,    49,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,    17,    17,    46,    46,
      46,    46,    46,    46,    67,   109,   110,   113,   -51,   -51,
     -51,   122,   178,   106,   -51,    37,   -51,   147,   137,    11,
     -51,   117,   142,   155,   -51,   -51,   134,   151,   130,   141,
     -51,    -9,   126,   132,   139,   -51,   -51
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     5,     0,     0,     2,     0,
       0,     0,    78,     0,     0,     6,    10,     5,     5,     0,
      15,     0,    17,     0,     0,     0,     3,     4,    80,     0,
       0,     0,     0,    37,     0,     0,     0,     0,    40,    39,
       0,    43,    19,     0,     0,    13,    12,    11,    14,    16,
       0,    10,     8,    51,     0,     0,     0,     0,     0,    52,
      54,    63,    66,    73,    75,    77,     0,    53,     0,     0,
      28,     0,     0,    38,    27,     0,    23,     0,     0,     0,
       0,    18,    21,     7,     9,     0,     0,     0,    57,    56,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    32,     0,    79,     0,
       0,    24,    25,    31,     0,    49,    47,     0,     0,    22,
      35,    55,    59,    61,    62,    60,    65,    64,    69,    72,
      68,    71,    67,    70,    74,     0,    76,     0,    29,    41,
      42,     0,     0,     0,    50,     0,    36,    33,     0,    47,
      48,    21,     0,     0,    46,    20,     0,     0,     0,     0,
      34,     0,     0,     0,     0,    44,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -51,   -51,    85,    45,   166,   133,   -22,   -51,   -51,   -51,
      30,   -51,   -51,   -24,   -48,    76,   -10,   -51,    39,   -17,
     -18,    10,   119,    84,    98,   -26,    -6,   -51,   -50
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,    35,    15,    25,    49,    10,    11,    22,
     119,    43,    20,    36,    69,    70,    71,    38,   143,    60,
      61,    62,    63,    64,    65,    66,    67,   110,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    16,    39,    52,    68,    87,    85,    73,    16,    37,
      74,     6,    12,    40,    39,    44,    78,    39,    51,   142,
      79,   104,    82,   103,    37,    40,    91,   105,    40,    86,
     117,   163,   104,     3,    42,    80,   104,    39,    88,    89,
      90,   104,     7,    45,    92,     1,   109,     4,    40,    46,
       9,   111,   113,   112,   116,   135,    47,   137,    39,    93,
      39,   104,     9,     9,     5,    37,    12,    37,   104,    40,
     121,    40,    94,   123,   124,   125,    17,   139,    96,    95,
      48,    12,    97,    98,    18,    21,    39,    14,    39,    99,
      39,    19,   100,    50,    28,   101,    24,    40,    72,    40,
      75,    40,    26,    27,   126,   127,    29,    76,   158,   162,
      12,    30,   145,   102,    31,    77,   149,    81,    83,    80,
     104,    28,   106,   151,   107,   118,   114,    32,   -26,   120,
     122,    33,   141,   161,    34,    28,   140,    12,     7,    39,
      53,   144,    28,    55,   146,   150,    56,    29,   147,    57,
      40,    12,    30,    58,   148,    31,    59,   152,    12,   115,
     153,    53,   157,   156,    55,   160,   164,    56,    32,   -30,
      57,   165,    33,    12,    58,   159,    53,    59,   166,    55,
      23,   155,    56,   138,    84,    57,   134,    12,   154,    58,
      53,    54,    59,    55,     0,    12,    56,     0,    53,    57,
     108,    55,   136,    58,    56,     0,    59,    57,     0,     0,
       0,    58,     0,     0,    59,   128,   129,   130,   131,   132,
     133
};

static const yytype_int16 yycheck[] =
{
       6,     7,    19,    25,    30,    55,    54,    33,    14,    19,
      34,    14,    17,    19,    31,    21,     4,    34,    24,     8,
       8,    30,    44,    21,    34,    31,     9,    21,    34,    55,
      80,    40,    30,    17,    39,    23,    30,    54,    56,    57,
      58,    30,    45,     6,    27,    31,    72,     0,    54,    12,
       5,    75,    78,    77,    80,   103,    19,   105,    75,    42,
      77,    30,    17,    18,    41,    75,    17,    77,    30,    75,
      39,    77,    26,    91,    92,    93,    41,    39,    11,    33,
      43,    17,    15,    16,    41,    23,   103,    23,   105,    22,
     107,    21,    25,    41,     1,    28,     8,   103,    23,   105,
      41,   107,    17,    18,    94,    95,    13,    35,   156,   159,
      17,    18,   118,     3,    21,    41,   142,    39,    39,    23,
      30,     1,    35,   145,    41,     8,     5,    34,    35,    35,
      39,    38,     4,   159,    41,     1,    39,    17,    45,   156,
      20,    39,     1,    23,    35,    39,    26,    13,    35,    29,
     156,    17,    18,    33,    32,    21,    36,    10,    17,    39,
      23,    20,     7,    21,    23,    35,    40,    26,    34,    35,
      29,    39,    38,    17,    33,    24,    20,    36,    39,    23,
      14,   151,    26,   107,    51,    29,   102,    17,   149,    33,
      20,    21,    36,    23,    -1,    17,    26,    -1,    20,    29,
      44,    23,   104,    33,    26,    -1,    36,    29,    -1,    -1,
      -1,    33,    -1,    -1,    36,    96,    97,    98,    99,   100,
     101
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,    47,    17,     0,    41,    14,    45,    48,    49,
      53,    54,    17,    72,    23,    50,    72,    41,    41,    21,
      58,    23,    55,    50,     8,    51,    48,    48,     1,    13,
      18,    21,    34,    38,    41,    49,    59,    62,    63,    65,
      72,    74,    39,    57,    72,     6,    12,    19,    43,    52,
      41,    72,    52,    20,    21,    23,    26,    29,    33,    36,
      65,    66,    67,    68,    69,    70,    71,    72,    71,    60,
      61,    62,    23,    71,    59,    41,    35,    41,     4,     8,
      23,    39,    52,    39,    51,    60,    71,    74,    66,    66,
      66,     9,    27,    42,    26,    33,    11,    15,    16,    22,
      25,    28,     3,    21,    30,    21,    35,    41,    44,    71,
      73,    59,    59,    71,     5,    39,    71,    74,     8,    56,
      35,    39,    39,    66,    66,    66,    67,    67,    68,    68,
      68,    68,    68,    68,    69,    60,    70,    60,    61,    39,
      39,     4,     8,    64,    39,    72,    35,    35,    32,    71,
      39,    52,    10,    23,    64,    56,    21,     7,    60,    24,
      35,    71,    74,    40,    40,    39,    39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    49,    49,    50,    51,
      51,    52,    52,    52,    52,    53,    54,    54,    55,    55,
      56,    56,    57,    58,    59,    59,    59,    59,    60,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    63,    63,    64,    64,    65,    65,
      65,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      67,    67,    67,    67,    68,    68,    68,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    71,    71,    72,    73,
      74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     3,     0,     2,     5,     3,     3,
       0,     1,     1,     1,     1,     2,     4,     3,     3,     2,
       4,     0,     3,     3,     3,     3,     0,     2,     1,     3,
       0,     3,     3,     5,     9,     4,     5,     1,     2,     1,
       1,     4,     4,     1,    11,    11,     3,     0,     5,     3,
       4,     1,     1,     1,     1,     3,     2,     2,     2,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     1,     3,     1,     1,     1,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 393 "gocompiler.y"
                                                  {
                    // printf("Program - %ld\n", stack.size);
                    push_with_children(Program, "Program", stack.size);
                    ast_ptr n = *(ast_ptr*)get(&stack,0);
                    vector d = new_vector(sizeof(ast_ptr));
                    // printf("Boo1 - %ld\n", n->children.size);
                    for(size_t i = 0; i<n->children.size; i++) {
                        ast_ptr ch = *(ast_ptr*)get(&(n->children), i);
                        // printf("Boo1.%d\n", i);
                        if(ch->node_type == VarSpec) {
                            for(size_t j = 0; j<(ch->children.size); j++) {
                                push_back(&d, get(&(ch->children), j));
                            }
                            free_ast_ptr(ch);
                        }
                        else push_back(&d, &ch);
                    }
                    free(n->children.array);
                    n->children = d;

                /*
                    S S S ->
                       RS
                     / | \
                   |S  T| RS -> S S RS ->S S S RS -> S S S
                      /\
                     S RS
                       /\
                      S RS
                        ()
                    */
                }
#line 1929 "y.tab.c"
    break;

  case 6:
#line 430 "gocompiler.y"
                              {/*printf("VarDecl\n");push_with_children(VarDecl, "VarDecl",1);*/}
#line 1935 "y.tab.c"
    break;

  case 7:
#line 431 "gocompiler.y"
                                                  {/*printf("VarDecl\n");push_with_children(VarDecl, "VarDecl",1);*/}
#line 1941 "y.tab.c"
    break;

  case 8:
#line 433 "gocompiler.y"
                                     {
    // ast_ptr n = new_node_ptr(VarDecl, "VarDecl");
    // printf("VarSpec\n");
    ast_ptr type = pop_node();
    // printf("Type: %s\n", type->str);
    ast_ptr rep = pop_node();
    ast_ptr id = pop_node();
    // printf("Id:%s\n", id->str);
    ast_ptr v_spec = new_node_ptr(VarSpec, "");
    ast_ptr n = new_node_ptr(VarDecl, "VarDecl");
    
    // if(rep->children.size ==0) {
        push_back(&(n->children), &type);
        push_back(&(n->children), &id);
        push_back(&(v_spec->children), &n);
    // }
        // push_back(&stack, &n);
   
    
    if(rep->children.size >0) {
        vector to_free = new_vector(sizeof(ast_ptr));
        ast_ptr aid = rep;
        push_back(&to_free, &aid);
        while(aid->children.size > 1) {
            ast_ptr ch = new_node_ptr(VarDecl, "VarDecl");
            ast_ptr t = new_node_ptr(type->node_type, type->str);
            // printf("Boo1\n");
            push_back(&(ch->children), &t);
            push_back(&(ch->children), get(&(aid->children), 0));
            // push_back(&stack, &ch);
            //printf("Boo1\n");
            push_back(&(v_spec->children), &ch);
            aid = (*(ast_ptr*)get(&(aid->children), 1));
            push_back(&to_free, &aid);
        }
        for(size_t i = 0; i<to_free.size; i++) free_ast_ptr(*(ast_ptr*)get(&to_free, i));
        free(to_free.array);
    }
    push_back(&stack, &v_spec);
    // handle_rep(VarDecl, "VarDecl", 1);
    // ast_ptr tot = pop_node();
    // push_back(&(n->children), )

}
#line 1990 "y.tab.c"
    break;

  case 9:
#line 477 "gocompiler.y"
                                          {push_with_children(Rep_Comma_Id, "", 2);}
#line 1996 "y.tab.c"
    break;

  case 10:
#line 477 "gocompiler.y"
                                                                                       {push_node(Rep_Comma_Id, "", "");}
#line 2002 "y.tab.c"
    break;

  case 11:
#line 478 "gocompiler.y"
                    {
                    // printf("Int\n");
                    P_NODE(Int, "");
                }
#line 2011 "y.tab.c"
    break;

  case 12:
#line 482 "gocompiler.y"
                          {
                    // printf("Float32\n");
                    P_NODE(Float32, "");
                }
#line 2020 "y.tab.c"
    break;

  case 13:
#line 486 "gocompiler.y"
                       {
                    //printf("Bool\n");
                    P_NODE(Bool, "");
                }
#line 2029 "y.tab.c"
    break;

  case 14:
#line 490 "gocompiler.y"
                         {
                    //printf("String\n");
                    P_NODE(String, "");
                }
#line 2038 "y.tab.c"
    break;

  case 15:
#line 495 "gocompiler.y"
                                      {
                    // printf("FuncDecl\n");
                    // push_with_children(FuncDecl, "FuncDecl", 2);
                    ast_ptr body, header;
                    body = pop_node();
                    header = pop_node();
                    // printf("FuncDecl: body : %s and header = %s\n", body->str, header->str);
                    ast_ptr n = new_node_ptr(FuncDecl, "FuncDecl");
                    push_back(&(n->children), &header);
                    push_back(&(n->children), &body);
                    push_back(&stack, &n);
                }
#line 2055 "y.tab.c"
    break;

  case 16:
#line 508 "gocompiler.y"
                                                {
                    // push_with_children(FuncHeader, "FuncHeader",3); 
                    // print_top();
                    ast_ptr type, id , params;
                    type = pop_node();
                    params = pop_node();
                    id = pop_node();
                    // printf("FuncHeader: id: %s, type: %s, params: %s\n", id->str, type->str, params->str);
                    ast_ptr n = new_node_ptr(FuncHeader, "FuncHeader");
                    push_back(&(n->children), &id);
                    push_back(&(n->children), &type);
                    push_back(&(n->children), &params);
                    
                    push_back(&stack,&n);
                }
#line 2075 "y.tab.c"
    break;

  case 17:
#line 523 "gocompiler.y"
                                           {
                    ast_ptr id , params;
                    // type = pop_node();
                    params = pop_node();
                    id = pop_node();
                    // printf("FuncHeader: id:%s; params:%s\n",id->str, params->str);
                    ast_ptr n = new_node_ptr(FuncHeader, "FuncHeader");
                    push_back(&(n->children), &id);
                    push_back(&(n->children), &params);
                    push_back(&stack,&n);
                    // push_with_children(FuncHeader, "FuncHeader",2); /*print_top();*/
                
                }
#line 2093 "y.tab.c"
    break;

  case 18:
#line 537 "gocompiler.y"
                                       {
                        // push_with_children(FuncParams, "FuncParams", 1);
                        ast_ptr par = pop_node(), funcPar = new_node_ptr(FuncParams, "FuncParams");
                        for(size_t i = 0; i< par->children.size/2; i++) {
                            ast_ptr p = new_node_ptr(ParamDecl, "ParamDecl");
                            push_back(&(p->children), get(&(par->children), 2*i));
                            push_back(&(p->children), get(&(par->children), 2*i+1));
                            push_back(&(funcPar->children), &p);
                        }
                        free_ast_ptr(par);
                        push_back(&stack, &funcPar);
                    }
#line 2110 "y.tab.c"
    break;

  case 19:
#line 549 "gocompiler.y"
                            {/*printf("FuncParams\n");*/push_node(FuncParams, "FuncParams", "");}
#line 2116 "y.tab.c"
    break;

  case 20:
#line 556 "gocompiler.y"
                                                          {/* printf("Rep_Comma_id here!!!\n"); */push_with_children(Rep_Comma_Id, "", 3);}
#line 2122 "y.tab.c"
    break;

  case 21:
#line 557 "gocompiler.y"
                      {push_node(Rep_Comma_Id, "", "");}
#line 2128 "y.tab.c"
    break;

  case 22:
#line 559 "gocompiler.y"
                                             {
    ast_ptr rp = pop_node();
    // printf("ParamDecl: children_size: %ld\n", rp->children.size);
    if(rp->children.size > 0) {
        // push_back(&stack, &rp);
        // handle_rep(ParamDecl, "ParamDecl", 2,true);
        // rp = pop_node();
        vector ch = flat_children(rp, 2, true);
        rp = new_node_ptr(ParamDecl, "ParamDecl");
        vector new_children = new_vector(sizeof(ast_ptr));
        ast_ptr type = pop_node();
        ast_ptr id = pop_node();
        push_back(&new_children, &type);
        push_back(&new_children, &id);
        for(size_t i =0; i< ch.size; i++) {
            push_back(&new_children, get(&(ch), i));
        }
        rp->children = new_children;
        push_back(&stack, &rp);
    }
    else {
        free_ast_ptr(rp);
        // push_with_children(ParamDecl, "ParamDecl", 2);
        ast_ptr type = pop_node();
        ast_ptr id = pop_node();
        vector new_children = new_vector(sizeof(ast_ptr));
        push_back(&new_children, &type);
        push_back(&new_children, &id);
        ast_ptr n = new_node_ptr(ParamDecl, "ParamDecl");
        n->children = new_children;
        push_back(&stack, &n);
    }
}
#line 2166 "y.tab.c"
    break;

  case 23:
#line 592 "gocompiler.y"
                                           {
    // printf("FuncBody\n");
    ast_ptr rp = pop_node();
    // printf("Top of stack: %d\n", rp->node_type);
    if(rp->children.size == 0) {
        free(rp);
        P_NODE(FuncBody, "");
    }
    else {
        ast_ptr node = new_node_ptr(FuncBody, "FuncBody");
        // fazer função para retornar vetor
        vector v = flat_children(rp, 1,0);
        // CAREFUL: RP HAS BEEN FREED
        for(size_t i = 0; i<v.size; i++)  {
            ast_ptr ch = *(ast_ptr*)get(&(v), i);
            if(ch->node_type == VarSpec) {
                vector w = ch->children;
                for(size_t i = 0; i<w.size; i++) {
                    ast_ptr s = *(ast_ptr*) get(&w, i);
                    // printf("Grandson: %s\n", s->str);
                    push_back(&(node->children), &s);
                }
                free_ast_ptr(ch);
            }
            else{ 
                // printf("Child:%s\n",ch->str);
                push_back(&(node->children), &ch);
            }
            // printf("%s;\n", ch->str);
            // printf("no_children: %ld\n", ch->children.size);
        }
        push_back(&stack, &node);
    }
    // handle_rep(FuncBody, "FuncBody", 1);
}
#line 2206 "y.tab.c"
    break;

  case 24:
#line 627 "gocompiler.y"
                                                                {push_with_children(Vars_Statements, "", 2);}
#line 2212 "y.tab.c"
    break;

  case 25:
#line 628 "gocompiler.y"
                                                             {push_with_children(Vars_Statements, "", 2);}
#line 2218 "y.tab.c"
    break;

  case 26:
#line 629 "gocompiler.y"
                      {push_node(Vars_Statements, "", "");}
#line 2224 "y.tab.c"
    break;

  case 28:
#line 632 "gocompiler.y"
                               {
    // handle_rep(Block, "Block", 1, 0);
    ast_ptr rp = pop_node();
    vector ch = flat_children(rp, 1,0);
    ast_ptr n = new_node_ptr(Block, "Block");
    n->children = ch;
    push_back(&stack, &n);
}
#line 2237 "y.tab.c"
    break;

  case 29:
#line 640 "gocompiler.y"
                                                                     {push_with_children(Rep_Statement_Semicolon, "", 2);}
#line 2243 "y.tab.c"
    break;

  case 30:
#line 641 "gocompiler.y"
                           {push_node(Rep_Statement_Semicolon, "", "");}
#line 2249 "y.tab.c"
    break;

  case 31:
#line 643 "gocompiler.y"
                                     {/*printf("Assign\n");*/ push_with_children(Assign, "Assign", 2);}
#line 2255 "y.tab.c"
    break;

  case 33:
#line 645 "gocompiler.y"
                                              {
                    ast_ptr bl = pop_node();
                    ast_ptr expr = pop_node();
                    ast_ptr n = new_node_ptr(If, "If"), b = new_node_ptr(Block, "Block");
                    vector v = new_vector(sizeof(ast_ptr));
                    push_back(&v, &expr);
                    push_back(&v, &bl);
                    push_back(&v, &b);
                    n->children = v;
                    push_back(&stack, &n);
                }
#line 2271 "y.tab.c"
    break;

  case 34:
#line 656 "gocompiler.y"
                                                                       {/*printf("If\n");*/ push_with_children(If, "If", 3);}
#line 2277 "y.tab.c"
    break;

  case 35:
#line 657 "gocompiler.y"
                                          {/*printf("For\n");*/ push_with_children(For, "For", 1);}
#line 2283 "y.tab.c"
    break;

  case 36:
#line 658 "gocompiler.y"
                                               {/*printf("For\n");*/ push_with_children(For, "For", 2);}
#line 2289 "y.tab.c"
    break;

  case 37:
#line 659 "gocompiler.y"
                         {/*printf("Return\n");*/push_node(Return, "Return", "");}
#line 2295 "y.tab.c"
    break;

  case 38:
#line 660 "gocompiler.y"
                              {/*printf("Return\n");*/push_with_children(Return, "Return", 1);}
#line 2301 "y.tab.c"
    break;

  case 41:
#line 663 "gocompiler.y"
                                       {/*printf("Print\n");*/push_with_children(Print, "Print", 1);}
#line 2307 "y.tab.c"
    break;

  case 42:
#line 664 "gocompiler.y"
                                               {/*printf("Print\n");*/push_with_children(Print, "Print", 1);}
#line 2313 "y.tab.c"
    break;

  case 43:
#line 665 "gocompiler.y"
                            {/* yyerrok; yyclearin; yyerror("syntax error");*/}
#line 2319 "y.tab.c"
    break;

  case 44:
#line 666 "gocompiler.y"
                                                                                  {/*printf("Parseargs\n");*/ push_with_children(ParseArgs, "ParseArgs", 2);}
#line 2325 "y.tab.c"
    break;

  case 45:
#line 667 "gocompiler.y"
                                                                                          {/*yyerror("syntax error");*/}
#line 2331 "y.tab.c"
    break;

  case 46:
#line 668 "gocompiler.y"
                                          {push_with_children(Rep_Comma_Expr, "", 2);}
#line 2337 "y.tab.c"
    break;

  case 47:
#line 669 "gocompiler.y"
                  {push_node(Rep_Comma_Expr, "", "");}
#line 2343 "y.tab.c"
    break;

  case 48:
#line 671 "gocompiler.y"
                                                        {
                    // printf("Call\n");
                    ast_ptr rp = *(ast_ptr*)get(&stack, stack.size-1);
                    // printf("CALLL\n");
                    if(rp->children.size > 0) {
                        // handle_rep(Call, "Call",1, 0);
                        rp = pop_node();
                        vector ch = flat_children(rp, 1, false); //! rp was freed
                        rp = new_node_ptr(Call, "Call");
                        vector new_children = new_vector(sizeof(ast_ptr));
                        // rp->children = ch;
                        ast_ptr expr = pop_node();
                        ast_ptr id = pop_node();
                        push_back(&new_children, &id);
                        push_back(&new_children, &expr);
                        // printf("All: %s\n", rp->str);
                        for(size_t i = 0; i<ch.size; i++) {
                            push_back(&new_children, get(&ch, i));
                            // ast_ptr a = *(ast_ptr*)get(&ch, i);
                            // printf("Child: %s\n", a->str);
                        } 
                        free(ch.array);
                        rp->children = new_children;
                        push_back(&stack, &rp);
                    }
                    else {
                        pop_node();
                        free_ast_ptr(rp);
                        push_with_children(Call, "Call", 2);
                    }
                }
#line 2379 "y.tab.c"
    break;

  case 49:
#line 702 "gocompiler.y"
                                     {/*printf("Call\n");*/push_with_children(Call,"Call", 1);}
#line 2385 "y.tab.c"
    break;

  case 50:
#line 703 "gocompiler.y"
                                               { }
#line 2391 "y.tab.c"
    break;

  case 51:
#line 705 "gocompiler.y"
               {
            // printf("IntLit(%s)\n", yytext);
            push_node(IntLit, "IntLit(%s)", yytext);
        }
#line 2400 "y.tab.c"
    break;

  case 52:
#line 709 "gocompiler.y"
                  {
            // printf("RealLit(%s)\n", yytext);
            push_node(RealLit, "RealLit(%s)", yytext);
            }
#line 2409 "y.tab.c"
    break;

  case 55:
#line 715 "gocompiler.y"
                        {/*yyerror("syntax error");*/}
#line 2415 "y.tab.c"
    break;

  case 56:
#line 716 "gocompiler.y"
                    {/*printf("Not\n");*/push_with_children(Not, "Not",1);}
#line 2421 "y.tab.c"
    break;

  case 57:
#line 717 "gocompiler.y"
                      {/*printf("Minus\n");*/push_with_children(Minus, "Minus",1);}
#line 2427 "y.tab.c"
    break;

  case 58:
#line 718 "gocompiler.y"
                     {/*printf("Plus\n");*/push_with_children(Plus, "Plus",1);}
#line 2433 "y.tab.c"
    break;

  case 60:
#line 720 "gocompiler.y"
                         {/*printf("Mul\n");*/push_with_children(Mul, "Mul",2);}
#line 2439 "y.tab.c"
    break;

  case 61:
#line 721 "gocompiler.y"
                          {/*printf("Div\n");*/push_with_children(Div, "Div",2);}
#line 2445 "y.tab.c"
    break;

  case 62:
#line 722 "gocompiler.y"
                          {/*printf("Mod\n");*/push_with_children(Mod, "Mod",2);}
#line 2451 "y.tab.c"
    break;

  case 64:
#line 724 "gocompiler.y"
                         {/*printf("Plus\n");*/ push_with_children(Add, "Add",2);}
#line 2457 "y.tab.c"
    break;

  case 65:
#line 725 "gocompiler.y"
                            {/*printf("Minus\n");*/push_with_children(Sub, "Sub",2);}
#line 2463 "y.tab.c"
    break;

  case 67:
#line 727 "gocompiler.y"
                       {/*printf("Lt\n");*/push_with_children(Lt, "Lt",2);}
#line 2469 "y.tab.c"
    break;

  case 68:
#line 728 "gocompiler.y"
                         {/*printf("Gt\n");*/push_with_children(Gt, "Gt",2);}
#line 2475 "y.tab.c"
    break;

  case 69:
#line 729 "gocompiler.y"
                         {/*printf("Eq\n");*/push_with_children(Eq, "Eq",2);}
#line 2481 "y.tab.c"
    break;

  case 70:
#line 730 "gocompiler.y"
                          {/*printf("Ne\n");*/push_with_children(Ne, "Ne",2);}
#line 2487 "y.tab.c"
    break;

  case 71:
#line 731 "gocompiler.y"
                          {/*printf("Le\n");*/push_with_children(Le, "Le",2);}
#line 2493 "y.tab.c"
    break;

  case 72:
#line 732 "gocompiler.y"
                         {/*printf("Ge\n");*/push_with_children(Ge, "Ge",2);}
#line 2499 "y.tab.c"
    break;

  case 74:
#line 734 "gocompiler.y"
                        {/*printf("And\n");*/push_with_children(And, "And",2);}
#line 2505 "y.tab.c"
    break;

  case 76:
#line 736 "gocompiler.y"
                      {/*printf("Or\n");*/push_with_children(Or, "Or",2);}
#line 2511 "y.tab.c"
    break;

  case 78:
#line 739 "gocompiler.y"
             {
    // printf("Id(%s)", yytext);
    push_node(Id, "Id(%s)", yytext);
}
#line 2520 "y.tab.c"
    break;

  case 79:
#line 743 "gocompiler.y"
                     {
    //printf("StrLit(%s)", yytext);
    push_node(StrLit, "StrLit(%s)", yytext);
}
#line 2529 "y.tab.c"
    break;

  case 80:
#line 747 "gocompiler.y"
                 {}
#line 2535 "y.tab.c"
    break;


#line 2539 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 748 "gocompiler.y"

int main()
{
    stack = new_vector(sizeof(ast_ptr));
    // printf("Boo1\n");
    yyparse();
    // printf("Boo2\n");
    if(stack.size == 1 && ! syn_error){
        ast_ptr root = *(ast_ptr*)get(&stack,0);
        handle_blocks(root);
        print_ast_tree(root, 0);
    }

    return 0;
}
