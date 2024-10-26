#ifndef GUPPY_H_
#define GUPPY_H_

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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
    void **data;
} GupArrayPtr;

// TODO: is there a way to have an interface for an allocator maybe?
typedef GupArrayPtr GupArena;

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

// Arena -------------------------------------------------------------------------------------------
GupArena  gup_arena_create();
void      gup_arena_destroy(GupArena a); // Free all the allocated memory and the arena itself
void     *gup_arena_alloc(GupArena *a, size_t bytes);
void      gup_arena_free(GupArena *a); // Free all the allocated memory, but not the arena itself

// Dynamic arrays ----------------------------------------------------------------------------------
GupArrayBool   gup_array_bool_create();
GupArrayBool   gup_array_bool_create_arena(GupArena *a);
void           gup_array_bool_destroy(GupArrayBool xs);
GupArrayBool   gup_array_bool_create_from_array(bool xs[], const int size);
GupArrayBool   gup_array_bool_create_from_array_arena(GupArena *a, bool xs[], const int size);
GupArrayBool   gup_array_bool_copy(GupArrayBool xs);
GupArrayBool   gup_array_bool_copy_arena(GupArena *a, GupArrayBool xs);
bool           gup_array_bool_eq(GupArrayBool xs, GupArrayBool ys);
bool           gup_array_bool_eq_arena(GupArena *a, GupArrayBool xs, GupArrayBool ys);
bool           gup_array_bool_contains(GupArrayBool xs, bool x);
void           gup_array_bool_print(GupArrayBool xs);
void           gup_array_bool_print_arena(GupArena *a, GupArrayBool xs);
void           gup_array_bool_append(GupArrayBool *xs, bool x);
void           gup_array_bool_append_arena(GupArena *a, GupArrayBool *xs, bool x);
void           gup_array_bool_prepend(GupArrayBool *xs, bool x);
void           gup_array_bool_prepend_arena(GupArena *a, GupArrayBool *xs, bool x);
GupArrayBool   gup_array_bool_map(GupArrayBool xs, bool (*fn)(bool));
GupArrayBool   gup_array_bool_map_arena(GupArena *a, GupArrayBool xs, bool (*fn)(bool));
void           gup_array_bool_map_in_place(GupArrayBool *xs, bool (*fn)(bool));
void           gup_array_bool_map_in_place_arena(GupArena *a, GupArrayBool *xs, bool (*fn)(bool));
GupArrayBool   gup_array_bool_filter(GupArrayBool xs, bool (*fn)(bool));
GupArrayBool   gup_array_bool_filter_arena(GupArena *a, GupArrayBool xs, bool (*fn)(bool));
void           gup_array_bool_filter_in_place(GupArrayBool *xs, bool (*fn)(bool));
void           gup_array_bool_filter_in_place_arena(GupArena *a, GupArrayBool *xs, bool (*fn)(bool));
bool           gup_array_bool_reduce(GupArrayBool xs, bool (*fn)(bool, bool), bool start);
bool           gup_array_bool_reduce_arena(GupArena *a, GupArrayBool xs, bool (*fn)(bool, bool), bool start);
bool           gup_array_bool_find(GupArrayBool xs, bool (*fn)(bool), bool *out);
bool           gup_array_bool_find_arena(GupArena *a, GupArrayBool xs, bool (*fn)(bool), bool *out);
   
GupArrayChar   gup_array_char_create();
GupArrayChar   gup_array_char_create_arena(GupArena *a);
void           gup_array_char_destroy(GupArrayChar xs);
GupArrayChar   gup_array_char_create_from_array(char xs[], const int size);
GupArrayChar   gup_array_char_create_from_cstr(char xs[]);
GupArrayChar   gup_array_char_create_from_cstr_arena(GupArena *a, char xs[]);
GupArrayChar   gup_array_char_copy(GupArrayChar xs);
bool           gup_array_char_eq(GupArrayChar xs, GupArrayChar ys);
bool           gup_array_char_eq_cstr(GupArrayChar xs, const char *cstr, int cstr_length);
bool           gup_array_char_contains(GupArrayChar xs, char x);
void           gup_array_char_print(GupArrayChar xs);
void           gup_array_char_append(GupArrayChar *xs, char x);
void           gup_array_char_append_arena(GupArena *a, GupArrayChar *xs, char x);
void           gup_array_char_prepend(GupArrayChar *xs, char x);
void           gup_array_char_prepend_arena(GupArena *a, GupArrayChar *xs, char x);
GupArrayChar   gup_array_char_map(GupArrayChar xs, char (*fn)(char));
void           gup_array_char_map_in_place(GupArrayChar *xs, char (*fn)(char));
GupArrayChar   gup_array_char_filter(GupArrayChar xs, bool (*fn)(char));
GupArrayChar   gup_array_char_filter_arena(GupArena *a, GupArrayChar xs, bool (*fn)(char));
void           gup_array_char_filter_in_place(GupArrayChar *xs, bool (*fn)(char));
char           gup_array_char_reduce(GupArrayChar xs, char (*fn)(char, char), char start);
bool           gup_array_char_find(GupArrayChar xs, bool (*fn)(char), char *out);
char          *gup_array_char_to_cstr(GupArrayChar chars);
char          *gup_array_char_to_cstr_arena(GupArena *a, GupArrayChar chars);
char         **gup_array_string_to_cstrs(GupArrayString strs);
char         **gup_array_string_to_cstrs_arena(GupArena *a, GupArrayString strs);
   
GupArrayDouble gup_array_double_create();
GupArrayDouble gup_array_double_create_arena(GupArena *a);
void           gup_array_double_destroy(GupArrayDouble xs);
GupArrayDouble gup_array_double_create_from_array(double xs[], const int size);
GupArrayDouble gup_array_double_copy(GupArrayDouble xs);
bool           gup_array_double_eq(GupArrayDouble xs, GupArrayDouble ys);
bool           gup_array_double_contains(GupArrayDouble xs, double x);
void           gup_array_double_print(GupArrayDouble xs);
void           gup_array_double_append(GupArrayDouble *xs, double x);
void           gup_array_double_prepend(GupArrayDouble *xs, double x);
GupArrayDouble gup_array_double_map(GupArrayDouble xs, double (*fn)(double));
void           gup_array_double_map_in_place(GupArrayDouble *xs, double (*fn)(double));
GupArrayDouble gup_array_double_filter(GupArrayDouble xs, bool (*fn)(double));
void           gup_array_double_filter_in_place(GupArrayDouble *xs, bool (*fn)(double));
double         gup_array_double_reduce(GupArrayDouble xs, double (*fn)(double, double), double start);
bool           gup_array_double_find(GupArrayDouble xs, bool (*fn)(double), double *out);
   
GupArrayFloat  gup_array_float_create();
GupArrayFloat gup_array_float_create_arena(GupArena *a);
void           gup_array_float_destroy(GupArrayFloat xs);
GupArrayFloat  gup_array_float_create_from_array(float xs[], const int size);
GupArrayFloat  gup_array_float_copy(GupArrayFloat xs);
bool           gup_array_float_eq(GupArrayFloat xs, GupArrayFloat ys);
bool           gup_array_float_contains(GupArrayFloat xs, float x);
void           gup_array_float_print(GupArrayFloat xs);
void           gup_array_float_append(GupArrayFloat *xs, float x);
void           gup_array_float_prepend(GupArrayFloat *xs, float x);
GupArrayFloat  gup_array_float_map(GupArrayFloat xs, float (*fn)(float));
void           gup_array_float_map_in_place(GupArrayFloat *xs, float (*fn)(float));
GupArrayFloat  gup_array_float_filter(GupArrayFloat xs, bool (*fn)(float));
void           gup_array_float_filter_in_place(GupArrayFloat *xs, bool (*fn)(float));
float          gup_array_float_reduce(GupArrayFloat xs, float (*fn)(float, float), float start);
bool           gup_array_float_find(GupArrayFloat xs, bool (*fn)(float), float *out);

GupArrayInt    gup_array_int_create();
GupArrayInt    gup_array_int_create_arena(GupArena *a);
void           gup_array_int_destroy(GupArrayInt xs);
GupArrayInt    gup_array_int_create_from_array(int xs[], const int size);
GupArrayInt    gup_array_int_copy(GupArrayInt xs);
bool           gup_array_int_eq(GupArrayInt xs, GupArrayInt ys);
bool           gup_array_int_contains(GupArrayInt xs, int x);
void           gup_array_int_print(GupArrayInt xs);
void           gup_array_int_append(GupArrayInt *xs, int x);
void           gup_array_int_prepend(GupArrayInt *xs, int x);
GupArrayInt    gup_array_int_map(GupArrayInt xs, int (*fn)(int));
void           gup_array_int_map_in_place(GupArrayInt *xs, int (*fn)(int));
GupArrayInt    gup_array_int_filter(GupArrayInt xs, bool (*fn)(int));
void           gup_array_int_filter_in_place(GupArrayInt *xs, bool (*fn)(int));
int            gup_array_int_reduce(GupArrayInt xs, int (*fn)(int, int), int start);
bool           gup_array_int_find(GupArrayInt xs, bool (*fn)(int), int *out);

GupArrayLong   gup_array_long_create();
GupArrayLong   gup_array_long_create_arena(GupArena *a);
void           gup_array_short_destroy(GupArrayShort xs);
GupArrayLong   gup_array_long_create_from_array(long xs[], const int size);
GupArrayLong   gup_array_long_copy(GupArrayLong xs);
bool           gup_array_long_eq(GupArrayLong xs, GupArrayLong ys);
bool           gup_array_long_contains(GupArrayLong xs, long x);
void           gup_array_long_print(GupArrayLong xs);
void           gup_array_long_append(GupArrayLong *xs, long x);
void           gup_array_long_prepend(GupArrayLong *xs, long x);
GupArrayLong   gup_array_long_map(GupArrayLong xs, long (*fn)(long));
void           gup_array_long_map_in_place(GupArrayLong *xs, long (*fn)(long));
GupArrayLong   gup_array_long_filter(GupArrayLong xs, bool (*fn)(long));
void           gup_array_long_filter_in_place(GupArrayLong *xs, bool (*fn)(long));
long           gup_array_long_reduce(GupArrayLong xs, long (*fn)(long, long), long start);
bool           gup_array_long_find(GupArrayLong xs, bool (*fn)(long), long *out);

GupArrayPtr    gup_array_ptr_create();
GupArrayPtr    gup_array_ptr_create_arena(GupArena *a);
void           gup_array_ptr_destroy(GupArrayPtr xs);
GupArrayPtr    gup_array_ptr_create_from_array(void* xs[], const int size);
GupArrayPtr    gup_array_ptr_copy(GupArrayPtr xs);
bool           gup_array_ptr_eq(GupArrayPtr xs, GupArrayPtr ys);
bool           gup_array_ptr_contains(GupArrayPtr xs, void* x);
void           gup_array_ptr_print(GupArrayPtr xs);
void           gup_array_ptr_append(GupArrayPtr *xs, void* x);
void           gup_array_ptr_prepend(GupArrayPtr *xs, void* x);
GupArrayPtr    gup_array_ptr_map(GupArrayPtr xs, void* (*fn)(void*));
void           gup_array_ptr_map_in_place(GupArrayPtr *xs, void* (*fn)(void*));
GupArrayPtr    gup_array_ptr_filter(GupArrayPtr xs, bool (*fn)(void*));
void           gup_array_ptr_filter_in_place(GupArrayPtr *xs, bool (*fn)(void*));
void*          gup_array_ptr_reduce(GupArrayPtr xs, void* (*fn)(void*, void*), void* start);
bool           gup_array_ptr_find(GupArrayPtr xs, bool (*fn)(void*), void* *out);

GupArrayShort  gup_array_short_create();
GupArrayShort  gup_array_short_create_arena(GupArena *a);
void           gup_array_short_destroy(GupArrayShort xs);
GupArrayShort  gup_array_short_create_from_array(short xs[], const int size);
GupArrayShort  gup_array_short_copy(GupArrayShort xs);
bool           gup_array_short_eq(GupArrayShort xs, GupArrayShort ys);
bool           gup_array_short_contains(GupArrayShort xs, short x);
void           gup_array_short_print(GupArrayShort xs);
void           gup_array_short_append(GupArrayShort *xs, short x);
void           gup_array_short_prepend(GupArrayShort *xs, short x);
GupArrayShort  gup_array_short_map(GupArrayShort xs, short (*fn)(short));
void           gup_array_short_map_in_place(GupArrayShort *xs, short (*fn)(short));
GupArrayShort  gup_array_short_filter(GupArrayShort xs, bool (*fn)(short));
void           gup_array_short_filter_in_place(GupArrayShort *xs, bool (*fn)(short));
short          gup_array_short_reduce(GupArrayShort xs, short (*fn)(short, short), short start);
bool           gup_array_short_find(GupArrayShort xs, bool (*fn)(short), short *out);

GupArrayString gup_array_string_create();
GupArrayString gup_array_string_create_arena(GupArena *a);
void           gup_array_string_destroy(GupArrayString xs);
GupArrayString gup_array_string_create_from_array(GupString xs[], const int size);
GupArrayString gup_array_string_create_from_cstrs(char **cstrs, const int size);
GupArrayString gup_array_string_create_from_cstrs_arena(GupArena *a, char **cstrs, const int size);
GupArrayString gup_array_string_copy(GupArrayString xs);
bool           gup_array_string_eq(GupArrayString xs, GupArrayString ys);
bool           gup_array_string_contains(GupArrayString xs, GupString x);
void           gup_array_string_print(GupArrayString xs);
void           gup_array_string_append(GupArrayString *xs, GupString x);
void           gup_array_string_append_arena(GupArena *a, GupArrayString *xs, GupString x);
void           gup_array_string_append_cstr(GupArrayString *xs, char cstr[]);
void           gup_array_string_prepend(GupArrayString *xs, GupString x);
void           gup_array_string_prepend_cstr(GupArrayString *xs, char cstr[]);
GupArrayString gup_array_string_map(GupArrayString xs, GupString (*fn)(GupString));
void           gup_array_string_map_in_place(GupArrayString *xs, void (*fn)(GupString*));
GupArrayString gup_array_string_filter(GupArrayString xs, bool (*fn)(GupString));
void           gup_array_string_filter_in_place(GupArrayString *xs, bool (*fn)(GupString));
GupString      gup_array_string_reduce(GupArrayString xs, GupString (*fn)(GupString, GupString), GupString start);
bool           gup_array_string_find(GupArrayString xs, bool (*fn)(GupString), GupString *out);

// File operations ---------------------------------------------------------------------------------
bool             gup_file_create(const char *file_path);
bool             gup_file_delete(const char *file_path);
bool             gup_file_is_empty(const char *file_path);
int              gup_file_line_count(const char *file_path);
void             gup_file_print(const char *file_path);
void             gup_file_print_lines(const char *file_path);
GupString        gup_file_read(const char *file_path);
GupString        gup_file_read_arena(GupArena *a, const char *file_path);
char            *gup_file_read_as_cstr(const char *file_path);
char            *gup_file_read_as_cstr_arena(GupArena *a, const char *file_path);
GupArrayString   gup_file_read_lines(const char *file_path);
GupArrayString   gup_file_read_lines_arena(GupArena *a, const char *file_path);
char           **gup_file_read_lines_as_cstrs(const char *file_path);
char           **gup_file_read_lines_as_cstrs_arena(GupArena *a, const char *file_path);
GupArrayString   gup_file_read_lines_keep_newlines(const char *file_path);
GupArrayString   gup_file_read_lines_keep_newlines_arena(GupArena *a, const char *file_path);
char           **gup_file_read_lines_as_cstrs_keep_newlines(const char *file_path);
char           **gup_file_read_lines_as_cstrs_keep_newlines_arena(GupArena *a, const char *file_path);
long             gup_file_size(const char *file_path);
bool             gup_file_write(const char *text_to_write, const char *file_path);
bool             gup_file_write_lines(char **lines_to_write, const int line_count, const char *file_path);

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
bool gup_settings_get_cstr(const char *key, GupString *out);
bool gup_settings_get_cstr_arena(GupArena *a, const char *key, GupString *out);
bool gup_settings_get_cstr_from_file(const char *key, const char *file_path, GupString *out);
bool gup_settings_get_cstr_from_file_arena(GupArena *a, const char *key, const char *file_path, GupString *out);
bool gup_settings_set(const char *key, const char *value);
bool gup_settings_set_to_file(const char *key, const char *value, const char *file_path);

// Strings -------------------------------------------------------------------------------------
GupString      gup_string_create();
GupString      gup_string_create_arena(GupArena *a);
void           gup_string_destroy(GupString str);
GupString      gup_string_create_from_cstr(char str[]);
GupString      gup_string_create_from_cstr_arena(GupArena *a, char str[]); // Aliased as "gup_string"
GupString      gup_string_copy(GupString str);
GupString      gup_string_copy_arena(GupArena *a, GupString str);
bool           gup_string_eq(GupString str_a, GupString str_b);
bool           gup_string_eq_cstr(GupString str, const char *cstr, int cstr_length);
bool           gup_string_contains(GupString str, char c);
bool           gup_string_contains_substring(GupString str, GupString sub_str); // TODO: contains cstr
void           gup_string_print(GupString str);
void           gup_string_append(GupString *str, char c);
void           gup_string_append_arena(GupArena *a, GupString *str, char c);
void           gup_string_prepend(GupString *str, char c);
void           gup_string_prepend_arena(GupArena *a, GupString *str, char c);
GupString      gup_string_map(GupString str, char (*fn)(char));
GupString      gup_string_map_arena(GupArena *a, GupString str, char (*fn)(char));
void           gup_string_map_in_place(GupString str, char (*fn)(char));
GupString      gup_string_filter(GupString str, bool (*fn)(char));
GupString      gup_string_filter_arena(GupArena *a, GupString str, bool (*fn)(char));
void           gup_string_filter_in_place(GupString *str, bool (*fn)(char));
char           gup_string_reduce(GupString str, char (*fn)(char, char), char start);
bool           gup_string_find(GupString str, bool (*fn)(char), char *out);
bool           gup_string_find_arena(GupArena *a, GupString str, bool (*fn)(char), char *out);
GupString      gup_string_trim_char(GupString str, char c);
void           gup_string_trim_char_in_place(GupString *str, char c);
GupString      gup_string_trim_fn(GupString str, bool (*fn)(char));
GupString      gup_string_trim_fn_arena(GupArena *a, GupString str, bool (*fn)(char));
void           gup_string_trim_fn_in_place(GupString *str, bool (*fn)(char));
GupString      gup_string_without_whitespace(GupString str);
void           gup_string_without_whitespace_in_place(GupString *str);
bool           gup_string_starts_with(GupString str, GupString sub_str);
bool           gup_string_starts_with_cstr(GupString str, const char* cstr);
bool           gup_string_ends_with(GupString str, GupString sub_str);
bool           gup_string_ends_with_cstr(GupString str, const char* cstr);
bool           gup_string_to_int(GupString str, int *out);
// TODO: split by substring
GupArrayString gup_string_split(GupString str, char c);
GupArrayString gup_string_split_arena(GupArena *a, GupString str, char c);

// Assert
void gup_assert(bool pass_condition);
void gup_assert_verbose(bool pass_condition, const char *failure_explanation);

// C-string utilities
char *gup_cstr_array_flatten_arena(GupArena *a, char **strs); // Assumes a null terminated string.
int   gup_cstr_length(const char* cstr); // Assumes a null terminated string. Excludes the null from the length.
int   gup_cstr_length_including_null(const char* cstr); // Assumes a null terminated string. Excludes the null from the length.
bool  gup_cstr_eq(const char *a, const char* b);
void  gup_cstr_copy(char *to, const char *from);
void  gup_cstr_copy_n(char *to, const char *from, int n);
void  gup_cstr_print(const char *cstr);

// Miscellaneous
double gup_operation_seconds(void (*fn)());
double gup_operation_seconds(void (*fn)());
#define gup_array_len(a) sizeof(a)/sizeof(a[0]) 
#define gup_defer_return(r) do { result = (r); goto defer; } while (0)
#define GUP_RUN if (true)
#define GUP_SKIP if (false)
int gup_char_to_int(char c); // -1 means the character was not an int.

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

#define GUP_ARRAY_DEFAULT_CAPACITY 256

// Assert ------------------------------------------------------------------------------------------

void _gup_assert_verbose(bool pass_condition, const char *failure_explanation, const char *readable_pass_condition, const char *file_path, int line_number) {
    if (!pass_condition) {
        printf("[%s:%d] Failed assertion!\n", file_path, line_number);
        printf("---> %s <---\n", readable_pass_condition);
        printf("%s\n", failure_explanation);
        exit(1);
    }
}
#define gup_assert_verbose(pass_condition, failure_explanation) _gup_assert_verbose(pass_condition, failure_explanation, #pass_condition, __FILE__, __LINE__)

void _gup_assert(bool pass_condition, const char *readable_pass_condition, const char *file_path, int line_number) {
    if (!pass_condition) {
        printf("[%s:%d] Failed assertion!\n", file_path, line_number);
        printf("---> %s <---\n", readable_pass_condition);
        exit(1);
    }
}
#define gup_assert(pass_condition) _gup_assert(pass_condition, #pass_condition, __FILE__, __LINE__)

// Arena -------------------------------------------------------------------------------------------

GupArena gup_arena_create() {
    return (GupArena) {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(void*)),
    };
}

void gup_arena_destroy(GupArena a) {
    gup_arena_free(&a);
    free(a.data);
}

void *gup_arena_alloc(GupArena *a, size_t bytes) {
    if (a->count == a->capacity) {
        const int new_capacity = a->capacity == 0 ? 1 : a->capacity * 2;
        a->data = realloc(a->data, new_capacity * sizeof(void *));
        a->capacity = new_capacity;
    }

    void *ptr = malloc(bytes);
    gup_assert(ptr != NULL);

    a->data[a->count] = ptr;
    a->count++;

    return ptr;
}

void *_gup_arena_alloc(GupArena *a, size_t bytes, const char *file, int line) {
    printf("Allocation of %zu bytes from %s:%d\n", bytes, file, line);

    return gup_arena_alloc(a, bytes);
}

#ifdef GUPPY_VERBOSE
#define gup_arena_alloc(a, bytes) _gup_arena_alloc(a, bytes, __FILE__, __LINE__)
#endif // GUPPY_VERBOSE

void gup_arena_free(GupArena *a) {
    for (int i = 0; i < a->count; i++) {
        free(a->data[i]);
    }
    a->count = 0;
}

// Dynamic Arrays ----------------------------------------------------------------------------------

// Default constructors
GupArrayBool gup_array_bool_create() {
    GupArrayBool xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(bool)),
    };
    return xs;
}

GupArrayBool gup_array_bool_create_arena(GupArena *a) {
    GupArrayBool xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(bool)),
    };
    return xs;
}

GupArrayChar gup_array_char_create() {
    GupArrayChar xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(char)),
    };
    return xs;
}

GupArrayChar gup_array_char_create_arena(GupArena *a) {
    GupArrayChar xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(char)),
    };
    return xs;
}

GupArrayDouble gup_array_double_create() {
    GupArrayDouble xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(double)),
    };
    return xs;
}

GupArrayDouble gup_array_double_create_arena(GupArena *a) {
    GupArrayDouble xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(double)),
    };
    return xs;
}

GupArrayFloat gup_array_float_create() {
    GupArrayFloat xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(float)),
    };
    return xs;
}

GupArrayFloat gup_array_float_create_arena(GupArena *a) {
    GupArrayFloat xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(float)),
    };
    return xs;
}

GupArrayInt gup_array_int_create() {
    GupArrayInt xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(int)),
    };
    return xs;
}

GupArrayInt gup_array_int_create_arena(GupArena *a) {
    GupArrayInt xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(int)),
    };
    return xs;
}

GupArrayLong gup_array_long_create() {
    GupArrayLong xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(long)),
    };
    return xs;
}

GupArrayLong gup_array_long_create_arena(GupArena *a) {
    GupArrayLong xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(long)),
    };
    return xs;
}

GupArrayPtr gup_array_ptr_create() {
    GupArrayPtr xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(void*)),
    };
    return xs;
}

GupArrayPtr gup_array_ptr_create_arena(GupArena *a) {
    GupArrayPtr xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(void*)),
    };
    return xs;
}

GupArrayShort gup_array_short_create() {
    GupArrayShort xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(short)),
    };
    return xs;
}

GupArrayShort gup_array_short_create_arena(GupArena *a) {
    GupArrayShort xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(short)),
    };
    return xs;
}

GupArrayString gup_array_string_create() {  
    GupArrayString xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(GupArrayChar)),
    };
    return xs;
}

GupArrayString gup_array_string_create_arena(GupArena *a) {
    GupArrayString xs = {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = gup_arena_alloc(a, GUP_ARRAY_DEFAULT_CAPACITY * sizeof(GupArrayChar)),
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
    for (int i = 0; i < xs.count; i++) {
        free(xs.data[i]);
    }
    free(xs.data);
}

void gup_array_string_destroy(GupArrayString xs) {
    for (int i = 0; i < xs.count; i++) {
        gup_array_char_destroy(xs.data[i]);
    }
    free(xs.data);
}

// From constructors
GupArrayBool gup_array_bool_create_from_array(bool xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayBool new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = malloc(size_to_alloc * sizeof(bool)),
    };

    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayBool gup_array_bool_create_from_array_arena(GupArena *a, bool xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayBool new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = gup_arena_alloc(a, size_to_alloc * sizeof(bool)),
    };

    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayChar gup_array_char_create_from_array(char xs[], const int size) {
    GupArrayChar new = gup_array_char_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(char));
    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayChar gup_array_char_create_from_array_arena(GupArena *a, char xs[], const int size) {
    int size_to_alloc = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;

    GupArrayChar new = {
        .capacity = size_to_alloc,
        .count = size,
        .data = gup_arena_alloc(a, size_to_alloc * sizeof(char)),
    };

    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

#define gup_array_char_create_from_cstr(cstr) gup_array_char_create_from_array(cstr, strlen(cstr))
#define gup_array_char_create_from_cstr_arena(a, cstr) gup_array_char_create_from_array_arena(a, cstr, strlen(cstr))

GupArrayDouble gup_array_double_create_from_array(double xs[], const int size) {
    GupArrayDouble new = gup_array_double_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(double));
    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayFloat gup_array_float_create_from_array(float xs[], const int size) {
    GupArrayFloat new = gup_array_float_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(float));
    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayInt gup_array_int_create_from_array(int xs[], const int size) {
    GupArrayInt new = gup_array_int_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(int));
    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayLong gup_array_long_create_from_array(long xs[], const int size) {
    GupArrayLong new = gup_array_long_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(long));
    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayPtr gup_array_ptr_create_from_array(void* xs[], const int size) {
    GupArrayPtr new = gup_array_ptr_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(void*));
    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayShort gup_array_short_create_from_array(short xs[], const int size) {
    GupArrayShort new = gup_array_short_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(short));
    for (int i = 0; i < size; i++) {
       new.data[i] = xs[i];
    }

    return new;
}

GupArrayString gup_array_string_create_from_array(GupArrayChar xs[], const int size) {
    GupArrayString new = gup_array_string_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(GupArrayChar));
    for (int i = 0; i < size; i++) {
       new.data[i] = gup_array_char_copy(xs[i]);
    }

    return new;
}

GupArrayString gup_array_string_create_from_cstrs(char **xs, const int size) {
    GupArrayString new = gup_array_string_create();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(char **));
    for (int i = 0; i < size; i++) {
       new.data[i] = gup_array_char_create_from_cstr(xs[i]);
    }

    return new;
}

GupArrayString gup_array_string_create_from_cstrs_arena(GupArena *a, char **cstrs, const int size) {
    GupArrayString new = gup_array_string_create_arena(a);
    
    for (int i = 0; i < size; i++) {
        gup_array_string_append_arena(a, &new, gup_array_char_create_from_cstr_arena(a, cstrs[i]));
    }

    return new;
}

// Copy constructors
GupArrayBool gup_array_bool_copy(GupArrayBool xs) {
    GupArrayBool new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = malloc(xs.capacity * sizeof(bool)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(bool));

    return new;
}

GupArrayChar gup_array_char_copy(GupArrayChar xs) {
    GupArrayChar new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = malloc(xs.capacity * sizeof(char)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(char));

    return new;
}

GupArrayChar gup_array_char_copy_arena(GupArena *a, GupArrayChar xs) {
    GupArrayChar new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = gup_arena_alloc(a, xs.capacity * sizeof(char)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(char));

    return new;
}

GupArrayDouble gup_array_double_copy(GupArrayDouble xs) {
    GupArrayDouble new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = malloc(xs.capacity * sizeof(double)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(double));

    return new;
}

GupArrayFloat gup_array_float_copy(GupArrayFloat xs) {
    GupArrayFloat new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = malloc(xs.capacity * sizeof(float)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(float));

    return new;
}

GupArrayInt gup_array_int_copy(GupArrayInt xs) {
    GupArrayInt new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = malloc(xs.capacity * sizeof(int)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(int));

    return new;
}

GupArrayLong gup_array_long_copy(GupArrayLong xs) {
    GupArrayLong new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = malloc(xs.capacity * sizeof(long)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(long));

    return new;
}

GupArrayShort gup_array_short_copy(GupArrayShort xs) {
    GupArrayShort new = {
        .capacity = xs.capacity,
        .count = xs.count,
        .data = malloc(xs.capacity * sizeof(short)),

    };
    memcpy(new.data, xs.data, xs.count * sizeof(short));

    return new;
}

GupArrayPtr gup_array_ptr_copy(GupArrayPtr xs) {
    GupArrayPtr new = {
        .capacity = xs.capacity,
        .count = 0,
        .data = malloc(xs.capacity * sizeof(void*)),
    };
    for (int i = 0; i < xs.count; i++) {
        gup_array_ptr_append(&new, xs.data[i]);
    }

    return new;
}

GupArrayString gup_array_string_copy(GupArrayString xs) {
    GupArrayString new = {
        .capacity = xs.capacity,
        .count = 0,
        .data = malloc(xs.capacity * sizeof(GupString)),
    };
    for (int i = 0; i < xs.count; i++) {
        gup_array_string_append(&new, xs.data[i]);
    }

    return new;
}

// Equals
bool gup_array_bool_eq(GupArrayBool xs, GupArrayBool ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_char_eq(GupArrayChar xs, GupArrayChar ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

#define gup_array_char_eq_cstr(xs, cstr) _gup_array_char_eq_cstr(xs, cstr, strlen(cstr))
bool _gup_array_char_eq_cstr(GupArrayChar xs, const char *cstr, int cstr_length) {
    if (xs.count != cstr_length) return false;
    
    return strncmp(xs.data, cstr, xs.count) == 0;
}

bool gup_array_double_eq(GupArrayDouble xs, GupArrayDouble ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_float_eq(GupArrayFloat xs, GupArrayFloat ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_int_eq(GupArrayInt xs, GupArrayInt ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_long_eq(GupArrayLong xs, GupArrayLong ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_ptr_eq(GupArrayPtr xs, GupArrayPtr ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_short_eq(GupArrayShort xs, GupArrayShort ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] != ys.data[i]) return false;
    }

    return true;
}

bool gup_array_string_eq(GupArrayString xs, GupArrayString ys) {
    if (xs.count != ys.count) return false;

    for (int i = 0; i < xs.count; i++) {
        if (!gup_array_char_eq(xs.data[i], ys.data[i])) return false;
    }

    return true;
}

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
        if (gup_array_char_eq(xs.data[i], x)) {
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
    printf("%s: [\n", xs_name);
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

// Append
void gup_array_bool_append(GupArrayBool *xs, bool x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(bool));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_char_append(GupArrayChar *xs, char x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(char));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_char_append_arena(GupArena *a, GupArrayChar *xs, char x) {
    // TODO: extract arena_realloc
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        char *new_data = gup_arena_alloc(a, new_capacity * sizeof(char));
        for (int i = 0; i < xs->count; i++) {
            new_data[i] = xs->data[i];
        }
        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_double_append(GupArrayDouble *xs, double x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(double));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_float_append(GupArrayFloat *xs, float x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(float));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_int_append(GupArrayInt *xs, int x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(int));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_long_append(GupArrayLong *xs, long x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(long));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_ptr_append(GupArrayPtr *xs, void* x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(void*));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_short_append(GupArrayShort *xs, short x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(short));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_string_append(GupArrayString *xs, GupArrayChar x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(GupArrayChar));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = gup_array_char_copy(x);
    xs->count++;
}

void gup_array_string_append_arena(GupArena *a, GupArrayString *xs, GupArrayChar x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        GupArrayChar *new_data = gup_arena_alloc(a, new_capacity * sizeof(GupArrayChar));
        for (int i = 0; i < xs->count; i++) {
            new_data[i] = xs->data[i];
        }
        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = gup_array_char_copy_arena(a, x);
    xs->count++;
}

void gup_array_string_append_cstr(GupArrayString *xs, char *cstr) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(char *));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = gup_array_char_create_from_cstr(cstr);
    xs->count++;
}

// Prepend
void gup_array_bool_prepend(GupArrayBool *xs, bool x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(bool));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_char_prepend(GupArrayChar *xs, char x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(char));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_char_prepend_arena(GupArena *a, GupArrayChar *xs, char x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        char *new_data = gup_arena_alloc(a, new_capacity * sizeof(char));
        for (int i = 0; i < xs->count; i++) {
            new_data[i] = xs->data[i];
        }
        xs->data = new_data;
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_double_prepend(GupArrayDouble *xs, double x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(double));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_float_prepend(GupArrayFloat *xs, float x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(float));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_int_prepend(GupArrayInt *xs, int x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(int));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_long_prepend(GupArrayLong *xs, long x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(long));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_short_prepend(GupArrayShort *xs, short x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(short));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_ptr_prepend(GupArrayPtr *xs, void* x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(void*));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_string_prepend(GupArrayString *xs, GupArrayChar x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(GupArrayChar));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_string_prepend_cstr(GupArrayString *xs, char *cstr){
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(char *));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = gup_array_char_create_from_cstr(cstr);
    xs->count++;
}

// Map
GupArrayBool gup_array_bool_map(GupArrayBool xs, bool (*fn)(bool)) {
    GupArrayBool new = gup_array_bool_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

GupArrayChar gup_array_char_map(GupArrayChar xs, char (*fn)(char)) {
    GupArrayChar new = gup_array_char_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

GupArrayDouble gup_array_double_map(GupArrayDouble xs, double (*fn)(double)) {
    GupArrayDouble new = gup_array_double_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

GupArrayFloat gup_array_float_map(GupArrayFloat xs, float (*fn)(float)) {
    GupArrayFloat new = gup_array_float_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

GupArrayInt gup_array_int_map(GupArrayInt xs, int (*fn)(int)) {
    GupArrayInt new = gup_array_int_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

GupArrayLong gup_array_long_map(GupArrayLong xs, long (*fn)(long)) {
    GupArrayLong new = gup_array_long_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

GupArrayShort gup_array_short_map(GupArrayShort xs, short (*fn)(short)) {
    GupArrayShort new = gup_array_short_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

GupArrayPtr gup_array_ptr_map(GupArrayPtr xs, void* (*fn)(void*)) {
    GupArrayPtr new = gup_array_ptr_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

GupArrayString gup_array_string_map(GupArrayString xs, GupString (*fn)(GupString)) {
    GupArrayString new = gup_array_string_create_from_array(xs.data, xs.count);

    for (int i = 0; i < xs.count; i++) {
        new.data[i] = fn(xs.data[i]);
    }

    return new;
}

// Map in place
void gup_array_bool_map_in_place(GupArrayBool *xs, bool (*fn)(bool)) {
    for (int i = 0; i < xs->count; i++) {
        xs->data[i] = fn(xs->data[i]);
    }
}

void gup_array_char_map_in_place(GupArrayChar *xs, char (*fn)(char)) {
    for (int i = 0; i < xs->count; i++) {
        xs->data[i] = fn(xs->data[i]);
    }
}

void gup_array_double_map_in_place(GupArrayDouble *xs, double (*fn)(double)) {
    for (int i = 0; i < xs->count; i++) {
        xs->data[i] = fn(xs->data[i]);
    }
}

void gup_array_float_map_in_place(GupArrayFloat *xs, float (*fn)(float)) {
    for (int i = 0; i < xs->count; i++) {
        xs->data[i] = fn(xs->data[i]);
    }
}

void gup_array_int_map_in_place(GupArrayInt *xs, int (*fn)(int)) {
    for (int i = 0; i < xs->count; i++) {
        xs->data[i] = fn(xs->data[i]);
    }
}

void gup_array_long_map_in_place(GupArrayLong *xs, long (*fn)(long)) {
    for (int i = 0; i < xs->count; i++) {
        xs->data[i] = fn(xs->data[i]);
    }
}

void gup_array_short_map_in_place(GupArrayShort *xs, short (*fn)(short)) {
    for (int i = 0; i < xs->count; i++) {
        xs->data[i] = fn(xs->data[i]);
    }
}

void gup_array_ptr_map_in_place(GupArrayPtr *xs, void* (*fn)(void*)) {
    for (int i = 0; i < xs->count; i++) {
        xs->data[i] = fn(xs->data[i]);
    }
}

void gup_array_string_map_in_place(GupArrayString *xs, void (*fn)(GupString*)) {
    for (int i = 0; i < xs->count; i++) {
        fn(&xs->data[i]);
    }
}

// Filter
GupArrayBool gup_array_bool_filter(GupArrayBool xs, bool (*fn)(bool)) {
    GupArrayBool new = gup_array_bool_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_bool_append(&new, xs.data[i]);
        }
    }

    return new;
}

GupArrayChar gup_array_char_filter(GupArrayChar xs, bool (*fn)(char)) {
    GupArrayChar new = gup_array_char_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_char_append(&new, xs.data[i]);
        }
    }

    return new;
}

GupArrayChar gup_array_char_filter_arena(GupArena *a, GupArrayChar xs, bool (*fn)(char)) {
    GupArrayChar new = gup_array_char_create_arena(a);

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_char_append_arena(a, &new, xs.data[i]);
        }
    }

    return new;
}

GupArrayDouble gup_array_double_filter(GupArrayDouble xs, bool (*fn)(double)) {
    GupArrayDouble new = gup_array_double_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_double_append(&new, xs.data[i]);
        }
    }

    return new;
}

GupArrayFloat gup_array_float_filter(GupArrayFloat xs, bool (*fn)(float)) {
    GupArrayFloat new = gup_array_float_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_float_append(&new, xs.data[i]);
        }
    }

    return new;
}

GupArrayInt gup_array_int_filter(GupArrayInt xs, bool (*fn)(int)) {
    GupArrayInt new = gup_array_int_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_int_append(&new, xs.data[i]);
        }
    }

    return new;
}

GupArrayLong gup_array_long_filter(GupArrayLong xs, bool (*fn)(long)) {
    GupArrayLong new = gup_array_long_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_long_append(&new, xs.data[i]);
        }
    }

    return new;
}

GupArrayShort gup_array_short_filter(GupArrayShort xs, bool (*fn)(short)) {
    GupArrayShort new = gup_array_short_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_short_append(&new, xs.data[i]);
        }
    }

    return new;
}

GupArrayPtr gup_array_ptr_filter(GupArrayPtr xs, bool (*fn)(void*)) {
    GupArrayPtr new = gup_array_ptr_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_ptr_append(&new, xs.data[i]);
        }
    }

    return new;
}

GupArrayString gup_array_string_filter(GupArrayString xs, bool (*fn)(GupArrayChar)) {
    GupArrayString new = gup_array_string_create();

    for (int i = 0; i < xs.count; i++) {
        if (fn(xs.data[i])) {
            gup_array_string_append(&new, xs.data[i]);
        }
    }

    return new;
}

// Filter in place
void gup_array_bool_filter_in_place(GupArrayBool *xs, bool (*fn)(bool)) {
    GupArrayBool new = gup_array_bool_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_bool_create_from_array(new.data, new.count);

    free(new.data);
}
    
void gup_array_char_filter_in_place(GupArrayChar *xs, bool (*fn)(char)) {
    GupArrayChar new = gup_array_char_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_char_create_from_array(new.data, new.count);

    free(new.data);
}
    
void gup_array_double_filter_in_place(GupArrayDouble *xs, bool (*fn)(double)) {
    GupArrayDouble new = gup_array_double_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_double_create_from_array(new.data, new.count);

    free(new.data);
}
    
void gup_array_float_filter_in_place(GupArrayFloat *xs, bool (*fn)(float)) {
    GupArrayFloat new = gup_array_float_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_float_create_from_array(new.data, new.count);

    free(new.data);
}
    
void gup_array_int_filter_in_place(GupArrayInt *xs, bool (*fn)(int)) {
    GupArrayInt new = gup_array_int_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_int_create_from_array(new.data, new.count);

    free(new.data);
}
    
void gup_array_long_filter_in_place(GupArrayLong *xs, bool (*fn)(long)) {
    GupArrayLong new = gup_array_long_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_long_create_from_array(new.data, new.count);

    free(new.data);
}
    
void gup_array_short_filter_in_place(GupArrayShort *xs, bool (*fn)(short)) {
    GupArrayShort new = gup_array_short_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_short_create_from_array(new.data, new.count);

    free(new.data);
}
    
void gup_array_ptr_filter_in_place(GupArrayPtr *xs, bool (*fn)(void*)) {
    GupArrayPtr new = gup_array_ptr_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_ptr_create_from_array(new.data, new.count);

    free(new.data);
}
    
void gup_array_string_filter_in_place(GupArrayString *xs, bool (*fn)(GupArrayChar)) {
    GupArrayString new = gup_array_string_filter(*xs, fn);

    free(xs->data);
    *xs = gup_array_string_create_from_array(new.data, new.count);

    free(new.data);
}

// Reduce
bool gup_array_reduce_bool(GupArrayBool xs, bool (*fn)(bool, bool), bool start) {
    bool result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
}

char gup_array_reduce_char(GupArrayChar xs, char (*fn)(char, char), char start) {
    char result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
}

double gup_array_reduce_double(GupArrayDouble xs, double (*fn)(double, double), double start) {
    double result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
}

float gup_array_reduce_float(GupArrayFloat xs, float (*fn)(float, float), float start) {
    float result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
}

int gup_array_reduce_int(GupArrayInt xs, int (*fn)(int, int), int start) {
    int result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
}

long gup_array_reduce_long(GupArrayLong xs, long (*fn)(long, long), long start) {
    long result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
}

short gup_array_reduce_short(GupArrayShort xs, short (*fn)(short, short), short start) {
    short result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
}

void* gup_array_reduce_ptr(GupArrayPtr xs, void* (*fn)(void*, void*), void* start) {
    void* result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
}

GupArrayChar gup_array_reduce_string(GupArrayString xs, GupArrayChar (*fn)(GupArrayChar, GupArrayChar), GupArrayChar start) {
    GupArrayChar result = start;
    for (int i = 0; i < xs.count; i++) {
        result = fn(result, xs.data[i]);
    }
    return result;
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
            *out = gup_array_char_copy(xs.data[i]);
            return true;
        }
    }

    return false;
}

// Miscellaneous

char *gup_array_char_to_cstr(GupArrayChar chars) {
    // count + 1 for null terminator
    char *result = malloc((chars.count + 1) * sizeof(char));
    
    for (int i = 0; i < chars.count; i++) {
        result[i] = chars.data[i];
    }
    result[chars.count] = '\0';

    return result;
}

char *gup_array_char_to_cstr_arena(GupArena *a, GupArrayChar chars) {
    // count + 1 for null terminator
    char *result = gup_arena_alloc(a, (chars.count + 1) * sizeof(char));
    
    for (int i = 0; i < chars.count; i++) {
        result[i] = chars.data[i];
    }
    result[chars.count] = '\0';

    return result;
}

char **gup_array_string_to_cstrs(GupArrayString strs) {
    // count + 1 for null terminator
    char **result = malloc((strs.count + 1) * sizeof(char *));

    for (int i = 0; i < strs.count; i++) {
        result[i] = gup_array_char_to_cstr(strs.data[i]);
    }
    result[strs.count] = NULL;

    return result;
}

char **gup_array_string_to_cstrs_arena(GupArena *a, GupArrayString strs) {
    // count + 1 for null terminator
    char **result = gup_arena_alloc(a, (strs.count + 1) * sizeof(char *));

    for (int i = 0; i < strs.count; i++) {
        result[i] = gup_array_char_to_cstr_arena(a, strs.data[i]);
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

void gup_file_print(const char *file_path) {
    printf("[%s]\n", file_path);
    char **file_lines = gup_file_read_lines_as_cstrs(file_path);
    if (file_lines == NULL) return;

    const int line_count = gup_file_line_count(file_path);
    for (int i = 0; i < line_count; i++) {
        if (file_lines[i] != NULL) {
            printf("%s\n", file_lines[i]);
            free(file_lines[i]);
        } else { // if there is an empty last line
            printf("\n");
        }
    }
    free(file_lines);
}

void gup_file_print_lines(const char *file_path) {
    printf("[%s]\n", file_path);
    char **file_lines = gup_file_read_lines_as_cstrs(file_path);
    if (file_lines == NULL) return;

    const int line_count = gup_file_line_count(file_path);
    for (int i = 0; i < line_count; i++) {
        if (file_lines[i] != NULL) { // 
            printf("%d %s\n", i+1, file_lines[i]);
            free(file_lines[i]);
        } else {
            // if there is an empty last line
            printf("%d", i+1);
        }
    }
    printf("\n");
    free(file_lines);
}

GupString gup_file_read(const char *file_path) {
    GupString result = {0};

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s: %s\n", file_path, strerror(errno));
        #endif
        return result;
    }

    long file_size = gup_file_size(file_path);
    char *buffer = (char *) malloc(file_size + 1);
    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);

    gup_assert_verbose((long)bytes_read == file_size, "Failed to read file");

    buffer[file_size] = '\0';
    result = gup_array_char_create_from_cstr(buffer);
    gup_defer_return(result);

defer:
    if (fp) fclose(fp);
    free(buffer);
    return result;
}

GupString gup_file_read_arena(GupArena *a, const char *file_path) {
    GupString result = {0};

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s: %s\n", file_path, strerror(errno));
        #endif
        return result;
    }

    long file_size = gup_file_size(file_path);
    char *buffer = (char *) gup_arena_alloc(a, file_size + 1);
    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);

    gup_assert_verbose((long)bytes_read == file_size, "Failed to read file");

    buffer[file_size] = '\0';
    result = gup_array_char_create_from_cstr_arena(a, buffer);
    gup_defer_return(result);

defer:
    if (fp) fclose(fp);
    return result;
}

char *gup_file_read_as_cstr(const char *file_path) {
    char *result;
    char *buffer;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        return NULL;
    }

    long file_size = gup_file_size(file_path);
    buffer = (char *) malloc(file_size + 1);

    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);
    if ((long)bytes_read != file_size) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to read file %s\n", file_path);
        #endif
        gup_defer_return(NULL);
    }
    buffer[file_size] = '\0';
    gup_defer_return(buffer);

defer:
    fclose(fp);
    return result;
}

char *gup_file_read_as_cstr_arena(GupArena *a, const char *file_path) {
    char *result;
    char *buffer;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        return NULL;
    }

    long file_size = gup_file_size(file_path);
    buffer = (char *) gup_arena_alloc(a, file_size + 1);

    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);
    if ((long)bytes_read != file_size) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to read file %s\n", file_path);
        #endif
        gup_defer_return(NULL);
    }
    buffer[file_size] = '\0';
    gup_defer_return(buffer);

defer:
    fclose(fp);
    return result;
}

void _remove_trailing_newline(GupString *str) {
    if (str->data[str->count-1] == '\n') {
        str->count--;
    }
}

// TODO: why doesn't this leak memory if I don't free it as a consumer?
GupArrayString gup_file_read_lines(const char *file_path) {
    GupArrayString result = gup_file_read_lines_keep_newlines(file_path);
    gup_array_string_map_in_place(&result, _remove_trailing_newline);
    return result;
}

GupArrayString gup_file_read_lines_arena(GupArena *a, const char *file_path) {
    GupArrayString result = gup_file_read_lines_keep_newlines_arena(a, file_path);
    gup_array_string_map_in_place(&result, _remove_trailing_newline);
    return result;
}

GupArrayString gup_file_read_lines_keep_newlines(const char *file_path) {
    GupArrayString result = {0};
    char *line_buffer = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(result);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(result);
    }

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) break;

        GupArrayChar line = gup_array_char_create_from_cstr(line_buffer);
        gup_array_string_append(&result, line);
        free(line.data);
    }

defer:
    free(line_buffer);
    if (fp) fclose(fp);

    return result;
}

GupArrayString gup_file_read_lines_keep_newlines_arena(GupArena *a, const char *file_path) {
    GupArrayString result = {0};
    char *line_buffer = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(result);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(result);
    }

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) break;

        GupArrayChar line = gup_array_char_create_from_cstr_arena(a, line_buffer);
        gup_array_string_append_arena(a, &result, line);
    }

defer:
    free(line_buffer);
    if (fp) fclose(fp);

    return result;
}

char **gup_file_read_lines_as_cstrs(const char *file_path) {
    GupArrayString lines = gup_array_string_create();
    char **result = NULL;
    char *line_buffer = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) {
            gup_defer_return(gup_array_string_to_cstrs(lines));
        }

        // In normal gup_read_file_lines we don't want to keep newlines.
        line_buffer[read-1] = '\0';
        GupArrayChar line = gup_array_char_create_from_cstr(line_buffer);
        gup_array_string_append(&lines, line);
        free(line.data);
    }

    gup_defer_return(gup_array_string_to_cstrs(lines));

defer:
    gup_array_string_destroy(lines);
    free(line_buffer);
    if (fp) fclose(fp);

    return result;
}

char **gup_file_read_lines_as_cstrs_arena(GupArena *a, const char *file_path) {
    GupArrayString lines = gup_array_string_create_arena(a );
    char **result = NULL;
    char *line_buffer = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) {
            gup_defer_return(gup_array_string_to_cstrs_arena(a, lines));
        }

        // In normal gup_read_file_lines we don't want to keep newlines.
        line_buffer[read-1] = '\0';
        GupArrayChar line = gup_array_char_create_from_cstr_arena(a, line_buffer);
        gup_array_string_append_arena(a, &lines, line);
    }

    gup_defer_return(gup_array_string_to_cstrs(lines));

defer:
    if (fp) fclose(fp);
    free(line_buffer);
    return result;
}

char **gup_file_read_lines_as_cstrs_keep_newlines(const char *file_path) {
    GupArrayString lines = {0};
    char **result = NULL;
    char *line_buffer = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) {
            gup_defer_return(gup_array_string_to_cstrs(lines));
        }

        GupArrayChar line = gup_array_char_create_from_cstr(line_buffer);
        gup_array_string_append(&lines, line);
        free(line.data);
    }

    gup_defer_return(gup_array_string_to_cstrs(lines));

defer:
    gup_array_string_destroy(lines);
    free(line_buffer);
    if (fp) fclose(fp);

    return result;
}

char **gup_file_read_lines_as_cstrs_keep_newlines_arena(GupArena *a, const char *file_path) {
    GupArrayString lines = {0};
    char **result = NULL;
    char *line_buffer = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) {
            gup_defer_return(gup_array_string_to_cstrs_arena(a, lines));
        }

        GupArrayChar line = gup_array_char_create_from_cstr_arena(a, line_buffer);
        gup_array_string_append_arena(a, &lines, line);
    }

    gup_defer_return(gup_array_string_to_cstrs_arena(a, lines));

defer:
    free(line_buffer);
    if (fp) fclose(fp);

    return result;
}

long gup_file_size(const char *file_path) {
    FILE *fp = fopen(file_path, "rb");
    char failure_reason[1024];
    sprintf(failure_reason, "Failed to open %s: %s", file_path, strerror(errno));
    gup_assert_verbose(fp != NULL, failure_reason);

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fclose(fp);

    return file_size;
}

bool gup_file_write(const char *text_to_write, const char *file_path) {
    bool result = true;

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        printf("Failed to open file %s\n", file_path);
        gup_defer_return(false);
    }

    fprintf(fp, "%s", text_to_write);

defer:
    fclose(fp);
    return result;
}

bool gup_file_write_lines(char **lines_to_write, const int line_count, const char *file_path) {
    bool result = true;

    if (!gup_file_delete(file_path)) {
        return false;
    }
    
    FILE *fp = fopen(file_path, "a");
    if (fp == NULL) {
        printf("Failed to open file %s\n", file_path);
        gup_defer_return(false);
    }

    for (int i = 0; i < line_count; i++) {
        fputs(lines_to_write[i], fp);
        fputs("\n", fp);
    }

defer:
    fclose(fp);
    return result;
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

// Strings -------------------------------------------------------------------------------------

#define gup_string_create gup_array_char_create
#define gup_string_create_arena gup_array_char_create_arena
#define gup_string_destroy gup_array_char_destroy
#define gup_string_create_from_cstr gup_array_char_create_from_cstr
#define gup_string_create_from_cstr_arena gup_array_char_create_from_cstr_arena
#define gup_string gup_string_create_from_cstr_arena
#define gup_string_copy gup_array_char_copy
#define gup_string_copy_arena gup_array_char_copy_arena
#define gup_string_eq gup_array_char_eq
#define gup_string_eq_cstr gup_array_char_eq_cstr
#define gup_string_contains gup_array_char_contains

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

#define gup_string_append gup_array_char_append
#define gup_string_append_arena gup_array_char_append_arena
#define gup_string_prepend gup_array_char_prepend
#define gup_string_prepend_arena gup_array_char_prepend_arena
#define gup_string_map gup_array_char_map
#define gup_string_map_in_place gup_array_char_map_in_place
#define gup_string_filter gup_array_char_filter
#define gup_string_filter_arena gup_array_char_filter_arena
#define gup_string_filter_in_place gup_array_char_filter_in_place
#define gup_string_reduce gup_array_char_reduce
#define gup_string_find gup_array_char_find

GupString gup_string_trim_char(GupString str, char c) {
    GupString trimmed_str = gup_string_copy(str);

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

GupString gup_string_trim_char_arena(GupArena *a, GupString str, char c) {
    GupString trimmed_str = gup_string_copy_arena(a, str);

    int i = 0;
    for (; i < trimmed_str.count && trimmed_str.data[i] == c; i++) {}
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

GupString gup_string_trim_fn(GupString str, bool (*fn)(char)) {
    GupString trimmed_str = gup_string_copy(str);

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

GupString gup_string_trim_fn_arena(GupArena *a, GupString str, bool (*fn)(char)) {
    GupString trimmed_str = gup_string_copy_arena(a, str);

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

bool is_not_whitespace(char c) {
    return !isspace(c);
}

GupString gup_string_without_whitespace(GupString str) {
    return gup_string_filter(str, is_not_whitespace);
}

void gup_string_without_whitespace_in_place(GupString *str) {
    gup_string_filter_in_place(str, is_not_whitespace);
}

GupArrayString gup_string_split(GupString str, char c) {
    GupArrayString tokens = gup_array_string_create();
    GupString token = gup_string_create();
    GupString trimmed = gup_string_trim_char(str, c);

    for (int i = 0; i < trimmed.count; i++) {
        if (trimmed.data[i] == c) {
            gup_array_string_append(&tokens, token);
            gup_string_destroy(token);
            token = gup_string_create();
        } else if (i == trimmed.count-1) {
            gup_string_append(&token, trimmed.data[i]);
            gup_array_string_append(&tokens, token);
            gup_string_destroy(token);
            token = gup_string_create();
        } else {
            gup_string_append(&token, trimmed.data[i]);
        }
    }

    gup_string_destroy(trimmed);
    gup_string_destroy(token);

    return tokens;
}

GupArrayString gup_string_split_arena(GupArena *a, GupString str, char c) {
    GupArrayString tokens = gup_array_string_create_arena(a);
    GupString token = gup_string_create_arena(a);
    GupString trimmed = gup_string_trim_char_arena(a, str, c);

    for (int i = 0; i < trimmed.count; i++) {
        if (trimmed.data[i] == c) {
            gup_array_string_append_arena(a, &tokens, token);
            token = gup_string_create_arena(a);
        } else if (i == trimmed.count-1) {
            gup_string_append(&token, trimmed.data[i]);
            gup_array_string_append_arena(a, &tokens, token);
            token = gup_string_create_arena(a);
        } else {
            gup_string_append(&token, trimmed.data[i]);
        }
    }

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
    const int cstr_len = gup_cstr_length(cstr);

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
    const int cstr_len = gup_cstr_length(cstr);

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
        const int char_as_int = gup_char_to_int(str.data[i]) * pow(10, j);
        if (char_as_int == -1) {
            return false;
        }
        result += char_as_int;
    }

    *out = result;
    return true;
}

// Settings ----------------------------------------------------------------------------------------

bool gup_settings_get_cstr(const char *key, GupString *out) {
    return gup_settings_get_cstr_from_file(key, "src/settings.txt", out);
}

bool gup_settings_get_cstr_arena(GupArena *a, const char *key, GupString *out) {
    return gup_settings_get_cstr_from_file_arena(a, key, "src/settings.txt", out);
}

bool gup_settings_get_cstr_from_file(const char *key, const char *file_path, GupString *out) {
    bool result = false;
    GupArrayString tokens;
    GupArrayString file_lines = gup_file_read_lines(file_path);

    for (int i = 0; i < file_lines.count; i++) {
        GupString line = file_lines.data[i];
        tokens = gup_string_split(line, '=');

        // If we have two tokens, we define that as a key-value pair.
        if (tokens.count == 2) {
            GupString line_key = tokens.data[0];
            GupString line_value = tokens.data[1];

            if (gup_string_eq_cstr(line_key, key)) {
                *out = gup_string_copy(line_value);
                gup_defer_return(true);
            }
        }
    }

defer:
    gup_array_string_destroy(tokens);
    gup_array_string_destroy(file_lines);
    return result;
}

bool gup_settings_get_cstr_from_file_arena(GupArena *a, const char *key, const char *file_path, GupString *out) {
    GupArrayString tokens;
    GupArrayString file_lines = gup_file_read_lines_arena(a, file_path);

    for (int i = 0; i < file_lines.count; i++) {
        GupString line = file_lines.data[i];
        tokens = gup_string_split_arena(a, line, '=');

        // If we have two tokens, we define that as a key-value pair.
        if (tokens.count == 2) {
            GupString line_key = tokens.data[0];
            GupString line_value = tokens.data[1];

            if (gup_string_eq_cstr(line_key, key)) {
                *out = gup_string_copy_arena(a, line_value);
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
char *gup_cstr_array_flatten_arena(GupArena *a, char **strings) {
    // Calculate the total length of all the strings.
    int total_length = 0;
    for (int i = 0; strings[i] != NULL; i++) {
        total_length += strlen(strings[i]);
    }

    // Allocate a new buffer to hold the flattened string.
    char *result = gup_arena_alloc(a, total_length + 1);
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
int gup_cstr_length(const char *cstr) {
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
bool gup_cstr_eq(const char *a, const char* b) {
    if (gup_cstr_length(a) != gup_cstr_length(b)) {
        return false;
    }

    for (int i = 0; i < gup_cstr_length(a); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

// Assumes null terminated "from" string.
// Assumes the "to" string has enough memory allocated to hold "from".
// Null terminates the "to" string.
void gup_cstr_copy(char *to, const char *from) {
    for (int i = 0; i < gup_cstr_length_including_null(from); i++) {
        to[i] = from[i];
    }
}

// Assumes null terminated "from" string. Allocates space for the "to" string.
void gup_cstr_copy_arena(GupArena *a, char *to, const char *from) {
    const int from_len = gup_cstr_length_including_null(from);

    to = gup_arena_alloc(a, from_len);
    
    for (int i = 0; i < from_len; i++) {
        to[i] = from[i];
    }
}

// Assumes the "to" string has enough memory allocated for n+1 characters (+1 for the null terminator).
// Null terminates the "to" string.
// Example: if you wanted to copy "Hello" you would need to pass in a pointer with 6 bytes allocated
// but only ask copy_n to copy 5 characters.
// ```
//   char *to = gup_arena_alloc(a, 6);
//   gup_cstr_copy_n(to, "Hello World", 5);
// ```
// this would result with `to` pointing to a chunk of memory with the contents 'H''e''l''l''o''\0'.
//   
void gup_cstr_copy_n(char *to, const char *from, int n) {
    for (int i = 0; i < n; i++) {
        to[i] = from[i];
    }
    to[n] = '\0';
}

// Allocates space for the "to" string.
void gup_cstr_copy_n_arena(GupArena *a, char *to, const char *from, int n) {
    // n+1 bytes because we need room for the null terminator.
    to = gup_arena_alloc(a, sizeof(char) * (n+1));
    
    for (int i = 0; i < n; i++) {
        to[i] = from[i];
    }

    to[n] = '\0';
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

#endif // GUPPY_H_
