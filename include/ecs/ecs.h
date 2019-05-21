#ifndef ZEENGINE_ENTITY_COMPONENT_SYSTEM
#define ZEENGINE_ENTITY_COMPONENT_SYSTEM

#include <array>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include "chunk_pool.h"
#include "ecs\arche_type.h"
#include "ecs\entity.h"
#include "ecs\archetype_factory.h"

namespace ZeEngine
{
	namespace ecs
	{
		typedef  std::vector<std::unique_ptr<Archetype>> Archetypes;

		class Entity_manager
		{
		public:
			template <typename... Args>
			const Entity& create_entity()
			{
				static auto archetype_index = std::type_index(typeid(Args)...);

				auto it = archetypes_.find(archetype_index);
				if (it == archetypes_.end())
				{
					auto factory = Archetype_factory::create_factory<Args...>(factory_);
					auto& entity = factory->create_entity<Args...>(factory_);
					archetypes_.insert({archetype_index, std::move(factory) });
					return entity;				
				}
				
				return it->second->create_entity<Args...>(factory_);
			}

		private:
			Chunk_pool_factory factory_;
			std::unordered_map<std::type_index, std::unique_ptr<Archetype_factory>> archetypes_;
		};
	}
}
#endif

