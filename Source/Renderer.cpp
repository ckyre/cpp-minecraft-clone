#include "Renderer.h"

bool Renderer::openglReady = false;
GLFWwindow* Renderer::window;
GLFWmonitor* Renderer::monitor;
int Renderer::windowWidth, Renderer::windowHeight, Renderer::monitorWidth, Renderer::monitorHeight;
Camera Renderer::camera;

// Initalization
void Renderer::PrepareOpenGL()
{
	if (!openglReady)
	{
		// Initalise GLFW
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
		}

		// OpenGL hints
		glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
	}

	// Define default vertex buffer layout
	vector<VertexBufferComponent> defaultLayout;
	defaultLayout.push_back(VertexBufferComponent(GL_FLOAT, 3, GL_FALSE));
	defaultLayout.push_back(VertexBufferComponent(GL_FLOAT, 2, GL_FALSE));
	VertexBufferLayout::defaultLayout = defaultLayout;
}

void Renderer::CreateWindow(int width, int height, const char* title)
{
	if (!openglReady)
	{
		windowWidth = width;
		windowHeight = height;

		// Ouvre une fenêtre et la centre
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
		{
			fprintf(stderr, "Failed to open GLFW window.\n");
			glfwTerminate();
		}
		monitor = glfwGetPrimaryMonitor();
		monitorWidth = glfwGetVideoMode(monitor)->width;
		monitorHeight = glfwGetVideoMode(monitor)->height;
		glfwSetWindowPos(window, (monitorWidth / 2) - (windowWidth / 2), (monitorHeight / 2) - (windowHeight / 2));

		// Créer un contexte OpenGL
		glfwMakeContextCurrent(window);

		// Initalise GLEW
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			fprintf(stderr, "Failed to initialize GLEW\n");
		}

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glfwSetCursorPos(window, (double)(windowWidth / 2), (double)(windowHeight / 2)); // Place cursor at center

		openglReady = true;
		cout << "[OpengGL] initialization succeeded : " << glGetString(GL_VERSION) << endl;
	}
}

// Rendering
void Renderer::Clear()
{
	if (openglReady)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	}
}

void Renderer::Draw(Mesh mesh, Shader shader)
{
	if (openglReady)
	{
		camera.computeMatrices();

		shader.Bind();
		mat4 mvp = CalculateMVP();
		shader.UniformMatrix4fv("mvp", mvp);

		mesh.Bind();

		glDrawArrays(GL_TRIANGLES, 0, mesh.GetSize());
	}
}

mat4 Renderer::CalculateMVP()
{
	mat4 model = mat4(1.0f);
	return (camera.getProjMatrix() * camera.getViewMatrix() * model);
}
