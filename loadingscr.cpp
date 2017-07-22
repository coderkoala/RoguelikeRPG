#include "loadingscr.h"

loadingscr::loadingscr(sf::RenderWindow &window) : Animation(0,0,320,100,0.500f,loading_anim, fsystem::loading), win(window)
{
	////////////////////////////////////////
	///		Load the Loading screen assets
	////////////////////////////////////////
	gTex=Texturecodex::Acquire(fsystem::loadingwallpaper);
}

void loadingscr::screen()
{
	///////////////////////////////////////
	/// LOCKS THREAD, MAKES IT MUTUALLY EX
	///////////////////////////////////////
	std::mutex mutex;
	mutex.lock();
	sf::Sprite assprite(*gTex);
	win.draw(assprite);
	win.display();
	Texturecodex::MurderOrphans();

	///////////////////////////////////////
	/// LOAD MUSIC
	///////////////////////////////////////
	sf::SoundBuffer sound;
	sound.loadFromFile(fsystem::snd + "snd_mushroomdance.ogg");
	sf::Sound asound(sound);
	asound.setLoop(true);
	asound.setVolume(40);
	asound.play();	
	for(int i = 0; i<6; i++){
	win.clear(sf::Color::Black);
	win.draw(assprite);
	draw(win, 0, 412);
	win.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	update(0.5);
	}

	///////////////////////////////////////
	/// UNLOCKS THREAD
	///////////////////////////////////////
	mutex.unlock();
}
