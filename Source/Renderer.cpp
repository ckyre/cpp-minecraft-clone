#include "Renderer.h"

GLFWwindow* Renderer::window;
GLuint Renderer::program;
int Renderer::windowWidth;
int Renderer::windowHeight;

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

    // Ouvre une fenêtre
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
    }

    // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void Renderer::Start()
{
	program = LoadShaders("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Source/Shaders/vDefault.glsl",
		        "E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Source/Shaders/fDefault.glsl");
}

void Renderer::Update()
{
	// Bind shader
	glUseProgram(program);

	// Calculate matrices
	mat4 proj = glm::perspective(radians(45.0f), float(windowWidth/windowHeight), 0.1f, 100.0f);
	mat4 view = glm::lookAt(vec3(4, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 model = mat4(1.0f);

	mat4 mvp = proj * view * model;

	// Send mvp to shader
	GLuint mvpUniform = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvp[0][0]);

    // VOA
    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // VB
    static const GLfloat vertices[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Send data to VB
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Layout
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
}

void Renderer::End()
{
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
		getchar();
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
