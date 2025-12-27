/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "calc.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "value.h"
#include "symtab.h"

/* yylex() is the flex scanner. yyerror() is the fuction Bison will call in case of an error. */
int yylex(void);
void yyerror(const char *s);
extern int yylineno;

extern FILE *yyin;

void print_result(struct TempValue *res);

char *strdup(const char *s);

struct TempValue* compare(struct TempValue* v1, struct TempValue* v2, int op);

struct Token* find_field(struct Token* list, char* name);

struct Token* copy_tokens(struct Token* source);


/* Line 189 of yacc.c  */
#line 99 "calc.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     STRING = 262,
     BOOL = 263,
     EOL = 264,
     FLOAT_LITERAL = 265,
     STRING_LITERAL = 266,
     BOOL_LITERAL = 267,
     ASSIGN = 268,
     POWER = 269,
     EQ = 270,
     LE = 271,
     GE = 272,
     NE = 273,
     LT = 274,
     GT = 275,
     AND = 276,
     OR = 277,
     NOT = 278,
     PI = 279,
     E = 280,
     SIN = 281,
     COS = 282,
     TAN = 283,
     LEN = 284,
     SUBSTR = 285,
     STRUCT = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 27 "calc.y"

    int ival;
    float fval;
    char *sval;
    int bval;
    struct TempValue *expr;
    struct Token *tokens;



/* Line 214 of yacc.c  */
#line 177 "calc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 189 "calc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   172

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    38,     2,     2,
      39,    40,    36,    34,    32,    35,    41,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    18,    21,
      23,    27,    29,    33,    35,    38,    40,    44,    48,    52,
      56,    60,    64,    66,    69,    71,    75,    79,    83,    87,
      91,    93,    97,   101,   103,   107,   111,   115,   117,   120,
     123,   125,   129,   131,   133,   135,   137,   139,   141,   143,
     148,   153,   158,   163,   172,   176,   180,   183,   186,   189,
     192,   199,   203
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    -1,    45,    46,    -1,    47,     9,    -1,
      59,     9,    -1,    60,     9,    -1,     9,    -1,     1,     9,
      -1,    48,    -1,    47,    22,    48,    -1,    49,    -1,    48,
      21,    50,    -1,    50,    -1,    23,    49,    -1,    54,    -1,
      54,    15,    54,    -1,    54,    18,    54,    -1,    54,    19,
      54,    -1,    54,    16,    54,    -1,    54,    20,    54,    -1,
      54,    17,    54,    -1,    53,    -1,    53,    51,    -1,     4,
      -1,    52,    32,     4,    -1,     5,     4,    33,    -1,     6,
       4,    33,    -1,     7,     4,    33,    -1,     8,     4,    33,
      -1,    55,    -1,    54,    34,    55,    -1,    54,    35,    55,
      -1,    56,    -1,    55,    36,    56,    -1,    55,    37,    56,
      -1,    55,    38,    56,    -1,    57,    -1,    35,    56,    -1,
      34,    56,    -1,    58,    -1,    57,    14,    58,    -1,     3,
      -1,    10,    -1,    12,    -1,    11,    -1,     4,    -1,    24,
      -1,    25,    -1,    26,    39,    54,    40,    -1,    27,    39,
      54,    40,    -1,    28,    39,    54,    40,    -1,    29,    39,
      54,    40,    -1,    30,    39,    54,    33,    54,    33,    54,
      40,    -1,     4,    41,     4,    -1,    39,    47,    40,    -1,
       5,     4,    -1,     6,     4,    -1,     7,     4,    -1,     8,
       4,    -1,    31,     4,    42,    51,    43,    52,    -1,     4,
      13,    47,    -1,     4,    41,     4,    13,    47,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    70,    74,    79,    80,    81,    82,    86,
      87,    96,    97,   106,   107,   119,   120,   121,   122,   123,
     124,   125,   129,   132,   139,   146,   157,   164,   171,   178,
     188,   189,   252,   284,   285,   315,   364,   384,   385,   396,
     400,   401,   418,   423,   428,   433,   439,   471,   476,   481,
     494,   507,   520,   534,   561,   594,   600,   612,   624,   636,
     649,   691,   732
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "ID", "INT", "FLOAT", "STRING",
  "BOOL", "EOL", "FLOAT_LITERAL", "STRING_LITERAL", "BOOL_LITERAL",
  "ASSIGN", "POWER", "EQ", "LE", "GE", "NE", "LT", "GT", "AND", "OR",
  "NOT", "PI", "E", "SIN", "COS", "TAN", "LEN", "SUBSTR", "STRUCT", "','",
  "';'", "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "')'", "'.'", "'{'",
  "'}'", "$accept", "program", "line", "or_predicate", "and_predicate",
  "not_predicate", "predicate", "token_list", "id_list", "token_decl",
  "expression", "term", "unary", "pow", "atom", "declaration",
  "assignation", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    44,    59,    43,    45,    42,    47,    37,    40,
      41,    46,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    46,    46,    46,    47,
      47,    48,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    51,    51,    52,    52,    53,    53,    53,    53,
      54,    54,    54,    55,    55,    55,    55,    56,    56,    56,
      57,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    59,    59,    59,    59,
      59,    60,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     1,     2,     1,
       3,     1,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     1,     2,     1,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     2,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     4,     4,     8,     3,     3,     2,     2,     2,     2,
       6,     3,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    42,    46,     0,     0,     0,     0,
       7,    43,    45,    44,     0,    47,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     9,    11,
      13,    15,    30,    33,    37,    40,     0,     0,     8,     0,
       0,    56,    57,    58,    59,    46,    14,     0,     0,     0,
       0,     0,     0,    39,    38,     0,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     6,    61,    54,     0,     0,     0,     0,     0,
       0,     0,    55,    10,    12,    16,    19,    21,    17,    18,
      20,    31,    32,    34,    35,    36,    41,     0,    54,    49,
      50,    51,    52,     0,     0,     0,     0,     0,     0,    22,
      62,     0,     0,     0,     0,     0,     0,    23,     0,    26,
      27,    28,    29,    24,    60,     0,     0,    53,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    26,    27,    28,    29,    30,   108,   124,   109,
      31,    32,    33,    34,    35,    36,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -54
static const yytype_int16 yypact[] =
{
     -54,    26,   -54,     0,   -54,    -2,    40,    54,    60,    62,
     -54,   -54,   -54,   -54,    59,   -54,   -54,    38,    51,    75,
      76,    84,   126,    92,    92,    59,   -54,    -1,   113,   -54,
     -54,    90,    42,   -54,   127,   -54,   130,   131,   -54,    59,
     138,   -54,   -54,   -54,   -54,   102,   -54,    92,    92,    92,
      92,    92,   103,   -54,   -54,   -12,   -54,    59,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
     125,   -54,   -54,   122,   133,   143,     8,    33,    41,    57,
      66,    17,   -54,   113,   -54,     6,     6,     6,     6,     6,
       6,    42,    42,   -54,   -54,   -54,   -54,    59,   -54,   -54,
     -54,   -54,   -54,    92,   144,   152,   153,   154,   116,    17,
     122,    78,   128,   129,   132,   134,   156,   -54,    92,   -54,
     -54,   -54,   -54,   -54,   136,    98,   159,   -54,   -54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   -54,   -25,   109,   155,   112,    63,   -54,   -54,
     -44,   -53,   -22,   -54,   101,   -54,   -54
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,    53,    54,    76,    77,    78,    79,    80,    56,    38,
      57,    39,    91,    92,    73,    85,    86,    87,    88,    89,
      90,    57,   104,   105,   106,   107,     2,     3,    82,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    40,
      65,    66,    65,    66,    41,    93,    94,    95,    99,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    42,   111,
      23,    24,     4,    45,    43,    25,    44,    65,    66,    11,
      12,    13,   110,   100,   125,    65,    66,    47,    67,    68,
      69,   101,    14,    15,    16,    17,    18,    19,    20,    21,
      48,    65,    66,    23,    24,     4,    45,   102,    25,   103,
      65,    66,    11,    12,    13,    59,    60,    61,    62,    63,
      64,   118,    65,    66,    49,    50,    15,    16,    17,    18,
      19,    20,    21,    51,    65,    66,    23,    24,     4,    45,
      52,    25,    65,    66,    58,    11,    12,    13,   127,    71,
      72,    70,    74,    75,    57,    81,    97,    98,   112,    15,
      16,    17,    18,    19,    20,    21,   113,   114,   115,   116,
     123,   119,   120,   128,    25,   121,    83,   122,   126,    46,
      84,    96,   117
};

static const yytype_uint8 yycheck[] =
{
      25,    23,    24,    47,    48,    49,    50,    51,     9,     9,
      22,    13,    65,    66,    39,    59,    60,    61,    62,    63,
      64,    22,     5,     6,     7,     8,     0,     1,    40,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    41,
      34,    35,    34,    35,     4,    67,    68,    69,    40,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     4,   103,
      34,    35,     3,     4,     4,    39,     4,    34,    35,    10,
      11,    12,    97,    40,   118,    34,    35,    39,    36,    37,
      38,    40,    23,    24,    25,    26,    27,    28,    29,    30,
      39,    34,    35,    34,    35,     3,     4,    40,    39,    33,
      34,    35,    10,    11,    12,    15,    16,    17,    18,    19,
      20,    33,    34,    35,    39,    39,    24,    25,    26,    27,
      28,    29,    30,    39,    34,    35,    34,    35,     3,     4,
       4,    39,    34,    35,    21,    10,    11,    12,    40,     9,
       9,    14,     4,    41,    22,    42,    13,     4,     4,    24,
      25,    26,    27,    28,    29,    30,     4,     4,     4,    43,
       4,    33,    33,     4,    39,    33,    57,    33,    32,    14,
      58,    70,   109
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,     0,     1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    34,    35,    39,    46,    47,    48,    49,
      50,    54,    55,    56,    57,    58,    59,    60,     9,    13,
      41,     4,     4,     4,     4,     4,    49,    39,    39,    39,
      39,    39,     4,    56,    56,    47,     9,    22,    21,    15,
      16,    17,    18,    19,    20,    34,    35,    36,    37,    38,
      14,     9,     9,    47,     4,    41,    54,    54,    54,    54,
      54,    42,    40,    48,    50,    54,    54,    54,    54,    54,
      54,    55,    55,    56,    56,    56,    58,    13,     4,    40,
      40,    40,    40,    33,     5,     6,     7,     8,    51,    53,
      47,    54,     4,     4,     4,     4,    43,    51,    33,    33,
      33,    33,    33,     4,    52,    54,    32,    40,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

/* Line 1464 of yacc.c  */
#line 74 "calc.y"
    {
        printf("BISON: Result: ");
        print_result((yyvsp[(1) - (2)].expr)); 
        free((yyvsp[(1) - (2)].expr));
    ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 79 "calc.y"
    { printf("BISON: DECLARATION TRACKED.\n"); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 80 "calc.y"
    { printf("BISON: ASSIGNATION TRACKED.\n"); ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 81 "calc.y"
    { printf("BISON: EOL\n"); ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 82 "calc.y"
    { printf("BISON: Detected error. Jumping to the next line.\n"); yyerrok; ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 86 "calc.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 87 "calc.y"
    {
        struct TempValue *res = (yyvsp[(1) - (3)].expr);
        res->value.b_val = ((yyvsp[(1) - (3)].expr)->value.b_val || (yyvsp[(3) - (3)].expr)->value.b_val);
        free((yyvsp[(3) - (3)].expr));
        (yyval.expr) = res;
    ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 96 "calc.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 97 "calc.y"
    {
        struct TempValue *res = (yyvsp[(1) - (3)].expr);
        res->value.b_val = ((yyvsp[(1) - (3)].expr)->value.b_val && (yyvsp[(3) - (3)].expr)->value.b_val);
        free((yyvsp[(3) - (3)].expr));
        (yyval.expr) = res;
    ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 106 "calc.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 107 "calc.y"
    {
        struct TempValue *res = (yyvsp[(2) - (2)].expr);
        if (res->type != TYPE_BOOL) {
            yyerror("Semantic Error: NOT requires boolean operand");
        } else {
            res->value.b_val = !res->value.b_val;
        }
        (yyval.expr) = res;
    ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 119 "calc.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 120 "calc.y"
    { (yyval.expr) = compare((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), EQ); ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 121 "calc.y"
    { (yyval.expr) = compare((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), NE); ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 122 "calc.y"
    { (yyval.expr) = compare((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), LT); ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 123 "calc.y"
    { (yyval.expr) = compare((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), LE); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 124 "calc.y"
    { (yyval.expr) = compare((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), GT); ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 125 "calc.y"
    { (yyval.expr) = compare((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), GE); ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 129 "calc.y"
    { 
        (yyval.tokens) = (yyvsp[(1) - (1)].tokens);
    ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 132 "calc.y"
    {
        (yyvsp[(1) - (2)].tokens)->next = (yyvsp[(2) - (2)].tokens); 
        (yyval.tokens) = (yyvsp[(1) - (2)].tokens); 
    ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 139 "calc.y"
    {
        /* Creamos un nodo solo para guardar el nombre */
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[(1) - (1)].sval); 
        t->next = NULL;
        (yyval.tokens) = t;
    ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 146 "calc.y"
    {
        /* Añadimos el nuevo ID al final o principio de la lista */
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[(3) - (3)].sval);
        t->next = (yyvsp[(1) - (3)].tokens); /* Lo ponemos al principio para ir rápido (orden inverso, no importa) */
        (yyval.tokens) = t;
    ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 157 "calc.y"
    {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[(2) - (3)].sval);      /* Guardamos el nombre "x" */
        t->type = TYPE_INT;
        t->next = NULL;
        (yyval.tokens) = t;            /* Subimos el puntero */
    ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 164 "calc.y"
    {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[(2) - (3)].sval);
        t->type = TYPE_FLOAT;
        t->next = NULL;
        (yyval.tokens) = t;
    ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 171 "calc.y"
    {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[(2) - (3)].sval);
        t->type = TYPE_STRING;
        t->next = NULL;
        (yyval.tokens) = t;
    ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 178 "calc.y"
    {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[(2) - (3)].sval);
        t->type = TYPE_BOOL;
        t->next = NULL;
        (yyval.tokens) = t;
    ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 188 "calc.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 189 "calc.y"
    {
        TempValue *res1 = (yyvsp[(1) - (3)].expr);
        TempValue *res2 = (yyvsp[(3) - (3)].expr);

        if (res1->type == TYPE_STRING || res2->type == TYPE_STRING) {
            char buffer1[100], buffer2[100];
            char *str1, *str2;

            /* Convertir primer operando a texto */
            if (res1->type == TYPE_STRING) {
                str1 = res1->value.s_val;
            } else if (res1->type == TYPE_INT) {
                sprintf(buffer1, "%d", res1->value.i_val);
                str1 = buffer1;
            } else if (res1->type == TYPE_FLOAT) {
                sprintf(buffer1, "%g", res1->value.f_val);
                str1 = buffer1;
            } else { /* BOOL */
                str1 = res1->value.b_val ? "true" : "false";
            }

            /* Convertir segundo operando a texto */
            if (res2->type == TYPE_STRING) {
                str2 = res2->value.s_val;
            } else if (res2->type == TYPE_INT) {
                sprintf(buffer2, "%d", res2->value.i_val);
                str2 = buffer2;
            } else if (res2->type == TYPE_FLOAT) {
                sprintf(buffer2, "%g", res2->value.f_val);
                str2 = buffer2;
            } else { /* BOOL */
                str2 = res2->value.b_val ? "true" : "false";
            }

            /* Reservar memoria y concatenar */
            char *resultStr = (char*)malloc(strlen(str1) + strlen(str2) + 1);
            strcpy(resultStr, str1);
            strcat(resultStr, str2);

            /* Liberar operandos viejos */
            if (res1->type == TYPE_STRING) free(res1->value.s_val);
            if (res2->type == TYPE_STRING) free(res2->value.s_val);
            free(res2); // res1 se reutiliza

            res1->type = TYPE_STRING;
            res1->value.s_val = resultStr;
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = res1->value.i_val + res2->value.i_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else {
             float v1 = (res1->type == TYPE_INT) ? (float)res1->value.i_val : res1->value.f_val;
             float v2 = (res2->type == TYPE_INT) ? (float)res2->value.i_val : res2->value.f_val;
             
             res1->type = TYPE_FLOAT;
             res1->value.f_val = v1 + v2;
             free(res2);
             (yyval.expr) = res1;
        }
    ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 252 "calc.y"
    {
        TempValue *res1 = (yyvsp[(1) - (3)].expr);
        TempValue *res2 = (yyvsp[(3) - (3)].expr);
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = res1->value.i_val - res2->value.i_val;
            free(res2);
            (yyval.expr) = res1;
        } 
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_FLOAT) {
            res1->value.f_val = res1->value.f_val - res2->value.f_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_FLOAT) {
            res1->type = TYPE_FLOAT;
            res1->value.f_val = (float)res1->value.i_val - res2->value.f_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_INT) {
            res1->value.f_val = res1->value.f_val - (float)res2->value.i_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else {
            yyerror("Semanthic error: Uncompatible type for '-'");
            (yyval.expr) = 0;
        }
    ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 284 "calc.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 285 "calc.y"
    {
        TempValue *res1 = (yyvsp[(1) - (3)].expr);
        TempValue *res2 = (yyvsp[(3) - (3)].expr);
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = res1->value.i_val * res2->value.i_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_FLOAT) {
            res1->value.f_val = res1->value.f_val * res2->value.f_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_FLOAT) {
            res1->type = TYPE_FLOAT;
            res1->value.f_val = (float)res1->value.i_val * res2->value.f_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_INT) {
            res1->value.f_val = res1->value.f_val * (float)res2->value.i_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else {
            yyerror("Semanthic error: Uncompatible type for '*'");
            (yyval.expr) = 0;
        }
        
    ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 315 "calc.y"
    {
        TempValue *res1 = (yyvsp[(1) - (3)].expr);
        TempValue *res2 = (yyvsp[(3) - (3)].expr);
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            if (res2->value.i_val == 0) {
                yyerror("Semanthic error: Division by 0");
                (yyval.expr) = 0;
            } else {
                res1->value.i_val = res1->value.i_val / res2->value.i_val;
                (yyval.expr) = res1;
            }
            free(res2);
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_FLOAT) {
            if (res2->value.f_val == 0) {
                yyerror("Semanthic error: Division by 0");
                (yyval.expr) = 0;
            } else {
                res1->value.f_val = res1->value.f_val / res2->value.f_val;
                (yyval.expr) = res1;
            }
            free(res2);
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_FLOAT) {
            if (res2->value.f_val == 0) {
                yyerror("Semanthic error: Division by 0");
                (yyval.expr) = 0;
            } else {
                res1->type = TYPE_FLOAT;
                res1->value.f_val = (float)res1->value.i_val / res2->value.f_val;
                (yyval.expr) = res1;
            }
            free(res2);
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_INT) {
            if (res2->value.i_val == 0) {
                yyerror("Semanthic error: Division by 0");
                (yyval.expr) = 0;
            } else {
                res1->value.f_val = res1->value.f_val / (float)res2->value.i_val;
                (yyval.expr) = res1;
            }
            free(res2);
        }
        else {
            yyerror("Semanthic error: Uncompatible type for '/'");
            (yyval.expr) = 0;
        }   
    ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 364 "calc.y"
    {
        TempValue *res1 = (yyvsp[(1) - (3)].expr);
        TempValue *res2 = (yyvsp[(3) - (3)].expr);
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            if (res2->value.i_val == 0) {
                 yyerror("Semantic error: Mod by 0");
                 (yyval.expr) = 0;
            } else {
                 res1->value.i_val = res1->value.i_val % res2->value.i_val;
                 (yyval.expr) = res1;
            }
            free(res2);
        } else {
            yyerror("Semantic error: Mod requires INTEGER types");
            (yyval.expr) = 0;
        }
    ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 384 "calc.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 385 "calc.y"
    {
        TempValue *res = (yyvsp[(2) - (2)].expr);
        if (res->type == TYPE_INT) {
            res->value.i_val = -res->value.i_val;
        } else if (res->type == TYPE_FLOAT) {
            res->value.f_val = -res->value.f_val;
        } else {
            yyerror("Semantic error: Invalid type for minus");
        }
        (yyval.expr) = res;
    ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 396 "calc.y"
    { (yyval.expr) = (yyvsp[(2) - (2)].expr); ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 400 "calc.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 401 "calc.y"
    { 
        TempValue *res1 = (yyvsp[(1) - (3)].expr);
        TempValue *res2 = (yyvsp[(3) - (3)].expr);
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = (int)pow((double)res1->value.i_val, (double)res2->value.i_val);
        } else {
            float val1 = (res1->type == TYPE_INT) ? (float)res1->value.i_val : res1->value.f_val;
            float val2 = (res2->type == TYPE_INT) ? (float)res2->value.i_val : res2->value.f_val;            
            res1->type = TYPE_FLOAT;
            res1->value.f_val = (float)pow((double)val1, (double)val2);
        }
        free(res2);
        (yyval.expr) = res1;
    ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 418 "calc.y"
    {
        (yyval.expr) = (TempValue*) malloc(sizeof(TempValue));
        (yyval.expr)->type = TYPE_INT;
        (yyval.expr)->value.i_val = (yyvsp[(1) - (1)].ival);
    ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 423 "calc.y"
    {
        (yyval.expr) = (TempValue*) malloc(sizeof(TempValue));
        (yyval.expr)->type = TYPE_FLOAT;
        (yyval.expr)->value.f_val = (yyvsp[(1) - (1)].fval);
    ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 428 "calc.y"
    {
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));
        (yyval.expr)->type = TYPE_BOOL;
        (yyval.expr)->value.b_val = (yyvsp[(1) - (1)].ival);
    ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 433 "calc.y"
    {
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));
        (yyval.expr)->type = TYPE_STRING;
        /* Flex ya hizo el strdup, así que nos lo quedamos */
        (yyval.expr)->value.s_val = (yyvsp[(1) - (1)].sval); 
    ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 439 "calc.y"
    {
        TokenValue *s;
        (yyval.expr) = (TempValue*) malloc(sizeof(TempValue)); 
        
        if (sym_lookup((yyvsp[(1) - (1)].sval), &s) == SYMTAB_NOT_FOUND) {
            yyerror("Semanthic error: Undeclared variable.");
            (yyval.expr)->type = TYPE_INT; (yyval.expr)->value.i_val = 0;
        } else if (!s->inicialized) {
            yyerror("Semanthic error: Uninicialized variable");
            (yyval.expr)->type = TYPE_INT; (yyval.expr)->value.i_val = 0;
        } else {
            (yyval.expr)->type = s->type;
            switch (s->type) {
                case TYPE_INT:
                    (yyval.expr)->value.i_val = s->value.i_val;
                    break;
                case TYPE_FLOAT:
                    (yyval.expr)->value.f_val = s->value.f_val;
                    break;
                case TYPE_STRING:
                    /* Para strings, duplicamos memoria */
                    (yyval.expr)->value.s_val = strdup(s->value.s_val);
                    break;
                case TYPE_BOOL:
                    (yyval.expr)->value.b_val = s->value.b_val;
                    break;
                default:
                    break;
            }
        }
        free((yyvsp[(1) - (1)].sval)); 
    ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 471 "calc.y"
    {
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));
        (yyval.expr)->type = TYPE_FLOAT;
        (yyval.expr)->value.f_val = 3.14159265358979323846;
    ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 476 "calc.y"
    {
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));
        (yyval.expr)->type = TYPE_FLOAT;
        (yyval.expr)->value.f_val = 2.71828182845904523536;
    ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 481 "calc.y"
    {
        struct TempValue *arg = (yyvsp[(3) - (4)].expr);
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: sin() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = sin(val);
        (yyval.expr) = arg; 
    ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 494 "calc.y"
    {
        struct TempValue *arg = (yyvsp[(3) - (4)].expr);
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: cos() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = cos(val); 
        (yyval.expr) = arg; 
    ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 507 "calc.y"
    {
        struct TempValue *arg = (yyvsp[(3) - (4)].expr);
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: tan() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = tan(val);
        (yyval.expr) = arg; 
    ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 520 "calc.y"
    {
        struct TempValue *arg = (yyvsp[(3) - (4)].expr);
        if (arg->type != TYPE_STRING) {
            yyerror("Semantic Error: LEN() requires a string");
            arg->type = TYPE_INT; 
            arg->value.i_val = 0;
        } else {
            int len = strlen(arg->value.s_val);
            free(arg->value.s_val); 
            arg->type = TYPE_INT;
            arg->value.i_val = len;
        }
        (yyval.expr) = arg;
    ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 534 "calc.y"
    {
        struct TempValue *str = (yyvsp[(3) - (8)].expr);
        struct TempValue *start = (yyvsp[(5) - (8)].expr);
        struct TempValue *len = (yyvsp[(7) - (8)].expr);
        if (str->type != TYPE_STRING || start->type != TYPE_INT || len->type != TYPE_INT) {
             yyerror("Semantic Error: SUBSTR expects (string; int; int)");
             (yyval.expr) = str; 
        } else {
             int s_idx = start->value.i_val;
             int l_val = len->value.i_val;
             int max_len = strlen(str->value.s_val);
             if (s_idx < 0) s_idx = 0;
             if (s_idx > max_len) s_idx = max_len;
             if (l_val < 0) l_val = 0;
             if (s_idx + l_val > max_len) l_val = max_len - s_idx;
             char *sub = (char*) malloc(l_val + 1);
             strncpy(sub, str->value.s_val + s_idx, l_val);
             sub[l_val] = '\0'; // Terminador nulo

             free(str->value.s_val);
             str->value.s_val = sub;
             (yyval.expr) = str;
        }
        free(start);
        free(len);
    ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 561 "calc.y"
    {
        TokenValue *s;
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));

        /* 1. Buscamos la variable principal (el struct) */
        if (sym_lookup((yyvsp[(1) - (3)].sval), &s) == SYMTAB_NOT_FOUND) {
            yyerror("Semantic Error: Struct variable not found");
            (yyval.expr)->type = TYPE_INT; (yyval.expr)->value.i_val = 0;
        } else if (s->type != TYPE_STRUCT) {
            yyerror("Semantic Error: Variable is not a struct");
            (yyval.expr)->type = TYPE_INT; (yyval.expr)->value.i_val = 0;
        } else {
            /* 2. Buscamos el campo dentro de su lista */
            struct Token *field = find_field(s->value.tokens, (yyvsp[(3) - (3)].sval));
            
            if (field == NULL) {
                yyerror("Semantic Error: Field not found in struct");
                (yyval.expr)->type = TYPE_INT; (yyval.expr)->value.i_val = 0;
            } else {
                /* 3. ¡Éxito! Copiamos tipo y valor al resultado temporal */
                (yyval.expr)->type = field->type;
                
                switch(field->type) {
                    case TYPE_INT: (yyval.expr)->value.i_val = field->value.i_val; break;
                    case TYPE_FLOAT: (yyval.expr)->value.f_val = field->value.f_val; break;
                    case TYPE_BOOL: (yyval.expr)->value.b_val = field->value.b_val; break;
                    case TYPE_STRING: (yyval.expr)->value.s_val = strdup(field->value.s_val); break;
                    default: break;
                }
            }
        }
        free((yyvsp[(1) - (3)].sval)); free((yyvsp[(3) - (3)].sval)); /* Limpieza de los nombres */
    ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 594 "calc.y"
    {
        (yyval.expr) = (yyvsp[(2) - (3)].expr); 
    ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 600 "calc.y"
    {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_INT;
        val->inicialized=false;
        if (sym_add((yyvsp[(2) - (2)].sval), &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free((yyvsp[(2) - (2)].sval));
        } else {
            printf("BISON: (%s) -> INTEGER.\n", (yyvsp[(2) - (2)].sval));
        }
    ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 612 "calc.y"
    {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_FLOAT;
        val->inicialized=false;
        if (sym_add((yyvsp[(2) - (2)].sval), &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free((yyvsp[(2) - (2)].sval));
        } else {
            printf("BISON: (%s) -> FLOAT.\n", (yyvsp[(2) - (2)].sval));
        }
    ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 624 "calc.y"
    {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_STRING;
        val->inicialized=false;
        if (sym_add((yyvsp[(2) - (2)].sval), &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free((yyvsp[(2) - (2)].sval));
        } else {
            printf("BISON: (%s) -> STRING.\n", (yyvsp[(2) - (2)].sval));
        }
    ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 636 "calc.y"
    {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_BOOL;
        val->inicialized=false;
        if (sym_add((yyvsp[(2) - (2)].sval), &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free((yyvsp[(2) - (2)].sval));
        } else {
            printf("BISON: (%s) -> BOOL.\n", (yyvsp[(2) - (2)].sval));
        }
    ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 649 "calc.y"
    {
        /* $2: Nombre del tipo (ej: "Punto") */
        /* $4: Plantilla de campos (x, y) */
        /* $6: Lista de variables (p1, p2) */
        
        printf("BISON: Defining struct type '%s'\n", (yyvsp[(2) - (6)].sval));
        
        /* Recorremos la lista de variables (p1, p2...) */
        struct Token *current_var = (yyvsp[(6) - (6)].tokens);
        while (current_var != NULL) {
            
            /* 1. Crear la variable en memoria */
            TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
            val->type = TYPE_STRUCT;
            val->inicialized = true;
            
            /* 2. ¡IMPORTANTE! Darle su propia COPIA de los campos */
            val->value.tokens = copy_tokens((yyvsp[(4) - (6)].tokens)); 
            
            /* 3. Registrar en la Tabla de Símbolos */
            if (sym_add(current_var->name, &val) == SYMTAB_DUPLICATE) {
                yyerror("SEMANTIC ERROR: Duplicate variable in struct declaration");
                free(val); /* (Deberíamos liberar también la lista copiada) */
                free(current_var->name);
            } else {
                printf("BISON: Struct instance '%s' created.\n", current_var->name);
            }
            
            /* Avanzar al siguiente ID (p2...) y limpiar el nodo auxiliar */
            struct Token *temp = current_var;
            current_var = current_var->next;
            free(temp); /* Liberamos el nodo de la lista de IDs */
        }
        
        /* Limpieza final */
        free((yyvsp[(2) - (6)].sval)); /* Nombre del tipo */
        /* Deberíamos liberar la plantilla original $4, ya que hemos hecho copias */
        /* (Te dejo esa limpieza como opcional para no complicar más) */
    ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 691 "calc.y"
    { 
        TokenValue *s;
        struct TempValue *res = (yyvsp[(3) - (3)].expr); 

        if (sym_lookup((yyvsp[(1) - (3)].sval), &s) == SYMTAB_NOT_FOUND) {
            yyerror("SEMANTIC ERROR: Variable not found");
        } else {
            if (s->type != res->type) {
                yyerror("SEMANTIC ERROR: Incompatible types in assignment");
                printf("Error detail: Variable is type %d, Value is type %d\n", s->type, res->type);
            } else {
                switch (s->type) {
                    case TYPE_INT:
                        s->value.i_val = res->value.i_val;
                        break;
                    case TYPE_FLOAT:
                        s->value.f_val = res->value.f_val;
                        break;
                    case TYPE_BOOL:
                        s->value.b_val = res->value.b_val;
                        break;
                    case TYPE_STRING:
                        if (s->inicialized && s->value.s_val) {
                            free(s->value.s_val);
                        }
                        s->value.s_val = strdup(res->value.s_val);
                        break;
                    default:
                        break;
                }
                s->inicialized = true;
                printf("BISON: Assigned variable '%s'\n", (yyvsp[(1) - (3)].sval));
            }
        }
        free((yyvsp[(1) - (3)].sval));
        if (res->type == TYPE_STRING) {
            free(res->value.s_val);
        }
        free(res);
    ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 732 "calc.y"
    {
        TokenValue *s;
        struct TempValue *res = (yyvsp[(5) - (5)].expr); /* El valor calculado (derecha) */

        /* 1. Buscar Struct */
        if (sym_lookup((yyvsp[(1) - (5)].sval), &s) == SYMTAB_NOT_FOUND) {
            yyerror("Error: Struct variable not found");
        } else if (s->type != TYPE_STRUCT) {
            yyerror("Error: Variable is not a struct");
        } else {
            /* 2. Buscar Campo */
            struct Token *field = find_field(s->value.tokens, (yyvsp[(3) - (5)].sval));
            
            if (field == NULL) {
                yyerror("Error: Field not found in struct");
            } else {
                /* 3. Chequear compatibilidad de tipos */
                if (field->type != res->type) {
                    yyerror("Error: Type mismatch in field assignment");
                } else {
                    /* 4. Asignar el valor directamente al campo */
                    switch(field->type) {
                        case TYPE_INT:   field->value.i_val = res->value.i_val; break;
                        case TYPE_FLOAT: field->value.f_val = res->value.f_val; break;
                        case TYPE_BOOL:  field->value.b_val = res->value.b_val; break;
                        case TYPE_STRING: 
                            /* (Aquí podrías hacer free si ya tenía valor, pero simplificamos) */
                            field->value.s_val = strdup(res->value.s_val); 
                            break;
                        default: break;
                    }
                    printf("BISON: Assigned field %s.%s\n", (yyvsp[(1) - (5)].sval), (yyvsp[(3) - (5)].sval));
                }
            }
        }
        free((yyvsp[(1) - (5)].sval)); free((yyvsp[(3) - (5)].sval)); 
        /* free(res); (Depende de si necesitas liberar el TempValue aquí o lo hace Bison) */
    ;}
    break;



/* Line 1464 of yacc.c  */
#line 2509 "calc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 772 "calc.y"


void print_result(struct TempValue *res) {
    if (!res) return;
    switch (res->type) {
        case TYPE_INT:
            printf("%d (TYPE_INT)\n", res->value.i_val);
            break;
        case TYPE_FLOAT:
            printf("%f (TYPE_FLOAT)\n", res->value.f_val);
            break;
        case TYPE_STRING:
            printf("%s (TYPE_STRING)\n", res->value.s_val);
            free(res->value.s_val); /* Liberamos la copia temporal */
            break;
        case TYPE_BOOL:
            printf("%s (TYPE_BOOL)\n", res->value.b_val ? "true" : "false");
            break;
        default:
            break;
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "LINE %d: Syntax Error - %s\n", yylineno, s);
}

struct TempValue* compare(struct TempValue* v1, struct TempValue* v2, int op) {
    struct TempValue* res = (struct TempValue*) malloc(sizeof(struct TempValue));
    res->type = TYPE_BOOL;
    
    /* 1. Obtenir els valors com a float per poder comparar INT amb FLOAT */
    float val1 = 0.0, val2 = 0.0;
    
    /* Extreure valor 1 */
    if (v1->type == TYPE_INT) val1 = (float)v1->value.i_val;
    else if (v1->type == TYPE_FLOAT) val1 = v1->value.f_val;
    else {
        /* Opcional: Gestionar error si intentes comparar strings o bools amb < > */
        /* Per simplicitat assumim 0 si no és número */
    }

    /* Extreure valor 2 */
    if (v2->type == TYPE_INT) val2 = (float)v2->value.i_val;
    else if (v2->type == TYPE_FLOAT) val2 = v2->value.f_val;
    else {
        /* Idem */
    }

    /* 2. Calcular el resultat */
    int r = 0;
    switch(op) {
        case EQ: r = (val1 == val2); break;
        case NE: r = (val1 != val2); break; /* Has definit el token com NE */
        case LT: r = (val1 < val2); break;
        case LE: r = (val1 <= val2); break;
        case GT: r = (val1 > val2); break;
        case GE: r = (val1 >= val2); break;
    }

    res->value.b_val = r;
    
    /* 3. Neteja de memòria: Els operands v1 i v2 ja no es necessiten */
    free(v1); 
    free(v2);
    
    return res;
}

struct Token* find_field(struct Token* list, char* name) {
    struct Token *current = list;
    while (current != NULL) {
        /* strcmp devuelve 0 si son iguales */
        if (strcmp(current->name, name) == 0) {
            return current; /* ¡Encontrado! */
        }
        current = current->next;
    }
    return NULL; /* No existe ese campo */
}

/* Copia profunda de la lista de campos para que cada variable tenga la suya propia */
struct Token* copy_tokens(struct Token* source) {
    if (source == NULL) return NULL;
    
    struct Token *new_node = (struct Token*) malloc(sizeof(struct Token));
    /* Copiamos los datos básicos */
    new_node->name = strdup(source->name);
    new_node->type = source->type;
    new_node->value = source->value; /* Copia la unión (inicializada a 0/NULL) */
    
    /* Recursión para copiar el resto de la lista */
    new_node->next = copy_tokens(source->next);
    
    return new_node;
}

int main(int argc, char **argv) {
    
    /* 1. Comprobamos que nos pasen 2 argumentos (entrada y salida) */
    if (argc != 3) {
        fprintf(stderr, "Uso correcto: %s <fichero_entrada> <fichero_salida>\n", argv[0]);
        return 1;
    }

    /* 2. Abrimos el archivo de ENTRADA en modo lectura ("r") */
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error: No se pudo abrir el archivo de entrada '%s'\n", argv[1]);
        return 1;
    }

    /* 3. Le decimos a Flex que lea de este archivo en vez de la consola */
    yyin = input;

    /* 4. Redirigimos la SALIDA estándar (stdout) al archivo de salida */
    /* De esta forma, todos tus printf() irán al archivo automáticamente */
    if (freopen(argv[2], "w", stdout) == NULL) {
        fprintf(stderr, "Error: No se pudo crear el archivo de salida '%s'\n", argv[2]);
        fclose(input);
        return 1;
    }

    /* 5. (Opcional) Mensaje de inicio para el log de errores (stderr) */
    fprintf(stderr, "--- Iniciando Compilacion ---\n");
    fprintf(stderr, "Entrada: %s\n", argv[1]);
    fprintf(stderr, "Salida:  %s\n", argv[2]);

    /* 6. Ejecutamos el parser */
    yyparse();

    /* 7. Cerramos el archivo de entrada (stdout se cierra solo al terminar) */
    fclose(input);
    
    fprintf(stderr, "--- Fin de la Compilacion ---\n");
    return 0;
}
