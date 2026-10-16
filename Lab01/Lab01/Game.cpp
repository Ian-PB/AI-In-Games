/// <summary>
/// author Pete Lowe May 2026
/// you need to change the above line or lose marks
/// </summary>


#include "Game.h"
#include "Globals.h"
#include <iostream>

// Behaviours
#include "Wander.h"
#include "Seek.h"
#include "Pursue.h"
#include "Arrive.h"

#include "Flocking.h"
#include "Swarming.h"


/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the texts
/// load and setup the images
/// load and setup the sounds
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{windowSize.x, windowSize.y}, 32U }, "SFML Game 3.1" },
	m_DELETEexitGame{false} //when true game will exit
{
	player.Init({100, 100});
	// NPC sprite
	if (!Npc::texture.loadFromFile("ASSETS\\IMAGES\\alienShip.png"))
	{
		// Error
	}
	SetupNpcs();

	if (!font.openFromFile(("ASSETS\\FONTS\\Jersey20-Regular.ttf")))
	{
		std::cout << "Font not found\n";
	}
	instructions.setFont(font);
	instructions.setFillColor(sf::Color::Black);
	instructions.setCharacterSize(24);
	instructions.setString("1 - Wander\n2 - Seek\n3 - Pursue\n4 - Arrive1\n5 - Arrive2");
	instructions.setPosition({ 10, 10 });

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but method needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{	
	while ( std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			sf::Event::KeyPressed newKeypress;
			newKeypress = *newEvent->getIf<sf::Event::KeyPressed>();
			processKeyPress(newKeypress);
		}
		if (newEvent->is < sf::Event::MouseButtonPressed>()) // user pressed mouse button
		{
			sf::Event::MouseButtonPressed newMousePress;
			newMousePress = *newEvent->getIf<sf::Event::MouseButtonPressed>();
			processMousePress(newMousePress);
		}
		//could also check for mouse move, mouse wheel, text entered, window resized etc.
		// sf::Event::KeyReleased
		// sf::Event::MouseMoved
		// sf::Event::MouseButtonReleased
		// sf::Event::TextEntered

	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeyPress(sf::Event::KeyPressed t_keyPress)
{	
	if (sf::Keyboard::Key::Escape == t_keyPress.code)
	{
		m_DELETEexitGame = true; // only need one of these, but this is an example of checking events rather than state
	}

	ToggleNpcs(t_keyPress);
}

/// <summary>
/// deal with mouse button presses
/// </summary>
/// <param name="t_event">Mouse press event</param>
void Game::processMousePress(sf::Event::MouseButtonPressed t_mousePress)
{
}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; // only need one of these, but this is an example of checking state rather than events
	}
}

/// <summary>
/// check current status of mouse
/// </summary>
void Game::checkMouseState()
{
	sf::Vector2f location;
	location = static_cast<sf::Vector2f>( sf::Mouse::getPosition(m_window));
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	checkMouseState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}

	if (activeBehaviour == ActiveBehaviours::Mixed)
	{
		player.Movement();

		for (int i = 0; i < MAX_NPC_AMOUNT; i++)
			npcs[i].Movement(npcs, MAX_NPC_AMOUNT);
	}
	else if (activeBehaviour == ActiveBehaviours::Groups)
	{
		for (int i = 0; i < GROUPING_AMOUNT; i++)
		{
			groupingNpcs[i].Movement(npcs, MAX_NPC_AMOUNT);
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(NICE_BLUE);


	if (activeBehaviour == ActiveBehaviours::Mixed)
	{
		player.Render(m_window);

		for (int i = 0; i < MAX_NPC_AMOUNT; i++)
			npcs[i].Render(m_window);

		m_window.draw(instructions);	
	}
	else if (activeBehaviour == ActiveBehaviours::Groups)
	{
		for (int i = 0; i < GROUPING_AMOUNT; i++)
			groupingNpcs[i].Render(m_window);
	}
	
	m_window.display();
}

void Game::ToggleNpcs(sf::Event::KeyPressed t_keyPress)
{
	if (activeBehaviour == ActiveBehaviours::Mixed)
	{
		if (sf::Keyboard::Key::Num1 == t_keyPress.code)
			npcs[0].Toggle();
		else if (sf::Keyboard::Key::Num2 == t_keyPress.code)
			npcs[1].Toggle();
		else if (sf::Keyboard::Key::Num3 == t_keyPress.code)
			npcs[2].Toggle();
		else if (sf::Keyboard::Key::Num4 == t_keyPress.code)
			npcs[3].Toggle();
		else if (sf::Keyboard::Key::Num5 == t_keyPress.code)
			npcs[4].Toggle();
	}
	else if (activeBehaviour == ActiveBehaviours::Groups)
	{
		if (sf::Keyboard::Key::F == t_keyPress.code)
		{
			for (int i = 0; i < GROUPING_AMOUNT; i++)
			{
				groupingNpcs[i].SetupBehaviour(new Flocking(groupingNpcs[i].GetPosRef(), groupingNpcs[i].GetVelocityRef(), groupingNpcs, GROUPING_AMOUNT));
			}
		}
		else if (sf::Keyboard::Key::S == t_keyPress.code)
		{
			for (int i = 0; i < GROUPING_AMOUNT; i++)
			{
				groupingNpcs[i].SetupBehaviour(new Swarming(groupingNpcs[i].GetPosRef(), groupingNpcs[i].GetVelocityRef(), groupingNpcs, GROUPING_AMOUNT));
			}
		}
	}
}

void Game::SetupNpcs()
{
	if (activeBehaviour == ActiveBehaviours::Mixed)
	{
		// Setup npcs behaviours
		npcs[0].Init(&player, { 400, 300 });
		npcs[0].SetupBehaviour(new Wander(npcs[0].GetPosRef()));
		npcs[0].SetColor(sf::Color::Green);
		npcs[0].SetName("Wander");

		npcs[1].Init(&player, { 300, 200 });
		npcs[1].SetupBehaviour(new Seek(npcs[1].GetPosRef(), player.GetPosRef()));
		npcs[1].SetColor(sf::Color::Yellow);
		npcs[1].SetName("Seek");

		npcs[2].Init(&player, { 400, 300 });
		npcs[2].SetupBehaviour(new Pursue(npcs[2].GetPosRef(), player.GetPosRef(), player.GetVelRef()));
		npcs[2].SetColor(sf::Color::Red);
		npcs[2].SetName("Pursue");

		npcs[3].Init(&player, { 500, 400 });
		npcs[3].SetupBehaviour(new Arrive(npcs[3].GetPosRef(), player.GetPosRef()));
		npcs[3].SetColor(sf::Color::Blue);
		npcs[3].SetSpeed(0.15f);
		npcs[3].SetName("Arrive 1");

		npcs[4].Init(&player, { 600, 500 });
		npcs[4].SetupBehaviour(new Arrive(npcs[4].GetPosRef(), player.GetPosRef()));
		npcs[4].SetColor(sf::Color::Blue);
		npcs[4].SetSpeed(0.2f);
		npcs[4].SetName("Arrive 2");

		for (int i = 0; i < MAX_NPC_AMOUNT; i++)
		{
			npcs[i].SetupObjectAvoidance(new ObjectAvoidance(npcs[i].GetPosRef()));
		}
	}
	else if (activeBehaviour == ActiveBehaviours::Groups)
	{
		// Grouping
		for (int i = 0; i < GROUPING_AMOUNT; i++)
		{
			sf::Vector2f randPos = { (float)(rand() % m_window.getSize().x), (float)(rand() % m_window.getSize().y) };
			// std::cout << "Pos: " << randPos.x << ", " << randPos.y << "\n";
			groupingNpcs[i].Init(&player, randPos);
			groupingNpcs[i].SetupBehaviour(new Swarming(groupingNpcs[i].GetPosRef(), groupingNpcs[i].GetVelocityRef(), groupingNpcs, GROUPING_AMOUNT));
			groupingNpcs[i].SetColor(sf::Color::Blue);
			groupingNpcs[i].SetName(""); // Empty so not shown
		}
	}
}
