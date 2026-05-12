#pragma once

#include <stdint.h>

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

		void SetData(uint32_t* indexData, int indexCount);
	private:
		unsigned int m_bufferId;
	};
}