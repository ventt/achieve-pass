#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "econio.h"
#include "view.h"
#include "controller.h"
#include "debugmalloc.h"

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
    econio_clrscr();
    int menu_state = main_Screen;
    int exit = stay;

    struct FileEntry *fe;

    if (!is_file_exists()) {
        menu_state = reg_Screen;
    } else {
        fe = read_file();
    }

    while (exit) {
        int subject_id;
        switch (menu_state) {
            case reg_Screen:
                fe = create_new_save();
                saved_window();
                menu_state = main_Screen;
                break;
            case main_Screen:
                main_screen(fe, 0);
                printf("\ncommands: /addtime <SubjectId> <ExamId> , /checksubject <SubjectId>, /addsubject, /showdone, /exit\n");
                char *input = get_line_from_input();
                char *cmd = strtok(input, " ");

                if (strcmp(cmd, "/addtime") == 0) {
                    //Ellenorizzuk hogy a commandhoz jar-e id
                    char *check_subject_id_valid = strtok(NULL, " ");
                    if (check_subject_id_valid == NULL) {
                        menu_state = main_Screen;
                        econio_clrscr();
                        free(input);
                        break;
                    }
                    char *check_exam_id_valid = strtok(NULL, " ");
                    if (check_exam_id_valid == NULL) {
                        menu_state = main_Screen;
                        econio_clrscr();
                        free(input);
                        break;
                    }
                    char *check_time_valid = strtok(NULL, " ");
                    if (check_time_valid == NULL || atoi(check_time_valid) <= 0) {
                        menu_state = main_Screen;
                        econio_clrscr();
                        free(input);
                        break;
                    }

                    subject_id = atoi(check_subject_id_valid);
                    int exam_id = atoi(check_exam_id_valid);
                    int time = atoi(check_time_valid);
                    for (struct SubjectList_node *iterator = fe->subjects_list;
                         iterator != NULL; iterator = iterator->nextNode) {
                        if (iterator->data->id == subject_id) {
                            iterator->data->exams[exam_id - 1].hoursDone += time;
                            if (iterator->data->exams[exam_id - 1].hoursDone >= iterator->data->credits * 5) {
                                fe->achievement_points +=
                                        iterator->data->exams[exam_id - 1].hoursDone * iterator->data->credits;
                            }
                        }
                    }

                } else if (strcmp(cmd, "/addsubject") == 0) {
                    menu_state = add_Subject;
                } else if (strcmp(cmd, "/showdone") == 0) {
                    menu_state = done_Subject;
                } else if (strcmp(cmd, "/checksubject") == 0) {
                    //Ellenorizzuk hogy a commandhoz jar-e id
                    char *check_id_valid = strtok(NULL, " ");
                    if (check_id_valid != NULL) {
                        int id = atoi(check_id_valid);
                        /*for(struct SubjectList_node *it = fe->subjects_list; it != NULL; it = it->nextNode) {
                            if (id == it->data->id) {
                                subject_id = id;
                                menu_state = check_Subject;
                                break;
                            }
                        }*/
                        subject_id = id;
                        menu_state = check_Subject;
                        free(input);
                        break;
                    } else {
                        menu_state = main_Screen;
                        econio_clrscr();
                        free(input);
                        break;
                    }


                } else if (strcmp(cmd, "/exit") == 0) {
                    menu_state = exit_app;
                } else {
                    printf("\n Invalid command.");
                    menu_state = main_Screen;
                }
                econio_clrscr();
                free(input);
                break;
            case add_Subject:
                add_subject(fe);
                save(fe);
                saved_window();
                menu_state = main_Screen;
                break;
            case done_Subject:
                main_screen(fe, 1);
                printf("\ncommands: /checksubject <SubjectId>, /mainmenu, /exit\n");
                char *input_2 = get_line_from_input();
                char *cmd_2 = strtok(input_2, " ");
                if (strcmp(cmd_2, "/checksubject") == 0) {
                    //ellenorizzuk hogy jo-e az id
                    char *check_id_valid = strtok(NULL, " ");
                    if (check_id_valid != NULL) {
                        int id = atoi(check_id_valid);
                        /*for(struct SubjectList_node *it = fe->subjects_list; it != NULL; it = it->nextNode) {
                            if (id == it->data->id) {
                                subject_id = id;
                                menu_state = check_Subject;
                                break;
                            }
                        }*/
                        subject_id = id;
                        menu_state = check_Subject;
                        free(input_2);
                        break;
                    } else {
                        menu_state = done_Subject;
                        econio_clrscr();
                        free(input_2);
                        break;
                    }

                } else if (strcmp(cmd_2, "/exit") == 0) {
                    menu_state = exit_app;
                } else if (strcmp(cmd_2, "/mainmenu") == 0) {
                    menu_state = main_Screen;
                }
                econio_clrscr();
                free(input_2);
                break;
            case check_Subject:
                econio_clrscr();
                struct SubjectList_node *subject = check_subject_window(fe->subjects_list, subject_id);
                printf("\n");
                if (subject == NULL) {
                    econio_sleep(0.5);
                    econio_clrscr();
                    menu_state = main_Screen;
                    break;
                }
                econio_textcolor(COL_RESET);
                printf("\ncommands: /editdata <DataNumber> <data>, /addexam <year> <month> <day> ,/addtime <ExamId> <time> ,/mainmenu, /delete ,/exit\n");
                char *input_3 = get_line_from_input();
                char *cmd_3 = strtok(input_3, " ");

                if (strcmp(cmd_3, "/addtime") == 0) {
                    int exam_id = atoi(strtok(NULL, " "));
                    int time = atoi(strtok(NULL, " "));
                    for (struct SubjectList_node *iterator = fe->subjects_list;
                         iterator != NULL; iterator = iterator->nextNode) {
                        if (iterator->data->id == subject_id) {
                            iterator->data->exams[exam_id - 1].hoursDone += time;
                        }
                    }
                } else if (strcmp(cmd_3, "/editdata") == 0) {
                    int dataNumber = atoi(strtok(NULL, " "));
                    if (dataNumber == 1) {

                        char *new_name = strtok(NULL, " ");
                        free(subject->data->name);
                        subject->data->name = malloc(strlen(new_name) * sizeof(char) + 1);
                        strcpy(subject->data->name, new_name);

                    } else if (dataNumber == 2) {
                        subject->data->credits = atoi(strtok(NULL, " "));
                    } else if (dataNumber == 3) {

                        char *new_desc = strtok(NULL, " ");
                        free(subject->data->description);
                        subject->data->description = malloc(strlen(new_desc) * sizeof(char) + 1);
                        strcpy(subject->data->description, new_desc);
                    }
                } else if (strcmp(cmd_3, "/addexam") == 0) {
                    struct Date date;
                    date.year = atoi(strtok(NULL, " "));
                    date.month = atoi(strtok(NULL, " "));
                    date.day = atoi(strtok(NULL, " "));
                    add_exam(subject->data, date, 0);
                } else if (strcmp(cmd_3, "/mainmenu") == 0) {
                    save(fe);
                    menu_state = main_Screen;
                } else if (strcmp(cmd_3, "/exit") == 0) {
                    menu_state = exit_app;
                } else if (strcmp(cmd_3, "/delete") == 0) {
                    fe->subjects_list = delete_subject(fe, subject->data->id);
                    menu_state = main_Screen;
                } else {
                    printf("\n Invalid command.");
                    menu_state = check_Subject;
                }
                save(fe);
                saved_window();
                free(input_3);
                break;
            case exit_app:
                save(fe);
                saved_window();
                econio_textcolor(COL_BLUE);
                printf("Tovabbi jo tanulast %s!\n", fe->user);
                exit = turn_off;
                break;
        }
    }

    free_entry(fe);
    return 0;
}
