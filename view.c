//
// Created by Adrian Szell on 2019. 11. 24..
//

#include "view.h"
#include "econio.h"
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

void main_screen_window(struct main_screen_model model) {
    econio_set_title("Achieve Pass - Exams");
    econio_textcolor(COL_LIGHTBLUE);
    printf("Your Courses:\n\n");
    if (model.exams_size != 0) {
        for (int i = 0; i < model.exams_size; i++) {
            struct main_screen_model_exam *exam = model.exams + i;

            econio_textcolor(COL_WHITE);
            printf("(%d) %s\n", exam->course_id, exam->course_name);
            if (model.exams->hoursLeft < 0) {
                printf(" %d.exam\t expired\n", exam->examNumber);
            } else {
                printf(" %d.exam\t %d hours left\n", exam->examNumber, exam->hoursLeft);
            }

            int allHour = exam->credit * 5;
            double percent = ((double) exam->elapsedHours / (double) allHour) * 100;
            printf(" %.0f%%\t%d/%d hours\n", percent, exam->elapsedHours, allHour);
            progress_bar((int) percent);

        }
    } else {
        econio_textcolor(COL_CYAN);
        printf(" _  _ __     ___ _  _  __  __  __ ___    ____ __     ___ _  _ __ _    _ \n"
               "( \\( )  \\   (  _| \\/ )(  )(  \\/  ) __)  (_  _)  \\   / __| )( )  ( \\/\\/ )\n"
               " )  ( () )   ) _))  ( /__\\ )    (\\__ \\    )(( () )  \\__ \\)__( () )    / \n"
               "(_)\\_)__/   (___|_/\\_|_)(_|_/\\/\\_|___/   (__)\\__/   (___(_)(_)__/ \\/\\/  ");
        econio_textcolor(COL_RESET);
        printf("\n");
    }

    if (model.exams_size > 0) {
        free(model.exams);
    }
    econio_flush();
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

void add_subject_window() {
    header();
    printf("\n\n Add new course\n");

}

void subject_window_details(int edit_choice_to_show) {
    switch (edit_choice_to_show) {
        case 1:
            printf("(1) Course Name = ");
            break;
        case 2:
            printf("(2) Worth of credits = ");
            break;
        case 3:
            printf("(3) Describe = ");
            break;
        case 4:
            printf("    Number of Exams = ");
            break;
        default:
            break;
    }
}

void add_subject_exam_date(int exam_idx) {
    printf("\t%d.Exam > Date of exam(YYYY.MM.DD) = ", exam_idx + 1);
}

void add_subject_exam_hours_done(int exam_idx) {
    printf("\t%d.Exam > Hours done = ", exam_idx + 1);
}

void saved_window() {
    econio_textcolor(COL_GREEN);
    econio_clrscr();
    printf("     _______.     ___      ____    ____  _______  _______  \n"
           "    /       |    /   \\     \\   \\  /   / |   ____||       \\ \n"
           "   |   (----`   /  ^  \\     \\   \\/   /  |  |__   |  .--.  |\n"
           "    \\   \\      /  /_\\  \\     \\      /   |   __|  |  |  |  |\n"
           ".----)   |    /  _____  \\     \\    /    |  |____ |  '--'  |\n"
           "|_______/    /__/     \\__\\     \\__/     |_______||_______/ \n"
           "                                                           ");
    printf("\n");
    econio_flush();
    econio_sleep(1);
    econio_textcolor(COL_RESET);
    econio_clrscr();
}

