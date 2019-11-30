//
// Created by Adrian Szell on 2019. 11. 25..
//
#include "controller.h"
#include "econio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


struct FileEntry create_new_save() {
    econio_clrscr();
    reg_window();
    char *name = get_line_from_input();
    struct FileEntry nf;
    nf.user = name;
    nf.achievement_points = 0;
    nf.subjects_size = 0;
    nf.subjects_list = NULL;
    save(&nf);
    free(name);
    return nf;
}

void add_subject(struct FileEntry *fileEntry, int id) {
    add_subject_window();
    struct SubjectEntry *subject = malloc(sizeof(struct SubjectEntry));
    struct SubjectList_node *new_node = malloc(sizeof(struct SubjectList_node));
    subject->id = id;


    add_subject_window_details(1);
    subject->name = get_line_from_input();


    add_subject_window_details(2);
    char *creditStr = get_line_from_input();
    subject->credits = atoi(creditStr);
    free(creditStr);


    add_subject_window_details(3);
    subject->description = get_line_from_input();


    add_subject_window_details(4);
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

void main_screen(struct FileEntry *fileEntry) {
    header();
    struct status_model statusModel;
    statusModel.achievement_points = fileEntry->achievement_points;
    status_bar();
    struct main_screen_model new_msm;
    new_msm.exams_size = 0;
    for (struct SubjectList_node *iterator = fileEntry->subjects_list;
         iterator != NULL; iterator = iterator->nextNode) {
        new_msm.exams_size += iterator->data->exams_size;
    }
    new_msm.exams = malloc(new_msm.exams_size * sizeof(struct main_screen_model_exam));
    int idx = 0;
    for (struct SubjectList_node *iterator = fileEntry->subjects_list;
         iterator != NULL; iterator = iterator->nextNode) {
        int i;
        for (i = 0; i < iterator->data->exams_size; ++i) {
            new_msm.exams[i + idx].course_name = iterator->data->name;
            new_msm.exams[i + idx].courseNumber = iterator->data->id;
            new_msm.exams[i + idx].examNumber = i + 1;
            new_msm.exams[i + idx].credit = iterator->data->credits;
            new_msm.exams[i + idx].elapsedHours = iterator->data->exams[i].hoursDone;
        }
        idx += idx + i + 1;
    }
    main_screen_window(new_msm);
}

