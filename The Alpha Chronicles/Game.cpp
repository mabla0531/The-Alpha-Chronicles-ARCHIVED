#include <stack>
#include "Game.h"
#include "GameState.h"

//Game System Objects
sf::RenderWindow* window;
sf::Clock tickLimiter;

//states and activeState object
std::stack<State*> states;
GameState* gs;

//initializer functions
void createWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "The Alpha Chronicles");
	window->setActive(false); //temporarily set the window to be active so an opengl error isn't caused when the render function is threaded
}

void init() {
	createWindow();
	gs = new GameState(window);
	states.push(gs);
	
}

//system functions
void tickEvents() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void tick() {
	tickEvents();

	if (states.top()->isFinished())
		states.pop();

	if (states.empty())
		window->close();

	states.top()->tick();
}

void render() {
	window->setActive(true);

	while (window->isOpen()) {
		window->clear(sf::Color::Black);

		states.top()->render(window);

		window->display();
	}
}

void startGame() {
	init(); //init the game system. bit shtewpid, init()?

	sf::Thread renderThread(&render);
	renderThread.launch(); //thread the needle I mean render shit

	while (window->isOpen()) {
		if (tickLimiter.getElapsedTime().asMilliseconds() >= 10) { //only tick the game 100 times per second, to keep game running the same speed on all PC's
			tickLimiter.restart();
			tick(); //what do you call a game's main backend function that has confidence issues? A nervous tick(). 
		}
	}
}
