#pragma once

#include <vector>

namespace DG {

	enum AttribType {
		FLOAT_ATTRIB,
		INT_ATTRIB,
		BYTE_ATTRIB
	};

	typedef struct {
		AttribType type;
		int size;
		size_t offset;
	} VertexAttribute;

	class VertexLayout {
	public:
		VertexLayout() = default;
		void AddAttribute(AttribType type, int size);
		void Apply() const;

		static VertexLayout GetDefaultMeshLayout();

	private:
		std::vector<VertexAttribute> m_attributes;
		unsigned int m_stride = 0;

		int attribTypeToOpenGlType(AttribType type) const;
		size_t attribTypeToSize(AttribType type) const;
	};

}