/*************************************************************************/
/* stdlib.h  v7.00                                                       */
/* Copyright (c) 1988-1996 Texas Instruments Inc.                        */
/*************************************************************************/
#ifndef _STDLIB
#define _STDLIB

#ifndef NULL
#define NULL 0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef char wchar_t;
#endif
#define MB_CUR_MAX 1

int           atoi(const char *_st);
long          atol(const char *_st);
double        atof(const char *_st);

double        strtod (const char *_st, char **_endptr);
long          strtol (const char *_st, char **_endptr, int _base);
unsigned long strtoul(const char *_st, char **_endptr, int _base);

typedef struct _div_t  { int  quot, rem; } div_t;
typedef struct _ldiv_t { long quot, rem; } ldiv_t;
div_t         div(int _numer, int _denom);
ldiv_t        ldiv(long _numer, long _denom);

#define RAND_MAX 32767
int           rand(void);
void          srand(unsigned _seed);

void         *calloc(size_t _num, size_t _size);
void          free(void *_ptr);
void         *malloc(size_t _size);
void          minit(void);
void         *realloc(void *_ptr, size_t _size);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
void          abort(void);
void          exit(int _status);
int           atexit(void (*_func)(void));

int           abs(int _i);
long          labs(long _l);

void qsort(void *_base,
           size_t _nmemb, 
           size_t _size,
           int (*_compar)(const void *, const void *));

void *bsearch(const void *_key,
	      const void *_abase,
	      size_t     _nmemb,
	      size_t     _size,
	      int (*_compar)(const void *, const void *));

char *getenv(const char *_name);

#endif /* ifndef _STDLIB */
