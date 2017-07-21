#pragma once

#include "SFML/Graphics.hpp"
#include "Animation.h"


class PC
{
public:

	sf::Vector2f bottomright;
    /////////////////////////////////////////////////////////////////////
    /// Grand jumble. Constructor, needs a vector position to initate
	/// Will implement the collision bounds later. -UPDATED- DONE!
	/// Collision is initiatialized before object instatiation. 
    /////////////////////////////////////////////////////////////////////
	PC( const sf::Vector2f& pos , std::string heroX ) :	pos(pos) , vel(0.0f,0.0f) , speed(64.0f), curAnimation(AnimationIndex::StandingDown)
		, collision_coordinates(pos.x + 16, pos.y +20)
	{
    

		collisionbounds.top = pos.y + 7;
		collisionbounds.left = pos.x + 8;
		collisionbounds.height = 24;
		collisionbounds.width = 16;
		
	/////////////////////////////////////////////////////////////////////
    ///By default, the facing direction is down.
    /////////////////////////////////////////////////////////////////////
		animations[(int)AnimationIndex::WalkingUp] = Animation(32,0,32,32,.001f,7,heroX);
		animations[(int)AnimationIndex::WalkingLeft] = Animation(32,32,32,32,0.001f,7,heroX);
		animations[(int)AnimationIndex::WalkingDown] = Animation(32,64,32,32,0.001f,7,heroX);
		animations[(int)AnimationIndex::WalkingRight] = Animation(32,96,32,32,0.001f,7,heroX);
		animations[(int)AnimationIndex::StandingUp] = Animation(0,0,32,32,0.0f,1,heroX);
		animations[(int)AnimationIndex::StandingLeft] = Animation(0,32,32,32,0.0f,1,heroX);
		animations[(int)AnimationIndex::StandingDown] = Animation(0,64,32,32,0.0f,1,heroX);
		animations[(int)AnimationIndex::StandingRight] = Animation(0,96,32,32,0.0f,1,heroX);
	}


    /////////////////////////////////////////////////////////////////////
    ///	Sets the facing direction, and plays the suitable animation
    /////////////////////////////////////////////////////////////////////
	void SetDirection( const sf::Vector2f& dir );
	
	/////////////////////////////////////////////////////////////////////
    /// Pass the Reference of window to this function, and it's drawn
    /////////////////////////////////////////////////////////////////////
	void Draw( sf::RenderTarget& rt );
	
    /////////////////////////////////////////////////////////////////////
    ///	Updates the model after time dt has been fed. Has to be in float
    /////////////////////////////////////////////////////////////////////
	void Update( float dt );

	//////////////////////////////////////////////////////////////////////////////////////////////
	////			Real character coordinates, at the middle of the sprite
	//////////////////////////////////////////////////////////////////////////////////////////////
	sf::Vector2f collision_coordinates;
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	///	The actual rectangle where the character sprite is bounded
	/////////////////////////////////////////////////////////////////////////////////////////////
	sf::FloatRect collisionbounds;

	/////////////////////////////////////////////////////
	/// Returns the rectangle where the character would
	/// have been had he were walking
	///	Second argument: Time dt from the main function
	/////////////////////////////////////////////////////
	sf::FloatRect nextframe(sf::Vector2f&, float );

	////////////////////////////////////////////////////
	/// Returns the position where the character would
	/// have been had he were walking: supply coordinates
	///	Second argument: Time dt from the main function
	/// true for left, false for right side collision
	////////////////////////////////////////////////////
	sf::Vector2f PC::nextpos(sf::Vector2f& dire, float dt);

	
	///////////////////////////////////////////////////
	///	Bounce the character model backwards by a small
	/// Offset for the purpose of 
	///////////////////////////////////////////////////
	void PC::bounce(int x, int y);

	//////////////////////////////////////////////////
	/// Returns the  private member of the class pos
	/// to
	/// outside procedures
	/////////////////////////////////////////////////
	inline sf::Vector2f PC::returnpos()
	{
		return sf::Vector2f(pos.x+8, pos.y+7);
	}

	////////////////////////////////////////////////
	///Returns the offset for the tilemap's collision
	///Variable retrival
	///1st and 2nd values are x and y coordinates
	///3rd and 4rth values are offset for x and y
	///(for collision)
	////////////////////////////////////////////////
	inline sf::Vector2i returntile(int valuex,int valuey,int offsetx, int offsety)
	{
		return sf::Vector2i((int)valuex/32 + offsetx , (int)valuey/32 + offsety);
	}

private:
	
	///////////////////////////////////////////////////////////////////////
    /// Enumerator, makes sure the number of animations are correctly taken
    /// Taken care of. Notice that count actually counts the number of the
	/// variables in the actual indices.
	///////////////////////////////////////////////////////////////////////


	enum class AnimationIndex
	{
		WalkingUp,
		WalkingDown,
		WalkingLeft,
		WalkingRight,
		StandingUp,
		StandingDown,
		StandingLeft,
		StandingRight,
		Count
	};

	const float speed;
	sf::Vector2f vel,pos; 
	sf::Sprite sprite;
	Animation animations[int( AnimationIndex::Count )];
	AnimationIndex curAnimation;
};