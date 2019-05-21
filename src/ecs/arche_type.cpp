#include "ecs/arche_type.h"

namespace ZeEngine
{
	namespace ecs
	{
		Archetype::Archetype(const Chunk& chunk, const Archetype_container& container) :
			count(chunk_size / (container.get_archetype_size() + sizeof(Entity))),
			ptr_(chunk.ptr_)
		{
			size_t address = 0;

			for (const auto& type : container)
			{
				components_[type.ref].address = address;
				components_[type.ref].size = type.size;

				address += type.size * count;
			}

			max_address = address;

			auto all_entities = fetch<Entity>();
			for (size_t i = 0; i < count; ++i)
			{
				all_entities[i].id = i;
				all_entities[i].index = i;
			}
		}

		const Entity& Archetype::create_entity()
		{
			if (entity_count > count - 1)
			{
				throw std::runtime_error("No more entities left in this archetype");
			}

			auto& entity = fetch<Entity>()[entity_count];
			entity_count++;
			return entity;
		}

		/*
		 * Removes the entity and moves the last entity to its position
		 */
		void Archetype::remove_entity(const Entity& entity)
		{
			if (entity_count == 0)
				return;

			//Nothing to copy theres only 1 entity just remove it
			if (entity_count == 1)
			{
				entity_count--;
				return;
			}

			//Swap indexes since we are moving
			auto index_to_remove = entity.index;
			auto& removed_entity = fetch<Entity>()[entity.index];
			auto& moved_entity = fetch<Entity>()[(entity_count - 1)];
			std::swap(removed_entity.index, moved_entity.index);

			for (const auto& types : components_)
			{
				//We already copied this above
				if (types.first.get() == typeid(Entity))
					continue;

				auto size = types.second.size;
				char* component = fetch_internal(types.first);

				auto destination = reinterpret_cast<void*>(&component[index_to_remove * size]);
				auto source = reinterpret_cast<void*>(&component[(entity_count - 1) * size]);

				memcpy_s(destination, size, source, size);
			}

			entity_count--;
		}

		char* Archetype::fetch_internal(const type_info_ref& type)
		{
			if (components_.find(type) == components_.end())
			{
				throw std::runtime_error("Component not found");
			}

			const auto address = components_[type].address;
			return static_cast<char*>(&ptr_[address]);
		}
	}
}