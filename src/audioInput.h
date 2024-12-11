#ifndef GAME_AUDIO_INPUT_H
#define GAME_AUDIO_INPUT_H

#include "portaudio.h"
#include <vector>
#include <iostream>
#include "states/gameState.h"
struct AudioData {
    std::vector<float> recordedSamples;
    bool isRecording;
};
class audioInput {  
private:
    static constexpr int SAMPLE_RATE = 44100;
    static constexpr int FRAMES_PER_BUFFER = 256;
    static constexpr int NUM_CHANNELS = 1;

    PaStream *stream;
    PaError err;
    AudioData audioData;
   
   

    static int audioCallback(const void *input, void *output,
                             unsigned long frameCount,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData);

public:
    void startRecording();
    void stopRecording();
    bool initPortAudio();
    ~audioInput();
};

#endif //GAME_AUDIO_INPUT_H