//
// Created by Adrian Szell on 2019. 11. 23..
//

#include "data.h"
#include <stdio.h>
#include <stdlib.h>

char *readLine(FILE *fp) {
    char buf[1024];
    int i = 0;
    int newLine = 0;

    while (!newLine) {
        int c;
        c = fgetc(fp);

        if (c == '\n') {
            newLine = 1;
        } else {
            buf[i++] = (char) c;
        }
    }
    buf[i++] = '\0';

    char *result = calloc(i + 1, sizeof(char));
    strlcpy(result, buf, i + 1);
    return result;
}

int readLineInt(FILE *fp) {
    return atoi(readLine(fp));
}

struct Date readDate(FILE *fp) {
    struct Date date;

    date.year = readLineInt(fp);
    date.month = readLineInt(fp);
    date.day = readLineInt(fp);

    return date;
}

void save(struct FileEntry *fe) {
    FILE *fp;
    fp = fopen("save.txt", "w");

    fprintf(fp, "%s\n", fe->user);
    fprintf(fp, "%d\n", fe->achievement_points);
    fprintf(fp, "%d\n", fe->subjects_size);
    fflush(fp);
    if (fe->subjects_list != NULL) {
    for (struct SubjectList_node *list_iterator = fe->subjects_list;
         list_iterator != NULL; list_iterator = list_iterator->nextNode) {
        fprintf(fp, "%d\n", list_iterator->data->id);
        fprintf(fp, "%s\n", list_iterator->data->name);
        fprintf(fp, "%s\n", list_iterator->data->description);
        fprintf(fp, "%d\n", list_iterator->data->credits);
        fprintf(fp, "%d\n", list_iterator->data->exams_size);

        for (int exam_idx = 0; exam_idx < list_iterator->data->exams_size; exam_idx++) {
            struct ExamEntry exam = list_iterator->data->exams[exam_idx];
            fprintf(fp, "%d\n", exam.date.year);
            fprintf(fp, "%d\n", exam.date.month);
            fprintf(fp, "%d\n", exam.date.day);
            fprintf(fp, "%d\n", exam.hoursDone);
        }
    }
    fflush(fp);
    }
    fclose(fp);
}

struct FileEntry *read() {
    FILE *fp;
    fp = fopen("save.txt", "r");

    struct FileEntry *fileEntry = malloc(sizeof(struct FileEntry));

    fileEntry->user = readLine(fp);
    fileEntry->achievement_points = readLineInt(fp);
    fileEntry->subjects_size = readLineInt(fp);
    fileEntry->subjects_list = malloc(sizeof(struct SubjectList_node));
    fileEntry->subjects_list->data = NULL;

    for (int subject_idx = 0; subject_idx < fileEntry->subjects_size; subject_idx++) {

        struct SubjectEntry *new_subject = malloc(sizeof(struct SubjectEntry));

        new_subject->id = readLineInt(fp);
        new_subject->name = readLine(fp);
        new_subject->description = readLine(fp);
        new_subject->credits = readLineInt(fp);
        new_subject->exams_size = readLineInt(fp);
        new_subject->exams = calloc(new_subject->exams_size, sizeof(struct SubjectEntry));

        for (int exam_idx = 0; exam_idx < new_subject->exams_size; exam_idx++) {
            struct ExamEntry exam;
            exam.date = readDate(fp);
            exam.hoursDone = readLineInt(fp);
            new_subject->exams[exam_idx] = exam;
        }
        if (fileEntry->subjects_list->data == NULL) {
            fileEntry->subjects_list->data = new_subject;
            fileEntry->subjects_list->nextNode = NULL;
        } else {
            struct SubjectList_node *new_node = malloc(sizeof(struct SubjectList_node));
            new_node->data = new_subject;
            struct SubjectList_node *list_iterator = fileEntry->subjects_list;
            while (list_iterator->nextNode != NULL) {
                list_iterator = list_iterator->nextNode;
            }
            list_iterator->nextNode = new_node;
            new_node->nextNode = NULL;
        }

    }
    fclose(fp);
    return fileEntry;
}

void free_entry(struct FileEntry *fileEntry) {
    free(fileEntry->user); //12. sor 3.

    struct SubjectList_node *next = fileEntry->subjects_list;
    while (next != NULL) {
        struct SubjectList_node *current = next;
        next = next->nextNode;

        free(current->data->name); //12. sor 1.
        free(current->data->description); //12. sor 2.
        free(current->data->exams); //99. sor
        free(current); //111. sor
    }

    free(fileEntry);
}
