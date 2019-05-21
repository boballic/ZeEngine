#ifndef ZEENGINE_ARCHE_TYPE
#define ZEENGINE_ARCHE_TYPE

#include <typeinfo>
#include <memory>
#include <vector>
#include <unordered_map>

#include "ecs/chunk_pool.h"
#include "ecs/entity.h"

namespace ZeEngine
{
	namespace ecs
	{
		using type_info_ref = std::reference_wrapper<const type_info>;

		struct Hasher {
			size_t operator()(type_info_ref code) const
			{
				return code.get().hash_code();
			}
		};

		struct Equal_to {
			bool operator()(type_info_ref lhs, type_info_ref rhs) const
			{
				return lhs.get() == rhs.get();
			}
		};

		struct Archetype_locator {
			size_t size{ 0 };
			size_t address{ 0 };
		};

		struct Archetype_component {
			type_info_ref ref;
			size_t size{ 0 };
		};

		class Archetype_container : public std::vector<Archetype_component>
		{
		public:

			Archetype_container()
			{
				add_component<Entity>();
			}

			template <typename T>
			void add_component()
			{
				archetype_size += sizeof(T);
				push_back(Archetype_component{ typeid(T), sizeof(T) });
			}

			size_t get_archetype_size() const { return archetype_size; }

		private:
			size_t archetype_size{ 0 };
		};

		template<typename... Args>
		Archetype_container archetype_component_factory()
		{
			Archetype_container container;
			archetype_component_factory<Args...>(container);
			return container;
		}

		template <typename T>
		void archetype_component_factory(Archetype_container& container)
		{
			container.add_component<T>();
		}

		template<typename T, typename U, typename... Args>
		void archetype_component_factory(Archetype_container& container)
		{
			container.add_component<T>();
			archetype_component_factory<U, Args...>(container);
		}

		class Archetype
		{
		public:

			template <typename... Args>
			static std::unique_ptr<Archetype> create(Chunk_pool_factory& factory)
			{
				return std::make_unique<Archetype>(factory.get_chunk(), archetype_component_factory<Args...>());
			}

			template <typename... Args>
			static std::unique_ptr<Archetype> create(Chunk_pool_factory& factory, const Archetype_container& container)
			{
				return std::make_unique<Archetype>(factory.get_chunk(), container);
			}

			Archetype(const Chunk& chunk, const Archetype_container& container);

			template <typename T>
			T* fetch()
			{
				if (components_.find(typeid(T)) == components_.end())
				{
					throw std::runtime_error("Component not found");
				}

				auto address = components_[typeid(T)].address;
				return reinterpret_cast<T*>(&ptr_[address]);
			}

			const Entity& create_entity();
			void remove_entity(const Entity& entity);

			template <typename T>
			bool supports_component() const noexcept
			{
				return components_.find(typeid(T)) != components_.end();
			}

			template <typename T, typename U, typename... Args>
			bool supports_component() const noexcept
			{
				//Would be faster to have a bit mask but at least like this we can support as many components as we want
				if (components_.find(typeid(T)) == components_.end())
					return false;

				return supports_component<U, Args...>();
			}

			inline size_t can_create_entity() const { return entity_count < count; }
			inline size_t get_entity_count() const { return entity_count; }
			inline size_t get_array_count() const { return count; }
			inline size_t get_max_address() const { return max_address; }

		private:
			char* fetch_internal(const type_info_ref& type);

		private:
			char* ptr_;
			std::unordered_map<type_info_ref, Archetype_locator, Hasher, Equal_to> components_;
			size_t count{ 0 };
			size_t max_address{ 0 };
			size_t entity_count{ 0 };
		};	
	}
}

#endif