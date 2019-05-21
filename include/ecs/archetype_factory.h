#ifndef ZEENGINE_ARCHETYPE_FACTORY
#define ZEENGINE_ARCHETYPE_FACTORY

#include <memory>
#include <vector>

#include "entity.h"
#include "chunk_pool.h"
#include "arche_type.h"
#include "archetype_factory.h"

namespace ZeEngine
{
	namespace ecs
	{
		class Archetype_factory
		{
		public:
			Archetype_factory(std::unique_ptr<Archetype> initial)
			{
				free_archetypes_.push_back(std::move(initial));
			}

			template <typename... Args>
			const Entity& create_entity(Chunk_pool_factory& factory)
			{
				auto& entity = free_archetypes_.back()->create_entity();

				if (!free_archetypes_.back()->can_create_entity())
				{
					free_archetypes_.push_back(create_archetype<Args...>(factory));
				}
				return entity;
			}

			template<typename... Args>
			static std::unique_ptr<Archetype> create_archetype(Chunk_pool_factory& factory)
			{
				static auto archetype_container = archetype_component_factory<Args...>();
				return Archetype::create<Args...>(factory, archetype_container);
			}

			template <typename... Args>
			static std::unique_ptr<Archetype_factory> create_factory(Chunk_pool_factory& factory)
			{
				auto& archetype = Archetype_factory::create_archetype<Args...>(factory);
				return std::make_unique<Archetype_factory>(std::move(archetype));
			}

		private:
			std::vector<std::unique_ptr<Archetype>> free_archetypes_;
		};
	}
}
#endif