// 2048 with SFML visualization (integrated logic)
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

const int ROW = 4;
const int COL = 4;
const int TILE_SIZE = 100;
const int PADDING = 10;
const int WINDOW_SIZE = TILE_SIZE * COL + PADDING * 5;

int table[ROW][COL];
int score = 0;

sf::Color getTileColor(int value) {
    switch (value) {
        case 0: return sf::Color(200, 200, 200);
        case 2: return sf::Color(240, 228, 217);
        case 4: return sf::Color(236, 224, 200);
        case 8: return sf::Color(242, 177, 121);
        case 16: return sf::Color(245, 149, 99);
        case 32: return sf::Color(246, 124, 95);
        case 64: return sf::Color(246, 94, 59);
        case 128: return sf::Color(237, 207, 114);
        case 256: return sf::Color(237, 204, 97);
        case 512: return sf::Color(237, 200, 80);
        case 1024: return sf::Color(237, 197, 63);
        case 2048: return sf::Color(237, 194, 46);
        default: return sf::Color::Black;
    }
}

void tableCopy(int src[ROW][COL], int dest[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int emptyFields() {
    int count = 0;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (table[i][j] == 0) count++;
        }
    }
    return count;
}

void addRandom() {
    int empty = emptyFields();
    if (empty == 0) return;
    int r = rand() % empty;
    int val = (rand() % 2 + 1) * 2;
    int count = 0;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (table[i][j] == 0) {
                if (count == r) {
                    table[i][j] = val;
                    return;
                }
                count++;
            }
        }
    }
}

int moveLeft() {
    int moved = 0;
    for (int i = 0; i < ROW; i++) {
        int temp[COL] = {0};
        int index = 0;
        for (int j = 0; j < COL; j++) {
            if (table[i][j] != 0) {
                if (temp[index] == 0) {
                    temp[index] = table[i][j];
                } else if (temp[index] == table[i][j]) {
                    temp[index++] *= 2;
                    score += temp[index - 1];
                } else {
                    temp[++index] = table[i][j];
                }
            }
        }
        for (int j = 0; j < COL; j++) {
            if (table[i][j] != temp[j]) moved = 1;
            table[i][j] = temp[j];
        }
    }
    return moved;
}

int moveRight() {
    int moved = 0;
    for (int i = 0; i < ROW; i++) {
        int temp[COL] = {0};
        int index = COL - 1;
        for (int j = COL - 1; j >= 0; j--) {
            if (table[i][j] != 0) {
                if (temp[index] == 0) {
                    temp[index] = table[i][j];
                } else if (temp[index] == table[i][j]) {
                    temp[index--] *= 2;
                    score += temp[index + 1];
                } else {
                    temp[--index] = table[i][j];
                }
            }
        }
        for (int j = 0; j < COL; j++) {
            if (table[i][j] != temp[j]) moved = 1;
            table[i][j] = temp[j];
        }
    }
    return moved;
}

int moveUp() {
    int moved = 0;
    for (int j = 0; j < COL; j++) {
        int temp[ROW] = {0};
        int index = 0;
        for (int i = 0; i < ROW; i++) {
            if (table[i][j] != 0) {
                if (temp[index] == 0) {
                    temp[index] = table[i][j];
                } else if (temp[index] == table[i][j]) {
                    temp[index++] *= 2;
                    score += temp[index - 1];
                } else {
                    temp[++index] = table[i][j];
                }
            }
        }
        for (int i = 0; i < ROW; i++) {
            if (table[i][j] != temp[i]) moved = 1;
            table[i][j] = temp[i];
        }
    }
    return moved;
}

int moveDown() {
    int moved = 0;
    for (int j = 0; j < COL; j++) {
        int temp[ROW] = {0};
        int index = ROW - 1;
        for (int i = ROW - 1; i >= 0; i--) {
            if (table[i][j] != 0) {
                if (temp[index] == 0) {
                    temp[index] = table[i][j];
                } else if (temp[index] == table[i][j]) {
                    temp[index--] *= 2;
                    score += temp[index + 1];
                } else {
                    temp[--index] = table[i][j];
                }
            }
        }
        for (int i = 0; i < ROW; i++) {
            if (table[i][j] != temp[i]) moved = 1;
            table[i][j] = temp[i];
        }
    }
    return moved;
}

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE + 50), "2048 Game");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Font load failed!\n";
        return 1;
    }

    addRandom();
    addRandom();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                int moved = 0;
                if (event.key.code == sf::Keyboard::W) moved = moveUp();
                if (event.key.code == sf::Keyboard::S) moved = moveDown();
                if (event.key.code == sf::Keyboard::A) moved = moveLeft();
                if (event.key.code == sf::Keyboard::D) moved = moveRight();
                if (moved) addRandom();
            }
        }

        window.clear(sf::Color(250, 248, 239));

        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setFillColor(getTileColor(table[i][j]));
                tile.setPosition(PADDING + j * (TILE_SIZE + PADDING), PADDING + i * (TILE_SIZE + PADDING));
                window.draw(tile);

                if (table[i][j] != 0) {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(std::to_string(table[i][j]));
                    text.setCharacterSize(32);
                    text.setFillColor(sf::Color::Black);
                    sf::FloatRect rect = text.getLocalBounds();
                    text.setOrigin(rect.width / 2, rect.height / 2);
                    text.setPosition(tile.getPosition().x + TILE_SIZE / 2, tile.getPosition().y + TILE_SIZE / 2 - 10);
                    window.draw(text);
                }
            }
        }

        sf::Text scoreText("Score: " + std::to_string(score), font, 24);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(PADDING, WINDOW_SIZE);
        window.draw(scoreText);

        window.display();
    }

    return 0;
}
