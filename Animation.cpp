#include "Animation.h"


Animation::Animation(){}


Animation::Animation(int left, int top,int sizex, int sizey, float holdt, int n , std::string texname) : currentframe(0), holdtime(holdt), time(0.0f), frame(n), sizex(sizex) , sizey(sizey)

{
	pTex=Texturecodex::Acquire(texname);
	bounds.height = sizey;
	bounds.width = sizex;
	bounds.left=left;
	bounds.top=top;
		
	if(n==0){frame = ++n;}

	////////////////////////////////////////////////////
	//Storing all the coordinates positions(x and y) in
	//the corresponding x-y vector structure.
	////////////////////////////////////////////////////
	for(int i=0; i<=n-1; i++)
	{
		frames[i].left = left + sizex*i;
		frames[i].top = top;
		frames[i].height = sizey;
		frames[i].width = sizex;
	}

}


void Animation::draw(sf::RenderTarget &window, int x, int y)
{
	sf::Sprite sprite(*pTex);
	sprite.setTextureRect(frames[currentframe]);
	sprite.setPosition((float)x,(float)y);
	window.draw(sprite);
}


void Animation::resetframe()
{
		if( ++currentframe >= frame)
		{
			currentframe = 0;
		}
}

void Animation::update(float dt)
{
	if(holdtime == 0){resetframe();
	}
	else {
	time += dt;
	while( time >= holdtime )
	{
		time -= holdtime;
		resetframe();
	}}
}

void Animation::ApplyToSprite( sf::Sprite& s )
{
	s.setTexture( *pTex );
	s.setTextureRect( frames[currentframe] );
}