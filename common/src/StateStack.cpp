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

#include <crogine/StateStack.hpp>
#include <crogine/App.hpp>
#include <crogine/Log.hpp>

#include <crogine/detail/Assert.hpp>
#include <crogine/system/Clock.hpp>

using namespace cro;

StateStack::StateStack(State::Context context)
	: m_context(context)
{

}

//public
void StateStack::handleEvent(const cro::Event& evt)
{
	for (auto i = m_stack.rbegin(); i != m_stack.rend(); ++i)
	{
		if (!(*i)->handleEvent(evt)) break;
	}
}

void StateStack::simulate(Time dt)
{
	applyPendingChanges();
	for (auto i = m_stack.rbegin(); i != m_stack.rbegin(); ++i)
	{
		if (!(*i)->simulate(dt)) break;
	}
}

void StateStack::render()
{
	for (auto& s : m_stack) s->render();
}

void StateStack::pushState(StateID id)
{
	if (empty() || m_stack.back()->getStateID() != id)
	{
		m_pendingChanges.emplace_back(Action::Push, id, false);
	}
}

void StateStack::popState()
{
	m_pendingChanges.emplace_back(Action::Pop);
}

void StateStack::clearStates()
{
	m_pendingChanges.emplace_back(Action::Clear);
}

bool StateStack::empty() const
{
	return m_stack.empty();
}

std::size_t StateStack::getStackSize() const
{
	return m_stack.size();
}

//private
State::Ptr StateStack::createState(StateID id)
{
	CRO_ASSERT(m_factories.count(id) != 0, "State not registered with statestack");
	return m_factories.find(id)->second();
}

void StateStack::applyPendingChanges()
{
	m_activeChanges.swap(m_pendingChanges);
	for (const auto& change : m_activeChanges)
	{
		switch (change.action)
		{
		default: break;
		case Action::Push:
			if (change.suspendPrevious && !m_stack.empty())
			{
				m_suspended.push_back(std::make_pair(change.id, std::move(m_stack.back())));
				m_stack.pop_back();
			}

			m_stack.emplace_back(createState(change.id));
			break;
		case Action::Pop:
		{
			auto id = m_stack.back()->getStateID();
			m_stack.pop_back();

			if (!m_suspended.empty() && m_suspended.back().first == id)
			{
				//restore suspended state
				m_stack.push_back(std::move(m_suspended.back().second));
				m_suspended.pop_back();
			}
		}
			break;
		case Action::Clear:
			m_stack.clear();
			m_suspended.clear();
			break;
		}
	}
	m_activeChanges.clear();
}