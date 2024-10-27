#include "guppy.h"

#define KEY_VAL(key_val_pair) \
    do {\
        if (has_namespace) gup_string_append_cstr_arena(a, &taillight_rule, "  ");\
        gup_string_append_cstr_arena(a, &taillight_rule, "  ");\
        gup_string_append_cstr_arena(a, &taillight_rule, key_val_pair);\
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");\
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n");\
    } while (0)

#define KEY_WITH_PARSED_VAL(key) \
    do {\
        if (has_namespace) gup_string_append_cstr_arena(a, &taillight_rule, "  ");\
        gup_string_append_cstr_arena(a, &taillight_rule, "  ");\
        gup_string_append_cstr_arena(a, &taillight_rule, key);\
        gup_string_append_cstr_arena(a, &taillight_rule, ": ");\
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);\
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");\
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n");\
    } while (0)

// "m_w-100rem!" -> ".w-100rem\! { width: 100rem !important; }:
GupString generate_rule(GupArena *a, GupString raw_rule) {
    GupString taillight_rule = gup_string_create_arena(a);

    // "m_w-100rem!":
    // namespace        = "m"
    // abbreviated_name = "w"
    // value_and_units  = "100rem"
    // has_namespace    = true
    // is_important     = true
    GupArrayString tokens = gup_string_split_arena(a, raw_rule, '-');

    GupArrayString name_and_namespace_as_tokens = gup_string_split_arena(a, tokens.data[0], '_');
    bool has_namespace = name_and_namespace_as_tokens.count == 2;
    GupString abbreviated_name = has_namespace
        ? name_and_namespace_as_tokens.data[1]
        : name_and_namespace_as_tokens.data[0];

    bool is_important = false;
    GupString value_and_units = tokens.count > 1
        ? gup_string_copy_arena(a, tokens.data[1])
        : (GupString) {0};
    gup_string_trim_char_in_place(&value_and_units, '!');

    GupString taillight_class = gup_string_create_arena(a);
    for (int i = 0; i < raw_rule.count; i++) {
        switch (raw_rule.data[i]) {
            case '!': {
                gup_string_append_cstr_arena(a, &taillight_class, "\\!");
                is_important = true;
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

    // ".w-100rem { "
    if (has_namespace) gup_string_append_cstr_arena(a, &taillight_rule, "  ");
    gup_string_append_arena(a, &taillight_rule, '.');
    gup_string_append_str_arena(a, &taillight_rule, taillight_class);
    gup_string_append_cstr_arena(a, &taillight_rule, " {\n");

    gup_array_string_print(name_and_namespace_as_tokens);
    printf("has_namespace: %d\n", has_namespace);

    if (gup_string_eq_cstr(abbreviated_name, "absolute")) {
        KEY_VAL("position: absolute");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignStart")) {
        KEY_VAL("align-items: flex-start");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignEnd")) {
        KEY_VAL("align-items: flex-end");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignCenter")) {
        KEY_VAL("align-items: center");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignBaseline")) {
        KEY_VAL("align-items: baseline");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignStretch")) {
        KEY_VAL("align-items: stretch");
    } else if (gup_string_eq_cstr(abbreviated_name, "b")) { // TODO: border is a strange one, it has such variable values, not sure how to process it yet.
        KEY_WITH_PARSED_VAL("border");
    } else if (gup_string_eq_cstr(abbreviated_name, "bb")) {
        KEY_WITH_PARSED_VAL("border-bottom");
    } else if (gup_string_eq_cstr(abbreviated_name, "bg")) {
        if (gup_string_eq_cstr(value_and_units, "default")) {
            KEY_VAL("background-color: var(--background-color)");
        } else {
            KEY_WITH_PARSED_VAL("background-color");
        }
    } else if (gup_string_eq_cstr(abbreviated_name, "bl")) {
        KEY_WITH_PARSED_VAL("border-left");
    } else if (gup_string_eq_cstr(abbreviated_name, "br")) {
        KEY_WITH_PARSED_VAL("border-right");
    } else if (gup_string_eq_cstr(abbreviated_name, "brad")) {
        KEY_WITH_PARSED_VAL("border-radius");
    } else if (gup_string_eq_cstr(abbreviated_name, "bt")) {
        KEY_WITH_PARSED_VAL("border-top");
    } else if (gup_string_eq_cstr(abbreviated_name, "bottom")) {
        KEY_WITH_PARSED_VAL("bottom");
    } else if (gup_string_eq_cstr(abbreviated_name, "bx")) {
        KEY_WITH_PARSED_VAL("border-left");
        KEY_WITH_PARSED_VAL("border-right");
    } else if (gup_string_eq_cstr(abbreviated_name, "by")) {
        KEY_WITH_PARSED_VAL("border-top");
        KEY_WITH_PARSED_VAL("border-bottom");
    } else if (gup_string_eq_cstr(abbreviated_name, "c")) {
        KEY_WITH_PARSED_VAL("color");
    } else if (gup_string_eq_cstr(abbreviated_name, "column")) {
        KEY_VAL("flex-direction: column");
    } else if (gup_string_eq_cstr(abbreviated_name, "dot")) {
        KEY_VAL("list-style-type: disc");
        KEY_VAL("margin-left: 1.5rem");
    } else if (gup_string_eq_cstr(abbreviated_name, "fixed")) {
        KEY_VAL("position: fixed");
    } else if (gup_string_eq_cstr(abbreviated_name, "flex")) {
        KEY_VAL("display: flex");
    } else if (gup_string_eq_cstr(abbreviated_name, "fs")) {
        KEY_WITH_PARSED_VAL("font-size");
    } else if (gup_string_eq_cstr(abbreviated_name, "gap")) {
        KEY_WITH_PARSED_VAL("gap");
    } else if (gup_string_eq_cstr(abbreviated_name, "h")) {
        KEY_WITH_PARSED_VAL("height");
    } else if (gup_string_eq_cstr(abbreviated_name, "hoverable")) { // TODO: macro for multi rule rules
        KEY_VAL("color: var(--text-primary-color)");
        KEY_VAL("transition: color 0.25s ease");
        gup_string_append_cstr_arena(a, &taillight_rule, "}\n");

        // .hoverable:hover {
        //   color: var(--text-secondary-color);
        // }
        gup_string_append_cstr_arena(a, &taillight_rule, ".hoverable:hover {\n");
        KEY_VAL("  color: var(--text-secondary-color)");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyStart")) {
        KEY_VAL("justify-content: flex-start");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyEnd")) {
        KEY_VAL("justify-content: flex-end");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyCenter")) {
        KEY_VAL("justify-content: center");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyBetween")) {
        KEY_VAL("justify-content: space-between");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyAround")) {
        KEY_VAL("justify-content: space-around");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyEvenly")) {
        KEY_VAL("justify-content: space-evenly");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyStretch")) {
        KEY_VAL("justify-content: stretch");
    } else if (gup_string_eq_cstr(abbreviated_name, "left")) {
        KEY_WITH_PARSED_VAL("left");
    } else if (gup_string_eq_cstr(abbreviated_name, "m")) {
        KEY_WITH_PARSED_VAL("margin");
    } else if (gup_string_eq_cstr(abbreviated_name, "maxh")) {
        KEY_WITH_PARSED_VAL("max-height");
    } else if (gup_string_eq_cstr(abbreviated_name, "maxw")) {
        KEY_WITH_PARSED_VAL("max-width");
    } else if (gup_string_eq_cstr(abbreviated_name, "mb")) {
        KEY_WITH_PARSED_VAL("margin-bottom");
    } else if (gup_string_eq_cstr(abbreviated_name, "minh")) {
        KEY_WITH_PARSED_VAL("min-height");
    } else if (gup_string_eq_cstr(abbreviated_name, "minw")) {
        KEY_WITH_PARSED_VAL("min-width");
    } else if (gup_string_eq_cstr(abbreviated_name, "ml")) {
        KEY_WITH_PARSED_VAL("margin-left");
    } else if (gup_string_eq_cstr(abbreviated_name, "mr")) {
        KEY_WITH_PARSED_VAL("margin-right");
    } else if (gup_string_eq_cstr(abbreviated_name, "mt")) {
        KEY_WITH_PARSED_VAL("margin-top");
    } else if (gup_string_eq_cstr(abbreviated_name, "mx")) {
        KEY_WITH_PARSED_VAL("margin-left");
        KEY_WITH_PARSED_VAL("margin-right");
    } else if (gup_string_eq_cstr(abbreviated_name, "my")) {
        KEY_WITH_PARSED_VAL("margin-top");
        KEY_WITH_PARSED_VAL("margin-bottom");
    } else if (gup_string_eq_cstr(abbreviated_name, "p")) {
        KEY_WITH_PARSED_VAL("padding");
    } else if (gup_string_eq_cstr(abbreviated_name, "pb")) {
        KEY_WITH_PARSED_VAL("padding-bottom");
    } else if (gup_string_eq_cstr(abbreviated_name, "pl")) {
        KEY_WITH_PARSED_VAL("padding-left");
    } else if (gup_string_eq_cstr(abbreviated_name, "pr")) {
        KEY_WITH_PARSED_VAL("padding-right");
    } else if (gup_string_eq_cstr(abbreviated_name, "pt")) {
        KEY_WITH_PARSED_VAL("padding-top");
    } else if (gup_string_eq_cstr(abbreviated_name, "px")) {
        KEY_WITH_PARSED_VAL("padding-left");
        KEY_WITH_PARSED_VAL("padding-right");
    } else if (gup_string_eq_cstr(abbreviated_name, "py")) {
        KEY_WITH_PARSED_VAL("padding-top");
        KEY_WITH_PARSED_VAL("padding-bottom");
    } else if (gup_string_eq_cstr(abbreviated_name, "right")) {
        KEY_WITH_PARSED_VAL("right");
    } else if (gup_string_eq_cstr(abbreviated_name, "relative")) {
        KEY_VAL("position: relative");
    } else if (gup_string_eq_cstr(abbreviated_name, "row")) {
        KEY_VAL("flex-direction: row");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowSm")) { 
        KEY_VAL("box-shadow: 0 1px 2px 0 rgb(0, 0, 0, 0.05)");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadow")) { 
        KEY_VAL("box-shadow: 0 1px 3px 0 rgb(0, 0, 0, 0.1), 0 1px 2px -1px rgb(0, 0, 0, 0.1)");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowMd")) { 
        KEY_VAL("box-shadow: 0 4px 6px -1px rgb(0, 0, 0, 0.1), 0 2px 4px -2px rgb(0, 0, 0, 0.1)");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowLg")) { 
        KEY_VAL("box-shadow: 0 10px 15px -3px rgb(0, 0, 0, 0.1), 0 4px 6px -4px rgb(0, 0, 0, 0.1)");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowXl")) { 
        KEY_VAL("box-shadow: 0 20px 25px -5px rgb(0, 0, 0, 0.1), 0 8px 10px -6px rgb(0, 0, 0, 0.1)");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowXxl")) {
        KEY_VAL("box-shadow: 0 25px 50px -12px rgb(0, 0, 0, 0.25)");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowInner")) { 
        KEY_VAL("box-shadow: inset 0 2px 4px 0 rgb(0, 0, 0, 0.05)");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowNone")) { 
        KEY_VAL("box-shadow: 0 0 #0000");
    } else if (gup_string_eq_cstr(abbreviated_name, "top")) {
        KEY_WITH_PARSED_VAL("top");
    } else if (gup_string_eq_cstr(abbreviated_name, "w")) {
        KEY_WITH_PARSED_VAL("width");
    } else if (gup_string_eq_cstr(abbreviated_name, "z")) {
        KEY_WITH_PARSED_VAL("z-index");
    } else {
        printf("WARNING: Unable to parse the following class name:\n");
        gup_string_print(abbreviated_name);
        printf("Either taillight does not support that key, you misspelled it, or there is a bug in taillight.\n");
    }

    if (has_namespace) gup_string_append_cstr_arena(a, &taillight_rule, "  ");
    gup_string_append_cstr_arena(a, &taillight_rule, "}");

    return taillight_rule;
}

int main(int argc, char **argv) {
    char *html_file_path = (argc > 1) ? argv[1] : "index.html";
    char *css_file_path = (argc > 2) ? argv[2] : "taillight.css";

    GupArena a = gup_arena_create();

    // Scrape the raw rules from the HTML
    printf("Parsing %s...\n", html_file_path);
    GupString html = gup_file_read_arena(&a, html_file_path);
    GupArrayString html_rules = gup_array_string_create_arena(&a);
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
                gup_array_string_append_arena(&a, &html_rules, tokens.data[k]);
            }
        }
    }
    printf("Successfully parsed %s.\n", html_file_path);

    printf("Generating taillight rules...\n");
    GupArrayString no_namespace_rules = gup_array_string_create_arena(&a);
    GupArrayString mobile_namespace_rules = gup_array_string_create_arena(&a);
    GupArrayString tablet_namespace_rules = gup_array_string_create_arena(&a);
    GupArrayString computer_namespace_rules = gup_array_string_create_arena(&a);
    GupArrayString ultrawide_namespace_rules = gup_array_string_create_arena(&a);
    // Write the boilerplate to the final css file
    // TODO: no boilerplate option
    {
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "* { box-sizing: border-box; }");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, ":root {");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  font-size: 16px;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  --text-primary-color: whitesmoke;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  --text-secondary-color: gray;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  color: var(--text-primary-color);");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  --background-color: rgba(18, 18, 18);");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  --primary-color: blue;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  --secondary-color: #2a2a2a;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "}");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "html {");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  scroll-behavior: smooth;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  scroll-padding-top: 2rem;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "}");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "a {");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  color: inherit;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  text-decoration: none;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "}");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "body {");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  background-color: var(--background-color);");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  font-family: \"Libre Baskerville\", serif;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  font-weight: 400;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "  font-style: normal;");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "}");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "li { list-style-type: none; }");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "ul { padding-left: 0; }");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "h1 { font-size: 3rem; }");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "h2 { font-size: 2rem; }");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "h3 { font-size: 1.5rem; }");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "h4 { font-size: 1rem; }");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "h5 { font-size: 0.75rem; }");
        gup_array_string_append_cstr_arena(&a, &no_namespace_rules, "h6 { font-size: 0.5rem; }\n");
    }

    // Generate the taillight rules from the parsed html rules
    for (int i = 0; i < html_rules.count; i++) {
        GupString html_rule = html_rules.data[i];
        GupString taillight_rule = generate_rule(&a, html_rule);
        
        // TODO: using Sets would be better instead of manually checking whether they're already contained, I'd guess 
        if (gup_string_starts_with_cstr(html_rule, "m_") && !gup_array_string_contains(mobile_namespace_rules, taillight_rule)) {
            gup_array_string_append_arena(&a, &mobile_namespace_rules, taillight_rule);
        } else if (gup_string_starts_with_cstr(html_rule, "t_") && !gup_array_string_contains(tablet_namespace_rules, taillight_rule)) {
            gup_array_string_append_arena(&a, &tablet_namespace_rules, taillight_rule);
        } else if (gup_string_starts_with_cstr(html_rule, "c_") && !gup_array_string_contains(computer_namespace_rules, taillight_rule)) {
            gup_array_string_append_arena(&a, &computer_namespace_rules, taillight_rule);
        } else if (gup_string_starts_with_cstr(html_rule, "uw_") && !gup_array_string_contains(ultrawide_namespace_rules, taillight_rule)) {
            gup_array_string_append_arena(&a, &ultrawide_namespace_rules, taillight_rule);
        } else if (!gup_array_string_contains(no_namespace_rules, taillight_rule)) {
            gup_array_string_append_arena(&a, &no_namespace_rules, taillight_rule);
        }
    }
    printf("Successfully generated taillight rules.\n");

    // Write the lines to the final css file 
    printf("Writing taillight rules to %s...\n", css_file_path);
    
    // NOTE: Writing this first line is actually a sort of hack to make sure we can append everything afterwards
    // but still be overwriting any old file. 
    gup_file_write_cstr("/* Stylesheet generated by taillight https://github.com/cbouwense/taillight */\n", css_file_path);
    gup_file_append_lines_arena(&a, no_namespace_rules, css_file_path);

    if (mobile_namespace_rules.count > 0) {
        gup_file_append_line_cstr("\n/* Mobile */", css_file_path);
        gup_file_append_line_cstr("@media (max-width: 768px) {", css_file_path);
        gup_file_append_line_cstr(".mobile { display: inherit; }", css_file_path);
        gup_file_append_line_cstr(".tablet { display: none; }", css_file_path);
        gup_file_append_line_cstr(".computer { display: none; }", css_file_path);
        gup_file_append_line_cstr(".ultrawide { display: none; }", css_file_path);
        gup_file_append_line_cstr(":root { font-size: 14px; }", css_file_path);
        gup_file_append_lines_arena(&a, mobile_namespace_rules, css_file_path);
        gup_file_append_line_cstr("}", css_file_path);
    }

    if (tablet_namespace_rules.count > 0) {
        gup_file_append_line_cstr("\n/* Tablet */", css_file_path);
        gup_file_append_line_cstr("@media (min-width: 768px) and (max-width: 1024px) {", css_file_path);
        gup_file_append_line_cstr("  .mobile { display: none; }", css_file_path);
        gup_file_append_line_cstr("  .tablet { display: inherit; }", css_file_path);
        gup_file_append_line_cstr("  .computer { display: none; }", css_file_path);
        gup_file_append_line_cstr("  .ultrawide { display: none; }", css_file_path);
        gup_file_append_line_cstr("  :root { font-size: 14px; }", css_file_path);
        gup_file_append_lines_arena(&a, tablet_namespace_rules, css_file_path);
        gup_file_append_line_cstr("}", css_file_path);
    }

    if (computer_namespace_rules.count > 0) {
        gup_file_append_line_cstr("\n/* Computer (desktop / laptop) */", css_file_path);
        gup_file_append_line_cstr("@media (min-width: 1024px) and (max-width: 3840px) {", css_file_path);
        gup_file_append_line_cstr("  .mobile { display: none; }", css_file_path);
        gup_file_append_line_cstr("  .tablet { display: none; }", css_file_path);
        gup_file_append_line_cstr("  .computer { display: inherit; }", css_file_path);
        gup_file_append_line_cstr("  .ultrawide { display: none; }", css_file_path);
        gup_file_append_line_cstr("  :root { font-size: 18px; }", css_file_path);
        gup_file_append_lines_arena(&a, computer_namespace_rules, css_file_path);
        gup_file_append_line_cstr("}", css_file_path);
    }

    if (ultrawide_namespace_rules.count > 0) {
        gup_file_append_line_cstr("\n/* Ultrawide */", css_file_path);
        gup_file_append_line_cstr("@media (min-width: 3840px) {", css_file_path);
        gup_file_append_line_cstr("  .mobile { display: none; }", css_file_path);
        gup_file_append_line_cstr("  .tablet { display: none; }", css_file_path);
        gup_file_append_line_cstr("  .computer { display: none; }", css_file_path);
        gup_file_append_line_cstr("  .ultrawide { display: inherit; }", css_file_path);
        gup_file_append_line_cstr("  :root { font-size: 18px; }", css_file_path); // TODO: do we maybe want a bigger font here?
        gup_file_append_lines_arena(&a, ultrawide_namespace_rules, css_file_path);
        gup_file_append_line_cstr("}", css_file_path);
    }

    printf("Successfully wrote taillight rules to %s.\n", css_file_path);
    printf("All done, hope it looks good!\n");

    gup_arena_destroy(a);
    return 0;
}
