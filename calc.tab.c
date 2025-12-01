/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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

#line 97 "calc.tab.c"

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

#include "calc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_STRING = 7,                     /* STRING  */
  YYSYMBOL_BOOL = 8,                       /* BOOL  */
  YYSYMBOL_EOL = 9,                        /* EOL  */
  YYSYMBOL_FLOAT_LITERAL = 10,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 11,            /* STRING_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 12,              /* BOOL_LITERAL  */
  YYSYMBOL_ASSIGN = 13,                    /* ASSIGN  */
  YYSYMBOL_POWER = 14,                     /* POWER  */
  YYSYMBOL_EQ = 15,                        /* EQ  */
  YYSYMBOL_LE = 16,                        /* LE  */
  YYSYMBOL_GE = 17,                        /* GE  */
  YYSYMBOL_NE = 18,                        /* NE  */
  YYSYMBOL_LT = 19,                        /* LT  */
  YYSYMBOL_GT = 20,                        /* GT  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_PI = 24,                        /* PI  */
  YYSYMBOL_E = 25,                         /* E  */
  YYSYMBOL_SIN = 26,                       /* SIN  */
  YYSYMBOL_COS = 27,                       /* COS  */
  YYSYMBOL_TAN = 28,                       /* TAN  */
  YYSYMBOL_LEN = 29,                       /* LEN  */
  YYSYMBOL_STRUCT = 30,                    /* STRUCT  */
  YYSYMBOL_31_ = 31,                       /* ','  */
  YYSYMBOL_32_ = 32,                       /* ';'  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '%'  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* '.'  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_line = 45,                      /* line  */
  YYSYMBOL_or_predicate = 46,              /* or_predicate  */
  YYSYMBOL_and_predicate = 47,             /* and_predicate  */
  YYSYMBOL_not_predicate = 48,             /* not_predicate  */
  YYSYMBOL_predicate = 49,                 /* predicate  */
  YYSYMBOL_token_list = 50,                /* token_list  */
  YYSYMBOL_id_list = 51,                   /* id_list  */
  YYSYMBOL_token_decl = 52,                /* token_decl  */
  YYSYMBOL_expression = 53,                /* expression  */
  YYSYMBOL_term = 54,                      /* term  */
  YYSYMBOL_unary = 55,                     /* unary  */
  YYSYMBOL_pow = 56,                       /* pow  */
  YYSYMBOL_atom = 57,                      /* atom  */
  YYSYMBOL_declaration = 58,               /* declaration  */
  YYSYMBOL_assignation = 59                /* assignation  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    37,     2,     2,
      38,    39,    35,    33,    31,    34,    40,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    69,    69,    70,    74,    79,    80,    81,    82,    86,
      87,    96,    97,   106,   107,   119,   120,   121,   122,   123,
     124,   125,   129,   132,   139,   146,   157,   164,   171,   178,
     188,   189,   219,   251,   252,   282,   331,   351,   352,   363,
     367,   368,   385,   390,   395,   400,   406,   438,   443,   448,
     461,   474,   487,   502,   535,   541,   553,   565,   577,   590,
     632,   671
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "ID", "INT",
  "FLOAT", "STRING", "BOOL", "EOL", "FLOAT_LITERAL", "STRING_LITERAL",
  "BOOL_LITERAL", "ASSIGN", "POWER", "EQ", "LE", "GE", "NE", "LT", "GT",
  "AND", "OR", "NOT", "PI", "E", "SIN", "COS", "TAN", "LEN", "STRUCT",
  "','", "';'", "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "')'", "'.'",
  "'{'", "'}'", "$accept", "program", "line", "or_predicate",
  "and_predicate", "not_predicate", "predicate", "token_list", "id_list",
  "token_decl", "expression", "term", "unary", "pow", "atom",
  "declaration", "assignation", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-26)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -26,    24,   -26,     4,   -26,    -3,    19,    36,    37,    39,
     -26,   -26,   -26,   -26,    56,   -26,   -26,    18,    23,    27,
      40,    82,    88,    88,    56,   -26,    33,    74,   -26,   -26,
     -12,   -17,   -26,    83,   -26,    87,    92,   -26,    56,    98,
     -26,   -26,   -26,   -26,    63,   -26,    88,    88,    88,    88,
      64,   -26,   -26,   -13,   -26,    56,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,   120,   -26,
     -26,    84,    91,   103,   -22,    30,    38,    54,    68,   -26,
      74,   -26,   -18,   -18,   -18,   -18,   -18,   -18,   -17,   -17,
     -26,   -26,   -26,   -26,    56,   -26,   -26,   -26,   -26,   -26,
     104,   105,   106,   107,    76,    68,    84,    95,    96,    97,
     101,   115,   -26,   -26,   -26,   -26,   -26,   -26,    89,   121,
     -26
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,    42,    46,     0,     0,     0,     0,
       7,    43,    45,    44,     0,    47,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     0,     9,    11,    13,
      15,    30,    33,    37,    40,     0,     0,     8,     0,     0,
      55,    56,    57,    58,    46,    14,     0,     0,     0,     0,
       0,    39,    38,     0,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,    60,    53,     0,     0,     0,     0,     0,     0,    54,
      10,    12,    16,    19,    21,    17,    18,    20,    31,    32,
      34,    35,    36,    41,     0,    53,    49,    50,    51,    52,
       0,     0,     0,     0,     0,    22,    61,     0,     0,     0,
       0,     0,    23,    26,    27,    28,    29,    24,    59,     0,
      25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -26,   -26,   -26,   -24,    79,   122,    81,    51,   -26,   -26,
      93,   -25,   -21,   -26,    67,   -26,   -26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    25,    26,    27,    28,    29,   104,   118,   105,
      30,    31,    32,    33,    34,    35,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      53,    51,    52,    57,    58,    59,    60,    61,    62,    55,
      38,    63,    64,    37,    71,    63,    64,    96,    65,    66,
      67,    63,    64,    40,     2,     3,    79,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    39,    88,    89,
      41,    42,    54,    43,    90,    91,    92,    14,    15,    16,
      17,    18,    19,    20,    21,    55,    46,    22,    23,     4,
      44,    47,    24,    63,    64,    48,    11,    12,    13,    97,
     106,    63,    64,   100,   101,   102,   103,    98,    49,    14,
      15,    16,    17,    18,    19,    20,    50,    63,    64,    22,
      23,     4,    44,    99,    24,    56,    69,    68,    11,    12,
      13,    70,    72,    73,    94,    78,    55,    95,   107,   108,
     109,   110,    15,    16,    17,    18,    19,    20,   111,   117,
     119,    22,    23,     4,    44,   120,    24,   113,   114,   115,
      11,    12,    13,   116,    80,    93,    45,    81,     0,    74,
      75,    76,    77,     0,    15,    16,    17,    18,    19,    20,
      82,    83,    84,    85,    86,    87,   112,     0,    24
};

static const yytype_int8 yycheck[] =
{
      24,    22,    23,    15,    16,    17,    18,    19,    20,    22,
      13,    33,    34,     9,    38,    33,    34,    39,    35,    36,
      37,    33,    34,     4,     0,     1,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    40,    63,    64,
       4,     4,     9,     4,    65,    66,    67,    23,    24,    25,
      26,    27,    28,    29,    30,    22,    38,    33,    34,     3,
       4,    38,    38,    33,    34,    38,    10,    11,    12,    39,
      94,    33,    34,     5,     6,     7,     8,    39,    38,    23,
      24,    25,    26,    27,    28,    29,     4,    33,    34,    33,
      34,     3,     4,    39,    38,    21,     9,    14,    10,    11,
      12,     9,     4,    40,    13,    41,    22,     4,     4,     4,
       4,     4,    24,    25,    26,    27,    28,    29,    42,     4,
      31,    33,    34,     3,     4,     4,    38,    32,    32,    32,
      10,    11,    12,    32,    55,    68,    14,    56,    -1,    46,
      47,    48,    49,    -1,    24,    25,    26,    27,    28,    29,
      57,    58,    59,    60,    61,    62,   105,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    44,     0,     1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    23,    24,    25,    26,    27,    28,
      29,    30,    33,    34,    38,    45,    46,    47,    48,    49,
      53,    54,    55,    56,    57,    58,    59,     9,    13,    40,
       4,     4,     4,     4,     4,    48,    38,    38,    38,    38,
       4,    55,    55,    46,     9,    22,    21,    15,    16,    17,
      18,    19,    20,    33,    34,    35,    36,    37,    14,     9,
       9,    46,     4,    40,    53,    53,    53,    53,    41,    39,
      47,    49,    53,    53,    53,    53,    53,    53,    54,    54,
      55,    55,    55,    57,    13,     4,    39,    39,    39,    39,
       5,     6,     7,     8,    50,    52,    46,     4,     4,     4,
       4,    42,    50,    32,    32,    32,    32,     4,    51,    31,
       4
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    45,    45,    45,    46,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      53,    53,    53,    54,    54,    54,    54,    55,    55,    55,
      56,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    58,
      59,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     1,     2,     1,
       3,     1,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     1,     2,     1,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     2,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     4,     4,     3,     3,     2,     2,     2,     2,     6,
       3,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 4: /* line: or_predicate EOL  */
#line 74 "calc.y"
                     {
        printf("BISON: Result: ");
        print_result((yyvsp[-1].expr)); 
        free((yyvsp[-1].expr));
    }
#line 1229 "calc.tab.c"
    break;

  case 5: /* line: declaration EOL  */
#line 79 "calc.y"
                      { printf("BISON: DECLARATION TRACKED.\n"); }
#line 1235 "calc.tab.c"
    break;

  case 6: /* line: assignation EOL  */
#line 80 "calc.y"
                      { printf("BISON: ASSIGNATION TRACKED.\n"); }
#line 1241 "calc.tab.c"
    break;

  case 7: /* line: EOL  */
#line 81 "calc.y"
                 { printf("BISON: EOL\n"); }
#line 1247 "calc.tab.c"
    break;

  case 8: /* line: error EOL  */
#line 82 "calc.y"
                 { printf("BISON: Detected error. Jumping to the next line.\n"); yyerrok; }
#line 1253 "calc.tab.c"
    break;

  case 9: /* or_predicate: and_predicate  */
#line 86 "calc.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1259 "calc.tab.c"
    break;

  case 10: /* or_predicate: or_predicate OR and_predicate  */
#line 87 "calc.y"
                                    {
        struct TempValue *res = (yyvsp[-2].expr);
        res->value.b_val = ((yyvsp[-2].expr)->value.b_val || (yyvsp[0].expr)->value.b_val);
        free((yyvsp[0].expr));
        (yyval.expr) = res;
    }
#line 1270 "calc.tab.c"
    break;

  case 11: /* and_predicate: not_predicate  */
#line 96 "calc.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1276 "calc.tab.c"
    break;

  case 12: /* and_predicate: and_predicate AND predicate  */
#line 97 "calc.y"
                                  {
        struct TempValue *res = (yyvsp[-2].expr);
        res->value.b_val = ((yyvsp[-2].expr)->value.b_val && (yyvsp[0].expr)->value.b_val);
        free((yyvsp[0].expr));
        (yyval.expr) = res;
    }
#line 1287 "calc.tab.c"
    break;

  case 13: /* not_predicate: predicate  */
#line 106 "calc.y"
              { (yyval.expr) = (yyvsp[0].expr); }
#line 1293 "calc.tab.c"
    break;

  case 14: /* not_predicate: NOT not_predicate  */
#line 107 "calc.y"
                        {
        struct TempValue *res = (yyvsp[0].expr);
        if (res->type != TYPE_BOOL) {
            yyerror("Semantic Error: NOT requires boolean operand");
        } else {
            res->value.b_val = !res->value.b_val;
        }
        (yyval.expr) = res;
    }
#line 1307 "calc.tab.c"
    break;

  case 15: /* predicate: expression  */
#line 119 "calc.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1313 "calc.tab.c"
    break;

  case 16: /* predicate: expression EQ expression  */
#line 120 "calc.y"
                               { (yyval.expr) = compare((yyvsp[-2].expr), (yyvsp[0].expr), EQ); }
#line 1319 "calc.tab.c"
    break;

  case 17: /* predicate: expression NE expression  */
#line 121 "calc.y"
                               { (yyval.expr) = compare((yyvsp[-2].expr), (yyvsp[0].expr), NE); }
#line 1325 "calc.tab.c"
    break;

  case 18: /* predicate: expression LT expression  */
#line 122 "calc.y"
                               { (yyval.expr) = compare((yyvsp[-2].expr), (yyvsp[0].expr), LT); }
#line 1331 "calc.tab.c"
    break;

  case 19: /* predicate: expression LE expression  */
#line 123 "calc.y"
                               { (yyval.expr) = compare((yyvsp[-2].expr), (yyvsp[0].expr), LE); }
#line 1337 "calc.tab.c"
    break;

  case 20: /* predicate: expression GT expression  */
#line 124 "calc.y"
                               { (yyval.expr) = compare((yyvsp[-2].expr), (yyvsp[0].expr), GT); }
#line 1343 "calc.tab.c"
    break;

  case 21: /* predicate: expression GE expression  */
#line 125 "calc.y"
                               { (yyval.expr) = compare((yyvsp[-2].expr), (yyvsp[0].expr), GE); }
#line 1349 "calc.tab.c"
    break;

  case 22: /* token_list: token_decl  */
#line 129 "calc.y"
               { 
        (yyval.tokens) = (yyvsp[0].tokens);
    }
#line 1357 "calc.tab.c"
    break;

  case 23: /* token_list: token_decl token_list  */
#line 132 "calc.y"
                            {
        (yyvsp[-1].tokens)->next = (yyvsp[0].tokens); 
        (yyval.tokens) = (yyvsp[-1].tokens); 
    }
#line 1366 "calc.tab.c"
    break;

  case 24: /* id_list: ID  */
#line 139 "calc.y"
       {
        /* Creamos un nodo solo para guardar el nombre */
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[0].sval); 
        t->next = NULL;
        (yyval.tokens) = t;
    }
#line 1378 "calc.tab.c"
    break;

  case 25: /* id_list: id_list ',' ID  */
#line 146 "calc.y"
                     {
        /* Añadimos el nuevo ID al final o principio de la lista */
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[0].sval);
        t->next = (yyvsp[-2].tokens); /* Lo ponemos al principio para ir rápido (orden inverso, no importa) */
        (yyval.tokens) = t;
    }
#line 1390 "calc.tab.c"
    break;

  case 26: /* token_decl: INT ID ';'  */
#line 157 "calc.y"
               {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[-1].sval);      /* Guardamos el nombre "x" */
        t->type = TYPE_INT;
        t->next = NULL;
        (yyval.tokens) = t;            /* Subimos el puntero */
    }
#line 1402 "calc.tab.c"
    break;

  case 27: /* token_decl: FLOAT ID ';'  */
#line 164 "calc.y"
                   {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[-1].sval);
        t->type = TYPE_FLOAT;
        t->next = NULL;
        (yyval.tokens) = t;
    }
#line 1414 "calc.tab.c"
    break;

  case 28: /* token_decl: STRING ID ';'  */
#line 171 "calc.y"
                    {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[-1].sval);
        t->type = TYPE_STRING;
        t->next = NULL;
        (yyval.tokens) = t;
    }
#line 1426 "calc.tab.c"
    break;

  case 29: /* token_decl: BOOL ID ';'  */
#line 178 "calc.y"
                  {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = (yyvsp[-1].sval);
        t->type = TYPE_BOOL;
        t->next = NULL;
        (yyval.tokens) = t;
    }
#line 1438 "calc.tab.c"
    break;

  case 30: /* expression: term  */
#line 188 "calc.y"
         { (yyval.expr) = (yyvsp[0].expr); }
#line 1444 "calc.tab.c"
    break;

  case 31: /* expression: expression '+' term  */
#line 189 "calc.y"
                          {
        TempValue *res1 = (yyvsp[-2].expr);
        TempValue *res2 = (yyvsp[0].expr);
        
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = res1->value.i_val + res2->value.i_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_FLOAT) {
            res1->value.f_val = res1->value.f_val + res2->value.f_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_FLOAT) {
            res1->type = TYPE_FLOAT;
            res1->value.f_val = (float)res1->value.i_val + res2->value.f_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_INT) {
            res1->value.f_val = res1->value.f_val + (float)res2->value.i_val;
            free(res2);
            (yyval.expr) = res1;
        }
        else {
            yyerror("Semanthic error: Uncompatible type for '+'");
            (yyval.expr) = 0;
        }
    }
#line 1479 "calc.tab.c"
    break;

  case 32: /* expression: expression '-' term  */
#line 219 "calc.y"
                          {
        TempValue *res1 = (yyvsp[-2].expr);
        TempValue *res2 = (yyvsp[0].expr);
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
    }
#line 1513 "calc.tab.c"
    break;

  case 33: /* term: unary  */
#line 251 "calc.y"
          { (yyval.expr) = (yyvsp[0].expr); }
#line 1519 "calc.tab.c"
    break;

  case 34: /* term: term '*' unary  */
#line 252 "calc.y"
                     {
        TempValue *res1 = (yyvsp[-2].expr);
        TempValue *res2 = (yyvsp[0].expr);
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
        
    }
#line 1554 "calc.tab.c"
    break;

  case 35: /* term: term '/' unary  */
#line 282 "calc.y"
                     {
        TempValue *res1 = (yyvsp[-2].expr);
        TempValue *res2 = (yyvsp[0].expr);
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
    }
#line 1608 "calc.tab.c"
    break;

  case 36: /* term: term '%' unary  */
#line 331 "calc.y"
                     {
        TempValue *res1 = (yyvsp[-2].expr);
        TempValue *res2 = (yyvsp[0].expr);
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
    }
#line 1630 "calc.tab.c"
    break;

  case 37: /* unary: pow  */
#line 351 "calc.y"
        { (yyval.expr) = (yyvsp[0].expr); }
#line 1636 "calc.tab.c"
    break;

  case 38: /* unary: '-' unary  */
#line 352 "calc.y"
                {
        TempValue *res = (yyvsp[0].expr);
        if (res->type == TYPE_INT) {
            res->value.i_val = -res->value.i_val;
        } else if (res->type == TYPE_FLOAT) {
            res->value.f_val = -res->value.f_val;
        } else {
            yyerror("Semantic error: Invalid type for minus");
        }
        (yyval.expr) = res;
    }
#line 1652 "calc.tab.c"
    break;

  case 39: /* unary: '+' unary  */
#line 363 "calc.y"
                { (yyval.expr) = (yyvsp[0].expr); }
#line 1658 "calc.tab.c"
    break;

  case 40: /* pow: atom  */
#line 367 "calc.y"
         { (yyval.expr) = (yyvsp[0].expr); }
#line 1664 "calc.tab.c"
    break;

  case 41: /* pow: pow POWER atom  */
#line 368 "calc.y"
                     { 
        TempValue *res1 = (yyvsp[-2].expr);
        TempValue *res2 = (yyvsp[0].expr);
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
    }
#line 1683 "calc.tab.c"
    break;

  case 42: /* atom: NUMBER  */
#line 385 "calc.y"
           {
        (yyval.expr) = (TempValue*) malloc(sizeof(TempValue));
        (yyval.expr)->type = TYPE_INT;
        (yyval.expr)->value.i_val = (yyvsp[0].ival);
    }
#line 1693 "calc.tab.c"
    break;

  case 43: /* atom: FLOAT_LITERAL  */
#line 390 "calc.y"
                    {
        (yyval.expr) = (TempValue*) malloc(sizeof(TempValue));
        (yyval.expr)->type = TYPE_FLOAT;
        (yyval.expr)->value.f_val = (yyvsp[0].fval);
    }
#line 1703 "calc.tab.c"
    break;

  case 44: /* atom: BOOL_LITERAL  */
#line 395 "calc.y"
                   {
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));
        (yyval.expr)->type = TYPE_BOOL;
        (yyval.expr)->value.b_val = (yyvsp[0].ival);
    }
#line 1713 "calc.tab.c"
    break;

  case 45: /* atom: STRING_LITERAL  */
#line 400 "calc.y"
                     {
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));
        (yyval.expr)->type = TYPE_STRING;
        /* Flex ya hizo el strdup, así que nos lo quedamos */
        (yyval.expr)->value.s_val = (yyvsp[0].sval); 
    }
#line 1724 "calc.tab.c"
    break;

  case 46: /* atom: ID  */
#line 406 "calc.y"
         {
        TokenValue *s;
        (yyval.expr) = (TempValue*) malloc(sizeof(TempValue)); 
        
        if (sym_lookup((yyvsp[0].sval), &s) == SYMTAB_NOT_FOUND) {
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
        free((yyvsp[0].sval)); 
    }
#line 1761 "calc.tab.c"
    break;

  case 47: /* atom: PI  */
#line 438 "calc.y"
         {
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));
        (yyval.expr)->type = TYPE_FLOAT;
        (yyval.expr)->value.f_val = 3.14159265358979323846;
    }
#line 1771 "calc.tab.c"
    break;

  case 48: /* atom: E  */
#line 443 "calc.y"
        {
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));
        (yyval.expr)->type = TYPE_FLOAT;
        (yyval.expr)->value.f_val = 2.71828182845904523536;
    }
#line 1781 "calc.tab.c"
    break;

  case 49: /* atom: SIN '(' expression ')'  */
#line 448 "calc.y"
                             {
        struct TempValue *arg = (yyvsp[-1].expr);
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: sin() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = sin(val);
        (yyval.expr) = arg; 
    }
#line 1799 "calc.tab.c"
    break;

  case 50: /* atom: COS '(' expression ')'  */
#line 461 "calc.y"
                             {
        struct TempValue *arg = (yyvsp[-1].expr);
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: cos() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = cos(val); 
        (yyval.expr) = arg; 
    }
#line 1817 "calc.tab.c"
    break;

  case 51: /* atom: TAN '(' expression ')'  */
#line 474 "calc.y"
                             {
        struct TempValue *arg = (yyvsp[-1].expr);
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: tan() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = tan(val);
        (yyval.expr) = arg; 
    }
#line 1835 "calc.tab.c"
    break;

  case 52: /* atom: LEN '(' expression ')'  */
#line 487 "calc.y"
                             {
        struct TempValue *arg = (yyvsp[-1].expr);
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
    }
#line 1854 "calc.tab.c"
    break;

  case 53: /* atom: ID '.' ID  */
#line 502 "calc.y"
                {
        TokenValue *s;
        (yyval.expr) = (struct TempValue*) malloc(sizeof(struct TempValue));

        /* 1. Buscamos la variable principal (el struct) */
        if (sym_lookup((yyvsp[-2].sval), &s) == SYMTAB_NOT_FOUND) {
            yyerror("Semantic Error: Struct variable not found");
            (yyval.expr)->type = TYPE_INT; (yyval.expr)->value.i_val = 0;
        } else if (s->type != TYPE_STRUCT) {
            yyerror("Semantic Error: Variable is not a struct");
            (yyval.expr)->type = TYPE_INT; (yyval.expr)->value.i_val = 0;
        } else {
            /* 2. Buscamos el campo dentro de su lista */
            struct Token *field = find_field(s->value.tokens, (yyvsp[0].sval));
            
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
        free((yyvsp[-2].sval)); free((yyvsp[0].sval)); /* Limpieza de los nombres */
    }
#line 1892 "calc.tab.c"
    break;

  case 54: /* atom: '(' or_predicate ')'  */
#line 535 "calc.y"
                           {
        (yyval.expr) = (yyvsp[-1].expr); 
    }
#line 1900 "calc.tab.c"
    break;

  case 55: /* declaration: INT ID  */
#line 541 "calc.y"
           {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_INT;
        val->inicialized=false;
        if (sym_add((yyvsp[0].sval), &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free((yyvsp[0].sval));
        } else {
            printf("BISON: (%s) -> INTEGER.\n", (yyvsp[0].sval));
        }
    }
#line 1917 "calc.tab.c"
    break;

  case 56: /* declaration: FLOAT ID  */
#line 553 "calc.y"
               {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_FLOAT;
        val->inicialized=false;
        if (sym_add((yyvsp[0].sval), &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free((yyvsp[0].sval));
        } else {
            printf("BISON: (%s) -> FLOAT.\n", (yyvsp[0].sval));
        }
    }
#line 1934 "calc.tab.c"
    break;

  case 57: /* declaration: STRING ID  */
#line 565 "calc.y"
                {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_STRING;
        val->inicialized=false;
        if (sym_add((yyvsp[0].sval), &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free((yyvsp[0].sval));
        } else {
            printf("BISON: (%s) -> STRING.\n", (yyvsp[0].sval));
        }
    }
#line 1951 "calc.tab.c"
    break;

  case 58: /* declaration: BOOL ID  */
#line 577 "calc.y"
              {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_BOOL;
        val->inicialized=false;
        if (sym_add((yyvsp[0].sval), &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free((yyvsp[0].sval));
        } else {
            printf("BISON: (%s) -> BOOL.\n", (yyvsp[0].sval));
        }
    }
#line 1968 "calc.tab.c"
    break;

  case 59: /* declaration: STRUCT ID '{' token_list '}' id_list  */
#line 590 "calc.y"
                                           {
        /* $2: Nombre del tipo (ej: "Punto") */
        /* $4: Plantilla de campos (x, y) */
        /* $6: Lista de variables (p1, p2) */
        
        printf("BISON: Defining struct type '%s'\n", (yyvsp[-4].sval));
        
        /* Recorremos la lista de variables (p1, p2...) */
        struct Token *current_var = (yyvsp[0].tokens);
        while (current_var != NULL) {
            
            /* 1. Crear la variable en memoria */
            TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
            val->type = TYPE_STRUCT;
            val->inicialized = true;
            
            /* 2. ¡IMPORTANTE! Darle su propia COPIA de los campos */
            val->value.tokens = copy_tokens((yyvsp[-2].tokens)); 
            
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
        free((yyvsp[-4].sval)); /* Nombre del tipo */
        /* Deberíamos liberar la plantilla original $4, ya que hemos hecho copias */
        /* (Te dejo esa limpieza como opcional para no complicar más) */
    }
#line 2012 "calc.tab.c"
    break;

  case 60: /* assignation: ID ASSIGN or_predicate  */
#line 632 "calc.y"
                           { 
        TokenValue *s;
        struct TempValue *res = (yyvsp[0].expr); 

        if (sym_lookup((yyvsp[-2].sval), &s) == SYMTAB_NOT_FOUND) {
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
                }
                s->inicialized = true;
                printf("BISON: Assigned variable '%s'\n", (yyvsp[-2].sval));
            }
        }
        free((yyvsp[-2].sval));
        if (res->type == TYPE_STRING) {
            free(res->value.s_val);
        }
        free(res);
    }
#line 2055 "calc.tab.c"
    break;

  case 61: /* assignation: ID '.' ID ASSIGN or_predicate  */
#line 671 "calc.y"
                                    {
        TokenValue *s;
        struct TempValue *res = (yyvsp[0].expr); /* El valor calculado (derecha) */

        /* 1. Buscar Struct */
        if (sym_lookup((yyvsp[-4].sval), &s) == SYMTAB_NOT_FOUND) {
            yyerror("Error: Struct variable not found");
        } else if (s->type != TYPE_STRUCT) {
            yyerror("Error: Variable is not a struct");
        } else {
            /* 2. Buscar Campo */
            struct Token *field = find_field(s->value.tokens, (yyvsp[-2].sval));
            
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
                    printf("BISON: Assigned field %s.%s\n", (yyvsp[-4].sval), (yyvsp[-2].sval));
                }
            }
        }
        free((yyvsp[-4].sval)); free((yyvsp[-2].sval)); 
        /* free(res); (Depende de si necesitas liberar el TempValue aquí o lo hace Bison) */
    }
#line 2098 "calc.tab.c"
    break;


#line 2102 "calc.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 711 "calc.y"


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

/* ... (Tus includes y definiciones de arriba siguen igual) ... */

/* Añade esto justo debajo de los includes en la sección %{ ... %} o antes del main */
extern FILE *yyin; /* Variable global de Flex para el archivo de entrada */

/* ... (Todo tu código de gramática sigue igual) ... */

/* ... (Tus funciones auxiliares print_result, yyerror, etc. siguen igual) ... */

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
