#include "Game.hpp"

#include <SFML/Window/Event.hpp>

namespace game
{
const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "lt47", sf::Style::Close)
    , mWorld(mWindow)
    , mFont()
    , mStatisticsText()
    , mStatisticsUpdateTime()
    , mStatisticsNumFrames(0)
{
    mFont.loadFromFile("assets/PT_Sans-Narrow.ttf");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.0f, 5.0f);
    mStatisticsText.setCharacterSize(12);
}

void Game::run()
{
    sf::Clock clock;
    auto timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        auto elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME)  {
            timeSinceLastUpdate -= TIME_PER_FRAME;

            processEvents();
            update(TIME_PER_FRAME);
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::update(sf::Time elapsedTime)
{
    mWorld.update(elapsedTime);
}

void Game::render()
{
    mWindow.clear();

    mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
        auto framePerSecond = "Frames / Second = "
            + std::to_string(mStatisticsNumFrames);
        auto updateTime = mStatisticsUpdateTime.asMicroseconds()
            / mStatisticsNumFrames;
        auto updatesPerSecond = "Time / Update = "
            + std::to_string(updateTime) + "us";
        auto displayString = framePerSecond + "\n" + updatesPerSecond;
        mStatisticsText.setString(displayString);

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}
} // namespace game
