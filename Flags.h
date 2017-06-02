#pragma once

#include "Game.h"
#include "PlayerData.h"

class Flags {

	PlayerData playerDataA;
	PlayerData playerDataB;
    Game* currentGame = nullptr;
    bool shouldExitProgram = false;
    bool isRecordMode = false;
	unsigned int roundCounter = 0;

	static bool isAutoModeEnabled();
	bool shouldContinueAutoMode() const;

    void selectPlayerNames();
    void beginKeyboardGame();
    void beginReverseKeyboardGame();
    void resetPlayerScores();
    void toggleRecordMode();

	void startKeyboardGame();
	void startAutoGame();
	void awardWinner();
	void printGameSummary() const;

	void displayMenu() const;
	void HandleMenuInput();

public:
	Flags();
	~Flags();
	Flags(Flags const&) = delete;
	void operator=(Flags const&) = delete;

	static void test_printMemoryLeakStatus();

	void configure(int argc, const char * argv[]);
    void run();
    void finishGame(bool shouldExitProgram);
	unsigned int roundsPlayed() const { return roundCounter; }
};
