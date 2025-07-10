#ifndef GAME_AUDIO_INPUT_H
#define GAME_AUDIO_INPUT_H

#include "portaudio.h"
#include <vector>
#include <iostream>
#include <complex>
#include <fftw3.h>
#include "states/gameState.h"

struct AudioData {
    std::vector<float> recordedSamples;
    bool isRecording;
    std::vector<float> currentBuffer;
    bool bufferReady;
};

class audioInput {  
private:
    static constexpr int SAMPLE_RATE = 44100;
    static constexpr int FRAMES_PER_BUFFER = 256;
    static constexpr int NUM_CHANNELS = 1;
    static constexpr int FFT_SIZE = 1024;

    PaStream *stream;
    PaError err;
    AudioData audioData;
    
    // FFT related
    fftw_complex *fftIn;
    fftw_complex *fftOut;
    fftw_plan fftPlan;

    static int audioCallback(const void *input, void *output,
                             unsigned long frameCount,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData);

    double calculateFundamentalFrequency(const std::vector<float>& samples);
    double findPeakFrequency(const std::vector<float>& samples);

public:
    audioInput();
    ~audioInput();
    
    void startRecording();
    void stopRecording();
    bool initPortAudio();
    double getCurrentPitch(); // Returns the fundamental frequency in Hz
    bool hasNewPitchData();
    std::vector<float> getRecordedSamples();
};

#endif //GAME_AUDIO_INPUT_H