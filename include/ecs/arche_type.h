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
		using TypeInfoRef = std::reference_wrapper<const type_info>;

		struct Hasher {
			size_t operator()(TypeInfoRef code) const
			{
				return code.get().hash_code();
			}
		};

		struct EqualTo {
			bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
			{
				return lhs.get() == rhs.get();
			}
		};

		struct Archetype_locator {
			size_t size{ 0 };
			size_t address{ 0 };
		};

		struct Archetype_component {
			TypeInfoRef ref;
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

			inline size_t get_archetype_size() const { return archetype_size; }

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

			Archetype(const Chunk& chunk, const Archetype_container& container);

			template <typename T>
			T* fetch()
			{
				if (components.find(typeid(T)) == components.end())
				{
					throw std::runtime_error("Component not found");
				}

				auto address = components[typeid(T)].address;
				return reinterpret_cast<T*>(&ptr_[address]);
			}

			const Entity& get_entity();
			void remove_entity(const Entity& entity);

			//Todo optimize this
			template <typename T, typename... Args>
			bool supports_component() const
			{
				if (components.find(typeid(T)) == components.end())
				{
					return false;
				}
				return true;
				//return supports_component<Args...>();
			}

			inline size_t can_create_entity() const { return entity_count < count; }
			inline size_t get_entity_count() const { return entity_count; }
			inline size_t get_array_count() const { return count; }
			inline size_t get_max_address() const { return max_address; }

		private:
			char* fetch_internal(const TypeInfoRef& type);

		private:
			char* ptr_;
			std::unordered_map<TypeInfoRef, Archetype_locator, Hasher, EqualTo> components;
			size_t count{ 0 };
			size_t max_address{ 0 };
			size_t entity_count{ 0 };
		};

		
	}
}

#endif