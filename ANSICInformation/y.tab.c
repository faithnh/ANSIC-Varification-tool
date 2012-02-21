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
#line 1 "ansic_kako.y"


#include <stdio.h>
#include <string.h>

#include "../Library/CSTLString.h"
#include "../Library/StoreInformation.h"
#include "../Library/FlagDatabase.h"
#include "AST.h"
#include "Synbol.h"
#include "Varidate_Statement.h"
#include "PreProcess.h"
#include "ForInformation.h"
#include "FunctionInformation.h"


#define FILE_PATH 512

void yyerror(char const *s);

#define ENABLE_ARGUMENT 2

extern int line;

extern TYPEDEF_TABLE_LIST *typedef_table_list;
extern STRUCT_TABLE_LIST *struct_table_list;
extern VARIABLE_TABLE_LIST *variable_table_list;
ValidateVariableList *varidate_variable_list;
ValidateStatementList *varidate_statement_list;
INCLUDE_LIST *include_list;
ForInformationList *for_information_list;
FUNCTION_INFORMATION_LIST *function_information_list;

AST *programAST;



/* Line 189 of yacc.c  */
#line 110 "y.tab.c"

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
     IDENTIFIER = 258,
     CONSTANT = 259,
     STRING_LITERAL = 260,
     SIZEOF = 261,
     PTR_OP = 262,
     INC_OP = 263,
     DEC_OP = 264,
     LEFT_OP = 265,
     RIGHT_OP = 266,
     LE_OP = 267,
     GE_OP = 268,
     EQ_OP = 269,
     NE_OP = 270,
     AND_OP = 271,
     OR_OP = 272,
     MUL_ASSIGN = 273,
     DIV_ASSIGN = 274,
     MOD_ASSIGN = 275,
     ADD_ASSIGN = 276,
     SUB_ASSIGN = 277,
     LEFT_ASSIGN = 278,
     RIGHT_ASSIGN = 279,
     AND_ASSIGN = 280,
     XOR_ASSIGN = 281,
     OR_ASSIGN = 282,
     TYPE_NAME = 283,
     TYPEDEF = 284,
     EXTERN = 285,
     STATIC = 286,
     AUTO = 287,
     REGISTER = 288,
     INLINE = 289,
     RESTRICT = 290,
     CHAR = 291,
     SHORT = 292,
     INT = 293,
     LONG = 294,
     SIGNED = 295,
     UNSIGNED = 296,
     FLOAT = 297,
     DOUBLE = 298,
     CONST = 299,
     VOLATILE = 300,
     VOID = 301,
     BOOL = 302,
     COMPLEX = 303,
     IMAGINARY = 304,
     STRUCT = 305,
     UNION = 306,
     ENUM = 307,
     ELLIPSIS = 308,
     CASE = 309,
     DEFAULT = 310,
     IF = 311,
     ELSE = 312,
     SWITCH = 313,
     WHILE = 314,
     DO = 315,
     FOR = 316,
     GOTO = 317,
     CONTINUE = 318,
     BREAK = 319,
     RETURN = 320
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CONSTANT 259
#define STRING_LITERAL 260
#define SIZEOF 261
#define PTR_OP 262
#define INC_OP 263
#define DEC_OP 264
#define LEFT_OP 265
#define RIGHT_OP 266
#define LE_OP 267
#define GE_OP 268
#define EQ_OP 269
#define NE_OP 270
#define AND_OP 271
#define OR_OP 272
#define MUL_ASSIGN 273
#define DIV_ASSIGN 274
#define MOD_ASSIGN 275
#define ADD_ASSIGN 276
#define SUB_ASSIGN 277
#define LEFT_ASSIGN 278
#define RIGHT_ASSIGN 279
#define AND_ASSIGN 280
#define XOR_ASSIGN 281
#define OR_ASSIGN 282
#define TYPE_NAME 283
#define TYPEDEF 284
#define EXTERN 285
#define STATIC 286
#define AUTO 287
#define REGISTER 288
#define INLINE 289
#define RESTRICT 290
#define CHAR 291
#define SHORT 292
#define INT 293
#define LONG 294
#define SIGNED 295
#define UNSIGNED 296
#define FLOAT 297
#define DOUBLE 298
#define CONST 299
#define VOLATILE 300
#define VOID 301
#define BOOL 302
#define COMPLEX 303
#define IMAGINARY 304
#define STRUCT 305
#define UNION 306
#define ENUM 307
#define ELLIPSIS 308
#define CASE 309
#define DEFAULT 310
#define IF 311
#define ELSE 312
#define SWITCH 313
#define WHILE 314
#define DO 315
#define FOR 316
#define GOTO 317
#define CONTINUE 318
#define BREAK 319
#define RETURN 320




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 37 "ansic_kako.y"

	AST *val;



/* Line 214 of yacc.c  */
#line 282 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 294 "y.tab.c"

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
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1736

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  243
/* YYNRULES -- Number of states.  */
#define YYNSTATES  423

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    78,     2,     2,     2,    84,    77,     2,
      72,    73,    82,    81,    69,    80,    76,    83,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    70,    66,
      85,    71,    86,    89,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    75,    87,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    90,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,    88,    68,    79,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    13,    15,    20,    24,
      29,    33,    37,    40,    43,    50,    58,    60,    64,    66,
      70,    72,    76,    78,    81,    84,    87,    90,    93,    96,
      99,   102,   105,   110,   112,   117,   121,   125,   129,   133,
     137,   141,   145,   149,   153,   157,   161,   165,   169,   173,
     177,   181,   185,   189,   191,   193,   199,   201,   205,   207,
     209,   211,   213,   215,   217,   219,   221,   223,   225,   227,
     229,   233,   235,   238,   242,   244,   247,   249,   252,   254,
     257,   259,   262,   264,   268,   270,   274,   276,   278,   280,
     282,   284,   286,   288,   290,   292,   294,   296,   298,   300,
     302,   304,   306,   308,   310,   312,   314,   320,   325,   328,
     330,   332,   334,   337,   341,   344,   346,   349,   351,   353,
     357,   359,   362,   366,   371,   377,   383,   390,   393,   395,
     399,   401,   405,   407,   409,   411,   413,   416,   418,   420,
     424,   430,   435,   440,   447,   454,   460,   465,   469,   474,
     479,   483,   485,   488,   491,   495,   497,   500,   502,   506,
     508,   512,   515,   518,   520,   522,   526,   528,   531,   533,
     535,   538,   542,   545,   549,   553,   558,   562,   567,   570,
     574,   578,   583,   585,   589,   594,   596,   599,   603,   608,
     611,   613,   616,   620,   623,   625,   627,   629,   631,   633,
     635,   639,   644,   648,   651,   655,   657,   660,   662,   664,
     666,   669,   675,   683,   689,   691,   695,   697,   701,   703,
     707,   709,   712,   715,   719,   725,   733,   740,   748,   755,
     763,   767,   770,   773,   776,   780,   782,   784,   787,   789,
     791,   796,   800,   802
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     153,     0,    -1,     3,    -1,     4,    -1,     5,    -1,    72,
     103,    73,    -1,    92,    -1,    93,    74,    94,    75,    -1,
      93,    72,    73,    -1,    93,    72,    95,    73,    -1,    93,
      76,     3,    -1,    93,     7,     3,    -1,    93,     8,    -1,
      93,     9,    -1,    72,   131,    73,    67,   135,    68,    -1,
      72,   131,    73,    67,   135,    69,    68,    -1,   101,    -1,
     103,    69,   101,    -1,    96,    -1,    95,    69,    96,    -1,
     100,    -1,    97,   102,    96,    -1,    93,    -1,     8,    97,
      -1,     9,    97,    -1,    77,    98,    -1,    82,    98,    -1,
      81,    98,    -1,    80,    98,    -1,    79,    98,    -1,    78,
      98,    -1,     6,    97,    -1,     6,    72,   131,    73,    -1,
      97,    -1,    72,   131,    73,    98,    -1,    99,    17,    99,
      -1,    99,    16,    99,    -1,    99,    88,    99,    -1,    99,
      87,    99,    -1,    99,    77,    99,    -1,    99,    14,    99,
      -1,    99,    15,    99,    -1,    99,    85,    99,    -1,    99,
      86,    99,    -1,    99,    12,    99,    -1,    99,    13,    99,
      -1,    99,    10,    99,    -1,    99,    11,    99,    -1,    99,
      81,    99,    -1,    99,    80,    99,    -1,    99,    82,    99,
      -1,    99,    83,    99,    -1,    99,    84,    99,    -1,    98,
      -1,    99,    -1,    99,    89,   103,    70,   100,    -1,   100,
      -1,    97,   102,   101,    -1,    71,    -1,    18,    -1,    19,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,   101,    -1,   103,
      69,   101,    -1,   100,    -1,   106,    66,    -1,   106,   107,
      66,    -1,   109,    -1,   109,   106,    -1,   110,    -1,   110,
     106,    -1,   121,    -1,   121,   106,    -1,   122,    -1,   122,
     106,    -1,   108,    -1,   107,    69,   108,    -1,   123,    -1,
     123,    71,   134,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    33,    -1,    46,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    42,    -1,    43,    -1,    40,    -1,
      41,    -1,    47,    -1,    48,    -1,    49,    -1,   111,    -1,
     118,    -1,    28,    -1,   112,     3,    67,   113,    68,    -1,
     112,    67,   113,    68,    -1,   112,     3,    -1,    50,    -1,
      51,    -1,   114,    -1,   113,   114,    -1,   115,   116,    66,
      -1,   110,   115,    -1,   110,    -1,   121,   115,    -1,   121,
      -1,   117,    -1,   116,    69,   117,    -1,   123,    -1,    70,
     104,    -1,   123,    70,   104,    -1,    52,    67,   119,    68,
      -1,    52,     3,    67,   119,    68,    -1,    52,    67,   119,
      69,    68,    -1,    52,     3,    67,   119,    69,    68,    -1,
      52,     3,    -1,   120,    -1,   119,    69,   120,    -1,     3,
      -1,     3,    71,   104,    -1,    44,    -1,    35,    -1,    45,
      -1,    34,    -1,   125,   124,    -1,   124,    -1,     3,    -1,
      72,   123,    73,    -1,   124,    74,   126,   101,    75,    -1,
     124,    74,   126,    75,    -1,   124,    74,   101,    75,    -1,
     124,    74,    31,   126,   101,    75,    -1,   124,    74,   126,
      31,   101,    75,    -1,   124,    74,   126,    82,    75,    -1,
     124,    74,    82,    75,    -1,   124,    74,    75,    -1,   124,
      72,   127,    73,    -1,   124,    72,   130,    73,    -1,   124,
      72,    73,    -1,    82,    -1,    82,   126,    -1,    82,   125,
      -1,    82,   126,   125,    -1,   121,    -1,   126,   121,    -1,
     128,    -1,   128,    69,    53,    -1,   129,    -1,   128,    69,
     129,    -1,   106,   123,    -1,   106,   132,    -1,   106,    -1,
       3,    -1,   130,    69,     3,    -1,   115,    -1,   115,   132,
      -1,   125,    -1,   133,    -1,   125,   133,    -1,    72,   132,
      73,    -1,    74,    75,    -1,    74,   101,    75,    -1,   133,
      74,    75,    -1,   133,    74,   101,    75,    -1,    74,    82,
      75,    -1,   133,    74,    82,    75,    -1,    72,    73,    -1,
      72,   127,    73,    -1,   133,    72,    73,    -1,   133,    72,
     127,    73,    -1,   101,    -1,    67,   135,    68,    -1,    67,
     135,    69,    68,    -1,   134,    -1,   136,   134,    -1,   135,
      69,   134,    -1,   135,    69,   136,   134,    -1,   137,    71,
      -1,   138,    -1,   137,   138,    -1,    74,   104,    75,    -1,
      76,     3,    -1,   140,    -1,   141,    -1,   144,    -1,   145,
      -1,   151,    -1,   152,    -1,     3,    70,   139,    -1,    54,
     104,    70,   139,    -1,    55,    70,   139,    -1,    67,    68,
      -1,    67,   142,    68,    -1,   143,    -1,   142,   143,    -1,
     105,    -1,   139,    -1,    66,    -1,   103,    66,    -1,    56,
      72,   103,    73,   139,    -1,    56,    72,   103,    73,   139,
      57,   139,    -1,    58,    72,   103,    73,   139,    -1,   101,
      -1,   103,    69,   101,    -1,   101,    -1,   103,    69,   101,
      -1,   101,    -1,   103,    69,   101,    -1,    66,    -1,   103,
      66,    -1,   106,    66,    -1,   106,   107,    66,    -1,    59,
      72,   147,    73,   139,    -1,    60,   139,    59,    72,   146,
      73,    66,    -1,    61,    72,   149,   149,    73,   139,    -1,
      61,    72,   149,   149,   148,    73,   139,    -1,    61,    72,
     150,   149,    73,   139,    -1,    61,    72,   150,   149,   148,
      73,   139,    -1,    62,     3,    66,    -1,    63,    66,    -1,
      64,    66,    -1,    65,    66,    -1,    65,   103,    66,    -1,
     154,    -1,   155,    -1,   154,   155,    -1,   156,    -1,   105,
      -1,   106,   123,   157,   141,    -1,   106,   123,   141,    -1,
     105,    -1,   157,   105,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   196,   196,   197,   198,   199,   203,   207,   211,   215,
     219,   223,   227,   231,   235,   239,   245,   249,   256,   260,
     266,   270,   277,   281,   285,   289,   293,   297,   301,   305,
     309,   313,   317,   325,   329,   336,   341,   345,   349,   353,
     357,   361,   365,   369,   373,   377,   381,   385,   389,   393,
     397,   401,   405,   409,   417,   421,   428,   432,   439,   442,
     445,   448,   451,   454,   457,   460,   463,   466,   469,   475,
     479,   486,   493,   497,   506,   510,   514,   518,   522,   526,
     530,   534,   541,   545,   552,   556,   563,   566,   569,   572,
     575,   581,   584,   587,   590,   593,   596,   599,   602,   605,
     608,   611,   614,   617,   621,   625,   631,   635,   639,   646,
     649,   655,   659,   666,   673,   677,   681,   685,   692,   696,
     703,   707,   711,   718,   722,   726,   730,   734,   741,   745,
     752,   756,   763,   766,   769,   775,   781,   785,   793,   797,
     801,   805,   809,   813,   817,   821,   825,   829,   833,   837,
     841,   848,   852,   856,   860,   867,   871,   879,   883,   890,
     894,   901,   905,   909,   916,   920,   927,   931,   938,   942,
     946,   953,   957,   961,   965,   969,   973,   977,   981,   985,
     989,   993,  1000,  1004,  1008,  1015,  1019,  1023,  1027,  1034,
    1041,  1045,  1052,  1056,  1063,  1067,  1071,  1075,  1079,  1083,
    1090,  1094,  1098,  1105,  1109,  1116,  1120,  1127,  1131,  1138,
    1142,  1149,  1153,  1157,  1165,  1169,  1176,  1180,  1187,  1191,
    1198,  1202,  1209,  1213,  1222,  1226,  1231,  1235,  1239,  1243,
    1250,  1254,  1258,  1262,  1266,  1272,  1281,  1285,  1292,  1296,
    1303,  1307,  1314,  1318
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT",
  "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "TYPE_NAME", "TYPEDEF", "EXTERN", "STATIC", "AUTO", "REGISTER", "INLINE",
  "RESTRICT", "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED",
  "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID", "BOOL", "COMPLEX",
  "IMAGINARY", "STRUCT", "UNION", "ENUM", "ELLIPSIS", "CASE", "DEFAULT",
  "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE",
  "BREAK", "RETURN", "';'", "'{'", "'}'", "','", "':'", "'='", "'('",
  "')'", "'['", "']'", "'.'", "'&'", "'!'", "'~'", "'-'", "'+'", "'*'",
  "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "'l'", "$accept",
  "primary_expression", "postfix_expression", "array_content",
  "argument_expression_list", "argument_expression", "unary_expression",
  "cast_expression", "all_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "function_specifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item", "expression_statement", "selection_statement",
  "do_while_expression", "while_expression", "for_expression",
  "for_expression_statement", "for_declaration", "iteration_statement",
  "jump_statement", "program", "translation_unit", "external_declaration",
  "function_definition", "declaration_list", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,    59,   123,   125,    44,
      58,    61,    40,    41,    91,    93,    46,    38,    33,   126,
      45,    43,    42,    47,    37,    60,    62,    94,   124,    63,
     108
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    92,    92,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    94,    94,    95,    95,
      96,    96,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    98,    98,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   101,   101,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   103,
     103,   104,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   106,   107,   107,   108,   108,   109,   109,   109,   109,
     109,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   111,   111,   111,   112,
     112,   113,   113,   114,   115,   115,   115,   115,   116,   116,
     117,   117,   117,   118,   118,   118,   118,   118,   119,   119,
     120,   120,   121,   121,   121,   122,   123,   123,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   125,   125,   125,   125,   126,   126,   127,   127,   128,
     128,   129,   129,   129,   130,   130,   131,   131,   132,   132,
     132,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   134,   134,   134,   135,   135,   135,   135,   136,
     137,   137,   138,   138,   139,   139,   139,   139,   139,   139,
     140,   140,   140,   141,   141,   142,   142,   143,   143,   144,
     144,   145,   145,   145,   146,   146,   147,   147,   148,   148,
     149,   149,   150,   150,   151,   151,   151,   151,   151,   151,
     152,   152,   152,   152,   152,   153,   154,   154,   155,   155,
     156,   156,   157,   157
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     6,     7,     1,     3,     1,     3,
       1,     3,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     1,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     3,     1,     2,     1,     2,     1,     2,
       1,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     4,     2,     1,
       1,     1,     2,     3,     2,     1,     2,     1,     1,     3,
       1,     2,     3,     4,     5,     5,     6,     2,     1,     3,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     3,
       5,     4,     4,     6,     6,     5,     4,     3,     4,     4,
       3,     1,     2,     2,     3,     1,     2,     1,     3,     1,
       3,     2,     2,     1,     1,     3,     1,     2,     1,     1,
       2,     3,     2,     3,     3,     4,     3,     4,     2,     3,
       3,     4,     1,     3,     4,     1,     2,     3,     4,     2,
       1,     2,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     2,     3,     1,     2,     1,     1,     1,
       2,     5,     7,     5,     1,     3,     1,     3,     1,     3,
       1,     2,     2,     3,     5,     7,     6,     7,     6,     7,
       3,     2,     2,     2,     3,     1,     1,     2,     1,     1,
       4,     3,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   105,    86,    87,    88,    89,    90,   135,   133,    92,
      93,    94,    95,    98,    99,    96,    97,   132,   134,    91,
     100,   101,   102,   109,   110,     0,   239,     0,    74,    76,
     103,     0,   104,    78,    80,     0,   235,   236,   238,   127,
       0,   138,    72,     0,   151,     0,    82,    84,   137,     0,
      75,    77,   108,     0,    79,    81,     1,   237,     0,   130,
       0,   128,     0,   155,   153,   152,    73,     0,     0,     0,
     242,     0,   241,     0,     0,     0,   136,     0,   115,     0,
     111,     0,   117,     0,     0,   123,     0,   139,   156,   154,
      83,    84,     2,     3,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   209,
     203,     0,     0,     0,     0,     0,     0,     0,     6,    22,
      33,    53,    54,    56,    69,     0,   207,   208,   194,   195,
       0,   205,   196,   197,   198,   199,     2,     0,   182,    85,
     243,   240,   164,   150,   163,     0,   157,   159,     0,     0,
     147,     0,     0,     0,     0,   114,   107,   112,     0,     0,
     118,   120,   116,   124,     0,    33,    71,   131,   125,   129,
       0,     0,    31,     0,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,   231,   232,   233,     0,     0,   166,
       0,    25,    30,    29,    28,    27,    26,     0,    12,    13,
       0,     0,     0,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   210,     0,   204,   206,     0,     0,
     185,     0,     0,     0,   190,     0,     0,   161,   168,   162,
     169,   148,     0,     0,   149,     0,   146,   142,     0,   141,
       0,     0,   106,   121,   113,     0,     0,   126,   200,     0,
       0,     0,   202,     0,     0,    69,     0,     0,     0,   220,
       0,     0,     0,     0,   230,   234,     5,     0,   168,   167,
       0,    11,     8,     0,    18,    33,    20,     0,    16,     0,
      10,    57,    46,    47,    44,    45,    40,    41,    36,    35,
      39,    49,    48,    50,    51,    52,    42,    43,    38,    37,
       0,    70,     0,   193,   183,     0,   186,   189,   191,   178,
       0,     0,   172,     0,     0,   170,     0,     0,   158,   160,
     165,     0,     0,   145,   140,   119,   122,    32,     0,   201,
       0,     0,     0,     0,     0,   221,   222,     0,     0,     0,
       0,    34,     0,     9,     0,     7,     0,     0,   192,   184,
     187,     0,   179,   171,   176,   173,   180,     0,   174,     0,
       0,   143,   144,   211,   213,    70,   224,    69,     0,     0,
     223,     0,    69,     0,     0,     0,     0,     0,    19,    21,
      17,    55,   188,   181,   177,   175,     0,     0,     0,   226,
       0,     0,   228,     0,    14,     0,   212,    70,   225,    70,
     227,   229,    15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   118,   119,   297,   293,   294,   120,   121,   122,   123,
     124,   214,   125,   167,    26,   144,    45,    46,    28,    29,
      30,    31,    79,    80,    81,   159,   160,    32,    60,    61,
      33,    34,    91,    48,    49,    65,   330,   146,   147,   148,
     190,   331,   250,   240,   241,   242,   243,   244,   127,   128,
     129,   130,   131,   132,   133,   389,   277,   394,   282,   283,
     134,   135,    35,    36,    37,    38,    73
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -333
static const yytype_int16 yypact[] =
{
    1659,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,    47,  -333,     8,  1659,  1659,
    -333,    63,  -333,  1659,  1659,    31,  1659,  -333,  -333,   -29,
      64,  -333,  -333,    86,    98,    16,  -333,  1481,    54,    20,
    -333,  -333,    73,  1684,  -333,  -333,  -333,  -333,    64,    76,
     -17,  -333,    61,  -333,  -333,    98,  -333,    86,   355,   911,
    -333,     8,  -333,  1593,  1315,   714,    54,  1684,  1684,  1518,
    -333,     9,  1684,   131,  1130,  -333,    38,  -333,  -333,  -333,
    -333,    89,    99,  -333,  -333,  1195,  1210,  1210,  1130,   106,
      92,   139,   145,   675,   166,   255,   194,   200,   935,  -333,
    -333,   570,  1130,  1130,  1130,  1130,  1130,  1130,  -333,    36,
     758,  -333,   445,  -333,  -333,    80,  -333,  -333,  -333,  -333,
     435,  -333,  -333,  -333,  -333,  -333,  -333,   831,  -333,  -333,
    -333,  -333,  -333,  -333,    55,   167,   201,  -333,   -20,    11,
    -333,   631,   196,   766,  1552,  -333,  -333,  -333,  1130,   118,
    -333,   205,  -333,  -333,    45,  -333,  -333,  -333,  -333,  -333,
     675,   570,  -333,   570,  -333,  -333,   207,   675,  1130,  1130,
    1130,   219,   515,   220,  -333,  -333,  -333,   126,    52,    -9,
     214,  -333,  -333,  -333,  -333,  -333,  -333,   285,  -333,  -333,
     946,  1130,   291,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  1130,  1130,  1130,  1130,  1130,  1130,
    1130,  1130,  1130,  1130,  1130,  1130,  1130,  1130,  1130,  1130,
    1130,  1130,  1130,  1130,  -333,  1130,  -333,  -333,  1130,   295,
    -333,   147,   911,    91,  -333,   625,   957,  -333,    33,  -333,
      67,  -333,  1633,   296,  -333,   855,  -333,  -333,  1130,  -333,
     968,   225,  -333,  -333,  -333,     9,  1130,  -333,  -333,   228,
     231,   675,  -333,   102,   110,   236,   241,   242,   244,  -333,
     128,    22,   991,   991,  -333,  -333,  -333,  1380,   116,  -333,
    1050,  -333,  -333,   112,  -333,   758,  -333,   249,   257,   259,
    -333,  -333,   269,   269,   251,   251,   237,   237,  1240,  1228,
     680,   125,   125,   252,   252,   252,   251,   251,  1319,  1216,
       7,  -333,   254,  -333,  -333,   799,  -333,  -333,  -333,  -333,
     264,   270,  -333,  1071,   267,    67,  1435,  1082,  -333,  -333,
    -333,   273,   279,  -333,  -333,  -333,  -333,   263,   263,  -333,
     675,   675,  1130,   675,  1130,  -333,  -333,   132,  1093,  1104,
     831,  -333,  1130,  -333,  1130,  -333,  1130,  1130,  -333,  -333,
    -333,   911,  -333,  -333,  -333,  -333,  -333,   271,  -333,  1115,
     280,  -333,  -333,   288,  -333,   289,  -333,   293,   299,   298,
    -333,   675,   301,   300,   305,   675,   306,   174,  -333,  -333,
     303,  -333,  -333,  -333,  -333,  -333,   675,  1130,   314,  -333,
    1130,   675,  -333,   675,  -333,   815,  -333,   308,  -333,   335,
    -333,  -333,  -333
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -333,  -333,  -333,  -333,  -333,  -332,     3,   -97,  1153,   -56,
     -69,   117,    94,   -88,   -34,   123,   143,   358,  -333,   202,
    -333,  -333,   349,   -57,   -49,  -333,   163,  -333,   371,   -78,
     -18,  -333,    -6,   -42,   -41,   -66,   -72,  -333,   178,  -333,
      41,  -117,  -179,   -68,    71,  -320,  -333,   199,   -99,  -333,
     -33,  -333,   315,  -333,  -333,  -333,  -333,    87,   -38,  -333,
    -333,  -333,  -333,  -333,   411,  -333,  -333
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -220
static const yytype_int16 yytable[] =
{
     138,   139,   145,    64,   181,   371,   152,    76,   169,   153,
     176,    41,    41,    70,    72,   191,   192,   193,   194,   195,
     196,    47,   157,    41,    89,    41,    63,   249,   166,   155,
     398,    56,   399,   162,   126,    82,    41,    62,    58,   140,
     141,    59,   166,   197,   198,   199,     8,    88,    59,   253,
      39,    85,    86,   254,   196,    17,    18,    63,    41,    82,
      82,    82,   189,   287,    82,   246,    52,    59,   138,   335,
     263,   268,   289,    44,    42,   161,   235,   367,   272,   158,
      43,    43,    66,   255,   261,    67,   169,   165,   356,    41,
      44,    44,    43,    82,    43,   371,   126,   157,   172,   174,
     175,   165,   166,   248,    44,   245,   168,   246,   200,   335,
     201,   275,   202,   267,    40,   165,   165,   165,   165,   165,
     165,   235,   189,    27,   189,   286,    74,   245,    75,   246,
      53,    63,   298,     8,    87,    88,    82,    44,   247,   336,
      77,   337,    17,    18,   296,   301,   234,    84,   288,   235,
     322,    50,    51,    82,   165,    82,    54,    55,    43,    27,
      69,   165,   327,   196,   178,   238,   321,   239,    44,   170,
      71,   235,   349,   138,   326,   350,   177,   334,   346,   235,
      44,   362,   166,   351,   264,   363,   341,   265,   287,   342,
     246,    71,   285,   361,   355,   235,    71,   235,   390,   163,
     164,    67,   187,   295,   248,   188,    76,   226,   227,   228,
     166,   179,   269,   232,   270,   324,   325,   180,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   196,    88,   182,    62,
     251,   165,   414,   415,   358,   359,   288,   215,   216,   217,
     218,   383,   384,    71,   386,    78,   138,   370,   183,   161,
     184,   215,   216,   165,   377,   188,   185,   188,   380,   165,
     252,   257,   273,   274,   276,   266,   280,   271,   278,    78,
      78,    78,   196,   385,    78,   387,   284,   290,   291,   392,
     392,   138,   409,   165,   300,   299,   412,   400,   323,   340,
     344,   347,   138,   402,   348,   281,   296,   416,   296,  -216,
     352,   401,   420,    78,   421,   353,   354,   224,   225,   226,
     227,   228,   229,   230,   365,   232,   -69,   320,   366,   368,
     360,   224,   225,   226,   227,   228,   165,   372,   417,   232,
     232,   419,   375,   373,   403,   406,   138,   370,   381,   224,
     225,   226,   227,   228,   382,   405,    78,   232,    92,    93,
      94,    95,  -217,    96,    97,   295,  -214,   295,   407,   410,
     165,   408,   -70,    78,  -218,    78,   280,   280,   411,   413,
     418,  -215,   165,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,  -219,    98,
      99,   100,   364,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    68,   110,   357,    90,   154,   111,   345,    83,
     339,   397,   112,   113,   114,   115,   116,   117,    92,    93,
      94,    95,   328,    96,    97,   237,   396,    57,   388,     0,
       0,     0,   393,   393,     0,   215,   216,   217,   218,   219,
     220,   221,   222,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     0,    98,
      99,   100,     0,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    68,   236,     0,     0,     0,   111,     0,     0,
       0,     0,   112,   113,   114,   115,   116,   117,   136,    93,
      94,    95,   223,    96,    97,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     0,     0,
       0,     0,     0,   136,    93,    94,    95,     0,    96,    97,
       0,   279,     0,     0,     0,     0,     0,   111,     0,     0,
       0,     0,   112,   113,   114,   115,   116,   117,     1,     0,
       0,     0,     0,     0,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,    41,     0,
       0,     0,     0,     0,   136,    93,    94,    95,     0,    96,
      97,     0,   111,     0,     0,     0,     0,   112,   113,   114,
     115,   116,   117,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    92,    93,
      94,    95,     0,    96,    97,     0,     0,     0,     0,     0,
     215,   216,   217,   218,   219,   220,     0,   245,   329,   246,
       0,     0,     0,   111,     0,     0,   256,    44,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   136,    93,    94,
      95,     0,    96,    97,     0,     0,     0,     0,     0,    98,
      99,   100,     0,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    68,     0,     0,   149,     0,   111,     0,     8,
       0,     0,   112,   113,   114,   115,   116,   117,    17,    18,
     224,   225,   226,   227,   228,   229,   230,     0,   232,   136,
      93,    94,    95,     0,    96,    97,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   111,     0,     0,   150,
       0,   112,   113,   114,   115,   116,   151,   258,     0,     0,
       0,     8,   136,    93,    94,    95,     0,    96,    97,     0,
      17,    18,     0,     0,     0,     0,     0,     0,   136,    93,
      94,    95,     0,    96,    97,     0,     0,     0,     0,   213,
       0,     0,     0,     0,   136,    93,    94,    95,   111,    96,
      97,   259,     0,   112,   113,   114,   115,   116,   260,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   136,    93,
      94,    95,     0,    96,    97,     0,   137,   369,     0,     0,
       0,   111,     0,   238,     0,   239,   112,   113,   114,   115,
     116,   117,   137,   422,     0,     0,     0,   111,     0,   238,
       8,   239,   112,   113,   114,   115,   116,   117,   137,    17,
      18,     0,     0,   111,     0,   238,     0,   239,   112,   113,
     114,   115,   116,   117,   136,    93,    94,    95,     0,    96,
      97,     0,     0,     0,     0,     0,     0,   111,     0,     0,
       0,     0,   112,   113,   114,   115,   116,   117,   136,    93,
      94,    95,     0,    96,    97,     0,     0,     0,     0,   136,
      93,    94,    95,     0,    96,    97,     0,     0,     0,     0,
     136,    93,    94,    95,     0,    96,    97,     0,     0,     0,
       0,   136,    93,    94,    95,     0,    96,    97,   137,     0,
       0,     0,     0,   111,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,   136,    93,    94,    95,     0,    96,
      97,   186,     0,     0,     0,     0,     0,   111,     0,     0,
       0,     0,   112,   113,   114,   115,   116,   117,   111,   292,
       0,     0,     0,   112,   113,   114,   115,   116,   117,   111,
       0,     0,   332,     0,   112,   113,   114,   115,   116,   333,
     111,     0,     0,   343,     0,   112,   113,   114,   115,   116,
     117,     0,     0,   136,    93,    94,    95,   279,    96,    97,
       0,     0,     0,   111,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,   136,    93,    94,    95,     0,    96,
      97,     0,     0,     0,     0,   136,    93,    94,    95,     0,
      96,    97,     0,     0,     0,     0,   136,    93,    94,    95,
       0,    96,    97,     0,     0,     0,     0,   136,    93,    94,
      95,     0,    96,    97,     0,     0,     0,   360,   136,    93,
      94,    95,   111,    96,    97,     0,     0,   112,   113,   114,
     115,   116,   117,   136,    93,    94,    95,     0,    96,    97,
       0,     0,     0,   111,     0,     0,   374,     0,   112,   113,
     114,   115,   116,   117,   111,     0,     0,   378,     0,   112,
     113,   114,   115,   116,   379,   111,   391,     0,     0,     0,
     112,   113,   114,   115,   116,   117,   111,   395,     0,     0,
       0,   112,   113,   114,   115,   116,   117,   111,     0,     0,
     404,     0,   112,   113,   114,   115,   116,   117,   136,    93,
      94,    95,   111,    96,    97,     0,     0,   112,   113,   114,
     115,   116,   117,   136,    93,    94,    95,     0,    96,    97,
       0,     0,     0,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,     0,     0,     0,     0,   215,   216,
     217,   218,   219,   220,   221,     0,     0,     0,     0,     0,
     215,   216,   217,   218,   219,   220,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   171,     0,     0,
       0,     0,   112,   113,   114,   115,   116,   117,     0,     0,
       0,     0,   173,     0,     0,     0,     0,   112,   113,   114,
     115,   116,   117,   223,     0,     0,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   223,     0,     0,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   223,   142,     0,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   215,
     216,   217,   218,   219,   220,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,     0,     0,   143,     0,
       0,     0,     0,     0,     0,     0,   223,     0,     0,   224,
     225,   226,   227,   228,   229,   230,     0,   232,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,   329,   246,     0,     0,     0,     0,     0,
       0,     0,    44,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   376,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     0,    68,     0,
       0,     0,    69,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,     0,   156,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     262,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      68,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,   338,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     1,     0,     0,     0,     0,     0,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25
};

static const yytype_int16 yycheck[] =
{
      69,    69,    74,    44,   103,   325,    75,    49,    86,    75,
      98,     3,     3,    47,    47,   112,   113,   114,   115,   116,
     117,    27,    79,     3,    65,     3,    44,   144,    84,    78,
     362,     0,   364,    82,    68,    53,     3,    43,    67,    73,
      73,     3,    98,     7,     8,     9,    35,    65,     3,    69,
       3,    68,    69,    73,   151,    44,    45,    75,     3,    77,
      78,    79,   111,    72,    82,    74,     3,     3,   137,   248,
     158,   170,   189,    82,    66,    81,    69,    70,   177,    70,
      72,    72,    66,   149,   153,    69,   164,    84,    66,     3,
      82,    82,    72,   111,    72,   415,   130,   154,    95,    96,
      97,    98,   158,   144,    82,    72,    68,    74,    72,   288,
      74,   180,    76,    68,    67,   112,   113,   114,   115,   116,
     117,    69,   171,     0,   173,    73,    72,    72,    74,    74,
      67,   149,   201,    35,    73,   153,   154,    82,   144,    72,
      67,    74,    44,    45,   200,   214,    66,    71,   189,    69,
     238,    28,    29,   171,   151,   173,    33,    34,    72,    36,
      71,   158,    71,   260,    72,    74,   235,    76,    82,    70,
      47,    69,   271,   242,   242,    73,    70,   246,   266,    69,
      82,    69,   238,    73,    66,    73,   255,    69,    72,   258,
      74,    68,    66,   290,    66,    69,    73,    69,    66,    68,
      69,    69,   108,   200,   245,   111,   248,    82,    83,    84,
     266,    72,   171,    88,   173,    68,    69,    72,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   333,   255,    72,   245,
      73,   238,    68,    69,   282,   283,   287,    10,    11,    12,
      13,   350,   351,   130,   353,    53,   325,   325,     3,   265,
      66,    10,    11,   260,   336,   171,    66,   173,   337,   266,
      69,    75,   178,   179,   180,    70,   182,    70,    59,    77,
      78,    79,   379,   352,    82,   354,    66,    73,     3,   358,
     359,   360,   391,   290,     3,   201,   395,   366,     3,     3,
      75,    73,   371,   371,    73,   182,   362,   406,   364,    73,
      69,   367,   411,   111,   413,    73,    72,    80,    81,    82,
      83,    84,    85,    86,    75,    88,    69,   233,    69,    75,
      67,    80,    81,    82,    83,    84,   333,    73,   407,    88,
      88,   410,    75,    73,    73,    57,   415,   415,    75,    80,
      81,    82,    83,    84,    75,    75,   154,    88,     3,     4,
       5,     6,    73,     8,     9,   362,    73,   364,    69,    69,
     367,    73,    69,   171,    73,   173,   282,   283,    73,    73,
      66,    73,   379,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    73,    54,
      55,    56,   295,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,   281,    67,    77,    72,   265,    58,
     252,   360,    77,    78,    79,    80,    81,    82,     3,     4,
       5,     6,   243,     8,     9,   130,   359,    36,   354,    -1,
      -1,    -1,   358,   359,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    54,
      55,    56,    -1,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,     3,     4,
       5,     6,    77,     8,     9,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    72,    -1,    -1,    -1,    -1,    77,    78,    79,
      80,    81,    82,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      10,    11,    12,    13,    14,    15,    -1,    72,    73,    74,
      -1,    -1,    -1,    72,    -1,    -1,    75,    82,    77,    78,
      79,    80,    81,    82,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    -1,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    31,    -1,    72,    -1,    35,
      -1,    -1,    77,    78,    79,    80,    81,    82,    44,    45,
      80,    81,    82,    83,    84,    85,    86,    -1,    88,     3,
       4,     5,     6,    -1,     8,     9,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    72,    -1,    -1,    75,
      -1,    77,    78,    79,    80,    81,    82,    31,    -1,    -1,
      -1,    35,     3,     4,     5,     6,    -1,     8,     9,    -1,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    72,     8,
       9,    75,    -1,    77,    78,    79,    80,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    67,    68,    -1,    -1,
      -1,    72,    -1,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    67,    68,    -1,    -1,    -1,    72,    -1,    74,
      35,    76,    77,    78,    79,    80,    81,    82,    67,    44,
      45,    -1,    -1,    72,    -1,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    67,    -1,
      -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    77,    78,
      79,    80,    81,    82,     3,     4,     5,     6,    -1,     8,
       9,    66,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,    72,    73,
      -1,    -1,    -1,    77,    78,    79,    80,    81,    82,    72,
      -1,    -1,    75,    -1,    77,    78,    79,    80,    81,    82,
      72,    -1,    -1,    75,    -1,    77,    78,    79,    80,    81,
      82,    -1,    -1,     3,     4,     5,     6,    66,     8,     9,
      -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    77,    78,
      79,    80,    81,    82,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    67,     3,     4,
       5,     6,    72,     8,     9,    -1,    -1,    77,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    72,    -1,    -1,    75,    -1,    77,    78,
      79,    80,    81,    82,    72,    -1,    -1,    75,    -1,    77,
      78,    79,    80,    81,    82,    72,    73,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    82,    72,    73,    -1,    -1,
      -1,    77,    78,    79,    80,    81,    82,    72,    -1,    -1,
      75,    -1,    77,    78,    79,    80,    81,    82,     3,     4,
       5,     6,    72,     8,     9,    -1,    -1,    77,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,    -1,    77,    78,    79,
      80,    81,    82,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    77,     3,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,    -1,    -1,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    80,
      81,    82,    83,    84,    85,    86,    -1,    88,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    67,    -1,
      -1,    -1,    71,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    68,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,   105,   106,   109,   110,
     111,   112,   118,   121,   122,   153,   154,   155,   156,     3,
      67,     3,    66,    72,    82,   107,   108,   123,   124,   125,
     106,   106,     3,    67,   106,   106,     0,   155,    67,     3,
     119,   120,   123,   121,   125,   126,    66,    69,    67,    71,
     105,   106,   141,   157,    72,    74,   124,    67,   110,   113,
     114,   115,   121,   119,    71,    68,    69,    73,   121,   125,
     108,   123,     3,     4,     5,     6,     8,     9,    54,    55,
      56,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      68,    72,    77,    78,    79,    80,    81,    82,    92,    93,
      97,    98,    99,   100,   101,   103,   105,   139,   140,   141,
     142,   143,   144,   145,   151,   152,     3,    67,   101,   134,
     105,   141,     3,    73,   106,   127,   128,   129,   130,    31,
      75,    82,   101,   126,   113,   115,    68,   114,    70,   116,
     117,   123,   115,    68,    69,    97,   100,   104,    68,   120,
      70,    72,    97,    72,    97,    97,   104,    70,    72,    72,
      72,   139,    72,     3,    66,    66,    66,   103,   103,   115,
     131,    98,    98,    98,    98,    98,    98,     7,     8,     9,
      72,    74,    76,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    71,   102,    10,    11,    12,    13,    14,
      15,    16,    17,    77,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    66,    69,    68,   143,    74,    76,
     134,   135,   136,   137,   138,    72,    74,   123,   125,   132,
     133,    73,    69,    69,    73,   126,    75,    75,    31,    75,
      82,   101,    68,   104,    66,    69,    70,    68,   139,   131,
     131,    70,   139,   103,   103,   101,   103,   147,    59,    66,
     103,   106,   149,   150,    66,    66,    73,    72,   125,   132,
      73,     3,    73,    95,    96,    97,   100,    94,   101,   103,
       3,   101,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
     103,   101,   104,     3,    68,    69,   134,    71,   138,    73,
     127,   132,    75,    82,   101,   133,    72,    74,    53,   129,
       3,   101,   101,    75,    75,   117,   104,    73,    73,   139,
      73,    73,    69,    73,    72,    66,    66,   107,   149,   149,
      67,    98,    69,    73,   102,    75,    69,    70,    75,    68,
     134,   136,    73,    73,    75,    75,    73,   127,    75,    82,
     101,    75,    75,   139,   139,   101,   139,   101,   103,   146,
      66,    73,   101,   103,   148,    73,   148,   135,    96,    96,
     101,   100,   134,    73,    75,    75,    57,    69,    73,   139,
      69,    73,   139,    73,    68,    69,   139,   101,    66,   101,
     139,   139,    68
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
        case 2:

/* Line 1464 of yacc.c  */
#line 196 "ansic_kako.y"
    {(yyval.val) = (yyvsp[(1) - (1)].val);}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 197 "ansic_kako.y"
    {(yyval.val) = (yyvsp[(1) - (1)].val);}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 198 "ansic_kako.y"
    {(yyval.val) = (yyvsp[(1) - (1)].val);}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 199 "ansic_kako.y"
    {(yyval.val) = new_AST("primary_expression","", (yyvsp[(1) - (3)].val)->line); multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 203 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("postfix_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 207 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("array_access", "", (yyvsp[(1) - (4)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																		}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 211 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("call_function", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 215 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("call_function", "", (yyvsp[(1) - (4)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																		}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 219 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_access", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 223 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("p_struct_access", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 227 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("inc_after_expr", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 231 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("dec_after_expr", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 235 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("postfix_expression", "", (yyvsp[(1) - (6)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 6, (yyvsp[(1) - (6)].val), (yyvsp[(2) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
																		}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 239 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("postfix_expression", "", (yyvsp[(1) - (7)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 7, (yyvsp[(1) - (7)].val), (yyvsp[(2) - (7)].val), (yyvsp[(3) - (7)].val), (yyvsp[(4) - (7)].val), (yyvsp[(5) - (7)].val), (yyvsp[(6) - (7)].val), (yyvsp[(7) - (7)].val));
																		}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 245 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("array_content", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 249 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("array_content", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 256 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("argument_expression_list", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 260 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("argument_expression_list", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 266 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_argument_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 270 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("argument_expression", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 277 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("unary_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 281 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("inc_expr","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 285 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("dec_expr","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 289 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("address_ref","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 293 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("direct_ref","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 297 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("plus_op","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 301 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("minus_op","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 305 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("xor_op","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 309 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("not_op","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 313 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("sizeof_expression","",(yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 317 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("sizeof_expression","",(yyvsp[(1) - (4)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																		}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 325 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_cast_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 329 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("cast_expression", "", (yyvsp[(1) - (4)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																		}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 336 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("log_or_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 341 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("log_and_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 345 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("or_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 349 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("xor_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 353 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("and_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 357 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("eq_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 361 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("ne_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 365 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("lethan_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 369 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("gethan_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 373 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("leeq_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 377 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("geeq_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 381 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("left_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 385 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("right_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 389 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("plus_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 393 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("minus_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 397 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("mul_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 401 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("div_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 405 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("mod_expr", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 409 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_all_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 417 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_conditional_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 421 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("conditional_expression", "", (yyvsp[(1) - (5)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
																		}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 428 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_assignment_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 432 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("assignment_expression", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 439 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 442 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 445 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 448 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 451 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 454 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 457 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 460 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 463 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 466 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 469 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 475 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 479 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("expression", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 486 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("constant_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 493 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("declaration", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 497 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("declaration_with_init", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																			//TYPEDEFテーブルリストに登録させる
																			getTYPEDEF_TABLE_DATA(typedef_table_list, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
																		}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 506 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("storage_class_specifier", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 510 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("declaration_specifiers", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 514 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("type_specifier", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 518 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("declaration_specifiers", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 522 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("type_qualifier", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 526 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("declaration_specifiers", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 530 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("function_specifier", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 534 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("declaration_specifiers", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 541 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_init_declarator_list", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 545 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("init_declarator_list", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 552 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_init_declarator", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 556 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("init_declarator", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 563 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 566 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 569 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 572 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 575 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 581 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 584 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 587 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 590 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 593 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 596 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 599 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 602 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 605 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 608 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 611 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 614 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 617 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("type_specifier", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 621 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("type_specifier", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 625 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 631 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_or_union_specifier", "", (yyvsp[(1) - (5)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val) ,(yyvsp[(5) - (5)].val));
																		}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 635 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_or_union_specifier", "", (yyvsp[(1) - (4)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val) ,(yyvsp[(4) - (4)].val));
																		}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 639 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_or_union_specifier", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 646 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 649 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 655 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_struct_declaration_list", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 659 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declaration_list", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 666 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declaration", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 673 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("specifier_qualifier_list", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 677 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("type_specifier", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 681 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("specifier_qualifier_list", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 685 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("type_qualifier", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 692 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_struct_declarator_list", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 696 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator_list", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 703 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 707 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator_list", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 711 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator_list", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 718 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator_list", "", (yyvsp[(1) - (4)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																		}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 722 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator_list", "", (yyvsp[(1) - (5)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
																		}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 726 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator_list", "", (yyvsp[(1) - (5)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
																		}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 730 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator_list", "", (yyvsp[(1) - (6)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 6, (yyvsp[(1) - (6)].val), (yyvsp[(2) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
																		}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 734 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("struct_declarator_list", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 741 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_enumerator_list", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 745 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("enumerator_list", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 752 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("enumerator", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 756 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("enumerator_assign", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 763 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 766 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 769 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 775 "ansic_kako.y"
    {
																			(yyval.val) = (yyvsp[(1) - (1)].val);
																		}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 781 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("declarator", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 785 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("declarator", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 793 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 797 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 801 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_array", "", (yyvsp[(1) - (5)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
																					}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 805 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_array", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 809 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_array", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 813 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_array", "", (yyvsp[(1) - (6)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 6, (yyvsp[(1) - (6)].val), (yyvsp[(2) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
																					}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 817 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_array", "", (yyvsp[(1) - (6)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 6, (yyvsp[(1) - (6)].val), (yyvsp[(2) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
																					}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 821 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_array", "", (yyvsp[(1) - (5)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
																					}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 825 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_array", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 829 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_array", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 833 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_function", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 837 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_function", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 841 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_declarator_function", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 848 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("pointer", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 852 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("pointer", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 856 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("pointer", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 860 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("pointer", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 867 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("type_qualifier", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 871 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("type_qualifier_list", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 879 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("parameter_type_list", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 883 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("parameter_type_list", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 890 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("t_parameter_list", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 894 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("parameter_list", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 901 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("parameter_declaration_with_declarator", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 905 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("parameter_declaration", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 909 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("parameter_declaration", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 916 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("t_identifier_list", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 920 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("identifier_list", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 927 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("type_name", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 931 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("type_name", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 938 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("abstract_declarator", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 942 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("abstract_declarator", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 946 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("abstract_declarator", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 953 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 957 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_array", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 961 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_array", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 965 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_array", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 969 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_array", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 973 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_array", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 977 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_array", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 981 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 985 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_array", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 989 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_function", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 993 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("direct_abstract_declarator_function", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 1000 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("initializer", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 1004 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("initializer", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 1008 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("initializer", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 1015 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("t_initializer_list", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 1019 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("t_initializer_list", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 1023 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("identifier_list", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 1027 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("identifier_list", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 1034 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("designation", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 1041 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("t_designator_list", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 1045 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("designator_list", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 1052 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("designator", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 1056 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("designator", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 1063 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("statement", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1067 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("statement", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1071 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("statement", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1075 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("statement", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1079 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("statement", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1083 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("statement", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1090 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("goto_labeled_statement", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1094 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("case_labeled_statement", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1098 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("default_labeled_statement", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1105 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("compound_statement_a", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1109 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("compound_statement_b", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1116 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("t_block_item_list", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1120 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("block_item_list", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1127 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("block_item", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1131 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("block_item", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1138 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("expression_statement", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1142 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("expression_statement", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1149 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("if_statement", "", (yyvsp[(1) - (5)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
																					}
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1153 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("ifelse_statement", "", (yyvsp[(1) - (7)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 7, (yyvsp[(1) - (7)].val), (yyvsp[(2) - (7)].val), (yyvsp[(3) - (7)].val), (yyvsp[(4) - (7)].val), (yyvsp[(5) - (7)].val), (yyvsp[(6) - (7)].val), (yyvsp[(7) - (7)].val));
																					}
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1157 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("switch_statement", "", (yyvsp[(1) - (5)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
																					}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1165 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_do_while_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1169 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("do_while_expression", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1176 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_while_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1180 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("while_expression", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1187 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("t_for_expression", "", (yyvsp[(1) - (1)].val)->line);
																			push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																		}
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1191 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("for_expression", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																		}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1198 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("for_expression_statement", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1202 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("for_expression_statement", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1209 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("for_declaration", "", (yyvsp[(1) - (2)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																		}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1213 "ansic_kako.y"
    {
																			(yyval.val) = new_AST("for_declaration_with_init", "", (yyvsp[(1) - (3)].val)->line);
																			multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																			//TYPEDEFテーブルリストに登録させる
																			getTYPEDEF_TABLE_DATA(typedef_table_list, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
																		}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1222 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("while_statement", "", (yyvsp[(1) - (5)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 5, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
																					}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1226 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("dowhile_statement", "", (yyvsp[(1) - (7)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 7, (yyvsp[(1) - (7)].val), (yyvsp[(2) - (7)].val), (yyvsp[(3) - (7)].val), (yyvsp[(4) - (7)].val), (yyvsp[(5) - (7)].val), (yyvsp[(6) - (7)].val), (yyvsp[(7) - (7)].val));
																					}
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 1231 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("for_statement_type_a", "", (yyvsp[(1) - (6)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 6, (yyvsp[(1) - (6)].val), (yyvsp[(2) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
																					}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1235 "ansic_kako.y"
    {
																									(yyval.val) = new_AST("for_statement_type_b", "", (yyvsp[(1) - (7)].val)->line);
																									multi_push_back_childrenAST((yyval.val), 7, (yyvsp[(1) - (7)].val), (yyvsp[(2) - (7)].val), (yyvsp[(3) - (7)].val), (yyvsp[(4) - (7)].val), (yyvsp[(5) - (7)].val), (yyvsp[(6) - (7)].val), (yyvsp[(7) - (7)].val));
																								}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1239 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("for_statement_type_c", "", (yyvsp[(1) - (6)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 6, (yyvsp[(1) - (6)].val), (yyvsp[(2) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
																					}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 1243 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("for_statement_type_d", "", (yyvsp[(1) - (7)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 7, (yyvsp[(1) - (7)].val), (yyvsp[(2) - (7)].val), (yyvsp[(3) - (7)].val), (yyvsp[(4) - (7)].val), (yyvsp[(5) - (7)].val), (yyvsp[(6) - (7)].val), (yyvsp[(7) - (7)].val));
																					}
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 1250 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("goto_statement", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val),(yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 1254 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("continue_statement", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 1258 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("break_statement", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 1262 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("return_statement", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 1266 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("return_expr_statement", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val),(yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1272 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("program", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																						programAST = (yyval.val);


																					}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 1281 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("t_translation_unit", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1285 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("translation_unit", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 1292 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("external_declaration", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 1296 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("external_declaration", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 1303 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("function_definition_type_a", "", (yyvsp[(1) - (4)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 4, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
																					}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 1307 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("function_definition_type_b", "", (yyvsp[(1) - (3)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 3, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
																					}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 1314 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("t_declaration_list", "", (yyvsp[(1) - (1)].val)->line);
																						push_back_childrenAST((yyval.val), (yyvsp[(1) - (1)].val));
																					}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 1318 "ansic_kako.y"
    {
																						(yyval.val) = new_AST("declaration_list", "", (yyvsp[(1) - (2)].val)->line);
																						multi_push_back_childrenAST((yyval.val), 2, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
																					}
    break;



/* Line 1464 of yacc.c  */
#line 4569 "y.tab.c"
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
#line 1325 "ansic_kako.y"

#include <stdio.h>

extern char yytext[];
extern int column;
extern int line;

//構文解析本体のエラーフラグ
int error_flag = 0;
void yyerror(char const *s)
{
	fflush(stdout);
	printf("#%s#:%d:Syntax Error!!\n", getFileName(), line);

	//構文解析本体のエラーフラグを立てる
	error_flag = 1;
}
/*
int main(int argc, char *argv[]){
	extern FILE *yyin;
	FILE *output;
	//フラグデータベースの設定
	int flag_database = getFlagDatabase(argc, argv);

	int i;
	//フラグを飛ばす
	for(i = 1;i < argc && strlen(argv[i]) >= 2 && ( argv[i][0] == '-' && argv[i][1] == '-' ); i++);
	if(i == argc){
		fprintf(stderr, "開くファイル名が存在しません！\n");
		exit(1);
	}

	char preprocess_file_name[FILE_PATH];
	char output_file_name[FILE_PATH];
	if(argc >= ENABLE_ARGUMENT){
		//ファイル名を設定する（これは他のエラー処理などでファイル名を表示させるようにするために必要）
		setFileName(argv[i]);

		//前処理に成功した場合
		if(preProcesser(argv[i])){

			//プリプロセス後のファイル名の設定
			snprintf(preprocess_file_name, FILE_PATH, "%s_out.c_pre.c", argv[i]);

			//インクルードファイルリストを取得
			include_list = INCLUDE_LIST_new();
			readIncludeDataFromFile(preprocess_file_name, include_list);

			yyin = fopen(preprocess_file_name, "r");

			//ファイルのオープンに成功したら、構文解析を開始する
			if(yyin != NULL){
				typedef_table_list = TYPEDEF_TABLE_LIST_new();
				//あらかじめプログラムのASTはNULLにしておく
				programAST = NULL;
				//構文解析の開始
				yyparse();


				//構文解析に成功した場合
				if(error_flag == 0 && programAST != NULL){

					//ASTノードに、返却の型名・ブロックレベル・ブロックIDを付加する。
					setASTReturnType(programAST);
					setASTBlocklevelAndId(programAST);

					//ＸＭＬモードである場合
					if(isXmlMode(flag_database)){
						//AST木全体をXMLとして出力する
						//traverseASTwithXML(programAST, 0);
						printTargetASTNode(programAST, "array_access", 1, 1);
						printTargetASTNode(programAST, "direct_ref", 1, 1);
						printTargetASTNode(programAST, "expression_statement", 1, 1);
						printTargetASTNode(programAST, "function_definition", 1, 1);
						printTargetASTNode(programAST, "if_statement",1, 1);
					}else{
						//AST木全体を出力する
						//traverseAST(programAST, 0);

						//AST木からプログラムを出力する
						int tmp = 1;
						//printDataFromAST(programAST, &tmp);

						//AST木から生成したTYPEDEFテーブルを表示
						//printTYPEDEF_TABLE_LIST(typedef_table_list);

						//AST木から構造体テーブルを生成して出力
						struct_table_list = STRUCT_TABLE_LIST_new();
						getSTRUCT_TABLE_DATA(struct_table_list, programAST);
						//printSTRUCT_TABLE_LIST(struct_table_list);

						//AST木から変数テーブルを生成して出力
						variable_table_list = VARIABLE_TABLE_LIST_new();
						getVARIABLE_TABLE_LIST(variable_table_list, programAST);
						getParameterVARIABLE_TABLE_LIST(variable_table_list, programAST);
						//printVARIABLE_TABLE_LIST(variable_table_list);

						//変数テーブルから検証用変数テーブルを生成して出力
						varidate_variable_list = VARIDATE_VARIABLE_LIST_new();
						getVaridate_Variable(variable_table_list, varidate_variable_list);

						//printVARIDATE_VARIABLE_LIST(varidate_variable_list);

						//関数に関するリストを生成して出力
						function_information_list = FUNCTION_INFORMATION_LIST_new();
						getFunctionInformation(function_information_list, programAST);

						printFUNCTION_INFORMATION_LIST(function_information_list);

						//（実験）指定されたASTの情報を出力
						//printTargetASTNode(programAST, "call_function", 0, 0);
						//printTargetASTNode(programAST, "direct_ref", 0, 0);
						//printTargetASTNode(programAST, "assignment_expression", 0, 0);
						//printTargetASTNode(programAST, "expression_statement", 0, 0);

						//検証式の生成
						varidate_statement_list = VARIDATE_STATEMENT_LIST_new();
						for_information_list = FOR_INFORMATION_LIST_new();
						createVaridateStatementFromArrayDefine(varidate_variable_list, varidate_statement_list, variable_table_list);
						createVaridateStatementFromPointerDefine(varidate_statement_list, variable_table_list);
						createVaridateStatement(programAST,  function_information_list, variable_table_list, varidate_variable_list, varidate_statement_list,
						 for_information_list, isUndefineControlCheckMode(flag_database), isZeroDivitionCheckMode(flag_database), isArrayUnboundCheckMode(flag_database));

						//出力ファイルに検証式付きのプログラムを出力させる
						snprintf(output_file_name, FILE_PATH, "%s_output.c", preprocess_file_name);
						output = fopen(output_file_name, "w");
						//printProgramDataWithVaridateStatement(programAST, varidate_variable_list, varidate_statement_list);
						fprintProgramDataWithVaridateStatement(output, programAST, varidate_variable_list, varidate_statement_list, for_information_list);

						//入力ファイルおよび出力ファイルを閉じる
						fclose(yyin);
						fclose(output);

						//インクルードリストからインクルードを付加する
						addIncludeDataFromFile(output_file_name, include_list);

					}
				}else{
					printf("Syntax_error is occured!! Please Check your source file!!\n");
				}

			}
		}else{
			printf("PreProcesser is failed!! Please Check your source file!!\n");
		}
	}
*/

AST *parserANSIC(FILE *name, TYPEDEF_TABLE_LIST **out_typedef_table_list){
	extern FILE *yyin;
	yyin = name;

	//lineとcolumnを初期化
	line = 1;
	column = 0;

	//あらかじめプログラムのASTはNULLにしておく
	programAST = NULL;
	//タイプ定義を初期化する
	typedef_table_list = TYPEDEF_TABLE_LIST_new();

	//構文解析の開始
	yyparse();

	//構文解析に成功した場合
	if(error_flag == 0 && programAST != NULL){
		*out_typedef_table_list = typedef_table_list;
	}
	//構文解析に失敗した場合は強制終了させる
	else{
		printf("Syntax_error is occured!! Please Check your source file!!\n");
		exit(1);
	}
	return programAST;
}
