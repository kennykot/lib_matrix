//  Copyright 2022 jewfishc
#ifndef SRC_S21_TEST_H_
#define SRC_S21_TEST_H_

#include <check.h>

#include "s21_matrix.h"

static const double mtr_3x3[3][3] = {
    {0.15, 0.0, -3.64},
    {8.53, -4.1321, 123.32},
    {0.0, 12.5, -78.321},
};

double test[10] = {1,     -1,      0,         0.000001, 0.00000001,
                   10000, 1000000, 1234.5678, 1234567,  12345678};

#endif  // SRC_S21_TEST_H_
