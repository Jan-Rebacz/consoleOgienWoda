#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include <vector>
class Level
{
public:
    Level();
    void draw(sf::RenderWindow& window);
    void checkCollisions(Player& player);
    void loadFromFile(const std::string& filename);
    void loadTextures(std::string texture_loader_filepath);
    bool chekGoalReached(Player& player);
    private:
    sf::Sprite goalTile;
    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::RectangleShape> walls;
    std::vector<sf::Sprite> sprites;
    sf::Vector2f playerStart;
    sf::Vector2f goal;
    sf::Vector2f tileSize=sf::Vector2f(18,13.5);
    std::vector<sf::Texture> textures;
};

#endif // LEVEL_H
