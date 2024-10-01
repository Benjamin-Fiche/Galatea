#pragma once

#ifndef _DEBUGEXE
	#ifdef GALATEADLL_EXPORTS
	#define GALATEA_API __declspec(dllexport)
	#else
	#define GALATEA_API __declspec(dllimport)
	#endif
#else
#define GALATEA_API
#endif