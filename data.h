//
// Created by Adrian Szell on 2019. 11. 23..
//

#ifndef ACHIEVE_PASS_DATA_H
#define ACHIEVE_PASS_DATA_H

#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"

struct Date {
    int year, month, day;
};

struct ExamEntry {
    struct Date date;
    int hoursDone;
};

struct SubjectEntry {
    int id;
    char *name;
    char *description;
    int credits;
    int exams_size;
    struct ExamEntry *exams;
};

struct FileEntry {
    char *user;
    int achievement_points;
    int subjects_size;
    struct SubjectList_node *subjects_list;
};
struct SubjectList_node {
    struct SubjectEntry *data;
    struct SubjectList_node *nextNode;
};

void save(struct FileEntry *fileEntry);

struct FileEntry *read_file();

void free_entry(struct FileEntry *fileEntry);

int is_file_exists();

struct SubjectList_node *delete_subject(struct SubjectList_node *, int);

void add_exam(struct SubjectEntry *subjectEntry, struct Date date, int hoursDone);

#endif //ACHIEVE_PASS_DATA_H
