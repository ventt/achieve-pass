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
    strcpy(result, buf);
    return result;
}

int readLineInt(FILE *fp) {
    char *str = readLine(fp);
    int i = atoi(str);
    free(str);
    return i;
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

int is_file_exists() {
    int result;
    FILE *fp = fopen("save.txt", "r");

    if (fp)
        result = 1;
    else
        result = 0;

    fclose(fp);
    return result;
}

struct FileEntry *read_file() {
    FILE *fp;
    fp = fopen("save.txt", "r");

    struct FileEntry *fileEntry = malloc(sizeof(struct FileEntry));

    fileEntry->user = readLine(fp);
    fileEntry->achievement_points = readLineInt(fp);
    fileEntry->subjects_size = readLineInt(fp);
    fileEntry->subjects_list = NULL;

    if (fileEntry->subjects_size) {
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
    }
    fclose(fp);
    return fileEntry;
}

void free_subject_node(struct SubjectList_node *node) {
    free(node->data->name); //12. sor 1.
    free(node->data->description); //12. sor 2.
    free(node->data->exams); //99. sor
    free(node->data);
    free(node); //111. sor
}

struct SubjectList_node *delete_subject(struct FileEntry *fileEntry, int id) {
    struct SubjectList_node *tmp;
    struct SubjectList_node *list = fileEntry->subjects_list;
    if (list->data->id == id) {
        tmp = list;
        list = list->nextNode;
        free_subject_node(tmp);
        fileEntry->subjects_size--;
        return list;
    }

    struct SubjectList_node *iterator;

    for (iterator = list; iterator != NULL; iterator = iterator->nextNode) {
        if (iterator->nextNode->data->id == id) {
            tmp = iterator->nextNode;
            iterator->nextNode = tmp->nextNode;
            free_subject_node(tmp);
            fileEntry->subjects_size--;
            return list;
        }
        if (iterator->nextNode->nextNode == NULL && iterator->nextNode->data->id == id) {
            tmp = iterator->nextNode;
            iterator->nextNode = NULL;
            free_subject_node(tmp);
            fileEntry->subjects_size--;
            return list;
        }
    }
    return list;
}

//Hozzafuz egy uj examat a subjecthez
void add_exam(struct SubjectEntry *subjectEntry, struct Date date, int hoursDone) {
    subjectEntry->exams = realloc(subjectEntry->exams, ++subjectEntry->exams_size * sizeof(struct ExamEntry));

    struct ExamEntry exam;
    exam.date = date;
    exam.hoursDone = hoursDone;

    subjectEntry->exams[subjectEntry->exams_size - 1] = exam;
}

void free_entry(struct FileEntry *fileEntry) {
    free(fileEntry->user); //12. sor 3.

    if (fileEntry->subjects_size) {
        struct SubjectList_node *tmp;
        struct SubjectList_node *it;
        for (it = fileEntry->subjects_list; it != NULL;) {
            tmp = it;
            it = it->nextNode;
            free_subject_node(tmp);
        }
    }

    free(fileEntry);
}


