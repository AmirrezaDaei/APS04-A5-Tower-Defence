#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class PathFollower {
public:
    PathFollower(sf::Sprite& targetEntity, const std::vector<sf::Vector2f>& path, float speed)
        : entity(targetEntity), path(path), speed(speed), currentIndex(0) {}

    void update(float deltaTime) {
        if (currentIndex >= path.size())
            return; // Finished path

        sf::Vector2f position = entity.getPosition();
        sf::Vector2f target = path[currentIndex];
        sf::Vector2f direction = target - position;

        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 1.0f) {
            // Normalize and move
            direction /= distance;
            entity.move(direction * speed * deltaTime);
        } else {
            // Snap and go to next target
            entity.setPosition(target);
            currentIndex++;
        }
    }

    bool isDone() const {
        return currentIndex >= path.size();
    }

    void reset() {
        currentIndex = 0;
    }

private:
    sf::Sprite& entity;
    std::vector<sf::Vector2f> path;
    float speed;
    size_t currentIndex;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Path Follower");

    sf::Texture texture;
    texture.loadFromFile("assets/sprites/normal.png");

    sf::Sprite player(texture);
    player.setPosition(64, 64);

    std::vector<sf::Vector2f> path = {
        {64, 64},
        {128, 64},
        {192, 64},
        {192, 128},
        {192, 256},
        {192, 320},
        {256, 320},
        {320, 320}
    };

    PathFollower follower(player, path, 100.0f);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        follower.update(dt);

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}
