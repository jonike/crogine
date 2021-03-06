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

#ifndef CRO_RENDER_TEXTURE_HPP_
#define CRO_RENDER_TEXTURE_HPP_

#include <crogine/graphics/Texture.hpp>
#include <crogine/graphics/Colour.hpp>

#include <array>

namespace cro
{
    /*!
    \brief A render buffer which can be used as a texture.
    RenderTextures are non-copyable objects but *can* be moved.
    */
    class CRO_EXPORT_API RenderTexture final : public Detail::SDLResource
    {
    public:
        /*!
        \brief Constructor.
        By default RenderTextures are in an invalid state until create() has been called
        at least once.
        To draw to a render texture first call its clear() function, which then activates
        it as the current target. All drawing operations will then be performed on it
        until display() is called. Both clear AND display() *must* be called either side of 
        drawing to prevent undefined results.
        */
        RenderTexture();
        ~RenderTexture();

        RenderTexture(const RenderTexture&) = delete;
        RenderTexture(RenderTexture&&);
        const RenderTexture& operator = (const RenderTexture&) = delete;
        RenderTexture& operator = (RenderTexture&&);

        /*!
        \brief Creates (or recreates) the render texture
        \param width Width of the texture to create. This should be
        power of 2 on mobile platforms
        \param height Height of the texture. This should be power of
        2 on mobile platforms.
        \param depthBuffer Creates an 24 bit depth buffer when set to true (default)
        \param stencilBuffer Creates an 8 bit stencil buffer when set to true (default false)
        Stencil buffers must be accompanied by a depth buffer. If depthbuffer is false no stencil
        buffer will be created.
        \returns true on success, else returns false
        */
        bool create(uint32 width, uint32 height, bool depthBuffer = true, bool stencilBuffer = false);

        /*!
        \brief Returns the current size in pixels of the render texture (zero if not yet created)
        */
        glm::uvec2 getSize() const;

        /*!
        \brief Returns a reference to the colour buffer texture to be used in rendering
        */
        const Texture& getTexture() const;

        /*!
        \brief Sets the underlying texture to repeated when wrapping
        */
        void setRepeated(bool);

        /*!
        \brief Returns true if the underlying texture is set to repeat on wrap, else returns false
        */
        bool isRepeated() const;

        /*!
        \brief Sets whether or not smoothing is enabled on the underlying texture.
        */
        void setSmooth(bool);

        /*!
        \brief Returns whether or not smoothing is enabled on the underlying texture.
        */
        bool isSmooth() const;

        /*!
        \brief Clears the texture ready for drawing
        \param colour Colour to clear the texture with.
        This should be called to activate the render texture as the current draw target.
        From then all drawing operations will be applied to the RenderTexture until display()
        is called. For every clear() call there must be exactly one display() call. This
        also attempts to save and restore any existing viewport, while also applying its
        own during rendering.
        */
        void clear(Colour colour = Colour::Black());

        /*!
        \brief This must be called once for each call to clear to properly validate
        the final state of the render texture. Failing to do this will result in undefined
        behaviour.
        */
        void display();

        /*!
        \brief Defines the area of the RenderTexture to which to draw.
        */
        void setViewport(URect);

        /*!
        \brief Returns the active viewport for this texture
        */
        URect getViewport() const;

        /*!
        \brief Returns the default viewport of the RenderTexture
        */
        URect getDefaultViewport() const;

        /*!
        \brief Returns true if the render texture is available for drawing.
        If create() has not yet been called, or previously failed then this
        will return false
        */
        bool available() const { return m_fboID != 0; }

    private:
        uint32 m_fboID;
        uint32 m_rboID;
        uint32 m_clearBits;
        Texture m_texture;
        URect m_viewport;
        std::array<int32, 4u> m_lastViewport;
        std::array<float, 4u> m_lastClearColour;
        int32 m_lastBuffer;
    };
}

#endif //CRO_RENDER_TEXTURE_HPP_