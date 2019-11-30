#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "econio.h"
#include "view.h"
#include "model.h"
#include "controller.h"


int main() {

    /*{
        struct FileEntry *fileEntry;
        fileEntry->user = "Adrian";
        fileEntry->achievement_points = 50;
        fileEntry->subjects_size = 2;
        struct SubjectEntry *se1 = malloc(sizeof(struct SubjectEntry));
        struct SubjectEntry *se2 = malloc(sizeof(struct SubjectEntry));
        se1->id = 1;
        se1->name = "analizs";
        se1->description = "szar";
        se1->credits = 6;
        se1->exams_size = 2;
        se1->exams = malloc(sizeof(struct ExamEntry) * se1->exams_size);

        se1->exams[0].hoursDone = 20;
        se1->exams[0].date.year = 2019;
        se1->exams[0].date.month = 2;
        se1->exams[0].date.day = 1;

        se1->exams[1].hoursDone = 25;
        se1->exams[1].date.year = 2019;
        se1->exams[1].date.month = 3;
        se1->exams[1].date.day = 4;

        se2->id = 2;
        se2->name = "bsz";
        se2->description = "fos";
        se2->credits = 6;
        se2->exams_size = 2;
        se2->exams = malloc(sizeof(struct ExamEntry) * se1->exams_size);

        se2->exams[0].hoursDone = 20;
        se2->exams[0].date.year = 2019;
        se2->exams[0].date.month = 2;
        se2->exams[0].date.day = 1;

        se2->exams[1].hoursDone = 25;
        se2->exams[1].date.year = 2019;
        se2->exams[1].date.month = 3;
        se2->exams[1].date.day = 4;
        fileEntry->subjects_list = malloc(sizeof(struct SubjectList_node));
        fileEntry->subjects_list->data = se1;
        fileEntry->subjects_list->nextNode = malloc(sizeof(struct SubjectList_node));
        fileEntry->subjects_list->nextNode->data = se2;

        save(fileEntry);
        free_entry(fileEntry);
    }
    {
        struct FileEntry *new_file_entry;
        new_file_entry = read();
        save(new_file_entry);
        free_entry(new_file_entry);
    }*/
    struct FileEntry fe = create_new_save();
    saved_window();
    add_subject(&fe, 1);
    saved_window();
    add_subject(&fe, 2);
    saved_window();
    save(&fe);
    econio_clrscr();
    main_screen(&fe);

    return 0;
}
