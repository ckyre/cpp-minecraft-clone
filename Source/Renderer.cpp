#include "Renderer.h"

GLFWwindow* Renderer::window;
GLFWmonitor* Renderer::monitor;
int Renderer::windowWidth;
int Renderer::windowHeight;
int Renderer::screenWidth;
int Renderer::screenHeight;

float Renderer::time;
float Renderer::deltaTime;

Camera Renderer::camera;

GLuint Renderer::program;
int Renderer::drawBufferSize;
float Renderer::lastTime;

Mesh Renderer::mesh("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/sphere.obj");

void Renderer::CreateWindow(int width, int height, const char* title)
{
	windowWidth = width;
	windowHeight = height;

    // OpenGL hints
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

    // Ouvre une fenêtre et la centre
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
    }

	monitor = glfwGetPrimaryMonitor();
	screenWidth = glfwGetVideoMode(monitor)->width;
	screenHeight = glfwGetVideoMode(monitor)->height;
	glfwSetWindowPos(window, (screenWidth/2) - (windowWidth/2), (screenHeight/2) - (windowHeight/2));

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

}

void Renderer::Start()
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glfwSetCursorPos(Renderer::window, (double)(Renderer::windowWidth / 2), (double)(Renderer::windowHeight / 2)); // Place cursor at center

	program = LoadShaders("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Source/Shaders/vDefault.glsl",
		                  "E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Source/Shaders/fDefault.glsl");

	// VOA
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Texture texture("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Textures/bricks.bmp");
}

void Renderer::Update()
{
	// Prepare frame
	// Mip maps settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Depth buffering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	// Update static time values
	time = (float)glfwGetTime();
	deltaTime = float(time - lastTime);
	// Update camera matrices
	camera.computeMatrices();

	drawBufferSize = 0;
	glUseProgram(program);

	// Load geometry and uniforms
	DrawCube(vec3(0, 0, 0));

	Buffer uvsBuffer(mesh.GetVerticesUVs(), mesh.GetUVsCount() * sizeof(GLfloat));
	drawBufferSize += mesh.GetUVsCount() * sizeof(GLfloat);
	glEnableVertexAttribArray(1); // UVs
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, drawBufferSize);

	// End frame
	lastTime = time;
}

void Renderer::End()
{
}

void Renderer::DrawCube(vec3 position)
{
	// Vertex buffer
	/*static GLfloat vertices[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};*/

	int size = mesh.GetPositionsCount() * sizeof(GLfloat);
	Buffer vertexBuffer(mesh.GetVerticesPositions(), size);

	// Layout
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	// MVP
	mat4 mvp = CalculateMVP(position);
	GLuint mvpUniform = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvp[0][0]);

	drawBufferSize += size;
}

mat4 Renderer::CalculateMVP(vec3 modelPosition)
{
	mat4 proj = glm::perspective(radians(45.0f), float(windowWidth / windowHeight), 0.1f, 100.0f);
	mat4 view = glm::lookAt(vec3(4, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 model = mat4(1.0f); // TODO : with modelPosition
	return (camera.getProjMatrix() * camera.getViewMatrix() * model);
}

GLuint Renderer::LoadShaders(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	//Create shaders
	GLuint vertexShader = CreateShader(VERTEX, vertexShaderPath);
	GLuint fragmentShader = CreateShader(FRAGMENT, fragmentShaderPath);

	// Link the program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Check the program status
	GLint result = GL_FALSE;
	int InfoLogLength;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

GLuint Renderer::CreateShader(Renderer::ShaderType type, const char* path)
{
	// Create shader
	GLuint shader = (type == VERTEX ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER));

	// Load source code
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
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", path);
		return 0;
	}

	// Compile source code
	GLint result = GL_FALSE;
	int InfoLogLength;

	char const* sourcePtr = source.c_str();
	glShaderSource(shader, 1, &sourcePtr, NULL);
	glCompileShader(shader);

	// Check shader compilation status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
	return shader;
}
