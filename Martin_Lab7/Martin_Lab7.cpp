#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Create the side2
	PhysicsRectangle side2;
	side2.setSize(Vector2f(20, 1200));
	side2.setCenter(Vector2f(50, 590));
	side2.setStatic(true);
	world.AddPhysicsBody(side2);

	// Create the side3
	PhysicsRectangle side3;
	side3.setSize(Vector2f(100, 100));
	side3.setCenter(Vector2f(400, 500));
	side3.setStatic(true);
	world.AddPhysicsBody(side3);

	// Create the side1
	PhysicsRectangle side1;
	side1.setSize(Vector2f(20, 1200));
	side1.setCenter(Vector2f(700, 590));
	side1.setStatic(true);
	world.AddPhysicsBody(side1);

	// Create the ceiling
	PhysicsRectangle ceilling;
	ceilling.setSize(Vector2f(800, 20));
	ceilling.setCenter(Vector2f(400, 10));
	ceilling.setStatic(true);
	world.AddPhysicsBody(ceilling);

	int bangCount(1);
	side3.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		if (bangCount == 3) 
		{
			exit(0);
		}
	};

	int thudCount(1);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	ball.applyImpulse(Vector2f(0.8, 0.5));
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(side1);
		window.draw(side2);
		window.draw(side3);
		window.draw(ceilling);
		window.display();
	}
}

