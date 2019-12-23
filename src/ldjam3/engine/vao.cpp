
#include "vao.h"

#include <iostream>

namespace FFF {
	/// constructs a vertex attribute
	/// data should be heap initialized
	/// memory management will be taken care of by the class
	Attribute::Attribute(u32 perVertex, u32 length, f32* data) {
		this->perVertex = perVertex;
		this->size = length * sizeof(float);
		this->data = data;

		glGenBuffers(1, &buffer);
	}

	/// the vertices in a vao are an attribute
	/// use this function to shortcut the creation
	Attribute Attribute::createVertexAttribute(u32 length, f32* data) {
		return Attribute(3, length, data);
	}

	VAO::VAO(
		i32 drawMode, Attribute &&vertexAttrib,
		u32 indexCount, u32 indices[],
		u32 attribCount, Attribute attribs[]
	) : Resource(false),
		indexCount(indexCount),
		drawMode(drawMode),
		attribs(attribs),
		vertexAttrib(vertexAttrib),
		indices(indices),
		attribCount(attribCount),
		ibo(0),
		vao(0)
	{}

	void VAO::customProcess() {
		// create this vao
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// the first attribute is of course vertices
		add_attribute(vertexAttrib, 0);

		// add the rest of the custom attributes
		for (auto i = 0; i < attribCount; ++i)
			add_attribute(attribs[i], i + 1);

		// add index buffer
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(int), indices, GL_STATIC_DRAW);
	}

	void VAO::customUnload() {
		// delete all custom vertex attribute buffers
		for (auto i = 0; i < attribCount; ++i) {
			glDeleteBuffers(1, &attribs[i].buffer);
		}

		// delete the vertex position attribute
		glDeleteBuffers(1, &vertexAttrib.buffer);

		// delete index buffer
		glDeleteBuffers(1, &ibo);

		// delete the whole thing
		glDeleteVertexArrays(1, &vao);
	}
	
	VAO::~VAO() {
		// memory manage the attributes
		for (auto i = 0; i < attribCount; ++i) {
			delete[] attribs[i].data;
		}
		delete[] attribs;

		// and the position attrib
		delete[] vertexAttrib.data;
	}

	/// actually draws this vao
	void VAO::render() {
		glBindVertexArray(vao);
		glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
	}

	/// internally adds a vertex attribute to this vao
		/// creates and returns the opengl buffer
	void VAO::add_attribute(Attribute& attrib, u32 location) {
		// make the attribute buffer current
		glBindBuffer(GL_ARRAY_BUFFER, attrib.buffer);

		// draw the float array from the attribute into the buffer
		glBufferData(GL_ARRAY_BUFFER, attrib.size, attrib.data, GL_STATIC_DRAW);

		// tell opengl where and how to use the data
		glVertexAttribPointer(location, attrib.perVertex, GL_FLOAT, false, 0, nullptr);

		// activate the attribute
		glEnableVertexAttribArray(location);
	}

}
