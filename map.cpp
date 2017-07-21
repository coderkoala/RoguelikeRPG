#include"map.h"
#include<fstream>
using namespace mapdomain;


map::map(std::string mapname)
{
	
	/*			FORMAT OF READING THE FILE IS::
	music name
	entry.x extry.y
	exit.x exit.y
	rain-boolean
	prevmapname
	nextmapname

	...
	Rest of the map detail
	...

	-1 means null
	0 means transparent for second layer
	0 means grass for first layer
	
	--FOR LAYER THIRD--
	0 means collision
	1-8 are animations
	9 is transparent.
	*/
	int slack;
	std::ifstream f(mapname, std::ios::in);
	f>>music;
	music = fsystem::muxc_path + music;
	f>>entry.x>>entry.y>>exit.x>>exit.y>>slack>>prevmap>>nextmap;
	if(slack == 1) rain= true;
	else rain = false;
	//Fill the map details
	for(int u = 0; u<3;u++) 
	{
		
		layer[u].filename = fsystem::layertexfile[u];
		
		for(int j = 0 ; j<16;j++)
		for(int i = 0; i<25; i ++)
		{
			f>>layer[u].tile[i][j];
			///////////////////////////////////////////////
			///		Modulus division yeilds the x axis
			///////////////////////////////////////////////
			layer[u].filecoords[i][j].x=(int) layer[u].tile[i][j] % 32;
			///////////////////////////////////////////////
			///		Integer division brings the y axis
			///////////////////////////////////////////////
			layer[u].filecoords[i][j].y=(int) layer[u].tile[i][j] /32 ;
		}
	}
}






