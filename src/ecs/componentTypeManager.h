#pragma on

#include <cstdint>

namespace DG {

	class ComponentTypeManager {
	public:
		template <typename T>
		static uint32_t GetId()
		{
			static uint32_t id = m_nextComponentId++;
			return id;
		}

	private:
		static inline uint32_t m_nextComponentId = 0;
	};

}