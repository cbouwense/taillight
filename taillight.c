#include "guppy.h"

// TODO: hashmap would be nice here
GupString name_from_prefix(GupArena *a, GupString prefix) {
    if (gup_string_eq_cstr(prefix, "w")) return gup_string_create_from_cstr_arena(a, "width");

    return gup_string_create_from_cstr_arena(a, "");
}

// TODO: namespaces
// w-100rem -> .w-100rem { width: 100rem; }
GupString generate_rule(GupArena *a, GupString raw_rule) {
    GupString taillight_rule = gup_string_create_arena(a);

    // "."
    gup_string_append_arena(a, &taillight_rule, '.');

    // ".w-100rem"
    for (int i = 0; i < raw_rule.count; i++) {
        gup_string_append_arena(a, &taillight_rule, raw_rule.data[i]);
    }

    // ".w-100rem { "
    gup_string_append_arena(a, &taillight_rule, ' ');
    gup_string_append_arena(a, &taillight_rule, '{');
    gup_string_append_arena(a, &taillight_rule, ' ');

    // "w-100rem" -> ["w", "100rem"] -> name = "w"
    GupArrayString tokens = gup_string_split_arena(a, raw_rule, '-');
    GupString name = name_from_prefix(a, tokens.data[0]);

    // ".w-100rem { width"
    for (int i = 0; i < name.count; i++) {
        gup_string_append_arena(a, &taillight_rule, name.data[i]);
    }

    // ".w-100rem { width: "
    gup_string_append_arena(a, &taillight_rule, ':');
    gup_string_append_arena(a, &taillight_rule, ' ');

    // ["w", "100rem"] -> name = "w"
    GupString value_and_units = tokens.data[1];
    
    // ".w-100rem { width: 100rem"
    for (int i = 0; i < value_and_units.count; i++) {
        gup_string_append_arena(a, &taillight_rule, value_and_units.data[i]);
    }

    // ".w-100rem { width: 100rem; }"
    gup_string_append_arena(a, &taillight_rule, ';');
    gup_string_append_arena(a, &taillight_rule, ' ');
    gup_string_append_arena(a, &taillight_rule, '}');

    return taillight_rule;
}

// TODO: args
int main() {
    GupArena a = gup_arena_create();

    // Scrape the raw rules from the HTML
    GupString html = gup_file_read_arena(&a, "index.html");
    // gup_string_print(html);
    GupArrayString raw_rules = gup_array_string_create_arena(&a);

    //        | class start
    //        |     | class value start
    //        |     |   | class value end
    // "<body class="m-0">" -> "m-0"
    //        01234567890
    //               i
    //                  j
    // TODO: is - 7 correct?
    for (int i = 0; i < html.count - 7; i++) {
        GupString view = {
            .data = &html.data[i],
            .count = 7,
            .capacity = 7
        };
        if (gup_string_eq_cstr(view, "class=\"")) {
            i += 7;
            int j = i;
            while (html.data[j] != '"') {
                j++;
            }

            view = (GupString) {
                .data = &html.data[i],
                .count = j - i,
                .capacity = j - i
            };

            gup_string_print(view);
            GupArrayString tokens = gup_string_split_arena(&a, view, ' ');
            // TODO: would be nice to have a Set
            for (int k = 0; k < tokens.count; k++) {
                gup_array_string_append_arena(&a, &raw_rules, tokens.data[k]);
            }
        }
    }
    gup_array_string_print(raw_rules);

    // Generate the taillight rules from the raw rules
    GupArrayString file_lines = gup_array_string_create_arena(&a);
    GupString raw_rule = gup_string_create_from_cstr_arena(&a, "w-100rem");
    GupString taillight_rule = generate_rule(&a, raw_rule);
    gup_array_string_append_arena(&a, &file_lines, taillight_rule);

    // Write the lines to the file 
    char **file_lines_as_cstrs = gup_arena_alloc(&a, sizeof(char *) * file_lines.count);
    for (int i = 0; i < file_lines.count; i++) {
        file_lines_as_cstrs[i] = gup_arena_alloc(&a, file_lines.data[i].count + 1);
        gup_cstr_copy_n(file_lines_as_cstrs[i], file_lines.data[i].data, file_lines.data[i].count);
    }
    gup_assert(gup_file_write_lines(file_lines_as_cstrs, file_lines.count, "taillight.css"));

    gup_arena_destroy(a);
    return 0;
}
