#include "playingState.h"
#include <sstream>
#include <iomanip>
#include <cmath>

void playingState::init(){
    audio.initPortAudio();
    
    if (!font2.loadFromFile("assets/gamefont.ttf")){
        std::cout << "Error while loading font assets " << std::endl;
        return;
    }

    // Load OGG file first, fallback to MP3 if needed
    if (!music.load("assets/music.ogg")){
        std::cout << "OGG file not found, trying MP3..." << std::endl;
        if (!music.load("assets/music.mp3")){
            std::cout << "Error while loading audio assets " << std::endl;
            return;
        }
    }
    
    text2.setCharacterSize(24);
    text2.setFillColor(sf::Color::Black);
    text2.setStyle(sf::Text::Bold);
    text2.setPosition({50, 50});
    text2.setFont(font2);
    text2.setString("Press SPACE to start singing game!\nPress ESC to return to menu.");
    
    gameStarted = false;
    userPitch = 0.0;
    targetPitch = 0.0;
    score = 0;
}

void playingState::handleInput(sf::Event *event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        if (gameStarted) {
            music.stop();
            audio.stopRecording();
        }
        Game::setState(Game::menu);
    }
    
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Space && !gameStarted) {
            startGame();
        }
    }
}

void playingState::update(float timeElapsed) { 
    if (!gameStarted) {
        return;
    }
    
    // Check if music is still playing
    if (!music.getIsPlaying() && music.getStatus() != sf::Music::Paused) {
        // Song finished
        audio.stopRecording();
        gameStarted = false;
        
        std::stringstream ss;
        ss << "Song finished! Final Score: " << score << "\n";
        ss << "Press SPACE to play again\nPress ESC to return to menu";
        text2.setString(ss.str());
        return;
    }
    
    // Get user's current pitch
    if (audio.hasNewPitchData()) {
        userPitch = audio.getCurrentPitch();
        calculateScore();
        
        // Update display
        std::stringstream ss;
        ss << "Singing Game Active!\n";
        ss << "Score: " << score << "\n";
        ss << "Your pitch: " << std::fixed << std::setprecision(1) << userPitch << " Hz";
        
        if (userPitch > 0) {
            ss << " (" << getPitchName(userPitch) << ")";
        }
        
        ss << "\nSong time: " << std::fixed << std::setprecision(1) 
           << music.getPlayingOffset() << "s / " << music.getDuration() << "s\n";
        
        if (userPitch > 0 && targetPitch > 0) {
            double accuracy = getPitchAccuracy(userPitch, targetPitch);
            ss << "Pitch accuracy: " << std::fixed << std::setprecision(1) << (accuracy * 100) << "%";
        }
        
        text2.setString(ss.str());
    }
}

void playingState::draw(sf::RenderWindow *window) { 
    window->draw(text2);
}

void playingState::startGame() {
    gameStarted = true;
    score = 0;
    
    // Start music and recording
    music.play();
    audio.startRecording();
    
    // For demonstration, set a target pitch (this could be enhanced to analyze the song)
    targetPitch = 440.0; // A4 note
    
    text2.setString("Game started! Start singing...");
}

void playingState::calculateScore() {
    if (userPitch <= 0 || targetPitch <= 0) {
        return;
    }
    
    double accuracy = getPitchAccuracy(userPitch, targetPitch);
    
    // Award points based on accuracy
    if (accuracy > 0.9) {
        score += 10; // Excellent
    } else if (accuracy > 0.8) {
        score += 7;  // Good
    } else if (accuracy > 0.7) {
        score += 5;  // Fair
    } else if (accuracy > 0.5) {
        score += 2;  // Poor
    }
    // No points for accuracy below 50%
}

double playingState::getPitchAccuracy(double userPitch, double targetPitch) {
    if (userPitch <= 0 || targetPitch <= 0) {
        return 0.0;
    }
    
    // Calculate the ratio between pitches
    double ratio = userPitch / targetPitch;
    
    // Convert to cents (1200 cents = 1 octave)
    double cents = 1200.0 * log2(ratio);
    
    // Get absolute difference in cents
    double absCents = abs(cents);
    
    // Perfect match = 100%, decreases as difference increases
    // 100 cents difference = ~50% accuracy, 200 cents = ~25%, etc.
    double accuracy = exp(-absCents / 100.0);
    
    return std::max(0.0, std::min(1.0, accuracy));
}

std::string playingState::getPitchName(double frequency) {
    if (frequency <= 0) {
        return "Silent";
    }
    
    // Array of note names
    const std::string noteNames[] = {
        "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
    };
    
    // Calculate the note number (A4 = 440 Hz is note number 69)
    double noteNumber = 12.0 * log2(frequency / 440.0) + 69.0;
    int noteIndex = (int)(noteNumber + 0.5) % 12;
    int octave = (int)(noteNumber + 0.5) / 12 - 1;
    
    if (noteIndex < 0) {
        noteIndex += 12;
        octave--;
    }
    
    return noteNames[noteIndex] + std::to_string(octave);
}