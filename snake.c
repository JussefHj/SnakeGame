#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "logic.h"


#define WIN_WIDTH  600
#define WIN_HEIGHT 600

int main(int argc,char **argv)
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	int status = EXIT_FAILURE;
	
	
	if( SDL_Init(SDL_INIT_VIDEO) )
	{
		fprintf(stderr,"Erreur SDL_Init : %s \n",SDL_GetError());
		goto Quit;
	
	}
	
	window = SDL_CreateWindow("SNAKE_Window", SDL_WINDOWPOS_CENTERED ,  SDL_WINDOWPOS_CENTERED ,WIN_WIDTH,WIN_HEIGHT,SDL_WINDOW_SHOWN);
	
	if(window == NULL)
	{
		fprintf(stderr,"Erreur SDL_CreateWindow : %s \n",SDL_GetError());
		goto Quit;
	
	}
	renderer = SDL_CreateRenderer( window, -1 ,SDL_RENDERER_ACCELERATED);
	
	if( renderer == NULL)
	{
		fprintf(stderr,"Erreur SDL_CreateRenderer : %s \n",SDL_GetError());
		goto Quit;
	
	}
	
	

	SDL_Event event;
	
	Fruit fruit = {300,300,20,20};
	
	Snake snake[90];
	snake[0].x = snake[0].y = 200;
	snake[0].w = snake[0].h = 20;
	
	Snake previous = snake[0];
	
	
	int lenSnake = 1,gap = 2;
	
	enum direction dir = -1;
	
	while( 1 )
	{
		SDL_PollEvent(&event);
		//SDL_WaitEvent(&event);
	   	
	   	if(  event.type == SDL_QUIT ) 
	   		break;
	   		
	   	
	   	if( SDL_HasIntersection( &snake[0] , &fruit ) )  
	   	{
	   		//Random fruit position
	   		do
	   		{
	   			fruit.x = randFruitPostion().x;
		   		fruit.y = randFruitPostion().y;
	   		}while( isFruitOnSnake(snake,fruit,lenSnake) );
		   	
		   	
		   	snake[ lenSnake ] = snake[ lenSnake - 1 ];
		   	if(lenSnake == 1)
		   	{
		   		
			   	if( dir == UP)
			   		snake[ lenSnake ].y = snake[ lenSnake - 1 ].y +  snake[ lenSnake - 1 ].h + gap;
			   		
			   	if( dir == DOWN)
			   		snake[ lenSnake ].y = snake[ lenSnake - 1 ].y -  snake[ lenSnake - 1 ].h - gap;
			   	
			   	if( dir == RIGHT)
			   		snake[ lenSnake ].x = snake[ lenSnake - 1 ].x -  snake[ lenSnake - 1 ].w - gap;
			   		
			   	if( dir == LEFT)
			   		snake[ lenSnake ].x = snake[ lenSnake - 1 ].x +  snake[ lenSnake - 1 ].w + gap ;
		   	
		   	}
		   	else
		   	{
		   		if( whereToAdd( snake, lenSnake ) == UP )
		   			snake[ lenSnake ].y = snake[ lenSnake - 1 ].y -  snake[ lenSnake - 1 ].h - gap;
		   		
			   	if( whereToAdd( snake , lenSnake ) == DOWN )
			   		snake[ lenSnake ].y = snake[ lenSnake - 1 ].y +  snake[ lenSnake - 1 ].h + gap;
			   	
			   	if( whereToAdd( snake , lenSnake ) == RIGHT )
			   		snake[ lenSnake ].x = snake[ lenSnake - 1 ].x +  snake[ lenSnake - 1 ].w + gap;
			   		
			   	if( whereToAdd( snake , lenSnake ) == LEFT )
			   		snake[ lenSnake ].x = snake[ lenSnake - 1 ].x -  snake[ lenSnake - 1 ].w - gap;
		   	
		   	}
		   	
		   	lenSnake++;
		   		
	   	}
	   	
	   	//Drawing the head
   		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRects(renderer,snake,1);
		SDL_RenderDrawRects(renderer,snake,1);
		
		//Drawing the body
		if( lenSnake > 1)
		{
   			SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);
			SDL_RenderFillRects(renderer,snake + 1,lenSnake - 1);
			SDL_RenderDrawRects(renderer,snake + 1,lenSnake - 1);
		}
		SDL_RenderPresent(renderer);
	   	
	   	
	   	//Died whe the snake eat him self
		if( isSnakeDied(snake,lenSnake) )
			break;
			
				
	   	squareDrawing(renderer,fruit,YELLOW);
	   	
	   	movingHeadSnake(event ,&dir,&snake[0],&previous,gap);
	   	
	   	//in case snake be out the screen
	   	comeBack(snake);
	   	
	   	updatePosition(renderer,snake,previous,lenSnake);
	   	
	   	
	   	
	   	//Reset the window
	   	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	   	SDL_RenderClear(renderer);
	   	SDL_Delay(100);
	   	
	
	}

    
	status = EXIT_SUCCESS;
	Quit:
		if( renderer != NULL)
			SDL_DestroyRenderer(renderer);
		
		if( window != NULL)
			SDL_DestroyWindow(window);
		
		SDL_Quit();
		return status;
		
}
