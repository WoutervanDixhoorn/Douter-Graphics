#pragma once

#include <stdint.h>
#include <cstddef>

namespace DG {

	class VertexBuffer {
	public: 
		VertexBuffer(); //Construct
		
		//Rule of Five
		~VertexBuffer(); //Desctruct
		VertexBuffer(const VertexBuffer&) = delete; //Copy constructor
		VertexBuffer& operator=(const VertexBuffer&) = delete; //Copy assignment
		VertexBuffer(VertexBuffer&& other) noexcept; //Move constructor
		VertexBuffer& operator=(VertexBuffer&& other) noexcept; //Move assignment

		void Bind();

		void SetData(void* vertexData, int vertexCount, size_t vertexSize);
		void UpdateData(void* vertexData, int vertexCount, size_t vertexSize);
	private:
		unsigned int m_bufferId;
	};

	class IndexBuffer {
	public:
		IndexBuffer();

		~IndexBuffer();
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		void Bind();

		void SetData(const uint32_t* indexData, int indexCount);
		void UpdateData(const uint32_t* indexData, int indexCount);
	private:
		unsigned int m_bufferId;
	};
}