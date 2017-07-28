#include "Event.h"


GE161::Event::Event()
{
}

GE161::Event::Event(int eventType, int* eventData) :   /// hw 8
type(eventType),
userEventData(eventData),
mouseButton(0),
mouseClicks(0),
x(0),
y(0)
{
}


GE161::Event::Event(SDL_Event& e) :
sdl_event(e),
key(""),
mouseButton(0),
mouseClicks(0),
x(0),
y(0)
{
	type = e.type;  // copy SDL type
	if (type == KEY_UP || type == KEY_DOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_0: key = "0"; break;
		case SDLK_1: key = "1"; break;
		case SDLK_2: key = "2"; break;
		case SDLK_3: key = "3"; break;
		case SDLK_4: key = "4"; break;
		case SDLK_5: key = "5"; break;
		case SDLK_6: key = "6"; break;
		case SDLK_7: key = "7"; break;
		case SDLK_8: key = "8"; break;
		case SDLK_9: key = "9"; break;
		case SDLK_a: key = "A"; break;
		case SDLK_b: key = "B"; break;
		case SDLK_c: key = "C"; break;
		case SDLK_d: key = "D"; break;
		case SDLK_e: key = "E"; break;
		case SDLK_f: key = "F"; break;
		case SDLK_g: key = "G"; break;
		case SDLK_h: key = "H"; break;
		case SDLK_i: key = "I"; break;
		case SDLK_j: key = "J"; break;
		case SDLK_k: key = "K"; break;
		case SDLK_l: key = "L"; break;
		case SDLK_m: key = "M"; break;
		case SDLK_n: key = "N"; break;
		case SDLK_o: key = "O"; break;
		case SDLK_p: key = "P"; break;
		case SDLK_q: key = "Q"; break;
		case SDLK_r: key = "R"; break;
		case SDLK_s: key = "S"; break;
		case SDLK_t: key = "T"; break;
		case SDLK_u: key = "U"; break;
		case SDLK_v: key = "V"; break;
		case SDLK_w: key = "W"; break;
		case SDLK_x: key = "X"; break;
		case SDLK_y: key = "Y"; break;
		case SDLK_z: key = "Z"; break;
		case SDLK_SPACE: key = " "; break;
		case SDLK_DOWN: key = "DOWN"; break;
		case SDLK_LEFT: key = "LEFT"; break;
		case SDLK_RIGHT: key = "RIGHT"; break;
		case SDLK_UP: key = "UP"; break;
		case SDLK_BACKSPACE: key = "BACKSPACE"; break;
		// many more symbols need to be accounted for.
		// see https://wiki.libsdl.org/SDL_Keycode
		}
		return;
	}
	if (type == MOUSE_BUTTONUP || type == MOUSE_BUTTONDOWN)
	{
		mouseButton = e.button.button;
		mouseClicks = e.button.clicks;
		x = e.button.x;
		y = e.button.y;
		return;
	}
	if (type == MOUSE_MOTION)
	{
		x = e.motion.x;
		y = e.motion.y;
		return;
	}
}


GE161::Event::~Event()
{
	delete userEventData;
}
