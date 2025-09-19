#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using namespace std;
using namespace sf;

class SoundManager {
private:
    map<string, shared_ptr<SoundBuffer>> buffers;
    vector<Sound> sound_pool;
    static const int MAX_SOUNDS = 16;

public:
    SoundManager();
    void loadSound(const string& filename);
    void playSound(const string& filename, float volume = 100.f);
};

#endif  // SOUNDMANAGER_HPP