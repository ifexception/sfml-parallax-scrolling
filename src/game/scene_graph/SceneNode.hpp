#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <memory>
#include <vector>

namespace game
{
class SceneNode
    : public sf::Transformable
    , public sf::Drawable
{
public:
    SceneNode();
    ~SceneNode() = default;

    void attachChild(std::unique_ptr<SceneNode> node);
    std::unique_ptr<SceneNode> detachChild(const SceneNode& node);

    void update(sf::Time dt);

    sf::Vector2f getWorldPosition();
    sf::Transform getWorldTransform();

protected:
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget& target,
        sf::RenderStates states) const;

private:
    void updateChildren(sf::Time dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<std::unique_ptr<SceneNode>> mNodes;
    SceneNode* pRoot;
};
} // namespace game
