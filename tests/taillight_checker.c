#include "../guppy.h"
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("ERROR: Didn't receive a file to watch, or a command to execute when it updated.\n");
        printf("USAGE: ./taillight_checker file_path command\n");
        printf("EXAMPLE: ./taillight_checker index.html \"./taillight index.html\"\n");
        exit(1);
    }
    if (argc == 2) {
        printf("ERROR: Didn't receive a command to execute when your file is updated.\n");
        printf("USAGE: ./taillight_checker file_path command\n");
        printf("EXAMPLE: ./taillight_checker index.html \"./taillight index.html\"\n");
        exit(1);
    }
    if (argc > 3) {
        printf("ERROR: Receive too many arguments. Did you not wrap your command in double quotes?\n");
        printf("USAGE: ./taillight_checker file_path command\n");
        printf("EXAMPLE: ./taillight_checker index.html \"./taillight index.html\"\n");
        exit(1);
    }

    const char *file_path = argv[1];
    const char *command = argv[2];
    struct stat file_stat;
    time_t last_modified_time = 0;

    while(true) {
        gup_assert_verbose(stat(file_path, &file_stat) == 0, "Tried to read the metadata of the file you're watching, but wasn't able to for whatever reason.");
        
        time_t current_modified_time = file_stat.st_mtime;

        bool file_was_updated_since_last_checked = current_modified_time > last_modified_time;
        if (file_was_updated_since_last_checked) {
            // Do the thing you wanted to do when the file is updated
            system(command);
            printf("Last modified: %s", ctime(&file_stat.st_mtime));

            last_modified_time = current_modified_time;
        }

        usleep(34000); // Should be around 30 fps
    } 

    return 0;
}
