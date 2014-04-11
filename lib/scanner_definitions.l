%{
#include <schemese/scanner.h>
#define YY_DEBUG 1
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) { \
  result = Scanner::read(buf, max_size); \
}

using namespace Schemese;
%}

%option yylineno
%option noyywrap
%option 8bit
%option nodefault

characters                        [a-zA-Z0-9()]
digit                             [0-9]
binary                            [01]+
hex                               [0-9ABCDEFabcdef]+
octal                             [0-7]+
integer                           {digit}+
sign                              [+-]
exponent                          [Ee]({sign})?{integer}
real                              (\.{integer}|{integer}\.({integer})?)({exponent})?
integer_with_exponent             {integer}{exponent}
identifier                        [a-zA-Z.+-<>=?-]+
whitespace                        [\n\t ]

%x block_id
%x character
%x string
%%
"("                           return LPAREN;
")"                           return RPAREN;
"{"                           return LCURLYBRACKET;
"}"                           return RCURLYBRACKET;
"["                           return LBRACKET;
"]"                           return RBRACKET;
"`"                           return BACKQUOTE;
"'"                           return QUOTE;
","                           return UNQUOTE;
",@"                          return UNQUOTESPLICE;

#t                            return TRUE;
#true                         return TRUE;
#f                            return FALSE;
#false                        return FALSE;

#\(                           return VECTOR_START;
#u8\(                         return BYTEVECTOR_START;

#\\                           BEGIN(character);
<character>" "                { yytext = " ";     BEGIN(INITIAL);   return CHARACTER; }
<character>{characters}       { BEGIN(INITIAL); return CHARACTER; }
<character>alarm              { yytext = "\a";    BEGIN(INITIAL);   return CHARACTER; }
<character>backspace          { yytext = "\b";    BEGIN(INITIAL);   return CHARACTER; }
<character>delete             { yytext = "\x7f";  BEGIN(INITIAL);   return CHARACTER; }
<character>escape             { yytext = "\x1b";  BEGIN(INITIAL);   return CHARACTER; }
<character>newline            { yytext = "\n";    BEGIN(INITIAL);   return CHARACTER; }
<character>null               { yytext = "\0";    BEGIN(INITIAL);   return CHARACTER; }
<character>return             { yytext = "\x0d";  BEGIN(INITIAL);   return CHARACTER; }
<character>space              { yytext = " ";     BEGIN(INITIAL);   return CHARACTER; }
<character>tab                { yytext = "\t";    BEGIN(INITIAL);   return CHARACTER; }

#b{binary}                    return INTEGER;
#b{binary}\/{binary}          return RATIONAL;
#o{octal}                     return INTEGER;
#o{octal}\/{octal}            return RATIONAL;
#d{integer}                   return INTEGER;
#d{integer}\/{integer}        return RATIONAL;
#x{hex}                       return INTEGER;
#x{hex}\/{hex}                return RATIONAL;
{real}                        return REAL;
{integer_with_exponent}       return REAL;
{integer}                     return INTEGER;
{integer}\/{integer}          return RATIONAL;

#e{integer}                   return RATIONAL;
#e{real}                      return RATIONAL;
#e{integer}\/{integer}        return RATIONAL;
#i{integer}                   return REAL;
#i{real}                      return REAL;
#i{integer}\/{integer}        return REAL;


\|                            BEGIN(block_id);
<block_id>[^|]+               return IDENTIFIER;
<block_id>\|                  BEGIN(INITIAL);

\"                            BEGIN(string);
<string>[^"]*                 return STRING;
<string>\"                    BEGIN(INITIAL);

{identifier}                  return IDENTIFIER;
{whitespace}+                 { }
%%
