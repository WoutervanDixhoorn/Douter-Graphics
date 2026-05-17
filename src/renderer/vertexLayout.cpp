#include "vertexLayout.h"

#include "glad/glad.h"

namespace DG {
	
	void VertexLayout::AddAttribute(AttribType type, int size)
	{
		m_attributes.push_back({ type, size, m_stride });
		m_stride += size * attribTypeToSize(type);
	}

	void VertexLayout::Apply() const
	{
		for (size_t i = 0; i < m_attributes.size(); i++) {
			const auto& attrib = m_attributes[i];
			int glType = attribTypeToOpenGlType(attrib.type);

			glVertexAttribPointer(i, attrib.size, glType, GL_FALSE, m_stride, (void*)attrib.offset);
			glEnableVertexAttribArray(i);
		}
	}

	int VertexLayout::attribTypeToOpenGlType(AttribType type) const
	{
		switch (type) {
		case FLOAT_ATTRIB:
			return GL_FLOAT;
		case INT_ATTRIB:
			return GL_INT;
		case BYTE_ATTRIB:
			return GL_BYTE;
		default:
			return GL_FLOAT;
		}
	}

	size_t VertexLayout::attribTypeToSize(AttribType type) const
	{
		switch (type) {
		case FLOAT_ATTRIB:
			return sizeof(float);
		case INT_ATTRIB:
			return sizeof(int);
		case BYTE_ATTRIB:
			return sizeof(char);
		default:
			return sizeof(float);
		}
	}
}