#include <iostream>
#include <SDL.h>

bool HandleEvent(SDL_Event *Event)
{
  bool ShouldQuit = false;

  switch(Event->type)
    {
    case SDL_QUIT:
      {
	printf("SDL_QUIT\n");
	ShouldQuit = true;
      } break;

    case SDL_WINDOWEVENT:
      {
	switch(Event->window.event)
	  {
	  case SDL_WINDOWEVENT_RESIZED:
	    {
	      printf("SDL_WINDOWEVENT_RESIZED (%d, %d)\n", Event->window.data1, Event -> window.data2);
	    }break;
	  case SDL_WINDOWEVENT_EXPOSED:
	    {
	      //get the window and renderer from the event
	      SDL_Window *Window = SDL_GetWindowFromID(Event->window.windowID);
	      SDL_Renderer *Renderer = SDL_GetRenderer(Window);
	      static bool IsWhite = true;

	      //switch from black and white
	      if(IsWhite==true)
		{
		  SDL_SetRenderDrawColor(Renderer, 255,255,255,255);
		  IsWhite=false;
		}
	      else
		{
		  SDL_SetRenderDrawColor(Renderer,0,0,0,255);
		  IsWhite = true;
		}

	      // clear and rerender
	      SDL_RenderClear(Renderer);
	      SDL_RenderPresent(Renderer);
	      
	    }break;
	  }
      }break;
      

    }


  return(ShouldQuit);
}

int main(int argc, char *argv[]){

  //DL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Handmade Hero", "This is Handmade Hero",0);


  if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      //TODOL SDL_INIT didn't work
    }
  
  SDL_Window *Window;

  Window = SDL_CreateWindow("Handmade Hero",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    640,
			    480,
			    SDL_WINDOW_RESIZABLE);


  if(Window)
    {
      //create a renderer for our window
      SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, 0);

      if(Renderer)
	{
	  for(;;)
	    {
	      SDL_Event Event;
	      SDL_WaitEvent(&Event);
	      if(HandleEvent(&Event)){
		break;
	      }
	    }
	  SDL_Quit();
	}
    }
  
  return(0);
}
