#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "resources/ResourceIdentifiers.hpp"
#include "resources/ResourceManager.hpp"
#include "scene_graph/SceneNode.hpp"
#include "scene_graph/SpriteNode.hpp"

#include <array>

namespace sf
{
class RenderWindow;
}

namespace game
{
class World
{
public:
    World() = delete;
    explicit World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();

private:
    void loadTextures();
    void buildScene();

    enum Layer
    {
        Background = 0,
        Air = 1,
        LayerCount
    };

    sf::RenderWindow& rWindow;
    sf::View mWorldView;
    rma::ResourceManager<sf::Texture, Textures> mTextures;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;

    std::vector<std::pair<float, sf::Sprite*>> mBackgrounds;
};
} // namespace game
