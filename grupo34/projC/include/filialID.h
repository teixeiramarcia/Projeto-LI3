#ifndef LI3_FILIALID_H
#define LI3_FILIALID_H

#include <stddef.h>

enum filialID {
    filial_1 = 0,
    filial_2 = 1,
    filial_3 = 2,
    filial_todas = -1
};

#define INT_2_FILIAL(i) ((FilialID) ((i) - 1))

typedef enum filialID FilialID;

#define N_FILIAIS 3

extern const FilialID FILIAIS[N_FILIAIS];

#endif //LI3_FILIALID_H
