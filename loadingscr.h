#pragma once
#include "SFML/Graphics.hpp"
#include "texturecodex.h"
#include "Animation.h"
#include "gameassets.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <SFML\Audio.hpp>


class loadingscr : public Animation
{
public:
	loadingscr(sf::RenderWindow&);
	void screen();

private:
	std::shared_ptr<sf::Texture> gTex;
	sf::RenderWindow&win;
};

