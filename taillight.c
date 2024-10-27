#include "guppy.h"

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
    gup_string_append_cstr_arena(a, &taillight_rule, " { ");

    gup_array_string_print(name_and_namespace_as_tokens);
    printf("has_namespace: %d\n", has_namespace);

    if (gup_string_eq_cstr(abbreviated_name, "absolute")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "position: absolute");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignStart")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: flex-start");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignEnd")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: flex-end");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignCenter")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: center");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignBaseline")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: baseline");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "alignStretch")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "align-items: stretch");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "b")) {
        // TODO: border is a strange one, it has such variable values, not sure how to process it yet. 
        gup_string_append_cstr_arena(a, &taillight_rule, "border: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "bb")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "bg")) {
        if (gup_string_eq_cstr(value_and_units, "default")) {
            gup_string_append_cstr_arena(a, &taillight_rule, "background-color: var(--background-color)");
        } else {
            gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        }
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "bl")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "br")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "brad")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-radius: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "bt")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "border-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "bottom")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "bx")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\nborder-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "border-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n}\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "by")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\nborder-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "border-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n}\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "c")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "color: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "column")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "flex-direction: column ");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "dot")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "list-style-type: disc");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");

        gup_string_append_cstr_arena(a, &taillight_rule, "margin-left: 1.5rem");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
        gup_string_append_cstr_arena(a, &taillight_rule, "}\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "fixed")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "position: fixed");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "flex")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "display: flex");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "fs")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "font-size: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "gap")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "gap: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "h")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "height: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "hoverable")) {
        // .hoverable {
        //   color: var(--text-primary-color);
        //   transition: color 0.25s ease;
        // }
        gup_string_append_cstr_arena(a, &taillight_rule, "\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "color: var(--text-primary-color)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
        gup_string_append_cstr_arena(a, &taillight_rule, "transition: color 0.25s ease");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
        gup_string_append_cstr_arena(a, &taillight_rule, "}\n");
        
        // .hoverable:hover {
        //   color: var(--text-secondary-color);
        // }
        gup_string_append_cstr_arena(a, &taillight_rule, ".hoverable:hover {\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "color: var(--text-secondary-color)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
        gup_string_append_cstr_arena(a, &taillight_rule, "}\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyStart")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: flex-start");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyEnd")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: flex-end");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyCenter")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: center");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyBetween")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: space-between");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyAround")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: space-around");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyEvenly")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: space-evenly");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "justifyStretch")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "{ justify-content: stretch");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "left")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "m")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "maxh")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "max-height: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "maxw")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "max-width: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "mb")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "minh")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "min-height: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "minw")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "min-width: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "ml")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "mr")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "mt")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "mx")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\n");
 
        if (has_namespace) gup_string_append_cstr_arena(a, &taillight_rule, "    ");
        gup_string_append_cstr_arena(a, &taillight_rule,                    "margin-left: ");
        gup_string_append_str_arena(a, &taillight_rule,                     value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule,  " !important");
        gup_string_append_cstr_arena(a, &taillight_rule,                    ";\n");

        if (has_namespace) gup_string_append_cstr_arena(a, &taillight_rule, "    ");
        gup_string_append_cstr_arena(a, &taillight_rule,                    "margin-right: ");
        gup_string_append_str_arena(a, &taillight_rule,                     value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule,  " !important");
        gup_string_append_cstr_arena(a, &taillight_rule,                    ";\n");
        if (has_namespace) gup_string_append_cstr_arena(a, &taillight_rule, "  ");
        gup_string_append_cstr_arena(a, &taillight_rule,                    "}");
    } else if (gup_string_eq_cstr(abbreviated_name, "my")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\nmargin-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "margin-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n}\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "p")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "pb")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "pl")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "pr")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "pt")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "px")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\npadding-left: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n}\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "py")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "\npadding-top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n");
        gup_string_append_cstr_arena(a, &taillight_rule, "padding-bottom: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, ";\n}\n");
    } else if (gup_string_eq_cstr(abbreviated_name, "right")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "right: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "relative")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "position: relative");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "row")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "flex-direction: row");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowSm")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 1px 2px 0 rgb(0, 0, 0, 0.05)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadow")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 1px 3px 0 rgb(0, 0, 0, 0.1), 0 1px 2px -1px rgb(0, 0, 0, 0.1)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowMd")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 4px 6px -1px rgb(0, 0, 0, 0.1), 0 2px 4px -2px rgb(0, 0, 0, 0.1)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowLg")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 10px 15px -3px rgb(0, 0, 0, 0.1), 0 4px 6px -4px rgb(0, 0, 0, 0.1)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowXl")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 20px 25px -5px rgb(0, 0, 0, 0.1), 0 8px 10px -6px rgb(0, 0, 0, 0.1)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowXxl")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 25px 50px -12px rgb(0, 0, 0, 0.25)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowInner")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: inset 0 2px 4px 0 rgb(0, 0, 0, 0.05)");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "shadowNone")) { 
        gup_string_append_cstr_arena(a, &taillight_rule, "box-shadow: 0 0 #0000");
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "top")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "top: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "w")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "width: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
    } else if (gup_string_eq_cstr(abbreviated_name, "z")) {
        gup_string_append_cstr_arena(a, &taillight_rule, "z-index: ");
        gup_string_append_str_arena(a, &taillight_rule, value_and_units);
        if (is_important) gup_string_append_cstr_arena(a, &taillight_rule, " !important");
        gup_string_append_cstr_arena(a, &taillight_rule, "; }");
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
