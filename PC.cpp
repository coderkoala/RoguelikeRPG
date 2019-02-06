#include "PC.h"
#include <ctype>
#include <time>


	void PC::Draw( sf::RenderTarget& rt )
	{
		rt.draw( sprite );
	}
	
	
	void PC::SetDirection( const sf::Vector2f& dir )
	{
		if( dir.x > 0.0f )
		{
			curAnimation = AnimationIndex::WalkingRight;
		}
		else if( dir.x < 0.0f )
		{
			curAnimation = AnimationIndex::WalkingLeft;
		}
		else if( dir.y < 0.0f )
		{
			curAnimation = AnimationIndex::WalkingUp;
		}
		else if( dir.y > 0.0f )
		{
			curAnimation = AnimationIndex::WalkingDown;
		}
		else
		{
			if( vel.x > 0.0f )
			{
				curAnimation = AnimationIndex::StandingRight;
			}
			else if( vel.x < 0.0f )
			{
				curAnimation = AnimationIndex::StandingLeft;
			}
			else if( vel.y < 0.0f )
			{
				curAnimation = AnimationIndex::StandingUp;
			}
			else if( vel.y > 0.0f )
			{
				curAnimation = AnimationIndex::StandingDown;
			}
		}
		vel = dir * speed;
	}
	
	
	void PC::Update( float dt )
	{
		pos += vel * dt;
		collision_coordinates += vel*dt;
		collisionbounds.top = pos.y + 7;
		collisionbounds.left = pos.x + 8;
		animations[int( curAnimation )].update( dt );
		animations[int( curAnimation )].ApplyToSprite( sprite );
		sprite.setPosition( pos );
	}

	sf::FloatRect PC::nextframe(sf::Vector2f& dire, float dt)
	{
		sf::Vector2f position = pos;
		sf::Vector2f vel = dire * speed;
		position += vel*dt;
		return sf::FloatRect( position.x+8 , position.y + 7, collisionbounds.width, collisionbounds.height);
	}

	sf::Vector2f PC::nextpos(sf::Vector2f& dire, float dt)
	{
		sf::Vector2f position = pos;
		bottomright = sf::Vector2f(pos.x+8 + collisionbounds.width, pos.y + 7 + collisionbounds.height)
		;sf::Vector2f vel = dire * (speed);
		position += vel*dt;
		position.x+=8 ; position.y +=7;
		return position;
	}





