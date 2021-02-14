#include "Shader.h"

Shader::Shader() : id(0)
{
}

void Shader::Load(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	// Compile shaders
	GLuint vertexShader = CompileShader(ShaderType::VERTEX, vertexShaderPath);
	GLuint fragmentShader = CompileShader(ShaderType::FRAGMENT, fragmentShaderPath);

	// Create program and link shaders
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	// Check program status
	GLint result = GL_FALSE;
	int infoLogLenght;
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLenght);
	if (infoLogLenght > 0)
	{
		vector<char> message(infoLogLenght + 1);
		glGetProgramInfoLog(id, infoLogLenght, NULL, &message[0]);
		cout << "Error while compiling shaders : " << message[0] << endl;
	}
	else { cout << "Shaders compiled sucessfully" << endl; }

	// Delete shaders
	glDetachShader(id, vertexShader);
	glDetachShader(id, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

GLuint Shader::CompileShader(ShaderType type, const char* path)
{
	// Create shader
	GLuint shader = (type == ShaderType::VERTEX ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER));
	
	// Load code
	string source;
	ifstream stream (path, ios::in);
	if (stream.is_open())
	{
		stringstream sstr;
		sstr << stream.rdbuf();
		source = sstr.str();
		stream.close();
	}
	else
	{
		cout << "Error while compiling shaders : Unable to open file at : " << path << endl;
		return 0;
	}

	// Compile code
	GLint result = GL_FALSE;
	int infoLogLength;

	char const* sourcePtr = source.c_str();
	glShaderSource(shader, 1, &sourcePtr, NULL);
	glCompileShader(shader);

	// Check shader compilation status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		vector<char> message(infoLogLength + 1);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &message[0]);
		cout << "Error while compiling shaders : Compilation failed : " << message[0] << endl;
	}

	return shader;
}

// Uniforms
void Shader::UniformTexture(Texture _texture)
{
	Bind();
	texture = _texture;
	texture.Bind();
}

void Shader::UniformMatrix4fv(const char* uniform, mat4 matrix)
{
	Bind();
	GLuint mvpUniform = glGetUniformLocation(id, uniform);
	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &matrix[0][0]);
}


void Shader::Bind()
{
	glUseProgram(id);
}

int Shader::GetId()
{
	return id;
}
