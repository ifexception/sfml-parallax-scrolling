#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "World.hpp"

namespace game
{
class Game
{
  public:
    Game();
    void run();

  private:
    void processEvents();
    void update(sf::Time elaspedTime);
    void render();

    void updateStatistics(sf::Time elaspedTime);

    static const sf::Time TIME_PER_FRAME;
    sf::RenderWindow mWindow;
    World mWorld;

    sf::Font mFont;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
};
} // namespace game
