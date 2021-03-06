/*-----------------------------------------------------------------------

Matt Marchant 2017
http://trederia.blogspot.com  

crogine - Zlib license.

This software is provided 'as-is', without any express or
implied warranty.In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.

-----------------------------------------------------------------------*/

#ifndef CRO_CONFIG_HPP_
#define CRO_CONFIG_HPP_

#if defined  __ANDROID__ || (defined __APPLE__ && TARGET_OS_IPHONE)
#define PLATFORM_MOBILE 1
#else
#define PLATFORM_DESKTOP 1
#endif //platform check

//check for audio backend defines and define a fallback if there are none
//#if defined(PLATFORM_MOBILE) && !defined(AL_AUDIO)
//#define SDL_AUDIO 1
//#elif defined(PLATFORM_DESKTOP) && !defined(SDL_AUDIO)
#if !defined(AL_AUDIO) || !defined (SDL_AUDIO)
#define AL_AUDIO 1
#endif

//check which platform we're on and create export macros as necessary
#if !defined(CRO_STATIC)

#if defined(_WIN32)

#ifndef NOMINMAX
#define NOMINMAX
#endif

//windows compilers need specific (and different) keywords for export
#define CRO_EXPORT_API __declspec(dllexport)

//for vc compilers we also need to turn off this annoying C4251 warning
#ifdef _MSC_VER
#pragma warning(disable: 4251)
//#ifdef _DEBUG_
//#ifdef _ITERATOR_DEBUG_LEVEL
//#undef _ITERATOR_DEBUG_LEVEL
//#define _ITERATOR_DEBUG_LEVEL 0
//#endif
//#endif //_DEBUG_
#endif //_MSC_VER

#else //linux, FreeBSD, Mac OS X

#if __GNUC__ >= 4

//gcc 4 has special keywords for showing/hiding symbols,
//the same keyword is used for both importing and exporting
#define CRO_EXPORT_API __attribute__ ((__visibility__ ("default")))

#else

//gcc < 4 has no mechanism to explicitly hide symbols, everything's exported
#define CRO_EXPORT_API
#endif //__GNUC__

#endif //_WIN32

#else

//static build doesn't need import/export macros
#define CRO_EXPORT_API

#endif //CRO_STATIC

#include <crogine/android/Android.hpp>

#endif //CRO_CONFIG_HPP_
