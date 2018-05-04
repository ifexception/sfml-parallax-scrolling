#include "SpriteNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace game
{
SpriteNode::SpriteNode(const sf::Texture &texture)
	: mSprite(texture) {}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect intRect)
	: mSprite(texture, intRect) {}

void SpriteNode::updateCurrent(sf::Time dt)
{}

void SpriteNode::drawCurrent(sf::RenderTarget &target,
	sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
} // namespace game
