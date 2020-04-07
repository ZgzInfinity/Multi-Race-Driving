#include "../include/SfmlLogoAnimation.h"

namespace
{

template <class T>
inline T linearInterpolation(const T& start, const T& end, const float alpha)
{
	return static_cast<T>(start * (1.f - alpha) + end * alpha);
}

}

SfmlLogoAnimation::SfmlLogoAnimation(sf::RenderWindow& theWindow)
	: window(theWindow)
	, sound(soundBuffer)
	, widescreenSize(960.f, 540.f)
	, startingView({ 0.f, 0.f }, { widescreenSize.y * (theWindow.getView().getSize().x / theWindow.getView().getSize().y), widescreenSize.y })
	, shakeStart(sf::seconds(1.944f))
	, volume(1.f)
	, shakeStrength(50.f)
	, letterScale(0.7f)
	, shakeLength(sf::seconds(0.6f))
	, fadeStart(sf::seconds(11.f))
	, length(sf::seconds(13.f))
{
	logo.setTexture(texture);
}

bool SfmlLogoAnimation::play()
{
	srand(static_cast<unsigned int>(time(NULL)));
	priv_prepareSound();
	priv_prepareSprites();
	priv_prepareAnimations();
	sound.play();
	clock.restart();
	const sf::Time syncOffset{ sound.getPlayingOffset() - clock.getElapsedTime() };
	bool inAnim{ true };
	while (inAnim)
	{
		currentTime = clock.getElapsedTime() + syncOffset;
		if (currentTime > length)
			inAnim = false;

		priv_updateObject(logo, animationLogo);
		priv_updateFade();
		priv_updateShake(startingView);

		window.setView(view);
		window.clear();
		window.draw(logo);
		window.display();
	}
	return true;
}

bool SfmlLogoAnimation::isSoundFinished() const
{
	return (sound.getStatus() == sf::Sound::Status::Stopped);
}

void SfmlLogoAnimation::stopSound()
{
	sound.stop();
}

void SfmlLogoAnimation::priv_prepareSound()
{
	sound.setVolume(volume * 100.f);
}

void SfmlLogoAnimation::priv_prepareSprites()
{
	logo.setOrigin(logo.getTextureRect().width / 2.f, logo.getTextureRect().height / 2.f);
}



void SfmlLogoAnimation::priv_prepareAnimations()
{
	const sf::Vector2f size{ widescreenSize };
	const float letterTextureScale{ letterScale };

	animationLogo.start.time = sf::seconds(1.7f);
	animationLogo.end.time = sf::seconds(1.944f);
	animationLogo.start.position = { size.x * 0.3f, -size.y * 0.4f };
	animationLogo.end.position = { -10.f, 25 };
	animationLogo.start.scale = 0.f;
	animationLogo.end.scale = 1.f;
}



void SfmlLogoAnimation::priv_updateObject(sf::Sprite& sprite, const Animation& animation)
{
	if (currentTime <= animation.start.time)
	{
		sprite.setPosition(animation.start.position);
		sprite.setScale({ animation.start.scale, animation.start.scale });
	}
	else if (currentTime >= animation.end.time)
	{
		sprite.setPosition(animation.end.position);
		sprite.setScale({ animation.end.scale, animation.end.scale });
	}
	else
	{
		const float ratio{ (currentTime - animation.start.time) / (animation.end.time - animation.start.time) };
		sprite.setPosition(linearInterpolation(animation.start.position, animation.end.position, ratio));
		const float scale{ linearInterpolation(animation.start.scale, animation.end.scale, ratio) };
		sprite.setScale({ scale, scale });
	}
}

void SfmlLogoAnimation::priv_updateFade()
{
	if (currentTime > fadeStart)
	{
		const float ratio{ (currentTime - fadeStart) / (length - fadeStart) };
		const sf::Color color(255, 255, 255, static_cast<sf::Uint8>(255.f * (1.f - ratio)));
		logo.setColor(color);
	}
}

void SfmlLogoAnimation::priv_updateShake(const sf::View& startingView)
{
	view = startingView;
	if ((currentTime >= shakeStart) && (currentTime <= (shakeStart + shakeLength)))
	{
		const float ratio{ (currentTime - shakeStart) / shakeLength };
		const float strength{ shakeStrength * (1.f - ratio) };
		view.move({ (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength, (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength });
	}
}
