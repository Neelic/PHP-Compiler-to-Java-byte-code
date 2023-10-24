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
#line 1 "parser.y"

#include <stdio.h>
extern int yylex();
void yyerror(char* str);

#line 77 "parser.tab.c"

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



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_START_CODE_PHP_TAG = 3,         /* START_CODE_PHP_TAG  */
  YYSYMBOL_END_CODE_PHP_TAG = 4,           /* END_CODE_PHP_TAG  */
  YYSYMBOL_HTML = 5,                       /* HTML  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_NUMBER = 7,                     /* NUMBER  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_COM_STRING = 9,                 /* COM_STRING  */
  YYSYMBOL_CONST = 10,                     /* CONST  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_TRY = 12,                       /* TRY  */
  YYSYMBOL_CATCH = 13,                     /* CATCH  */
  YYSYMBOL_FINALLY = 14,                   /* FINALLY  */
  YYSYMBOL_MATCH = 15,                     /* MATCH  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_END_FOR = 17,                   /* END_FOR  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_END_WHILE = 19,                 /* END_WHILE  */
  YYSYMBOL_DO = 20,                        /* DO  */
  YYSYMBOL_FOREACH = 21,                   /* FOREACH  */
  YYSYMBOL_AS = 22,                        /* AS  */
  YYSYMBOL_END_FOREACH = 23,               /* END_FOREACH  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_END_IF = 26,                    /* END_IF  */
  YYSYMBOL_SWITCH = 27,                    /* SWITCH  */
  YYSYMBOL_CASE = 28,                      /* CASE  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_DEFAULT = 30,                   /* DEFAULT  */
  YYSYMBOL_END_SWITCH = 31,                /* END_SWITCH  */
  YYSYMBOL_FUNCTION = 32,                  /* FUNCTION  */
  YYSYMBOL_FN = 33,                        /* FN  */
  YYSYMBOL_USE = 34,                       /* USE  */
  YYSYMBOL_GLOBAL = 35,                    /* GLOBAL  */
  YYSYMBOL_CLASS = 36,                     /* CLASS  */
  YYSYMBOL_ABSTRACT = 37,                  /* ABSTRACT  */
  YYSYMBOL_EXTENDS = 38,                   /* EXTENDS  */
  YYSYMBOL_IMPLEMENTS = 39,                /* IMPLEMENTS  */
  YYSYMBOL_PUBLIC = 40,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 41,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 42,                 /* PROTECTED  */
  YYSYMBOL_FINAL = 43,                     /* FINAL  */
  YYSYMBOL_STATIC = 44,                    /* STATIC  */
  YYSYMBOL_INTERFACE = 45,                 /* INTERFACE  */
  YYSYMBOL_TRAIT = 46,                     /* TRAIT  */
  YYSYMBOL_THROW = 47,                     /* THROW  */
  YYSYMBOL_LOGIC_OR = 48,                  /* LOGIC_OR  */
  YYSYMBOL_LOGIC_XOR = 49,                 /* LOGIC_XOR  */
  YYSYMBOL_LOGIC_AND = 50,                 /* LOGIC_AND  */
  YYSYMBOL_BOOLEAN_OR = 51,                /* BOOLEAN_OR  */
  YYSYMBOL_BOOLEAN_AND = 52,               /* BOOLEAN_AND  */
  YYSYMBOL_EQUAL = 53,                     /* EQUAL  */
  YYSYMBOL_EQUAL_STRICT = 54,              /* EQUAL_STRICT  */
  YYSYMBOL_55_ = 55,                       /* '?'  */
  YYSYMBOL_56_ = 56,                       /* ':'  */
  YYSYMBOL_57_ = 57,                       /* '>'  */
  YYSYMBOL_58_ = 58,                       /* '<'  */
  YYSYMBOL_EQU_MORE = 59,                  /* EQU_MORE  */
  YYSYMBOL_EQU_LESS = 60,                  /* EQU_LESS  */
  YYSYMBOL_61_ = 61,                       /* '|'  */
  YYSYMBOL_62_ = 62,                       /* '&'  */
  YYSYMBOL_63_ = 63,                       /* '^'  */
  YYSYMBOL_64_ = 64,                       /* '='  */
  YYSYMBOL_SHIFT_L = 65,                   /* SHIFT_L  */
  YYSYMBOL_SHIFT_R = 66,                   /* SHIFT_R  */
  YYSYMBOL_67_ = 67,                       /* '-'  */
  YYSYMBOL_68_ = 68,                       /* '+'  */
  YYSYMBOL_69_ = 69,                       /* '.'  */
  YYSYMBOL_70_ = 70,                       /* '/'  */
  YYSYMBOL_71_ = 71,                       /* '*'  */
  YYSYMBOL_72_ = 72,                       /* '%'  */
  YYSYMBOL_U_MINUS = 73,                   /* U_MINUS  */
  YYSYMBOL_U_PLUS = 74,                    /* U_PLUS  */
  YYSYMBOL_75_ = 75,                       /* '!'  */
  YYSYMBOL_76_ = 76,                       /* '~'  */
  YYSYMBOL_77_ = 77,                       /* '['  */
  YYSYMBOL_78_ = 78,                       /* ']'  */
  YYSYMBOL_R_ARROW = 79,                   /* R_ARROW  */
  YYSYMBOL_R_DOUBLE_ARROW = 80,            /* R_DOUBLE_ARROW  */
  YYSYMBOL_QUARTER_DOT = 81,               /* QUARTER_DOT  */
  YYSYMBOL_82_ = 82,                       /* '('  */
  YYSYMBOL_83_ = 83,                       /* ')'  */
  YYSYMBOL_NEW = 84,                       /* NEW  */
  YYSYMBOL_CLONE = 85,                     /* CLONE  */
  YYSYMBOL_86_ = 86,                       /* '$'  */
  YYSYMBOL_87_ = 87,                       /* ','  */
  YYSYMBOL_88_ = 88,                       /* ';'  */
  YYSYMBOL_89_ = 89,                       /* '{'  */
  YYSYMBOL_90_ = 90,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 91,                  /* $accept  */
  YYSYMBOL_start = 92,                     /* start  */
  YYSYMBOL_top_stmt_list = 93,             /* top_stmt_list  */
  YYSYMBOL_top_stmt_list_not_e = 94,       /* top_stmt_list_not_e  */
  YYSYMBOL_top_stmt = 95,                  /* top_stmt  */
  YYSYMBOL_get_value = 96,                 /* get_value  */
  YYSYMBOL_get_value_func = 97,            /* get_value_func  */
  YYSYMBOL_get_value_func_list_not_e = 98, /* get_value_func_list_not_e  */
  YYSYMBOL_if_stmt = 99,                   /* if_stmt  */
  YYSYMBOL_switch_stmt = 100,              /* switch_stmt  */
  YYSYMBOL_case_default_stmt_list = 101,   /* case_default_stmt_list  */
  YYSYMBOL_case_default_stmt = 102,        /* case_default_stmt  */
  YYSYMBOL_case_html_stmt_list = 103,      /* case_html_stmt_list  */
  YYSYMBOL_for_stmt = 104,                 /* for_stmt  */
  YYSYMBOL_foreach_stmt = 105,             /* foreach_stmt  */
  YYSYMBOL_while_stmt = 106,               /* while_stmt  */
  YYSYMBOL_do_while_stmt = 107,            /* do_while_stmt  */
  YYSYMBOL_match_stmt = 108,               /* match_stmt  */
  YYSYMBOL_match_stmt_list = 109,          /* match_stmt_list  */
  YYSYMBOL_match_stmt_list_not_e = 110,    /* match_stmt_list_not_e  */
  YYSYMBOL_match_arm = 111,                /* match_arm  */
  YYSYMBOL_try_stmt = 112,                 /* try_stmt  */
  YYSYMBOL_try_catch_stmt = 113,           /* try_catch_stmt  */
  YYSYMBOL_return_stmt = 114,              /* return_stmt  */
  YYSYMBOL_stmt = 115,                     /* stmt  */
  YYSYMBOL_static_var_list = 116,          /* static_var_list  */
  YYSYMBOL_global_var_list = 117,          /* global_var_list  */
  YYSYMBOL_simple_stmt = 118,              /* simple_stmt  */
  YYSYMBOL_stmt_list = 119,                /* stmt_list  */
  YYSYMBOL_stmt_list_may_empty = 120,      /* stmt_list_may_empty  */
  YYSYMBOL_php_code_section = 121,         /* php_code_section  */
  YYSYMBOL_html_php_stmt_list_not_e = 122, /* html_php_stmt_list_not_e  */
  YYSYMBOL_html_php_stmt_list = 123,       /* html_php_stmt_list  */
  YYSYMBOL_expr = 124,                     /* expr  */
  YYSYMBOL_expr_or_const = 125,            /* expr_or_const  */
  YYSYMBOL_expr_or_const_list_not_e = 126, /* expr_or_const_list_not_e  */
  YYSYMBOL_expr_may_empty = 127,           /* expr_may_empty  */
  YYSYMBOL_var_expr = 128,                 /* var_expr  */
  YYSYMBOL_callable_var = 129,             /* callable_var  */
  YYSYMBOL_id_list = 130,                  /* id_list  */
  YYSYMBOL_expr_list_not_e = 131,          /* expr_list_not_e  */
  YYSYMBOL_expr_list = 132,                /* expr_list  */
  YYSYMBOL_const_decl_expr = 133,          /* const_decl_expr  */
  YYSYMBOL_const_decl_list_not_e = 134,    /* const_decl_list_not_e  */
  YYSYMBOL_new_expr = 135,                 /* new_expr  */
  YYSYMBOL_class_expr_def = 136,           /* class_expr_def  */
  YYSYMBOL_class_stmt_decl = 137,          /* class_stmt_decl  */
  YYSYMBOL_class_stmt_list = 138,          /* class_stmt_list  */
  YYSYMBOL_class_access_mod = 139,         /* class_access_mod  */
  YYSYMBOL_class_expr_visibility = 140,    /* class_expr_visibility  */
  YYSYMBOL_class_stmt_list_not_e = 141,    /* class_stmt_list_not_e  */
  YYSYMBOL_class_stmt = 142,               /* class_stmt  */
  YYSYMBOL_class_expr = 143,               /* class_expr  */
  YYSYMBOL_abstract_class_def = 144,       /* abstract_class_def  */
  YYSYMBOL_abstract_class_stmt_list = 145, /* abstract_class_stmt_list  */
  YYSYMBOL_abstract_class_stmt_list_not_e = 146, /* abstract_class_stmt_list_not_e  */
  YYSYMBOL_abstract_class_expr_visibility = 147, /* abstract_class_expr_visibility  */
  YYSYMBOL_abstract_class_expr = 148,      /* abstract_class_expr  */
  YYSYMBOL_abstract_class_stmt = 149,      /* abstract_class_stmt  */
  YYSYMBOL_interface_expr_def = 150,       /* interface_expr_def  */
  YYSYMBOL_interface_stmt_decl = 151,      /* interface_stmt_decl  */
  YYSYMBOL_interface_stmt_list = 152,      /* interface_stmt_list  */
  YYSYMBOL_interface_stmt_list_not_e = 153, /* interface_stmt_list_not_e  */
  YYSYMBOL_interface_stmt = 154,           /* interface_stmt  */
  YYSYMBOL_trait_expr_def = 155,           /* trait_expr_def  */
  YYSYMBOL_trait_stmt_decl = 156,          /* trait_stmt_decl  */
  YYSYMBOL_function_call_expr = 157,       /* function_call_expr  */
  YYSYMBOL_branches = 158,                 /* branches  */
  YYSYMBOL_function_def = 159,             /* function_def  */
  YYSYMBOL_function_stmt_decl = 160,       /* function_stmt_decl  */
  YYSYMBOL_anon_function_expr = 161,       /* anon_function_expr  */
  YYSYMBOL_expr_func_list = 162,           /* expr_func_list  */
  YYSYMBOL_expr_func_list_not_e = 163,     /* expr_func_list_not_e  */
  YYSYMBOL_anon_function_def = 164,        /* anon_function_def  */
  YYSYMBOL_anon_function_stmt_decl = 165,  /* anon_function_stmt_decl  */
  YYSYMBOL_anon_function_short_def = 166,  /* anon_function_short_def  */
  YYSYMBOL_anon_function_short_stmt_decl = 167 /* anon_function_short_stmt_decl  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  114
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1882

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  259
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  583

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


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
       2,     2,     2,    75,     2,     2,    86,    72,    62,     2,
      82,    83,    71,    68,    87,    67,    69,    70,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    88,
      58,    64,    57,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    77,     2,    78,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,    61,    90,    76,     2,     2,     2,
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
      59,    60,    65,    66,    73,    74,    79,    80,    81,    84,
      85
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    83,    84,    86,    87,    89,    91,    92,
      94,    95,    97,    98,   100,   101,   102,   103,   104,   105,
     107,   108,   109,   110,   111,   113,   114,   116,   117,   118,
     119,   120,   122,   123,   124,   125,   127,   128,   129,   131,
     132,   133,   134,   135,   136,   138,   139,   140,   142,   144,
     146,   147,   149,   150,   152,   153,   154,   156,   158,   159,
     160,   162,   163,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   186,   187,   188,   189,   191,   192,   194,
     196,   197,   199,   200,   202,   204,   205,   206,   207,   209,
     210,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   255,   256,   258,   259,   261,   262,   264,
     265,   266,   267,   268,   270,   271,   272,   273,   275,   276,
     278,   279,   281,   282,   284,   286,   287,   289,   290,   291,
     292,   293,   295,   296,   297,   298,   300,   301,   303,   304,
     306,   307,   308,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   322,   323,   325,   326,   327,   328,
     330,   331,   332,   334,   336,   337,   339,   340,   341,   342,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     355,   356,   357,   358,   360,   361,   362,   364,   365,   367,
     369,   370,   372,   373,   375,   377,   379,   381,   382,   384,
     385,   387,   389,   390,   392,   393,   395,   396,   398,   399,
     400,   401,   403,   404,   405,   406,   408,   410,   411,   413
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
  "\"end of file\"", "error", "\"invalid token\"", "START_CODE_PHP_TAG",
  "END_CODE_PHP_TAG", "HTML", "ID", "NUMBER", "STRING", "COM_STRING",
  "CONST", "RETURN", "TRY", "CATCH", "FINALLY", "MATCH", "FOR", "END_FOR",
  "WHILE", "END_WHILE", "DO", "FOREACH", "AS", "END_FOREACH", "IF", "ELSE",
  "END_IF", "SWITCH", "CASE", "BREAK", "DEFAULT", "END_SWITCH", "FUNCTION",
  "FN", "USE", "GLOBAL", "CLASS", "ABSTRACT", "EXTENDS", "IMPLEMENTS",
  "PUBLIC", "PRIVATE", "PROTECTED", "FINAL", "STATIC", "INTERFACE",
  "TRAIT", "THROW", "LOGIC_OR", "LOGIC_XOR", "LOGIC_AND", "BOOLEAN_OR",
  "BOOLEAN_AND", "EQUAL", "EQUAL_STRICT", "'?'", "':'", "'>'", "'<'",
  "EQU_MORE", "EQU_LESS", "'|'", "'&'", "'^'", "'='", "SHIFT_L", "SHIFT_R",
  "'-'", "'+'", "'.'", "'/'", "'*'", "'%'", "U_MINUS", "U_PLUS", "'!'",
  "'~'", "'['", "']'", "R_ARROW", "R_DOUBLE_ARROW", "QUARTER_DOT", "'('",
  "')'", "NEW", "CLONE", "'$'", "','", "';'", "'{'", "'}'", "$accept",
  "start", "top_stmt_list", "top_stmt_list_not_e", "top_stmt", "get_value",
  "get_value_func", "get_value_func_list_not_e", "if_stmt", "switch_stmt",
  "case_default_stmt_list", "case_default_stmt", "case_html_stmt_list",
  "for_stmt", "foreach_stmt", "while_stmt", "do_while_stmt", "match_stmt",
  "match_stmt_list", "match_stmt_list_not_e", "match_arm", "try_stmt",
  "try_catch_stmt", "return_stmt", "stmt", "static_var_list",
  "global_var_list", "simple_stmt", "stmt_list", "stmt_list_may_empty",
  "php_code_section", "html_php_stmt_list_not_e", "html_php_stmt_list",
  "expr", "expr_or_const", "expr_or_const_list_not_e", "expr_may_empty",
  "var_expr", "callable_var", "id_list", "expr_list_not_e", "expr_list",
  "const_decl_expr", "const_decl_list_not_e", "new_expr", "class_expr_def",
  "class_stmt_decl", "class_stmt_list", "class_access_mod",
  "class_expr_visibility", "class_stmt_list_not_e", "class_stmt",
  "class_expr", "abstract_class_def", "abstract_class_stmt_list",
  "abstract_class_stmt_list_not_e", "abstract_class_expr_visibility",
  "abstract_class_expr", "abstract_class_stmt", "interface_expr_def",
  "interface_stmt_decl", "interface_stmt_list",
  "interface_stmt_list_not_e", "interface_stmt", "trait_expr_def",
  "trait_stmt_decl", "function_call_expr", "branches", "function_def",
  "function_stmt_decl", "anon_function_expr", "expr_func_list",
  "expr_func_list_not_e", "anon_function_def", "anon_function_stmt_decl",
  "anon_function_short_def", "anon_function_short_stmt_decl", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-451)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-222)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1352,   -28,  -451,  -451,  -451,    53,   360,     8,    60,   123,
     132,  1352,   182,   195,   214,    22,   220,   224,    71,   287,
       9,   322,   325,  1398,  1398,  1398,  1398,  1398,  1398,    17,
    1398,  -451,  -451,  1352,   345,  -451,  1352,  -451,     7,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,   338,  -451,  -451,  -451,
    -451,   308,   771,   179,  -451,  -451,   281,  -451,   288,   291,
    -451,   295,  -451,  -451,   299,  -451,   313,   316,  -451,   352,
    -451,  1398,   361,  -451,   232,   365,   362,  -451,  1508,  -451,
    1352,  1398,  1398,  1398,   425,    19,  1398,  1398,   373,   111,
     111,    25,   324,   415,  -451,   380,   382,   465,   372,   445,
    -451,    -5,  1680,  -451,  -451,  -451,  -451,   104,   407,  1398,
      29,  -451,  -451,   297,  -451,  -451,   439,  -451,  1398,   469,
     451,  1398,  1398,  1398,  1398,  1398,  1398,  1398,  1398,  1398,
    1398,  1398,  1398,  1398,  1398,  1398,  1398,  1398,  1398,  1398,
    1398,  1398,  1398,  1398,  -451,   390,  1398,    38,    39,   366,
     529,   397,   529,  1352,  -451,  1352,  1398,   -12,   432,   472,
    1398,    53,  -451,  -451,  1352,   430,   474,    95,   464,  1457,
     476,   -28,   134,  1540,  1567,   111,   470,   553,   555,   477,
     484,   487,   492,  -451,   224,  -451,   571,   573,   111,   111,
     516,   495,  -451,   573,  -451,   -13,  1398,   112,   500,  -451,
    -451,  1398,   501,    -9,   578,  1398,  1704,  1727,  1749,  1770,
    1790,  1810,  1810,  1630,   644,   644,   644,   644,   290,   740,
     433,   268,   268,   215,   215,   215,  -451,  -451,  -451,    19,
     433,     1,   -28,  -451,   -28,  -451,   573,  -451,  -451,  -451,
     306,   427,  -451,   496,   438,    68,   366,  -451,   499,   248,
     334,   257,   190,    28,  -451,   521,   529,   138,   526,  -451,
     583,   534,   397,  -451,   539,   610,   712,  -451,  1398,  -451,
      -3,  -451,  -451,   543,  1398,   846,  1398,    19,   932,    -1,
     550,   629,  -451,   572,   111,   604,   111,  -451,    41,   600,
    -451,   554,   557,   561,  1398,   642,   554,    51,    52,   566,
    -451,  1398,   567,  1398,  -451,    23,   924,  1398,   336,  -451,
     399,   409,   607,   409,   609,  -451,   614,   616,    53,    57,
    -451,   313,  -451,  -451,  -451,   617,   285,   437,   389,   466,
    -451,  -451,  -451,  -451,    53,    61,   565,   574,  -451,   654,
     576,  -451,  -451,  -451,  -451,  -451,   105,  1385,   577,  1352,
    -451,  1594,   336,    92,  1352,   641,   207,    62,  -451,  -451,
    1398,  -451,   585,   663,   477,  -451,   573,   664,   637,  -451,
    1680,   611,   -28,   336,   -28,   336,  -451,   590,  -451,   591,
     587,   673,   924,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
     424,   618,   409,   409,   409,  -451,   409,   636,   638,   428,
     619,  -451,  -451,  -451,   130,   594,   601,  -451,  1680,   164,
    1398,   158,   599,   111,  1016,   154,  1352,   602,  1398,   633,
      33,  -451,   135,  -451,  1680,   111,   626,   554,  -451,   615,
    1398,  -451,  -451,  1352,   625,  -451,  1398,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  1469,  1398,   613,   643,  1385,  1398,
    1398,   634,   256,   646,  -451,   719,  1352,  -451,   256,   649,
    -451,  1352,  1655,  1352,   311,   650,  -451,  -451,  -451,   153,
    1398,   111,  1680,   639,   651,  1680,   180,    -2,  1680,  1398,
    -451,  -451,  1680,  1680,  1100,  1352,  -451,  -451,   386,   723,
    -451,   659,    87,   743,  -451,   660,  1352,   722,   207,  -451,
     416,  -451,  -451,  1680,   184,  -451,  1352,  1680,  1352,  -451,
     748,  -451,  -451,  1352,  1184,   256,   665,  1268,  -451,   725,
     667,   170,   729,   207,  -451,  -451,   672,   205,  -451,   744,
    1352,  -451,   761,  -451,   677,   741,   679,  -451,  -451,   681,
     198,   742,  -451,   256,   683,   684,   181,  1352,  -451,   720,
    -451,  -451,  -451,   687,   774,  -451,  -451,   256,   690,   758,
    1352,  -451,  1352,   779,  -451,   695,   197,   767,  1352,  -451,
     256,   697,   698,   766,   787,  -451,  -451,   703,  1352,  -451,
     769,   704,  -451
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,   144,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,    67,     0,     0,     2,     3,     5,     0,    64,
      65,    72,    73,    70,    71,    80,    60,    79,    82,     7,
      63,   143,     0,   104,   149,   142,     0,    75,     0,     0,
      76,     0,    77,   157,     0,    74,   138,     0,   244,     0,
     245,   163,     0,   165,     0,     0,     0,    62,     0,   138,
      93,     0,   148,     0,     0,     0,     0,     0,     0,   247,
     247,     0,     0,   172,   203,     0,     0,     0,     0,   227,
     235,   143,     0,   134,   135,   136,   137,   143,   168,     0,
       0,   139,    90,     0,     1,     6,   154,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,     0,     0,     0,     0,   179,
     205,   231,   205,     0,   243,     0,     0,   143,   162,     0,
       0,     0,    81,    61,    92,     0,     0,   143,     0,     0,
       0,     0,     0,     0,     0,   247,     0,     0,    12,   248,
       0,   246,     0,    87,     0,    69,     0,     0,   247,   247,
      83,     0,    68,     0,    78,   107,   163,   143,   169,    66,
      91,   163,   238,   143,     0,     0,   122,   123,   124,   120,
     121,   125,   126,     0,   118,   119,   127,   128,   132,   133,
     131,   129,   130,   112,   113,   117,   115,   114,   116,     0,
     105,   143,   150,   151,   152,   153,     0,   180,   182,   181,
       0,     0,   199,     0,   183,     0,   178,   194,     0,     0,
       0,     0,   183,     0,   206,     0,   204,     0,     0,   207,
       0,     0,   230,   232,     0,     0,     0,   259,     0,   237,
     143,   166,    57,     0,   148,     0,     0,     0,     0,     0,
       0,     0,    11,     0,     0,   252,     0,   257,     0,   173,
     158,   174,     0,     0,     0,     0,   228,     0,     0,     0,
     171,   163,     0,   163,   155,     0,   141,     0,   106,   156,
       0,     0,   186,     0,   185,   176,   187,   184,     0,     0,
     197,     0,   195,   196,   219,     0,     0,     0,     0,     0,
     210,   177,   208,   209,     0,     0,     0,     0,   226,     0,
       0,   229,   233,   236,   242,   256,   143,    51,     0,    93,
      45,     0,     0,   149,    93,    14,     0,     0,   241,    10,
       0,    13,     0,    12,   250,    88,     0,     0,   254,   258,
      84,    85,   108,   109,   110,   111,   167,     0,   239,     0,
       0,     0,   140,   198,   190,   191,   189,   188,   193,   192,
       0,   201,     0,     0,     0,   214,     0,     0,   211,     0,
     222,   224,   225,   234,     0,     0,    50,    52,   145,     0,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,     0,    25,   249,     0,     0,   175,   159,     0,
       0,   170,   240,    93,     0,   202,     0,   216,   218,   215,
     217,   213,   212,   223,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,    93,    39,     0,     0,
      15,    93,     0,    93,     0,     0,    21,    26,    12,     0,
       0,     0,    86,     0,     0,   200,   144,   143,    55,     0,
      49,    53,    54,   146,     0,    93,    95,    96,     0,     0,
      46,     0,     0,     0,    16,     0,    93,    29,     0,    33,
       0,    22,   253,   251,     0,    59,    93,    56,    93,    36,
       0,    97,    98,    93,     0,     0,     0,    93,    31,    27,
       0,     0,    25,     0,    35,   255,     0,     0,    94,     0,
      93,    40,     0,    41,     0,     0,     0,    30,    32,     0,
       0,    25,    58,     0,     0,     0,     0,    93,    17,     0,
      28,    23,    34,     0,     0,    37,    47,     0,     0,     0,
      93,    24,    93,     0,    42,     0,     0,     0,    93,    43,
       0,     0,     0,     0,     0,    18,    38,     0,    93,    44,
       0,     0,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -451,  -451,  -451,  -451,   757,   -15,  -268,  -281,  -451,  -451,
    -450,  -337,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
     351,  -451,  -451,  -451,     4,  -451,  -451,  -451,   -21,  -267,
     327,  -451,  -441,   -20,   467,  -451,  -264,   -78,   527,  -187,
    -451,  -162,   652,  -102,  -451,   -18,  -123,  -451,  -120,  -127,
    -451,  -128,  -451,  -451,   666,  -451,  -451,  -451,   560,  -451,
    -451,  -451,  -451,   582,  -451,  -451,  -451,  -451,    -8,     2,
       0,   -81,  -451,  -451,  -451,  -451,  -451
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    34,    35,    36,    37,    38,   178,   179,    39,    40,
     422,   467,   500,    41,    42,    43,    44,    45,   405,   406,
     407,    46,    47,    48,   112,    98,    92,    50,   164,   165,
     487,   488,   489,    51,    52,   409,   168,    53,    54,   291,
     158,   159,    73,    74,    55,    56,    57,   243,   244,   253,
     246,   254,   248,    58,   255,   256,   257,   258,   259,    59,
      60,   261,   262,   263,    61,    62,    63,   202,    64,    65,
      79,   180,   181,    67,    68,    69,    70
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    94,    91,   101,    49,   364,   296,   172,   107,   182,
     348,    66,   113,   116,   110,    84,   361,   493,   363,   420,
     423,   247,   245,   108,   260,   171,   242,   242,    88,   242,
     252,   183,   252,    66,   299,   198,    66,   464,   318,   302,
      49,    95,    96,   120,   232,   234,   120,   365,   521,   310,
     120,   157,   120,   120,    71,   356,   120,   372,   374,    72,
      15,    16,   167,   391,   465,   330,   297,   400,   298,   233,
     235,  -160,    76,   540,   532,  -160,   417,    93,   318,   309,
      66,   304,   411,   194,  -164,  -164,  -220,   415,   357,   197,
     418,   515,   419,   117,   280,    97,   118,    80,   203,   109,
      15,    16,   554,    31,    89,    31,   380,   292,   293,   381,
     516,   117,    76,    66,    31,   117,   563,   200,   322,   245,
     312,   314,   324,   242,    31,    31,   231,   117,   332,   574,
     312,   314,   265,   242,   266,   260,   252,    31,    31,   377,
     270,   379,    81,   117,   469,   455,   451,   117,   334,   417,
     120,   308,   421,    66,    31,    66,   277,   468,   458,   120,
     120,   522,   452,   418,    66,   419,   473,   120,   200,   288,
      15,    16,   413,   176,   538,   414,   157,   453,  -147,   427,
     459,   157,    76,  -147,   417,   557,   541,   195,  -161,   492,
     504,   384,  -161,   386,   495,   300,   497,   177,   418,   352,
     419,   570,   552,   468,   558,    82,   384,   395,   386,   543,
     445,   146,   417,   147,    83,   148,   390,   446,   510,   373,
     375,   417,   544,   571,    31,   466,   418,   329,   419,   519,
     319,    94,   399,   316,   317,   418,   502,   419,   319,   526,
     284,   527,   335,   145,   449,   321,   529,   320,   346,   336,
     535,   450,   340,   321,   167,   320,   146,   337,   147,   485,
     148,   486,    71,   546,    85,    66,    66,   525,  -221,   200,
     200,   284,   437,   438,   439,    66,   440,    86,    66,   350,
     559,   157,   355,   157,    18,   141,   142,   143,   237,   238,
     239,   240,   241,   566,   327,   567,    87,   237,   238,   239,
     328,   573,    90,     1,     2,     3,     4,     5,     6,     7,
      31,   580,     8,     9,   498,    10,   499,    11,    12,   161,
     162,    13,   393,    18,    14,   237,   238,   239,    99,    15,
      16,   100,    17,    18,    19,   138,   139,   140,   141,   142,
     143,    20,    21,    22,    23,   114,   237,   238,   239,    66,
     311,   119,   134,   135,    66,   136,   137,   138,   139,   140,
     141,   142,   143,   120,    24,    25,     1,     2,     3,     4,
     149,   325,    26,    27,   237,   238,   239,   150,   326,    28,
     151,    29,    30,    31,   152,    32,    33,   199,   153,   485,
     167,   511,    75,    16,    95,    96,     1,     2,     3,     4,
     236,   154,    18,    19,    76,   155,   237,   238,   239,   240,
     241,   184,   185,   146,    66,   147,    66,   148,   457,   523,
     460,   524,    75,    16,   477,   160,   396,    24,    25,   237,
     238,   239,   156,    66,    76,    26,    27,   237,   238,   239,
     240,   241,    28,   170,    29,    30,    31,    89,    77,   237,
     238,   239,   229,   186,   187,   175,    66,    24,    25,   191,
     192,    66,   188,    66,   189,    26,    27,   237,   238,   239,
     313,   190,    28,    78,    29,    30,    31,   237,   238,   239,
     394,   316,   317,   193,    66,    66,   367,   383,   509,   196,
     102,   103,   104,   105,   106,   102,    66,   111,   136,   137,
     138,   139,   140,   141,   142,   143,    66,   205,    66,   397,
     398,   161,   435,    66,    66,   161,   443,    66,   531,   268,
     272,   201,   121,   122,   123,   124,   125,   126,   127,   128,
      66,   129,   130,   131,   132,   133,   134,   135,   102,   136,
     137,   138,   139,   140,   141,   142,   143,    66,   166,   102,
     169,   204,   274,   173,   174,   269,   281,   273,   276,   282,
      66,   283,    66,   236,   284,    18,   249,   285,    66,   237,
     238,   239,   250,   251,   286,   287,   102,   289,    66,   290,
     294,   295,   301,   303,   305,   102,   315,   323,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   331,   230,   102,   338,   339,     1,     2,     3,     4,
       5,     6,     7,   267,   341,     8,     9,   102,    10,   343,
      11,    12,   347,   358,    13,   359,   360,    14,   362,   366,
     368,   367,    15,    16,   369,    17,    18,    19,   371,   376,
     378,   385,   387,   401,    20,    21,    22,    23,   388,   389,
      88,   392,   402,   102,   403,   410,   416,   425,   102,   426,
     428,   429,   306,   431,   432,   430,   433,    24,    25,   434,
     441,   442,   436,   444,   447,    26,    27,   454,   448,   463,
     470,   461,    28,   479,    29,    30,    31,   471,    32,    33,
     344,  -222,  -222,  -222,  -222,   133,   134,   135,   474,   136,
     137,   138,   139,   140,   141,   142,   143,   484,     1,     2,
       3,     4,     5,     6,     7,   491,   513,     8,     9,   505,
      10,   480,    11,    12,   490,   102,    13,   494,   501,    14,
     506,   102,   514,   351,    15,    16,   517,    17,    18,    19,
     518,   520,   528,   533,   536,   537,    20,    21,    22,    23,
     539,   370,   542,   545,   547,   548,   549,   550,   102,   551,
     102,   555,   556,   553,   382,   561,   560,   562,   564,    24,
      25,   565,   568,   569,   572,   575,   576,    26,    27,   577,
     578,   579,   582,   115,    28,   581,    29,    30,    31,   481,
      32,    33,   345,   135,   353,   136,   137,   138,   139,   140,
     141,   142,   143,   271,   408,   512,   333,     0,   264,   121,
     122,   123,   124,   125,   126,   127,   128,   424,   129,   130,
     131,   132,   133,   134,   135,     0,   136,   137,   138,   139,
     140,   141,   142,   143,   342,     0,     0,     0,     0,     0,
       0,     0,     1,     2,     3,     4,     5,     6,     7,   144,
       0,     8,     9,     0,    10,     0,    11,    12,     0,     0,
      13,     0,     0,    14,     0,     0,     0,   102,    15,    16,
       0,    17,    18,    19,     0,   462,     0,     0,     0,     0,
      20,    21,    22,    23,     0,     0,     0,   472,     0,     0,
       0,     0,   349,   475,     0,     0,     0,     0,     0,     0,
       0,   102,   478,    24,    25,   408,   482,   483,     0,     0,
       0,    26,    27,     0,     0,     0,     0,     0,    28,     0,
      29,    30,    31,     0,    32,    33,     0,   503,     1,     2,
       3,     4,     5,     6,     7,     0,   507,     8,     9,     0,
      10,     0,    11,    12,     0,     0,    13,     0,     0,    14,
       0,     0,     0,     0,    15,    16,     0,    17,    18,    19,
       0,     0,     0,     0,     0,     0,    20,    21,    22,    23,
       0,   129,   130,   131,   132,   133,   134,   135,   354,   136,
     137,   138,   139,   140,   141,   142,   143,     0,     0,    24,
      25,     0,     0,     0,     0,     0,     0,    26,    27,     0,
       0,     0,     0,     0,    28,     0,    29,    30,    31,     0,
      32,    33,     1,     2,     3,     4,     5,     6,     7,     0,
       0,     8,     9,     0,    10,     0,    11,    12,     0,     0,
      13,     0,     0,    14,     0,     0,     0,     0,    15,    16,
       0,    17,    18,    19,     0,     0,     0,     0,     0,     0,
      20,    21,    22,    23,     0,     0,     0,     0,     0,     0,
       0,     0,   456,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,    25,     0,     0,     0,     0,     0,
       0,    26,    27,     0,     0,     0,     0,     0,    28,     0,
      29,    30,    31,     0,    32,    33,     1,     2,     3,     4,
       5,     6,     7,     0,     0,     8,     9,     0,    10,     0,
      11,    12,     0,     0,    13,     0,     0,    14,     0,     0,
       0,     0,    15,    16,     0,    17,    18,    19,     0,     0,
       0,     0,     0,     0,    20,    21,    22,    23,     0,     0,
       0,     0,     0,     0,     0,     0,   508,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,    25,     0,
       0,     0,     0,     0,     0,    26,    27,     0,     0,     0,
       0,     0,    28,     0,    29,    30,    31,     0,    32,    33,
       1,     2,     3,     4,     5,     6,     7,     0,     0,     8,
       9,     0,    10,     0,    11,    12,     0,     0,    13,     0,
       0,    14,     0,     0,     0,     0,    15,    16,     0,    17,
      18,    19,     0,     0,     0,     0,     0,     0,    20,    21,
      22,    23,     0,     0,     0,     0,     0,     0,     0,     0,
     530,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    24,    25,     0,     0,     0,     0,     0,     0,    26,
      27,     0,     0,     0,     0,     0,    28,     0,    29,    30,
      31,     0,    32,    33,     1,     2,     3,     4,     5,     6,
       7,     0,     0,     8,     9,     0,    10,     0,    11,    12,
       0,     0,    13,     0,   534,    14,     0,     0,     0,     0,
      15,    16,     0,    17,    18,    19,     0,     0,     0,     0,
       0,     0,    20,    21,    22,    23,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,    25,     0,     0,     0,
       0,     0,     0,    26,    27,     0,     0,     0,     0,     0,
      28,     0,    29,    30,    31,     0,    32,    33,     1,     2,
       3,     4,     5,     6,     7,     0,     0,     8,     9,     0,
      10,     0,    11,    12,     0,     0,    13,     0,     0,    14,
       0,     0,     0,     0,    15,    16,     0,    17,    18,    19,
       0,     1,     2,     3,     4,     0,    20,    21,    22,    23,
       0,     0,     0,     0,     1,     2,     3,     4,     0,     0,
       0,     0,     0,     0,     0,   404,     0,    75,    16,    24,
      25,     0,     0,     0,     0,     0,     0,    26,    27,    76,
      75,    16,     0,     0,    28,     0,    29,    30,    31,     0,
      32,    33,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    24,    25,     0,     0,     0,     0,     0,     0,
      26,    27,     0,     0,     0,    24,    25,    28,     0,    29,
      30,    31,     0,    26,    27,   476,     2,     3,     4,     0,
      28,     0,    29,    30,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,    16,     0,     0,   121,   122,   123,   124,   125,
     126,   127,   128,    76,   129,   130,   131,   132,   133,   134,
     135,     0,   136,   137,   138,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,    24,    25,     0,     0,
     275,     0,     0,     0,    26,    27,     0,     0,     0,     0,
       0,    28,     0,    29,    30,    31,   121,   122,   123,   124,
     125,   126,   127,   128,     0,   129,   130,   131,   132,   133,
     134,   135,     0,   136,   137,   138,   139,   140,   141,   142,
     143,     0,     0,     0,     0,     0,     0,     0,   121,   122,
     123,   124,   125,   126,   127,   128,   163,   129,   130,   131,
     132,   133,   134,   135,     0,   136,   137,   138,   139,   140,
     141,   142,   143,     0,     0,   121,   122,   123,   124,   125,
     126,   127,   128,   278,   129,   130,   131,   132,   133,   134,
     135,     0,   136,   137,   138,   139,   140,   141,   142,   143,
       0,     0,   121,   122,   123,   124,   125,   126,   127,   128,
     279,   129,   130,   131,   132,   133,   134,   135,     0,   136,
     137,   138,   139,   140,   141,   142,   143,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   412,   121,   122,
     123,   124,   125,   126,   127,   128,   307,   129,   130,   131,
     132,   133,   134,   135,     0,   136,   137,   138,   139,   140,
     141,   142,   143,   121,   122,   123,   124,   125,   126,   127,
     128,   496,   129,   130,   131,   132,   133,   134,   135,     0,
     136,   137,   138,   139,   140,   141,   142,   143,   121,   122,
     123,   124,   125,   126,   127,   128,     0,   129,   130,   131,
     132,   133,   134,   135,     0,   136,   137,   138,   139,   140,
     141,   142,   143,   122,   123,   124,   125,   126,   127,   128,
       0,   129,   130,   131,   132,   133,   134,   135,     0,   136,
     137,   138,   139,   140,   141,   142,   143,   123,   124,   125,
     126,   127,   128,     0,   129,   130,   131,   132,   133,   134,
     135,     0,   136,   137,   138,   139,   140,   141,   142,   143,
     124,   125,   126,   127,   128,     0,   129,   130,   131,   132,
     133,   134,   135,     0,   136,   137,   138,   139,   140,   141,
     142,   143,   125,   126,   127,   128,     0,   129,   130,   131,
     132,   133,   134,   135,     0,   136,   137,   138,   139,   140,
     141,   142,   143,   126,   127,   128,     0,   129,   130,   131,
     132,   133,   134,   135,     0,   136,   137,   138,   139,   140,
     141,   142,   143,  -222,  -222,   128,     0,   129,   130,   131,
     132,   133,   134,   135,     0,   136,   137,   138,   139,   140,
     141,   142,   143
};

static const yytype_int16 yycheck[] =
{
       0,    19,    17,    23,     0,   286,   193,    85,    28,    90,
     274,    11,    33,     6,    29,    11,   284,   458,   286,   356,
     357,   149,   149,     6,   151,     6,   149,   150,     6,   152,
     150,     6,   152,    33,   196,     6,    36,     4,    10,   201,
      36,    32,    33,    55,     6,     6,    55,     6,   498,   236,
      55,    71,    55,    55,    82,    56,    55,     6,     6,     6,
      32,    33,    82,     6,    31,    37,    79,     6,    81,   147,
     148,    83,    44,   523,   515,    87,    14,     6,    10,    78,
      80,    90,   349,    88,    87,    88,    88,   354,    89,   109,
      28,     4,    30,    86,   175,    86,    89,    89,   118,    82,
      32,    33,   543,    86,    82,    86,    83,   188,   189,    86,
      23,    86,    44,   113,    86,    86,   557,   113,   246,   246,
     240,   241,   249,   246,    86,    86,   146,    86,   256,   570,
     250,   251,   153,   256,   155,   262,   256,    86,    86,   301,
     160,   303,    82,    86,   425,   413,   410,    86,    10,    14,
      55,   229,    90,   153,    86,   155,    22,   425,     4,    55,
      55,   498,     4,    28,   164,    30,   433,    55,   164,   184,
      32,    33,    80,    62,     4,    83,   196,    19,    83,   366,
      26,   201,    44,    88,    14,     4,   523,    83,    83,   456,
     471,   311,    87,   313,   461,    83,   463,    86,    28,   277,
      30,     4,     4,   471,    23,    82,   326,   327,   328,     4,
      80,    77,    14,    79,    82,    81,   318,    87,   485,   297,
     298,    14,    17,    26,    86,    90,    28,    37,    30,   496,
     245,   249,   334,    43,    44,    28,    83,    30,   253,   506,
      87,   508,   257,    64,    80,   245,   513,   245,   268,   257,
     517,    87,   260,   253,   274,   253,    77,   257,    79,     3,
      81,     5,    82,   530,    82,   265,   266,    83,    88,   265,
     266,    87,   392,   393,   394,   275,   396,    82,   278,   275,
     547,   301,   278,   303,    36,    70,    71,    72,    40,    41,
      42,    43,    44,   560,    37,   562,    82,    40,    41,    42,
      43,   568,    82,     6,     7,     8,     9,    10,    11,    12,
      86,   578,    15,    16,     3,    18,     5,    20,    21,    87,
      88,    24,    37,    36,    27,    40,    41,    42,     6,    32,
      33,     6,    35,    36,    37,    67,    68,    69,    70,    71,
      72,    44,    45,    46,    47,     0,    40,    41,    42,   349,
      44,    13,    62,    63,   354,    65,    66,    67,    68,    69,
      70,    71,    72,    55,    67,    68,     6,     7,     8,     9,
      89,    37,    75,    76,    40,    41,    42,    89,    44,    82,
      89,    84,    85,    86,    89,    88,    89,    90,    89,     3,
     410,     5,    32,    33,    32,    33,     6,     7,     8,     9,
      34,    88,    36,    37,    44,    89,    40,    41,    42,    43,
      44,    87,    88,    77,   414,    79,   416,    81,   414,     3,
     416,     5,    32,    33,   444,    64,    37,    67,    68,    40,
      41,    42,    80,   433,    44,    75,    76,    40,    41,    42,
      43,    44,    82,    18,    84,    85,    86,    82,    88,    40,
      41,    42,    62,    38,    39,    82,   456,    67,    68,    87,
      88,   461,    82,   463,    82,    75,    76,    40,    41,    42,
      43,     6,    82,     6,    84,    85,    86,    40,    41,    42,
      43,    43,    44,    38,   484,   485,    87,    88,   484,    82,
      23,    24,    25,    26,    27,    28,   496,    30,    65,    66,
      67,    68,    69,    70,    71,    72,   506,    56,   508,    43,
      44,    87,    88,   513,   514,    87,    88,   517,   514,    87,
      90,    82,    48,    49,    50,    51,    52,    53,    54,    55,
     530,    57,    58,    59,    60,    61,    62,    63,    71,    65,
      66,    67,    68,    69,    70,    71,    72,   547,    81,    82,
      83,    82,    88,    86,    87,    83,    86,    83,    82,     6,
     560,     6,   562,    34,    87,    36,    37,    83,   568,    40,
      41,    42,    43,    44,    87,    83,   109,     6,   578,     6,
      64,    86,    82,    82,     6,   118,    90,    88,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,    90,   145,   146,    88,    32,     6,     7,     8,     9,
      10,    11,    12,   156,    90,    15,    16,   160,    18,    90,
      20,    21,    89,    83,    24,     6,    64,    27,    34,    39,
      83,    87,    32,    33,    83,    35,    36,    37,     6,    83,
      83,    44,    43,    88,    44,    45,    46,    47,    44,    43,
       6,    44,    88,   196,    88,    88,    25,    82,   201,     6,
       6,    34,   205,    83,    83,    64,    89,    67,    68,     6,
      44,    43,    64,    64,    90,    75,    76,    88,    87,    56,
      64,    89,    82,    80,    84,    85,    86,    82,    88,    89,
      90,    57,    58,    59,    60,    61,    62,    63,    83,    65,
      66,    67,    68,    69,    70,    71,    72,    83,     6,     7,
       8,     9,    10,    11,    12,     6,     3,    15,    16,    90,
      18,    88,    20,    21,    88,   268,    24,    88,    88,    27,
      89,   274,    83,   276,    32,    33,     3,    35,    36,    37,
      90,    29,     4,    88,    29,    88,    44,    45,    46,    47,
      31,   294,    90,    19,     3,    88,    25,    88,   301,    88,
     303,    88,    88,    31,   307,    88,    56,     3,    88,    67,
      68,    23,     3,    88,    17,    88,    88,    75,    76,    23,
       3,    88,    88,    36,    82,    26,    84,    85,    86,   448,
      88,    89,    90,    63,   277,    65,    66,    67,    68,    69,
      70,    71,    72,   161,   347,   488,   256,    -1,   152,    48,
      49,    50,    51,    52,    53,    54,    55,   360,    57,    58,
      59,    60,    61,    62,    63,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,   262,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,     9,    10,    11,    12,    88,
      -1,    15,    16,    -1,    18,    -1,    20,    21,    -1,    -1,
      24,    -1,    -1,    27,    -1,    -1,    -1,   410,    32,    33,
      -1,    35,    36,    37,    -1,   418,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    -1,    -1,   430,    -1,    -1,
      -1,    -1,    56,   436,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   444,   445,    67,    68,   448,   449,   450,    -1,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      84,    85,    86,    -1,    88,    89,    -1,   470,     6,     7,
       8,     9,    10,    11,    12,    -1,   479,    15,    16,    -1,
      18,    -1,    20,    21,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    32,    33,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      -1,    57,    58,    59,    60,    61,    62,    63,    56,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    84,    85,    86,    -1,
      88,    89,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    15,    16,    -1,    18,    -1,    20,    21,    -1,    -1,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    32,    33,
      -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      84,    85,    86,    -1,    88,    89,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,    15,    16,    -1,    18,    -1,
      20,    21,    -1,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    32,    33,    -1,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    84,    85,    86,    -1,    88,    89,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    15,
      16,    -1,    18,    -1,    20,    21,    -1,    -1,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    32,    33,    -1,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,    -1,    -1,    -1,    -1,    82,    -1,    84,    85,
      86,    -1,    88,    89,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,    -1,    18,    -1,    20,    21,
      -1,    -1,    24,    -1,    26,    27,    -1,    -1,    -1,    -1,
      32,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    84,    85,    86,    -1,    88,    89,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    15,    16,    -1,
      18,    -1,    20,    21,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    32,    33,    -1,    35,    36,    37,
      -1,     6,     7,     8,     9,    -1,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,     6,     7,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    44,
      32,    33,    -1,    -1,    82,    -1,    84,    85,    86,    -1,
      88,    89,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    -1,    -1,    -1,    67,    68,    82,    -1,    84,
      85,    86,    -1,    75,    76,     6,     7,     8,     9,    -1,
      82,    -1,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    44,    57,    58,    59,    60,    61,    62,
      63,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    -1,    -1,
      83,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    84,    85,    86,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    57,    58,    59,    60,    61,
      62,    63,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    88,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    83,    57,    58,    59,    60,    61,    62,
      63,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      83,    57,    58,    59,    60,    61,    62,    63,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    49,    50,    51,    52,    53,    54,    55,
      -1,    57,    58,    59,    60,    61,    62,    63,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    50,    51,    52,
      53,    54,    55,    -1,    57,    58,    59,    60,    61,    62,
      63,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      51,    52,    53,    54,    55,    -1,    57,    58,    59,    60,
      61,    62,    63,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    52,    53,    54,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    53,    54,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    53,    54,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,     9,    10,    11,    12,    15,    16,
      18,    20,    21,    24,    27,    32,    33,    35,    36,    37,
      44,    45,    46,    47,    67,    68,    75,    76,    82,    84,
      85,    86,    88,    89,    92,    93,    94,    95,    96,    99,
     100,   104,   105,   106,   107,   108,   112,   113,   114,   115,
     118,   124,   125,   128,   129,   135,   136,   137,   144,   150,
     151,   155,   156,   157,   159,   160,   161,   164,   165,   166,
     167,    82,     6,   133,   134,    32,    44,    88,   125,   161,
      89,    82,    82,    82,   115,    82,    82,    82,     6,    82,
      82,    96,   117,     6,   136,    32,    33,    86,   116,     6,
       6,   124,   125,   125,   125,   125,   125,   124,     6,    82,
      96,   125,   115,   119,     0,    95,     6,    86,    89,    13,
      55,    48,    49,    50,    51,    52,    53,    54,    55,    57,
      58,    59,    60,    61,    62,    63,    65,    66,    67,    68,
      69,    70,    71,    72,    88,    64,    77,    79,    81,    89,
      89,    89,    89,    89,    88,    89,    80,   124,   131,   132,
      64,    87,    88,    88,   119,   120,   125,   124,   127,   125,
      18,     6,   128,   125,   125,    82,    62,    86,    97,    98,
     162,   163,   162,     6,    87,    88,    38,    39,    82,    82,
       6,    87,    88,    38,    88,    83,    82,   124,     6,    90,
     115,    82,   158,   124,    82,    56,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,    62,
     125,   124,     6,   128,     6,   128,    34,    40,    41,    42,
      43,    44,   137,   138,   139,   140,   141,   142,   143,    37,
      43,    44,   139,   140,   142,   145,   146,   147,   148,   149,
     140,   152,   153,   154,   145,   119,   119,   125,    87,    83,
     124,   133,    90,    83,    88,    83,    82,    22,    83,    83,
     162,    86,     6,     6,    87,    83,    87,    83,    96,     6,
       6,   130,   162,   162,    64,    86,   130,    79,    81,   132,
      83,    82,   132,    82,    90,     6,   125,    56,   128,    78,
     130,    44,   139,    43,   139,    90,    43,    44,    10,    96,
     160,   161,   142,    88,   140,    37,    44,    37,    43,    37,
      37,    90,   142,   149,    10,    96,   159,   161,    88,    32,
     159,    90,   154,    90,    90,    90,   124,    89,   127,    56,
     115,   125,   128,   129,    56,   115,    56,    89,    83,     6,
      64,    97,    34,    97,    98,     6,    39,    87,    83,    83,
     125,     6,     6,   128,     6,   128,    83,   132,    83,   132,
      83,    86,   125,    88,   139,    44,   139,    43,    44,    43,
     134,     6,    44,    37,    43,   139,    37,    43,    44,   134,
       6,    88,    88,    88,    30,   109,   110,   111,   125,   126,
      88,   120,    83,    80,    83,   120,    25,    14,    28,    30,
     102,    90,   101,   102,   125,    82,     6,   130,     6,    34,
      64,    83,    83,    89,     6,    88,    64,   139,   139,   139,
     139,    44,    43,    88,    64,    80,    87,    90,    87,    80,
      87,   127,     4,    19,    88,    97,    56,   115,     4,    26,
     115,    89,   125,    56,     4,    31,    90,   102,    97,    98,
      64,    82,   125,   120,    83,   125,     6,   124,   125,    80,
      88,   111,   125,   125,    83,     3,     5,   121,   122,   123,
      88,     6,   120,   123,    88,   120,    56,   120,     3,     5,
     103,    88,    83,   125,    98,    90,    89,   125,    56,   115,
     120,     5,   121,     3,    83,     4,    23,     3,    90,   120,
      29,   101,   102,     3,     5,    83,   120,   120,     4,   120,
      56,   115,   123,    88,    26,   120,    29,    88,     4,    31,
     101,   102,    90,     4,    17,    19,   120,     3,    88,    25,
      88,    88,     4,    31,   123,    88,    88,     4,    23,   120,
      56,    88,     3,   123,    88,    23,   120,   120,     3,    88,
       4,    26,    17,   120,   123,    88,    88,    23,     3,    88,
     120,    26,    88
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    93,    93,    94,    94,    95,    96,    96,
      97,    97,    98,    98,    99,    99,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   101,   101,   102,   102,   102,
     102,   102,   103,   103,   103,   103,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   106,   106,   106,   107,   108,
     109,   109,   110,   110,   111,   111,   111,   112,   113,   113,
     113,   114,   114,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   116,   116,   116,   116,   117,   117,   118,
     119,   119,   120,   120,   121,   122,   122,   122,   122,   123,
     123,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   125,   125,   126,   126,   127,   127,   128,
     128,   128,   128,   128,   129,   129,   129,   129,   130,   130,
     131,   131,   132,   132,   133,   134,   134,   135,   135,   135,
     135,   135,   136,   136,   136,   136,   137,   137,   138,   138,
     139,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   141,   141,   142,   142,   142,   142,
     143,   143,   143,   144,   145,   145,   146,   146,   146,   146,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     148,   148,   148,   148,   149,   149,   149,   150,   150,   151,
     152,   152,   153,   153,   154,   155,   156,   157,   157,   158,
     158,   159,   160,   160,   161,   161,   162,   162,   163,   163,
     163,   163,   164,   164,   164,   164,   165,   166,   166,   167
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     0,     1,     2,     1,     1,     2,
       3,     2,     1,     3,     5,     7,     8,    11,    15,    19,
       6,     7,     8,    11,    12,     1,     2,     4,     6,     3,
       5,     4,     3,     1,     4,     2,     9,    12,    16,     7,
      10,    10,    13,    14,    17,     5,     8,    12,     7,     8,
       1,     0,     1,     3,     3,     3,     4,     4,    10,     8,
       1,     3,     2,     1,     1,     1,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     3,     1,     2,     4,     4,     6,     2,     4,     2,
       1,     2,     1,     0,     3,     1,     1,     2,     2,     1,
       0,     1,     1,     1,     1,     3,     4,     3,     5,     5,
       5,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     1,     2,
       5,     4,     1,     1,     1,     1,     3,     1,     0,     1,
       3,     3,     3,     3,     2,     4,     4,     1,     1,     3,
       1,     3,     1,     0,     3,     1,     3,     5,     2,     3,
       6,     4,     2,     4,     4,     6,     4,     4,     1,     0,
       1,     1,     1,     1,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     1,     2,     2,     2,     3,     1,
       5,     3,     4,     2,     1,     0,     1,     1,     2,     2,
       2,     3,     4,     4,     3,     4,     4,     4,     4,     2,
       5,     5,     3,     4,     3,     3,     2,     2,     4,     4,
       1,     0,     1,     2,     3,     2,     4,     4,     3,     3,
       4,     5,     4,     2,     1,     1,     1,     0,     1,     4,
       3,     6,     4,     8,     5,     9,     4,     4,     5,     3
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

#line 1993 "parser.tab.c"

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

#line 415 "parser.y"


void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}
