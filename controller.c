//
// Created by Adrian Szell on 2019. 11. 25..
//
#include "controller.h"
#include "econio.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *get_line_from_input() { //always free when made its purpose
    int buf_size = 32, index = 0;
    char *line = calloc(buf_size, sizeof(char));
    if (line == NULL) {
        perror("Nem sikerult memoriat foglalni!");
        return NULL;
    }
    int ch = 1;

    while (ch) {
        ch = getchar();

        if (ch == '\n')
            ch = 0;

        if (buf_size <= index) {
            buf_size += 32;
            line = realloc(line, buf_size * sizeof(char));
        }
        line[index++] = ch;

    }
    line[index] = '\0';
    return line;
}

int string_to_date_array(char *string, int which) {
    int date[3];
    sscanf(string, "%d.%d.%d", &date[0], &date[1], &date[2]);
    if (which == 0) {
        return date[0];
    } else if (which == 1) {
        return date[1];
    } else {
        return date[2];
    }
}

time_t toTime(struct Date date) {
    // Forras: http://www.cplusplus.com/reference/ctime/mktime/
    time_t t;
    struct tm *tm;

    time(&t);
    tm = localtime(&t);
    tm->tm_year = date.year - 1900;
    tm->tm_mon = date.month - 1;
    tm->tm_mday = date.day;
    // Visszaadja masodpercben az eltelt idot a megadott datumohoz kepest
    time_t result = mktime(tm);
    free(tm);
    return result;
}

struct FileEntry *create_new_save() {
    econio_clrscr();
    reg_window();
    char *name = get_line_from_input();
    struct FileEntry *nf = malloc(sizeof(struct FileEntry));
    nf->user = name;
    nf->achievement_points = 0;
    nf->subjects_size = 0;
    nf->subjects_list = NULL;
    save(nf);
    free(name);
    return nf;
}

void add_subject(struct FileEntry *fileEntry) {
    add_subject_window();
    //ID kiosztas
    int max = 0;
    for (struct SubjectList_node *iterator = fileEntry->subjects_list;
         iterator != NULL; iterator = iterator->nextNode) {
        if (iterator->data->id > max) {
            max = iterator->data->id;
        }
    }
    int id = max + 1;

    struct SubjectEntry *subject = malloc(sizeof(struct SubjectEntry));
    struct SubjectList_node *new_node = malloc(sizeof(struct SubjectList_node));
    {
        subject->id = id;
        subject->name = NULL;
        subject->description = NULL;
        subject->exams_size = 0;
        subject->exams = NULL;
    }

    subject_window_details(1);
    subject->name = get_line_from_input();


    subject_window_details(2);
    char *creditStr = get_line_from_input();
    subject->credits = atoi(creditStr);
    free(creditStr);


    subject_window_details(3);
    subject->description = get_line_from_input();


    subject_window_details(4);
    char *numberOEStr = get_line_from_input();
    subject->exams_size = atoi(numberOEStr);
    free(numberOEStr);

    subject->exams = malloc(sizeof(struct ExamEntry) * subject->exams_size);

    for (int i = 1; i <= subject->exams_size; ++i) {
        subject->exams[i - 1].date.year = 0;
        subject->exams[i - 1].date.month = 0;
        subject->exams[i - 1].date.year = 0;


        add_subject_exam_date(i);
        char *date = get_line_from_input();
        subject->exams[i - 1].date.year = string_to_date_array(date, 0);
        subject->exams[i - 1].date.month = string_to_date_array(date, 1);
        subject->exams[i - 1].date.day = string_to_date_array(date, 2);

        add_subject_exam_hours_done(i);
        char *hoursDoneStr = get_line_from_input();
        subject->exams[i - 1].hoursDone = atoi(hoursDoneStr);
        free(hoursDoneStr);


    }
    new_node->data = subject;
    new_node->nextNode = NULL;
    if (fileEntry->subjects_list == NULL) {
        fileEntry->subjects_list = new_node;
        fileEntry->subjects_size++;
    } else {
        struct SubjectList_node *iterator;
        for (iterator = fileEntry->subjects_list; iterator->nextNode != NULL; iterator = iterator->nextNode);
        iterator->nextNode = new_node;
        fileEntry->subjects_size++;
    }
}

int is_exam_done(struct ExamEntry *examEntry, struct SubjectEntry *entry) {
    return examEntry->hoursDone >= entry->credits * 5;
}

int absolved_practicing(struct FileEntry *fe) {
    int result = 0;
    for (struct SubjectList_node *subject_it = fe->subjects_list;
         subject_it != NULL; subject_it = subject_it->nextNode) {
        for (int i = 0; i < subject_it->data->exams_size; i++) {
            // xnor
            if (is_exam_done(&subject_it->data->exams[i], subject_it->data)) {
                result++;
            }
        }
    }
    return result;
}

void main_screen(struct FileEntry *fileEntry, int showOnlyDone) {
    header();
    struct status_model statusModel;
    statusModel.achievement_points = fileEntry->achievement_points;
    statusModel.absolved = absolved_practicing(fileEntry);
    //kell meg a keszek

    status_bar(statusModel);
    struct main_screen_model new_msm;
    new_msm.exams_size = 0;
    if (fileEntry->subjects_size != 0) {
        //ossze szamolja az examokat
        for (struct SubjectList_node *subject_it = fileEntry->subjects_list;
             subject_it != NULL; subject_it = subject_it->nextNode) {
            for (int i = 0; i < subject_it->data->exams_size; i++) {
                // xnor
                if (showOnlyDone == is_exam_done(&subject_it->data->exams[i], subject_it->data)) {
                    new_msm.exams_size++;
                }
            }
        }
        new_msm.exams = malloc(new_msm.exams_size * sizeof(struct main_screen_model_exam));

        int idx = 0;
        for (struct SubjectList_node *subject_it = fileEntry->subjects_list;
             subject_it != NULL; subject_it = subject_it->nextNode) {

            for (int i = 0; i < subject_it->data->exams_size; i++) {
                if (showOnlyDone == is_exam_done(&subject_it->data->exams[i], subject_it->data)) {
                    new_msm.exams[idx].course_name = subject_it->data->name;
                    new_msm.exams[idx].course_id = subject_it->data->id;
                    new_msm.exams[idx].examNumber = i + 1;
                    new_msm.exams[idx].credit = subject_it->data->credits;
                    new_msm.exams[idx].elapsedHours = subject_it->data->exams[i].hoursDone;

                    time_t diff = toTime(subject_it->data->exams[i].date) - time(NULL);
                    new_msm.exams[idx].hoursLeft = (int) (diff - (diff % 86400) * 12 * 3600) / 3600;

                    idx++;
                }
            }
        }
    }
    main_screen_window(new_msm);
}

struct SubjectList_node *check_subject_window(struct SubjectList_node *list, int id) {
    //kikeresi a targyat
    header();
    int found = 0;
    struct SubjectList_node *subject;
    for (struct SubjectList_node *subject_it = list; subject_it != NULL; subject_it = subject_it->nextNode) {
        if (subject_it->data->id == id) {
            subject = subject_it;
            found = 1;
        }
    }
    if (found) {
        printf("\n");
        subject_window_details(1);
        printf("%s\n", subject->data->name);
        subject_window_details(2);
        printf("%d\n", subject->data->credits);
        subject_window_details(3);
        printf("%s\n", subject->data->description);
        subject_window_details(4);
        printf("%d", subject->data->exams_size);
        for (int i = 0; i < subject->data->exams_size; ++i) {
            printf("\n");
            add_subject_exam_date(i + 1);
            printf("%d.%d.%d", subject->data->exams[i].date.year, subject->data->exams[i].date.month,
                   subject->data->exams[i].date.day);
            printf("\n");
            add_subject_exam_hours_done(i + 1);
            printf("%d", subject->data->exams[i].hoursDone);
        }
        printf("\n");
    } else {
        printf("\nThere is no such Subject with this index!\n");
        return NULL;
    }

    econio_flush();
    return subject;
}


