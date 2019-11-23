//
// Created by Adrian Szell on 2019. 11. 23..
//

#ifndef ACHIEVE_PASS_DATA_H
#define ACHIEVE_PASS_DATA_H
#include <stdio.h>
#include <string.h>

struct Date {
    int year, month, day;
};

struct ExamEntry {
    struct Date date;
    int hoursDone;
};

struct FileEntry {
    int id;
    char *subject;
    char *description;
    short credits;
    short numberOfExams;
    struct ExamEntry exams[];
};
void createNewProfile();
void create(FILE* fp,struct FileEntry* FileEntry);
struct FileEntry retrieveEntry(int id);
void update(struct FileEntry);
struct FileEntry delete(int id);
#endif //ACHIEVE_PASS_DATA_H
