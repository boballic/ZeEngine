#ifndef ZEENGINE_ENTITY_COMPONENT_SYSTEM
#define ZEENGINE_ENTITY_COMPONENT_SYSTEM

#include <array>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include <memory>
#include "chunk_pool.h"
#include "ecs\arche_type.h"
#include "ecs\entity.h"
namespace ZeEngine
{
	namespace ecs
	{
		class Entity_manager
		{
		public:

			//Todo optimize this
			template <typename... Args>
			const Entity& create_entity()
			{
				for (auto& archetype : archetypes_)
				{
					if (archetype->supports_component<Args...>())
					{
						if (archetype->can_create_entity())
						{
							return archetype->get_entity();
						}
					}
				}

				archetypes_.emplace_back(Archetype::create<Args...>(factory_));
				return archetypes_.back()->get_entity();
			}

		private:
			Chunk_pool_factory factory_;

			//Todo this is probably not super efficient
			//Todo group by archetype some unique id then group those by an internal id and save that in entity
			std::vector<std::unique_ptr<Archetype>> archetypes_;
		};
	}
}
#endif

