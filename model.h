//
// Created by Adrian Szell on 2019. 11. 24..
//

#ifndef ACHIEVE_PASS_MODEL_H
#define ACHIEVE_PASS_MODEL_H

/**
 * Status bar
 */
struct status_model {
    int achievement_points;
    int absolved;
};

/**
 * Main Screen
 */
struct main_screen_model_exam {
    char *course_name;
    int courseNumber, credit, examNumber, elapsedHours;
};
struct main_screen_model {
    int exams_size;
    struct main_screen_model_exam *exams;
};
#endif //ACHIEVE_PASS_MODEL_H
