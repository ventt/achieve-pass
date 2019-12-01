#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "econio.h"
#include "view.h"
#include "model.h"
#include "controller.h"

enum menu {
    reg_Screen, // 0
    main_Screen, // 1
    add_Subject, // 2
    done_Subject, // 3
    check_Subject, // 4
    exit_app // 5
};
enum exit_value {
    turn_off,
    stay,
};

int main() {
    int menu_state = main_Screen;
    int exit = stay;

    struct FileEntry *fe;

    if (!is_file_exists()) {
        menu_state = reg_Screen;
    } else {
        fe = read();
    }

    while (exit) {
        switch (menu_state) {
            case reg_Screen:
                fe = create_new_save();
                saved_window();
                menu_state = main_Screen;
                break;
            case main_Screen:
                main_screen(fe, 0);
                printf("Parancs >");
                menu_state = atoi(get_line_from_input());
                break;
            case add_Subject:
                add_subject(fe, 6);
                save(fe);
                saved_window();
                menu_state = main_Screen;
                break;
            case done_Subject:
                main_screen(fe, 1);
                menu_state = atoi(get_line_from_input());
                break;
            case check_Subject:
                printf("Hianyzo funkcio");
                saved_window();
                menu_state = main_Screen;
                break;
            case exit_app:
                save(fe);
                saved_window();
                exit = turn_off;
                break;
        }
    }

    free_entry(fe);
    return 0;
}
