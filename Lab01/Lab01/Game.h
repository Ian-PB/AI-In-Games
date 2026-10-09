/// <summary>
/// author Pete Lowe May 2026
/// you need to change the above line or lose marks
/// Also don't have any member properties called Delete...
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.1\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the #endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Npc.h"


enum class ActiveBehaviours
{
	Mixed, // Wander, seek, ext
	Groups
};

const sf::Color NICE_BLUE{ 16, 122,176,255 }; // const colour

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeyPress(sf::Event::KeyPressed t_keyPress);
	void processMousePress(sf::Event::MouseButtonPressed t_mousePress);
	void checkKeyboardState();
	void checkMouseState();
	void update(sf::Time t_deltaTime);
	void render();

	void ToggleNpcs(sf::Event::KeyPressed t_keyPress);
	void SetupNpcs();
	
	sf::RenderWindow m_window; // main SFML window

	bool m_DELETEexitGame; // control exiting game

	// Objects
	ActiveBehaviours activeBehaviour = ActiveBehaviours::Groups;

	Player player;
	static const int MAX_NPC_AMOUNT = 5;
	Npc npcs[MAX_NPC_AMOUNT];

	static const int GROUPING_AMOUNT = 200;
	Npc groupingNpcs[GROUPING_AMOUNT];

	sf::Font font;
	sf::Text instructions{ font };
};

#pragma warning( pop ) 
#endif // !GAME_HPP

