#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "cpoint.h"
#include "winsys.h"
#include <list>
enum Directions {UP,DOWN,RIGHT,LEFT};
struct Body{
  Directions direct; // Actuall snake direction
  list<CPoint> body; //List of CPoint represents body in rectangular coordinate system
};
class CSnake: public CFramedWindow{
  Body fullsnake; // Logic of body, sets of points and 0-3 number of direction
  int speed; // Speed of snake - Lower is faster
  int points; // How many fruits Snake got
  bool lost; // Did you lost ?
  CPoint fruitxy; // Position of fruit
  bool fruitexist; // Is fruit in game yet ?
  void paint(); // Print snake in game
  void changeSnakeDirection(int key); // Based on key, change direction of snake
  void adjustSnakeMovement(int direction); // Change front of the snake and check if he is not goind to run away from game
  bool handleEvent(int key); // Wrapper of changing direction and make a move
  void finalScore(); // Print final score (if lost)
  void move(); // BIG. Calculate of every tick. Smth like rendering
  void score(); // Check if collide with fruit add score and correct speed
  void paintSnake(); // Just print snake in window
  void makefruit(); // Create new fruit
  void level();
  bool collision(CPoint&); // Check collision snake with point

public:
  CSnake(CRect r, char _c = ' ');
};

#endif
