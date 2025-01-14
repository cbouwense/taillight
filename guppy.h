#ifndef GUPPY_H_
#define GUPPY_H_

// TODO: windows includes
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

// Boolean -------------------------------------------------------------------------------------------------------------
#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
typedef unsigned char bool;

// Primitive types -----------------------------------------------------------------------------------------------------
typedef unsigned char   u8;
typedef signed char     i8;
typedef unsigned short u16;
typedef signed short   i16;
typedef unsigned int   u32;
typedef signed int     i32;
typedef unsigned long  u64;
typedef signed long    i64;
typedef float          f32;
typedef double         f64;

// TODO: flexible array members
typedef struct {
    int   capacity;
    int   count;
    bool *data;
} GupArrayBool;

typedef struct {
    int   capacity;
    int   count;
    char *data;
} GupArrayChar;

typedef GupArrayChar GupString;

typedef struct {
    int     capacity;
    int     count;
    double *data;
} GupArrayDouble;

typedef struct {
    int    capacity;
    int    count;
    float *data;
} GupArrayFloat;

typedef struct {
    int  capacity;
    int  count;
    int *data;
} GupArrayInt;

typedef struct {
    int   capacity;
    int   count;
    long *data;
} GupArrayLong;

typedef struct {
    int capacity;
    int count;
    void **data;
} GupArrayPtr;

typedef struct {
    int    capacity;
    int    count;
    short *data;
} GupArrayShort;

typedef struct {
    int capacity;
    int count;
    GupArrayChar *data;
} GupArrayString;

typedef struct {
    int capacity;
    int count;
    char **data;
} GupArrayCstr;

// Allocators ----------------------------------------------------------------------------------------------------------

typedef enum {
    GUP_ALLOCATOR_TYPE_MALLOC = 0,
    GUP_ALLOCATOR_TYPE_ARENA  = 1,
    GUP_ALLOCATOR_TYPE_COUNT  = 2,
} GupAllocatorType;

typedef struct {
    GupAllocatorType type;
    // TODO: could have stuff here like bytes_allocated, free_count, etc.
} GupAllocator;

typedef struct {
    GupAllocator  head;
    GupArrayPtr  *data;
} GupArena;

// ---------------------------------------------------------------------------------------------------------------------

// TODO: do this with a single byte and bitwise logic
typedef struct {
    bool has_false;
    bool has_true;
} GupSetBool;

typedef struct {
    int capacity;
    int count;
    bool data[256]; // pigeon hole
} GupSetChar;

typedef struct {
    int capacity;
    int count;
    GupArrayDouble *data;
} GupSetDouble;

typedef struct {
    int capacity;
    int count;
    GupArrayFloat *data;
} GupSetFloat;

typedef struct {
    int capacity;
    GupArrayInt *data;
} GupSetInt;

typedef struct {
    int capacity;
    int count;
    GupArrayLong *data;
} GupSetLong;

typedef struct {
    int capacity;
    int count;
    GupArrayPtr *data;
} GupSetPtr;

typedef struct {
    int capacity;
    int count;
    GupArrayShort *data;
} GupSetShort;

typedef struct {
    int capacity;
    int count;
    GupArrayString *data;
} GupSetString;

typedef struct {
    int capacity;
    int count;
    GupArrayCstr *data;
} GupSetCstr;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayBool *values;
} GupHashmapBool;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayChar *values;
} GupHashmapChar;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayDouble *values;
} GupHashmapDouble;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayFloat *values;
} GupHashmapFloat;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayInt *values;
} GupHashmapInt;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayLong *values;
} GupHashmapLong;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayPtr *values;
} GupHashmapPtr;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayShort *values;
} GupHashmapShort;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayString *values;
} GupHashmapString;

typedef struct {
    int capacity;
    GupArrayCstr *keys;
    GupArrayCstr *values;
} GupHashmapCstr;

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

// Allocator -----------------------------------------------------------------------------------------------------------

void *gup_alloc(GupAllocator *a, size_t bytes);
void  gup_free(GupAllocator *a, void *ptr);

// Arena ---------------------------------------------------------------------------------------------------------------
GupArena  gup_arena_create();
void      gup_arena_destroy(GupArena *a); // Free all the allocated memory and the arena itself
void     *gup_arena_alloc(GupArena *a, size_t bytes);
void      gup_arena_free(GupArena *a); // Free all the allocated memory, but not the arena itself

// Dynamic arrays ------------------------------------------------------------------------------------------------------
GupArrayBool   gup_array_bool_create(GupAllocator *a);
void           gup_array_bool_destroy(GupArrayBool xs);
GupArrayBool   gup_array_bool_create_from_array(GupAllocator *a, bool xs[], const int size);
GupArrayBool   gup_array_bool_copy(GupAllocator *a, GupArrayBool xs);
bool           gup_array_bool_equals(GupArrayBool xs, GupArrayBool ys);
bool           gup_array_bool_contains(GupArrayBool xs, bool x);
void           gup_array_bool_print(GupArrayBool xs);
void           gup_array_bool_append(GupAllocator *a, GupArrayBool *xs, bool x);
void           gup_array_bool_prepend(GupAllocator *a, GupArrayBool *xs, bool x);
void           gup_array_bool_remove(GupArrayBool *xs, bool x, int count_to_remove);
void           gup_array_bool_remove_all(GupArrayBool *xs, bool x);
GupArrayBool   gup_array_bool_sort(GupAllocator *a, GupArrayBool xs);
// TODO sort fn, is_sorted, sort_in_place

GupArrayChar   gup_array_char_create(GupAllocator *a);
void           gup_array_char_destroy(GupArrayChar xs);
GupArrayChar   gup_array_char_create_from_array(GupAllocator *a, char xs[], const int size);
GupArrayChar   gup_array_char_create_from_cstr(GupAllocator *a, char xs[]);
GupArrayChar   gup_array_char_copy(GupAllocator *a, GupArrayChar xs);
bool           gup_array_char_equals(GupArrayChar xs, GupArrayChar ys);
bool           gup_array_char_equals_cstr(GupArrayChar xs, const char *cstr);
bool           gup_array_char_contains(GupArrayChar xs, char x);
void           gup_array_char_print(GupArrayChar xs);
void           gup_array_char_append(GupAllocator *a, GupArrayChar *xs, char x);
void           gup_array_char_prepend(GupAllocator *a, GupArrayChar *xs, char x);
void           gup_array_char_remove(GupArrayChar *xs, char x, int count_to_remove);
void           gup_array_char_remove_all(GupArrayChar *xs, char x);
char          *gup_array_char_to_cstr(GupAllocator *a, GupArrayChar chars);
char         **gup_array_string_to_cstrs(GupAllocator *a, GupArrayString strs);
GupArrayChar   gup_array_char_sort(GupAllocator *a, GupArrayChar xs);
   
GupArrayDouble gup_array_double_create(GupAllocator *a);
void           gup_array_double_destroy(GupArrayDouble xs);
GupArrayDouble gup_array_double_create_from_array(GupAllocator *a, double xs[], const int size);
GupArrayDouble gup_array_double_copy(GupAllocator *a, GupArrayDouble xs);
bool           gup_array_double_equals(GupArrayDouble xs, GupArrayDouble ys);
bool           gup_array_double_contains(GupArrayDouble xs, double x);
void           gup_array_double_print(GupArrayDouble xs);
void           gup_array_double_append(GupAllocator *a, GupArrayDouble *xs, double x);
void           gup_array_double_prepend(GupAllocator *a, GupArrayDouble *xs, double x);
void           gup_array_double_remove(GupArrayDouble *xs, double x, int count_to_remove);
void           gup_array_double_remove_all(GupArrayDouble *xs, double x);
GupArrayDouble gup_array_double_sort(GupAllocator *a, GupArrayDouble xs);

GupArrayFloat  gup_array_float_create(GupAllocator *a);
void           gup_array_float_destroy(GupArrayFloat xs);
GupArrayFloat  gup_array_float_create_from_array(GupAllocator *a, float xs[], const int size);
GupArrayFloat  gup_array_float_copy(GupAllocator *a, GupArrayFloat xs);
bool           gup_array_float_equals(GupArrayFloat xs, GupArrayFloat ys);
bool           gup_array_float_contains(GupArrayFloat xs, float x);
void           gup_array_float_print(GupArrayFloat xs);
void           gup_array_float_append(GupAllocator *a, GupArrayFloat *xs, float x);
void           gup_array_float_prepend(GupAllocator *a, GupArrayFloat *xs, float x);
void           gup_array_float_remove(GupArrayFloat *xs, float x, int count_to_remove);
void           gup_array_float_remove_all(GupArrayFloat *xs, float x);
GupArrayFloat  gup_array_float_sort(GupAllocator *a, GupArrayFloat xs);

// TODO: gup_array_int_create_size();
GupArrayInt    gup_array_int_create(GupAllocator *a);
void           gup_array_int_destroy(GupArrayInt xs);
GupArrayInt    gup_array_int_create_from_array(GupAllocator *a, int xs[], const int size);
GupArrayInt    gup_array_int_copy(GupAllocator *a, GupArrayInt xs);
bool           gup_array_int_equals(GupArrayInt xs, GupArrayInt ys);
bool           gup_array_int_contains(GupArrayInt xs, int x);
void           gup_array_int_print(GupArrayInt xs);
void           gup_array_int_debug(GupArrayInt xs);
void           gup_array_int_append(GupAllocator *a, GupArrayInt *xs, int x);
void           gup_array_int_prepend(GupAllocator *a, GupArrayInt *xs, int x);
void           gup_array_int_remove(GupArrayInt *xs, int x, int count_to_remove);
void           gup_array_int_remove_all(GupArrayInt *xs, int x);
GupArrayInt    gup_array_int_sort(GupAllocator *a, GupArrayInt xs);

GupArrayLong   gup_array_long_create(GupAllocator *a);
void           gup_array_short_destroy(GupArrayShort xs);
GupArrayLong   gup_array_long_create_from_array(GupAllocator *a, long xs[], const int size);
GupArrayLong   gup_array_long_copy(GupAllocator *a, GupArrayLong xs);
bool           gup_array_long_equals(GupArrayLong xs, GupArrayLong ys);
bool           gup_array_long_contains(GupArrayLong xs, long x);
void           gup_array_long_print(GupArrayLong xs);
void           gup_array_long_append(GupAllocator *a, GupArrayLong *xs, long x);
void           gup_array_long_prepend(GupAllocator *a, GupArrayLong *xs, long x);
void           gup_array_long_remove(GupArrayLong *xs, long x, int count_to_remove);
void           gup_array_long_remove_all(GupArrayLong *xs, long x);
GupArrayLong   gup_array_long_sort(GupAllocator *a, GupArrayLong xs);

GupArrayPtr    gup_array_ptr_create(GupAllocator *a);
void           gup_array_ptr_destroy(GupArrayPtr xs);
GupArrayPtr    gup_array_ptr_create_from_array(GupAllocator *a, void* xs[], const int size);
GupArrayPtr    gup_array_ptr_copy(GupAllocator *a, GupArrayPtr xs);
void           gup_array_ptr_print(GupArrayPtr xs);
void           gup_array_ptr_append(GupAllocator *a, GupArrayPtr *xs, void* x);
void           gup_array_ptr_prepend(GupAllocator *a, GupArrayPtr *xs, void* x);

GupArrayShort  gup_array_short_create(GupAllocator *a);
void           gup_array_short_destroy(GupArrayShort xs);
GupArrayShort  gup_array_short_create_from_array(GupAllocator *a, short xs[], const int size);
GupArrayShort  gup_array_short_copy(GupAllocator *a, GupArrayShort xs);
bool           gup_array_short_equals(GupArrayShort xs, GupArrayShort ys);
bool           gup_array_short_contains(GupArrayShort xs, short x);
void           gup_array_short_print(GupArrayShort xs);
void           gup_array_short_append(GupAllocator *a, GupArrayShort *xs, short x);
void           gup_array_short_prepend(GupAllocator *a, GupArrayShort *xs, short x);
void           gup_array_short_remove(GupArrayShort *xs, short x, int count_to_remove);
void           gup_array_short_remove_all(GupArrayShort *xs, short x);
GupArrayShort  gup_array_short_sort(GupAllocator *a, GupArrayShort xs);

GupArrayString gup_array_string_create(GupAllocator *a);
void           gup_array_string_destroy(GupArrayString xs);
GupArrayString gup_array_string_create_from_array(GupAllocator *a, GupString xs[], const int size);
GupArrayString gup_array_string_create_from_cstrs(GupAllocator *a, char **cstrs, const int size);
GupArrayString gup_array_string_copy(GupAllocator *a, GupArrayString xs);
bool           gup_array_string_equals(GupArrayString xs, GupArrayString ys);
bool           gup_array_string_contains(GupArrayString xs, GupString x);
void           gup_array_string_print(GupArrayString xs);
void           gup_array_string_append(GupAllocator *a, GupArrayString *xs, GupString x);
void           gup_array_string_append_cstr(GupAllocator *a, GupArrayString *xs, char cstr[]);
void           gup_array_string_prepend(GupAllocator *a, GupArrayString *xs, GupString x);
void           gup_array_string_prepend_cstr(GupAllocator *a, GupArrayString *xs, char cstr[]);
void           gup_array_string_remove(GupArrayString *xs, GupArrayChar x, int count_to_remove);
void           gup_array_string_remove_all(GupArrayString *xs, GupString x);
void           gup_array_string_remove_all_cstr(GupAllocator *a, GupArrayString *xs, char *x);
GupArrayString gup_array_string_sort(GupAllocator *a, GupArrayString xs);

GupArrayCstr   gup_array_cstr_create(GupAllocator *a);
void           gup_array_cstr_destroy(GupArrayCstr xs);
GupArrayCstr   gup_array_cstr_create_from_array(GupAllocator *a, char *xs[], const int size);
GupArrayCstr   gup_array_cstr_copy(GupAllocator *a, GupArrayCstr xs);
bool           gup_array_cstr_equals(GupArrayCstr xs, GupArrayCstr ys);
bool           gup_array_cstr_contains(GupArrayCstr xs, char *x);
void           gup_array_cstr_print(GupArrayCstr xs);
void           gup_array_cstr_append(GupAllocator *a, GupArrayCstr *xs, char *x);
void           gup_array_cstr_prepend(GupAllocator *a, GupArrayCstr *xs, char *x);
void           gup_array_cstr_remove(GupArrayCstr *xs, char *x, int count_to_remove);
void           gup_array_cstr_remove_all(GupArrayCstr *xs, char *x);
GupArrayCstr   gup_array_cstr_sort(GupAllocator *a, GupArrayCstr xs);

// File operations ---------------------------------------------------------------------------------
bool           gup_file_create(const char *file_path);
bool           gup_file_delete(const char *file_path);
bool           gup_file_exists(const char *file_path);
bool           gup_file_is_empty(const char *file_path);
int            gup_file_line_count(const char *file_path);
void           gup_file_print(GupAllocator *a, const char *file_path);
void           gup_file_print_lines(GupAllocator *a, const char *file_path);
bool           gup_file_read(GupAllocator *a, const char *file_path, GupString *out);
bool           gup_file_read_as_cstr(GupAllocator *a, const char *file_path, char **out);
GupArrayString gup_file_read_lines(GupAllocator *a, const char *file_path);
bool           gup_file_read_lines_as_cstrs(GupAllocator *a, const char *file_path, char ***out);
bool           gup_file_read_lines_keep_newlines(GupAllocator *a, const char *file_path, GupArrayString *out);
bool           gup_file_read_lines_as_cstrs_keep_newlines(GupAllocator *a, const char *file_path, char ***out);
bool           gup_file_size(const char *file_path, long *out);
int            gup_file_watch(const char *file_path, void (*fn)(void));
int            gup_file_watch_cli_command(const char *file_path, const char *cli_command);
bool           gup_file_write(GupAllocator *a, GupString text_to_write, const char *file_path);
bool           gup_file_write_cstr(const char *text_to_write, const char *file_path);
bool           gup_file_write_lines(GupAllocator *a, GupArrayString lines_to_write, const char *file_path);
bool           gup_file_write_lines_cstrs(char **lines_to_write, const int line_count, const char *file_path);
void           gup_file_append_line(GupAllocator *a, GupString line_to_write, const char *file_path);
void           gup_file_append_line_cstr(const char *line_to_write, const char *file_path);
void           gup_file_append_lines(GupAllocator *a, GupArrayString lines_to_write, const char *file_path);
void           gup_file_append_lines_cstrs(char **lines_to_write, const int line_count, const char *file_path);

// Sets --------------------------------------------------------------------------------------------
GupSetBool   gup_set_bool_create();
GupSetBool   gup_set_bool_create_size(int size);
GupSetBool   gup_set_bool_create_from_array(bool xs[], const int size);
void         gup_set_bool_destroy(GupSetBool set);
bool         gup_set_bool_has(GupSetBool set, bool x);
void         gup_set_bool_add(GupSetBool *set, bool x);
void         gup_set_bool_remove(GupSetBool *set, bool x);
int          gup_set_bool_size(GupSetBool set);
void         gup_set_bool_print(GupSetBool set);
void         gup_set_bool_debug(GupSetBool set);

GupSetChar   gup_set_char_create();
GupSetChar   gup_set_char_create_from_array(char xs[], const int size);
bool         gup_set_char_has(GupSetChar set, char x);
void         gup_set_char_add(GupSetChar *set, char x);
void         gup_set_char_remove(GupSetChar *set, char x);
int          gup_set_char_size(GupSetChar set);
void         gup_set_char_print(GupSetChar set);
void         gup_set_char_debug(GupSetChar set);

GupSetDouble gup_set_double_create(GupAllocator *a);
GupSetDouble gup_set_double_create_size(GupAllocator *a, int size);
GupSetDouble gup_set_double_create_from_array(GupAllocator *a, double xs[], const int size);
void         gup_set_double_destroy(GupSetDouble set);
bool         gup_set_double_has(GupSetDouble set, double x);
void         gup_set_double_add(GupAllocator *a, GupSetDouble *set, double x);
void         gup_set_double_remove(GupSetDouble *set, double x);
int          gup_set_double_size(GupSetDouble set);
void         gup_set_double_print(GupSetDouble set);
void         gup_set_double_debug(GupSetDouble set);

GupSetFloat  gup_set_float_create(GupAllocator *a);
GupSetFloat  gup_set_float_create_size(GupAllocator *a, int size);
GupSetFloat  gup_set_float_create_from_array(GupAllocator *a, float xs[], const int size);
void         gup_set_float_destroy(GupSetFloat set);
bool         gup_set_float_has(GupSetFloat set, float x);
void         gup_set_float_add(GupAllocator *a, GupSetFloat *set, float x);
void         gup_set_float_remove(GupSetFloat *set, float x);
int          gup_set_float_size(GupSetFloat set);
void         gup_set_float_print(GupSetFloat set);
void         gup_set_float_debug(GupSetFloat set);

GupSetInt    gup_set_int_create(GupAllocator *a);
GupSetInt    gup_set_int_create_size(GupAllocator *a, int capacity);
GupSetInt    gup_set_int_create_from_array(GupAllocator *a, int xs[], const int size);
void         gup_set_int_destroy(GupSetInt set);
bool         gup_set_int_has(GupSetInt set, int x);
void         gup_set_int_add(GupAllocator *a, GupSetInt *set, int x);
void         gup_set_int_remove(GupSetInt *set, int x);
int          gup_set_int_size(GupSetInt set);
void         gup_set_int_print(GupSetInt set);
void         gup_set_int_debug(GupSetInt set);

GupSetLong   gup_set_long_create(GupAllocator *a);
GupSetLong   gup_set_long_create_size(GupAllocator *a, int size);
GupSetLong   gup_set_long_create_from_array(GupAllocator *a, long xs[], const int size);
void         gup_set_long_destroy(GupSetLong set);
bool         gup_set_long_has(GupSetLong set, long x);
void         gup_set_long_add(GupAllocator *a, GupSetLong *set, long x);
void         gup_set_long_remove(GupSetLong *set, long x);
int          gup_set_long_size(GupSetLong set);
void         gup_set_long_print(GupSetLong set);
void         gup_set_long_debug(GupSetLong set);

GupSetPtr    gup_set_ptr_create(GupAllocator *a);
GupSetPtr    gup_set_ptr_create_size(GupAllocator *a, int size);
GupSetPtr    gup_set_ptr_create_from_array(GupAllocator *a, void* xs[], const int size);
void         gup_set_ptr_destroy(GupSetPtr set);
bool         gup_set_ptr_has(GupSetPtr set, void* x);
void         gup_set_ptr_add(GupAllocator *a, GupSetPtr *set, void* x);
void         gup_set_ptr_remove(GupSetPtr *set, void* x);
int          gup_set_ptr_size(GupSetPtr set);
void         gup_set_ptr_print(GupSetPtr set);
void         gup_set_ptr_debug(GupSetPtr set);

GupSetShort  gup_set_short_create(GupAllocator *a);
GupSetShort  gup_set_short_create_size(GupAllocator *a, int size);
GupSetShort  gup_set_short_create_from_array(GupAllocator *a, short xs[], const int size);
void         gup_set_short_destroy(GupSetShort set);
bool         gup_set_short_has(GupSetShort set, short x);
void         gup_set_short_add(GupAllocator *a, GupSetShort *set, short x);
void         gup_set_short_remove(GupSetShort *set, short x);
int          gup_set_short_size(GupSetShort set);
void         gup_set_short_print(GupSetShort set);
void         gup_set_short_debug(GupSetShort set);

GupSetString gup_set_string_create(GupAllocator *a);
GupSetString gup_set_string_create_size(GupAllocator *a, int size);
GupSetString gup_set_string_create_from_array(GupAllocator *a, GupString xs[], const int size);
void         gup_set_string_destroy(GupSetString set);
bool         gup_set_string_has(GupSetString set, GupString x);
void         gup_set_string_add(GupAllocator *a, GupSetString *set, GupString x);
void         gup_set_string_remove(GupSetString *set, GupString x);
int          gup_set_string_size(GupSetString set);
void         gup_set_string_print(GupSetString set);
void         gup_set_string_debug(GupSetString set);

// TODO: GupSetCstr?

// Hashmap
GupHashmapBool   gup_hashmap_bool_create(GupAllocator *a);
void             gup_hashmap_bool_destroy(GupHashmapBool hashmap);
bool             gup_hashmap_bool_get(GupHashmapBool hashmap, char *key, bool *out);
void             gup_hashmap_bool_set(GupAllocator *a, GupHashmapBool *hashmap, char *key, bool value);
void             gup_hashmap_bool_remove(GupHashmapBool *hashmap, char *key);
int              gup_hashmap_bool_size(GupHashmapBool hashmap);
void             gup_hashmap_bool_print(GupHashmapBool hashmap);
void             gup_hashmap_bool_debug(GupHashmapBool hashmap);

GupHashmapChar   gup_hashmap_char_create(GupAllocator *a);
void             gup_hashmap_char_destroy(GupHashmapChar hashmap);
bool             gup_hashmap_char_get(GupHashmapChar hashmap, char *key, char *out);
void             gup_hashmap_char_set(GupAllocator *a, GupHashmapChar *hashmap, char *key, char value);
void             gup_hashmap_char_remove(GupHashmapChar *hashmap, char *key);
int              gup_hashmap_char_size(GupHashmapChar hashmap);
void             gup_hashmap_char_print(GupHashmapChar hashmap);
void             gup_hashmap_char_debug(GupHashmapChar hashmap);

GupHashmapDouble gup_hashmap_double_create(GupAllocator *a);
void             gup_hashmap_double_destroy(GupHashmapDouble hashmap);
bool             gup_hashmap_double_get(GupHashmapDouble hashmap, char *key, double *out);
void             gup_hashmap_double_set(GupAllocator *a, GupHashmapDouble *hashmap, char *key, double value);
void             gup_hashmap_double_remove(GupHashmapDouble *hashmap, char *key);
int              gup_hashmap_double_size(GupHashmapDouble hashmap);
void             gup_hashmap_double_print(GupHashmapDouble hashmap);
void             gup_hashmap_double_debug(GupHashmapDouble hashmap);

GupHashmapFloat  gup_hashmap_float_create(GupAllocator *a);
void             gup_hashmap_float_destroy(GupHashmapFloat hashmap);
bool             gup_hashmap_float_get(GupHashmapFloat hashmap, char *key, float *out);
void             gup_hashmap_float_set(GupAllocator *a, GupHashmapFloat *hashmap, char *key, float value);
void             gup_hashmap_float_remove(GupHashmapFloat *hashmap, char *key);
int              gup_hashmap_float_size(GupHashmapFloat hashmap);
void             gup_hashmap_float_print(GupHashmapFloat hashmap);
void             gup_hashmap_float_debug(GupHashmapFloat hashmap);

GupHashmapInt    gup_hashmap_int_create(GupAllocator *a);
void             gup_hashmap_int_destroy(GupHashmapInt hashmap);
bool             gup_hashmap_int_get(GupHashmapInt hashmap, char *key, int *out);
void             gup_hashmap_int_set(GupAllocator *a, GupHashmapInt *hashmap, char *key, int value);
void             gup_hashmap_int_remove(GupHashmapInt *hashmap, char *key);
int              gup_hashmap_int_size(GupHashmapInt hashmap);
void             gup_hashmap_int_print(GupHashmapInt hashmap);
void             gup_hashmap_int_debug(GupHashmapInt hashmap);

GupHashmapLong   gup_hashmap_long_create(GupAllocator *a);
void             gup_hashmap_long_destroy(GupHashmapLong hashmap);
bool             gup_hashmap_long_get(GupHashmapLong hashmap, char *key, long *out);
void             gup_hashmap_long_set(GupAllocator *a, GupHashmapLong *hashmap, char *key, long value);
void             gup_hashmap_long_remove(GupHashmapLong *hashmap, char *key);
int              gup_hashmap_long_size(GupHashmapLong hashmap);
void             gup_hashmap_long_print(GupHashmapLong hashmap);
void             gup_hashmap_long_debug(GupHashmapLong hashmap);

GupHashmapPtr    gup_hashmap_ptr_create(GupAllocator *a);
void             gup_hashmap_ptr_destroy(GupHashmapPtr hashmap);
bool             gup_hashmap_ptr_get(GupHashmapPtr hashmap, char *key, void* *out);
void             gup_hashmap_ptr_set(GupAllocator *a, GupHashmapPtr *hashmap, char *key, void* value);
int              gup_hashmap_ptr_size(GupHashmapPtr hashmap);
void             gup_hashmap_ptr_print(GupHashmapPtr hashmap);
void             gup_hashmap_ptr_debug(GupHashmapPtr hashmap);

GupHashmapShort  gup_hashmap_short_create(GupAllocator *a);
void             gup_hashmap_short_destroy(GupHashmapShort hashmap);
bool             gup_hashmap_short_get(GupHashmapShort hashmap, char *key, short *out);
void             gup_hashmap_short_set(GupAllocator *a, GupHashmapShort *hashmap, char *key, short value);
void             gup_hashmap_short_remove(GupHashmapShort *hashmap, char *key);
int              gup_hashmap_short_size(GupHashmapShort hashmap);
void             gup_hashmap_short_print(GupHashmapShort hashmap);
void             gup_hashmap_short_debug(GupHashmapShort hashmap);

GupHashmapString gup_hashmap_string_create(GupAllocator *a);
void             gup_hashmap_string_destroy(GupHashmapString hashmap);
bool             gup_hashmap_string_get(GupHashmapString hashmap, char *key, GupString *out);
void             gup_hashmap_string_set(GupAllocator *a, GupHashmapString *hashmap, char *key, GupString value);
void             gup_hashmap_string_remove(GupHashmapString *hashmap, char *key);
int              gup_hashmap_string_size(GupHashmapString hashmap);
void             gup_hashmap_string_print(GupHashmapString hashmap);
void             gup_hashmap_string_debug(GupHashmapString hashmap);

GupHashmapCstr   gup_hashmap_cstr_create(GupAllocator *a);
void             gup_hashmap_cstr_destroy(GupHashmapCstr hashmap);
bool             gup_hashmap_cstr_get(GupHashmapCstr hashmap, char *key, char * *out);
void             gup_hashmap_cstr_set(GupAllocator *a, GupHashmapCstr *hashmap, char *key, char * value);
void             gup_hashmap_cstr_remove(GupHashmapCstr *hashmap, char *key);
int              gup_hashmap_cstr_size(GupHashmapCstr hashmap);
void             gup_hashmap_cstr_print(GupHashmapCstr hashmap);
void             gup_hashmap_cstr_debug(GupHashmapCstr hashmap);

// Print -------------------------------------------------------------------------------------------
void gup_print_cwd(void);
void gup_print_string(const char *string);

// Print array slices [start, end) -----------------------------------------------------------------
void gup_print_array_slice_bool(bool array[], size_t start, size_t end);
void gup_print_array_slice_char(char array[], size_t start, size_t end);
void gup_print_array_slice_double(double array[], size_t start, size_t end);
void gup_print_array_slice_float(float array[], size_t start, size_t end);
void gup_print_array_slice_int(int array[], size_t start, size_t end);
void gup_print_array_slice_long(long array[], size_t start, size_t end);

// Settings ----------------------------------------------------------------------------------------
bool gup_settings_get_cstr(GupAllocator *a, const char *key, GupString *out);
bool gup_settings_get_cstr_from_file(GupAllocator *a, const char *key, const char *file_path, GupString *out);
bool gup_settings_set(const char *key, const char *value);
bool gup_settings_set_to_file(const char *key, const char *value, const char *file_path);

// Strings -------------------------------------------------------------------------------------
GupString       gup_string_create();
GupString       gup_string_create(GupAllocator *a);
void            gup_string_destroy(GupString str);
GupString       gup_string_create_from_cstr(GupAllocator *a, char str[]); // Aliased as "gup_string"
GupString       gup_string_copy(GupAllocator *a, GupString str);
bool            gup_string_equals(GupString str_a, GupString str_b);
bool            gup_string_equals_cstr(GupString str, const char *cstr, int cstr_length);
int             gup_string_compare(GupAllocator *a, GupString x, GupString y); // Returns negative if x < y, 0 if x == y, positive if x > y (think strcmp).
bool            gup_string_contains(GupString str, char c);
bool            gup_string_contains_substring(GupString str, GupString sub_str); // TODO: contains cstr
void            gup_string_print(GupString str);
void            gup_string_debug(GupString str);
void            gup_string_append(GupAllocator *a, GupString *str, char c);
void            gup_string_append_str(GupAllocator *a, GupString *str, GupString str_to_append);
void            gup_string_append_cstr(GupAllocator *a, GupString *str, const char *cstr_to_append);
void            gup_string_prepend(GupAllocator *a, GupString *str, char c);
GupString       gup_string_map(GupAllocator *a, GupString str, char (*fn)(char));
void            gup_string_map_in_place(GupString str, char (*fn)(char));
GupString       gup_string_filter(GupAllocator *a, GupString str, bool (*fn)(char));
void            gup_string_filter_in_place(GupString *str, bool (*fn)(char));
char            gup_string_reduce(GupString str, char (*fn)(char, char), char start);
bool            gup_string_find(GupAllocator *a, GupString str, bool (*fn)(char), char *out);
GupString       gup_string_trim_char(GupAllocator *a, GupString str, char c);
void            gup_string_trim_char_in_place(GupString *str, char c);
GupString       gup_string_trim_fn(GupAllocator *a, GupString str, bool (*fn)(char));
void            gup_string_trim_fn_in_place(GupString *str, bool (*fn)(char));
GupString       gup_string_without_whitespace(GupString str);
void            gup_string_without_whitespace_in_place(GupString *str);
bool            gup_string_starts_with(GupString str, GupString sub_str);
bool            gup_string_starts_with_cstr(GupString str, const char* cstr);
bool            gup_string_ends_with(GupString str, GupString sub_str);
bool            gup_string_ends_with_cstr(GupString str, const char* cstr);
bool            gup_string_to_int(GupString str, int *out);
char           *gup_string_to_cstr(GupAllocator *a, GupString str);
GupArrayString  gup_string_split(GupAllocator *a, GupString str, char c);
GupArrayString  gup_string_split_by_cstr(GupAllocator *a, GupString str, char *sub_str);

// Assert

#define gup_assert(pass_condition) _gup_assert(pass_condition, #pass_condition, __FILE__, __LINE__)
#define gup_assert_verbose(pass_condition, failure_explanation) _gup_assert_verbose(pass_condition, failure_explanation, #pass_condition, __FILE__, __LINE__)

// C-string utilities
char *gup_cstr_array_flatten(GupAllocator *a, char **strs); // Assumes a null terminated string.
int   gup_cstr_length_excluding_null(const char* cstr); // Assumes a null terminated string. Excludes the null from the length.
int   gup_cstr_length_including_null(const char* cstr); // Assumes a null terminated string. Excludes the null from the length.
bool  gup_cstr_equals(const char *a, const char* b);
void  gup_cstr_copy(char *to, const char *from);
void  gup_cstr_copy_n(char *to, const char *from, int n);
void  gup_cstr_print(const char *cstr);

// Math
u8  gup_pow_u8(u8 x, u8 y);
i8  gup_pow_i8(i8 x, i8 y);
u16 gup_pow_u16(u16 x, u16 y);
i16 gup_pow_i16(i16 x, i16 y);
u32 gup_pow_u32(u32 x, u32 y);
i32 gup_pow_i32(i32 x, i32 y);
u64 gup_pow_u64(u64 x, u64 y);
i64 gup_pow_i64(i64 x, i64 y);
f32 gup_pow_f32(f32 x, f32 y);
f64 gup_pow_f64(f64 x, f64 y);

// Miscellaneous
double gup_operation_seconds(void (*fn)());
#define gup_array_len(a) sizeof(a)/sizeof(a[0]) 
#define gup_defer_return(r) do { result = (r); goto defer; } while (0)
#define GUP_RUN if (true)
#define GUP_SKIP if (false)
int gup_char_to_int(char c); // -1 means the character was not an int.
u32 gup_fnv1a_hash(const char *s);


/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

#define GUPPY_IMPLEMENTATION
#ifdef GUPPY_IMPLEMENTATION

#define GUP_ARRAY_DEFAULT_CAPACITY 256
#define GUP_SET_DEFAULT_CAPACITY 8192
#define GUP_HASHMAP_DEFAULT_CAPACITY 8192

// Assert ------------------------------------------------------------------------------------------

void _gup_assert(bool pass_condition, const char *literal_pass_condition, const char *file_path, int line_number) {
    if (!pass_condition) {
        printf("[%s:%d] Failed assertion!\n", file_path, line_number);
        printf("---> %s <---\n", literal_pass_condition);
        exit(1);
    }
}

void _gup_assert_verbose(bool pass_condition, const char *failure_explanation, const char *literal_pass_condition, const char *file_path, int line_number) {
    if (!pass_condition) {
        printf("[%s:%d] Failed assertion!\n", file_path, line_number);
        printf("---> %s <---\n", literal_pass_condition);
        printf("%s\n", failure_explanation);
        exit(1);
    }
}

// Allocator -----------------------------------------------------------------------------------------------------------

void *gup_alloc(GupAllocator *head, size_t bytes) {
    if (head == NULL) return malloc(bytes);

    switch (head->type) {
        case GUP_ALLOCATOR_TYPE_MALLOC: return malloc(bytes);
        case GUP_ALLOCATOR_TYPE_ARENA:  return gup_arena_alloc((GupArena *)head, bytes);
        default: {
            printf("ERROR: unknown allocator type.\n");
            exit(1);
        } break;
    }
}

// TODO: gup_realloc

void gup_free(GupAllocator *head, void *ptr) {
    if (head == NULL) {
        free(ptr);
        return;
    }
    
    switch (head->type) {
        case GUP_ALLOCATOR_TYPE_MALLOC: {
            free(ptr);
        } break;
        case GUP_ALLOCATOR_TYPE_ARENA:  {
            printf("WARNING: Tried to free memory that is within an arena. You probably don't actually want to do that. If you do, you probably should not be using an arena to allocate that memory.\n");
        } break;
        default: {
            printf("ERROR: unknown allocator type.\n");
            exit(1);
        } break;
    }
}

// Arena ---------------------------------------------------------------------------------------------------------------

GupArena gup_arena_create() {
    GupArrayPtr *ptrs = malloc(sizeof(GupArrayPtr));
    *ptrs = gup_array_ptr_create(NULL);

    return (GupArena) {
        .head = (GupAllocator) { .type = GUP_ALLOCATOR_TYPE_ARENA },
        .data = ptrs,
    };
}

void gup_arena_destroy(GupArena *a) {
    gup_arena_free(a);
    gup_array_ptr_destroy(*(a->data));
    free(a->data);
}

void *gup_arena_alloc(GupArena *a, size_t bytes) {
    if (a->data->count == a->data->capacity) {
        const int new_capacity = a->data->capacity == 0 ? 1 : a->data->capacity * 2;
        a->data->data = realloc(a->data->data, new_capacity * sizeof(void *));
        a->data->capacity = new_capacity;
    }

    void *ptr = malloc(bytes);
    gup_assert(ptr != NULL);

    a->data->data[a->data->count] = ptr;
    a->data->count++;

    return ptr;
}

void gup_arena_free(GupArena *a) {
    for (int i = 0; i < a->data->count; i++) {
        free(a->data->data[i]);
    }
    a->data->count = 0;
}

// Dynamic Arrays ----------------------------------------------------------------------------------

// Default constructors
GupArrayBool gup_array_bool_create(GupAllocator *a) {
    GupArrayBool xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(bool)),
    };
    return xs;
}

GupArrayChar gup_array_char_create(GupAllocator *a) {
    GupArrayChar xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(char)),
    };
    return xs;
}

GupArrayDouble gup_array_double_create(GupAllocator *a) {
    GupArrayDouble xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(double)),
    };
    return xs;
}

GupArrayFloat gup_array_float_create(GupAllocator *a) {
    GupArrayFloat xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(float)),
    };
    return xs;
}

GupArrayInt gup_array_int_create(GupAllocator *a) {
    GupArrayInt xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(int)),
    };
    return xs;
}

GupArrayLong gup_array_long_create(GupAllocator *a) {
    GupArrayLong xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(long)),
    };
    return xs;
}

GupArrayPtr gup_array_ptr_create(GupAllocator *a) {
    GupArrayPtr xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(void *)),
    };
    return xs;
}

GupArrayShort gup_array_short_create(GupAllocator *a) {
    GupArrayShort xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(short)),
    };
    return xs;
}

GupArrayString gup_array_string_create(GupAllocator *a) {
    GupArrayString xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(GupArrayChar)),
    };
    return xs;
}

GupArrayCstr gup_array_cstr_create(GupAllocator *a) {
    GupArrayCstr xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(char *)),
    };
    return xs;
}

// Destructors
void gup_array_bool_destroy(GupArrayBool xs) {
    free(xs.data);
}

void gup_array_char_destroy(GupArrayChar xs) {
    free(xs.data);
}

void gup_array_double_destroy(GupArrayDouble xs) {
    free(xs.data);
}

void gup_array_float_destroy(GupArrayFloat xs) {
    free(xs.data);
}

void gup_array_int_destroy(GupArrayInt xs) {
    free(xs.data);
}

void gup_array_long_destroy(GupArrayLong xs) {
    free(xs.data);
}

void gup_array_short_destroy(GupArrayShort xs) {
    free(xs.data);
}

void gup_array_ptr_destroy(GupArrayPtr xs) {
    free(xs.data);
}

void gup_array_string_destroy(GupArrayString xs) {
    free(xs.data);
}

void gup_array_cstr_destroy(GupArrayCstr xs) {
    free(xs.data);
}

// From constructors
#define gup_array_char_create_from_cstr(a, cstr) gup_array_char_create_from_array(a, cstr, strlen(cstr))

GupArrayBool gup_array_bool_create_from_array(GupAllocator *a, bool xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayBool new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = gup_alloc(a, size_to_alloc * sizeof(bool)),
    };

    memcpy(new.data, xs, size * sizeof(bool));

    return new;
}

/** Copies the string into the result. */
GupArrayChar gup_array_char_create_from_array(GupAllocator *a, char xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayChar new = {
        .capacity = size_to_alloc,
        .count    = size,
        .data     = gup_alloc(a, size_to_alloc * sizeof(char)),
    };

    memcpy(new.data, xs, size * sizeof(char));

    return new;
}

GupArrayDouble gup_array_double_create_from_array(GupAllocator *a, double xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayDouble new = {
        .capacity = size_to_alloc,
        .count    = size,
        .data     = gup_alloc(a, size_to_alloc * sizeof(double)),
    };

    memcpy(new.data, xs, size * sizeof(double));

    return new;
}

GupArrayFloat gup_array_float_create_from_array(GupAllocator *a, float xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayFloat new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = gup_alloc(a, size_to_alloc * sizeof(float)),
    };

    memcpy(new.data, xs, size * sizeof(float));

    return new;
}

GupArrayInt gup_array_int_create_from_array(GupAllocator *a, int xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayInt new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = gup_alloc(a, size_to_alloc * sizeof(int)),
    };

    memcpy(new.data, xs, size * sizeof(int));

    return new;
}

GupArrayLong gup_array_long_create_from_array(GupAllocator *a, long xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayLong new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = gup_alloc(a, size_to_alloc * sizeof(long)),
    };

    memcpy(new.data, xs, size * sizeof(long));

    return new;
}

GupArrayPtr gup_array_ptr_create_from_array(GupAllocator *a, void *xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayPtr new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = gup_alloc(a, size_to_alloc * sizeof(void *)),
    };

    memcpy(new.data, xs, size * sizeof(void *));

    return new;
}

/** Copies the GupArrayChars into the new GupArrayString. */
GupArrayString gup_array_string_create_from_array(GupAllocator *a, GupArrayChar xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayString new = {
        .capacity = size_to_alloc,
        .count    = size,
        .data     = gup_alloc(a, size_to_alloc * sizeof(GupArrayChar)),
    };

    memcpy(new.data, xs, size * sizeof(GupArrayChar));

    return new;
}

GupArrayString gup_array_string_create_from_cstrs(GupAllocator *a, char **cstrs, const int size) {
    GupArrayString new = gup_array_string_create(a);
    
    for (int i = 0; i < size; i++) {
        gup_array_string_append(a, &new, gup_array_char_create_from_cstr(a, cstrs[i]));
    }

    return new;
}

GupArrayCstr gup_array_cstr_create_from_array(GupAllocator *a, char *xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayCstr new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = gup_alloc(a, size_to_alloc * sizeof(char *)),
    };

    memcpy(new.data, xs, size * sizeof(char *));

    return new;
}

// Copy constructors
GupArrayBool gup_array_bool_copy(GupAllocator *a, GupArrayBool xs) {
    GupArrayBool new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = gup_alloc(a, xs.capacity * sizeof(bool)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(bool));

    return new;
}

GupArrayChar gup_array_char_copy(GupAllocator *a, GupArrayChar xs) {
    GupArrayChar new = {
        .capacity = xs.capacity,
        .count    = xs.count,
        .data     = gup_alloc(a, xs.capacity * sizeof(char)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(char));

    return new;
}

GupArrayDouble gup_array_double_copy(GupAllocator *a, GupArrayDouble xs) {
    GupArrayDouble new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = gup_alloc(a, xs.capacity * sizeof(double)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(double));

    return new;
}

GupArrayFloat gup_array_float_copy(GupAllocator *a, GupArrayFloat xs) {
    GupArrayFloat new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = gup_alloc(a, xs.capacity * sizeof(float)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(float));

    return new;
}

GupArrayInt gup_array_int_copy(GupAllocator *a, GupArrayInt xs) {
    GupArrayInt new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = gup_alloc(a, xs.capacity * sizeof(int)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(int));

    return new;
}

GupArrayLong gup_array_long_copy(GupAllocator *a, GupArrayLong xs) {
    GupArrayLong new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = gup_alloc(a, xs.capacity * sizeof(long)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(long));

    return new;
}

GupArrayPtr gup_array_ptr_copy(GupAllocator *a, GupArrayPtr xs) {
    GupArrayPtr new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = gup_alloc(a, xs.capacity * sizeof(void *)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(void *));

    return new;
}

GupArrayString gup_array_string_copy(GupAllocator *a, GupArrayString xs) {
    GupArrayString new = {
        .capacity = xs.capacity,
        .count    = xs.count,
        .data     = gup_alloc(a, xs.capacity * sizeof(GupArrayChar)),
    };

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = gup_array_char_copy(a, xs.data[i]);
    }

    return new;
}

GupArrayCstr gup_array_cstr_copy(GupAllocator *a, GupArrayCstr xs) {
    GupArrayCstr new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = gup_alloc(a, xs.capacity * sizeof(char *)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(char *));

    return new;
}

// Equals
bool gup_array_bool_equals(GupArrayBool xs, GupArrayBool ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_char_equals(GupArrayChar xs, GupArrayChar ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_char_equals_cstr(GupArrayChar xs, const char *cstr) {
    return strncmp(xs.data, cstr, xs.count) == 0;
}

bool gup_array_double_equals(GupArrayDouble xs, GupArrayDouble ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_float_equals(GupArrayFloat xs, GupArrayFloat ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_int_equals(GupArrayInt xs, GupArrayInt ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_long_equals(GupArrayLong xs, GupArrayLong ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_short_equals(GupArrayShort xs, GupArrayShort ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_string_equals(GupArrayString xs, GupArrayString ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (!gup_array_char_equals(xs.data[i], ys.data[i])) return false;
    }

    return true;
}

bool gup_array_cstr_equals(GupArrayCstr xs, GupArrayCstr ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (strcmp(xs.data[i], ys.data[i]) != 0) return false;
    }

    return true;
}

// Contains
bool gup_array_bool_contains(GupArrayBool xs, bool x) {
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_char_contains(GupArrayChar xs, char x) {
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_double_contains(GupArrayDouble xs, double x) {
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_float_contains(GupArrayFloat xs, float x) {
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_int_contains(GupArrayInt xs, int x) {
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_long_contains(GupArrayLong xs, long x) {
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_ptr_contains(GupArrayPtr xs, void* x) {
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_short_contains(GupArrayShort xs, short x) {
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_string_contains(GupArrayString xs, GupString x) {
    for (int i = 0; i < xs.count; i++) {
        if (gup_array_char_equals(xs.data[i], x)) {
            return true;
        }
    }

    return false;
}

bool gup_array_cstr_contains(GupArrayCstr xs, char *x) {
    for (int i = 0; i < xs.count; i++) {
        if (strcmp(xs.data[i], x) == 0) {
            return true;
        }
    }

    return false;
}

// Print
#define gup_array_bool_print(xs) _gup_array_bool_print(xs, #xs)
void _gup_array_bool_print(GupArrayBool xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == true) printf("true");
        else printf("false");

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_char_print(xs) _gup_array_char_print(xs, #xs)
void _gup_array_char_print(GupArrayChar xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("'%c'", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_double_print(xs) _gup_array_double_print(xs, #xs)
void _gup_array_double_print(GupArrayDouble xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%f", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_float_print(xs) _gup_array_float_print(xs, #xs)
void _gup_array_float_print(GupArrayFloat xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%f", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_int_print(xs) _gup_array_int_print(xs, #xs)
void _gup_array_int_print(GupArrayInt xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%d", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_long_print(xs) _gup_array_long_print(xs, #xs)
void _gup_array_long_print(GupArrayLong xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%ld", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_ptr_print(xs) _gup_array_ptr_print(xs, #xs)
void _gup_array_ptr_print(GupArrayPtr xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%p", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_short_print(xs) _gup_array_short_print(xs, #xs)
void _gup_array_short_print(GupArrayShort xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%d", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_string_print(xs) _gup_array_string_print(xs, #xs)
void _gup_array_string_print(GupArrayString xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("  \"");
        for (int j = 0; j < xs.data[i].count; j++) {
            printf("%c", xs.data[i].data[j]);
        }
        printf("\"");
        if (i != xs.count-1) printf(",");
        printf("\n");
    }
    printf("]\n");
}

#define gup_array_cstr_print(xs) _gup_array_cstr_print(xs, #xs)
void _gup_array_cstr_print(GupArrayCstr xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("\"%s\"", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

// TODO
// Debug
#define gup_array_int_debug(xs) _gup_array_int_debug(xs, #xs)
void _gup_array_int_debug(GupArrayInt xs, const char *xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs.capacity);
    printf("  count: %d\n", xs.count);
    printf("  data: %p\n", (void *)(xs.data));
    printf("}\n");
}

// Append
void gup_array_bool_append(GupAllocator *a, GupArrayBool *xs, bool x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        bool *new_data = gup_alloc(a, new_capacity * sizeof(bool));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_char_append(GupAllocator *a, GupArrayChar *xs, char x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        char *new_data = gup_alloc(a, new_capacity * sizeof(char));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_double_append(GupAllocator *a, GupArrayDouble *xs, double x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        double *new_data = gup_alloc(a, new_capacity * sizeof(double));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_float_append(GupAllocator *a, GupArrayFloat *xs, float x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        float *new_data = gup_alloc(a, new_capacity * sizeof(float));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_int_append(GupAllocator *a, GupArrayInt *xs, int x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        int *new_data = gup_alloc(a, new_capacity * sizeof(int));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_long_append(GupAllocator *a, GupArrayLong *xs, long x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        long *new_data = gup_alloc(a, new_capacity * sizeof(long));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_ptr_append(GupAllocator *a, GupArrayPtr *xs, void * x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        void * *new_data = gup_alloc(a, new_capacity * sizeof(void *));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_short_append(GupAllocator *a, GupArrayShort *xs, short x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        short *new_data = gup_alloc(a, new_capacity * sizeof(short));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

/** Appends the pointer, does NOT copy. */
void gup_array_string_append(GupAllocator *a, GupArrayString *xs, GupArrayChar x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;

        // TODO: this is actually kinda like a gup_realloc
        GupArrayChar *new_data = gup_alloc(a, new_capacity * sizeof(GupArrayChar));
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

/** Copies the cstr into the array. */
void gup_array_string_append_cstr(GupAllocator *a, GupArrayString *xs, char *cstr) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        GupString *new_data = gup_alloc(a, new_capacity * sizeof(GupString));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = gup_array_char_create_from_cstr(a, cstr);
    xs->count++;
}

void gup_array_cstr_append(GupAllocator *a, GupArrayCstr *xs, char * x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        char **new_data = gup_alloc(a, new_capacity * sizeof(char *));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data     = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

// Prepend
void gup_array_bool_prepend(GupAllocator *a, GupArrayBool *xs, bool x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        bool *new_data = gup_alloc(a, new_capacity * sizeof(bool));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_char_prepend(GupAllocator *a, GupArrayChar *xs, char x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        char *new_data = gup_alloc(a, new_capacity * sizeof(char));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_double_prepend(GupAllocator *a, GupArrayDouble *xs, double x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        double *new_data = gup_alloc(a, new_capacity * sizeof(double));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_float_prepend(GupAllocator *a, GupArrayFloat *xs, float x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        float *new_data = gup_alloc(a, new_capacity * sizeof(float));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_int_prepend(GupAllocator *a, GupArrayInt *xs, int x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        int *new_data = gup_alloc(a, new_capacity * sizeof(int));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_long_prepend(GupAllocator *a, GupArrayLong *xs, long x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        long *new_data = gup_alloc(a, new_capacity * sizeof(long));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_ptr_prepend(GupAllocator *a, GupArrayPtr *xs, void * x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        void * *new_data = gup_alloc(a, new_capacity * sizeof(void *));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_string_prepend(GupAllocator *a, GupArrayString *xs, GupArrayChar x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        GupArrayChar *new_data = gup_alloc(a, new_capacity * sizeof(GupArrayChar));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

/** Copies the cstr into the array. */
void gup_array_string_prepend_cstr(GupAllocator *a, GupArrayString *xs, char *cstr){
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(char *));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = gup_array_char_create_from_cstr(a, cstr);
    xs->count++;
}

void gup_array_cstr_prepend(GupAllocator *a, GupArrayCstr *xs, char * x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        char * *new_data = gup_alloc(a, new_capacity * sizeof(char *));
        
        memcpy(new_data, xs->data, xs->count);
        gup_free(a, xs->data);

        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

// Remove
void gup_array_bool_remove(GupArrayBool *xs, bool x, int count_to_remove) {
    bool new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        xs->data[i] = new_data[i];
        xs->count++;
    }
}

void gup_array_char_remove(GupArrayChar *xs, char x, int count_to_remove) {
    char new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        xs->data[i] = new_data[i];
        xs->count++;
    }
}

void gup_array_double_remove(GupArrayDouble *xs, double x, int count_to_remove) {
    double new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        xs->data[i] = new_data[i];
        xs->count++;
    }
}

void gup_array_float_remove(GupArrayFloat *xs, float x, int count_to_remove) {
    float new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        xs->data[i] = new_data[i];
        xs->count++;
    }
}

void gup_array_int_remove(GupArrayInt *xs, int x, int count_to_remove) {
    int new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        xs->data[i] = new_data[i];
        xs->count++;
    }
}

void gup_array_long_remove(GupArrayLong *xs, long x, int count_to_remove) {
    long new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        xs->data[i] = new_data[i];
        xs->count++;
    }
}

void gup_array_short_remove(GupArrayShort *xs, short x, int count_to_remove) {
    short new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        xs->data[i] = new_data[i];
        xs->count++;
    }
}

void gup_array_string_remove(GupArrayString *xs, GupString x, int count_to_remove) {
    GupString new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (!gup_array_char_equals(xs->data[i], x)) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        xs->data[i] = new_data[i];
        xs->count++;
    }
}

void gup_array_string_remove_cstr(GupArrayString *xs, char *x, int count_to_remove) {
    char* new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (!gup_array_char_equals_cstr(xs->data[i], x)) {
            // TODO: does this even work? might not null terminate
            strncpy(new_data[new_data_size], xs->data[i].data, xs->data[i].count);
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        // TODO: probably doesn't work?... I don't think is null terminated
        strcpy(xs->data[i].data, new_data[i]);
        xs->count++;
    }
}

void gup_array_cstr_remove(GupArrayCstr *xs, char *x, int count_to_remove) {
    char *new_data[xs->count];
    int removed_count = 0;

    int new_data_size = 0;
    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (strcmp(xs->data[i], x) != 0) {
            strcpy(new_data[new_data_size], xs->data[i]);
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        // TODO: probably doesn't work?... I don't think is null terminated
        strcpy(xs->data[i], new_data[i]);
        xs->count++;
    }
}

// Remove all
void gup_array_bool_remove_all(GupArrayBool *xs, bool x) {
    bool new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        }
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(bool));
}

void gup_array_char_remove_all(GupArrayChar *xs, char x) {
    char new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        }
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(char));
}

void gup_array_double_remove_all(GupArrayDouble *xs, double x) {
    double new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        }
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(double));
}

void gup_array_float_remove_all(GupArrayFloat *xs, float x) {
    float new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        }
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(float));
}

void gup_array_int_remove_all(GupArrayInt *xs, int x) {
    int new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        }
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(int));
}

void gup_array_long_remove_all(GupArrayLong *xs, long x) {
    long new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        }
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(long));
}

void gup_array_short_remove_all(GupArrayShort *xs, short x) {
    short new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        }
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(short));
}

void gup_array_string_remove_all(GupArrayString *xs, GupString x) {
    GupString new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (!gup_array_char_equals(xs->data[i], x)) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        }
        gup_array_char_destroy(xs->data[i]);
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(GupString));
}

void gup_array_string_remove_all_cstr(GupAllocator *a, GupArrayString *xs, char *x) {
    char *new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (!gup_array_char_equals_cstr(xs->data[i], x)) {
            strncpy(new_data[new_data_size], xs->data[i].data, xs->data[i].count);
            new_data_size++;
        }
        gup_array_char_destroy(xs->data[i]);
    }

    xs->count = 0;

    for (int i = 0; i < new_data_size; i++) {
        gup_array_string_append_cstr(a, xs, new_data[i]);
        xs->count++;
    }
}

void gup_array_cstr_remove_all(GupArrayCstr *xs, char *x) {
    char *new_data[xs->count];

    int new_data_size = 0;
    for (int i = 0; i < xs->count; i++) {
        if (strcmp(xs->data[i], x) != 0) {
            strcpy(new_data[new_data_size], xs->data[i]);
            new_data_size++;
        }
    }

    xs->count = new_data_size;
    memcpy(xs->data, new_data, new_data_size * sizeof(char *));
}

// Find
bool gup_array_bool_find(GupArrayBool xs, bool (*fn)(bool), bool *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

bool gup_array_char_find(GupArrayChar xs, bool (*fn)(char), char *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

bool gup_array_double_find(GupArrayDouble xs, bool (*fn)(double), double *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

bool gup_array_float_find(GupArrayFloat xs, bool (*fn)(float), float *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

bool gup_array_int_find(GupArrayInt xs, bool (*fn)(int), int *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

bool gup_array_long_find(GupArrayLong xs, bool (*fn)(long), long *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

bool gup_array_ptr_find(GupArrayPtr xs, bool (*fn)(void*), void* *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

bool gup_array_short_find(GupArrayShort xs, bool (*fn)(short), short *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

bool gup_array_string_find(GupArrayString xs, bool (*fn)(GupArrayChar), GupArrayChar *out) {
    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            *out = xs.data[i];
            return true;
        }
    }

    return false;
}

// Sort
// Orders false before true, (e.g. [false, false, true, true])
GupArrayBool gup_array_bool_sort(GupAllocator *a, GupArrayBool xs) {
    GupArrayBool sorted = gup_array_bool_create(a);

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == false) {
            gup_array_bool_prepend(a, &sorted, false);
        } else {
            gup_array_bool_append(a, &sorted, true);
        }
    }

    return sorted;
}

GupArrayChar gup_array_char_sort(GupAllocator *a, GupArrayChar xs) {
    if (xs.count <= 1) return xs;

    GupArrayChar sorted = gup_array_char_create(a);
    GupArrayChar left   = gup_array_char_create(a);
    GupArrayChar right  = gup_array_char_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs.count - 1;
    const char pivot = xs.data[pivot_idx];

    for (int i = 0; i < xs.count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

        if (xs.data[i] <= pivot) {
            gup_array_char_append(a, &left, xs.data[i]);
        } else {
            gup_array_char_append(a, &right, xs.data[i]);
        }
    }

    GupArrayChar sorted_left = gup_array_char_sort(a, left);
    GupArrayChar sorted_right = gup_array_char_sort(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left.count; i++) {
            gup_array_char_append(a, &sorted, sorted_left.data[i]);
        }

        gup_array_char_append(a, &sorted, pivot);

        for (int i = 0; i < sorted_right.count; i++) {
            gup_array_char_append(a, &sorted, sorted_right.data[i]);
        }
    }

    return sorted;
}

GupArrayDouble gup_array_double_sort(GupAllocator *a, GupArrayDouble xs) {
    if (xs.count <= 1) return xs;

    GupArrayDouble sorted = gup_array_double_create(a);
    GupArrayDouble left   = gup_array_double_create(a);
    GupArrayDouble right  = gup_array_double_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs.count - 1;
    const double pivot = xs.data[pivot_idx];

    for (int i = 0; i < xs.count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

        if (xs.data[i] <= pivot) {
            gup_array_double_append(a, &left, xs.data[i]);
        } else {
            gup_array_double_append(a, &right, xs.data[i]);
        }
    }

    GupArrayDouble sorted_left = gup_array_double_sort(a, left);
    GupArrayDouble sorted_right = gup_array_double_sort(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left.count; i++) {
            gup_array_double_append(a, &sorted, sorted_left.data[i]);
        }

        gup_array_double_append(a, &sorted, pivot);

        for (int i = 0; i < sorted_right.count; i++) {
            gup_array_double_append(a, &sorted, sorted_right.data[i]);
        }
    }

    return sorted;
}

GupArrayFloat gup_array_float_sort(GupAllocator *a, GupArrayFloat xs) {
    if (xs.count <= 1) return xs;

    GupArrayFloat sorted = gup_array_float_create(a);
    GupArrayFloat left   = gup_array_float_create(a);
    GupArrayFloat right  = gup_array_float_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs.count - 1;
    const float pivot = xs.data[pivot_idx];

    for (int i = 0; i < xs.count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

        if (xs.data[i] <= pivot) {
            gup_array_float_append(a, &left, xs.data[i]);
        } else {
            gup_array_float_append(a, &right, xs.data[i]);
        }
    }

    GupArrayFloat sorted_left = gup_array_float_sort(a, left);
    GupArrayFloat sorted_right = gup_array_float_sort(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left.count; i++) {
            gup_array_float_append(a, &sorted, sorted_left.data[i]);
        }

        gup_array_float_append(a, &sorted, pivot);

        for (int i = 0; i < sorted_right.count; i++) {
            gup_array_float_append(a, &sorted, sorted_right.data[i]);
        }
    }

    return sorted;
}

GupArrayInt gup_array_int_sort(GupAllocator *a, GupArrayInt xs) {
    if (xs.count <= 1) return xs;

    GupArrayInt sorted = gup_array_int_create(a);
    GupArrayInt left   = gup_array_int_create(a);
    GupArrayInt right  = gup_array_int_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs.count - 1;
    const int pivot = xs.data[pivot_idx];

    for (int i = 0; i < xs.count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

        if (xs.data[i] <= pivot) {
            gup_array_int_append(a, &left, xs.data[i]);
        } else {
            gup_array_int_append(a, &right, xs.data[i]);
        }
    }

    GupArrayInt sorted_left = gup_array_int_sort(a, left);
    GupArrayInt sorted_right = gup_array_int_sort(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left.count; i++) {
            gup_array_int_append(a, &sorted, sorted_left.data[i]);
        }

        gup_array_int_append(a, &sorted, pivot);

        for (int i = 0; i < sorted_right.count; i++) {
            gup_array_int_append(a, &sorted, sorted_right.data[i]);
        }
    }

    return sorted;
}

GupArrayLong gup_array_long_sort(GupAllocator *a, GupArrayLong xs) {
    if (xs.count <= 1) return xs;

    GupArrayLong sorted = gup_array_long_create(a);
    GupArrayLong left   = gup_array_long_create(a);
    GupArrayLong right  = gup_array_long_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs.count - 1;
    const long pivot = xs.data[pivot_idx];

    for (int i = 0; i < xs.count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

        if (xs.data[i] <= pivot) {
            gup_array_long_append(a, &left, xs.data[i]);
        } else {
            gup_array_long_append(a, &right, xs.data[i]);
        }
    }

    GupArrayLong sorted_left = gup_array_long_sort(a, left);
    GupArrayLong sorted_right = gup_array_long_sort(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left.count; i++) {
            gup_array_long_append(a, &sorted, sorted_left.data[i]);
        }

        gup_array_long_append(a, &sorted, pivot);

        for (int i = 0; i < sorted_right.count; i++) {
            gup_array_long_append(a, &sorted, sorted_right.data[i]);
        }
    }

    return sorted;
}

GupArrayShort gup_array_short_sort(GupAllocator *a, GupArrayShort xs) {
    if (xs.count <= 1) return xs;

    GupArrayShort sorted = gup_array_short_create(a);
    GupArrayShort left   = gup_array_short_create(a);
    GupArrayShort right  = gup_array_short_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs.count - 1;
    const short pivot = xs.data[pivot_idx];

    for (int i = 0; i < xs.count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

        if (xs.data[i] <= pivot) {
            gup_array_short_append(a, &left, xs.data[i]);
        } else {
            gup_array_short_append(a, &right, xs.data[i]);
        }
    }

    GupArrayShort sorted_left = gup_array_short_sort(a, left);
    GupArrayShort sorted_right = gup_array_short_sort(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left.count; i++) {
            gup_array_short_append(a, &sorted, sorted_left.data[i]);
        }

        gup_array_short_append(a, &sorted, pivot);

        for (int i = 0; i < sorted_right.count; i++) {
            gup_array_short_append(a, &sorted, sorted_right.data[i]);
        }
    }

    return sorted;
}

GupArrayString gup_array_string_sort(GupAllocator *a, GupArrayString xs) {
    if (xs.count <= 1) return xs;

    GupArrayString sorted = gup_array_string_create(a);
    GupArrayString left   = gup_array_string_create(a);
    GupArrayString right  = gup_array_string_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs.count - 1;
    const GupString pivot = xs.data[pivot_idx];

    for (int i = 0; i < xs.count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

        if (gup_string_compare(a, xs.data[i], pivot) <= 0) {
            gup_array_string_append(a, &left, xs.data[i]);
        } else {
            gup_array_string_append(a, &right, xs.data[i]);
        }
    }

    GupArrayString sorted_left = gup_array_string_sort(a, left);
    GupArrayString sorted_right = gup_array_string_sort(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left.count; i++) {
            gup_array_string_append(a, &sorted, sorted_left.data[i]);
        }

        gup_array_string_append(a, &sorted, pivot);

        for (int i = 0; i < sorted_right.count; i++) {
            gup_array_string_append(a, &sorted, sorted_right.data[i]);
        }
    }

    return sorted;
}

GupArrayCstr gup_array_cstr_sort(GupAllocator *a, GupArrayCstr xs) {
    if (xs.count <= 1) return xs;

    GupArrayCstr sorted = gup_array_cstr_create(a);
    GupArrayCstr left   = gup_array_cstr_create(a);
    GupArrayCstr right  = gup_array_cstr_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs.count - 1;
    char *pivot = xs.data[pivot_idx];

    for (int i = 0; i < xs.count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

        if (strcmp(xs.data[i], pivot) <= 0) {
            gup_array_cstr_append(a, &left, xs.data[i]);
        } else {
            gup_array_cstr_append(a, &right, xs.data[i]);
        }
    }

    GupArrayCstr sorted_left = gup_array_cstr_sort(a, left);
    GupArrayCstr sorted_right = gup_array_cstr_sort(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left.count; i++) {
            gup_array_cstr_append(a, &sorted, sorted_left.data[i]);
        }

        gup_array_cstr_append(a, &sorted, pivot);

        for (int i = 0; i < sorted_right.count; i++) {
            gup_array_cstr_append(a, &sorted, sorted_right.data[i]);
        }
    }

    return sorted;
}

// Miscellaneous
char *gup_array_char_to_cstr(GupAllocator *a, GupArrayChar chars) {
    // count + 1 for null terminator
    char *result = gup_alloc(a, (chars.count + 1) * sizeof(char));
    
    for (int i = 0; i < chars.count; i++) {
        result[i] = chars.data[i];
    }
    result[chars.count] = '\0';

    return result;
}

char **gup_array_string_to_cstrs(GupAllocator *a, GupArrayString strs) {
    // count + 1 for null terminator
    char **result = gup_alloc(a, (strs.count + 1) * sizeof(char *));

    for (int i = 0; i < strs.count; i++) {
        result[i] = gup_array_char_to_cstr(a, strs.data[i]);
    }
    result[strs.count] = NULL;

    return result;
}

// TODO: Memory ------------------------------------------------------------------------------------------

/* TODO
 * Thanks to Eskil Steenberg for his explanation of using these custom memory macros for debugging.
 * Check out his masterclass on programming in C: https://youtu.be/443UNeGrFoM
 */

// File operations ---------------------------------------------------------------------------------

const char *GUP_DEFAULT_FILE_ERROR_MESSAGE = "File operation failed.\nYou should probably double check that you:\n1) spelled the file name correctly\n2) are creating the file in the directory you think you are\n3) have permissions to create a file in that directory\n";

bool gup_file_create(const char *file_path) {
    bool result = true;
    
    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        printf("Failed to create file %s\n", file_path);
        gup_defer_return(false);
    }

defer:
    fclose(fp);
    return result;
}

bool gup_file_delete(const char *file_path) {
    const bool result = remove(file_path);

    #ifdef GUPPY_VERBOSE
    if (!result) {    
        printf("Failed to delete file %s\n", file_path);
    }
    #endif // GUPPY_VERBOSE

    return result;
}

bool gup_file_exists(const char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Error opening file %s\n", file_path);
        #endif

        return false;
    }

    fclose(fp);
    return true;
}

bool gup_file_is_empty(const char *file_path) {
    int line_count = gup_file_line_count(file_path);
    gup_assert_verbose(line_count != -1, "gup_file_line_count had an issue while opening the file.");

    return line_count == 0;
}

/**
 * This will basically tell you what number you would see in a text editor on the last line.
 * So, if you have a file with 5 lines, the line count will be 5.
 * If you have a file with 5 lines, but the last line is empty, the line count will be 6.
 * If you have an absolutely empty file, the line count will be 0.
 */
int gup_file_line_count(const char *file_path) {
    int c = 0;
    int line_count = 0;
    int result = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Error opening file %s\n", file_path);
        #endif

        return -1;
    }

    // If the very first character of the file is the end of the file, then we can say the line
    // count is 0.
    c = fgetc(fp);
    if (c == EOF) {
        #ifdef GUPPY_VERBOSE
        printf("The file you're trying to open (\"%s\") is empty\n", file_path);
        #endif

        gup_defer_return(0);
    }

    // If the first character is anything other than the end of the file, then we can say there is
    // at least one line in the file (even if it is a newline).
    line_count++;

    do {
        if (c == '\n') {
            line_count++;
        }
    } while ((c = fgetc(fp)) != EOF);
    gup_defer_return(line_count);

defer:
    fclose(fp);
    return result;
}

void gup_file_print(GupAllocator *a, const char *file_path) {
    printf("[%s]\n", file_path);
    char **file_lines = NULL;
    if (!gup_file_read_lines_as_cstrs(a, file_path, &file_lines)) return;

    const int line_count = gup_file_line_count(file_path);
    for (int i = 0; i < line_count-1; i++) {
        printf("%s\n", file_lines[i]);
        gup_free(a, file_lines[i]);
    }
    printf("\n");
    gup_free(a, file_lines);
}

void gup_file_print_lines(GupAllocator *a, const char *file_path) {
    printf("[%s]\n", file_path);
    char **file_lines = NULL;
    if (!gup_file_read_lines_as_cstrs(a, file_path, &file_lines)) return;

    const int line_count = gup_file_line_count(file_path);
    for (int i = 0; i < line_count-1; i++) {
        printf("%d %s\n", i+1, file_lines[i]);
        gup_free(a, file_lines[i]);
    }
    printf("\n");
    gup_free(a, file_lines);
}

bool gup_file_read(GupAllocator *a, const char *file_path, GupString *out) {
    GupAllocator local = (GupAllocator) { .type = GUP_ALLOCATOR_TYPE_MALLOC };
    bool result  = true;
    char *buffer = NULL;

    FILE *fp = fopen(file_path, "r");

    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open %s: %s", file_path, strerror(errno));
        #endif // GUPPY_VERBOSE
        return false;
    }

    long file_size = 0;
    gup_assert(gup_file_size(file_path, &file_size));
    buffer = (char *) gup_alloc(&local, file_size + 1);
    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);

    if ((long)bytes_read != file_size) {
        #ifdef GUPPY_VERBOSE
        printf("Was unable to fully read %s", file_path);
        #endif // GUPPY_VERBOSE
        gup_defer_return(false);
    }

    buffer[file_size] = '\0';
    *out = gup_array_char_create_from_cstr(a, buffer);
    gup_free(&local, buffer);

defer:
    if (fp) fclose(fp);
    return result;
}

bool gup_file_read_as_cstr(GupAllocator *a, const char *file_path, char **out) {
    bool result = true;
    char *buffer = NULL;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        return false;
    }

    long file_size = 0;
    gup_assert(gup_file_size(file_path, &file_size));
    buffer = (char *) gup_alloc(a, file_size + 1);

    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);
    if ((long)bytes_read != file_size) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to read file %s\n", file_path);
        #endif
        gup_defer_return(false);
    }

    buffer[file_size] = '\0';
    *out = buffer;

defer:
    if (fp) fclose(fp);
    return result;
}

void _remove_trailing_newline(GupString *str) {
    if (str->data[str->count-1] == '\n') {
        str->count--;
    }
}

GupArrayString gup_file_read_lines(GupAllocator *a, const char *file_path) {
    GupArrayString result = {0};
    gup_file_read_lines_keep_newlines(a, file_path, &result);

    for (int i = 0; i < result.count; i++) {
        gup_array_char_remove_all(&result.data[i], '\n');
    }

    return result;
}

bool gup_file_read_lines_keep_newlines(GupAllocator *a, const char *file_path, GupArrayString *out) {
    bool result = true;
    GupArrayString lines = gup_array_string_create(a);

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(false);
    }

    char buffer[65536];
    while (fgets(buffer, 65536, fp) != NULL) {
        gup_array_string_append_cstr(a, &lines, buffer);
    }
    *out = lines;

defer:
    if (fp) fclose(fp);
    return result;
}

bool gup_file_read_lines_as_cstrs(GupAllocator *a, const char *file_path, char ***out) {
    bool result = true;
    
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(false);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("The file you are trying to read has no lines %s\n", file_path);
        #endif
        
        gup_defer_return(false);
    }
    char **lines = (char **) gup_alloc(a, sizeof(char **) * line_count);

    char butter[65536];
    for (int i = 0; fgets(butter, 65536, fp) != NULL; i++) {
        const int line_length = gup_cstr_length_excluding_null(butter);
        lines[i] = (char *) gup_alloc(a, sizeof(char *) * line_length);
        gup_cstr_copy_n(lines[i], butter, line_length-1);
    }

    *out = lines;

defer:
    if (fp) fclose(fp);
    return result;
}

bool gup_file_read_lines_as_cstrs_keep_newlines(GupAllocator *a, const char *file_path, char ***out) {
    bool result = true;
    
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(false);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("The file you are trying to read has no lines %s\n", file_path);
        #endif
        
        gup_defer_return(false);
    }
    char **lines = (char **) gup_alloc(a, sizeof(char **) * line_count);

    char buffer[65536];
    for (int i = 0; fgets(buffer, 65536, fp) != NULL; i++) {
        lines[i] = (char *) gup_alloc(a, sizeof(char *) * gup_cstr_length_excluding_null(buffer));
        gup_cstr_copy(lines[i], buffer);
    }

    *out = lines;

defer:
    if (fp) fclose(fp);
    return result;
}

bool gup_file_size(const char *file_path, long *out) {
    bool result = true;

    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open %s: %s", file_path, strerror(errno));
        #endif // GUPPY_VERBOSE
        gup_defer_return(false);
    }

    fseek(fp, 0, SEEK_END);
    *out = ftell(fp);

defer:
    if (fp) fclose(fp);
    return result;
}

int gup_file_watch(const char *file_path, void (*fn)(void)) {
    if (file_path == NULL || strcmp(file_path, "") == 0) {
        printf("ERROR: Didn't receive a file to watch.\n");
        exit(1);
    }

    struct stat file_stat;
    time_t last_modified_time = 0;

    while(true) {
        gup_assert_verbose(stat(file_path, &file_stat) == 0, "Tried to read the metadata of the file you're watching, but wasn't able to for whatever reason.");
        
        time_t current_modified_time = file_stat.st_mtime;

        bool file_was_updated_since_last_checked = current_modified_time > last_modified_time;
        if (file_was_updated_since_last_checked) {
            // Do the thing you wanted to do when the file is updated
            fn();
            printf("Last modified: %s", ctime(&file_stat.st_mtime));

            last_modified_time = current_modified_time;
        }

        usleep(34000); // Should be around 30 fps
    }

    return 0;
}

int gup_file_watch_cli_command(const char *file_path, const char *cli_command) {
    if (file_path == NULL || strcmp(file_path, "") == 0) {
        printf("ERROR: Didn't receive a file to watch.\n");
        exit(1);
    }

    struct stat file_stat;
    time_t last_modified_time = 0;

    while(true) {
        gup_assert_verbose(stat(file_path, &file_stat) == 0, "Tried to read the metadata of the file you're watching, but wasn't able to for whatever reason.");
        
        time_t current_modified_time = file_stat.st_mtime;

        bool file_was_updated_since_last_checked = current_modified_time > last_modified_time;
        if (file_was_updated_since_last_checked) {
            // Do the thing you wanted to do when the file is updated
            system(cli_command);
            printf("Last modified: %s", ctime(&file_stat.st_mtime));

            last_modified_time = current_modified_time;
        }

        usleep(34000); // Should be around 30 fps
    }

    return 0;
}

bool gup_file_write(GupAllocator *a, GupString text_to_write, const char *file_path) {
    bool result = true;

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open %s: %s", file_path, strerror(errno));
        #endif // GUPPY_VERBOSE
        gup_defer_return(false);
    }

    fprintf(fp, "%s", gup_string_to_cstr(a, text_to_write));

defer:
    if (fp) fclose(fp);
    return result;
}

bool gup_file_write_cstr(const char *text_to_write, const char *file_path) {
    bool result = true;

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
            printf("Failed to open %s: %s", file_path, strerror(errno));
        #endif // GUPPY_VERBOSE
        gup_defer_return(false);
    }

    fprintf(fp, "%s", text_to_write);

defer:
    if (fp) fclose(fp);
    return result;
}

bool gup_file_write_lines(GupAllocator *a, GupArrayString lines_to_write, const char *file_path) {
    bool result = true;

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
            printf("Failed to open %s: %s", file_path, strerror(errno));
        #endif // GUPPY_VERBOSE
        gup_defer_return(false);
    }

    for (int i = 0; i < lines_to_write.count; i++) {
        fputs(gup_string_to_cstr(a, lines_to_write.data[i]), fp);
        fputs("\n", fp);
    }

defer:
    if (fp) fclose(fp);
    return result;
}

bool gup_file_write_lines_cstrs(char **lines_to_write, const int line_count, const char *file_path) {
    char result = true;

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
            printf("Failed to open %s: %s", file_path, strerror(errno));
        #endif // GUPPY_VERBOSE
        gup_defer_return(false);
    }

    for (int i = 0; i < line_count; i++) {
        fputs(lines_to_write[i], fp);
        fputs("\n", fp);
    }

defer:
    if (fp) fclose(fp);
    return result;
}

void gup_file_append_line(GupAllocator *a, GupString line_to_write, const char *file_path) {
    FILE *fp = fopen(file_path, "a");
    gup_assert_verbose(fp != NULL, "tried opening a file to append to it, but wasn't able to.");

    fprintf(fp, "%s\n", gup_string_to_cstr(a, line_to_write));

    fclose(fp);
}

void gup_file_append_line_cstr(const char *line_to_write, const char *file_path) {
    FILE *fp = fopen(file_path, "a");
    gup_assert_verbose(fp != NULL, "tried opening a file to append to it, but wasn't able to.");

    fprintf(fp, "%s\n", line_to_write);

    fclose(fp);
}

void gup_file_append_lines(GupAllocator *a, GupArrayString lines_to_write, const char *file_path) {
    FILE *fp = fopen(file_path, "a");
    gup_assert_verbose(fp != NULL, "tried opening a file to append to it, but wasn't able to.");

    for (int i = 0; i < lines_to_write.count; i++) {
        fprintf(fp, "%s\n", gup_string_to_cstr(a, lines_to_write.data[i]));
    }

    fclose(fp);
}

void gup_file_append_lines_cstrs(char **lines_to_write, const int line_count, const char *file_path) {
    FILE *fp = fopen(file_path, "a");
    gup_assert_verbose(fp != NULL, "tried opening a file to append to it, but wasn't able to.");

    for (int i = 0; i < line_count; i++) {
        fprintf(fp, "%s\n", lines_to_write[i]);
    }

    fclose(fp);
}

// Strings -------------------------------------------------------------------------------------

#define gup_string_create gup_array_char_create
#define gup_string_destroy gup_array_char_destroy
#define gup_string_create_from_cstr gup_array_char_create_from_cstr
#define gup_string gup_string_create_from_cstr
#define gup_string_copy gup_array_char_copy
#define gup_string_equals gup_array_char_equals
#define gup_string_equals_cstr gup_array_char_equals_cstr
#define gup_string_contains gup_array_char_contains

// TODO: do not allocate memory for this lol
int gup_string_compare(GupAllocator *a, GupString x, GupString y) {
    const char *x_cstr = gup_string_to_cstr(a, x);
    const char *y_cstr = gup_string_to_cstr(a, y);
    
    return strcmp(x_cstr, y_cstr);
}

bool gup_string_contains_substring(GupString str, GupString sub_str) {
    if (sub_str.count > str.count) {
        return false;
    }

    for (int i = 0, j = 0; i < str.count; i++) {
        if (str.data[i] == sub_str.data[j]) {
            if (j == sub_str.count - 1) {
                return true;
            }

            j++;
        } else {
            j = 0;
        }
    }

    return false;
}

void _gup_string_print(GupString str, const char* str_name) {
    printf("%s: \"", str_name);
    for (int i = 0; i < str.count; i++) {
        printf("%c", str.data[i]);
    }
    printf("\"\n");
}
#define gup_string_print(str) _gup_string_print(str, #str)

void _gup_string_debug(GupString str, const char* str_name) {
    printf("%s: {\n", str_name);
    printf("  capacity: %d\n", str.capacity);
    printf("  count:    %d\n", str.count);
    printf("  data:     [");
    for (int i = 0; i < str.count; i++) {
        printf("%c", str.data[i]);
        if (i == str.count - 1) {
            printf(", ");
        }
    }
    printf("]\n}\n");
}
#define gup_string_debug(str) _gup_string_debug(str, #str)

#define gup_string_append gup_array_char_append

void gup_string_append_str(GupAllocator *a, GupString *str, GupString str_to_append) {
    for (int i = 0; i < str_to_append.count; i++) {
        gup_array_char_append(a, str, str_to_append.data[i]);
    }
}

void gup_string_append_cstr(GupAllocator *a, GupString *str, const char *cstr_to_append) {
    const int cstr_len = gup_cstr_length_excluding_null(cstr_to_append);
    for (int i = 0; i < cstr_len; i++) {
        gup_array_char_append(a, str, cstr_to_append[i]);
    }
}

#define gup_string_prepend gup_array_char_prepend
#define gup_string_find gup_array_char_find

GupString gup_string_trim_char(GupAllocator *a, GupString str, char c) {
    GupString trimmed_str = gup_string_copy(a, str);

    int i = 0;
    while (i < trimmed_str.count && trimmed_str.data[i] == c) {
        i++;
    }
    memmove(trimmed_str.data, trimmed_str.data + i, trimmed_str.count - i);
    trimmed_str.count -= i;

    while (trimmed_str.count > 0 && trimmed_str.data[trimmed_str.count - 1] == c) {
        trimmed_str.count--;
    }

    return trimmed_str;
}

void gup_string_trim_char_in_place(GupString *str, char c) {
    int i = 0;
    for (; i < str->count && str->data[i] == c; i++) {}
    memmove(str->data, str->data + i, str->count - i);
    str->count -= i;

    for (; str->count > 0 && str->data[str->count - 1] == c; str->count--) {}
}

GupString gup_string_trim_fn(GupAllocator *a, GupString str, bool (*fn)(char)) {
    GupString trimmed_str = gup_string_copy(a, str);

    int i = 0;
    while (i < trimmed_str.count && fn(trimmed_str.data[i])) {
        i++;
    }
    memmove(trimmed_str.data, trimmed_str.data + i, trimmed_str.count - i);
    trimmed_str.count -= i;

    while (trimmed_str.count > 0 && fn(trimmed_str.data[trimmed_str.count - 1])) {
        trimmed_str.count--;
    }

    return trimmed_str;
}

void gup_string_trim_fn_in_place(GupString *str, bool (*fn)(char)) {
    int i = 0;
    while (i < str->count && fn(str->data[i])) {
        i++;
    }
    memmove(str->data, str->data + i, str->count - i);
    str->count -= i;

    while (str->count > 0 && fn(str->data[str->count - 1])) {
        str->count--;
    }
}

/**
 * Returns an array of strings allocated by the GupAllocator param j.
 * "  hello world  " -> ["hello", "world"]
 */
GupArrayString gup_string_split(GupAllocator *a, GupString str, char c) {
    GupArrayString tokens = gup_array_string_create(a);
    GupString token = gup_string_create(a);
    // "  hello world  " -> "hello world"
    GupString trimmed = gup_string_trim_char(a, str, c);

    for (int i = 0; i < trimmed.count; i++) {
        // i (5): ' ' == ' '
        if (trimmed.data[i] == c) {
            // tokens: [] -> ["hello"]
            gup_array_string_append(a, &tokens, token);
            token = gup_string_create(a);
        }
        // Are we at the end of the string? If so, append the final token to the list. Then we're done.
        // i (10): 10 == 11-1
        else if (i == trimmed.count-1) {
            // token: "worl" -> "world"
            gup_string_append(a, &token, trimmed.data[i]);
            // tokens: ["hello"] -> ["hello", "world"]
            gup_array_string_append(a, &tokens, token);
        }
        // i (0): 'h' == ' ' -> token: "h"
        // i (1): 'e' == ' ' -> token: "he"
        // i (2): 'l' == ' ' -> token: "hel"
        // i (3): 'l' == ' ' -> token: "hell"
        // i (4): 'o' == ' ' -> token: "hello"
        else {
            gup_string_append(a, &token, trimmed.data[i]);
        }
    }

    return tokens;
}

// TODO: test
GupArrayString gup_string_split_by_cstr(GupAllocator *a, GupString str, char *sub_str) {
    GupArena local = gup_arena_create();
    GupArrayString tokens = gup_array_string_create(a);
    GupString token = gup_string_create((GupAllocator *)&local);

    for (int i = 0; i < str.count; i++) {
        // TODO: have a macro for this, basically just making a string view
        GupString source = (GupString) {
            .capacity = str.capacity,
            .count    = gup_cstr_length_excluding_null(sub_str), // TODO: slow?
            .data     = str.data + i,
        };

        if (gup_string_equals_cstr(source, sub_str)) {
            gup_array_string_append(a, &tokens, token);
            token = gup_string_create((GupAllocator *)&local);
            i += gup_cstr_length_excluding_null(sub_str) - 1;
        } else if (i == str.count-1) {
            gup_string_append((GupAllocator *)&local, &token, str.data[i]);
            gup_array_string_append(a, &tokens, token);
            token = gup_string_create((GupAllocator *)&local);
        } else {
            gup_string_append((GupAllocator *)&local, &token, str.data[i]);
        }
    }

    gup_arena_destroy(&local);
    return tokens;
}

bool gup_string_starts_with(GupString str, GupString sub_str) {
    // Don't count string as "starting with" empty strings.
    if (sub_str.count == 0) {
        return false;
    }

    // A string can't start with a substring that is longer than itself.
    if (str.count < sub_str.count) {
        return false;
    }

    for (int i = 0; i < sub_str.count; i++) {
        if (str.data[i] != sub_str.data[i]) {
            return false;
        }
    }

    return true;
}

bool gup_string_starts_with_cstr(GupString str, const char* cstr) {
    const int cstr_len = gup_cstr_length_excluding_null(cstr);

    // Don't count string as "starting with" empty strings.
    if (cstr_len == 0) {
        return false;
    }

    // A string can't start with a substring that is longer than itself.
    if (cstr_len > str.count) {
        return false;
    }

    for (int i = 0; i < cstr_len; i++) {
        if (cstr[i] != str.data[i]) {
            return false;
        }
    }

    return true;
}

bool gup_string_ends_with(GupString str, GupString sub_str) {
    // Don't count string as "ending with" empty strings.
    if (sub_str.count == 0) {
        return false;
    }

    // A string can't end with a substring that is longer than itself.
    if (str.count < sub_str.count) {
        return false;
    }

    for (int i = str.count - sub_str.count, j = 0; i < str.count; i++, j++) {
        if (sub_str.data[j] != str.data[i]) {
            return false;
        }
    }

    return true;
}

bool gup_string_ends_with_cstr(GupString str, const char* cstr) {
    const int cstr_len = gup_cstr_length_excluding_null(cstr);

    // Don't count string as "ending with" empty strings.
    if (cstr_len == 0) {
        return false;
    }

    // A string can't end with a substring that is longer than itself.
    if (str.count < cstr_len) {
        return false;
    }

    for (int i = str.count - cstr_len, j = 0; i < str.count; i++, j++) {
        if (cstr[j] != str.data[i]) {
            return false;
        }
    }

    return true;
}

bool gup_string_to_int(GupString str, int *out) {
    int result = 0;
    
    for (int i = str.count-1, j = 0; i >= 0; i--, j++) {
        const int char_as_int = gup_char_to_int(str.data[i]) * gup_pow_i32(10, j);
        if (char_as_int == -1) {
            return false;
        }
        result += char_as_int;
    }

    *out = result;
    return true;
}

char *gup_string_to_cstr(GupAllocator *a, GupString str) {
    // +1 because we need to allocate room for null terminator.
    char *cstr = gup_alloc(a, sizeof(char) * (str.count + 1));
    for (int i = 0; i < str.count; i++) {
        cstr[i] = str.data[i];
    }
    cstr[str.count] = '\0';
    return cstr;
}

// Sets --------------------------------------------------------------------------------------------

int _gup_hash_char_index(const char x) {
    return x < 0 ? 127 + (x * -1) : x;
}

int _gup_hash_double_index(const double key, const int modulo) {
    char input_cstr[1024];
    snprintf(input_cstr, 1024, "%f", key);
    
    const u32 hash = gup_fnv1a_hash(input_cstr);
    const int index = hash % modulo;
    
    gup_assert_verbose(index >= 0, "Got a negative index for the array of the Set");

    return index;
}

int _gup_hash_float_index(const float key, const int modulo) {
    char input_cstr[1024];
    snprintf(input_cstr, 1024, "%f", key);
    
    const u32 hash = gup_fnv1a_hash(input_cstr);
    const int index = hash % modulo;
    
    gup_assert_verbose(index >= 0, "Got a negative index for the array of the Set");

    return index;
}

int _gup_hash_ptr_index(const void* key, const int modulo) {
    char input_cstr[1024];
    snprintf(input_cstr, 1024, "%p", key);
    
    const u32 hash = gup_fnv1a_hash(input_cstr);
    const int index = hash % modulo;
    
    gup_assert_verbose(index >= 0, "Got a negative index for the array of the Set");

    return index;
}

int _gup_hash_string_index(const GupString key, const int modulo) {
    GupAllocator local = (GupAllocator) { .type = GUP_ALLOCATOR_TYPE_MALLOC };
    char *input_cstr = gup_string_to_cstr((GupAllocator *)&local, key);
    
    const u32 hash = gup_fnv1a_hash(input_cstr);
    const int index = hash % modulo;
    
    gup_assert_verbose(index >= 0, "Got a negative index for the array of the Set");
    
    gup_free((GupAllocator *)&local, input_cstr);
    return index;
}

int _gup_hash_cstr_index(const char *key, const int modulo) {
    const u32 hash = gup_fnv1a_hash(key);
    const int index = hash % modulo;
    
    gup_assert_verbose(index >= 0, "Got a negative index for the array of the Set");

    return index;
}

// Create
GupSetBool gup_set_bool_create() {
    return (GupSetBool) {
        .has_false = false,
        .has_true = false,
    };
}

GupSetChar gup_set_char_create() {
    GupSetChar xs = (GupSetChar) {
        .capacity = 256,
        .count    = 0,
        .data     = {0},
    };

    return xs;
}

GupSetDouble gup_set_double_create(GupAllocator *a) {
    GupSetDouble xs = (GupSetDouble) {
        .capacity = GUP_SET_DEFAULT_CAPACITY,
        .data     = gup_alloc(a, GUP_SET_DEFAULT_CAPACITY * sizeof(GupArrayDouble)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_double_create(a);
    }

    return xs;
}

GupSetDouble gup_set_double_create_size(GupAllocator *a, int capacity) {
    GupSetDouble xs = (GupSetDouble) {
        .capacity = capacity,
        .data     = gup_alloc(a, capacity * sizeof(GupArrayDouble)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_double_create(a);
    }

    return xs;
}

GupSetFloat gup_set_float_create(GupAllocator *a) {
    GupSetFloat xs = (GupSetFloat) {
        .capacity = GUP_SET_DEFAULT_CAPACITY,
        .data     = gup_alloc(a, GUP_SET_DEFAULT_CAPACITY * sizeof(GupArrayFloat)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_float_create(a);
    }

    return xs;
}

GupSetFloat gup_set_float_create_size(GupAllocator *a, int capacity) {
    GupSetFloat xs = (GupSetFloat) {
        .capacity = capacity,
        .data     = gup_alloc(a, capacity * sizeof(GupArrayFloat)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_float_create(a);
    }

    return xs;
}

GupSetInt gup_set_int_create(GupAllocator *a) {
    GupSetInt xs = (GupSetInt) {
        .capacity = GUP_SET_DEFAULT_CAPACITY,
        .data = gup_alloc(a, GUP_SET_DEFAULT_CAPACITY * sizeof(GupArrayInt)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_int_create(a);
    }

    return xs;
}

GupSetInt gup_set_int_create_size(GupAllocator *a, int capacity) {
    GupSetInt xs = (GupSetInt) {
        .capacity = capacity,
        .data     = gup_alloc(a, capacity * sizeof(GupArrayInt)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_int_create(a);
    }

    return xs;
}

GupSetLong gup_set_long_create(GupAllocator *a) {
    GupSetLong xs = (GupSetLong) {
        .capacity = GUP_SET_DEFAULT_CAPACITY,
        .data     = gup_alloc(a, GUP_SET_DEFAULT_CAPACITY * sizeof(GupArrayLong)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_long_create(a);
    }

    return xs;
}

GupSetLong gup_set_long_create_size(GupAllocator *a, int capacity) {
    GupSetLong xs = (GupSetLong) {
        .capacity = capacity,
        .data     = gup_alloc(a, capacity * sizeof(GupArrayLong)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_long_create(a);
    }

    return xs;
}

GupSetPtr gup_set_ptr_create(GupAllocator *a) {
    GupSetPtr xs = (GupSetPtr) {
        .capacity = GUP_SET_DEFAULT_CAPACITY,
        .data     = gup_alloc(a, GUP_SET_DEFAULT_CAPACITY * sizeof(GupArrayPtr)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_ptr_create(a);
    }

    return xs;
}

GupSetPtr gup_set_ptr_create_size(GupAllocator *a, int capacity) {
    GupSetPtr xs = (GupSetPtr) {
        .capacity = capacity,
        .data     = gup_alloc(a, capacity * sizeof(GupArrayPtr)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_ptr_create(a);
    }

    return xs;
}

GupSetShort gup_set_short_create(GupAllocator *a) {
    GupSetShort xs = (GupSetShort) {
        .capacity = GUP_SET_DEFAULT_CAPACITY,
        .data     = gup_alloc(a, GUP_SET_DEFAULT_CAPACITY * sizeof(GupArrayShort)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_short_create(a);
    }

    return xs;
}

GupSetShort gup_set_short_create_size(GupAllocator *a, int capacity) {
    GupSetShort xs = (GupSetShort) {
        .capacity = capacity,
        .data     = gup_alloc(a, capacity * sizeof(GupArrayShort)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_short_create(a);
    }

    return xs;
}

GupSetString gup_set_string_create(GupAllocator *a) {
    GupSetString xs = (GupSetString) {
        .capacity = GUP_SET_DEFAULT_CAPACITY,
        .data     = gup_alloc(a, GUP_SET_DEFAULT_CAPACITY * sizeof(GupArrayString)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_string_create(a);
    }

    return xs;
}

GupSetString gup_set_string_create_size(GupAllocator *a, int capacity) {
    GupSetString xs = (GupSetString) {
        .capacity = capacity,
        .data     = gup_alloc(a, capacity * sizeof(GupArrayString)),
    };

    for (int i = 0; i < xs.capacity; i++) {
        xs.data[i] = gup_array_string_create(a);
    }

    return xs;
}

// Create from array
GupSetBool gup_set_bool_create_from_array(bool xs[], const int size) {
    GupSetBool set = gup_set_bool_create();

    for (int i = 0; i < size; i++) {
        gup_set_bool_add(&set, xs[i]);
    }

    return set;
}

GupSetChar gup_set_char_create_from_array(char xs[], const int size) {
    GupSetChar set = gup_set_char_create();

    for (int i = 0; i < size; i++) {
        gup_set_char_add(&set, xs[i]);
    }

    return set;
}

GupSetDouble gup_set_double_create_from_array(GupAllocator *a, double xs[], const int size) {
    GupSetDouble set = gup_set_double_create(a);

    for (int i = 0; i < size; i++) {
        gup_set_double_add(a, &set, xs[i]);
    }

    return set;
}

GupSetFloat gup_set_float_create_from_array(GupAllocator *a, float xs[], const int size) {
    GupSetFloat set = gup_set_float_create(a);

    for (int i = 0; i < size; i++) {
        gup_set_float_add(a, &set, xs[i]);
    }

    return set;
}

GupSetInt gup_set_int_create_from_array(GupAllocator *a, int xs[], const int size) {
    GupSetInt set = gup_set_int_create(a);

    for (int i = 0; i < size; i++) {
        gup_set_int_add(a, &set, xs[i]);
    }

    return set;
}

GupSetLong gup_set_long_create_from_array(GupAllocator *a, long xs[], const int size) {
    GupSetLong set = gup_set_long_create(a);

    for (int i = 0; i < size; i++) {
        gup_set_long_add(a, &set, xs[i]);
    }

    return set;
}

GupSetPtr gup_set_ptr_create_from_array(GupAllocator *a, void* xs[], const int size) {
    GupSetPtr set = gup_set_ptr_create(a);

    for (int i = 0; i < size; i++) {
        gup_set_ptr_add(a, &set, xs[i]);
    }

    return set;
}

GupSetShort gup_set_short_create_from_array(GupAllocator *a, short xs[], const int size) {
    GupSetShort set = gup_set_short_create(a);

    for (int i = 0; i < size; i++) {
        gup_set_short_add(a, &set, xs[i]);
    }

    return set;
}

GupSetString gup_set_string_create_from_array(GupAllocator *a, GupString xs[], const int size) {
    GupSetString set = gup_set_string_create(a);

    for (int i = 0; i < size; i++) {
        gup_set_string_add(a, &set, xs[i]);
    }

    return set;
}

// Destroy
void gup_set_double_destroy(GupSetDouble set) {
    for (int i = 0; i < set.capacity; i++) {
        gup_array_double_destroy(set.data[i]);
    }
    free(set.data);
}

void gup_set_float_destroy(GupSetFloat set) {
    for (int i = 0; i < set.capacity; i++) {
        gup_array_float_destroy(set.data[i]);
    }
    free(set.data);
}

void gup_set_int_destroy(GupSetInt set) {
    for (int i = 0; i < set.capacity; i++) {
        gup_array_int_destroy(set.data[i]);
    }
    free(set.data);
}

void gup_set_long_destroy(GupSetLong set) {
    for (int i = 0; i < set.capacity; i++) {
        gup_array_long_destroy(set.data[i]);
    }
    free(set.data);
}

void gup_set_ptr_destroy(GupSetPtr set) {
    for (int i = 0; i < set.capacity; i++) {
        gup_array_ptr_destroy(set.data[i]);
    }
    free(set.data);
}

void gup_set_short_destroy(GupSetShort set) {
    for (int i = 0; i < set.capacity; i++) {
        gup_array_short_destroy(set.data[i]);
    }
    free(set.data);
}

void gup_set_string_destroy(GupSetString set) {
    for (int i = 0; i < set.capacity; i++) {
        gup_array_string_destroy(set.data[i]);
    }
    free(set.data);
}

// Has
bool gup_set_bool_has(GupSetBool set, bool b) {
    if (b == false) {
        return set.has_false;
    } else {
        return set.has_true;
    }
}

bool gup_set_char_has(GupSetChar set, char x) {
    return set.data[_gup_hash_char_index(x)];
}

bool gup_set_double_has(GupSetDouble set, double x) {
    int index = _gup_hash_double_index(x, set.capacity);
    const GupArrayDouble entries = set.data[index];

    return gup_array_double_contains(entries, x);
}

bool gup_set_float_has(GupSetFloat set, float x) {
    int index = _gup_hash_float_index(x, set.capacity);
    const GupArrayFloat entries = set.data[index];

    return gup_array_float_contains(entries, x);
}

bool gup_set_int_has(GupSetInt set, int x) {
    int index = x % set.capacity;
    const GupArrayInt entries = set.data[index];

    return gup_array_int_contains(entries, x);
}

bool gup_set_long_has(GupSetLong set, long x) {
    int index = x % set.capacity;
    const GupArrayLong entries = set.data[index];

    return gup_array_long_contains(entries, x);
}

bool gup_set_ptr_has(GupSetPtr set, void* x) {
    int index = _gup_hash_ptr_index(x, set.capacity);
    const GupArrayPtr entries = set.data[index];

    return gup_array_ptr_contains(entries, x);
}

bool gup_set_short_has(GupSetShort set, short x) {
    int index = x % set.capacity;
    const GupArrayShort entries = set.data[index];

    return gup_array_short_contains(entries, x);
}

bool gup_set_string_has(GupSetString set, GupString x) {
    int index = _gup_hash_string_index(x, set.capacity);
    const GupArrayString entries = set.data[index];

    return gup_array_string_contains(entries, x);
}

// Add
void gup_set_bool_add(GupSetBool *set, bool b) {
    if (b == false) {
        set->has_false = true;
    } else {
        set->has_true = true;
    }
}

void gup_set_char_add(GupSetChar *set, char x) {
    const int index = _gup_hash_char_index(x);

    if (!set->data[index]) {
        set->count++;
    }

    set->data[index] = true;
}

void gup_set_double_add(GupAllocator *a, GupSetDouble *set, double x) {
    const int index = _gup_hash_double_index(x, set->capacity);

    if (gup_array_double_contains(set->data[index], x)) return;

    gup_array_double_append(a, &(set->data[index]), x);
}

void gup_set_float_add(GupAllocator *a, GupSetFloat *set, float x) {
    const int index = _gup_hash_float_index(x, set->capacity);

    if (gup_array_float_contains(set->data[index], x)) return;

    gup_array_float_append(a, &(set->data[index]), x);
}

void gup_set_int_add(GupAllocator *a, GupSetInt *set, int x) {
    const int index = x % set->capacity;

    if (gup_array_int_contains(set->data[index], x)) return;

    gup_array_int_append(a, &(set->data[index]), x);
}

void gup_set_long_add(GupAllocator *a, GupSetLong *set, long x) {
    const int index = x % set->capacity;

    if (gup_array_long_contains(set->data[index], x)) return;

    gup_array_long_append(a, &(set->data[index]), x);
}

void gup_set_ptr_add(GupAllocator *a, GupSetPtr *set, void *x) {
    const int index = _gup_hash_ptr_index(x, set->capacity);

    if (gup_array_ptr_contains(set->data[index], x)) return;

    gup_array_ptr_append(a, &(set->data[index]), x);
}

void gup_set_short_add(GupAllocator *a, GupSetShort *set, short x) {
    const int index = x % set->capacity;

    if (gup_array_short_contains(set->data[index], x)) return;

    gup_array_short_append(a, &(set->data[index]), x);
}

void gup_set_string_add(GupAllocator *a, GupSetString *set, GupString x) {
    const int index = _gup_hash_string_index(x, set->capacity);

    if (gup_array_string_contains(set->data[index], x)) return;

    gup_array_string_append(a, &(set->data[index]), x);
}

// Remove
void gup_set_bool_remove(GupSetBool *set, bool b) {
    if (b == false) {
        set->has_false = false;
    } else {
        set->has_true = false;
    }
}

void gup_set_char_remove(GupSetChar *set, char x) {
    const int index = _gup_hash_char_index(x);

    if (set->data[index]) {
        set->count--;
    }
    set->data[index] = false;
}

void gup_set_int_remove(GupSetInt *set, int x) {
    const int index = x % set->capacity;

    if (set->data[index].count == 0) return;
    if (!gup_array_int_contains(set->data[index], x)) return;

    gup_array_int_remove_all(&(set->data[index]), x);
}

// Size
int gup_set_bool_size(GupSetBool set) {
    if (set.has_false && set.has_true) return 2;
    if (set.has_false || set.has_true) return 1;
    return 0;
}

int gup_set_char_size(GupSetChar set) {
    return set.count;
}

// int gup_set_double_size(GupSet set) {
//     return set.count;
// }

// int gup_set_float_size(GupSet set) {
//     return set.count;
// }

int gup_set_int_size(GupSetInt set) {
    int size = 0;

    for (int i = 0; i < set.capacity; i++) {
        size += set.data[i].count;
    }

    return size;
}

// int gup_set_long_size(GupSet set) {
//     return set.count;
// }

// int gup_set_ptr_size(GupSet set) {
//     return set.count;
// }

// int gup_set_short_size(GupSet set) {
//     return set.count;
// }

// int gup_set_string_size(GupSet set) {
//     return set.count;
// }

// Print
#define gup_set_bool_print(xs) _gup_set_bool_print(xs, #xs)
void _gup_set_bool_print(GupSetBool xs, const char *xs_name) {
    printf("%s: [", xs_name);
    if (xs.has_false && xs.has_true) printf("false, true");
    if (xs.has_false) printf("false");
    if (xs.has_true)  printf("true");
    printf("]\n");
}

#define gup_set_char_print(xs) _gup_set_char_print(xs, #xs)
void _gup_set_char_print(GupSetChar xs, const char *xs_name) {
    printf("%s: {", xs_name);
    bool preceeding_comma = false;
    for (int i = 0; i < xs.capacity; i++) {
        if (!xs.data[i]) continue;
        if (preceeding_comma) printf(", ");
        printf("%c (%d)", i, i);
        preceeding_comma = true;
    }
    printf("}\n");
}

#define gup_set_double_print(xs) _gup_set_double_print(xs, #xs)
void _gup_set_double_print(GupSetDouble xs, const char *xs_name) {
    printf("%s: {", xs_name);
    for (int i = 0; i < xs.capacity; i++) {
        for (int j = 0; j < xs.data[i].count; j++) {
            printf("%f", xs.data[i].data[j]);
            if (j != xs.data[i].count-1) printf(", ");
        }
    }
    printf("}\n");
}

#define gup_set_float_print(xs) _gup_set_float_print(xs, #xs)
void _gup_set_float_print(GupSetFloat xs, const char *xs_name) {
    printf("%s: {", xs_name);
    bool preceeding_comma = false;
    for (int i = 0; i < xs.capacity; i++) {
        for (int j = 0; j < xs.data[i].count; j++) {
            if (preceeding_comma) printf(", ");
            printf("%f", xs.data[i].data[j]);
            preceeding_comma = true;
        }
    }
    printf("}\n");
}

#define gup_set_int_print(xs) _gup_set_int_print(xs, #xs)
void _gup_set_int_print(GupSetInt xs, const char *xs_name) {
    printf("%s: {", xs_name);
    bool preceeding_comma = false;
    for (int i = 0; i < xs.capacity; i++) {
        for (int j = 0; j < xs.data[i].count; j++) {
            if (preceeding_comma) printf(", ");
            printf("%d", xs.data[i].data[j]);
            preceeding_comma = true;
        }
    }
    printf("}\n");
}

#define gup_set_long_print(xs) _gup_set_long_print(xs, #xs)
void _gup_set_long_print(GupSetLong xs, const char *xs_name) {
    printf("%s: {", xs_name);
    bool preceeding_comma = false;
    for (int i = 0; i < xs.capacity; i++) {
        for (int j = 0; j < xs.data[i].count; j++) {
            if (preceeding_comma) printf(", ");
            printf("%ld", xs.data[i].data[j]);
            preceeding_comma = true;
        }
    }
    printf("}\n");
}

#define gup_set_ptr_print(xs) _gup_set_ptr_print(xs, #xs)
void _gup_set_ptr_print(GupSetPtr xs, const char *xs_name) {
    printf("%s: {", xs_name);
    bool preceeding_comma = false;
    for (int i = 0; i < xs.capacity; i++) {
        for (int j = 0; j < xs.data[i].count; j++) {
            if (preceeding_comma) printf(", ");
            printf("%p", xs.data[i].data[j]);
            preceeding_comma = true;
        }
    }
    printf("}\n");
}

#define gup_set_short_print(xs) _gup_set_short_print(xs, #xs)
void _gup_set_short_print(GupSetShort xs, const char *xs_name) {
    printf("%s: {", xs_name);
    bool preceeding_comma = false;
    for (int i = 0; i < xs.capacity; i++) {
        for (int j = 0; j < xs.data[i].count; j++) {
            if (preceeding_comma) printf(", ");
            printf("%hd", xs.data[i].data[j]);
            preceeding_comma = true;
        }
    }
    printf("}\n");
}

#define gup_set_string_print(xs) _gup_set_string_print(xs, #xs)
void _gup_set_string_print(GupSetString xs, const char *xs_name) {
    printf("%s: {", xs_name);
    bool preceeding_comma = false;
    for (int i = 0; i < xs.capacity; i++) {
        for (int j = 0; j < xs.data[i].count; j++) {
            if (preceeding_comma) printf(", ");
            printf("\"");
            for (int k = 0; k < xs.data[i].data[j].count; k++) {
                printf("%c", xs.data[i].data[j].data[k]);
            }
            printf("\"");
            preceeding_comma = true;
        }
    }
    printf("}\n");
}

#define gup_set_cstr_print(xs) _gup_set_cstr_print(xs, #xs)
void _gup_set_cstr_print(GupSetCstr xs, const char *xs_name) {
    printf("%s: {", xs_name);
    bool preceeding_comma = false;
    for (int i = 0; i < xs.capacity; i++) {
        for (int j = 0; j < xs.data[i].count; j++) {
            if (preceeding_comma) printf(", ");
            printf("%s", xs.data[i].data[j]);
            preceeding_comma = true;
        }
    }
    printf("}\n");
}

// Debug

#define gup_set_int_debug(xs) _gup_hash_int_debug(xs, #xs)
void _gup_hash_int_debug(GupSetInt xs, const char *xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d", xs.capacity);
    for (int i = 0; i < xs.capacity; i++) {
        gup_array_int_debug(xs.data[i]);
    }
    printf("}\n");
}

// Hashmaps ----------------------------------------------------------------------------------------

// Create
GupHashmapBool gup_hashmap_bool_create(GupAllocator *a) {
    GupHashmapBool hashmap = (GupHashmapBool) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayBool)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_bool_create(a);
    }

    return hashmap;
}

GupHashmapChar gup_hashmap_char_create(GupAllocator *a) {
    GupHashmapChar hashmap = (GupHashmapChar) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayChar)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_char_create(a);
    }

    return hashmap;
}

GupHashmapDouble gup_hashmap_double_create(GupAllocator *a) {
    GupHashmapDouble hashmap = (GupHashmapDouble) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayDouble)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_double_create(a);
    }

    return hashmap;
}

GupHashmapFloat gup_hashmap_float_create(GupAllocator *a) {
    GupHashmapFloat hashmap = (GupHashmapFloat) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayFloat)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_float_create(a);
    }

    return hashmap;
}

GupHashmapInt gup_hashmap_int_create(GupAllocator *a) {
    GupHashmapInt hashmap = (GupHashmapInt) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayInt)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_int_create(a);
    }

    return hashmap;
}

GupHashmapLong gup_hashmap_long_create(GupAllocator *a) {
    GupHashmapLong hashmap = (GupHashmapLong) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayLong)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_long_create(a);
    }

    return hashmap;
}

GupHashmapPtr gup_hashmap_ptr_create(GupAllocator *a) {
    GupHashmapPtr hashmap = (GupHashmapPtr) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayPtr)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_ptr_create(a);
    }

    return hashmap;
}

GupHashmapShort gup_hashmap_short_create(GupAllocator *a) {
    GupHashmapShort hashmap = (GupHashmapShort) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayShort)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_short_create(a);
    }

    return hashmap;
}

GupHashmapString gup_hashmap_string_create(GupAllocator *a) {
    GupHashmapString hashmap = (GupHashmapString) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayString)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_string_create(a);
    }

    return hashmap;
}

GupHashmapCstr gup_hashmap_cstr_create(GupAllocator *a) {
    GupHashmapCstr hashmap = (GupHashmapCstr) {
        .capacity = GUP_HASHMAP_DEFAULT_CAPACITY,
        .keys     = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
        .values   = gup_alloc(a, GUP_HASHMAP_DEFAULT_CAPACITY * sizeof(GupArrayCstr)),
    };

    for (int i = 0; i < hashmap.capacity; i++) {
        hashmap.keys[i]   = gup_array_cstr_create(a);
        hashmap.values[i] = gup_array_cstr_create(a);
    }

    return hashmap;
}

// Destroy
void gup_hashmap_bool_destroy(GupHashmapBool hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_bool_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_char_destroy(GupHashmapChar hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_char_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_double_destroy(GupHashmapDouble hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_double_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_float_destroy(GupHashmapFloat hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_float_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_int_destroy(GupHashmapInt hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_int_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_long_destroy(GupHashmapLong hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_long_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_ptr_destroy(GupHashmapPtr hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_ptr_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_short_destroy(GupHashmapShort hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_short_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_string_destroy(GupHashmapString hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_string_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

void gup_hashmap_cstr_destroy(GupHashmapCstr hashmap) {
    for (int i = 0; i < hashmap.capacity; i++) {
        gup_array_cstr_destroy(hashmap.keys[i]);
        gup_array_cstr_destroy(hashmap.values[i]);
    }
    free(hashmap.keys);
    free(hashmap.values);
}

// Get
bool gup_hashmap_bool_get(GupHashmapBool hashmap, char *key, bool *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_char_get(GupHashmapChar hashmap, char *key, char *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_double_get(GupHashmapDouble hashmap, char *key, double *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_float_get(GupHashmapFloat hashmap, char *key, float *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_int_get(GupHashmapInt hashmap, char *key, int *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_long_get(GupHashmapLong hashmap, char *key, long *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_ptr_get(GupHashmapPtr hashmap, char *key, void* *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_short_get(GupHashmapShort hashmap, char *key, short *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_string_get(GupHashmapString hashmap, char *key, GupString *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

bool gup_hashmap_cstr_get(GupHashmapCstr hashmap, char *key, char * *out) {
    const int index = _gup_hash_cstr_index(key, hashmap.capacity);
    
    for (int i = 0; i < hashmap.keys[index].count; i++) {
        if (strcmp(hashmap.keys[index].data[i], key) == 0) {
            *out = hashmap.values[index].data[i];
            return true;
        }
    }

    return false;
}

// Set
void gup_hashmap_bool_set(GupAllocator *a, GupHashmapBool *hashmap, char *key, bool value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_bool_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_char_set(GupAllocator *a, GupHashmapChar *hashmap, char *key, char value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_char_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_double_set(GupAllocator *a, GupHashmapDouble *hashmap, char *key, double value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_double_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_float_set(GupAllocator *a, GupHashmapFloat *hashmap, char *key, float value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_float_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_int_set(GupAllocator *a, GupHashmapInt *hashmap, char *key, int value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_int_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_long_set(GupAllocator *a, GupHashmapLong *hashmap, char *key, long value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_long_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_ptr_set(GupAllocator *a, GupHashmapPtr *hashmap, char *key, void* value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_ptr_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_short_set(GupAllocator *a, GupHashmapShort *hashmap, char *key, short value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_short_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_string_set(GupAllocator *a, GupHashmapString *hashmap, char *key, GupString value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_string_append(a, &(hashmap->values[index]), value);
}

void gup_hashmap_cstr_set(GupAllocator *a, GupHashmapCstr *hashmap, char *key, char *value) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    if (gup_array_cstr_contains(hashmap->keys[index], key)) return;

    gup_array_cstr_append(a, &(hashmap->keys[index]), key);
    gup_array_cstr_append(a, &(hashmap->values[index]), value);
}

// Remove
void gup_hashmap_bool_remove(GupHashmapBool *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    bool value = false;
    if (!gup_hashmap_bool_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_bool_remove_all(&(hashmap->values[index]), value);
}

void gup_hashmap_char_remove(GupHashmapChar *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    char value = '\0';
    if (!gup_hashmap_char_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_char_remove_all(&(hashmap->values[index]), value);
}

void gup_hashmap_double_remove(GupHashmapDouble *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    double value = 0;
    if (!gup_hashmap_double_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_double_remove_all(&(hashmap->values[index]), value);
}

void gup_hashmap_float_remove(GupHashmapFloat *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    float value = 0;
    if (!gup_hashmap_float_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_float_remove_all(&(hashmap->values[index]), value);
}

void gup_hashmap_int_remove(GupHashmapInt *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    int value = 0;
    if (!gup_hashmap_int_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_int_remove_all(&(hashmap->values[index]), value);
}

void gup_hashmap_long_remove(GupHashmapLong *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    long value = 0;
    if (!gup_hashmap_long_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_long_remove_all(&(hashmap->values[index]), value);
}

void gup_hashmap_short_remove(GupHashmapShort *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    short value = 0;
    if (!gup_hashmap_short_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_short_remove_all(&(hashmap->values[index]), value);
}

void gup_hashmap_string_remove(GupHashmapString *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    GupString value = {0};
    if (!gup_hashmap_string_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_string_remove_all(&(hashmap->values[index]), value);
}

void gup_hashmap_cstr_remove(GupHashmapCstr *hashmap, char *key) {
    const int index = _gup_hash_cstr_index(key, hashmap->capacity);

    char *value = NULL;
    if (!gup_hashmap_cstr_get(*hashmap, key, &value)) return;

    gup_array_cstr_remove_all(&(hashmap->keys[index]), key);
    gup_array_cstr_remove_all(&(hashmap->values[index]), value);
}

// Size
int gup_hashmap_bool_size(GupHashmapBool hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_char_size(GupHashmapChar hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_double_size(GupHashmapDouble hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_float_size(GupHashmapFloat hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_int_size(GupHashmapInt hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_long_size(GupHashmapLong hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_ptr_size(GupHashmapPtr hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_short_size(GupHashmapShort hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_string_size(GupHashmapString hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

int gup_hashmap_cstr_size(GupHashmapCstr hashmap) {
    int size = 0;
    
    for (int i = 0; i < hashmap.capacity; i++) {
        size += hashmap.keys[i].count;
    }

    return size;
}

// Print
#define gup_hashmap_bool_print(hashmap) _gup_hashmap_bool_print(hashmap, #hashmap)
void _gup_hashmap_bool_print(GupHashmapBool hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%d,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

#define gup_hashmap_char_print(hashmap) _gup_hashmap_char_print(hashmap, #hashmap)
void _gup_hashmap_char_print(GupHashmapChar hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%c,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

#define gup_hashmap_double_print(hashmap) _gup_hashmap_double_print(hashmap, #hashmap)
void _gup_hashmap_double_print(GupHashmapDouble hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%f,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

#define gup_hashmap_float_print(hashmap) _gup_hashmap_float_print(hashmap, #hashmap)
void _gup_hashmap_float_print(GupHashmapFloat hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%f,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

#define gup_hashmap_int_print(hashmap) _gup_hashmap_int_print(hashmap, #hashmap)
void _gup_hashmap_int_print(GupHashmapInt hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%d,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

#define gup_hashmap_long_print(hashmap) _gup_hashmap_long_print(hashmap, #hashmap)
void _gup_hashmap_long_print(GupHashmapLong hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%ld,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

#define gup_hashmap_ptr_print(hashmap) _gup_hashmap_ptr_print(hashmap, #hashmap)
void _gup_hashmap_ptr_print(GupHashmapPtr hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%p,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

#define gup_hashmap_short_print(hashmap) _gup_hashmap_short_print(hashmap, #hashmap)
void _gup_hashmap_short_print(GupHashmapShort hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%hd,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

#define gup_hashmap_string_print(hashmap) _gup_hashmap_string_print(hashmap, #hashmap)
void _gup_hashmap_string_print(GupHashmapString hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": \"", hashmap.keys[i].data[j]);
            for (int k = 0; k < hashmap.values[i].data[j].count; k++) {
                printf("%c", hashmap.values[i].data[j].data[k]);
            }
            printf("\",\n");
        }
    }
    printf("}\n");
}

#define gup_hashmap_cstr_print(hashmap) _gup_hashmap_cstr_print(hashmap, #hashmap)
void _gup_hashmap_cstr_print(GupHashmapCstr hashmap, const char *hashmap_name) {    
    printf("%s: {\n", hashmap_name);
    for (int i = 0; i < hashmap.capacity; i++) {
        for (int j = 0; j < hashmap.keys[i].count; j++) {
            printf("  \"%s\": ", hashmap.keys[i].data[j]);
            printf("%s,\n", hashmap.values[i].data[j]);
        }
    }
    printf("}\n");
}

// Debug
#define gup_hashmap_bool_debug(hashmap) _gup_hashmap_bool_debug(hashmap, #hashmap)
void _gup_hashmap_bool_debug(GupHashmapBool hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_char_debug(hashmap) _gup_hashmap_char_debug(hashmap, #hashmap)
void _gup_hashmap_char_debug(GupHashmapChar hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_double_debug(hashmap) _gup_hashmap_double_debug(hashmap, #hashmap)
void _gup_hashmap_double_debug(GupHashmapDouble hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_float_debug(hashmap) _gup_hashmap_float_debug(hashmap, #hashmap)
void _gup_hashmap_float_debug(GupHashmapFloat hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_int_debug(hashmap) _gup_hashmap_int_debug(hashmap, #hashmap)
void _gup_hashmap_int_debug(GupHashmapInt hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_long_debug(hashmap) _gup_hashmap_long_debug(hashmap, #hashmap)
void _gup_hashmap_long_debug(GupHashmapLong hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_ptr_debug(hashmap) _gup_hashmap_ptr_debug(hashmap, #hashmap)
void _gup_hashmap_ptr_debug(GupHashmapPtr hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_short_debug(hashmap) _gup_hashmap_short_debug(hashmap, #hashmap)
void _gup_hashmap_short_debug(GupHashmapShort hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_string_debug(hashmap) _gup_hashmap_string_debug(hashmap, #hashmap)
void _gup_hashmap_string_debug(GupHashmapString hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

#define gup_hashmap_cstr_debug(hashmap) _gup_hashmap_cstr_debug(hashmap, #hashmap)
void _gup_hashmap_cstr_debug(GupHashmapCstr hashmap, const char *hashmap_name) {
    printf("%s: {\n", hashmap_name);
    printf("  capacity: %d\n", hashmap.capacity);
    printf("  keys:     %p\n", (void *)(hashmap.keys));
    printf("  values:   %p\n", (void *)(hashmap.values));
    printf("}\n");
}

// Print -------------------------------------------------------------------------------------------

void gup_print_cwd(void) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
}

void gup_print_string(const char *string) {
    printf("\"%s\"\n", string);
}

// Print array slices ------------------------------------------------------------------------------

void gup_print_array_slice_bool(bool array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        if (array[i] == true) {
            printf("true");
        } else {
            printf("false");
        }

        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_char(char array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("'%c'", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_double(double array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("%.17f", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_float(float array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("%f", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_int(int array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("%d", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_long(long array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("%ld", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

// Settings ----------------------------------------------------------------------------------------

bool gup_settings_get_cstr(GupAllocator *a, const char *key, GupString *out) {
    return gup_settings_get_cstr_from_file(a, key, "src/settings.txt", out);
}

bool gup_settings_get_cstr_from_file(GupAllocator *a, const char *key, const char *file_path, GupString *out) {
    GupArrayString tokens;
    GupArrayString file_lines = gup_file_read_lines(a, file_path);

    for (int i = 0; i < file_lines.count; i++) {
        GupString line = file_lines.data[i];
        tokens = gup_string_split(a, line, '=');

        // If we have two tokens, we define that as a key-value pair.
        if (tokens.count == 2) {
            GupString line_key = tokens.data[0];
            GupString line_value = tokens.data[1];

            if (gup_string_equals_cstr(line_key, key)) {
                *out = gup_string_copy(a, line_value);
                return true;
            }
        }
    }

    return false;
}

// bool gup_settings_set(const char *key, const char *value) {}

// bool gup_settings_set_to_file(const char *key, const char *value, const char *file_path) {}

// C-string utilities ------------------------------------------------------------------------------

// Assumes a null terminated string.
void _gup_cstr_print(const char *cstr, const char *display_name) {
    printf("%s: \"", display_name);
    
    for (int i = 0; cstr[i] != '\0'; i++) {
        printf("%c", cstr[i]);
    }

    printf("\"\n");
}

#define gup_cstr_print(cstr) _gup_cstr_print(cstr, #cstr)

// Assumes a null terminated array of strings.
char *gup_cstr_array_flatten(GupAllocator *a, char **strings) {
    // Calculate the total length of all the strings.
    int total_length = 0;
    for (int i = 0; strings[i] != NULL; i++) {
        total_length += strlen(strings[i]);
    }

    // Allocate a new buffer to hold the flattened string.
    char *result = gup_alloc(a, total_length + 1);
    if (result == NULL) return NULL;

    // Copy each string into the buffer.
    int offset = 0;
    for (int i = 0; strings[i] != NULL; i++) {
        strcpy(result + offset, strings[i]);
        offset += strlen(strings[i]);
    }

    // Add a null terminator to the end of the buffer.
    result[total_length] = '\0';

    return result;
}

// Assumes a null terminated string. Excludes the null terminator from the returned length.
int gup_cstr_length_excluding_null(const char *cstr) {
    int i = 0;
    while (cstr[i] != '\0') {
        i++;
    }
    return i;
}

// Assumes a null terminated string.
int gup_cstr_length_including_null(const char *cstr) {
    int i = 0;
    while (cstr[i] != '\0') {
        i++;
    }
    return i + 1;
}

// Assumes null terminated strings
bool gup_cstr_equals(const char *a, const char* b) {
    if (gup_cstr_length_excluding_null(a) != gup_cstr_length_excluding_null(b)) {
        return false;
    }

    for (int i = 0; i < gup_cstr_length_excluding_null(a); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

/**
 * Assumes null terminated "from" string.
 * Assumes "to" has enough memory allocated to fit "from".
 * Null terminates the "to" string.
 */
 void gup_cstr_copy(char *to, const char *from) {
    const int from_len = gup_cstr_length_including_null(from);

    for (int i = 0; i < from_len; i++) {
        to[i] = from[i];
    }
}

/**
 * Assumes "to" has enough memory allocatd for for n+1 characters (+1 for the null terminator).
 * Null terminates the "to" string.
 * ```
 * char *to = gup_alloc(a, 6);
 * gup_cstr_copy_n(a, to, "Hello World", 5);
 * ```
 * this would result with `to` pointing to a chunk of memory with the contents 'H''e''l''l''o''\0'.
 */
void gup_cstr_copy_n(char *to, const char *from, int n) {
    for (int i = 0; i < n; i++) {
        to[i] = from[i];
    }
    to[n] = '\0';
}

// Math ----------------------------------------------------------------------------------------------------------------

inline u8 gup_pow_u8(u8 x, u8 y) {
    u8 result = 1;
    for (u8 i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

inline i8 gup_pow_i8(i8 x, i8 y) {
    i8 result = 1;
    for (i8 i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

inline u16 gup_pow_u16(u16 x, u16 y) {
    u16 result = 1;
    for (u16 i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

inline i16 gup_pow_i16(i16 x, i16 y) {
    i16 result = 1;
    for (i16 i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

inline u32 gup_pow_u32(u32 x, u32 y) {
    u32 result = 1;
    for (u32 i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

inline i32 gup_pow_i32(i32 x, i32 y) {
    i32 result = 1;
    for (i32 i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

inline u64 gup_pow_u64(u64 x, u64 y) {
    u64 result = 1;
    for (u64 i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

inline i64 gup_pow_i64(i64 x, i64 y) {
    i64 result = 1;
    for (i64 i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

inline f32 gup_pow_f32(f32 x, f32 y) {
    f32 result = 1;
    for (f32 f = 0; f < y; f++) {
        result *= x;
    }
    return result;
}

inline f64 gup_pow_f64(f64 x, f64 y) {
    f64 result = 1;
    for (f64 f = 0; f < y; f++) {
        result *= x;
    }
    return result;
}


// Miscellaneous -----------------------------------------------------------------------------------

// TODO: DRY this up?
double gup_operation_seconds(void (*fn)()) {
    clock_t start, end;
    double cpu_seconds_used;

    start = clock();

    fn();

    end = clock();
    
    cpu_seconds_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    #ifdef GUPPY_VERBOSE
    printf("The operation took %f seconds to execute.\n", cpu_seconds_used);
    #endif // GUPPY_VERBOSE

    return cpu_seconds_used;
}

double gup_operation_seconds_verbose(void (*fn)()) {
    double result = gup_operation_seconds(fn);
    printf("The operation took %f seconds to execute.\n", result);

    return result;
}

// -1 means the character was not an int.
int gup_char_to_int(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default:  return -1;
    }
}

u32 gup_fnv1a_hash(const char* str) {
    u32 hash = 2166136261; // FNV-1a initial hash value
    u32 prime = 16777219; // FNV-1a prime number

    while (*str != '\0') {
        hash = (hash ^ *str) * prime;
        str++;
    }

    gup_assert_verbose(hash >= 0, "Got a negative hash from FNV-1a");
    return hash;
}

#endif // GUPPY_IMPLEMENTATION
#endif // GUPPY_H_
