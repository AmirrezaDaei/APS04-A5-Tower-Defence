#include "constants.hpp"

int generateRandom(int from, int to) {
    random_device rd;
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(from, to);
    return dist(gen);
}

void loadSound(Sound& sound, string filename) {
    static vector<SoundBuffer> buffers;
    SoundBuffer buffer;
    if (!buffer.loadFromFile(filename))
        cerr << "Failed to load sound" << endl;
    buffers.push_back(buffer);
    sound.setBuffer(buffers.back());
}

void createText(Text& text ,Font& font, int size, Color color)
{
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
}
