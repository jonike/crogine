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

#ifndef CRO_SKELETAL_ANIMATOR_HPP_
#define CRO_SKELETAL_ANIMATOR_HPP_

#include <crogine/ecs/System.hpp>
#include <crogine/ecs/components/Skeleton.hpp>

namespace cro
{
    /*!
    \brief System used to update any models which have a skeleton component
    */
    class CRO_EXPORT_API SkeletalAnimator : public System
    {
    public:
        explicit SkeletalAnimator(MessageBus&);

        void process(Time) override;

    private:
        void onEntityAdded(Entity) override;

        void interpolate(std::size_t a, std::size_t b, float time, Skeleton& skelteton);
    };
}

#endif //CRO_SKELETAL_ANIMATOR_HPP_