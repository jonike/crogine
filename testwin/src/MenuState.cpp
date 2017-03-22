/*-----------------------------------------------------------------------

Matt Marchant 2017
http://trederia.blogspot.com

crogine test application - Zlib license.

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

#include "MenuState.hpp"

#include <crogine/system/Clock.hpp>
#include <crogine/App.hpp>

namespace
{
	struct Buns
	{
		int flaps = 20;
	};
}

MenuState::MenuState(cro::StateStack& stack, cro::State::Context context)
	: cro::State(stack, context)
{

}

//public
bool MenuState::handleEvent(const cro::Event& evt)
{
	return true;
}

bool MenuState::simulate(cro::Time dt)
{
	
	return true;
}

void MenuState::render() const
{
	
}