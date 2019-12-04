//
// Created by Adrian Szell on 2019. 11. 25..
//

#ifndef ACHIEVE_PASS_CONTROLLER_H
#define ACHIEVE_PASS_CONTROLLER_H

#include "data.h"
#include "model.h"
#include "view.h"
#include "debugmalloc.h"

char *get_line_from_input();

struct FileEntry *create_new_save();

void add_subject(struct FileEntry *fileEntry);

void main_screen(struct FileEntry *fileEntry, int showOnlyDone);

struct SubjectList_node *check_subject_window(struct SubjectList_node *list, int id);

int absolved_practicing(struct FileEntry *fe);

#endif //ACHIEVE_PASS_CONTROLLER_H
