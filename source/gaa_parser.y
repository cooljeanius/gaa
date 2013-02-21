%{
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

%}

%token IDENTIFIER
%token ACTION
%token TERMINATE
%token CSOURCE
%token CPART
%token TYPE
%token STRING
%token UNDERSCORE_STRINGS

%token INIT "init"
%token DEFITEM "defitem"
%token OPTION "option"
%token REST "rest"
%token HELPNODE "helpnode"
%token OBLIGATORY "obligat"
%token INCOMPATIBLE "incomp"
%token DATA "data"
%token AS "as"
%token OPTIONAL "optional"

%token_table

%%

input:
	source TERMINATE { c_code = $2; }
        | source { c_code = -1; }
	| CSOURCE source { c_code = $1; }
;

source:
	line
        | source line
;
arg:
    	IDENTIFIER
        {
            $$ = $1;
        }
        | '*' IDENTIFIER
        {
            $$ = -$2;
        }
;
arg_list:
        {
        $$ = (int)malloc(sizeof(int));
        ((int*)$$)[0] = 0;
        }
        | arg_real_list
        {
            $$ = $1;
        }
;
arg_real_list:
	OPTIONAL arg_real_list
	{
	        $$ = $2;
                ((int*)$$)[0]++;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 1] = 0;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 2] = -1;
        }
	| arg STRING
    {
        	$$ = (int)malloc((2 * GAAMAX_ARGLIST_COUNT + 1)* sizeof(int));
                ((int*)$$)[0] = 1;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 1] = $1;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 2] = $2;
        }
        | arg STRING arg_real_list
        {
        	$$ = $3;
                ((int*)$$)[0]++;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 1] = $1;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 2] = $2;
        }
        | arg
        {
        	$$ = (int)malloc((2 * GAAMAX_ARGLIST_COUNT + 1)* sizeof(int));
                ((int*)$$)[0] = 1;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 1] = $1;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 2] = -1;
        }
        | arg arg_real_list
        {
        	$$ = $2;
                ((int*)$$)[0]++;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 1] = $1;
                ((int*)$$)[2*(((int*)$$)[0] - 1) + 2] = -1;
        }
;
many_strings:
	STRING {
		$$ = $1;
	}
	| many_strings STRING {
		$$ = $1;
	}
;
line:
        CPART
        {
            NEW(struct_elt, first_struct_elt, struct_elt_tmp);
            struct_elt_tmp->data = 0;
            struct_elt_tmp->location = $1;
            nb_struct_elt++;
        }
        | DATA IDENTIFIER AS arg
        {
            NEW(struct_elt, first_struct_elt, struct_elt_tmp);
            struct_elt_tmp->data = 1;
            struct_elt_tmp->id = $2;
            if($4 < 0)
            {
                struct_elt_tmp->type = GAA_LIST;
                struct_elt_tmp->arg_type = -$4;
            }
            else
            {
                struct_elt_tmp->type = GAA_SINGLE;
                struct_elt_tmp->arg_type = $4;
            }
            nb_struct_elt++;
        }
        | HELPNODE many_strings
        {
            NEW(help, first_help, help_tmp);
            help_tmp->str = $2;
            help_tmp->line = @1.first_line;
            nb_help++;
            
            fprintf(glb_out, "\tprintf(");
            copy_str(glb_fd, $2, glb_out, "\\n");
            fprintf(glb_out, ");\n");
        }
        | INIT ACTION { init_loc = $2; }
	| DEFITEM IDENTIFIER IDENTIFIER CPART
        {
            NEW(atype, first_atype, atype_tmp);
            atype_tmp->id = $2;
            atype_tmp->fnName = $3;
            atype_tmp->argtype = $4;
            nb_atype++;

        }
        | OPTION '(' IDENTIFIER ')' arg_list ACTION many_strings
        {
            int i, *tab, sent=0;
            SUPERLOOKUP(id2, $3, @1.first_line);
            NEW(option, first_option, option_tmp);
            option_tmp->fa = NULL;
            option_tmp->id1 = 0;
            option_tmp->id2 = $3;
            option_tmp->action = $6;
            option_tmp->line = @1.first_line;
            option_tmp->help = $7;
            tab = (int*)$5;
            option_tmp->nb_arg = tab[0];
            nb_option++;

   	    fprintf(glb_out, "\t__gaa_helpsingle(0, \"%s\", ", num2str($3));

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
            copy_str(glb_fd, $7, glb_out, NULL);
            fprintf(glb_out,");\n");
        }
        | OPTION '(' IDENTIFIER ',' IDENTIFIER ')' arg_list ACTION many_strings
        {
            int i, *tab, sent=0;
            SUPERLOOKUP(id2, $5, @1.first_line);
            SUPERLOOKUP(id1, $3, @1.first_line);

            if(strlen(num2str($3)) != 1)
            {
                fprintf( stderr, "%s:%d: first identifier must be a single character\n", st_in, @1.first_line);
                error_flag = 1;
            }
            NEW(option, first_option, option_tmp);
            option_tmp->fa = NULL;
            option_tmp->id1 = $3;
            option_tmp->id2 = $5;
            option_tmp->action = $8;
            option_tmp->line = @1.first_line;
            option_tmp->help = $9;
            tab = (int*)$7;
            option_tmp->nb_arg = tab[0];
            nb_option++;
	    fprintf(glb_out, "\t__gaa_helpsingle('%c', \"%s\", ",
		num2str($3)[0], num2str($5));
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
            copy_str(glb_fd, $9, glb_out, NULL);
            fprintf(glb_out,");\n");
        }
        | REST arg_list ACTION
        {
            int i, *tab;
            
            rest_action = $3;
            tab = (int*)$2;
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
        | OBLIGATORY   IDENTIFIER
        {
            NEW(condition, first_condition, condition_tmp);
            condition_tmp->options = $2;
            condition_tmp->type = GAA_OBLIGAT;
	    k_needed = 1;
        }
        | INCOMPATIBLE IDENTIFIER
        {
            NEW(condition, first_condition, condition_tmp);
            condition_tmp->options = $2;
            condition_tmp->type = GAA_INCOMP;
	    k_needed = 1;
        }
        | UNDERSCORE_STRINGS
        {
	    glb_underscore_strings = 1;
        }
;

%%

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
