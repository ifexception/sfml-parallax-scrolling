#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "SceneNode.hpp"

namespace game
{
class SpriteNode : public SceneNode
{
public:
	SpriteNode() = delete;
	explicit SpriteNode(const sf::Texture& texture);
	explicit SpriteNode(const sf::Texture& texture, const sf::IntRect intRect);
	~SpriteNode() = default;

protected:
	void updateCurrent(sf::Time dt) override;
	void drawCurrent(sf::RenderTarget &target,
		sf::RenderStates states) const override;

private:
	sf::Sprite mSprite;
};
} // namespace game
