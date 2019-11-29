//
// Created by Adrian Szell on 2019. 11. 24..
//

#ifndef ACHIEVE_PASS_VIEW_H
#define ACHIEVE_PASS_VIEW_H

#include "model.h"
#include "controller.h"

void header();

void progress_bar(int percentage);

void main_screen(struct main_screen_model);

void status_bar(struct status_model);

void reg_window();

#endif //ACHIEVE_PASS_VIEW_H
