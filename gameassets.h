#pragma once
#include <string>

////////////////////////////////////////////////
///		Definition of the number of frames for 
///		Various animation
////////////////////////////////////////////////
#define water_tiles 8
#define pendulum_tiles 4
#define furnace_tiles 3
#define pot_tiles 3
#define fountain_tiles 5
#define rain_tiles 4
#define waterfall_tiles 4
#define torch_tiles 8
#define loading_anim 3
#define grass_tiles 2


//////////////////////////////////////////////////
/// This is where all the files are listed out
///	simply declare a string variable, make it
/// understandable, then use the alias path name!
//////////////////////////////////////////////////

namespace fsystem{

/////////////////////////////////////////
///	Animation index
///	Used generally for counting the 
///	number of frames in an animation
///	in order to pass it as argument easily
/////////////////////////////////////////
enum anim_object
{
	collide_tile,
	pendulum_tile,
	furnace_tile,
	pot_tile,
	fountain_tile,
	water_tile,
	waterfall_tile,
	waterfall_small_tile,
	torch_tile,
	count
};

	
static const std::string animation_path = "game/anim/anim_ddx";
static const std::string rain_path = "game/shd/rain_shd";
static const std::string heroX = "game/char/hero_ddx";
static const std::string loadingwallpaper="game/tex/loading_background";
static const std::string loading="game/anim/anim_loading";
static const std::string muxc_path = "game/mux/";
static const std::string bump = "game/snd/snd_bump.wav";
static const std::string layertexfile[3]={"game/tex/layer_01", "game/tex/layer_02","game/tex/layer_03"};
static const std::string map[5] = {"game/map/map_01","game/map/map_02","game/map/map_03","game/map/map_04","game/map/map_05"};
};
