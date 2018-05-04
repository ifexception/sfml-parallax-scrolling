#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace game
{
World::World(sf::RenderWindow & window)
    : rWindow(window)
    , mWorldView()
    , mTextures()
    , mSceneGraph()
    , mSceneLayers()
    , mWorldBounds(0.0f, 0.0f, 2000.0f, mWorldView.getSize().y)
    , mSpawnPosition(mWorldView.getSize().x / 2.0f,
        mWorldBounds.height - mWorldView.getSize().y / 2.0f)
    , mScrollSpeed(50.0f)
    , mBackgrounds()
{
    loadTextures();
    //buildScene();

    std::pair<float, sf::Sprite*> temp;

    temp.first = 0.2f;
    temp.second = new sf::Sprite(mTextures.get(Textures::MainBackground));
    mBackgrounds.push_back(temp);

    temp.first = 0.5f;
    temp.second = new sf::Sprite(mTextures.get(Textures::BigMountainBackground));
    mBackgrounds.push_back(temp);

    /*temp.first = 0.8f;
    temp.second = new sf::Sprite(mTextures.get(Textures::SmallMountainBackground));
    mBackgrounds.push_back(temp);*/

    temp.first = 0.8f;
    temp.second = new sf::Sprite(mTextures.get(Textures::TreesBackground));
    mBackgrounds.push_back(temp);

    temp.first = 1.0f;
    temp.second = new sf::Sprite(mTextures.get(Textures::TreesForeground));
    mBackgrounds.push_back(temp);

    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    mWorldView.move(mScrollSpeed * dt.asSeconds(), 0.0f);
    mSceneGraph.update(dt);
}

void World::draw()
{
    for (auto iter = mBackgrounds.begin(); iter != mBackgrounds.end(); iter++) {
        auto currentTarget = mWorldView.getCenter();
        auto parallaxCoefficient = iter->first;
        auto background = iter->second;
        sf::View v;
        v.setCenter(parallaxCoefficient * currentTarget);
        rWindow.setView(v);
        rWindow.draw(*background);
    }

    rWindow.setView(mWorldView);
    rWindow.draw(mSceneGraph);

    // loop for foreground screens
}

void World::loadTextures()
{
    mTextures.load(Textures::MainBackground, "assets/parallax-mountain-bg.png");
    mTextures.load(Textures::BigMountainBackground, "assets/parallax-mountain-montain-far.png");
    //mTextures.load(Textures::SmallMountainBackground, "assets/parallax-mountain-montains.png");
    mTextures.load(Textures::TreesBackground, "assets/parallax-mountain-trees.png");
    mTextures.load(Textures::TreesForeground, "assets/parallax-mountain-foreground-trees.png");
}

//void World::buildScene()
//{
//    for (std::size_t i = 0; i < LayerCount; ++i) {
//        auto layer = std::make_unique<SceneNode>();
//        mSceneLayers[i] = layer.get();
//        mSceneGraph.attachChild(std::move(layer));
//    }
//
//    auto& texture = mTextures.get(Textures::Background);
//    sf::IntRect textureRect(mWorldBounds);
//    texture.setRepeated(true);
//
//    auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
//    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
//    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
//}
}
