#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"

#include "SDL/include/SDL.h"
#include "ModuleInput.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

#include "ModuleWindow.h"

enum class Main_States
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char* argv[])
{
	ReportMemoryLeaks();

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint64 frameStart;
	int frameTime;

	bool fullScreen = false;

	int main_return = EXIT_FAILURE;
	Main_States state = Main_States::MAIN_CREATION;

	while (state != Main_States::MAIN_EXIT)
	{
		

		switch (state)
		{
			case Main_States::MAIN_CREATION:
			{
				LOG("Application Creation --------------\n");
				App = new Application();
				state = Main_States::MAIN_START;
			}	break;

			case Main_States::MAIN_START:
			{
				LOG("Application Start --------------\n");
				if(App->Init() == false)
				{
					LOG("Application Init exits with error -----\n");
					state = Main_States::MAIN_EXIT;
				}
				else
				{
					state = Main_States::MAIN_UPDATE;
				}
			}	break;

			case Main_States::MAIN_UPDATE:
			{
				frameStart = SDL_GetTicks();

				Update_Status status = App->Update();

				frameTime = SDL_GetTicks() - frameStart;

				if (frameDelay > frameTime)
				{
					SDL_Delay(frameDelay - frameTime);
				}

				if (App->input->keys[SDL_SCANCODE_F11] == Key_State::KEY_DOWN)
				{
					fullScreen = !fullScreen;
				}

				if (fullScreen == false)
				{
					SDL_SetWindowFullscreen(App->window->window, 0);
				}
				else if (fullScreen == true)
				{
					SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN);
				}

				if (status == Update_Status::UPDATE_ERROR)
				{
					LOG("Application Update exits with error -----\n");
					state = Main_States::MAIN_EXIT;
				}
				else if (status == Update_Status::UPDATE_STOP)
				{
					state = Main_States::MAIN_FINISH;
				}
				else if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
				{
					state = Main_States::MAIN_FINISH;
				}
			}	break;

			case Main_States::MAIN_FINISH:
			{
				LOG("Application Finish --------------\n");
				if (App->CleanUp() == true)
				{
					main_return = EXIT_SUCCESS;
				}
				else
				{
					LOG("Application CleanUp exits with error -----\n");
				}
				state = Main_States::MAIN_EXIT;
			}
		}

		
	}

	LOG("\nBye :)\n");

	delete App;

	return main_return;
}