#include "SceneNode.hpp"

#include <algorithm>
#include <cassert>

namespace game
{
SceneNode::SceneNode()
    : mNodes()
    , pRoot(nullptr)
{}

void SceneNode::attachChild(std::unique_ptr<SceneNode> node)
{
    node->pRoot = this;
    mNodes.push_back(std::move(node));
}

std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode &node)
{
    auto nodeToRemove = [&](std::unique_ptr<SceneNode>& p) {
        return p.get() == &node;
    };
    auto found = std::find_if(mNodes.begin(), mNodes.end(), nodeToRemove);

    assert(found != mNodes.end());

    auto result = std::move(*found);
    result->pRoot = nullptr;
    mNodes.erase(found);
    return result;
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

sf::Vector2f SceneNode::getWorldPosition()
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform()
{
    auto transform = sf::Transform::Identity;

    for (const SceneNode *node = this; node != nullptr; node = node->pRoot) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

void SceneNode::updateCurrent(sf::Time dt)
{}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{}

void SceneNode::updateChildren(sf::Time dt)
{
    for (auto& node : mNodes) {
        node->update(dt);
    }
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawChildren(sf::RenderTarget & target,
    sf::RenderStates states) const
{
    for (auto& node : mNodes) {
        node->draw(target, states);
    }
}

} // namespace game
