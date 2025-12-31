/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     ID = 259,
     INT = 260,
     FLOAT = 261,
     BOOL = 262,
     EOL = 263,
     FLOAT_LITERAL = 264,
     ASSIGN = 265,
     POWER = 266,
     REPEAT = 267,
     DO = 268,
     DONE = 269,
     TRUE = 270,
     FALSE = 271,
     IF = 272,
     THEN = 273,
     ELSE = 274,
     FI = 275,
     WHILE = 276,
     UNTIL = 277,
     FOR = 278,
     IN = 279,
     SWITCH = 280,
     CASE = 281,
     BREAK = 282,
     DEFAULT = 283,
     FSWITCH = 284,
     AND = 285,
     OR = 286,
     NOT = 287,
     GT = 288,
     GE = 289,
     LT = 290,
     LE = 291,
     EQ = 292,
     NE = 293,
     RANGE = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 57 "./calc.y"

    int ival;
    float fval;
    char *sval;
    struct TempValue *expr;



/* Line 1685 of yacc.c  */
#line 99 "calc.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


