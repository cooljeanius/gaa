/* A Bison parser, made by GNU Bison 1.875a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     ACTION = 259,
     TERMINATE = 260,
     CSOURCE = 261,
     CPART = 262,
     TYPE = 263,
     STRING = 264,
     UNDERSCORE_STRINGS = 265,
     INIT = 266,
     DEFITEM = 267,
     OPTION = 268,
     REST = 269,
     HELPNODE = 270,
     OBLIGATORY = 271,
     INCOMPATIBLE = 272,
     DATA = 273,
     AS = 274,
     OPTIONAL = 275
   };
#endif
#define IDENTIFIER 258
#define ACTION 259
#define TERMINATE 260
#define CSOURCE 261
#define CPART 262
#define TYPE 263
#define STRING 264
#define UNDERSCORE_STRINGS 265
#define INIT 266
#define DEFITEM 267
#define OPTION 268
#define REST 269
#define HELPNODE 270
#define OBLIGATORY 271
#define INCOMPATIBLE 272
#define DATA 273
#define AS 274
#define OPTIONAL 275




/* Copy the first part of user declarations.  */
#line 1 "gaa_parser.y"

/*
 *      Copyright (C) 1998,1999 Joran Maille
 *      Portions Copyright (C) 2002 Nikos Mavroyanopoulos
 *
 * This file is part of GAA-ng.
 *
 * GAA-ng is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GAA-ng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

/* needed in newer bisons for yytoknum.
 */
#define YYPRINT
#define YYERROR_VERBOSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../config.h"

#include "gaaout.h"
    
#define NEW(x,first, tmp)              \
    tmp = (x*) malloc(sizeof(x));      \
    tmp->next = first;                 \
    first = tmp;

#define GAA_NOREST            -1
    
#define GAA_SINGLE            0
#define GAA_LIST              1

#define GAA_OBLIGAT           1
#define GAA_INCOMP            2
#define GAAMAX_ARGLIST_COUNT 30


#define LOOKUP(first, tmp,  id, key, _line)                                       \
    for(tmp = first; tmp != NULL; tmp = tmp->next)                                \
    {                                                                             \
        if(tmp->id == key)                                                        \
        {                                                                \
            fprintf(stderr, "%s:%d: identifier '%s' redefined\n", st_in, _line, num2str(key));  \
            fprintf(stderr, "%s:%d: this is the location of the previous definition\n", st_in, tmp->line);  \
            error_flag = 1;                                                        \
        }                                                                          \
    }

#define SUPERLOOKUP(id, key, line)                                                 \
    LOOKUP(first_option, option_tmp,  id, key, line);
    
FILE* glb_fd, *glb_skel;
FILE* glb_out;
FILE* glb_sfd; /* emulates stdin */

int glb_underscore_strings = 0;

int yyerror( char* s);  /* Called by yyparse on error */
int yylex();

int type = 0;
extern int num_lines; /* current line */
char* st_in; /* hold input_filename */

struct _option;
struct _option_argless;
struct _arg;
struct _type;
struct _help;
struct _struct_elt;

typedef struct _option option;
typedef struct _arg arg;
typedef struct _atype atype;
typedef struct _struct_elt struct_elt;
typedef struct _help help;
typedef struct _condition condition;


int k_needed = 0, init_loc = -1, rest_nb_arg = 0;
int error_flag = 0;

int rest_type = GAA_NOREST, rest_action = 0;
int c_code = 0;
int nb_option = 0, nb_option_argless = 0, nb_atype = 0, nb_struct_elt = 0, nb_help = 0;
option *option_tmp, *first_option = NULL;
atype *atype_tmp, *first_atype = NULL;
struct_elt *struct_elt_tmp, *first_struct_elt = NULL;
help *help_tmp, *first_help = NULL;
arg *arg_tmp, *first_rest_arg = NULL;
condition *condition_tmp, *first_condition = NULL;

char* num2str(int n);
int get_id_line(int n);

struct _help
{
    int str;
    int line;
    help *next;
};

help* get_help(int num)
{
    int i;
    help *tmp;
    tmp = first_help;
    for(i = 0; (i < num) && (tmp !=NULL); i++)
    tmp = tmp->next;
    if(tmp == NULL)
    {
        fprintf(stderr, "%s: '%d' out of range\n", st_in, num);
        exit(1);
    }
    return tmp;
}

struct _option
{
    int id1, id2;
    int action;
    int help;
    int nb_arg;
    arg *fa;
    int line;
    option *next;
};

option* get_option(int num)
{
    int i;
    option *tmp;
    tmp = first_option;
    for(i = 0; (i < num) && (tmp !=NULL); i++)
    tmp = tmp->next;
    if(tmp == NULL)
    {
        fprintf(stderr, "%s: '%d' out of range\n", st_in, num);
        exit(1);
    }
    return tmp;
}

struct _condition
{
    int type;
    int options;
    condition *next;
};


struct _arg
{
    int type;
    int help;
    int id;
    arg *next;
};

arg* get_arg(int numOpt, int num)
{
    int i;
    arg *tmp;
    tmp = (get_option(numOpt))->fa;
    for(i = 0; (i < num) && (tmp !=NULL); i++)
    tmp = tmp->next;
    if(tmp == NULL)
    {
        fprintf(stderr, "%s: '%d' out of range\n", st_in, num);
        exit(1);
    }
    return tmp;
}



struct _atype
{
    int id;
    int fnName;
    int argtype;
    int line;
    char* type_str;
    atype *next;
};

atype* get_atype(int num)
{
    int i;
    atype *tmp;
    tmp = first_atype;
    for(i = 0; (i < num) && (tmp !=NULL); i++)
    tmp = tmp->next;
    if(tmp == NULL)
    {
        fprintf(stderr, "%s: '%d' out of range\n", st_in, num);
        exit(1);
    }
    return tmp;
}
atype* get_atype_from_id(int num)
{
    int i;
    atype *tmp;
    tmp = first_atype;
    for(i = 0; (tmp!=NULL) && (tmp->id != num); i++) {
	    tmp = tmp->next;
    }
    if(tmp == NULL)
    {
        fprintf(stderr, "%s:%d: identifier '%s' out of range\n", st_in, 
		get_id_line(num), num2str(num));
        exit(1);
    }
    return tmp;
}

atype* get_type(arg *in)
{
    int i;
    atype *tmp = first_atype;
    for(i = 0; i < nb_atype; i++)
    {
        if(in->id == tmp->id)
            return tmp;
        tmp = tmp->next;
    }
    fprintf(stderr, "%s:%d: Unknown type '%s'.\n", st_in, num_lines - 1, num2str(in->id));
    exit(1);
}


struct _struct_elt
{
    int data; /* 0 for '#' statement, 1 for 'DATA' 'AS' statement */
    int type; /* only if data == 1  GAA_LIST / GAA_SINGLE */
    int id;   /* only if data == 1 */
    int arg_type; /* only if data == 1 */
    int location; /* only if data == 0 */
    struct_elt *next;
};

struct_elt* get_struct_elt(int num)
{
    int i;
    struct_elt *tmp;
    tmp = first_struct_elt;
    for(i = 0; (i < num) && (tmp !=NULL); i++)
    tmp = tmp->next;
    if(tmp == NULL)
    {
        printf("Out of range\n");
        exit(1);
    }
    return tmp;
};

void read_str(FILE* fd, int offset, char **target, char separator)
{
    int i, size = -1;
    int a;
    fseek(fd, offset, SEEK_SET);
    do
    {
        if( (a=fgetc( fd)) == EOF)
        {
            printf("Read error\n");
            exit(1);
        }
        size++;
    }
    while(a != separator);
    *target = malloc(size+1);
    fseek(fd, offset, SEEK_SET);
    for(i = 0; i < size; i++)
    {
        if( (a=fgetc(fd)) == EOF)
        {
            printf("Read error\n");
            exit(1);
        }
       (*target)[i] = a;
    }
    (*target)[size] = 0;
}

/* append is appended to the string output */
void copy_str(FILE* fd, int offset, FILE* out, const char* append)
{
    int a = '"', b, last = ' ';
    int flag;

    fseek(fd, offset-1, SEEK_SET);
    if( (a=fgetc(fd)) == EOF)
    {
        printf("Read error\n");
        exit(1);
    }
    while(a == '"' || a == '%')
    {
        b = a;
        if(a == '"') {
		if (glb_underscore_strings!=0) fputs("_(", out);
	        fprintf(out,"%c", '"');
	}
        flag = 1;
        do
        {
            if( (a=fgetc(fd)) == EOF)
            {
                printf("Read error\n");
                exit(1);
            }
            if((a == b) && (last != '\\'))
            {
                if(flag == 1)
                    flag = 0;
                else
                    flag = 1;
            }
            if((flag == 1) || (a == b && b != '%'))
            {
		if (a=='"' && append!=NULL) fputs( append, out);
                fprintf(out, "%c", a);
		if (a=='"' && glb_underscore_strings!=0) fputs(")", out);
	    }
            last = a;
        }
        while(flag == 1);
        do
        {
            if( (a=fgetc(fd)) == EOF)
            {
                return;
            }
        }
        while ((a == ' ' || a == '\r' || a == '\t' || a == '\n'));
    }
}



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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 494 "gaa_parser.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   73

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  8
/* YYNRULES -- Number of rules. */
#define YYNRULES  28
/* YYNRULES -- Number of states. */
#define YYNSTATES  55

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      22,    23,    21,     2,    24,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    13,    16,    18,    21,
      22,    24,    27,    30,    34,    36,    39,    41,    44,    46,
      51,    54,    57,    62,    70,    80,    84,    87,    90
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      26,     0,    -1,    27,     5,    -1,    27,    -1,     6,    27,
      -1,    32,    -1,    27,    32,    -1,     3,    -1,    21,     3,
      -1,    -1,    30,    -1,    20,    30,    -1,    28,     9,    -1,
      28,     9,    30,    -1,    28,    -1,    28,    30,    -1,     9,
      -1,    31,     9,    -1,     7,    -1,    18,     3,    19,    28,
      -1,    15,    31,    -1,    11,     4,    -1,    12,     3,     3,
       7,    -1,    13,    22,     3,    23,    29,     4,    31,    -1,
      13,    22,     3,    24,     3,    23,    29,     4,    31,    -1,
      14,    29,     4,    -1,    16,     3,    -1,    17,     3,    -1,
      10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   381,   381,   382,   383,   387,   388,   391,   395,   401,
     405,   411,   418,   425,   432,   439,   448,   451,   456,   463,
     480,   491,   492,   501,   544,   593,   617,   624,   631
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "ACTION", "TERMINATE", 
  "CSOURCE", "CPART", "TYPE", "STRING", "UNDERSCORE_STRINGS", "\"init\"", 
  "\"defitem\"", "\"option\"", "\"rest\"", "\"helpnode\"", "\"obligat\"", 
  "\"incomp\"", "\"data\"", "\"as\"", "\"optional\"", "'*'", "'('", "')'", 
  "','", "$accept", "input", "source", "arg", "arg_list", "arg_real_list", 
  "many_strings", "line", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    42,    40,    41,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    25,    26,    26,    26,    27,    27,    28,    28,    29,
      29,    30,    30,    30,    30,    30,    31,    31,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     1,     2,     1,     2,     1,     2,     0,
       1,     2,     2,     3,     1,     2,     1,     2,     1,     4,
       2,     2,     4,     7,     9,     3,     2,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,    18,    28,     0,     0,     0,     9,     0,     0,
       0,     0,     0,     3,     5,     4,    21,     0,     0,     7,
       0,     0,    14,     0,    10,    16,    20,    26,    27,     0,
       1,     2,     6,     0,     0,    11,     8,    12,    15,    25,
      17,     0,    22,     9,     0,    13,    19,     0,     0,     0,
       9,    23,     0,     0,    24
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,    12,    13,    22,    23,    24,    26,    14
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -43
static const yysigned_char yypact[] =
{
      31,    43,   -43,   -43,     8,    12,   -18,    -1,    15,    23,
      24,    36,    40,    18,   -43,    43,   -43,    48,    49,   -43,
      -1,    59,    -3,    60,   -43,   -43,    54,   -43,   -43,    46,
     -43,   -43,   -43,    61,   -13,   -43,   -43,    -1,   -43,   -43,
     -43,     0,   -43,    -1,    63,   -43,   -43,    65,    44,    15,
      -1,    54,    66,    15,    54
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -43,   -43,    70,    32,   -42,   -15,   -40,     1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      19,    47,    19,    19,    18,    35,    37,    38,    52,    51,
      43,    44,    16,    54,    32,    17,    32,    20,    21,    20,
      21,    21,    45,    31,    25,     2,    27,    28,     3,     4,
       5,     6,     7,     8,     9,    10,    11,     1,     2,    29,
      30,     3,     4,     5,     6,     7,     8,     9,    10,    11,
       2,    33,    34,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    36,    40,    39,    41,    48,    50,    42,    49,
      53,    15,     0,    46
};

static const yysigned_char yycheck[] =
{
       3,    43,     3,     3,    22,    20,     9,    22,    50,    49,
      23,    24,     4,    53,    13,     3,    15,    20,    21,    20,
      21,    21,    37,     5,     9,     7,     3,     3,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     6,     7,     3,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
       7,     3,     3,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     3,     9,     4,    19,     3,    23,     7,     4,
       4,     1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     6,     7,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    26,    27,    32,    27,     4,     3,    22,     3,
      20,    21,    28,    29,    30,     9,    31,     3,     3,     3,
       0,     5,    32,     3,     3,    30,     3,     9,    30,     4,
       9,    19,     7,    23,    24,    30,    28,    29,     3,     4,
      23,    31,    29,     4,    31
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		do				\
			  {				\
			    yylerrsp = yylsp;		\
			    *++yylerrsp = yyloc;	\
			    goto yyerrlab1;		\
			  }				\
			while (0)


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yytype, yyvaluep, yylocationp)
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  YYLTYPE *yylerrsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 381 "gaa_parser.y"
    { c_code = yyvsp[0]; }
    break;

  case 3:
#line 382 "gaa_parser.y"
    { c_code = -1; }
    break;

  case 4:
#line 383 "gaa_parser.y"
    { c_code = yyvsp[-1]; }
    break;

  case 7:
#line 392 "gaa_parser.y"
    {
            yyval = yyvsp[0];
        }
    break;

  case 8:
#line 396 "gaa_parser.y"
    {
            yyval = -yyvsp[0];
        }
    break;

  case 9:
#line 401 "gaa_parser.y"
    {
        yyval = (int)malloc(sizeof(int));
        ((int*)yyval)[0] = 0;
        }
    break;

  case 10:
#line 406 "gaa_parser.y"
    {
            yyval = yyvsp[0];
        }
    break;

  case 11:
#line 412 "gaa_parser.y"
    {
	        yyval = yyvsp[0];
                ((int*)yyval)[0]++;
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 1] = 0;
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 2] = -1;
        }
    break;

  case 12:
#line 419 "gaa_parser.y"
    {
        	yyval = (int)malloc((2 * GAAMAX_ARGLIST_COUNT + 1)* sizeof(int));
                ((int*)yyval)[0] = 1;
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 1] = yyvsp[-1];
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 2] = yyvsp[0];
        }
    break;

  case 13:
#line 426 "gaa_parser.y"
    {
        	yyval = yyvsp[0];
                ((int*)yyval)[0]++;
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 1] = yyvsp[-2];
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 2] = yyvsp[-1];
        }
    break;

  case 14:
#line 433 "gaa_parser.y"
    {
        	yyval = (int)malloc((2 * GAAMAX_ARGLIST_COUNT + 1)* sizeof(int));
                ((int*)yyval)[0] = 1;
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 1] = yyvsp[0];
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 2] = -1;
        }
    break;

  case 15:
#line 440 "gaa_parser.y"
    {
        	yyval = yyvsp[0];
                ((int*)yyval)[0]++;
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 1] = yyvsp[-1];
                ((int*)yyval)[2*(((int*)yyval)[0] - 1) + 2] = -1;
        }
    break;

  case 16:
#line 448 "gaa_parser.y"
    {
		yyval = yyvsp[0];
	}
    break;

  case 17:
#line 451 "gaa_parser.y"
    {
		yyval = yyvsp[-1];
	}
    break;

  case 18:
#line 457 "gaa_parser.y"
    {
            NEW(struct_elt, first_struct_elt, struct_elt_tmp);
            struct_elt_tmp->data = 0;
            struct_elt_tmp->location = yyvsp[0];
            nb_struct_elt++;
        }
    break;

  case 19:
#line 464 "gaa_parser.y"
    {
            NEW(struct_elt, first_struct_elt, struct_elt_tmp);
            struct_elt_tmp->data = 1;
            struct_elt_tmp->id = yyvsp[-2];
            if(yyvsp[0] < 0)
            {
                struct_elt_tmp->type = GAA_LIST;
                struct_elt_tmp->arg_type = -yyvsp[0];
            }
            else
            {
                struct_elt_tmp->type = GAA_SINGLE;
                struct_elt_tmp->arg_type = yyvsp[0];
            }
            nb_struct_elt++;
        }
    break;

  case 20:
#line 481 "gaa_parser.y"
    {
            NEW(help, first_help, help_tmp);
            help_tmp->str = yyvsp[0];
            help_tmp->line = yylsp[-1].first_line;
            nb_help++;
            
            fprintf(glb_out, "\tprintf(");
            copy_str(glb_fd, yyvsp[0], glb_out, "\\n");
            fprintf(glb_out, ");\n");
        }
    break;

  case 21:
#line 491 "gaa_parser.y"
    { init_loc = yyvsp[0]; }
    break;

  case 22:
#line 493 "gaa_parser.y"
    {
            NEW(atype, first_atype, atype_tmp);
            atype_tmp->id = yyvsp[-2];
            atype_tmp->fnName = yyvsp[-1];
            atype_tmp->argtype = yyvsp[0];
            nb_atype++;

        }
    break;

  case 23:
#line 502 "gaa_parser.y"
    {
            int i, *tab, sent=0;
            SUPERLOOKUP(id2, yyvsp[-4], yylsp[-6].first_line);
            NEW(option, first_option, option_tmp);
            option_tmp->fa = NULL;
            option_tmp->id1 = 0;
            option_tmp->id2 = yyvsp[-4];
            option_tmp->action = yyvsp[-1];
            option_tmp->line = yylsp[-6].first_line;
            option_tmp->help = yyvsp[0];
            tab = (int*)yyvsp[-2];
            option_tmp->nb_arg = tab[0];
            nb_option++;

   	    fprintf(glb_out, "\t__gaa_helpsingle(0, \"%s\", ", num2str(yyvsp[-4]));

	    for(i = 1; i < option_tmp->nb_arg  + 1; i++)
            {

                NEW(arg, option_tmp->fa, arg_tmp);

                arg_tmp->id = tab[2*(i-1) + 1];
                if(tab[2*(option_tmp->nb_arg-i)  + 2]>0)
                {
		    sent++;
                    copy_str(glb_fd, tab[2*(option_tmp->nb_arg-i)  + 2], glb_out, " ");
		}
                if(arg_tmp->id < 0)
                {
                    arg_tmp->type = GAA_LIST;
                    arg_tmp->id *= -1;
                }
                else
                {
                    arg_tmp->type = GAA_SINGLE;
                }
            }
            if (sent==0) fputs( "\"\"", glb_out);
	    fprintf(glb_out, ", ");
            copy_str(glb_fd, yyvsp[0], glb_out, NULL);
            fprintf(glb_out,");\n");
        }
    break;

  case 24:
#line 545 "gaa_parser.y"
    {
            int i, *tab, sent=0;
            SUPERLOOKUP(id2, yyvsp[-4], yylsp[-8].first_line);
            SUPERLOOKUP(id1, yyvsp[-6], yylsp[-8].first_line);

            if(strlen(num2str(yyvsp[-6])) != 1)
            {
                fprintf( stderr, "%s:%d: first identifier must be a single character\n", st_in, yylsp[-8].first_line);
                error_flag = 1;
            }
            NEW(option, first_option, option_tmp);
            option_tmp->fa = NULL;
            option_tmp->id1 = yyvsp[-6];
            option_tmp->id2 = yyvsp[-4];
            option_tmp->action = yyvsp[-1];
            option_tmp->line = yylsp[-8].first_line;
            option_tmp->help = yyvsp[0];
            tab = (int*)yyvsp[-2];
            option_tmp->nb_arg = tab[0];
            nb_option++;
	    fprintf(glb_out, "\t__gaa_helpsingle('%c', \"%s\", ",
		num2str(yyvsp[-6])[0], num2str(yyvsp[-4]));
            for(i = 1; i < option_tmp->nb_arg  + 1; i++)
            {
		
                NEW(arg, option_tmp->fa, arg_tmp);

                arg_tmp->id = tab[2*(i-1) + 1];
                if(tab[2*(option_tmp->nb_arg-i)  + 2]>0)
                {
		    sent++;
                    copy_str(glb_fd, tab[2*(option_tmp->nb_arg-i)  + 2], glb_out, " ");
                }
                if(arg_tmp->id < 0)
                {
                    arg_tmp->type = GAA_LIST;
                    arg_tmp->id *= -1;
                }
                else
                {
                    arg_tmp->type = GAA_SINGLE;
                }
            }
            if (sent==0) fputs( "\"\"", glb_out);
            fprintf(glb_out, ", ");
            copy_str(glb_fd, yyvsp[0], glb_out, NULL);
            fprintf(glb_out,");\n");
        }
    break;

  case 25:
#line 594 "gaa_parser.y"
    {
            int i, *tab;
            
            rest_action = yyvsp[0];
            tab = (int*)yyvsp[-1];
            rest_nb_arg = tab[0];
            
            for(i = 1; i < rest_nb_arg  + 1; i++)
            {
                NEW(arg, first_rest_arg, arg_tmp);

                arg_tmp->id = tab[2*(i-1) + 1];
                if(arg_tmp->id < 0)
                {
                    arg_tmp->type = GAA_LIST;
                    arg_tmp->id *= -1;
                }
                else
                {
                    arg_tmp->type = GAA_SINGLE;
                }
            }
        }
    break;

  case 26:
#line 618 "gaa_parser.y"
    {
            NEW(condition, first_condition, condition_tmp);
            condition_tmp->options = yyvsp[0];
            condition_tmp->type = GAA_OBLIGAT;
	    k_needed = 1;
        }
    break;

  case 27:
#line 625 "gaa_parser.y"
    {
            NEW(condition, first_condition, condition_tmp);
            condition_tmp->options = yyvsp[0];
            condition_tmp->type = GAA_INCOMP;
	    k_needed = 1;
        }
    break;

  case 28:
#line 632 "gaa_parser.y"
    {
	    glb_underscore_strings = 1;
        }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1748 "gaa_parser.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }

  yylerrsp = yylsp;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp, yylsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval, &yylloc);
      yychar = YYEMPTY;
      *++yylerrsp = yylloc;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp, yylsp);
      yyvsp--;
      yystate = *--yyssp;
      yylsp--;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  YYLLOC_DEFAULT (yyloc, yylsp, (yylerrsp - yylsp));
  *++yylsp = yyloc;

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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 637 "gaa_parser.y"


extern int loc_index;

struct _idStruct;
typedef struct _idStruct idStruct;

struct _idStruct
{
    char *name;
    int line; /* the first line it was encountered */
    idStruct *next;
};

idStruct *firstId = NULL;

#define RM(x) remove_illegal_C_char(x)
static char *remove_illegal_C_char( const char* str)
{
static char ret[512];
int i;
	if (strlen(str)+1 > sizeof(ret)) {
		fprintf(stderr, "num2str: Too long string\n");
		exit(1);
	}
	memset( ret, 0, sizeof ret);
	for (i=0;i<strlen(str);i++) {
		ret[i] = str[i];
		if (ret[i]=='-') ret[i]='_';
	}
	ret[i]=0;

	return ret;
}

char* num2str(int n)
{
    int i;
    idStruct *tmp;
    tmp = firstId;
    if(n == 0)
	return "";
    for(i = 0; (i < n - 1) && (tmp != NULL); i++)
    {
        tmp = tmp->next;
    }
    if(tmp == NULL)
    {
        fprintf(stderr, "num2str: Out of range\n");
        exit(1);
    }
    return tmp->name;
}

/* returns the line of the identifier, indexed
 * by n;
 */
int get_id_line(int n)
{
    int i;
    idStruct *tmp;
    tmp = firstId;
    if(n == 0)
	return num_lines - 1;
    for(i = 0; (i < n - 1) && (tmp != NULL); i++)
    {
        tmp = tmp->next;
    }
    if(tmp == NULL)
    {
        fprintf(stderr, "get_id_line: Out of range\n");
        exit(1);
    }
    return tmp->line;
}

int length(char *a)
{
    int i = 0;
    while(*(a+i) != 0) i++;
    return i;
}


int getTokenNum( char* str) {
int i;
     for (i = 0; i < YYNTOKENS; i++)
     {
     	   if (yytname[i] != 0
		&& yytname[i][0] == '"'
    	        && strncasecmp (yytname[i] + 1, str, strlen (str)) == 0
 	        && yytname[i][strlen (str) + 1] == '"'
                && yytname[i][strlen (str) + 2] == 0)
	   {
	       return yytoknum[i];
	   }
     }
     return -1;
}

int getIdNum(char *name, int line)
{
    int len, data = 1;
    idStruct **pter, *blurp;
    
    pter = &firstId;
    while(*pter != NULL)
    {
        if(strcmp(name, (*pter)->name) == 0)
            break;
        data++;
        pter = &((*pter)->next);
    }
    if(*pter == NULL)
    {
        blurp = *pter;
        len = length(name);
        blurp = malloc(sizeof(idStruct));
        *pter = blurp;
        blurp->name = malloc((len + 1)* sizeof(char));
        strcpy(blurp->name, name);
        blurp->next = NULL;
        blurp->line = line;
    }

    return data;
}

#define MAXIDSIZE 300

char *tmpStr;


int yyerror( char* s)  /* Called by yyparse on error */
{
    fprintf (stderr, "%s:%d: %s\n", st_in, num_lines, s);
    exit(1);
}

/* Copies the skel file to target file
 * if term!=EOF, then the file is copied until
 * the terminator byte.
 * 
 * This function will use the file seek pointers
 * to keep a state in copying.
 */
void copy_file_state(FILE* source, FILE* target, int term)
{
    int a;
    do
    {
        if( (a=fgetc(source)) == EOF && term!=EOF)
        {
            fprintf(stderr, "copy_file_state: Source read error\n");
            exit(1);
        }
        if(a != term)
        {
            if(fputc(a, target) == EOF)
            {
                fprintf(stderr, "copy_file_state: Output write error\n");
                exit(1);
            }
        }
    }
    while(a != term);
}

/* Returns the number of the line, that the index-th character
 * is placed.
 */
int getline(FILE* fd, int index)
{
    int tmp, line = 1, i;
    int a = 0;
    tmp = fseek(fd, 0, SEEK_CUR);
    fseek(fd, 0, SEEK_SET);
    for(i = 0; i < index; i++)
    {
        a=fgetc(fd);
        if(a==EOF) {
            printf("Read error\n");
            exit(1);
	}
        if(a == '\n')
            line++;
    }
    fseek(fd, tmp, SEEK_SET);
    return line;
}

/* term holds the terminator character ';', or '\n'
 */
void copy_line(FILE* fd, int index, FILE* target, char* file, char term)
{
    int a;
    fprintf(target, "#line %d \"%s\"\n\t", getline(fd, index), file);
    fseek(fd, index, SEEK_SET);
    do
    {
        if( (a=fgetc(fd)) == EOF)
        {
            printf("Read error\n");
            exit(1);
        }
        if(fputc(a, target) == EOF)
        {
            printf("Output write error\n");
            exit(1);
        }
    }
    while(a != term);
}

void put_action( FILE* fd, int index, FILE* target, char *opt, int narg, char* file)
{
    int a;
    char *str_cmp;
    int i, flag = 1;
    fprintf(target, "#line %d \"%s\"\n", getline(fd, index), file);
    fprintf(target, "{");
    fseek(fd, index, SEEK_SET);
    if(opt[0] == 0)
        str_cmp = "GAAREST_tmp";
    else
        str_cmp = "GAATMP_";
    while(flag != 0)
    {
        if( (a=fgetc(fd)) == EOF)
        {
            printf("Read error\n");
            exit(1);
        }
        switch(a)
            {
            case '{':
                flag ++;
                break;
            case '}':
                flag --;
                break;
            case '@':
                i = 0;
                a = '0';
                flag *= -1;
                do
                {
                    i *= 10;
                    i += (a - '0');
                    if( (a=fgetc(fd)) == EOF)
                    {
                        printf("Read error\n");
                        exit(1);
                    }
                }
                while(isdigit(a) != 0);
                fseek(fd, -1, SEEK_CUR);
                if(( i > narg ) || (i <= 0))
                {
                    printf("Fatal: Option %s: argument $%d unknown\n", opt, i);
                    exit(1);
                }
                fprintf(target, "%s%s.size%d", str_cmp, RM(opt), i);
                break;
            case '$':
                if( (a=fgetc(fd)) == EOF)
                {
                    printf("Read error\n");
                    exit(1);
                }
                fseek(fd, -1, SEEK_CUR);
                flag *= -1;
                if(isdigit(a) == 0)
                {
                    fprintf(target, "gaaval->");
                }
                else
                {
                    i = 0;
                    a = '0';
                    do
                    {
                        i *= 10;
                        i += (a - '0');
                        if( (a=fgetc(fd)) == EOF)
                        {
                            printf("Read error\n");
                            exit(1);
                        }
                    }
                    while(isdigit(a) != 0);
                    fseek(fd, -1, SEEK_CUR);
                    if(( i > narg ) || (i <= 0))
                    {
                        printf("Fatal: Option %s: argument $%d unknown\n", opt, i);
                        exit(1);
                    }
                    fprintf(target, "%s%s.arg%d", str_cmp, RM(opt), i);
                }
                break;
            default:  break;
            }
        if(flag > 0)
        {
            if(fputc( a, target) == EOF)
            {
                printf("Output write error\n");
                exit(1);
            }
        }
        if(flag < 0)
            flag *= -1;
    }
    fprintf(target, ";};\n");
}

/* copies the file until it finds #} */
void copy_file(FILE* fd, int index, FILE* target, char *file)
{
    int a, pa = -1;
    fprintf(target, "#line %d \"%s\"\n", getline(fd, index), file);
    fseek(fd, index, SEEK_SET);
    while( (a=fgetc(fd)) != EOF)
    {
        if (pa=='#' && a=='}') break;

	if (pa!=-1)
		if(fputc( pa, target) == EOF)
	        {
	            printf("Output write error\n");
	            exit(1);
	       	}
	pa = a;
    };

    if (a==EOF) {
	    if(fputc( pa, target) == EOF)
	    {
	            printf("Output write error\n");
	            exit(1);
	    }
    }
}

void add_type(char *id, char *fnName, char *type)
{
    NEW(atype, first_atype, atype_tmp);
    atype_tmp->id = getIdNum(id, 0);
    atype_tmp->fnName = getIdNum(fnName, 0);
    atype_tmp->type_str = type;
    nb_atype++;
}

#define SHORTNAME num2str(option_tmp_loc->id1)
#define LONGNAME num2str(option_tmp_loc->id2)

char __optional_flag;

void write_get_arg(FILE *out, arg *x, char *name, int arg_number)
{
    char *str_name;
    char _name[512];

    strcpy( _name, RM(name));

    if(x->id == 0)
	{
	__optional_flag = 1;
	return;
	}
    
    if(name[0] == 0)
        str_name = "GAAREST_tmp";
    else
        str_name = "GAATMP_";

    if(x->type == GAA_SINGLE)
     {
	if(__optional_flag)
	{
        fprintf(out, "\t\tGAA_TESTMOREOPTIONALARGS;\n\t\tGAA_FILL(%s%s.arg%d, %s, %s%s.size%d);\n\t\tgaa_index++;\n",
                str_name,_name,arg_number,RM(num2str(get_type(x)->fnName)),str_name,_name,arg_number);
	}
	else
        {
        fprintf(out, "\t\tGAA_TESTMOREARGS;\n\t\tGAA_FILL(%s%s.arg%d, %s, %s%s.size%d);\n\t\tgaa_index++;\n",
                str_name,_name,arg_number,RM(num2str(get_type(x)->fnName)),str_name, _name,arg_number);
        }
     }
    else
     {
        if(!__optional_flag)
        fprintf(out, "\t\tGAA_LIST_FILL(%s%s.arg%d, %s, %s, %s%s.size%d);\n",
                str_name,_name,arg_number,
                RM(num2str(get_type(x)->fnName)), get_type(x)->type_str,
                str_name,_name,arg_number);
	else
        fprintf(out, "\t\tGAA_OPTIONALLIST_FILL(%s%s.arg%d, %s, %s, %s%s.size%d);\n",
                str_name,_name,arg_number,
                RM(num2str(get_type(x)->fnName)), get_type(x)->type_str,
                str_name,_name,arg_number);
     }
}

#define EXT_GAA_H "_gaa.h"
#define EXT_GAA_C "_gaa.c"

int main(int argc, char **argv)
{
    option *option_tmp_loc;
    atype *atype_tmp_loc;
    struct_elt *struct_elt_tmp_loc;
/*    help *help_tmp_loc;   */
    arg *arg_tmp_loc;
    FILE* fd,* skel;
    FILE *out,*header;
    int i, j, k, header_start, header_limit;
    int rval;
    int a;
    char *st_out,*st_header, *ptr;
    gaainfo info;

    if(gaa(argc, argv, &info) != -1)
    {
	fprintf(stderr, "Error in the arguments.\n");
	fprintf(stderr, "Use the -h or --help parameters for help.\n");
        return 0;
    }
    if(info.skel == NULL)
      {
       j = 0;
       info.skel = malloc(sizeof(char) * (length("gaa.skel") + length(argv[0])));
       for(i = 0; i < length(argv[0]); i++)
	  {
	    if(argv[0][i] == '\\')
		j = i+1;
            info.skel[i] = argv[0][i];
	  }
       strcpy(info.skel + j, "gaa.skel");
      }
    st_in = info.input; st_out = info.output; st_header = info.header;

    /* generate file names
     */
    if (st_header==NULL) {
	st_header= malloc( strlen(st_in)+ strlen(EXT_GAA_H));
        strcpy(st_header, st_in);
	ptr = strstr( st_header, ".gaa");
	if (ptr==NULL)
		strcat( st_header, EXT_GAA_H);
	else
		strcpy( ptr, EXT_GAA_H);
    }
    if (st_out==NULL) {
	st_out= malloc( strlen(st_in)+ strlen(EXT_GAA_C));
        strcpy(st_out, st_in);
	ptr = strstr( st_out, ".gaa");
	if (ptr==NULL) 
		strcat( st_out, EXT_GAA_C);
	else
		strcpy( ptr, EXT_GAA_C);
    }

    if((skel = fopen(info.skel, "r")) == NULL)
    {
        printf("Couldn't open skeleton file: %s\n", info.skel);
        exit(1);
    }
    if((glb_fd = fopen(st_in, "r")) == NULL)
    {
        printf("Couldn't open gaa file '%s'.\n", st_in);
        exit(1);
    }
    if((out = fopen(st_out, "w+")) == NULL)
    {
        printf("Couldn't open output file '%s'.\n", st_out);
        exit(1);
    }
    if((glb_out = tmpfile()) == NULL)
    {
        printf("Couldn't open tmp output file.\n");
        exit(1);
    }
    glb_skel = skel;
    tmpStr = malloc((MAXIDSIZE + 1)*sizeof(char));

    if(( glb_sfd=fopen(st_in, "r")) == NULL)
    {
        printf("Couldn't open gaa file\n");
        exit(1);
    }

    fprintf(out, "/* File generated by GAA %s\n */\n", VERSION);


    if (info.prefix) {
	fprintf(out, "\n#define gaainfo %sgaainfo\n", info.prefix);
	fprintf(out, "#define gaa %sgaa\n", info.prefix);
	fprintf(out, "#define gaa_help %sgaa_help\n", info.prefix);
	fprintf(out, "#define gaa_file %sgaa_file\n", info.prefix);
    }

    /* write the WIN32 headers */
    if(info.win32 == 1)
      fprintf(out, "#define GAA_WIN32\n");
    else  
      fprintf(out, "#define GAA_NO_WIN32\n");

    /* Parse the input file */
    rval = yyparse();
    fclose( glb_sfd);
    free(tmpStr);

    fd = glb_fd;

    /* Write the C declarations */
    if(c_code != -1)
        copy_file(fd, c_code, out, st_in);

    /* Write the skel file */
    copy_file_state(skel,out, '@');

    fseek( glb_out, 0, SEEK_SET);
    copy_file_state(glb_out, out, EOF);
    fclose(glb_out); /* close tmp file */

    copy_file_state(skel,out, '@');

    header_start = ftell(out);
    if((rval != 0) || (error_flag == 1))
        return 1;
    
    for(i = 0; i < nb_atype; i++)
    {
        atype_tmp_loc = get_atype(i);
        read_str(fd, atype_tmp_loc->argtype, &(atype_tmp_loc->type_str), ';');
    }
    add_type("STR", "gaa_getstr", "char*");
    add_type("INT", "gaa_getint", "int");
    add_type("CHAR", "gaa_getchar", "char");
    add_type("FLOAT", "gaa_getfloat", "float");
    
    copy_file_state(skel,out, '@');
    for(i = 0; i < nb_struct_elt; i++)
    {
        struct_elt_tmp_loc = get_struct_elt(i);
        if(struct_elt_tmp_loc->data == 0)
            copy_line(fd, struct_elt_tmp_loc->location, out, st_in, ';');
        else
        {
            if(struct_elt_tmp_loc->type == GAA_SINGLE)
            fprintf(out, "\t%s %s;",
                    get_atype_from_id(struct_elt_tmp_loc->arg_type)->type_str,
                    num2str(struct_elt_tmp_loc->id));
            else
            fprintf(out, "\t%s *%s;",
                    get_atype_from_id(struct_elt_tmp_loc->arg_type)->type_str,
                    num2str(struct_elt_tmp_loc->id));
        }
        fprintf(out, "\n");
    }
    copy_file_state(skel,out, '@');
    header_limit = ftell(out);
    copy_file_state(skel,out, '@');

    fprintf(out, "%d\n", nb_option + nb_option_argless);

    for(j = 0; j < nb_option; j++)
    {
        option_tmp_loc = get_option(j);

        fprintf(out,"#define GAAOPTID_%s\t%d\n", RM(num2str( option_tmp_loc->id2)),
	 j + 1 );
    }

    copy_file_state(skel,out, '@');
    for(i = 0; i < nb_option; i++)
    {
	k = 0;
        option_tmp_loc = get_option(i);
        if(option_tmp_loc->nb_arg > 0)
        {
         fprintf(out, "\nstruct GAAOPTION_%s \n{\n", RM(num2str(option_tmp_loc->id2)));
         for(j = 0; j < option_tmp_loc->nb_arg; j++)
         {
             arg_tmp_loc = get_arg(i,j);
	    if(arg_tmp_loc->id != 0)
	    {
	     k++;
             atype_tmp_loc = get_type(arg_tmp_loc);
             fprintf(out, "\t%s", atype_tmp_loc->type_str);
             if(arg_tmp_loc->type == GAA_LIST)
                 fprintf(out, "*");
             fprintf(out, " arg%d;\n", k);
/*             if(arg_tmp_loc->type == GAA_LIST) */
                 fprintf(out, "\tint size%d;\n", k);
	   }
         }
        fprintf(out, "};\n");
       }
    }
    if(rest_nb_arg != 0)
    {
        fprintf(out, "#define GAA_REST_EXISTS\n");
        fprintf(out, "\nstruct GAAREST\n{\n");
	j = 0;
        for(arg_tmp_loc = first_rest_arg; arg_tmp_loc != NULL; arg_tmp_loc = arg_tmp_loc->next)
        {

	    if(arg_tmp_loc->id != 0)
	    {
            atype_tmp_loc = get_type(arg_tmp_loc);
            fprintf(out, "\t%s", atype_tmp_loc->type_str);
            if(arg_tmp_loc->type == GAA_LIST)
                fprintf(out, "*");
            fprintf(out, " arg%d;\n", j + 1);
/*            if(arg_tmp_loc->type == GAA_LIST)*/
                fprintf(out, "\tint size%d;\n", j+1);
	    j++;
	    }
        }
        fprintf(out, "};\n");
    }
    copy_file_state(skel,out, '@');
    for(j = 0; j < nb_option; j++)
    {
        option_tmp_loc = get_option(j);
        if(option_tmp_loc->nb_arg != 0)
        fprintf(out,"\t\t\tGAA_CHECK1STR(\"%s\", GAAOPTID_%s);\n",
		num2str(option_tmp_loc->id1), RM(num2str(option_tmp_loc->id2)));
    }
    copy_file_state(skel,out,'@');
    for(j = 0; j < nb_option; j++)
    {
        option_tmp_loc = get_option(j);
        if(option_tmp_loc->nb_arg == 0)
        fprintf(out,"\t\t\tGAA_CHECK1STR(\"%s\", GAAOPTID_%s);\n",
		num2str(option_tmp_loc->id1), RM(num2str(option_tmp_loc->id2)));
    }
    copy_file_state(skel,out, '@');
    for(j = 0; j < nb_option; j++)
    {
        option_tmp_loc = get_option(j);
        fprintf(out,"\t\t\tGAA_CHECKSTR(\"%s\", GAAOPTID_%s);\n",
		num2str(option_tmp_loc->id2), RM(num2str(option_tmp_loc->id2)));
    }
    copy_file_state(skel,out, '@');
    
    for(j = 0; j < nb_option; j++)
    {
        option_tmp_loc = get_option(j);
	if(option_tmp_loc->nb_arg > 0)
        fprintf(out,"\tstruct GAAOPTION_%s GAATMP_%s;\n",
		RM(num2str(option_tmp_loc->id2)), RM(num2str(option_tmp_loc->id2)));
    }
    copy_file_state(skel,out, '@');
/*    for(j = 0; j < nb_option_argless; j++)
    {
        option_argless_tmp_loc = get_option_argless(j);
        fprintf(out,"\tcase GAAOPTID_%s:\n", RM(ALONGNAME));
        put_action(fd, option_argless_tmp_loc->action, out, ALONGNAME, 0, st_in);
        fprintf(out,"\n\t\treturn GAA_OK;\n\t\tbreak;\n");
    }     */
    for(i = 0; i < nb_option; i++)
    {
        __optional_flag = 0;
        option_tmp_loc = get_option(i);
        fprintf(out,"\tcase GAAOPTID_%s:\n\tOK = 0;\n", RM(LONGNAME));
	k = 0;
        for(j = 0; j < option_tmp_loc->nb_arg; j++)
        {
            arg_tmp_loc = get_arg(i,j);
	    if(arg_tmp_loc->id != 0)
		k ++;
            write_get_arg(out, arg_tmp_loc, LONGNAME, k);
        }
        put_action(fd, option_tmp_loc->action, out, LONGNAME, option_tmp_loc->nb_arg, st_in);
        fprintf(out,"\n\t\treturn GAA_OK;\n\t\tbreak;\n");
    }
    if(rest_nb_arg != 0)
    {
        j = 1;
        fprintf(out,"\tcase GAA_REST:\n");
        for(arg_tmp_loc = first_rest_arg; arg_tmp_loc != NULL; arg_tmp_loc = arg_tmp_loc->next)
        {
            write_get_arg(out, arg_tmp_loc, "", j);
            if(arg_tmp_loc->id != 0)
              j++;
        }
        put_action(fd, rest_action, out, "", rest_nb_arg, st_in);
        fprintf(out,"\n\t\treturn GAA_OK;\n\t\tbreak;\n");
    }
    copy_file_state(skel,out, '@');
    if(k_needed)
        fprintf(out, ", k");
    copy_file_state(skel, out, '@');
    if(init_loc >= 0)
        put_action(fd, init_loc, out, "init", 0, st_in);
    copy_file_state(skel,out, '@');
    for(condition_tmp = first_condition; condition_tmp != NULL;
        condition_tmp = condition_tmp->next)
    {
        switch(condition_tmp->type)
            {
            case GAA_OBLIGAT:
                fprintf(out, "\tGAA_OBLIGAT(\"%s\");\n", num2str(condition_tmp->options));
                break;
            case GAA_INCOMP:
                fprintf(out, "\tGAA_INCOMP(\"%s\");\n", num2str(condition_tmp->options));
                break;
            default:  break;
            }
    }
    copy_file_state(skel,out, '@');
    
    
    if((header = fopen(st_header, "w")) == NULL)
    {
        printf("Couldn't open header file '%s'.\n", st_header);
        exit(1);
    }

    if (info.prefix) {
	fprintf(header, "\n#define gaainfo %sgaainfo\n", info.prefix);
	fprintf(header, "#define gaa %sgaa\n", info.prefix);
	fprintf(header, "#define gaa_help %sgaa_help\n", info.prefix);
	fprintf(header, "#define gaa_file %sgaa_file\n", info.prefix);
    }

    fseek(out, header_start, SEEK_SET);
    for(i = header_start; i < header_limit; i++)
    {
        if( (a=fgetc(out)) == EOF)
        {
            printf("Read error\n");
            exit(1);
        }
        if(fputc( a, header) == EOF)
        {
            printf("Header write error\n");
            exit(1);
        }
    }

    if (info.prefix) {
	fprintf(header, "\n#undef gaainfo\n");
	fprintf(header, "#undef gaa\n");
	fprintf(header, "#undef gaa_help\n");
	fprintf(header, "#undef gaa_file\n\n");
    }
        
    return 0;
}

void gaa_version(void) {
	printf("Reading skeleton from %s\n", SKEL_DIR);
	printf("gaa version %s\n", VERSION);
}

