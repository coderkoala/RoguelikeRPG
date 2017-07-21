#pragma once
#include<string>
#include<SFML\Graphics.hpp>
#include"gameassets.h"

namespace mapdomain
{
	
class map
{
public:
map();

map(std::string mapname);

struct layer
{
		std::string filename;
		int tile[25][16];
		sf::Vector2f filecoords[25][16];
	}layer[3]; 

std::string music,prevmap, nextmap;
sf::Vector2f entry;
sf::Vector2f exit;
bool rain;

};};
