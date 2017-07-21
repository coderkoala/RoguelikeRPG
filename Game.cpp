#include "SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include<chrono>
#include"World.h"
#include"gameassets.h"
#include"PC.h"
#include"Animation.h"
#include"texturecodex.h"
#include"map.h"

#define collision_down 80
#define collision_up 80

float xmax = 800;
float ymax = 512;


//////////////////////////////////////////////////////////////////////////////////
////					MAIN GAME FUNCTION
//////////////////////////////////////////////////////////////////////////////////
int main(std::string map)
{
	sf::Vector2f slack;  sf::FloatRect rekt;
	bool pause = false;
	mapdomain::map mapdata("game/map/map_02");
	///////////////////////////////////////
	///		Window Render
	///////////////////////////////////////
	sf::RenderWindow window(sf::VideoMode(800,512), "This shit ruined my life lmao");

	bool rainbool=mapdata.rain;

	//////////////////////m/////////////////
	///		Load the Loading screen assets
	///////////////////////////////////////
	sf::Texture fxscre_n; fxscre_n.loadFromFile(fsystem::loadingwallpaper);
	sf::Sprite fxscreen(fxscre_n);
	sf::Sprite sprite;

	///////////////////////////////////////
	///		Load Animation
	///////////////////////////////////////
	Animation pendulum(0,0,32,96, 0.500f, pendulum_tiles, fsystem::animation_path);
	Animation furnace(0,96,32,32, 0.175f, furnace_tiles, fsystem::animation_path);
	Animation pot(0,128,32,32, 0.175f, pot_tiles, fsystem::animation_path);
	Animation fountain(0,160,64,64, 0.200f, fountain_tiles, fsystem::animation_path);
	Animation water(0,224,32,32, 0.150f, water_tiles, fsystem::animation_path);
	Animation rain(0,0, 200, 128, 0.175f, rain_tiles, fsystem::rain_path);
	Animation waterfall(0,256,96,192, 0.200f, waterfall_tiles, fsystem::animation_path);
	Animation waterfall_small(0,448,96,160, 0.200f, waterfall_tiles, fsystem::animation_path);
	Animation torch(0, 608,32,64,0.100f, torch_tiles, fsystem::animation_path);
	Animation loadscr(0,0,320,100,0.500f,loading_anim, fsystem::loading);
	Animation grass(0,672,32,32,1.000f, grass_tiles, fsystem::animation_path);

	///////////////////////////////////////
	/// LOAD MUSIC
	///////////////////////////////////////
	sf::Music music;
	music.openFromFile(mapdata.music);
	music.setLoop(true);
	music.setVolume(40);
	music.play();
	
	//////////////////////////////////////
	///	Load sounds
	//////////////////////////////////////
	sf::SoundBuffer buff;
    buff.loadFromFile(fsystem::bump);
	sf::Sound bump;
	bump.setBuffer(buff);

	//////////////////////////////////////
	///		Textures loading
	//////////////////////////////////////
	sf::Texture _layer1, _layer2, _layer3;
	_layer1.loadFromFile(mapdata.layer[0].filename);
	_layer2.loadFromFile(mapdata.layer[1].filename);
	_layer3.loadFromFile(mapdata.layer[2].filename);
	sf::Sprite layer[3];
	layer[0].setTexture(_layer1);layer[1].setTexture(_layer2);layer[2].setTexture(_layer3);

	//////////////////////////////////////
	///Purging all cell buffer
	//////////////////////////////////////
	Texturecodex::MurderOrphans();

	///////////////////////////////////////////
	////	CHARACTER INITIALIZED
	///////////////////////////////////////////
	PC chara(sf::Vector2f((float)mapdata.entry.x*32,(float)mapdata.entry.y*32),fsystem::heroX);

		
	///////////////////////////////////////////
	///Time counter initialized
	///////////////////////////////////////////
	auto tp = std::chrono::steady_clock::now();
	//////////////////////////////////////////
	///		Game loop starts here
	//////////////////////////////////////////
	while(window.isOpen())
		{
		sf::Event e;

		//////////////////////////////////
		///		EVENT POLLING LOOP
		//////////////////////////////////
		while(window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
			window.close();
		}


		//////////////////////////////////
		///      get dt
		//////////////////////////////////
		float dt;
		const auto new_tp = std::chrono::steady_clock::now();
		dt = std::chrono::duration<float>( new_tp - tp ).count();
		tp = new_tp;


		/////////////////////////////////////////////////////
		///		Handle Input
		/////////////////////////////////////////////////////
		sf::Vector2f dir( 0.0f,0.0f );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
		{
			sf::Vector2f pos = chara.returnpos();
			slack = chara.nextpos(sf::Vector2f(0, -1.0), dt);
			
			if(chara.collision_coordinates.y - dt*(collision_up) <= 0){chara.Update(-dt/2);bump. play();}
			//	prevent itp from spilling upwards , play a music

			else if( ( (int)pos.y/32)*32 >= slack.y && (mapdata.layer[2].tile[(int)pos.x/32][(int)pos.y/32 - 1] > -1))
				{chara.Update(-dt/2);bump. play();}
			
			//If nothing happens, let him be free!
			else dir.y -= 1.0f;
		
		}

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
		{
			sf::Vector2f pos = chara.returnpos();
			sf::Vector2i g = chara.returntile((int)pos.x, (int)pos.y, 0 , 1);
			slack = chara.nextpos(sf::Vector2f(0, 1.0), dt);
			
			//	stop chara from falling off the screen!
			if(chara.collision_coordinates.y + dt*collision_up >= ymax){chara.Update(-dt/2);bump. play();}
	
			//	prevent it from spilling downwards
			else if( ( (int)pos.y/32)*32 < slack.y
			&& (mapdata.layer[2].tile[g.x][g.y] > -1 ))
			{chara.Update(-dt/2);bump. play();}
			
			//If nothing happens, let him be free!
			else dir.y += 1.0f;
		}

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
		{
			
			sf::Vector2f pos = chara.returnpos();
			sf::Vector2i g = chara.returntile((int)pos.x, (int)pos.y, 0 , 0);
			slack = chara.nextpos(sf::Vector2f(-1.0, 0), dt);
			
			//	stop chara from falling off the screen!
			if(chara.collision_coordinates.x - dt*collision_down <= 0){chara.Update(-dt/2);bump. play();}
			
			//	prevent it from spilling leftward
			else if( ( (int)pos.x/32)*32 < slack.x
			&& (mapdata.layer[2].tile[g.x][g.y] > -1 ))
			{chara.Update(-dt/2);bump. play();}

			//If nothing happens, let him be free!
			else dir.x -= 1.0f;

		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
		{
			
			sf::Vector2f pos = chara.returnpos();
			sf::Vector2i g = chara.returntile((int)pos.x, (int)pos.y, 1 , 0);
			slack = chara.nextpos(sf::Vector2f(1.0, 0), dt);
			
			//	stop chara from falling off the screen!
			if(chara.collision_coordinates.x + dt*collision_down >= xmax){chara.Update(-dt/2);bump. play();}
			
			//	prevent it from spilling rightward
			else if( ( (int)chara.bottomright.x/32)*32 < slack.x
			&& (mapdata.layer[2].tile[g.x][g.y] > -1 ))
			{chara.Update(-dt/2);bump. play();}

			//If nothing happens, let him be free!
			else dir.x += 1.0f;

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
		{
			//menu shit
			if(pause == false) {pause = true; music.stop();}
		}

		}
		chara.SetDirection( dir );

		
		
		// ------- IN CASE PAUSE, STOP UPDATE!!! --------
		if(pause == false){
		///////////////////////////////
		///		Update
		///////////////////////////////
		chara.Update(dt);
		water.update(dt);
		fountain.update(dt);
		pendulum.update(dt);
		furnace.update(dt);
		torch.update(dt);
		grass.update(dt);
		pot.update(dt);
		waterfall.update(dt);
		waterfall_small.update(dt);

		///////////////////////////////
		///		Rain - update
		///////////////////////////////
		if(rainbool == true)
		{rain.update(dt);}
		}


		///////////////////////////////
		///   Clear Window
		///////////////////////////////
		window.clear(sf::Color::Black);


		///////////////////////////////
		///   Draw Procedure
		///////////////////////////////


		//////////////////////////////////////////////////////////////////////////////
		///						Draw Layers 1 and 3
		//////////////////////////////////////////////////////////////////////////////
		
		
		///------------------------------Layer 1
		for(int i=0;i<25;i++)
			for(int j=0;j<16;j++)
			{
				if(mapdata.layer[0].tile[i][j] == -1){ continue;}
				if(mapdata.layer[0].tile[i][j] == 0)
				grass.draw(window, i*32, j*32);
				else{

				layer[0].setTexture(_layer1);
				layer[0].setTextureRect(sf::IntRect((int)mapdata.layer[0].filecoords[i][j].x * 32, 	(int)mapdata.layer[0].filecoords[i][j].y * 32, 32, 32));
				layer[0].setPosition((float)i*32, (float)j*32);
				window.draw(layer[0]);
				}
			}

		
		///-------------------------------Layer 3
		for(int i=0;i<25;i++)
			for(int j=0;j<16;j++)
			{

				if(mapdata.layer[2].tile[i][j] == -1)
				continue;

				switch(mapdata.layer[2].tile[i][j])
				{

				case 2:

					furnace.draw(window,(int)mapdata.layer[2].filecoords[i][j].x * 32, (int)mapdata.layer[2].filecoords[i][j].y * 32);
					break;
				case 3:

					pot.draw(window,(int)mapdata.layer[2].filecoords[i][j].x * 32, (int)mapdata.layer[2].filecoords[i][j].y * 32);
					break;

				case 4:
					fountain.draw(window,(int)mapdata.layer[2].filecoords[i][j].x * 32, (int)mapdata.layer[2].filecoords[i][j].y * 32);
					break;

				case 5:
					water.draw(window,(int)mapdata.layer[2].filecoords[i][j].x * 32, (int)mapdata.layer[2].filecoords[i][j].y * 32);
					break;

				case 8:
					torch.draw(window,(int)mapdata.layer[2].filecoords[i][j].x * 32, (int)mapdata.layer[2].filecoords[i][j].y * 32);
					break;

				default:
				if(mapdata.layer[2].tile[i][j] == -1) break;
				layer[2].setTexture(_layer3);
				layer[2].setTextureRect(sf::IntRect((int)mapdata.layer[2].filecoords[i][j].x * 32, 
				(int)mapdata.layer[2].filecoords[i][j].y * 32, 32, 32));
				layer[2].setPosition((float)i*32, (float)j*32);
				window.draw(layer[2]);
				}
		
		}
		
			
		//////////////////////////////////////////
		/// Layer 1+3 -> chara -> Layer 2 + anims
		//////////////////////////////////////////
		chara.Draw(window);


		////////////////////////////////////////////////////////////////////////////
		///						Draw Layer - 2
		////////////////////////////////////////////////////////////////////////////
		for(int i=0;i<25;i++)
			for(int j=0;j<16;j++)
			{
				if(mapdata.layer[1].tile[i][j] == -1)
				continue;
				layer[1].setTexture(_layer2);
				layer[1].setTextureRect(sf::IntRect((int)mapdata.layer[1].filecoords[i][j].x * 32, 
				(int)mapdata.layer[1].filecoords[i][j].y * 32, 32, 32));
				layer[1].setPosition((float)i*32, (float)j*32);
				window.draw(layer[1]);
				
			}



		//////////////////////////////////////////////////////////
		////	ADDS WATERFALL SMALL AND BIG ANIMATIONS
		////	IF ANY FOUND
		//////////////////////////////////////////////////////////
		

		for(int i =0;i<25;i++)
			for(int j=0;j<16;j++)
			{
				if(mapdata.layer[2].tile[i][j] == 6)
					waterfall.draw(window, (int)mapdata.layer[2].filecoords[i][j].x,(int)mapdata.layer[2].filecoords[i][j].y);
				
				if(mapdata.layer[2].tile[i][j] == 7)
				waterfall_small.draw(window, (int)mapdata.layer[2].filecoords[i][j].x,(int)mapdata.layer[2].filecoords[i][j].y);
			}
		
		
		///////////////////////////////
		///   RAIN!!!!!!!
		///////////////////////////////
		if(rainbool == true)
		for(int i = 0; i<4; i++)
			for(int j = 0; j < 4; j++)
			{
				rain.draw(window, i*200, j*128);
			}


		////////////////////////////////////////////
		///	   Display and purge cell buffers
		////////////////////////////////////////////
		window.display();
}
return EXIT_SUCCESS;
}