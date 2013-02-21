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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;


