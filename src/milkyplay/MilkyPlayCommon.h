/*
 *  MilkyPlayCommon.h
 *
 *  Created by Peter Barth on 23.12.04.
 *  Copyright 2004 milkytracker.net, All rights reserved.
 *
 */
#ifndef __MILKYPLAYCOMMON_H__
#define __MILKYPLAYCOMMON_H__

#include "MilkyPlayTypes.h"

#if defined WIN32 && !defined _WIN32_WCE
#include <assert.h>
#define ASSERT assert
#endif

#if defined WIN32 || defined _WIN32_WCE
	#include <windows.h>
#elif defined __PSP__
	#include <assert.h>
	#define ASSERT assert

	#include <malloc.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
#else
	#include <assert.h>
	#define ASSERT assert
	
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
#endif

#if defined WIN32 || defined _WIN32_WCE
	typedef TCHAR SYSCHAR;
	typedef HANDLE FHANDLE;
#ifdef __GNUWIN32__
	typedef long long mp_int64;
#else
	typedef __int64 mp_int64;
#endif
#else
	typedef long long mp_int64;
	typedef char SYSCHAR;
	typedef FILE* FHANDLE;
#endif

#ifdef MILKYTRACKER
	#define MP_MAXSAMPLES 256*16
#else
	#define MP_MAXSAMPLES 256
#endif

#define MP_NUMEFFECTS 4

#if defined(WIN32) || defined(_WIN32_WCE) && !defined(__FORCE_SDL_AUDIO__)
	#define DRIVER_WIN32
#elif defined(__APPLE__) && !defined(__FORCE_SDL_AUDIO__)
	#define DRIVER_OSX
#elif defined(__MILKYPLAY_UNIX__) && !defined(__FORCE_SDL_AUDIO__)
	#define DRIVER_UNIX
#elif defined(__PSP__) && !defined(__FORCE_SDL_AUDIO__)
	#define DRIVER_PSP
#else
	#define DRIVER_SDL
#endif

#endif

