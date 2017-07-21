#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "SFML\Graphics.hpp"

class Texturecodex
{
public:
	Texturecodex(void);
	~Texturecodex(void);
	static std::shared_ptr<sf::Texture> Acquire( const std::string& name );
	static void Texturecodex::MurderOrphans();


private:
	static std::unordered_map<std::string,std::shared_ptr<sf::Texture>> texturePtrs;
};

