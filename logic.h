#ifndef _LOGIC_H
#define _LOGIC_H

	#define TRUE 1
	#define FALSE 0
	
	typedef SDL_Rect Fruit;
	typedef SDL_Rect Snake;
	typedef int boolean;
	
	enum squareColor {RED , GREEN , YELLOW};
	enum direction {UP,DOWN,RIGHT,LEFT};
	
	
	/* Signature of function implemented in logic.c */
	
	Fruit randFruitPostion(void);
	void squareDrawing(SDL_Renderer *,SDL_Rect,const enum squareColor);
	void movingHeadSnake(SDL_Event  ,enum direction *,Snake*,Snake*, int);
	void updatePosition(SDL_Renderer *,Snake*,Snake,int );
	enum direction whereToAdd(SDL_Rect *,int );
	boolean isFruitOnSnake(Snake *,Fruit,int);
	boolean isSnakeDied(Snake *,int );
	void comeBack(Snake *);
	

#endif
