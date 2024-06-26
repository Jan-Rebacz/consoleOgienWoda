#include "level.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

Level::Level() {
    this->loadTextures("/home/michal/QT_Apps/consoleOgienWoda/assets/textures.txt");
}

void Level::draw(sf::RenderWindow& window) {
    for (const auto& platform : platforms) {
        window.draw(platform);
    }
    for (const auto& sprite : sprites) {
        window.draw(sprite);
        // std::cout << "Sprite texture address: " << sprite.getTexture() << std::endl;
        // std::cerr << "Sprite drawn at position (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
    }
    // std::cerr << "Level drawn" << std::endl;
}

void Level::checkCollisions(Player& player) {
    sf::FloatRect playerBounds = player.getBounds();

    // Check collisions with platforms
    for (const auto& platform : platforms) {
        if (platform.getGlobalBounds().intersects(playerBounds)) {
            player.handleCollision(platform);
        }
    }

    // Check collisions with walls
    for (const auto& wall : walls) {
        if (wall.getGlobalBounds().intersects(playerBounds)) {
            player.handleCollision(wall);
        }
    }

    // Check side collisions with walls
    for (const auto& wall : walls) {
        sf::FloatRect wallBounds = wall.getGlobalBounds();
        if (wallBounds.intersects(playerBounds)) {
            player.handleCollision(wallBounds);
        }
    }

    // Check collisions with sprites
    for (const auto& sprite : sprites) {
        if (sprite.getGlobalBounds().intersects(playerBounds)) {
            player.handleCollision(sprite);
        }
    }

    // Check side collisions with sprites
    for (const auto& sprite : sprites) {
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();

       if(spriteBounds==goalTile.getGlobalBounds()){
         continue;
         }
        if (spriteBounds.intersects(playerBounds)) {
            player.handleCollision(spriteBounds);
        }
    }
}

void Level::loadTextures(std::string texture_loader_filepath) {
    std::string line;
    std::ifstream file(texture_loader_filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open texture file");
    }
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string texturePath;
        iss >> texturePath;
        sf::Texture newTexture;
        if (!newTexture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture from " + texturePath);
        }

        // std::cerr << "Loaded texture: " << texturePath << std::endl;
        textures.emplace_back(newTexture);
    }
}

void Level::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open level file");
    }

    int mapWidth, mapHeight;
    int tileSizeX, tileSizeY;
    file >> mapWidth >> mapHeight >> tileSizeX >> tileSizeY;
    // std::cerr << "Map width: " << mapWidth << " Map height: " << mapHeight << " Tile size x: " << tileSizeX << " Tile size y: " << tileSizeY << std::endl;
    std::cout << "Map width: " << mapWidth << " Map height: " << mapHeight << " Tile size x: " << tileSizeX << " Tile size y: " << tileSizeY << std::endl;

    std::map<std::pair<int, int>, char> tileMap;

    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < line.size(); ++x) {
            char tileType = line[x];
            tileMap[{x, y}] = tileType;

            switch (tileType) {
            case '#': {
                sf::Sprite wall;
                wall.setTexture(textures[0]);
                wall.setScale(tileSizeX / static_cast<float>(textures[0].getSize().x),
                              tileSizeY / static_cast<float>(textures[0].getSize().y));
                wall.setPosition(x * tileSizeX, y * tileSizeY);
                sprites.push_back(wall);
                // std::cerr << "Wall added at (" << x * tileSizeX << ", " << y * tileSizeY << ")" << std::endl;
                break;
            }
            case '@': {
                sf::RectangleShape coin(sf::Vector2f(tileSizeX, tileSizeY));
                coin.setFillColor(sf::Color::Yellow);
                coin.setPosition(x * tileSizeX, y * tileSizeY);
                walls.emplace_back(coin);
                // std::cerr << "Coin added at (" << x * tileSizeX << ", " << y * tileSizeY << ")" << std::endl;
                break;
            }
            case '$': {
                sf::Sprite grass;
                grass.setTexture(textures[1]);
                grass.setScale(tileSizeX / static_cast<float>(textures[1].getSize().x),
                               tileSizeY / static_cast<float>(textures[1].getSize().y));
                grass.setPosition(x * tileSizeX, y * tileSizeY);
                sprites.push_back(grass);
                // std::cerr << "Grass added at (" << x * tileSizeX << ", " << y * tileSizeY << ")" << std::endl;
                break;
            }
            case 'o':
            {
             sf::Sprite goal;
                goal.setTexture(textures[2]);
                goal.setScale(tileSizeX / static_cast<float>(textures[2].getSize().x),
                               tileSizeY / static_cast<float>(textures[2].getSize().y));
                goal.setPosition(x * tileSizeX, y * tileSizeY);
                sprites.push_back(goal);
                goalTile = goal;
                // std::cerr << "Goal added at (" << x * tileSizeX << ", " << y * tileSizeY << ")" << std::endl;   
            }
            default:
                // Handle other tile types
                break;
            }
        }
        y++;
    }
    std::cerr << "Finished loading level" << std::endl;
    file.close();
}
 bool Level::chekGoalReached(Player& player){
     sf::FloatRect playerBounds = player.getBounds();
     if(playerBounds.intersects(goalTile.getGlobalBounds())){
         std::cout<<"Goal reached"<<std::endl;
         return true;
     }
     return false;
 }