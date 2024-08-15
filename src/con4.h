#ifndef CONNECT4_H
#define CONNECT4_H

extern int grid[7][6];
extern int player1, player2;
extern int currentplayer;
extern bool winquestionmark;

void populategrid();
void dropcoin(int column, int playercoin);
void checkdraw();
void checkwin();
int randomstarter();
void swapturn(int playert);
void playerturn(int player);
bool endgame();
void connect4();

#endif // CONNECT4_H
