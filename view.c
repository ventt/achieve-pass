//
// Created by Adrian Szell on 2019. 11. 24..
//

#include "view.h"
#include "econio.h"
#include "controller.h"
#include <stdio.h>
#include <string.h>


void header() {
    econio_textcolor(COL_LIGHTBLUE);
    printf("    _        _     _                  ____               \n"
           "   / \\   ___| |__ (_) _____   _____  |  _ \\ __ _ ___ ___\n"
           "  / _ \\ / __| '_ \\| |/ _ \\ \\ / / _ \\ | |_) / _  / __/ __|\n"
           " / ___ \\ (__| | | | |  __/\\ V /  __/ |  __/ (_| \\__ \\__ \\\n"
           "/_/   \\_\\___|_| |_|_|\\___| \\_/ \\___| |_|   \\__,_|___/___/");
    printf("\nHelping absolving University\t\t  by Szell Adrian");
}

void status_bar(struct status_model model) {
    printf("\n\nAchievement Points = > %d\tAbsolved practicing => %d\n\n", model.achievement_points, model.absolved);
}

void progress_bar(int percentage) {
    econio_textcolor(COL_BLUE);
    printf(" ");
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
    econio_textcolor(COL_GREEN);
    printf("\n|");
    for (int i = 0; i < percentage / 2; i++) {
        printf(">");
    }
    printf("|");
    econio_textcolor(COL_BLUE);
    printf("\n ");
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
    printf("\n");
    econio_textcolor(COL_RESET);
}

void main_screen(struct main_screen_model model) {
    econio_set_title("Achieve Pass - Exams");
    struct status_model;
    econio_textcolor(COL_LIGHTBLUE);
    printf("Your Courses:\n\n");

    for (int i = 0; i < model.exams_size; i++) {
        struct main_screen_model_exam *exam = model.exams + i;

        econio_textcolor(COL_WHITE);
        printf("(%d) %s\n", i, exam->course_name);
        printf(" %d.exam\t %d hours left\n", exam->examNumber, 666);
        int allHour = exam->credit * 5;
        double percent = ((double) exam->elapsedHours / (double) allHour) * 100;
        printf(" %.0f%%\t%d/%d hours\n", percent, exam->elapsedHours, allHour);
        progress_bar((int) percent);
        printf("Commands: /addtime <CourseId> <ExamId> /addcourse\n"
               "/checkcourse <CourseId> /showdone\n");
    }
}

void reg_window() {
    header();
    printf("\n\n");
    char show_cool_stuff[36] = {"Create new profile >\nEnter name?> "};
    econio_textcolor(COL_CYAN);
    for (int i = 0; i < strlen(show_cool_stuff); i++) {
        printf("%c", show_cool_stuff[i]);
        econio_sleep(0.1);
        econio_flush();
    }

    econio_textcolor(COL_RESET);
}

