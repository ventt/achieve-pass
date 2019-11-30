//
// Created by Adrian Szell on 2019. 11. 24..
//

#ifndef ACHIEVE_PASS_VIEW_H
#define ACHIEVE_PASS_VIEW_H

#include "model.h"
#include "controller.h"

void header();

void progress_bar(int percentage);

void main_screen_window(struct main_screen_model model);

void status_bar(struct status_model);

void reg_window();

void add_subject_window();

void add_subject_window_details(int edit_choice_to_show);

void add_subject_exam_date(int exam_idx);

void add_subject_exam_hours_done(int exam_idx);

void saved_window();

#endif //ACHIEVE_PASS_VIEW_H
