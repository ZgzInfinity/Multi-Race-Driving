
#ifndef SFMLLOGOANIMATION_H
#define SFMLLOGOANIMATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

class SfmlLogoAnimation
{
public:
	sf::Texture texture;
	sf::Sprite logo, theS, theF, theM, theL;
	sf::SoundBuffer soundBuffer;
	std::vector<sf::Keyboard::Key> exitKeys;
	std::vector<sf::Keyboard::Key> skipKeys;

	float volume; // multiplier (range 0 - 1)
	float shakeStrength;
	float letterScale;
	sf::Time shakeLength;
	sf::Time fadeStart;
	sf::Time length;

	SfmlLogoAnimation(sf::RenderWindow& window);
	bool play();
	bool isSoundFinished() const;
	void stopSound();



private:
	const sf::Vector2f widescreenSize;
	const sf::View startingView;
	const sf::Time shakeStart;
	sf::RenderWindow& window;
	sf::Clock clock;
	sf::Sound sound;
	sf::Time currentTime;
	sf::View view;
	struct KeyFrame
	{
		sf::Time time;
		sf::Vector2f position;
		float scale{ 1.f };
	};
	struct Animation
	{
		KeyFrame start;
		KeyFrame end;
	};
	Animation animationLogo;
	Animation animationTheS;
	Animation animationTheF;
	Animation animationTheM;
	Animation animationTheL;

	void priv_prepareSound();
	void priv_prepareSprites();
	void priv_prepareAnimations();
	void priv_updateObject(sf::Sprite& sprite, const Animation& animation);
	void priv_updateFade();
	void priv_updateShake(const sf::View& startingView);
};

#endif // SFMLLOGOANIMATION_HPP
