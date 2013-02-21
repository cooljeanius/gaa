%{
/*
 *      Copyright (C) 2002 Nikos Mavroyanopoulos
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

#include <stdio.h>
#include <string.h>
#include <gaa_parser.h>

void yyerror( char*);

int num_lines = 1, loc_index = 0;

int getIdNum(char *name, int line);
int getTokenNum(char *name);
extern FILE* glb_sfd;

extern YYLTYPE yylloc;

%}

%option noyywrap
%x comment
%x string
%x csource
%x define
%x identifier

%{
 #define YY_INPUT(buf,result,max_size) \
 { \
   int c = getc( glb_sfd); \
   loc_index++; \
   if (c=='\n') num_lines++; \
   result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
 }
%}


%%

[ \t\r]+$       /* ignore this token */
[ \t\r\n]+        /* this too */


[a-zA-Z0-9_-]+\** { /* tokens or identifiers 
		    * (ie. helpnode, STR) */
		int ret;
//		yylval = loc_index;
	        yylloc.first_line = num_lines;
		ret = getTokenNum( yytext);

		if (ret >= 0) return ret;

		yylval = getIdNum( yytext, num_lines - 1);
	        yylloc.first_line = num_lines;
		return IDENTIFIER;

	}

#\{	{
	yylval = loc_index; 
        yylloc.first_line = num_lines;
	BEGIN(csource);
}

<csource>#\} { /* #{ csource #} */
	BEGIN(INITIAL);

	return CSOURCE;

}
<csource>.	/* ignore */
<csource>\n	/* ignore */

#[a-z][a-zA-Z0-9_* ]+; { /* #int x, the C part */

	yylval = loc_index - strlen( yytext) + 1;
        yylloc.first_line = num_lines;

	return CPART;
}

"##"$	{ /* ## end parsing */
	char c;

	yylval = loc_index - strlen( yytext) + 2;
        yylloc.first_line = num_lines;

	while ((c = input()) != EOF) {
		if (c == EOF) {
			break;	/* found the end */
		}
	}

	return TERMINATE;
}

"{"([^}])+"}" { /* { actions } */

	yylval = loc_index - strlen( yytext) + 1;
        yylloc.first_line = num_lines;

	return ACTION;
}

("gettext_strings"|"GETTEXT_STRINGS")$	{ /* underscore all strings */
	return UNDERSCORE_STRINGS;
}

\"	{ /* "strings" */
	BEGIN(string);
	yylval = loc_index;
        yylloc.first_line = num_lines;
}

<string>\\\"	/* ignore */
<string>\" {
	BEGIN(INITIAL);

	/* yylval is set on the first
	 * bracket detected.
	 */
	return STRING;

}
<string>.	/* ignore */

<string,define>\n  {
         yyerror("unterminated string constant");
}

\%	BEGIN(define);

<define>([^\%]*)+\% { /* %defines% */
	BEGIN(INITIAL);
	yylval = loc_index - strlen(yytext);
        yylloc.first_line = num_lines;

	return STRING;

}


"/*"         BEGIN(comment);
     
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             /* eat up new lines */
<comment>"*"+"/"        BEGIN(INITIAL);

.	return yytext[0];

<<EOF>>		{return 0;}



%%
