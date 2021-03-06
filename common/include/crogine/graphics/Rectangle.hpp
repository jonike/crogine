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

#ifndef CRO_RECTANGLE_HPP_
#define CRO_RECTANGLE_HPP_

#include <crogine/Config.hpp>
#include <crogine/detail/Types.hpp>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <type_traits>
#include <algorithm>
#include <array>
#include <limits>

namespace cro
{
    /*!
    \brief Defines a 2D rectangle, starting at the bottom left position with width and height
    */
    template <class T>
    class CRO_EXPORT_API Rectangle final
    {
    public:
        Rectangle(T l = 0, T b = 0, T w = 0, T h = 0)
            : left(l), bottom(b), width(w), height(h) 
        {
            static_assert(std::is_pod<T>::value, "Only PODs allowed");
        }

        T left, bottom, width, height;

        /*!
        \brief Conversion constructor.
        Creates a rectangle of T when the param is of type U
        */
        template <typename U>
        explicit Rectangle(const Rectangle<U>&);

        /*!
        \brief Returns true if the given rectangle intersects this one
        \param overlap If a rectangle instance is passed in as a second parameter
        then it will contain the overlapping area of the two rectangles, if they
        overlap
        */
        bool intersects(Rectangle<T>, Rectangle<T>& overlap = Rectangle<T>()) const;

        /*!
        \brief Returns true if this rectangle fully contains the given rectangle
        */
        bool contains(Rectangle<T>) const;

        /*!
        \brief Returns true if this rectangle contains the given point
        */
        bool contains(glm::vec2) const;

        /*!
        \brief Returns a copy of this rectangle transformed by the given matrix
        */
        Rectangle<T> transform(const glm::mat4&);
    };

    /*Some short cuts for concrete types*/
    using IntRect = Rectangle<int32>;
    using URect = Rectangle<uint32>;
    using FloatRect = Rectangle<float>;

#include "Rectangle.inl"
}

#endif //CRO_RECTANGLE_HPP_
