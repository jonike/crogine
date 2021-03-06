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

#ifndef CRO_SYSTEM_HPP_
#define CRO_SYSTEM_HPP_

#include <crogine/Config.hpp>
#include <crogine/ecs/Entity.hpp>
#include <crogine/ecs/Component.hpp>
#include <crogine/core/MessageBus.hpp>

#include <vector>
#include <typeindex>

namespace cro
{
    class Time;
    class Scene;

    using UniqueType = std::type_index;

    /*!
    \brief Base class for systems.
    Systems should all derive from this base class, and instanciated before any entities
    are created. Concrete system types should declare a list component types via requireComponent()
    on construction, so that only entities with the relevant components are added to the system.
    */
    class CRO_EXPORT_API System
    {
    public:

        using Ptr = std::unique_ptr<System>;

        /*!
        \brief Constructor.
        Pass in a reference to the concrete implementation to generate
        a unique type ID for this system.
        */
        //template <typename T>
        System(MessageBus& mb, UniqueType t) 
            : m_messageBus(mb), m_type(t), m_scene(nullptr){}

        virtual ~System() = default;

        /*!
        \brief Returns the unique type ID of the system
        */
        UniqueType getType() const { return m_type; }

        /*!
        \brief Returns a list of entities that this system is currently interested in
        */
        std::vector<Entity> getEntities() const;

        /*!
        \brief Adds an entity to the list to process
        */
        void addEntity(Entity);

        /*!
        \brief Removes an entity from the list to process
        */
        void removeEntity(Entity);

        /*!
        \brief Returns the component mask used to mask entities with corresponding
        components for this system to process
        */
        const ComponentMask& getComponentMask() const;

        /*!
        \brief Used to process any incoming system messages
        */
        virtual void handleMessage(const cro::Message&);

        /*!
        \brief Implement this for system specific processing to entities.
        */
        virtual void process(cro::Time);

    protected:

        /*!
        \brief Adds a component type to the list of components required by the
        system for it to be interested in a particular entity.
        */
        template <typename T>
        void requireComponent();

        std::vector<Entity>& getEntities() { return m_entities; }

        /*!
        \brief Optional callback performed when an entity is added
        */
        virtual void onEntityAdded(Entity) {}

        /*!
        \brief Optional callback performed when an entity is removed
        */
        virtual void onEntityRemoved(Entity) {}

        /*!
        \brief Posts a message on the system wide message bus
        */
        template <typename T>
        T* postMessage(Message::ID id);

        /*!
        \brief Returns a reference to the MessageBus
        */
        MessageBus& getMessageBus() { return m_messageBus; }

        /*
        \brief Used by the SystemManager to supply the active scene
        */
        void setScene(Scene&);

        /*!
        \brief Returns a pointer to the scene to which this system belongs
        */
        Scene* getScene();

    private:

        MessageBus& m_messageBus;
        UniqueType m_type;

        ComponentMask m_componentMask;
        std::vector<Entity> m_entities;

        Scene* m_scene;

        friend class SystemManager;
    };

    class CRO_EXPORT_API SystemManager final
    {
    public:
        explicit SystemManager(Scene&);

        ~SystemManager() = default;
        SystemManager(const SystemManager&) = delete;
        SystemManager(const SystemManager&&) = delete;
        SystemManager& operator = (const SystemManager&) = delete;
        SystemManager& operator = (const SystemManager&&) = delete;

        /*!
        \brief Adds a system of a given type to the manager.
        If the system already exists nothing is changed.
        \returns Reference to the system, for instance a rendering
        system maybe required elsewhere so a reference to it can be kept.
        */
        template <typename T, typename... Args>
        T& addSystem(Args&&... args);

        /*!
        \brief Removes the system of this type, if it exists
        */
        template <typename T>
        void removeSystem();

        /*!
        \brief Returns a reference to this system type, if it exists
        */
        template <typename T>
        T& getSystem();

        /*!
        \brief Returns true if a system of this type exists within the manager
        */
        template <typename T>
        bool hasSystem() const;

        /*!
        \brief Submits an entity to all available systems
        */
        void addToSystems(Entity);

        /*!
        \brief Removes the given Entity from any systems to which it may belong
        */
        void removeFromSystems(Entity);

        /*!
        \brief Forwards messages to all systems
        */
        void forwardMessage(const cro::Message&);

        /*!
        \brief Runs a simulation step by calling process() on each system
        */
        void process(Time);
    private:
        Scene& m_scene;
        std::vector<std::unique_ptr<System>> m_systems;
    };

#include "System.inl"
#include "SystemManager.inl"
}

#endif //CRO_SYSTEM_HPP_