#include "audioInput.h"

bool audioInput::initPortAudio() {

    err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    
    err = Pa_OpenDefaultStream(&stream, NUM_CHANNELS, 0, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audioCallback, &audioData);

    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    
    return true;

}

audioInput::~audioInput() {
    if(stream) {
        Pa_CloseStream(stream);
    }
    Pa_Terminate();
}


void audioInput::startRecording() {
  audioData.isRecording = true;
  err = Pa_StartStream(stream);
   if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    }
    
}

void audioInput::stopRecording() {
    audioData.isRecording = false;
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    }

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    }
}
int audioInput::audioCallback(const void *input, void *output,
                              unsigned long frameCount,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData) {
    audioInput *audio = static_cast<audioInput*>(userData);
    const float *in = static_cast<const float*>(input);
    AudioData *audioData = static_cast<AudioData*>(userData);
    if (audioData->isRecording && in) {
        for (int i = 0; i < frameCount; i++) {
            audioData->recordedSamples.push_back(in[i]);
        }
    }
    return paContinue;
                              }


   













