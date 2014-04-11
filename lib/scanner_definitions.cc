%{
#include <stdio.h>
%}

%option noyywrap

%%
test { printf("testing ..."); }
%%
