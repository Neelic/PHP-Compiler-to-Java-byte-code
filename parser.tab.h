/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    START_CODE_PHP_TAG = 258,      /* START_CODE_PHP_TAG  */
    END_CODE_PHP_TAG = 259,        /* END_CODE_PHP_TAG  */
    HTML = 260,                    /* HTML  */
    ID = 261,                      /* ID  */
    NUMBER = 262,                  /* NUMBER  */
    STRING = 263,                  /* STRING  */
    COM_STRING = 264,              /* COM_STRING  */
    CONST = 265,                   /* CONST  */
    RETURN = 266,                  /* RETURN  */
    TRY = 267,                     /* TRY  */
    CATCH = 268,                   /* CATCH  */
    FINALLY = 269,                 /* FINALLY  */
    MATCH = 270,                   /* MATCH  */
    FOR = 271,                     /* FOR  */
    END_FOR = 272,                 /* END_FOR  */
    WHILE = 273,                   /* WHILE  */
    END_WHILE = 274,               /* END_WHILE  */
    DO = 275,                      /* DO  */
    FOREACH = 276,                 /* FOREACH  */
    AS = 277,                      /* AS  */
    END_FOREACH = 278,             /* END_FOREACH  */
    IF = 279,                      /* IF  */
    ELSE = 280,                    /* ELSE  */
    END_IF = 281,                  /* END_IF  */
    SWITCH = 282,                  /* SWITCH  */
    CASE = 283,                    /* CASE  */
    BREAK = 284,                   /* BREAK  */
    DEFAULT = 285,                 /* DEFAULT  */
    END_SWITCH = 286,              /* END_SWITCH  */
    FUNCTION = 287,                /* FUNCTION  */
    FN = 288,                      /* FN  */
    USE = 289,                     /* USE  */
    GLOBAL = 290,                  /* GLOBAL  */
    CLASS = 291,                   /* CLASS  */
    ABSTRACT = 292,                /* ABSTRACT  */
    EXTENDS = 293,                 /* EXTENDS  */
    IMPLEMENTS = 294,              /* IMPLEMENTS  */
    PUBLIC = 295,                  /* PUBLIC  */
    PRIVATE = 296,                 /* PRIVATE  */
    PROTECTED = 297,               /* PROTECTED  */
    FINAL = 298,                   /* FINAL  */
    STATIC = 299,                  /* STATIC  */
    INTERFACE = 300,               /* INTERFACE  */
    TRAIT = 301,                   /* TRAIT  */
    THROW = 302,                   /* THROW  */
    LOGIC_OR = 303,                /* LOGIC_OR  */
    LOGIC_XOR = 304,               /* LOGIC_XOR  */
    LOGIC_AND = 305,               /* LOGIC_AND  */
    BOOLEAN_OR = 306,              /* BOOLEAN_OR  */
    BOOLEAN_AND = 307,             /* BOOLEAN_AND  */
    EQUAL = 308,                   /* EQUAL  */
    EQUAL_STRICT = 309,            /* EQUAL_STRICT  */
    EQU_MORE = 310,                /* EQU_MORE  */
    EQU_LESS = 311,                /* EQU_LESS  */
    SHIFT_L = 312,                 /* SHIFT_L  */
    SHIFT_R = 313,                 /* SHIFT_R  */
    U_MINUS = 314,                 /* U_MINUS  */
    U_PLUS = 315,                  /* U_PLUS  */
    R_ARROW = 316,                 /* R_ARROW  */
    R_DOUBLE_ARROW = 317,          /* R_DOUBLE_ARROW  */
    QUARTER_DOT = 318,             /* QUARTER_DOT  */
    NEW = 319,                     /* NEW  */
    CLONE = 320                    /* CLONE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
