#include "guppy.h"

// "m_w-100rem!" -> ".m_w-100rem\! { width: 100rem !important; }:
GupString generate_rule(GupArena *a, GupString raw_rule) {
    GupString taillight_rule = gup_string_create_arena(a);

    // "m_w-100rem" -> ["m_w", "100rem"] -> abbreviated_name = "w", value_and_units = "100rem"
    GupArrayString tokens = gup_string_split_arena(a, raw_rule, '-');
    GupArrayString name_and_namespace_as_tokens = gup_string_split_arena(a, tokens.data[0], '_');
    GupString abbreviated_name = name_and_namespace_as_tokens.data[0];
    // If there is a namespace, then the prefix token would be the second one.
    if (name_and_namespace_as_tokens.count == 2) {
        abbreviated_name = name_and_namespace_as_tokens.data[1];
    }
    // "m_w-100rem" -> ["m_w", "100rem"] -> value_and_units = "100rem"
    GupString value_and_units = tokens.data[1];

    GupString taillight_class = gup_string_create_arena(a);
    for (int i = 0; i < raw_rule.count; i++) {
        switch (raw_rule.data[i]) {
            // TODO: implement !important
            case '!': {
                gup_string_append_cstr_arena(a, &taillight_class, "\\!");
                break;
            }
            case '%': {
                gup_string_append_cstr_arena(a, &taillight_class, "\\%");
                break;
            }
            case '.': {
                gup_string_append_cstr_arena(a, &taillight_class, "\\.");
                break;
            }
            default: {
                gup_string_append_arena(a, &taillight_class, raw_rule.data[i]);
                break;
            }
        }
    }

    // ".m_w-100rem { "
    gup_string_append_arena(a, &taillight_rule, '.');
    gup_string_append_str_arena(a, &taillight_rule, taillight_class);
    gup_string_append_cstr_arena(a, &taillight_rule, " { ");

    // TODO: process namespaces
    if (gup_string_eq_cstr(abbreviated_name, "absolute")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "position: absolute; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignStart")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: flex-start; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignEnd")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: flex-end; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignCenter")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: center; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignBaseline")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: baseline; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignStretch")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: stretch; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "b")) {
        // TODO: border is a strange one, it has such variable values, not sure how to process it yet. 
        gup_string_append_cstr_arena(a, &taillight_rule, "border: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "bb")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "bg")) {
        if (gup_string_eq_cstr(value_and_units, "default")) {
            gup_string_append_cstr_arena(a, &taillight_rule, "background-color: var(--background-color)");
        } else {
            gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        }

        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "bl")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "br")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "brad")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-radius: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "bt")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
    } else if (gup_string_eq_cstr(abbreviated_name, "bottom")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "bx")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "border-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "by")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "border-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "c")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "color: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "column")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "flex-direction: column };\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "dot")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\n    list-style-type: disc;\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "    margin-left: 1.5rem;\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "}\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "fixed")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "position: fixed; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "flex")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "display: flex; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "fs")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "font-size: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "gap")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "gap: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "h")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "height: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "hoverable")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\n    color: var(--text-primary-color);\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "    transition: color 0.25s ease;\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "}\n");
        gup_string_append_cstr_arena(a, &taillight_rule, ".hoverable-text:hover {\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "    color: var(--text-secondary-color);\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "}\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyStart")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: flex-start; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyEnd")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: flex-end; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyCenter")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: center; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyBetween")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: space-between; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyAround")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: space-around; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyEvenly")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: space-evenly; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyStretch")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: stretch; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "left")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "m")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "maxh")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "max-height: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "maxw")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "max-width: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "mb")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "minh")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "min-height: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "minw")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "min-width: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "ml")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "mr")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "mt")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "mx")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "my")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "p")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "pb")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "pl")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "pr")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "pt")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "px")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "py")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "right")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "relative")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "position: relative; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "row")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "flex-direction: row; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowSm")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 1px 2px 0 rgb(0, 0, 0, 0.05); }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadow")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 1px 3px 0 rgb(0, 0, 0, 0.1), 0 1px 2px -1px rgb(0, 0, 0, 0.1); }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowMd")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 4px 6px -1px rgb(0, 0, 0, 0.1), 0 2px 4px -2px rgb(0, 0, 0, 0.1); }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowLg")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 10px 15px -3px rgb(0, 0, 0, 0.1), 0 4px 6px -4px rgb(0, 0, 0, 0.1); }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowXl")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 20px 25px -5px rgb(0, 0, 0, 0.1), 0 8px 10px -6px rgb(0, 0, 0, 0.1); }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowXxl")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 25px 50px -12px rgb(0, 0, 0, 0.25); }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowInner")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: inset 0 2px 4px 0 rgb(0, 0, 0, 0.05); }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowNone")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 0 #0000; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "top")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "w")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "width: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "z")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "z-index: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        gup_string_append_cstr_arena(a, &taillight_rule, "; }\n");
    } else {
        printf("WARNING: Unable to parse the following class name:\n");
        gup_string_print(abbreviated_name);
        printf("Either taillight does not support that key, you misspelled it, or there is a bug in taillight.\n");
    }

    return taillight_rule;
}

int main(int argc, char **argv) {
    char *html_file_path = (argc > 1) ? argv[1] : "index.html";
    char *css_file_path = (argc > 2) ? argv[2] : "taillight.css";

    GupArena a = gup_arena_create();
    GupArrayString file_lines = gup_array_string_create_arena(&a);

    // Scrape the raw rules from the HTML
    printf("Parsing %s...\n", html_file_path);
    GupString html = gup_file_read_arena(&a, html_file_path);
    GupArrayString raw_rules = gup_array_string_create_arena(&a);
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

            GupArrayString tokens = gup_string_split_arena(&a, view, ' ');
            // TODO: would be nice to have a Set
            for (int k = 0; k < tokens.count; k++) {
                gup_array_string_append_arena(&a, &raw_rules, tokens.data[k]);
            }
        }
    }
    printf("Successfully parsed %s.\n", html_file_path);

    // Write the boilerplate to the final css file
    printf("Generating taillight rules...\n");
    {
        gup_array_string_append_cstr_arena(&a, &file_lines, "* { box-sizing: border-box; }\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, ":root {\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    font-size: 16px;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    --text-primary-color: whitesmoke;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    --text-secondary-color: gray;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    color: var(--text-primary-color);\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    --background-color: rgba(18, 18, 18);\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    --primary-color: blue;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    --secondary-color: #2a2a2a;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "}\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "html {\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    scroll-behavior: smooth;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    scroll-padding-top: 2rem;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "}\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "a {\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    color: inherit;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    text-decoration: none;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "}\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "body {\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    background-color: var(--background-color);\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    font-family: \"Libre Baskerville\", serif;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    font-weight: 400;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "    font-style: normal;\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "}\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "li { list-style-type: none; }\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "ul { padding-left: 0; }\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "h1 { font-size: 3rem; }\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "h2 { font-size: 2rem; }\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "h3 { font-size: 1.5rem; }\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "h4 { font-size: 1rem; }\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "h5 { font-size: 0.75rem; }\n");
        gup_array_string_append_cstr_arena(&a, &file_lines, "h6 { font-size: 0.5rem; }\n");
    }

    // Generate the taillight rules from the raw rules
    for (int i = 0; i < raw_rules.count; i++) {
        GupString taillight_rule = generate_rule(&a, raw_rules.data[i]);
        if (!gup_array_string_contains(file_lines, taillight_rule)) {
            gup_array_string_append_arena(&a, &file_lines, taillight_rule);
        }
    }
    printf("Successfully generated taillight rules.\n");

    // Write the lines to the final css file 
    printf("Writing taillight rules to %s...\n", css_file_path);
    char **file_lines_as_cstrs = gup_arena_alloc(&a, sizeof(char *) * file_lines.count);
    for (int i = 0; i < file_lines.count; i++) {
        file_lines_as_cstrs[i] = gup_arena_alloc(&a, file_lines.data[i].count + 1);
        gup_cstr_copy_n(file_lines_as_cstrs[i], file_lines.data[i].data, file_lines.data[i].count);
        // gup_cstr_print(file_lines_as_cstrs[i]);
    }
    gup_file_write_lines(file_lines_as_cstrs, file_lines.count, css_file_path);
    printf("Successfully wrote taillight rules to %s.\n", css_file_path);
    printf("All done, hope it looks good!\n");

    gup_arena_destroy(a);
    return 0;
}
