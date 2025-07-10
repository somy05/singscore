#include "audioInput.h"
#include <cmath>
#include <algorithm>

audioInput::audioInput() : stream(nullptr), fftIn(nullptr), fftOut(nullptr), fftPlan(nullptr) {
    // Initialize FFT
    fftIn = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
    fftOut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
    fftPlan = fftw_plan_dft_1d(FFT_SIZE, fftIn, fftOut, FFTW_FORWARD, FFTW_ESTIMATE);
    
    audioData.isRecording = false;
    audioData.bufferReady = false;
}

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
    
    // Clean up FFT
    if (fftPlan) fftw_destroy_plan(fftPlan);
    if (fftIn) fftw_free(fftIn);
    if (fftOut) fftw_free(fftOut);
    fftw_cleanup();
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
}

int audioInput::audioCallback(const void *input, void *output,
                              unsigned long frameCount,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData) {
    const float *in = static_cast<const float*>(input);
    AudioData *audioData = static_cast<AudioData*>(userData);
    
    if (audioData->isRecording && in) {
        for (unsigned long i = 0; i < frameCount; i++) {
            audioData->recordedSamples.push_back(in[i]);
            audioData->currentBuffer.push_back(in[i]);
        }
        
        // If we have enough samples for FFT analysis
        if (audioData->currentBuffer.size() >= FFT_SIZE) {
            audioData->bufferReady = true;
        }
    }
    return paContinue;
}

double audioInput::getCurrentPitch() {
    if (!audioData.bufferReady || audioData.currentBuffer.size() < FFT_SIZE) {
        return 0.0;
    }
    
    return calculateFundamentalFrequency(audioData.currentBuffer);
}

bool audioInput::hasNewPitchData() {
    return audioData.bufferReady;
}

std::vector<float> audioInput::getRecordedSamples() {
    return audioData.recordedSamples;
}

double audioInput::calculateFundamentalFrequency(const std::vector<float>& samples) {
    if (samples.size() < FFT_SIZE) {
        return 0.0;
    }
    
    // Copy samples to FFT input buffer
    for (int i = 0; i < FFT_SIZE; i++) {
        fftIn[i][0] = samples[i]; // Real part
        fftIn[i][1] = 0.0;        // Imaginary part
    }
    
    // Execute FFT
    fftw_execute(fftPlan);
    
    // Find the peak frequency
    double maxMagnitude = 0.0;
    int peakBin = 0;
    
    // Only check frequencies up to half the sample rate (Nyquist frequency)
    for (int i = 1; i < FFT_SIZE / 2; i++) {
        double magnitude = sqrt(fftOut[i][0] * fftOut[i][0] + fftOut[i][1] * fftOut[i][1]);
        if (magnitude > maxMagnitude) {
            maxMagnitude = magnitude;
            peakBin = i;
        }
    }
    
    // Convert bin to frequency
    double frequency = (double)peakBin * SAMPLE_RATE / FFT_SIZE;
    
    // Clear the current buffer for next analysis
    audioData.currentBuffer.clear();
    audioData.bufferReady = false;
    
    return frequency;
}

double audioInput::findPeakFrequency(const std::vector<float>& samples) {
    // Alternative method using autocorrelation for pitch detection
    // This is a simpler approach that can be more accurate for fundamental frequency
    
    if (samples.size() < 2 * FRAMES_PER_BUFFER) {
        return 0.0;
    }
    
    std::vector<double> autocorr(samples.size() / 2);
    
    // Calculate autocorrelation
    for (size_t lag = 0; lag < autocorr.size(); lag++) {
        double sum = 0.0;
        for (size_t i = 0; i < samples.size() - lag; i++) {
            sum += samples[i] * samples[i + lag];
        }
        autocorr[lag] = sum;
    }
    
    // Find the peak (excluding lag 0)
    double maxCorr = 0.0;
    size_t maxLag = 0;
    for (size_t lag = 20; lag < autocorr.size(); lag++) { // Start from lag 20 to avoid spurious peaks
        if (autocorr[lag] > maxCorr) {
            maxCorr = autocorr[lag];
            maxLag = lag;
        }
    }
    
    if (maxLag > 0) {
        return (double)SAMPLE_RATE / maxLag;
    }
    
    return 0.0;
}