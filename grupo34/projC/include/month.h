#ifndef LI3_MONTH_H
#define LI3_MONTH_H

#include <stddef.h>

enum month {
    janeiro = 0,
    fevereiro = 1,
    marco = 2,
    abril = 3,
    maio = 4,
    junho = 5,
    julho = 6,
    agosto = 7,
    setembro = 8,
    outubro = 9,
    novembro = 10,
    dezembro = 11
};

#define INT_2_MONTH(i) ((Month) ((i) - 1))

typedef enum month Month;

char* mes_to_string(Month mes);

extern Month const MONTHS[];

#define N_MONTHS 12

#endif //LI3_MONTH_H
