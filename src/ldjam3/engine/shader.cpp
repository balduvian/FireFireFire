
#include <filesystem>
#include <fstream>
#include <iostream>

#include "shader.h"

#include "transform.h"

namespace FFF {

	/// constructs the shader
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	: Resource(true), program(), vertexPath(vertexPath), fragmentPath(fragmentPath), vertexData(nullptr), fragmentData(nullptr), modelLocation(), projviewLocation() {}

	void Shader::customGather() {
		auto readFile = [](const char* path) {
			auto filePath = std::filesystem::path(path);

			if (!std::filesystem::exists(filePath))
				throw "this shader file does not exist";

			// get the size of the file in bytes
			// add a byte at the end for the null character
			auto size = (GLint)std::filesystem::file_size(filePath) + 1;

			// create the buffer
			// which will be a single line of text essentially
			auto buffer = new char[size];

			// a pointer to buffer that can iterate
			auto buf_ptr = buffer - 1;

			auto file = std::ifstream{};

			file.open(filePath);

			// read the whole file into buffer
			while (file.good())
				*++buf_ptr = file.get();

			// add null character
			*buf_ptr = NULL;

			// close file reading
			file.close();

			return buffer;
		};

		vertexData = readFile(vertexPath);
		fragmentData = readFile(fragmentPath);
	}

	void Shader::customProcess() {
		auto loadShader = [](char* data, int type) -> u32 {
			auto shader = glCreateShader(type);

			// put the shader into opengl
			glShaderSource(shader, 1, &data, nullptr);
			glCompileShader(shader);

			// see if the shader is properly compiled
			GLint status;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

			if (status != GL_TRUE)
			{
				// create a buffer for the info log
				constexpr auto err_size = 256;
				char err_buffer[err_size];

				int len_return;
				glGetShaderInfoLog(shader, err_size, &len_return, err_buffer);

				std::cout << err_buffer << std::endl;

				throw err_buffer;
			}

			return shader;
		};

		program = glCreateProgram();

		GLint vertex_shader;
		GLint fragment_shader;

		vertex_shader = loadShader(vertexData, GL_VERTEX_SHADER);
		fragment_shader = loadShader(fragmentData, GL_FRAGMENT_SHADER);

		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);

		glDetachShader(program, vertex_shader);
		glDetachShader(program, fragment_shader);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		// load base uniforms
		modelLocation = getUniform(MODEL_NAME);
		projviewLocation = getUniform(PROJVIEW_NAME);

		// now load custom uniforms
		getUniforms();
	}

	void Shader::customUnload() {
		glDeleteProgram(program);
	}

	void Shader::customDiscard() {
		delete[] vertexData;
		delete[] fragmentData;
	}

	/*
	 * use
	 */

	/// getter
	int Shader::getUniform(const char* _name) {
		return glGetUniformLocation(program, _name);
	}

	/// start using this shader
	/// after calling this then give other things
	void Shader::enable(f32 model[], f32 projview[]) {
		glUseProgram(program);

		giveMatrix4(modelLocation, model);
		giveMatrix4(projviewLocation, projview);
	}

	void Shader::enable() {
		glUseProgram(program);

		giveMatrix4(modelLocation, Transform::defaultModel);
		giveMatrix4(projviewLocation, Transform::defaultProjview);
	}

	/*
	 * GIVERS
	 */

	void Shader::giveFloat(int location, float x) {
		glUniform1f(location, x);
	}

	void Shader::giveVector2(int location, float x, float y) {
		glUniform2f(location, x, y);
	}

	void Shader::giveVector3(int location, float x, float y, float z) {
		glUniform3f(location, x, y, z);
	}

	void Shader::giveVector4(int location, float x, float y, float z, float w) {
		glUniform4f(location, x, y, z, w);
	}

	void Shader::giveVector4(int location, float values[]) {
		glUniform4fv(location, 1, values);
	}

	void Shader::giveMatrix4(int location, float values[]) {
		glUniformMatrix4fv(location, 1, false, values);
	}

	Shader::~Shader() {
		unload();
	}
}
