#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "econio.h"
#include "view.h"
#include "model.h"
#include "controller.h"


int main() {

    struct FileEntry *fileEntry;

    /* struct SubjectEntry s1;
     {
         s1.id = 1;
         s1.name = "Subject 1";
         s1.description = "Subect 1 Description";
         s1.credits = 5;
         s1.exams_size = 2;
         s1.exams = calloc(2, sizeof(struct ExamEntry));

         {
             struct ExamEntry examEntry;
             examEntry.date.day = 1;
             examEntry.date.month = 2;
             examEntry.date.year = 2019;
             examEntry.hoursDone = 3;

             s1.exams[0] = examEntry;
         }
         {
             struct ExamEntry examEntry;
             examEntry.date.day = 2;
             examEntry.date.month = 3;
             examEntry.date.year = 2020;
             examEntry.hoursDone = 4;

             s1.exams[1] = examEntry;
         }
     }

     fileEntry.user = "Adrian";
     fileEntry.subjects_size = 1;
     fileEntry.subjects_list = calloc(1, sizeof(struct SubjectEntry));
     fileEntry.subjects_list[0] = s1;*/

    fileEntry = read();
    save(fileEntry);
    //free(fileEntry);
    //fileEntry = read();
    //save(fileEntry);
    return 0;
}
