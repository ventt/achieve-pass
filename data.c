//
// Created by Adrian Szell on 2019. 11. 23..
//

#include "data.h"

void createNewProfile(FILE *fp, char *userName) {
    if (fp != NULL) {
        fprintf(fp, "%s\n", userName);
        fprintf(fp, "0\n");
    } else {
        perror("Sikertelen fajl eleres");
    }
    fclose(fp);
}

void create(FILE *fp, struct FileEntry *file) {
    if (fp != NULL) {
        fprintf(fp, "%d\n", file->id);
        fprintf(fp, "%s\n", file->subject);
        fprintf(fp, "%s\n", file->description);
        fprintf(fp, "%d\n", file->credits);
        fprintf(fp, "%d\n", file->numberOfExams);
        /*for (int i = 0; i < file->numberOfExams; ++i){
            fprintf(fp,"%d.%d.%d\n"file->exams[i].date.year,file->exams[i].date.month,file->exams[i].date.day);
            fprintf(fp,"%d\n"file->exams[i].hoursDone);
        }*/
    } else {
        perror("Sikertelen fajl eleres");
    }
    fclose(fp);
}