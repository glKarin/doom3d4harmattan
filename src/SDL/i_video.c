/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2006 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *  DOOM graphics stuff for SDL
 *
 *-----------------------------------------------------------------------------
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "SDL.h"

#include "m_argv.h"
#include "doomstat.h"
#include "doomdef.h"
#include "doomtype.h"
#include "v_video.h"
#include "r_draw.h"
#include "d_main.h"
#include "d_event.h"
#include "i_joy.h"
#include "i_video.h"
#include "z_zone.h"
#include "s_sound.h"
#include "sounds.h"
#include "w_wad.h"
#include "st_stuff.h"
#include "lprintf.h"


int gl_colorbuffer_bits=16;
int gl_depthbuffer_bits=16;

extern void M_QuitDOOM(int choice);
#ifdef DISABLE_DOUBLEBUFFER
int use_doublebuffer = 0;
#else
int use_doublebuffer = 1; // Included not to break m_misc, but not relevant to SDL
#endif
int use_fullscreen;
int desired_fullscreen;
static SDL_Surface *screen;

#ifndef _NON_HARMATTAN
//god mode - iddqd 
//ammo & keys - idkfa
//clip idspispopd
#include "m_cheat.h"

#define VB_W 64
#define VB_S 20

#define UPX 192
#define DOWNX 320
#define LEFTX 128
#define RIGHTX 256
#define OPENX 256
#define ESCAPEX 64
#define FIREX 128
#define RUNX 320
#define WEAPONTOGGLEX 192
#define GODMODEX 320
#define KAMODEX 448
#define CLIPMODEX 384
#define YX 64
#define NX 0
#define WEAPON1X 384
#define WEAPON2X 448
#define WEAPON3X 448
#define WEAPON4X 64
#define WEAPON5X 192
#define WEAPON6X 128
#define WEAPON7X 0
#define WEAPON8X 64
#define WEAPON9X 384
#define MOVELEFTX 128
#define MOVERIGHTX 256
#define ESCAPEX 64
#define FORWARDX 192
#define BACKWARDX 320
#define TURNLEFTX 128
#define TURNRIGHTX 256
#define MENUX 0
#define ENTERX 320
#define BACKSPACEX 256
#define PAUSEX 256

#define UPY_R 0
#define DOWNY_R 0
#define LEFTY_R 0
#define RIGHTY_R 0
#define OPENY_R 128
#define FIREY_R 128
#define ESCAPEY_R 0
#define RUNY_R 256
#define WEAPONTOGGLEY_R 128
#define GODMODEY_R 128
#define KAMODEY_R 128
#define CLIPMODEY_R 128
#define YY_R 128
#define NY_R 128
#define WEAPON1Y_R 0
#define WEAPON2Y_R 0
#define WEAPON3Y_R 256
#define WEAPON4Y_R 256
#define WEAPON5Y_R 256
#define WEAPON6Y_R 256
#define WEAPON7Y_R 128
#define WEAPON8Y_R 128
#define WEAPON9Y_R 256
#define MOVELEFTY_R 0
#define MOVERIGHTY_R 0
#define MENUY_R 0
#define FORWARDY_R 0
#define BACKWARDY_R 0
#define TURNLEFTY_R 0
#define TURNRIGHTY_R 0
#define ENTERY_R 256
#define BACKSPACEY_R 256
#define PAUSEY_R 256

#define UPY_P 64
#define DOWNY_P 64
#define LEFTY_P 64
#define RIGHTY_P 64
#define OPENY_P 192
#define FIREY_P 192
#define ESCAPEY_P 64
#define RUNY_P 320
#define WEAPONTOGGLEY_P 192
#define GODMODEY_P 192
#define KAMODEY_P 192
#define CLIPMODEY_P 192
#define CHEATY_P 64
#define YY_P 192
#define NY_P 192
#define WEAPON1Y_P 64
#define WEAPON2Y_P 64
#define WEAPON3Y_P 320
#define WEAPON4Y_P 320
#define WEAPON5Y_P 320
#define WEAPON6Y_P 320
#define WEAPON7Y_P 192
#define WEAPON8Y_P 192
#define WEAPON9Y_P 320
#define MOVELEFTY_P 64
#define MOVERIGHTY_P 64
#define FORWARDY_P 64
#define BACKWARDY_P 64
#define TURNLEFTY_P 64
#define TURNRIGHTY_P 64
#define MENUY_P 64
#define ENTERY_P 320
#define BACKSPACEY_P 320
#define PAUSEY_P 320

typedef enum
{
	//for menu
	YesFunction = 0,
	NoFunction,
	UpFunction,
	DownFunction,
	LeftFunction,
	RightFunction,
	EnterFunction,
	EscapeFunction,
	BackspaceFunction,
	//for menu & game
	PauseFunction,
	//for game
	ForwardFunction,
	BackwardFunction,
	MoveLeftFunction,
	MoveRightFunction,
	FireFunction,
	MenuFunction,
	OpenFunction,
	RunFunction,
	WeaponToggleFunction,
	Weapon1Function,
	Weapon2Function,
	Weapon3Function,
	Weapon4Function,
	Weapon5Function,
	Weapon6Function,
	Weapon7Function,
	Weapon8Function,
	Weapon9Function,
	TurnLeftFunction,
	TurnRightFunction,
	//for cheat
	GodModeFunction,
	KAModeFunction,
	ClipModeFunction,
	TotalFunction
} ButtonFunction;

#include <SDL/SDL_image.h>

#include "g_game.h"

#define VB_FILE "/usr/share/prboom+freedoom/anna_buttons.png"

static SDL_Surface *vb_surface = NULL;

static SDL_Rect sprite_rects[TotalFunction] = {
	//for menu
	{
		YX,
		YY_R,
		VB_W, VB_W
	},//yes

	{
		NX,
		NY_R,
		VB_W, VB_W
	},//no

	{
		UPX,
		UPY_R,
		VB_W, VB_W
	},//up

	{
		DOWNX,
		DOWNY_R,
		VB_W, VB_W
	},//down

	{
		LEFTX,
		LEFTY_R,
		VB_W, VB_W
	},//left

	{
		RIGHTX,
		RIGHTY_R,
		VB_W, VB_W
	},//right

	{
		ENTERX,
		ENTERY_R,
		VB_W, VB_W
	},//enter

	{
		ESCAPEX,
		ESCAPEY_R,
		VB_W, VB_W
	},//escape

	{
		BACKSPACEX,
		BACKSPACEY_R,
		VB_W, VB_W
	},//backsapce

	//for game & menu
	{
		PAUSEX,
		PAUSEY_R,
		VB_W, VB_W
	},//pause

	//for game
	{
		FORWARDX,
		FORWARDY_R,
		VB_W, VB_W
	},//forward

	{
		BACKWARDX,
		BACKWARDY_R,
		VB_W, VB_W
	},//backward

	{
		MOVELEFTX,
		MOVELEFTY_R,
		VB_W, VB_W
	},//move left

	{
		MOVERIGHTX,
		MOVERIGHTY_R,
		VB_W, VB_W
	},//move right

	{
		FIREX,
		FIREY_R,
		VB_W, VB_W
	},//fire

	{
		MENUX,
		MENUY_R,
		VB_W, VB_W
	},//menu

	{
		OPENX,
		OPENY_R,
		VB_W, VB_W
	},//open

	{
		RUNX,
		RUNY_R,
		VB_W, VB_W
	},//run

	{
		WEAPONTOGGLEX,
		WEAPONTOGGLEY_R,
		VB_W, VB_W
	},

	{
		WEAPON1X,
		WEAPON1Y_R,
		VB_W, VB_W
	},

	{
		WEAPON2X,
		WEAPON2Y_R,
		VB_W, VB_W
	},

	{
		WEAPON3X,
		WEAPON3Y_R,
		VB_W, VB_W
	},

	{
		WEAPON4X,
		WEAPON4Y_R,
		VB_W, VB_W
	},

	{
		WEAPON5X,
		WEAPON5Y_R,
		VB_W, VB_W
	},

	{
		WEAPON6X,
		WEAPON6Y_R,
		VB_W, VB_W
	},

	{
		WEAPON7X,
		WEAPON7Y_R,
		VB_W, VB_W
	},

	{
		WEAPON8X,
		WEAPON8Y_R,
		VB_W, VB_W
	},

	{
		WEAPON9X,
		WEAPON9Y_R,
		VB_W, VB_W
	},

	{
		TURNLEFTX,
		TURNLEFTY_R,
		VB_W, VB_W
	},//turn left

	{
		TURNRIGHTX,
		TURNRIGHTY_R,
		VB_W, VB_W
	},//turn right

	//for cheat
	{
		GODMODEX,
		GODMODEY_R,
		VB_W, VB_W
	},//god mode

	{
		KAMODEX,
		KAMODEY_R,
		VB_W, VB_W
	},//KA mode

	{
		CLIPMODEX,
		CLIPMODEY_R,
		VB_W, VB_W
	}//clip mode

};

static SDL_Rect button_sdlrects[TotalFunction] = {
	//for menu
	{
		N950_W / 2 - VB_S - VB_W,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//yes

	{
		N950_W / 2 + VB_S,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//no

	{
		VB_S * 2 + VB_W,
		N950_H - VB_S * 3 - VB_W * 3,
		VB_W, VB_W
	},//up

	{
		VB_S * 2 + VB_W,
		N950_H - VB_S - VB_W,
		VB_W, VB_W
	},//down

	{
		VB_S,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//left

	{
		VB_S * 3 + VB_W * 2,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//right

	{
		N950_W - VB_S * 2 - VB_W * 2,
		N950_H - VB_S * 3 - VB_W * 3,
		VB_W, VB_W
	},//enter

	{
		N950_W - VB_W,
		0,
		VB_W, VB_W
	},//escape

	{
		N950_W - VB_S * 2 - VB_W * 2,
		N950_H - VB_S - VB_W,
		VB_W, VB_W
	},//backspace

	{
		0,
		0,
		VB_W, VB_W
	},//pause

	//for game
	{
		VB_S * 2 + VB_W,
		N950_H - VB_S * 3 - VB_W * 3,
		VB_W, VB_W
	},//forward

	{
		VB_S * 2 + VB_W,
		N950_H - VB_S - VB_W,
		VB_W, VB_W
	},//backward

	{
		VB_S,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//move left

	{
		VB_S * 3 + VB_W * 2,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//move right

	{
		N950_W - VB_S * 2 - VB_W * 2,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//fire

	{
		N950_W - VB_W,
		0,
		VB_W, VB_W
	},//menu

	{
		N950_W - VB_S * 2 - VB_W * 2,
		N950_H - VB_S * 3 - VB_W * 3,
		VB_W, VB_W
	},//open

	{
		N950_W - VB_W,
		VB_S * 2 + VB_W * 2,
		VB_W, VB_W
	},//run

	{
		N950_W - VB_S * 2 - VB_W * 2,
		N950_H - VB_S - VB_W,
		VB_W, VB_W
	},//weapon toggle

	{
		N950_W / 2 - VB_W / 2 * 9 - VB_S * 2,
		VB_S,
		VB_W, VB_W
	},//1

	{
		N950_W / 2 - VB_W / 2 * 7 - VB_S / 2 * 3,
		VB_S,
		VB_W, VB_W
	},//2

	{
		N950_W / 2 - VB_W / 2 * 5 - VB_S,
		VB_S,
		VB_W, VB_W
	},//3

	{
		N950_W / 2 - VB_W / 2 * 3 - VB_S / 2,
		VB_S,
		VB_W, VB_W
	},//4

	{
		N950_W / 2 - VB_W / 2,
		VB_S,
		VB_W, VB_W
	},//5

	{
		N950_W / 2 + VB_W / 2 + VB_S / 2,
		VB_S,
		VB_W, VB_W
	},//6

	{
		N950_W / 2 + VB_W / 2 * 3 + VB_S,
		VB_S,
		VB_W, VB_W
	},//7

	{
		N950_W / 2 + VB_W / 2 * 5 + VB_S / 2 * 3,
		VB_S,
		VB_W, VB_W
	},//8

	{
		N950_W / 2 + VB_W / 2 * 7 + VB_S * 2,
		VB_S,
		VB_W, VB_W
	},//9

	{
		N950_W - VB_S * 3 - VB_W * 3,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//turn left

	{
		N950_W - VB_S - VB_W,
		N950_H - VB_S * 2 - VB_W * 2,
		VB_W, VB_W
	},//turn right

	{
		0,
		VB_W + VB_S,
		VB_W, VB_W
	},//god mode

	{
		0,
		VB_W * 2 + VB_S * 2,
		VB_W, VB_W
	},//KA mode

	{
		N950_W - VB_W,
		VB_W + VB_S,
		VB_W, VB_W
	}//clip mode
};

inline void KARIN_DrawVirtualButtons(void)
{
	ButtonFunction start, end;
	//if(menuactive || (gamestate != GS_LEVEL && gamestate != GS_INTERMISSION && gamestate != GS_FINALE) || paused || demoplayback )
	if(menuactive || gamestate == GS_DEMOSCREEN || paused || demoplayback )
	{
		start = YesFunction;
		end = ForwardFunction;
	}
	else
	{
		start = PauseFunction;
		end = TotalFunction;
	}
	unsigned int i;
	for(i = start; i < end; i++)
		SDL_BlitSurface(vb_surface, &sprite_rects[i], screen, &button_sdlrects[i]);
}

typedef struct{
	int x_1;
	int y_1;
	int x_2;
	int y_2;
}KARIN_Rect;

typedef struct{
	KARIN_Rect rect;
	ButtonFunction index;
	int pressedY;
	int releasedY;
	const int * const function1; //for game
	//const int * const function2; //for menu
	//const int * const function3; //others...
} KARIN_VirtualButton;

static const int key_y = SDLK_y; 
static const int key_n = SDLK_n; 

#define GODMODE_INDEX 2
#define KAMODE_INDEX 3
#define CLIPMODE_INDEX 5

static const int cheat_godmode = GODMODE_INDEX;
static const int cheat_kamode = KAMODE_INDEX;
static const int cheat_clipmode = CLIPMODE_INDEX;

static KARIN_VirtualButton button_rects[TotalFunction] = {
	//for menu
	{
		{
			N950_W / 2 - VB_S - VB_W,
			N950_H - VB_S * 2 - VB_W * 2,
			N950_W / 2 - VB_S,
			N950_H - VB_S * 2 - VB_W
		},
		YesFunction,
		YY_P,
		YY_R,
		&key_y//SDLK_y
	},

	{
		{
			N950_W / 2 + VB_S,
			N950_H - VB_S * 2 - VB_W * 2,
			N950_W / 2 + VB_S + VB_W,
			N950_H - VB_S * 2 - VB_W
		},
		NoFunction,
		NY_P,
		NY_R,
		&key_n//SDLK_n
	},

	{
		{
			VB_S,
			N950_H - VB_S * 3 - VB_W * 3,
			VB_S * 3 + VB_W * 3,
			N950_H - VB_S * 3 - VB_W * 2
		},
		UpFunction,
		UPY_P,
		UPY_R,
		&key_menu_up
	},

	{
		{
			VB_S,
			N950_H - VB_S - VB_W,
			VB_S * 3 + VB_W * 3,
			N950_H - VB_S
		},
		DownFunction,
		DOWNY_P,
		DOWNY_R,
		&key_menu_down
	},

	{
		{
			VB_S,
			N950_H - VB_S * 3 - VB_W * 3,
			VB_S + VB_W,
			N950_H - VB_S
		},
		LeftFunction,
		LEFTY_P,
		LEFTY_R,
		&key_menu_left
	},

	{
		{
			VB_S * 3 + VB_W * 2,
			N950_H - VB_S * 3 - VB_W * 3,
			VB_S * 3 + VB_W * 3,
			N950_H - VB_S
		},
		RightFunction,
		RIGHTY_P,
		RIGHTY_R,
		&key_menu_right
	},

	{
		{
			N950_W - VB_S * 2 - VB_W * 2,
			N950_H - VB_S * 3 - VB_W * 3,
			N950_W - VB_S * 2 - VB_W,
			N950_H - VB_S * 3 - VB_W * 2
		},
		EnterFunction,
		ENTERY_P,
		ENTERY_R,
		&key_menu_enter
	},

	{
		{
			N950_W - VB_W,
			0,
			N950_W,
			VB_W
		},
		EscapeFunction,
		ESCAPEY_P,
		ESCAPEY_R,
		&key_menu_escape
	},

	{
		{
			N950_W - VB_S * 2 - VB_W * 2,
			N950_H - VB_S - VB_W,
			N950_W - VB_S * 2 - VB_W,
			N950_H - VB_S
		},
		BackspaceFunction,
		BACKSPACEY_P,
		BACKSPACEY_R,
		&key_menu_backspace
	},

	{
		{
			0,
			0,
			VB_W,
			VB_W
		},
		PauseFunction,
		PAUSEY_P,
		PAUSEY_R,
		&key_pause
	},

	//for game
	{
		{
			VB_S,
			N950_H - VB_S * 3 - VB_W * 3,
			VB_S * 3 + VB_W * 3,
			N950_H - VB_S * 3 - VB_W * 2
		},
		ForwardFunction,
		FORWARDY_P,
		FORWARDY_R,
		&key_up
	},

	{
		{
			VB_S,
			N950_H - VB_S - VB_W,
			VB_S * 3 + VB_W * 3,
			N950_H - VB_S
		},
		BackwardFunction,
		BACKWARDY_P,
		BACKWARDY_R,
		&key_down
	},

	{
		{
			VB_S,
			N950_H - VB_S * 3 - VB_W * 3,
			VB_S + VB_W,
			N950_H - VB_S
		},
		MoveLeftFunction,
		MOVELEFTY_P,
		MOVELEFTY_R,
		&key_strafeleft
	},

	{
		{
			VB_S * 3 + VB_W * 2,
			N950_H - VB_S * 3 - VB_W * 3,
			VB_S * 3 + VB_W * 3,
			N950_H - VB_S
		},
		MoveRightFunction,
		MOVERIGHTY_P,
		MOVERIGHTY_R,
		&key_straferight
	},

	{
		{
			N950_W - VB_S * 2 - VB_W * 2,
			N950_H - VB_S * 2 - VB_W * 2,
			N950_W - VB_S * 2 - VB_W,
			N950_H - VB_S * 2 - VB_W
		},
		FireFunction,
		FIREY_P,
		FIREY_R,
		&key_fire
	},

	{
		{
			N950_W - VB_W,
			0,
			N950_W,
			VB_W
		},
		MenuFunction,
		MENUY_P,
		MENUY_R,
		&key_setup
	},

	{
		{
			N950_W - VB_S * 2 - VB_W * 2,
			N950_H - VB_S * 3 - VB_W * 3,
			N950_W - VB_S * 2 - VB_W,
			N950_H - VB_S * 3 - VB_W * 2
		},
		OpenFunction,
		OPENY_P,
		OPENY_R,
		&key_use
	},

	{
		{
			N950_W - VB_W,
			VB_S * 2 + VB_W * 2,
			N950_W,
			VB_S * 2 + VB_W * 3
		},
		RunFunction,
		RUNY_P,
		RUNY_R,
		&key_autorun
	},

	{
		{
			N950_W - VB_S * 2 - VB_W * 2,
			N950_H - VB_S - VB_W,
			N950_W - VB_S * 2 - VB_W,
			N950_H - VB_S
		},
		WeaponToggleFunction,
		WEAPONTOGGLEY_P,
		WEAPONTOGGLEY_R,
		&key_weapontoggle
	},

	{
		{
			N950_W / 2 - VB_W / 2 * 9 - VB_S * 2,
			VB_S,
			N950_W / 2 - VB_W / 2 * 7 - VB_S * 2,
			VB_W + VB_S
		},
		Weapon1Function,
		WEAPON1Y_P,
		WEAPON1Y_R,
		&key_weapon1
	},//1

	{
		{
			N950_W / 2 - VB_W / 2 * 7 - VB_S / 2 * 3,
			VB_S,
			N950_W / 2 - VB_W / 2 * 5 - VB_S / 2 * 3,
			VB_W + VB_S
		},
		Weapon2Function,
		WEAPON2Y_P,
		WEAPON2Y_R,
		&key_weapon2
	},//2

	{
		{
			N950_W / 2 - VB_W / 2 * 5 - VB_S,
			VB_S,
			N950_W / 2 - VB_W / 2 * 3 - VB_S,
			VB_W + VB_S
		},
		Weapon3Function,
		WEAPON3Y_P,
		WEAPON3Y_R,
		&key_weapon3
	},//3

	{
		{
			N950_W / 2 - VB_W / 2 * 3 - VB_S / 2,
			VB_S,
			N950_W / 2 - VB_W / 2 - VB_S / 2,
			VB_W + VB_S
		},
		Weapon4Function,
		WEAPON4Y_P,
		WEAPON4Y_R,
		&key_weapon4
	},//4

	{
		{
			N950_W / 2 - VB_W / 2,
			VB_S,
			N950_W / 2 + VB_W / 2,
			VB_W + VB_S
		},
		Weapon5Function,
		WEAPON5Y_P,
		WEAPON5Y_R,
		&key_weapon5
	},//5

	{
		{
			N950_W / 2 + VB_W / 2 + VB_S / 2,
			VB_S,
			N950_W / 2 + VB_W / 2 * 3 + VB_S / 2,
			VB_W + VB_S
		},
		Weapon6Function,
		WEAPON6Y_P,
		WEAPON6Y_R,
		&key_weapon6
	},//6

	{
		{
			N950_W / 2 + VB_W / 2 * 3 + VB_S,
			VB_S,
			N950_W / 2 + VB_W / 2 * 5 + VB_S,
			VB_W + VB_S
		},
		Weapon7Function,
		WEAPON7Y_P,
		WEAPON7Y_R,
		&key_weapon7
	},//7

	{
		{
			N950_W / 2 + VB_W / 2 * 5 + VB_S / 2 * 3,
			VB_S,
			N950_W / 2 + VB_W / 2 * 7 + VB_S / 2 * 3,
			VB_W + VB_S
		},
		Weapon8Function,
		WEAPON8Y_P,
		WEAPON8Y_R,
		&key_weapon8
	},//8

	{
		{
			N950_W / 2 + VB_W / 2 * 7 + VB_S * 2,
			VB_S,
			N950_W / 2 + VB_W / 2 * 9 + VB_S * 2,
			VB_W + VB_S
		},
		Weapon9Function,
		WEAPON9Y_P,
		WEAPON9Y_R,
		&key_weapon9
	},//9

	{
		{
			N950_W - VB_S * 3 - VB_W * 3,
			N950_H - VB_S * 2 - VB_W * 2,
			N950_W - VB_S * 3 - VB_W * 2,
			N950_H - VB_S * 2 - VB_W
		},
		TurnLeftFunction,
		TURNLEFTY_P,
		TURNLEFTY_R,
		&key_left
	},

	{
		{
			N950_W - VB_S - VB_W,
			N950_H - VB_S * 2 - VB_W * 2,
			N950_W - VB_S,
			N950_H - VB_S * 2 - VB_W
		},
		TurnRightFunction,
		TURNRIGHTY_P,
		TURNRIGHTY_R,
		&key_right
	},

	{
		{
			0,
			VB_W + VB_S,
			VB_W,
			VB_W * 2 + VB_S
		},
		GodModeFunction,
		GODMODEY_P,
		GODMODEY_R,
		&cheat_godmode
	},//god mode

	{
		{
			0,
			VB_W * 2 + VB_S * 2,
			VB_W,
			VB_W * 3 + VB_S * 2
		},
		KAModeFunction,
		KAMODEY_P,
		KAMODEY_R,
		&cheat_kamode
	},//KA mode

	{
		{
			N950_W - VB_W,
			VB_W + VB_S,
			N950_W,
			VB_W * 2 + VB_S
		},
		ClipModeFunction,
		CLIPMODEY_P,
		CLIPMODEY_R,
		&cheat_clipmode
	}

};

static inline void KARIN_EmulateKeyEvent(int x, int y, boolean pressed, const KARIN_VirtualButton *rect)
{
	if((x >= rect -> rect.x_1 && x <= rect -> rect.x_2)
			&& (y >= rect -> rect.y_1 && y <= rect -> rect.y_2))
	{
		sprite_rects[rect -> index].y = pressed ? rect -> pressedY : rect -> releasedY;
		event_t event;
    event.type = pressed ? ev_keydown : ev_keyup;
    event.data1 = *(rect -> function1);
    D_PostEvent(&event);
	}
}

static inline void KARIN_EmulateKeyEvent_Motion(int ox, int oy, int nx, int ny, const KARIN_VirtualButton *rect)
{
	boolean oldState = ((ox >= rect -> rect.x_1 && ox <= rect -> rect.x_2)
			&& (oy >= rect -> rect.y_1 && oy <= rect -> rect.y_2));
	boolean newState = ((nx >= rect -> rect.x_1 && nx <= rect -> rect.x_2)
			&& (ny >= rect -> rect.y_1 && ny <= rect -> rect.y_2));
	if(oldState && !newState)
	{
		sprite_rects[rect -> index].y = rect -> releasedY;
		event_t event;
    event.type = ev_keyup;
    event.data1 = *(rect -> function1);
    D_PostEvent(&event);
	}
	else if(newState && !oldState)
	{
		sprite_rects[rect -> index].y = rect -> pressedY;
		event_t event;
    event.type = ev_keydown;
    event.data1 = *(rect -> function1);
    D_PostEvent(&event);
	}
}

static inline void KARIN_EmulateCheat(int x, int y, boolean pressed, const KARIN_VirtualButton *rect)
{
	if((x >= rect -> rect.x_1 && x <= rect -> rect.x_2)
			&& (y >= rect -> rect.y_1 && y <= rect -> rect.y_2))
	{
		sprite_rects[rect -> index].y = pressed ? rect -> pressedY : rect -> releasedY;
		if(pressed)
			cheat[*(rect -> function1)].func();
	}
}

static inline void KARIN_EmulateCheat_Motion(int ox, int oy, int nx, int ny, const KARIN_VirtualButton *rect)
{
	boolean oldState = ((ox >= rect -> rect.x_1 && ox <= rect -> rect.x_2)
			&& (oy >= rect -> rect.y_1 && oy <= rect -> rect.y_2));
	boolean newState = ((nx >= rect -> rect.x_1 && nx <= rect -> rect.x_2)
			&& (ny >= rect -> rect.y_1 && ny <= rect -> rect.y_2));
	if(oldState && !newState)
	{
		sprite_rects[rect -> index].y = rect -> releasedY;
	}
	else if(newState && !oldState)
	{
		sprite_rects[rect -> index].y = rect -> pressedY;
		cheat[*(rect -> function1)].func();
	}
}

inline void KARIN_CheckVirtualButtons(const SDL_Event *ev)
{
	boolean b = (ev -> type == SDL_MOUSEBUTTONDOWN ? true : false);
	int x = ev -> button.x;
	int y = ev -> button.y;
	ButtonFunction start, end;
	//if(menuactive || (gamestate != GS_LEVEL && gamestate != GS_INTERMISSION && gamestate != GS_FINALE) || paused || demoplayback )
	if(menuactive || gamestate == GS_DEMOSCREEN || paused || demoplayback )
	{
		start = YesFunction;
		end = ForwardFunction;
	}
	else
	{
		start = PauseFunction;
		end = GodModeFunction;
		unsigned int i;
		for(i = GodModeFunction; i < TotalFunction; i++)
			KARIN_EmulateCheat(x, y, b, &(button_rects[i]));
	}
	unsigned int i;
	for(i = start; i < end; i++)
		KARIN_EmulateKeyEvent(x, y, b, &(button_rects[i]));
}

inline void KARIN_CheckVirtualButtons_Motion(const SDL_Event *ev)
{
	if(ev -> motion.state == SDL_PRESSED)
	{
		int xoffset = ev -> motion.x - ev -> motion.xrel;
		int yoffset = ev -> motion.y - ev -> motion.yrel;
		int x = ev -> motion.x;
		int y = ev -> motion.y;
		ButtonFunction start, end;
		//if(menuactive || (gamestate != GS_LEVEL && gamestate != GS_INTERMISSION && gamestate != GS_FINALE) || paused || demoplayback )
		if(menuactive || gamestate == GS_DEMOSCREEN || paused || demoplayback )
		{
			start = YesFunction;
			end = ForwardFunction;
		}
		else
		{
			start = PauseFunction;
			end = GodModeFunction;
			unsigned int i;
			for(i = GodModeFunction; i < TotalFunction; i++)
				KARIN_EmulateCheat_Motion(xoffset, yoffset, x, y, &(button_rects[i]));
		}
		unsigned int i;
		for(i = start; i < end; i++)
			KARIN_EmulateKeyEvent_Motion(xoffset, yoffset, x, y, &(button_rects[i]));
	}
}

#endif

////////////////////////////////////////////////////////////////////////////
// Input code
int             leds_always_off = 0; // Expected by m_misc, not relevant

// Mouse handling
extern int     usemouse;        // config file var
#ifndef _NON_HARMATTAN
#else
static boolean mouse_enabled; // usemouse, but can be overriden by -nomouse
static boolean mouse_currently_grabbed;
#endif

/////////////////////////////////////////////////////////////////////////////////
// Keyboard handling

//
//  Translates the key currently in key
//

static int I_TranslateKey(SDL_keysym* key)
{
  int rc = 0;

  switch (key->sym) {
  case SDLK_LEFT: rc = KEYD_LEFTARROW;  break;
  case SDLK_RIGHT:  rc = KEYD_RIGHTARROW; break;
  case SDLK_DOWN: rc = KEYD_DOWNARROW;  break;
  case SDLK_UP:   rc = KEYD_UPARROW;  break;
  case SDLK_ESCAPE: rc = KEYD_ESCAPE; break;
  case SDLK_RETURN: rc = KEYD_ENTER;  break;
  case SDLK_TAB:  rc = KEYD_TAB;    break;
  case SDLK_F1:   rc = KEYD_F1;   break;
  case SDLK_F2:   rc = KEYD_F2;   break;
  case SDLK_F3:   rc = KEYD_F3;   break;
  case SDLK_F4:   rc = KEYD_F4;   break;
  case SDLK_F5:   rc = KEYD_F5;   break;
  case SDLK_F6:   rc = KEYD_F6;   break;
  case SDLK_F7:   rc = KEYD_F7;   break;
  case SDLK_F8:   rc = KEYD_F8;   break;
  case SDLK_F9:   rc = KEYD_F9;   break;
  case SDLK_F10:  rc = KEYD_F10;    break;
  case SDLK_F11:  rc = KEYD_F11;    break;
  case SDLK_F12:  rc = KEYD_F12;    break;
  case SDLK_BACKSPACE:  rc = KEYD_BACKSPACE;  break;
  case SDLK_DELETE: rc = KEYD_DEL;  break;
  case SDLK_INSERT: rc = KEYD_INSERT; break;
  case SDLK_PAGEUP: rc = KEYD_PAGEUP; break;
  case SDLK_PAGEDOWN: rc = KEYD_PAGEDOWN; break;
  case SDLK_HOME: rc = KEYD_HOME; break;
  case SDLK_END:  rc = KEYD_END;  break;
  case SDLK_PAUSE:  rc = KEYD_PAUSE;  break;
  case SDLK_EQUALS: rc = KEYD_EQUALS; break;
  case SDLK_MINUS:  rc = KEYD_MINUS;  break;
  case SDLK_KP0:  rc = KEYD_KEYPAD0;  break;
  case SDLK_KP1:  rc = KEYD_KEYPAD1;  break;
  case SDLK_KP2:  rc = KEYD_KEYPAD2;  break;
  case SDLK_KP3:  rc = KEYD_KEYPAD3;  break;
  case SDLK_KP4:  rc = KEYD_KEYPAD4;  break;
  case SDLK_KP5:  rc = KEYD_KEYPAD5;  break;
  case SDLK_KP6:  rc = KEYD_KEYPAD6;  break;
  case SDLK_KP7:  rc = KEYD_KEYPAD7;  break;
  case SDLK_KP8:  rc = KEYD_KEYPAD8;  break;
  case SDLK_KP9:  rc = KEYD_KEYPAD9;  break;
  case SDLK_KP_PLUS:  rc = KEYD_KEYPADPLUS; break;
  case SDLK_KP_MINUS: rc = KEYD_KEYPADMINUS;  break;
  case SDLK_KP_DIVIDE:  rc = KEYD_KEYPADDIVIDE; break;
  case SDLK_KP_MULTIPLY: rc = KEYD_KEYPADMULTIPLY; break;
  case SDLK_KP_ENTER: rc = KEYD_KEYPADENTER;  break;
  case SDLK_KP_PERIOD:  rc = KEYD_KEYPADPERIOD; break;
  case SDLK_LSHIFT:
  case SDLK_RSHIFT: rc = KEYD_RSHIFT; break;
  case SDLK_LCTRL:
  case SDLK_RCTRL:  rc = KEYD_RCTRL;  break;
  case SDLK_LALT:
  case SDLK_LMETA:
  case SDLK_RALT:
  case SDLK_RMETA:  rc = KEYD_RALT;   break;
  case SDLK_CAPSLOCK: rc = KEYD_CAPSLOCK; break;
  default:    rc = key->sym;    break;
  }

  return rc;

}

/////////////////////////////////////////////////////////////////////////////////
// Main input code

/* cph - pulled out common button code logic */
static int I_SDLtoDoomMouseState(Uint8 buttonstate)
{
  return 0
      | (buttonstate & SDL_BUTTON(1) ? 1 : 0)
      | (buttonstate & SDL_BUTTON(2) ? 2 : 0)
      | (buttonstate & SDL_BUTTON(3) ? 4 : 0);
}

static void I_GetEvent(SDL_Event *Event)
{
  event_t event;

  switch (Event->type) {
  case SDL_KEYDOWN:
    event.type = ev_keydown;
    event.data1 = I_TranslateKey(&Event->key.keysym);
    D_PostEvent(&event);
    break;

  case SDL_KEYUP:
  {
    event.type = ev_keyup;
    event.data1 = I_TranslateKey(&Event->key.keysym);
    D_PostEvent(&event);
  }
  break;

  case SDL_MOUSEBUTTONDOWN:
  case SDL_MOUSEBUTTONUP:
#ifndef _NON_HARMATTAN
	KARIN_CheckVirtualButtons(Event);
#else
  if (mouse_enabled) // recognise clicks even if the pointer isn't grabbed
  {
    event.type = ev_mouse;
    event.data1 = I_SDLtoDoomMouseState(SDL_GetMouseState(NULL, NULL));
    event.data2 = event.data3 = 0;
    D_PostEvent(&event);
  }
#endif
  break;

  case SDL_MOUSEMOTION:
#ifndef _NON_HARMATTAN
	KARIN_CheckVirtualButtons_Motion(Event);
#else
  if (mouse_currently_grabbed) {
    event.type = ev_mouse;
    event.data1 = I_SDLtoDoomMouseState(Event->motion.state);
    event.data2 = Event->motion.xrel << 5;
    event.data3 = -Event->motion.yrel << 5;
    D_PostEvent(&event);
  }
#endif
  break;


  case SDL_QUIT:
    S_StartSound(NULL, sfx_swtchn);
    M_QuitDOOM(0);

  default:
    break;
  }
}


//
// I_StartTic
//

void I_StartTic (void)
{
  SDL_Event Event;
#ifndef _NON_HARMATTAN
#else
  {
    boolean should_be_grabbed = mouse_enabled &&
      !(paused || (gamestate != GS_LEVEL) || demoplayback);

    if (mouse_currently_grabbed != should_be_grabbed)
      SDL_WM_GrabInput((mouse_currently_grabbed = should_be_grabbed)
          ? SDL_GRAB_ON : SDL_GRAB_OFF);
  }
#endif

  while ( SDL_PollEvent(&Event) )
    I_GetEvent(&Event);

  I_PollJoystick();
}

//
// I_StartFrame
//
void I_StartFrame (void)
{
}

//
// I_InitInputs
//

static void I_InitInputs(void)
{
  int nomouse_parm = M_CheckParm("-nomouse");

  // check if the user wants to use the mouse
#ifndef _NON_HARMATTAN
#else
  mouse_enabled = usemouse && !nomouse_parm;
#endif

  // e6y: fix for turn-snapping bug on fullscreen in software mode
  if (!nomouse_parm)
    SDL_WarpMouse((unsigned short)(SCREENWIDTH/2), (unsigned short)(SCREENHEIGHT/2));

  I_InitJoystick();
}
/////////////////////////////////////////////////////////////////////////////

// I_SkipFrame
//
// Returns true if it thinks we can afford to skip this frame

inline static boolean I_SkipFrame(void)
{
  static int frameno;

  frameno++;
  switch (gamestate) {
  case GS_LEVEL:
    if (!paused)
      return false;
  default:
    // Skip odd frames
    return (frameno & 1) ? true : false;
  }
}

///////////////////////////////////////////////////////////
// Palette stuff.
//
static void I_UploadNewPalette(int pal)
{
  // This is used to replace the current 256 colour cmap with a new one
  // Used by 256 colour PseudoColor modes

  // Array of SDL_Color structs used for setting the 256-colour palette
  static SDL_Color* colours;
  static int cachedgamma;
  static size_t num_pals;

  if (V_GetMode() == VID_MODEGL)
    return;

  if ((colours == NULL) || (cachedgamma != usegamma)) {
    int pplump = W_GetNumForName("PLAYPAL");
    int gtlump = (W_CheckNumForName)("GAMMATBL",ns_prboom);
    register const byte * palette = W_CacheLumpNum(pplump);
    register const byte * const gtable = (const byte *)W_CacheLumpNum(gtlump) + 256*(cachedgamma = usegamma);
    register int i;

    num_pals = W_LumpLength(pplump) / (3*256);
    num_pals *= 256;

    if (!colours) {
      // First call - allocate and prepare colour array
      colours = malloc(sizeof(*colours)*num_pals);
    }

    // set the colormap entries
    for (i=0 ; (size_t)i<num_pals ; i++) {
      colours[i].r = gtable[palette[0]];
      colours[i].g = gtable[palette[1]];
      colours[i].b = gtable[palette[2]];
      palette += 3;
    }

    W_UnlockLumpNum(pplump);
    W_UnlockLumpNum(gtlump);
    num_pals/=256;
  }

#ifdef RANGECHECK
  if ((size_t)pal >= num_pals)
    I_Error("I_UploadNewPalette: Palette number out of range (%d>=%d)",
      pal, num_pals);
#endif

  // store the colors to the current display
  // SDL_SetColors(SDL_GetVideoSurface(), colours+256*pal, 0, 256);
  SDL_SetPalette(
      SDL_GetVideoSurface(),
      SDL_LOGPAL | SDL_PHYSPAL,
      colours+256*pal, 0, 256);
}

//////////////////////////////////////////////////////////////////////////////
// Graphics API

void I_ShutdownGraphics(void)
{
}

//
// I_UpdateNoBlit
//
void I_UpdateNoBlit (void)
{
}

//
// I_FinishUpdate
//
static int newpal = 0;
#define NO_PALETTE_CHANGE 1000

void I_FinishUpdate (void)
{
  if (I_SkipFrame()) return;

#ifdef MONITOR_VISIBILITY
  if (!(SDL_GetAppState()&SDL_APPACTIVE)) {
    return;
  }
#endif

#ifdef GL_DOOM
  if (V_GetMode() == VID_MODEGL) {
    // proff 04/05/2000: swap OpenGL buffers
    gld_Finish();
    return;
  }
#endif
  if (SDL_MUSTLOCK(screen)) {
      int h;
      byte *src;
      byte *dest;

      if (SDL_LockSurface(screen) < 0) {
        lprintf(LO_INFO,"I_FinishUpdate: %s\n", SDL_GetError());
        return;
      }
      dest=screen->pixels;
      src=screens[0].data;
      h=screen->h;
      for (; h>0; h--)
      {
        memcpy(dest,src,SCREENWIDTH*V_GetPixelDepth());
        dest+=screen->pitch;
        src+=screens[0].byte_pitch;
      }
      SDL_UnlockSurface(screen);
  }
  /* Update the display buffer (flipping video pages if supported)
   * If we need to change palette, that implicitely does a flip */
  if (newpal != NO_PALETTE_CHANGE) {
    I_UploadNewPalette(newpal);
    newpal = NO_PALETTE_CHANGE;
  }
#ifndef _NON_HARMATTAN
	KARIN_DrawVirtualButtons();
#endif
  SDL_Flip(screen);
}

//
// I_ScreenShot - moved to i_sshot.c
//

//
// I_SetPalette
//
void I_SetPalette (int pal)
{
  newpal = pal;
}

// I_PreInitGraphics

static void I_ShutdownSDL(void)
{
  SDL_Quit();
	SDL_FreeSurface(vb_surface);
  return;
}

void I_PreInitGraphics(void)
{
  // Initialize SDL
  unsigned int flags = 0;
  if (!(M_CheckParm("-nodraw") && M_CheckParm("-nosound")))
    flags = SDL_INIT_VIDEO;
#ifdef _DEBUG
  flags |= SDL_INIT_NOPARACHUTE;
#endif
  if ( SDL_Init(flags) < 0 ) {
    I_Error("Could not initialize SDL [%s]", SDL_GetError());
  }

  atexit(I_ShutdownSDL);
}

// e6y
// GLBoom use this function for trying to set the closest supported resolution if the requested mode can't be set correctly.
// For example glboom.exe -geom 1025x768 -nowindow will set 1024x768.
// It should be used only for fullscreen modes.
static void I_ClosestResolution (int *width, int *height, int flags)
{
  SDL_Rect **modes;
  int twidth, theight;
  int cwidth = 0, cheight = 0;
//  int iteration;
  int i;
  unsigned int closest = UINT_MAX;
  unsigned int dist;

  modes = SDL_ListModes(NULL, flags);

  //for (iteration = 0; iteration < 2; iteration++)
  {
    for(i=0; modes[i]; ++i)
    {
      twidth = modes[i]->w;
      theight = modes[i]->h;

      if (twidth > MAX_SCREENWIDTH || theight> MAX_SCREENHEIGHT)
        continue;
      
      if (twidth == *width && theight == *height)
        return;

      //if (iteration == 0 && (twidth < *width || theight < *height))
      //  continue;

      dist = (twidth - *width) * (twidth - *width) + 
             (theight - *height) * (theight - *height);

      if (dist < closest)
      {
        closest = dist;
        cwidth = twidth;
        cheight = theight;
      }
    }
    if (closest != 4294967295u)
    {
      *width = cwidth;
      *height = cheight;
      return;
    }
  }
}  

// CPhipps -
// I_CalculateRes
// Calculates the screen resolution, possibly using the supplied guide
void I_CalculateRes(unsigned int width, unsigned int height)
{
  // e6y: how about 1680x1050?
  /*
  SCREENWIDTH = (width+3) & ~3;
  SCREENHEIGHT = (height+3) & ~3;
  */

// e6y
// GLBoom will try to set the closest supported resolution 
// if the requested mode can't be set correctly.
// For example glboom.exe -geom 1025x768 -nowindow will set 1024x768.
// It affects only fullscreen modes.
  if (V_GetMode() == VID_MODEGL) {
    if ( desired_fullscreen )
    {
      I_ClosestResolution(&width, &height, SDL_OPENGL|SDL_FULLSCREEN);
    }
    SCREENWIDTH = width;
    SCREENHEIGHT = height;
    SCREENPITCH = SCREENWIDTH;
  } else {
    SCREENWIDTH = (width+15) & ~15;
#ifndef _NON_HARMATTAN
		if(SCREENWIDTH > N950_W)
			SCREENWIDTH = N950_W;
#endif
    SCREENHEIGHT = height;
#ifndef _NON_HARMATTAN
		if(SCREENHEIGHT > N950_H)
			SCREENHEIGHT = N950_H;
#endif
    if (!(SCREENWIDTH % 1024)) {
      SCREENPITCH = SCREENWIDTH*V_GetPixelDepth()+32;
    } else {
      SCREENPITCH = SCREENWIDTH*V_GetPixelDepth();
    }
  }
}

// CPhipps -
// I_SetRes
// Sets the screen resolution
void I_SetRes(void)
{
  int i;

  I_CalculateRes(SCREENWIDTH, SCREENHEIGHT);

  // set first three to standard values
  for (i=0; i<3; i++) {
    screens[i].width = SCREENWIDTH;
    screens[i].height = SCREENHEIGHT;
    screens[i].byte_pitch = SCREENPITCH;
    screens[i].short_pitch = SCREENPITCH / V_GetModePixelDepth(VID_MODE16);
    screens[i].int_pitch = SCREENPITCH / V_GetModePixelDepth(VID_MODE32);
  }

  // statusbar
  screens[4].width = SCREENWIDTH;
  screens[4].height = (ST_SCALED_HEIGHT+1);
  screens[4].byte_pitch = SCREENPITCH;
  screens[4].short_pitch = SCREENPITCH / V_GetModePixelDepth(VID_MODE16);
  screens[4].int_pitch = SCREENPITCH / V_GetModePixelDepth(VID_MODE32);

  lprintf(LO_INFO,"I_SetRes: Using resolution %dx%d\n", SCREENWIDTH, SCREENHEIGHT);
}

void I_InitGraphics(void)
{
  char titlebuffer[2048];
  static int    firsttime=1;

  if (firsttime)
  {
    firsttime = 0;

    atexit(I_ShutdownGraphics);
    lprintf(LO_INFO, "I_InitGraphics: %dx%d\n", SCREENWIDTH, SCREENHEIGHT);

    /* Set the video mode */
    I_UpdateVideoMode();

    /* Setup the window title */
    strcpy(titlebuffer,PACKAGE);
    strcat(titlebuffer," ");
    strcat(titlebuffer,VERSION);
    SDL_WM_SetCaption(titlebuffer, titlebuffer);

    /* Initialize the input system */
    I_InitInputs();
  }
}

int I_GetModeFromString(const char *modestr)
{
  video_mode_t mode;

  if (!stricmp(modestr,"15")) {
    mode = VID_MODE15;
  } else if (!stricmp(modestr,"15bit")) {
    mode = VID_MODE15;
  } else if (!stricmp(modestr,"16")) {
    mode = VID_MODE16;
  } else if (!stricmp(modestr,"16bit")) {
    mode = VID_MODE16;
  } else if (!stricmp(modestr,"32")) {
    mode = VID_MODE32;
  } else if (!stricmp(modestr,"32bit")) {
    mode = VID_MODE32;
  } else if (!stricmp(modestr,"gl")) {
    mode = VID_MODEGL;
  } else if (!stricmp(modestr,"OpenGL")) {
    mode = VID_MODEGL;
  } else {
    mode = VID_MODE8;
  }
  return mode;
}

void I_UpdateVideoMode(void)
{
  int init_flags;
  int i;
  video_mode_t mode;

  lprintf(LO_INFO, "I_UpdateVideoMode: %dx%d (%s)\n", SCREENWIDTH, SCREENHEIGHT, desired_fullscreen ? "fullscreen" : "nofullscreen");

  mode = I_GetModeFromString(default_videomode);
  if ((i=M_CheckParm("-vidmode")) && i<myargc-1) {
    mode = I_GetModeFromString(myargv[i+1]);
  }

  V_InitMode(mode);
  V_DestroyUnusedTrueColorPalettes();
  V_FreeScreens();

  I_SetRes();

  // Initialize SDL with this graphics mode
  if (V_GetMode() == VID_MODEGL) {
    init_flags = SDL_OPENGL;
  } else {
    if (use_doublebuffer)
      init_flags = SDL_DOUBLEBUF;
    else
      init_flags = SDL_SWSURFACE;
#ifndef _DEBUG
    init_flags |= SDL_HWPALETTE;
#endif
  }

  if ( desired_fullscreen )
    init_flags |= SDL_FULLSCREEN;

  if (V_GetMode() == VID_MODEGL) {
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 0 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, gl_colorbuffer_bits );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, gl_depthbuffer_bits );
    screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, gl_colorbuffer_bits, init_flags);
  } else {
    screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, V_GetNumPixelBits(), init_flags);
  }

  if(screen == NULL) {
    I_Error("Couldn't set %dx%d video mode [%s]", SCREENWIDTH, SCREENHEIGHT, SDL_GetError());
  }

  lprintf(LO_INFO, "I_UpdateVideoMode: 0x%x, %s, %s\n", init_flags, screen->pixels ? "SDL buffer" : "own buffer", SDL_MUSTLOCK(screen) ? "lock-and-copy": "direct access");

#ifndef _NON_HARMATTAN
#else
  mouse_currently_grabbed = false;
#endif

  // Get the info needed to render to the display
  if (!SDL_MUSTLOCK(screen))
  {
    screens[0].not_on_heap = true;
    screens[0].data = (unsigned char *) (screen->pixels);
    screens[0].byte_pitch = screen->pitch;
    screens[0].short_pitch = screen->pitch / V_GetModePixelDepth(VID_MODE16);
    screens[0].int_pitch = screen->pitch / V_GetModePixelDepth(VID_MODE32);
  }
  else
  {
    screens[0].not_on_heap = false;
  }

  V_AllocScreens();

  // Hide pointer while over this window
  SDL_ShowCursor(0);

  R_InitBuffer(SCREENWIDTH, SCREENHEIGHT);

  if (V_GetMode() == VID_MODEGL) {
    int temp;
    lprintf(LO_INFO,"SDL OpenGL PixelFormat:\n");
    SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_RED_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_GREEN_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_BLUE_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_STENCIL_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_STENCIL_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_ACCUM_RED_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_ACCUM_RED_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_ACCUM_GREEN_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_ACCUM_GREEN_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_ACCUM_BLUE_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_ACCUM_BLUE_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_ACCUM_ALPHA_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &temp );
    lprintf(LO_INFO,"    SDL_GL_DOUBLEBUFFER: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_BUFFER_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_BUFFER_SIZE: %i\n",temp);
    SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE, &temp );
    lprintf(LO_INFO,"    SDL_GL_DEPTH_SIZE: %i\n",temp);
#ifdef GL_DOOM
    gld_Init(SCREENWIDTH, SCREENHEIGHT);
#endif
  }
	
#ifndef _NON_HARMATTAN
		vb_surface = IMG_Load(VB_FILE);
		if(!vb_surface)
		{
			printf("Can't load virtual buttons image to SDL surface from %s\n", VB_FILE);
		}
#endif
}
