// chckrs.h

#ifndef CHCKRS_H
#define CHCKRS_H

#include <string>
#include <iostream>
#include <sstream>

extern int checkersGrid[8][8];
extern int player1, player2, currentplayer;
extern bool winquestionmark;

void populateCheckersGrid();
void forcejump(int playerturn, std::string piece);
void checkwin();
void playerturn(int curre);
void move(int playerturn, std::string piece);
int randomstarter();
void swapturn(int playert);
void display();
void checkers();

#endif // CHCKRS_H