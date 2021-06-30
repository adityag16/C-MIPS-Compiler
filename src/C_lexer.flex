%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
// [0-9]+([.][0-9]*)?

extern "C" int fileno(FILE *stream);

#include "C_parser.tab.hpp"

%}

%%
[=]             { yylval.string=new std::string(yytext); return T_ASS; }
[*]             { yylval.string=new std::string(yytext); return T_TIMES; }
[+]             { yylval.string=new std::string(yytext); return T_PLUS; }
[-]             { yylval.string=new std::string(yytext); return T_MINUS; }
[\/]             { return T_DIVIDE; }
[%]             { return T_MOD; }
[;]             { return T_SEMICOLON; }
[:]             { return T_COLON; }
[(]             { return T_LBRACKET; }
[\]]            { return T_RSBRACKET; }
[)]             { return T_RBRACKET; }
[{]             { return T_LCBRACKET; }
[}]             { return T_RCBRACKET; }
[,]             { return T_COMMA; }
[\[]            { return T_LSBRACKET; }

[&]             { yylval.string=new std::string(yytext); return T_AND_OP; }
[&][&]          { return T_LOGICAL_AND_OP; }
[|]             { return T_OR_OP; }
[|][|]          { return T_LOGICAL_OR_OP; }
[\^]             { return T_XOR_OP; }
[!]             { yylval.string=new std::string(yytext); return T_NOT; }
[~]             { yylval.string=new std::string(yytext); return T_TILDA; }
[<]             { return T_LT; }
[>]             { return T_GT; }
[<][=]             { return T_LE_OP; }
[>][=]             { return T_GE_OP; }
[=][=]          { return T_EQUALTO; }
[!][=]          { return T_NOT_EQUALTO; }
[+][+]          { yylval.string=new std::string(yytext); return T_INC_OP; }
[-][-]          { yylval.string=new std::string(yytext); return T_DEC_OP; }
[>][>]          { return T_RIGHT_OP; }
[<][<]          { return T_LEFT_OP; }
[*][=]          { yylval.string=new std::string(yytext); return MUL_ASSIGN; }
[/][=]          { yylval.string=new std::string(yytext); return DIV_ASSIGN; }
[+][=]          { yylval.string=new std::string(yytext); return ADD_ASSIGN; }
[-][=]          { yylval.string=new std::string(yytext); return SUB_ASSIGN; }
[&][=]          { yylval.string=new std::string(yytext); return AND_ASSIGN; }
[\^][=]          { yylval.string=new std::string(yytext); return XOR_ASSIGN; }
[|][=]          { yylval.string=new std::string(yytext); return OR_ASSIGN; }
[<][<][=]         { yylval.string=new std::string(yytext); return LEFT_ASSIGN; }
[>][>][=]         { yylval.string=new std::string(yytext); return RIGHT_ASSIGN; }

double		      { yylval.string=new std::string(yytext);  return T_DOUBLE; }
float			      { yylval.string=new std::string(yytext);  return T_FLOAT; }
int			      { yylval.string=new std::string(yytext);  return T_INT; }
unsigned		      { yylval.string=new std::string(yytext);  return T_UNSIGNED; }
char			      { yylval.string=new std::string(yytext);  return T_CHAR; }

typedef       { yylval.string=new std::string(yytext);  return T_TYPEDEF; }

if			      { yylval.string=new std::string(yytext);  return T_IF; }
else			      { yylval.string=new std::string(yytext);  return T_ELSE; }
while			      { yylval.string=new std::string(yytext);  return T_WHILE; }
for			      { yylval.string=new std::string(yytext);  return T_FOR; }
void			      { yylval.string=new std::string(yytext);  return T_VOID; }
break           { yylval.string=new std::string(yytext);  return T_BREAK; }
continue        { yylval.string=new std::string(yytext);  return T_CONTINUE; }
switch        { yylval.string=new std::string(yytext);  return T_SWITCH; }
case          { yylval.string=new std::string(yytext);  return T_CASE; }
default        { yylval.string=new std::string(yytext);  return T_DEFAULT; }
return		      { yylval.string=new std::string(yytext);  return T_RETURN; }
enum            { yylval.string=new std::string(yytext);  return T_ENUM; }

[0-9]+            { yylval.number=strtod(yytext, 0); return T_INTEGER; }
[0][xX][0-9a-fA-F]*       { yylval.number=strtod(yytext, 0); return T_INTEGER; }
[_]*[a-zA-Z0-9_]+         { yylval.string=new std::string(yytext); return T_VARIABLE; }

[ \t\r\n]+		   {;}

.                 { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
