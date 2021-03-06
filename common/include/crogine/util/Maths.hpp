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

#ifndef CRO_UTIL_MATHS_HPP_
#define CRO_UTIL_MATHS_HPP_

#ifdef _MSC_VER
#define NOMINMAX
#endif //_MSC_VER

#include <type_traits>
#include <algorithm>

namespace cro
{
    namespace Util
    {
        namespace Maths
        {
            template <typename T>
            T clamp(T value, T min, T max)
            {
                static_assert(std::is_pod<T>::value, "Only available on POD");
                return std::min(max, std::max(min, value));
            }
        }
    }
}

#endif //CRO_UTIL_MATHS_HPP_