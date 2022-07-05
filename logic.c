#include <SDL2/SDL.h>
#include "logic.h"

Fruit randFruitPostion(void)
{
	Fruit position;
	
	position.x = rand() % 550;
	position.y = rand() % 550;
	
	return position;
	
	
}
void squareDrawing(SDL_Renderer *renderer,SDL_Rect rect,const enum squareColor color )
{
	if(color == RED)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	if(color == GREEN)
		SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);
	if(color == YELLOW)
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);


	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	
	
	
}


void movingHeadSnake(SDL_Event event ,enum direction *dir,Snake *headSnake,Snake* previous,int gap)
{
		
		previous->x = headSnake->x;
		previous->y = headSnake->y;
		
		if( ( event.key.keysym.sym == SDLK_UP && *dir != DOWN ) || *dir == UP )	
	   	{
	   		*dir = UP; 
	   		headSnake->y -= (20 + gap);
	   		
	   	}
	   	if( ( event.key.keysym.sym == SDLK_DOWN && *dir != UP) || *dir == DOWN )
	   	{
	   		*dir = DOWN;
	   		headSnake->y += 20 + gap; 
	   		
	   	}
	   	if( ( event.key.keysym.sym == SDLK_RIGHT && *dir != LEFT )  || *dir == RIGHT)
	   	{
	   		*dir = RIGHT;
	   		headSnake->x += 20 + gap; 
	   		
	   		
	   	}
	   	if( ( event.key.keysym.sym == SDLK_LEFT && *dir != RIGHT ) || *dir == LEFT )
	   	{
	   		*dir = LEFT;
	   		headSnake->x -= (20 + gap); 

	   	}



}

void updatePosition(SDL_Renderer *renderer,Snake *snake,Snake previous,int lenSnake)
{
	
	for(int len = 1; len < lenSnake ;len++)
	{
		Snake tmp  = snake[len];
		
   		snake[len] = previous;
   		 
   		previous   = tmp; 
	}

}

enum direction whereToAdd(SDL_Rect *snake,int lenSnake)
{
	Snake tmpSnake = snake[ lenSnake - 1 ];
	
	int gap = 2;
	
	tmpSnake.x  +=  (tmpSnake.w + ( 2*gap ));
	if( SDL_HasIntersection( &tmpSnake , &snake[ lenSnake - 2]) )
		return LEFT;
	
	tmpSnake = snake[ lenSnake - 1 ];
	tmpSnake.x  -=  (tmpSnake.w + ( 2*gap ));
	if( SDL_HasIntersection( &tmpSnake , &snake[ lenSnake - 2]) )
		return RIGHT;
		
	tmpSnake = snake[ lenSnake - 1 ];
	tmpSnake.y  +=  (tmpSnake.h + ( 2*gap ));
	if( SDL_HasIntersection( &tmpSnake , &snake[ lenSnake - 2]) )
		return UP;
	
	tmpSnake = snake[ lenSnake - 1 ];
	tmpSnake.y  -=  (tmpSnake.h + ( 2*gap ));
	if( SDL_HasIntersection( &tmpSnake , &snake[ lenSnake - 2]) )
		return DOWN;


}
boolean isFruitOnSnake(Snake *snake,Fruit fruit,int lenSnake)
{
	for(int len = 0 ; len < lenSnake ; len++ )
	{
		if( SDL_HasIntersection( &snake[len] , &fruit ) )
			return TRUE;
	}
	return FALSE;

}
boolean isSnakeDied(Snake *snake,int lenSnake)
{
	for(int len = 1 ; len < lenSnake ; len++ )
	{
		if( SDL_HasIntersection( &snake[0] , &snake[len] ) )
			return TRUE;
		
	}
	return FALSE;

}
void comeBack(Snake *snake)
{

	if(snake[0].x >= 600 )
		snake[0].x = 0;
	
	if( ( snake[0].x + snake[0].w ) <= 0 )
		snake[0].x = 600;
	
	if( snake[0].y   >= 600 )
		snake[0].y = 0;
	
	if( ( snake[0].y + snake[0].h ) <= 0 )
		snake[0].y = 600;
	

}

