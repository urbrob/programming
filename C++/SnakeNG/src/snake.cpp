#include "snake.h"
#include "screen.h"
#include <unistd.h>
#include <time.h>

CSnake::CSnake(CRect r, char _c):
CFramedWindow(r, _c){
    lost = false;
    fruitexist = false;
    points = 0;
    speed = 200;
    timeout(200);
    fullsnake.direct = UP;
    fullsnake.body.push_back(CPoint(10,2));
    fullsnake.body.push_back(CPoint(9,2));
    fullsnake.body.push_back(CPoint(8,2));
}

void CSnake::finalScore(){
	if(lost){
	  gotoyx(geom.topleft.y + 5,geom.topleft.x + 12);
    printl("GAME OVER - SCORE: %d",points);
	}
}

// Change direction based on key
void CSnake::changeSnakeDirection(int key){
  switch (key){
    case KEY_RIGHT: if(fullsnake.direct != LEFT) fullsnake.direct = RIGHT; break;
    case KEY_LEFT: if(fullsnake.direct != RIGHT) fullsnake.direct = LEFT; break;
    case KEY_UP: if(fullsnake.direct != DOWN) fullsnake.direct = UP; break;
    case KEY_DOWN: if(fullsnake.direct != UP) fullsnake.direct = DOWN; break;
  }
}

// Show snake
void CSnake::paintSnake(){
  list< CPoint >::iterator i = fullsnake.body.begin();
  for(;i != fullsnake.body.end(); i++){
      gotoyx(i->y + geom.topleft.y, i->x + geom.topleft.x);
      printc('x');
  }
  gotoyx(fullsnake.body.begin()->y + geom.topleft.y, fullsnake.body.begin()->x + geom.topleft.x);
  printc('*');
}

// Move snake and correct if he gets out from the bounds
void CSnake::adjustSnakeMovement(int direction){
  switch(direction){
    case UP:
      fullsnake.body.front() +=  CPoint(0, -1); // Move him
      if(fullsnake.body.front().y == 0) fullsnake.body.front().y = geom.size.y - 2; // Every 'if' checks if snake didn't run away from game
      break;
    case DOWN:
      fullsnake.body.front() +=  CPoint(0, 1);
      if(fullsnake.body.front().y == geom.size.y - 1) fullsnake.body.front().y = 1;
      break;
    case RIGHT:
      fullsnake.body.front() +=  CPoint(1, 0);
      if(fullsnake.body.front().x == geom.size.x - 1) fullsnake.body.front().x = 1;
      break;
    case LEFT:
      fullsnake.body.front() +=  CPoint(-1, 0);
      if(fullsnake.body.front().x == 0) fullsnake.body.front().x = geom.size.x - 2;
      break;
  }
}

// Print scoreboard
void CSnake::level(){
    gotoyx(geom.topleft.y - 1,geom.topleft.x + 15);
    printl("|LEVEL : %d|", points);
}

// Check if snake collide with given point *MAGIC*
bool CSnake::collision(CPoint &it){
  list< CPoint >::iterator i = fullsnake.body.begin();
  for(;i != fullsnake.body.end(); i++){
    if(i->x == it.x && i->y == it.y) return true;
  }
  return false;
}


void CSnake::makefruit(){
  if(!fruitexist){
    srand(time(0));
    do{
      fruitxy.x = rand() % (geom.size.x-3) + 1;
      fruitxy.y = rand() % (geom.size.y-3) + 1;
    } while(collision(fruitxy));
    fruitexist = true;
  }
  gotoyx(fruitxy.y + geom.topleft.y, fruitxy.x + geom.topleft.x);
  printc('o');
}

// Calculate score and adjust movement
void CSnake::score(){
  if(collision(fruitxy)){
    fruitexist = false;
    points++;
    speed -= 13;
    timeout(speed);
  }
  else fullsnake.body.pop_back();
}

// One move of our Snake
void CSnake::move(){
  fullsnake.body.push_front(fullsnake.body.front());
  adjustSnakeMovement(fullsnake.direct);
  score();
  CPoint x = fullsnake.body.front();
  fullsnake.body.pop_front();
  if(collision(x)) lost = true;
  fullsnake.body.push_front(x);
}


void CSnake::paint(){
  CFramedWindow::paint();
  makefruit();
  level();
  finalScore();
  paintSnake();
}

bool CSnake::handleEvent(int key) {
  if(!lost){
    changeSnakeDirection(key);
    move();
  }
  return true;
}
