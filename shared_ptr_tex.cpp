#include "texturecodex.h"

std::shared_ptr<sf::Texture> Texturecodex::Acquire( const std::string& name )
{
		const auto i = texturePtrs.find( name );
		if( i != texturePtrs.end() )
		{
			return i->second;
		}
		else
		{
			auto pTex = std::make_shared<sf::Texture>();
			pTex->loadFromFile( name );
			//texturePtrs.insert( { name , pTex } );
			return pTex;
		}
}
void Texturecodex::MurderOrphans()
	{
		for( auto i = texturePtrs.begin(); i != texturePtrs.end(); )
		{
			if( i->second.unique() )
			{
				i = texturePtrs.erase( i );
			}
			else
			{
				++i;
			}
		}
	}

std::unordered_map<std::string,std::shared_ptr<sf::Texture>> Texturecodex::texturePtrs;
