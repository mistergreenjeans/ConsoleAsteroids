#include <windows.h>

#include <iostream>
#include "ConsoleGraphicsEngine.h"
#include <unordered_map>
#include <chrono>
#include <vector>
#include "Entity.h"
#include "Asteroid.h"
#include "Player.h"
#include "Bullet.h"

using namespace std;
using namespace chrono;


 
/*
* method for checking if two circles overlap
* 
* @param point1 : center of circle 1
* @param r1 : radius of circle 1
* @param point2 : center of circle 2
* @param r2 : radius of circle 2
* 
* @return true if circles overlap, otherwise false
*/
bool circleCircle(Vec2 point1, double r1, Vec2 point2, double r2) {
	if ((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) < (r1 + r2) * (r1 + r2)) {
		return true;
	}
	return false;
}

/*
* method for checking if two circles overlap in a screen wrapping environment
*
* @param point1 : center of circle 1
* @param r1 : radius of circle 1
* @param point2 : center of circle 2
* @param r2 : radius of circle 2
* @param width : width of game world
* @param height : height of game world
* 
* @return true if circles overlap (normally or over screen border), otherwise false
*/
bool circleCircleWrap(Vec2 point1, double r1, Vec2 point2, double r2,int width,int height) {
	// checks multiple versions of the circles shifted by the screens width
	return circleCircle(point1, r1, point2, r2) || circleCircle(point1 - Vec2(width, 0), r1, point2, r2) || circleCircle(point1- Vec2(0, height), r1, point2 , r2) || circleCircle(point1 + Vec2(width, 0), r1, point2, r2)|| circleCircle(point1 + Vec2(0, height), r1, point2, r2);
}




int main()
{
	int garbage;
	
	
	
	string scoreSprite = "000000000000000000000000000000000\n";
		  scoreSprite += "011111011111011111011111011111000\n";
		  scoreSprite += "010000010000010001010001010000010\n";
		  scoreSprite += "011111010000010001011110011111000\n";
		  scoreSprite += "000001010000010001010001010000000\n";
		  scoreSprite += "011111011111011111010001011111010\n";
		  scoreSprite += "000000000000000000000000000000000\n";

	string livesSprite = "000000000000000000000000000000000\n";
	      livesSprite += "010000011111010001011111011111000\n";
		  livesSprite += "010000000100010001010000010000010\n";
		  livesSprite += "010000000100001010011111011111000\n";
		  livesSprite += "010000000100001010010000000001000\n";
		  livesSprite += "011111011111000100011111011111010\n";
		  livesSprite += "000000000000000000000000000000000\n";

	string shipSprite = "0001000\n";
	      shipSprite += "0001000\n";
		  shipSprite += "0010100\n";
		  shipSprite += "0010100\n";
		  shipSprite += "0010100\n";
		  shipSprite += "0100010\n";
		  shipSprite += "0111110\n";
	
	std::unordered_map<int, std::string> intToSprite;
	intToSprite[1]  = "0000000\n";
	intToSprite[1] += "0111000\n";
	intToSprite[1] += "0001000\n";
	intToSprite[1] += "0001000\n";
	intToSprite[1] += "0001000\n";
	intToSprite[1] += "0111110\n";
	intToSprite[1] += "0000000\n";

	intToSprite[2]  = "0000000\n";
	intToSprite[2] += "0111110\n";
	intToSprite[2] += "0000010\n";
	intToSprite[2] += "0111110\n";
	intToSprite[2] += "0100000\n";
	intToSprite[2] += "0111110\n";
	intToSprite[2] += "0000000\n";

	intToSprite[3]  = "0000000\n";
	intToSprite[3] += "0111110\n";
	intToSprite[3] += "0000010\n";
	intToSprite[3] += "0111110\n";
	intToSprite[3] += "0000010\n";
	intToSprite[3] += "0111110\n";
	intToSprite[3] += "0000000\n";

	intToSprite[4]  = "0000000\n";
	intToSprite[4] += "0100010\n";
	intToSprite[4] += "0100010\n";
	intToSprite[4] += "0111110\n";
	intToSprite[4] += "0000010\n";
	intToSprite[4] += "0000010\n";
	intToSprite[4] += "0000000\n";

	intToSprite[5]  = "0000000\n";
	intToSprite[5] += "0111110\n";
	intToSprite[5] += "0100000\n";
	intToSprite[5] += "0111110\n";
	intToSprite[5] += "0000010\n";
	intToSprite[5] += "0111110\n";
	intToSprite[5] += "0000000\n";

	intToSprite[6]  = "0000000\n";
	intToSprite[6] += "0111110\n";
	intToSprite[6] += "0100000\n";
	intToSprite[6] += "0111110\n";
	intToSprite[6] += "0100010\n";
	intToSprite[6] += "0111110\n";
	intToSprite[6] += "0000000\n";

	intToSprite[7]  = "0000000\n";
	intToSprite[7] += "0111110\n";
	intToSprite[7] += "0000010\n";
	intToSprite[7] += "0000010\n";
	intToSprite[7] += "0000010\n";
	intToSprite[7] += "0000010\n";
	intToSprite[7] += "0000000\n";

	intToSprite[8]  =  "0000000\n";
	intToSprite[8] += "0111110\n";
	intToSprite[8] += "0100010\n";
	intToSprite[8] += "0111110\n";
	intToSprite[8] += "0100010\n";
	intToSprite[8] += "0111110\n";
	intToSprite[8] += "0000000\n";

	intToSprite[9]  = "0000000\n";
	intToSprite[9] += "0111110\n";
	intToSprite[9] += "0100010\n";
	intToSprite[9] += "0111110\n";
	intToSprite[9] += "0000010\n";
	intToSprite[9] += "0000010\n";
	intToSprite[9] += "0000000\n";


	intToSprite[0]  = "0000000\n";
	intToSprite[0] += "0111110\n";
	intToSprite[0] += "0100110\n";
	intToSprite[0] += "0101010\n";
	intToSprite[0] += "0110010\n";
	intToSprite[0] += "0111110\n";
	intToSprite[0] += "0000000\n";

	const int SCREEN_HEIGHT = 250;
	const int SCREEN_WIDTH = 300;
		 
	bool sure = false;
	int cSize;
	cout << "Console asteroids\n";
	cout << "enter your prefered size of text (reccommended 4 for 3840 x 2160)\n";
	cout << "note that numbers too big for your monitor will result in the program breaking\n";
	cout << "if something goes wrong, try again with a smaller number\n";

		
	std::cin >> cSize;

	

	

	int CHARACTER_W = cSize;
	int CHARACTER_H = cSize;
	//create console graphics class with size parameters. (did not change font size)
	ConsoleGraphicsEngine temp = ConsoleGraphicsEngine(SCREEN_WIDTH, SCREEN_HEIGHT, CHARACTER_W, CHARACTER_H);		
	
	// create player, pass in 
	Player p1 = Player(temp);

	// create list to store asteroids
	vector<Asteroid> rockList;

	// create variables to use later
	int spawnX;
	int spawnY;
	Vec2 rockSpawn;
	Vec2 rockVelSpawn;
	double rRadius;
	int score = 0;
	int scoreTenK = 0;
	vector<int> scoreDraw;
	

	
	double rockNum = 0;
	double maxRockNum = 1;
	double sizePrev = 0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////######################################################################################################################################################/////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	//while loop that runs the game
	while (!temp.keys[KEY(ESC)]) {
		// calculate time between frames (Delta time)
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		temp.updateKeyState();	//update the keys array every frame

		// populate vector with integers that represent each place of score
		// (will iterate through vector later to draw the score using the number "sprites")
		scoreDraw.clear();
		for (int scoreTemp = score; scoreTemp != 0; scoreTemp /= 10) {
			scoreDraw.push_back(scoreTemp % 10);
		}

		// iterate through list of asteroids updating them
		for (int i = 0; i < rockList.size(); i++) {
			
			// check if asteroid collides with player (and player is active (alive/onscreen))
			if (circleCircleWrap(rockList.at(i).pos, rockList.at(i).radius, p1.pos, p1.radius, temp.width, temp.height)&&p1.isOnScreen) {
				// player takes damage and rock that killed player is turned red
				rockList.at(i).setColor(COLOR(FG_RED) + COLOR(BG_RED));
				p1.setColor(COLOR(FG_RED) + COLOR(BG_RED));
				p1.die();
			}
			
			// draw and update asteroid
			rockList.at(i).draw(temp);
			rockList.at(i).updatePos(temp, fElapsedTime);

			// iterate through all of the players current shots
			for (int j = 0; j < p1.shots.size()&& rockList.size() >0; j++) {

				// check if bullet collides with asteroid
				if (circleCircle(rockList.at(i).pos, rockList.at(i).radius, p1.shots.at(j).pos, p1.shots.at(j).radius)) {
					// after a collision, remove bullet from scene and split asteriod
					p1.endBullet(j);
					j--;

					// increase score
					score += 50;
					scoreTenK += 50;
					vector<Asteroid> temp = rockList.at(i).split();
					if (!temp.empty()) {
						// after getting two new asteriods, add them to the scene
						for (int i = 0; i < temp.size(); i++) {
							rockList.push_back(temp.at(i));
						}
					}
					// remove asteriod that was hit
					rockList.erase(rockList.begin() + i);
					// go back to stop error
					if (i > 0) {
						i--;
					}

					// if the player gets 10000 points, give the player another life and
					// reset variable that tracks when the player gets 10000 pts
					if (scoreTenK == 10000) {
						p1.lives++;
						scoreTenK = 0;
					}

				}
			}
			
		}
		
		// every time a rock is broken, re calculate the number of rocks that can spawn
		// (as this number goes up, difficulty increases)
		if (rockList.size() != sizePrev) {
			rockNum = 0;
			for (int i = 0; i < rockList.size(); i++) {
				rockNum += 1/pow(2,rockList.at(i).splits);
			}
		}
		sizePrev = rockList.size();
		
		// spawn rocks if the current number of rocks is not the max number of rocks
		if(rockNum<=maxRockNum-1){

			// generate a spawn position for the rock
			rockSpawn = Vec2(((float)rand() / (float)RAND_MAX) * temp.width, ((float)rand() / (float)RAND_MAX) * temp.height);
			rockVelSpawn = Vec2(((float)rand() / (float)RAND_MAX) * 50 - 25, ((float)rand() / (float)RAND_MAX) * 40 - 20);
			rRadius = 0;

			// if the rock spawns near the player, do nothing, otherwise create a new asteroid to spawn
			if (!circleCircleWrap(rockSpawn, rRadius, p1.pos, p1.radius + 100, temp.width, temp.height)) {
				rockList.push_back(Asteroid(rockSpawn, rockVelSpawn, 30, 2, 15));
			}

		}

		// equation to calculate the allowed number of rocks in the scene
		maxRockNum = (int)(sqrt(score/600)) + 1;

		// respawn player sequence
		if (p1.respawn(temp, fElapsedTime)) {
			for (int i = 0; i < rockList.size(); i++) {
				// give player spawn protection so they dont die immediatly (erase rocks in close radius)
				if (circleCircle(Vec2(temp.width / 2, temp.height / 2), p1.rr, rockList.at(i).pos, rockList.at(i).radius)) {
					rockList.erase(rockList.begin() + i);
					i--;
				}

			}
		}

		if (p1.lives == 0) {
			temp.setColor(BG_WHITE + FG_WHITE);

			std::string gameover  = "0000000000000000000000000000000000000000000000000000000\n";
						gameover += "0111110111110100010111110000000111110100010111110111110\n";
						gameover += "0100000100010110110100000000000100010100010100000100010\n";
						gameover += "0101110111110101010111110000000100010010100111110111110\n";
						gameover += "0100010100010100010100000000000100010010100100000100100\n";
						gameover += "0111110100010100010111110000000111110001000111110100010\n";
						gameover += "0000000000000000000000000000000000000000000000000000000\n";
			temp.drawString(SCREEN_WIDTH/2 - 27, SCREEN_HEIGHT / 2 - 4, gameover);

			std::string restartR  = "0000000000000000000000000000000000000000000\n";
						restartR += "0100111110010000000011111010000111110100010\n";
						restartR += "0010100010100111110010001010000100010100010\n";
						restartR += "0000111110000000000011111010000111110111110\n";
						restartR += "0000100100000111110010000010000100010001000\n";
						restartR += "0000100010000000000010000011110100010001000\n";
						restartR += "0000000000000000000000000000000000000000000\n";
			
			temp.drawString(SCREEN_WIDTH / 2 - 21, SCREEN_HEIGHT / 2 + 5, restartR);
			if (temp.keys['R']) {
				p1.lives = 3;
				rockList.clear();
				score = 0;
				scoreTenK = 0;
			}
		}

		// draw player
		p1.setColor(COLOR(BG_WHITE) + COLOR(FG_WHITE));
		p1.draw(temp);
		p1.drawShots(temp);

		// update player
		p1.bulletHandler(temp, fElapsedTime);
		p1.shoot(temp.keys[' '],fElapsedTime,.25);
		

		p1.thrust(100, fElapsedTime, temp.keys['W'], temp.keys['A'], temp.keys['D']);
		p1.update(temp);

		// draw triangles in top left to display the number of lives that the player has
		int livesXPosition = 34;
		for (int i = 0; i < p1.lives; i++) {
			temp.drawString(livesXPosition,8, shipSprite);
			livesXPosition += 6;
		}
		
		// draw lives text
		temp.drawString(1, 8, livesSprite);

		// draw score to screen
		temp.drawString(1,1,scoreSprite);

		// draw score to screen (in retrospect, a map wouldve been way better)
		int scoreXPosition=34;
		// iterate through vector of integers and draw each one as a sprite
		for (int i = scoreDraw.size()-1; i >=0; i--) {
			temp.drawString(scoreXPosition, 1, intToSprite[scoreDraw.at(i)]);
			scoreXPosition += 6;
		}

		// draw to console
		temp.render();				

		// reset to black screen
		temp.setColor(COLOR(FG_GREEN) + COLOR(BG_BLACK));
		temp.clear(' ');			
		
	}
	temp.setColor(BG_BLACK + FG_WHITE);
	temp.clear(' ');
	temp.render();
	temp.close();
	system("cls");
}








