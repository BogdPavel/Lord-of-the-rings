#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "cstring.h"
#include "camera.h"

using namespace sf;
using std::string;

const int LENGTH = 20;

class Records {
	static int position;
	static float pos;
	int score;
	char playerName[LENGTH];
	int gameTime;
	//time_t date_of_game;
	
public:
	Records(int = 0, String = "", int = 0);

	void setPlayerName(String name);
	String getPlayerName() const; 
	void setScore(int number);
	int getScore() const;
	void setGameTime(int time);
	int getGameTime() const;

	static void showRecords(RenderWindow& window);
	static void printTable(RenderWindow& window, Text& buffer);
	static void printPlayers(RenderWindow& window, Text& buffer, Records& player);
	static void setResult(String playerName, int score, int gameTime);
	static void function(int number, Records& player);
	static void init();
};

#endif