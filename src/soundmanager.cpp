#include "soundmanager.hpp"

SoundManager::SoundManager() { sound_pool.resize(MAX_SOUNDS); }

void SoundManager::loadSound(const string& filename) {
    if (buffers.find(filename) == buffers.end()) {
        auto buffer = make_shared<SoundBuffer>();
        if (!buffer->loadFromFile(filename)) cerr << "Failed to load sound: " << filename << endl;
        buffers[filename] = buffer;
    }
}

void SoundManager::playSound(const string& filename, float volume) {
    if (buffers.find(filename) == buffers.end()) {
        loadSound(filename);
    }

    for (auto& sound : sound_pool) {
        if (sound.getStatus() == Sound::Stopped) {
            sound.setBuffer(*buffers[filename]);
            sound.setVolume(volume);
            sound.play();
            return;
        }
    }

    Sound* quietest_sound = nullptr;
    float quietest_volume = -1.f;
    for (auto& sound : sound_pool) {
        if (sound.getVolume() < quietest_volume || quietest_volume < 0.f) {
            quietest_volume = sound.getVolume();
            quietest_sound = &sound;
        }
    }

    if (quietest_sound) {
        quietest_sound->setBuffer(*buffers[filename]);
        quietest_sound->setVolume(volume);
        quietest_sound->play();
    }
}