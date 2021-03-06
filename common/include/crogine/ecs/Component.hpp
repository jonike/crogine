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

#ifndef CRO_COMPONENT_HPP_
#define CRO_COMPONENT_HPP_

#include <crogine/Config.hpp>
#include <crogine/detail/Types.hpp>

#include <cstdlib>
#include <vector>
#include <typeindex>
#include <algorithm>

namespace cro
{
    class CRO_EXPORT_API Component final
    {
    public:

        using ID = uint32;

        /*!
        \brief Returns a unique ID based on the component type
        */
        template <typename T>
        static ID getID()
        {
            auto id = std::type_index(typeid(T));
            return getFromTypeID(id);
        }

    private:
        static ID getFromTypeID(std::type_index);
    };
}

#endif //CRO_COMPONENT_HPP_
