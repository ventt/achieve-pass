//
// Created by Adrian Szell on 2019. 11. 25..
//

#ifndef ACHIEVE_PASS_CONTROLLER_H
#define ACHIEVE_PASS_CONTROLLER_H

#include "data.h"
#include "model.h"
#include "view.h"

char *get_line_from_input();

struct FileEntry create_new_save();

void add_subject(struct FileEntry *fileEntry, int id);

void main_screen(struct FileEntry *fileEntry);

#endif //ACHIEVE_PASS_CONTROLLER_H
