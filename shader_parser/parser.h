/* A Bison parser, made by GNU Bison 3.3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 8 ".\\parser.y" /* yacc.c:1921  */

    #include "ast.h"

    #define YY_NO_UNISTD_H 1

#line 54 "parser.h" /* yacc.c:1921  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_TRUE = 258,
    TK_FALSE = 259,
    TK_CODEBLOCK = 260,
    TK_TECHNIQUE = 261,
    TK_PASS = 262,
    TK_CODE = 263,
    TK_REQUIRE = 264,
    TK_CULLMODE = 265,
    TK_FRONT_FACE = 266,
    TK_FACE = 267,
    TK_CW = 268,
    TK_CCW = 269,
    TK_BACK = 270,
    TK_FRONT = 271,
    TK_FRONT_AND_BACK = 272,
    TK_ENABLE = 273,
    TK_CODE_VALUE = 274,
    TK_NAME = 275,
    TK_STRING = 276,
    TK_VERTEX = 277,
    TK_FRAGMENT = 278
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 ".\\parser.y" /* yacc.c:1921  */

    int intValue;
    const char* strValue;
    ASTNode* nodePtr;

#line 96 "parser.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (ParserContext* context);
/* "%code provides" blocks.  */
#line 26 ".\\parser.y" /* yacc.c:1921  */

   #define YY_DECL \
       int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param, ParserContext* context)
   YY_DECL;

   int yyerror(YYLTYPE* yylloc, ParserContext* context, const char* message);

#line 130 "parser.h" /* yacc.c:1921  */

#endif /* !YY_YY_PARSER_H_INCLUDED  */
