#include "guppy.h"

#define ADD_CLASSNAME(classname) \
    if (has_namespace) gup_string_append_cstr_arena(&a, &taillight_rule, "  ");\
    gup_string_append_arena(&a, &taillight_rule, '.');\
    gup_string_append_str_arena(&a, &taillight_rule, classname);\
    gup_string_append_cstr_arena(&a, &taillight_rule, " {\n");

#define ADD_KEY_VALUE_LITERAL(key_val_pair) \
    do {\
        if (has_namespace) gup_string_append_cstr_arena(&a, &taillight_rule, "  ");\
        gup_string_append_cstr_arena(&a, &taillight_rule, "  ");\
        gup_string_append_cstr_arena(&a, &taillight_rule, key_val_pair);\
        if (is_important) gup_string_append_cstr_arena(&a, &taillight_rule, " !important");\
        gup_string_append_cstr_arena(&a, &taillight_rule, ";\n");\
    } while (0)

#define ADD_KEY_WITH_PARSED_VALUE(key) \
    do {\
        if (has_namespace) gup_string_append_cstr_arena(&a, &taillight_rule, "  ");\
        gup_string_append_cstr_arena(&a, &taillight_rule, "  ");\
        gup_string_append_cstr_arena(&a, &taillight_rule, key);\
        gup_string_append_cstr_arena(&a, &taillight_rule, ": ");\
        gup_string_append_str_arena(&a, &taillight_rule, value_and_units);\
        if (is_important) gup_string_append_cstr_arena(&a, &taillight_rule, " !important");\
        gup_string_append_cstr_arena(&a, &taillight_rule, ";\n");\
    } while (0)

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
    GupArrayString unknown_rules = gup_array_string_create_arena(&a);
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
        GupString taillight_rule = gup_string_create_arena(&a);
        // Generate rule for this html rule
        {
            GupArrayString tokens = gup_string_split_arena(&a, html_rule, '-');

            GupArrayString name_and_namespace_as_tokens = gup_string_split_arena(&a, tokens.data[0], '_');
            bool has_namespace = name_and_namespace_as_tokens.count == 2;
            GupString abbreviated_name = has_namespace
                ? name_and_namespace_as_tokens.data[1]
                : name_and_namespace_as_tokens.data[0];

            bool is_important = false;
            GupString value_and_units = tokens.count > 1
                ? gup_string_copy_arena(&a, tokens.data[1])
                : (GupString) {0};
            gup_string_trim_char_in_place(&value_and_units, '!');

            GupString taillight_class = gup_string_create_arena(&a);
            for (int i = 0; i < html_rule.count; i++) {
                switch (html_rule.data[i]) {
                    case '!': {
                        gup_string_append_cstr_arena(&a, &taillight_class, "\\!");
                        is_important = true;
                        break;
                    }
                    case '%': {
                        gup_string_append_cstr_arena(&a, &taillight_class, "\\%");
                        break;
                    }
                    case '.': {
                        gup_string_append_cstr_arena(&a, &taillight_class, "\\.");
                        break;
                    }
                    default: {
                        gup_string_append_arena(&a, &taillight_class, html_rule.data[i]);
                        break;
                    }
                }
            }

            // These keywords are used by the media queries and don't need anything to be auto generated for them.
            if (
                gup_string_eq_cstr(html_rule, "mobile")   ||
                gup_string_eq_cstr(html_rule, "tablet")   ||
                gup_string_eq_cstr(html_rule, "computer") ||
                gup_string_eq_cstr(html_rule, "ultrawide")
            ) {
                continue;
            }

            if (gup_string_eq_cstr(abbreviated_name, "absolute")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("position: absolute");
            } else if (gup_string_eq_cstr(abbreviated_name, "alignStart")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("align-items: flex-start");
            } else if (gup_string_eq_cstr(abbreviated_name, "alignEnd")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("align-items: flex-end");
            } else if (gup_string_eq_cstr(abbreviated_name, "alignCenter")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("align-items: center");
            } else if (gup_string_eq_cstr(abbreviated_name, "alignBaseline")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("align-items: baseline");
            } else if (gup_string_eq_cstr(abbreviated_name, "alignStretch")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("align-items: stretch");
            } else if (gup_string_eq_cstr(abbreviated_name, "b")) { // TODO: border is a strange one, it has such variable values, not sure how to process it yet.
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("border");
            } else if (gup_string_eq_cstr(abbreviated_name, "basis")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("flex-basis");
            } else if (gup_string_eq_cstr(abbreviated_name, "bb")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("border-bottom");
            } else if (gup_string_eq_cstr(abbreviated_name, "bg")) {
                ADD_CLASSNAME(taillight_class);
                if (gup_string_eq_cstr(value_and_units, "default")) {
                    ADD_KEY_VALUE_LITERAL("background-color: var(--background-color)");
                } else {
                    ADD_KEY_WITH_PARSED_VALUE("background-color");
                }
            } else if (gup_string_eq_cstr(abbreviated_name, "bl")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("border-left");
            } else if (gup_string_eq_cstr(abbreviated_name, "br")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("border-right");
            } else if (gup_string_eq_cstr(abbreviated_name, "brad")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("border-radius");
            } else if (gup_string_eq_cstr(abbreviated_name, "bt")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("border-top");
            } else if (gup_string_eq_cstr(abbreviated_name, "bottom")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("bottom");
            } else if (gup_string_eq_cstr(abbreviated_name, "bx")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("border-left");
                ADD_KEY_WITH_PARSED_VALUE("border-right");
            } else if (gup_string_eq_cstr(abbreviated_name, "by")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("border-top");
                ADD_KEY_WITH_PARSED_VALUE("border-bottom");
            } else if (gup_string_eq_cstr(abbreviated_name, "c")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("color");
            } else if (gup_string_eq_cstr(abbreviated_name, "column")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("flex-direction: column");
            } else if (gup_string_eq_cstr(abbreviated_name, "dot")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("list-style-type: disc");
                ADD_KEY_VALUE_LITERAL("margin-left: 1.5rem");
            } else if (gup_string_eq_cstr(abbreviated_name, "fixed")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("position: fixed");
            } else if (gup_string_eq_cstr(abbreviated_name, "flex")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("display: flex");
            } else if (gup_string_eq_cstr(abbreviated_name, "fs")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("font-size");
            } else if (gup_string_eq_cstr(abbreviated_name, "gap")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("gap");
            } else if (gup_string_eq_cstr(abbreviated_name, "grid")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("display: grid");
            } else if (gup_string_eq_cstr(abbreviated_name, "gridCol")) {
                ADD_CLASSNAME(taillight_class);
                if (has_namespace) gup_string_append_cstr_arena(&a, &taillight_rule, "  ");
                gup_string_append_cstr_arena(&a, &taillight_rule, "  ");
                gup_string_append_cstr_arena(&a, &taillight_rule, "grid-template-columns: ");
                if (gup_string_eq_cstr(value_and_units, "1")) {
                    gup_string_append_cstr_arena(&a, &taillight_rule, "minmax(0, 1fr)");
                } else {
                    gup_string_append_cstr_arena(&a, &taillight_rule, "repeat(");
                    gup_string_append_str_arena(&a, &taillight_rule, value_and_units);
                    gup_string_append_cstr_arena(&a, &taillight_rule,", 1fr)");
                }
                if (is_important) gup_string_append_cstr_arena(&a, &taillight_rule, " !important");
                gup_string_append_cstr_arena(&a, &taillight_rule, ";\n");
            } else if (gup_string_eq_cstr(abbreviated_name, "grow")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("flex-grow");
            } else if (gup_string_eq_cstr(abbreviated_name, "h")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("height");
            } else if (gup_string_eq_cstr(abbreviated_name, "justifyStart")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("justify-content: flex-start");
            } else if (gup_string_eq_cstr(abbreviated_name, "justifyEnd")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("justify-content: flex-end");
            } else if (gup_string_eq_cstr(abbreviated_name, "justifyCenter")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("justify-content: center");
            } else if (gup_string_eq_cstr(abbreviated_name, "justifyBetween")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("justify-content: space-between");
            } else if (gup_string_eq_cstr(abbreviated_name, "justifyAround")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("justify-content: space-around");
            } else if (gup_string_eq_cstr(abbreviated_name, "justifyEvenly")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("justify-content: space-evenly");
            } else if (gup_string_eq_cstr(abbreviated_name, "justifyStretch")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("justify-content: stretch");
            } else if (gup_string_eq_cstr(abbreviated_name, "left")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("left");
            } else if (gup_string_eq_cstr(abbreviated_name, "lightShadow")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 0 16px 0 rgba(255, 255, 255, 0.2)");
            } else if (gup_string_eq_cstr(abbreviated_name, "lightShadowSmall")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 0 8px 0 rgba(255, 255, 255, 0.2)");
            } else if (gup_string_eq_cstr(abbreviated_name, "m")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("margin");
            } else if (gup_string_eq_cstr(abbreviated_name, "maxh")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("max-height");
            } else if (gup_string_eq_cstr(abbreviated_name, "maxw")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("max-width");
            } else if (gup_string_eq_cstr(abbreviated_name, "mb")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("margin-bottom");
            } else if (gup_string_eq_cstr(abbreviated_name, "minh")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("min-height");
            } else if (gup_string_eq_cstr(abbreviated_name, "minw")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("min-width");
            } else if (gup_string_eq_cstr(abbreviated_name, "ml")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("margin-left");
            } else if (gup_string_eq_cstr(abbreviated_name, "mr")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("margin-right");
            } else if (gup_string_eq_cstr(abbreviated_name, "mt")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("margin-top");
            } else if (gup_string_eq_cstr(abbreviated_name, "mx")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("margin-left");
                ADD_KEY_WITH_PARSED_VALUE("margin-right");
            } else if (gup_string_eq_cstr(abbreviated_name, "my")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("margin-top");
                ADD_KEY_WITH_PARSED_VALUE("margin-bottom");
            } else if (gup_string_eq_cstr(abbreviated_name, "p")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("padding");
            } else if (gup_string_eq_cstr(abbreviated_name, "pb")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("padding-bottom");
            } else if (gup_string_eq_cstr(abbreviated_name, "pl")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("padding-left");
            } else if (gup_string_eq_cstr(abbreviated_name, "pr")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("padding-right");
            } else if (gup_string_eq_cstr(abbreviated_name, "pt")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("padding-top");
            } else if (gup_string_eq_cstr(abbreviated_name, "px")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("padding-left");
                ADD_KEY_WITH_PARSED_VALUE("padding-right");
            } else if (gup_string_eq_cstr(abbreviated_name, "py")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("padding-top");
                ADD_KEY_WITH_PARSED_VALUE("padding-bottom");
            } else if (gup_string_eq_cstr(abbreviated_name, "right")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("right");
            } else if (gup_string_eq_cstr(abbreviated_name, "relative")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("position: relative");
            } else if (gup_string_eq_cstr(abbreviated_name, "rounded")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("border-radius: 8px;");
            } else if (gup_string_eq_cstr(abbreviated_name, "row")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("flex-direction: row");
            } else if (gup_string_eq_cstr(abbreviated_name, "shadowSm")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 1px 2px 0 rgb(0, 0, 0, 0.05)");
            } else if (gup_string_eq_cstr(abbreviated_name, "shadow")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 1px 3px 0 rgb(0, 0, 0, 0.1), 0 1px 2px -1px rgb(0, 0, 0, 0.1)");
            } else if (gup_string_eq_cstr(abbreviated_name, "shadowMd")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 4px 6px -1px rgb(0, 0, 0, 0.1), 0 2px 4px -2px rgb(0, 0, 0, 0.1)");
            } else if (gup_string_eq_cstr(abbreviated_name, "shadowLg")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 10px 15px -3px rgb(0, 0, 0, 0.1), 0 4px 6px -4px rgb(0, 0, 0, 0.1)");
            } else if (gup_string_eq_cstr(abbreviated_name, "shadowXl")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 20px 25px -5px rgb(0, 0, 0, 0.1), 0 8px 10px -6px rgb(0, 0, 0, 0.1)");
            } else if (gup_string_eq_cstr(abbreviated_name, "shadowXxl")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 25px 50px -12px rgb(0, 0, 0, 0.25)");
            } else if (gup_string_eq_cstr(abbreviated_name, "shadowInner")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: inset 0 2px 4px 0 rgb(0, 0, 0, 0.05)");
            } else if (gup_string_eq_cstr(abbreviated_name, "shadowNone")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("box-shadow: 0 0 #0000");
            } else if (gup_string_eq_cstr(abbreviated_name, "shrink")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("flex-shrink");
            } else if (gup_string_eq_cstr(abbreviated_name, "sticky")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("position: sticky");
                ADD_KEY_VALUE_LITERAL("top: 0");
                ADD_KEY_VALUE_LITERAL("box-sizing: border-box");
            } else if (gup_string_eq_cstr(abbreviated_name, "top")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("top");
            } else if (gup_string_eq_cstr(abbreviated_name, "underlineDots")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("text-decoration: underline dotted");
            } else if (gup_string_eq_cstr(abbreviated_name, "w")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("width");
            } else if (gup_string_eq_cstr(abbreviated_name, "wrap")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_VALUE_LITERAL("word-wrap: break-word");
            } else if (gup_string_eq_cstr(abbreviated_name, "z")) {
                ADD_CLASSNAME(taillight_class);
                ADD_KEY_WITH_PARSED_VALUE("z-index");
            } else {
                if (!gup_array_string_contains(unknown_rules, html_rule)) {
                    gup_array_string_append_arena(&a, &unknown_rules, html_rule);
                }
            }

            if (has_namespace) gup_string_append_cstr_arena(&a, &taillight_rule, "  ");
            gup_string_append_cstr_arena(&a, &taillight_rule, "}");
        }
        
        // TODO: using Sets would be better instead of manually checking whether they're already contained, I'd guess 
        if (gup_string_starts_with_cstr(html_rule, "m_")) {
            if (!gup_array_string_contains(mobile_namespace_rules, taillight_rule)) {
                gup_array_string_append_arena(&a, &mobile_namespace_rules, taillight_rule);
            }
        } else if (gup_string_starts_with_cstr(html_rule, "t_")) {
            if (!gup_array_string_contains(tablet_namespace_rules, taillight_rule)) {
                gup_array_string_append_arena(&a, &tablet_namespace_rules, taillight_rule);
            }
        } else if (gup_string_starts_with_cstr(html_rule, "c_")) {
            if (!gup_array_string_contains(computer_namespace_rules, taillight_rule)) {
                gup_array_string_append_arena(&a, &computer_namespace_rules, taillight_rule);
            }
        } else if (gup_string_starts_with_cstr(html_rule, "uw_")) {
            if (!gup_array_string_contains(ultrawide_namespace_rules, taillight_rule)) {
                gup_array_string_append_arena(&a, &ultrawide_namespace_rules, taillight_rule);
            }
        } else if (!gup_array_string_contains(no_namespace_rules, taillight_rule)) {
            gup_array_string_append_arena(&a, &no_namespace_rules, taillight_rule);
        }
    }

    printf("WARNING: Taillight found the following class names but didn't recognize them. These are probably just custom classes you have, but you might want to check out this list just in case:\n");
    gup_array_string_print(unknown_rules);
    printf("Successfully generated taillight rules.\n");

    // Write the lines to the final css file 
    printf("Writing taillight rules to %s...\n", css_file_path);

    // NOTE: Writing this first line is actually a sort of hack to make sure we can append everything afterwards
    // but still be overwriting any old file that might be there. 
    gup_file_write_cstr("/* Stylesheet generated by taillight https://github.com/cbouwense/taillight */\n", css_file_path);
    gup_file_append_lines_arena(&a, no_namespace_rules, css_file_path);

    gup_file_append_line_cstr("\n/* Mobile */", css_file_path);
    gup_file_append_line_cstr("@media (max-width: 768px) {", css_file_path);
    gup_file_append_line_cstr(".mobile { display: inherit; }", css_file_path);
    gup_file_append_line_cstr(".tablet { display: none; }", css_file_path);
    gup_file_append_line_cstr(".computer { display: none; }", css_file_path);
    gup_file_append_line_cstr(".ultrawide { display: none; }", css_file_path);
    gup_file_append_line_cstr(":root { font-size: 14px; }", css_file_path);
    gup_file_append_lines_arena(&a, mobile_namespace_rules, css_file_path);
    gup_file_append_line_cstr("}", css_file_path);

    gup_file_append_line_cstr("\n/* Tablet */", css_file_path);
    gup_file_append_line_cstr("@media (min-width: 768px) and (max-width: 1024px) {", css_file_path);
    gup_file_append_line_cstr("  .mobile { display: none; }", css_file_path);
    gup_file_append_line_cstr("  .tablet { display: inherit; }", css_file_path);
    gup_file_append_line_cstr("  .computer { display: none; }", css_file_path);
    gup_file_append_line_cstr("  .ultrawide { display: none; }", css_file_path);
    gup_file_append_line_cstr("  :root { font-size: 14px; }", css_file_path);
    gup_file_append_lines_arena(&a, tablet_namespace_rules, css_file_path);
    gup_file_append_line_cstr("}", css_file_path);

    gup_file_append_line_cstr("\n/* Computer (desktop / laptop) */", css_file_path);
    gup_file_append_line_cstr("@media (min-width: 1024px) and (max-width: 3840px) {", css_file_path);
    gup_file_append_line_cstr("  .mobile { display: none; }", css_file_path);
    gup_file_append_line_cstr("  .tablet { display: none; }", css_file_path);
    gup_file_append_line_cstr("  .computer { display: inherit; }", css_file_path);
    gup_file_append_line_cstr("  .ultrawide { display: none; }", css_file_path);
    gup_file_append_line_cstr("  :root { font-size: 18px; }", css_file_path);
    gup_file_append_lines_arena(&a, computer_namespace_rules, css_file_path);
    gup_file_append_line_cstr("}", css_file_path);

    gup_file_append_line_cstr("\n/* Ultrawide */", css_file_path);
    gup_file_append_line_cstr("@media (min-width: 3840px) {", css_file_path);
    gup_file_append_line_cstr("  .mobile { display: none; }", css_file_path);
    gup_file_append_line_cstr("  .tablet { display: none; }", css_file_path);
    gup_file_append_line_cstr("  .computer { display: none; }", css_file_path);
    gup_file_append_line_cstr("  .ultrawide { display: inherit; }", css_file_path);
    gup_file_append_line_cstr("  :root { font-size: 18px; }", css_file_path); // TODO: do we maybe want a bigger font here?
    gup_file_append_lines_arena(&a, ultrawide_namespace_rules, css_file_path);
    gup_file_append_line_cstr("}", css_file_path);

    printf("Successfully wrote taillight rules to %s.\n", css_file_path);

    printf("All done, hope it looks good!\n");

    gup_arena_destroy(a);
    return 0;
}
