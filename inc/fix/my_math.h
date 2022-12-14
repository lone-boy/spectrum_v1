//
// Created by jcc on 22-11-30.
//

#ifndef SPECTRUM_MY_MATH_H
#define SPECTRUM_MY_MATH_H

#include <cmath>
#include "QVector"

int get_one_number_from_position(double input,int index);

/**
 * Moving average algorithm
 * */

void fft_data_average(QVector<double>& src_data,int average_point,int all_sample_size);

float set_window(int16_t i, int size, int index, int window_type);

void get_window_coefficient(float *coefficient,int size,int window_type);
#endif //SPECTRUM_MY_MATH_H
