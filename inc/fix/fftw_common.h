//
// Created by jcc on 22-11-28.
//

#ifndef SPECTRUM_FFTW_COMMON_H
#define SPECTRUM_FFTW_COMMON_H
#include "unistd.h"
#include <cstdint>
#include "fftw3.h"
#include "cstring"
#include "complex"

typedef fftwf_complex DSPCOMPLEX;
class common_fft{
public:
    common_fft(int32_t size);
    ~common_fft(void);

    DSPCOMPLEX *getVector(void);
    void do_FFT(void);
//    void do_IFFT(void);
    void do_Shift(void);
    DSPCOMPLEX *resetVecotr(int32_t size);

private:
    DSPCOMPLEX *_vector;
    fftwf_plan _plan;
    int32_t _fft_size;
};

//class common_ifft{
//public:
//    common_ifft(uint32_t);
//    ~common_ifft(void);
//
//    fftw_complex  *get_vector(void);
//    void do_IFFT(void);
//
//private:
//    fftw_plan _plan;
//    fftw_complex *_vector;
//};

#endif //SPECTRUM_FFTW_COMMON_H
