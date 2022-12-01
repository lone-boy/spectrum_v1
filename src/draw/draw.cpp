//
// Created by jcc on 22-12-1.
//
#include "draw/draw.h"


spectrumProcess::spectrumProcess(QCustomPlot *custcomPlot, DataBuffer<double> *buffer_data,
                                 double input_sample_rate, double average_count) {
    this->_spectrum_draw = new SpectrumScope(custcomPlot);

    this->_buffer_data = buffer_data;
    this->_sample_rate = input_sample_rate;
    this->_average_cout = average_count;
    this->_is_running = false;


    _buffer_data = new DataBuffer<double>(10*1024);
    _spectrum_fft = new common_fft(1024);
    _spectrumBuffer_fft = _spectrum_fft->getVector();

    _cos10k = new SINCOS("COS", _sample_rate, 1024, 100e3);
//    _cos10k->save_source_file("cos2e3.txt");
}

spectrumProcess::~spectrumProcess() {
    free(_spectrum_draw);
}

void spectrumProcess::run() {
    DSPCOMPLEX *dataBuffer;
    dataBuffer =  _cos10k->get_source_ptr();
    uint32_t set_size = _buffer_data->put_data_into_buffer((void*)dataBuffer,2 * _cos10k->get_source_size());

    uint32_t get_size = _buffer_data->get_data_from_buffer(_spectrumBuffer_fft,2 * _cos10k->get_source_size());
    if(get_size != 0){
        _spectrum_fft->do_FFT();
        _spectrum_fft->do_Shift();

        QVector<double> x_fft(1024);
        for(int i = 0;i<x_fft.size();i++){
            x_fft[i] = _sample_rate / 1024 * i - _sample_rate / 2;
        }
        QVector<double> y_fft(1024);
        for(int i = 0;i<y_fft.size();i++){
            double M = sqrt(_spectrumBuffer_fft[i][0]*_spectrumBuffer_fft[i][0] + _spectrumBuffer_fft[i][1]*_spectrumBuffer_fft[i][1]);
            double A = 2 * M / 1024;
            y_fft[i] = 20 * log10(A / 1e3);
        }
        _spectrum_draw->display(x_fft,y_fft);

    }


    while(_is_running){
        usleep(50);
    }
}

void spectrumProcess::clicked_status(bool is_on) {
    this->_is_running = is_on;
    if(_is_running){
        this->start();
    }
}

SpectrumScope::SpectrumScope(QCustomPlot *customPlot) {
    this->_fft_scope = customPlot;
}

void SpectrumScope::display(QVector<double> x_axe, QVector<double> y_axe) {
    this->_fft_scope->graph(0)->setData(x_axe,y_axe);
    this->_fft_scope->xAxis->rescale();
//    this->_fft_scope->graph(0)->rescaleAxes();
    this->_fft_scope->replot(QCustomPlot::rpQueuedReplot);
}


SpectrumScope::~SpectrumScope() {

}

