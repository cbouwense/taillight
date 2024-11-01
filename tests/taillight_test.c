#include "../guppy.h"

int main() {
    GupArena a = gup_arena_create();

    char html_file_path[32];
    char css_actual_file_path[32];
    char css_expected_file_path[32];
    char test_command[128];

    int test_num = 1;

    sprintf(html_file_path, "./tests/test%d.html", test_num);
    sprintf(css_actual_file_path, "./tests/test%d_actual.css", test_num);
    sprintf(css_expected_file_path, "./tests/test%d_expected.css", test_num);

    system("make -B -s");
    while (gup_file_exists(html_file_path)) {
        sprintf(test_command, "./taillight %s %s", html_file_path, css_actual_file_path);

        printf("Test %d...", test_num);
        system(test_command);

        gup_assert_verbose(gup_file_exists(css_expected_file_path), "Taillight didn't actually produce an output css file.");
        
        GupString expected = gup_file_read_arena(&a, css_expected_file_path);
        GupString actual = gup_file_read_arena(&a, css_actual_file_path);
        gup_assert_verbose(gup_string_eq(expected, actual), "The output css didn't match the expected!");

        printf("PASS\n");
        test_num++;
        sprintf(html_file_path, "./tests/test%d.html", test_num);
        sprintf(css_actual_file_path, "./tests/test%d_actual.css", test_num);

        // TODO: is this overkill?
        gup_arena_free(&a);
    }

    printf("All tests succeeded.\n");
    gup_arena_destroy(&a);
    return 0;
}
