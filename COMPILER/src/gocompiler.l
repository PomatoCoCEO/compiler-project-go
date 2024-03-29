/*
    Compiladores, 2021

    Meta 2

    Autores:
        Paulo Cortesão, uc2019216517
        Samuel Carinhas, uc2019217199
*/

%X COMMENT_LINE COMMENT_MULTILINE STR INVALID_STRING
%{
    #include "semantic.h"
    #include "tokens.h"
    #include "y.tab.h"
    #include "tok_type.h"
    #include "ast_tree.h"
    #include "code_gen.h"

    int print_syn, print_sem;

    int syn_error;
    extern vector stack, token_free, nodes_free, stack_tables, vec_tables;
    int semicolon = 0, column = 1, line = 1, saved_line, saved_column, prev_col=1, prev_line=1; 
    void yyerror(const char *s)
    {
        if(print_syn)
            printf("Line %d, column %d: %s: %s\n", prev_line, prev_col, s, yytext);
        syn_error = 1;
    }
    void act_prev() {prev_col = column, prev_line= line;}
    int print=0;
    void print_tok(tok_type tok) {
        if(tok>=RESERVED_T) {
            printf("%s", tok_names[tok]);
            printf("(%s)", yytext);
        }
        else printf("%s",tok_names[tok]);
        printf("\n");
    }

    void handle_tok(tok_type tok) {
        if(print) print_tok(tok);
    }

    void free_token_vector(vector* vector) {
        // printf("Size: %ld\n", vector->size);
        if(vector->size) {
            for(int i = 0; i<vector->size; i++) {
                token_t* elem = *(token_t**)get(vector, i);
                free(elem->id);
                free(elem);
            }
            free(vector->array);
        }
    }

    void free_node_vector(vector*vector) {
        // printf("Node size: %ld\n", vector->size);
        if(vector->size) {
            for(int i = 0; i<vector->size; i++) {
                ast_ptr node = *(ast_ptr*)get(vector, i);
                free(node->str);
                if(node->children.size) 
                    free(node->children.array);
                if(node->type.isVec) {
                    if(node->type.u.vec.capacity)
                        free(node->type.u.vec.array);
                    if(node->annotate) free(node->annotate);
                }
                free(node);
            }   
            free(vector->array);
        }
    }

    void free_hash_tables() {
        if(stack_tables.size){
            for(int i = 0; i<stack_tables.size; i++) {
                hash_table h = *(hash_table*) get(&stack_tables, i);
                free(h.name);
                if(h.vec.capacity) {
                    for(int j = 0; j<h.vec.size; j++) {
                        vector v = *(vector*) get(&(h.vec), j);
                        if(v.capacity) free(v.array);
                    }
                    free(h.vec.array);
                }
            }
            free(stack_tables.array);
        }
        if(vec_tables.size){
            for(int i = 0; i<vec_tables.size; i++) {
                hash_table h = *(hash_table*) get(&vec_tables, i);
                free(h.name);
                if(h.vec.capacity) {
                    for(int j = 0; j<h.vec.size; j++) {
                        vector v = *(vector*) get(&(h.vec), j);
                        if(v.capacity) free(v.array);
                    }
                    free(h.vec.array);
                }
            }
            free(vec_tables.array);
        }
    }

%}
COMMENT                                                 "//"
OPEN_COMMENT                                            "/*"
CLOSE_COMMENT                                           "*/"
SEMICOLON                                               ";"
COMMA                                                   ","
BLANKID                                                 "_"
ASSIGN                                                  "="
STAR                                                    "*"
DIV                                                     "/"
MINUS                                                   "-"
PLUS                                                    "+"
EQ                                                      "=="
GE                                                      ">="
GT                                                      ">"
LBRACE                                                  "{"
LE                                                      "<="
LPAR                                                    "("
LSQ                                                     "["
LT                                                      "<"
MOD                                                     "%"
NE                                                      "!="
NOT                                                     "!"
AND                                                     "&&"
OR                                                      "||"
RBRACE                                                  "}"
RPAR                                                    ")"
RSQ                                                     "]"
PACKAGE                                                 package
RETURN                                                  return
ELSE                                                    else
FOR                                                     for
IF                                                      if
VAR                                                     var
INT                                                     int
FLOAT32                                                 float32
BOOL                                                    bool
STRING                                                  string
PRINT                                                   fmt"."Println
PARSEINT                                                strconv"."Atoi
FUNC                                                    func
CMDARGS                                                 os"."Args
letter                                                  [a-zA-Z_]
digit                                                   [0-9]
hexdigit                                                [0-9A-Fa-f]
octaldigit                                              [0-7]
decint                                                  [1-9]({digit})*|0
hexint                                                  {hexdigit}({hexdigit})*
octalint                                                0({octaldigit})*
alphanum                                                {letter}|{digit}
ID                                                      {letter}{alphanum}*
VALID_ESCAPE                                            "\\f"|"\\n"|"\\t"|"\\\\"|"\\\""|"\\r"
EMPTY_STRING                                            \"\"
STRLIT                                                  \"([^\r\n\"\\]|({VALID_ESCAPE}))+\"
QUOTE                                                   \"
INVALID_ESCAPE                                          "\\"|("\\"[^\n\r])
INTLIT                                                  {decint}|({octalint})|(0[xX]{hexint})
INVALID_OCTAL                                           0[0-9]+
REALLIT                                                 (({digit}+"."{digit}*)|({digit}*"."{digit}+)|({digit}+))([eE][+-]?{digit}+)?
RESERVED                                                "--"|"++"|"break"|"default"|"interface"|"select"|"case"|"defer"|"go"|"map"|"struct"|"chan"|"goto"|"package"|"switch"|"const"|"fallthrough"|"range"|"type"|"continue"|"import"
NEWLINE                                                 "\n" 
%%
{COMMENT}                                               { BEGIN COMMENT_LINE; act_prev(); column += yyleng; if(semicolon) {semicolon = 0;  if(print) print_tok(SEMICOLON_T); return SEMICOLON;} }
<COMMENT_LINE>\n                                        { BEGIN 0; act_prev(); line++; column = 1; }
<COMMENT_LINE>.                                         { act_prev(); column += yyleng; }
{OPEN_COMMENT}                                          { BEGIN COMMENT_MULTILINE; act_prev(); saved_line = line, saved_column = column; column += yyleng; }
<COMMENT_MULTILINE>{CLOSE_COMMENT}                      { BEGIN 0; act_prev(); column += yyleng; }
<COMMENT_MULTILINE><<EOF>>                              { semicolon = 0; printf("Line %d, column %d: unterminated comment\n", saved_line, saved_column); BEGIN 0; }
<COMMENT_MULTILINE>.                                    { act_prev(); column += yyleng; }
<COMMENT_MULTILINE>\n                                   { act_prev();  line ++; column = 1; } 
{SEMICOLON}                                             { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(SEMICOLON_T); return SEMICOLON; }
{COMMA}                                                 { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(COMMA_T); return COMMA; }
{BLANKID}                                               { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(BLANKID_T); return BLANKID; }
{ASSIGN}                                                { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(ASSIGN_T); return ASSIGN; }
{STAR}                                                  { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(STAR_T); return STAR; }
{DIV}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(DIV_T); return DIV; }
{MINUS}                                                 { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(MINUS_T); return MINUS; }
{PLUS}                                                  { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(PLUS_T); return PLUS; }
{EQ}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(EQ_T); return EQ; }
{GE}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(GE_T); return GE; }
{GT}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(GT_T); return GT; }
{LBRACE}                                                { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(LBRACE_T); return LBRACE; }
{LE}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(LE_T); return LE; }
{LPAR}                                                  { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(LPAR_T); return LPAR; }
{LSQ}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(LSQ_T); return LSQ; }
{LT}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(LT_T); return LT; }
{MOD}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(MOD_T); return MOD; }
{NE}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(NE_T); return NE; }
{NOT}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(NOT_T); return NOT; }
{AND}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(AND_T); return AND; }
{OR}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(OR_T); return OR; }
{RBRACE}                                                { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng; if(print) print_tok(RBRACE_T); return RBRACE; }
{RPAR}                                                  { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng; if(print) print_tok(RPAR_T); return RPAR; }
{RSQ}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng; if(print) print_tok(RSQ_T); return RSQ; }
{PACKAGE}                                               { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(PACKAGE_T); return PACKAGE; }
{RETURN}                                                { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng; if(print) print_tok(RETURN_T); return RETURN; }
{ELSE}                                                  { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(ELSE_T); return ELSE; }
{FOR}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(FOR_T); return FOR; }
{IF}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(IF_T); return IF; }
{VAR}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(VAR_T); return VAR; }
{INT}                                                   { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(INT_T); return INT; }
{FLOAT32}                                               { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(FLOAT32_T); return FLOAT32; }
{BOOL}                                                  { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(BOOL_T); return BOOL; }
{STRING}                                                { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(STRING_T); return STRING; }
{PRINT}                                                 { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(PRINT_T); return PRINT; }
{PARSEINT}                                              { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(PARSEINT_T); return PARSEINT; }
{FUNC}                                                  { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(FUNC_T); return FUNC; }
{CMDARGS}                                               { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(CMDARGS_T); return CMDARGS; }
{RESERVED}                                              { yylval.token_id = new_token(yytext, line, column); semicolon = 0; act_prev(); column += yyleng; if(print) print_tok(RESERVED_T); return RESERVED; }
{ID}                                                    { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng; if(print) print_tok(ID_T); return ID; }
{INTLIT}                                                { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng; if(print) print_tok(INTLIT_T); return INTLIT; }
{INVALID_OCTAL}                                         { yylval.token_id = new_token(yytext, line, column); if(print || print_syn) printf("Line %d, column %d: invalid octal constant (%s)\n", line, column, yytext); act_prev(); semicolon = 1; column += yyleng; }
{REALLIT}                                               { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng;  if(print) print_tok(REALLIT_T);return REALLIT; }
{EMPTY_STRING}                                          { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng;  if(print) print_tok(STRLIT_T);return STRLIT; }
{STRLIT}                                                { yylval.token_id = new_token(yytext, line, column); semicolon = 1; act_prev(); column += yyleng; BEGIN 0;  if(print) print_tok(STRLIT_T);return STRLIT; }
{QUOTE}                                                 { BEGIN INVALID_STRING; saved_line = line, saved_column = column; semicolon = 0; act_prev(); column += yyleng; } 
<INVALID_STRING>{QUOTE}                                 { BEGIN 0;  semicolon = 0; act_prev(); column += yyleng; }
<INVALID_STRING>{VALID_ESCAPE}                          { semicolon = 0; act_prev(); column += yyleng; }
<INVALID_STRING>{INVALID_ESCAPE}                        { if(print || print_syn) printf("Line %d, column %d: invalid escape sequence (%s)\n", line, column, yytext); act_prev(); column += yyleng; }
<INVALID_STRING><<EOF>>                                 { BEGIN 0; if(print || print_syn) printf("Line %d, column %d: unterminated string literal\n", saved_line, saved_column); column += yyleng; semicolon = 0;}
<INVALID_STRING>\n                                      { semicolon = 0; act_prev(); BEGIN 0; if(print || print_syn) printf("Line %d, column %d: unterminated string literal\n", saved_line, saved_column); column = 1; line++; }
<INVALID_STRING>.                                       { act_prev();  column += yyleng; semicolon = 0; }
\n                                                      { act_prev(); column = 1; line++; if(semicolon) {semicolon = 0;  if(print) print_tok(SEMICOLON_T); return SEMICOLON;} }
<<EOF>>                                                 { if(semicolon) { semicolon=0; if(print) print_tok(SEMICOLON_T); return SEMICOLON;} return 0; }
" "|"\t"|"\r"                                           { act_prev(); column += yyleng; }
.                                                       { act_prev(); if(print || print_syn) printf("Line %d, column %d: illegal character (%s)\n", line, column, yytext); act_prev(); column += yyleng; }
%%

int yywrap() {
    return 1;
}

int main(int argc, char** argv) {
    token_free = new_vector(sizeof(token_t*));
    nodes_free = new_vector(sizeof(ast_ptr));
    if(argc>=2 && strcmp(argv[1], "-l")==0) {
        print=1;
        print_syn = 0;
        while(yylex());
    }
    else if(argc>=2 && strcmp(argv[1], "-t")==0) {
        print_syn = 1;
        print = 0;
        stack = new_vector(sizeof(ast_ptr));
        yyparse();
        if(stack.size == 1 && ! syn_error){
            ast_ptr root = *(ast_ptr*)get(&stack,0);
            handle_blocks(root);
            print_ast_tree(root, 0);
        }
        if(stack.size) free(stack.array);
        free_node_vector(&nodes_free);
    } else if(argc >= 2 && strcmp(argv[1], "-s")==0) {
        print_sem = 1;
        print_syn = 0;
        print = 0;
        stack = new_vector(sizeof(ast_ptr));
        yyparse();
        if(stack.size == 1 && ! syn_error){
            ast_ptr root = *(ast_ptr*)get(&stack,0);
            handle_blocks(root);
            semantic_analysis(root);
            if(semantic_errors == 0)
                print_ast_tree(root, 0);
        }
        free_node_vector(&nodes_free);
        free_hash_tables();
        if(stack.size) free(stack.array);
    } else {
        print_sem = 0;
        print_syn = 0;
        print = 0;
        stack = new_vector(sizeof(ast_ptr));
        yyparse();
        if(stack.size == 1 && ! syn_error){
            ast_ptr root = *(ast_ptr*)get(&stack,0);
            handle_blocks(root);
            semantic_analysis(root);
            /*
            if(semantic_errors == 0)
                print_ast_tree(root, 0);
            */
            generate_code(root);
        }
        free_node_vector(&nodes_free);
        free_hash_tables();
        if(stack.size) free(stack.array);
    }
    free_token_vector(&token_free);
    yylex_destroy();
    return 0;
}
