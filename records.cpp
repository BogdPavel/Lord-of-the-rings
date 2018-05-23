#include "records.h"

int Records::position = 50;
float Records::pos;

void Records::init() {
	pos = view.getCenter().x - 400;
}

Records::Records(int scoreValue, String playerNameValue, int gameTimeValue) {
	setPlayerName(playerNameValue);
	setScore(scoreValue);
	setGameTime(gameTimeValue);
}

int Records::getScore() const {
	return score;
}

int Records::getGameTime() const {
	return gameTime;
}

String Records::getPlayerName() const {
	return playerName;
}

void Records::setScore(int scoreValue) {
	score = scoreValue;
}

void Records::setGameTime(int gameTimeValue) {
	gameTime = gameTimeValue;
}

void Records::setPlayerName(String playerNameValue) {
	string buf = playerNameValue;
	const char* string = buf.c_str();
	int length = playerNameValue.getSize();
	length = length < LENGTH ? length : LENGTH - 1;
	memcpy(playerName, string, length);
	playerName[length] = '\0';
}

void Records::printPlayers(RenderWindow& window, Text& buffer, Records& player) {
	char buf[10];
	position += 50;
	buffer.setString(player.getPlayerName()); buffer.setPosition(pos + 140, position); window.draw(buffer);
	buffer.setString(itoa(player.getScore(), buf,10)); buffer.setPosition(pos + 320, position); window.draw(buffer);
	buffer.setString(itoa(player.getGameTime(), buf,10)); buffer.setPosition(pos + 460, position); window.draw(buffer);
	if(position == 300) position = 50;
}

void Records::printTable(RenderWindow& window, Text& buffer) {
	buffer.setString("Name"); buffer.setPosition(pos + 140, 50); window.draw(buffer);
	buffer.setString("Score"); buffer.setPosition(pos + 300, 50); window.draw(buffer);
	buffer.setString("Time"); buffer.setPosition(pos + 440, 50); window.draw(buffer);
	buffer.setString("Date"); buffer.setPosition(pos + 600, 50); window.draw(buffer);
}

void Records::showRecords(RenderWindow& window) {
	window.clear(Color(200, 193, 174));

	Image scoreBackgroungImage; scoreBackgroungImage.loadFromFile("images/scorebackground.png");
	Texture scoreBackgroungTexture; scoreBackgroungTexture.loadFromImage(scoreBackgroungImage);
	Sprite scoreBackgroung; scoreBackgroung.setTexture(scoreBackgroungTexture); scoreBackgroung.setPosition(pos + 0, 0);

	window.draw(scoreBackgroung);

	Font font; font.loadFromFile("Applications/a_font_with_serifs.ttf");
	Text buffer("", font, 40); buffer.setColor(Color(255, 215, 0)); buffer.setStyle(Text::Bold);
	printTable(window, buffer);

	ifstream recordsFile("RecordTable.dat", ios::binary);
	Records player;
	recordsFile.read(reinterpret_cast< char* >(&player), sizeof(Records));

	while(recordsFile && !recordsFile.eof()) {
		printPlayers(window, buffer, player);
		recordsFile.read(reinterpret_cast< char* >(&player), sizeof(Records));
	}
	recordsFile.close();
	window.display();
}

void Records::setResult(String playerNameValue, int score, int gameTime) {
	init();
	Records player(score, playerNameValue, gameTime);
	string buffer;
	Records object;
	int flag = -1, arr[5];
	ifstream recordsFile("RecordTable.dat", ios::binary);
	if(!recordsFile) 
		exit(1);
	for(int i = 0; i < 5; i++) {
		recordsFile.read(reinterpret_cast< char* >(&object), sizeof(Records));
		arr[i] = object.getScore();
		if(object.getPlayerName() == player.getPlayerName()) {
			if(object.getScore() <= player.getScore()) {
				flag = i;
			}
			else return;
		}
	}
	recordsFile.close();
	if(flag < 0) {
		for(int i = 0; i < 5; i++) {
			if(arr[i] == player.getScore()) {
				int j;
				for(j = i; arr[j] == arr[i]; j++) ;
				function(j, player); break;
			}
			if(arr[i] < player.getScore()) {
				function(i, player); break;
			}
		}
	}
	else {
		 function(flag, player);
	}
}

void Records::function(int number, Records& player) {
	Records object;
	fstream recordsFile("RecordTable.dat", ios::binary | ios::in | ios::out);
	if(!recordsFile) 
		exit(1);
	for(int i = 0; i < 5; i++) {
		if(4 - i == number) {
			recordsFile.seekp((4 - i) * sizeof(Records));
			recordsFile.write(reinterpret_cast< const char* >(&player), sizeof(Records));
			recordsFile.close();
			return;
		}
		recordsFile.seekp((3 - i) * sizeof(Records));
		recordsFile.read(reinterpret_cast< char* >(&object), sizeof(Records));
		recordsFile.write(reinterpret_cast< const char* >(&object), sizeof(Records));
	}
}
