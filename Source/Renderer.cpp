#include "Renderer.h"

bool Renderer::openglReady = false;
GLFWwindow* Renderer::window;
GLFWmonitor* Renderer::monitor;
int Renderer::windowWidth, Renderer::windowHeight, Renderer::monitorWidth, Renderer::monitorHeight;

Mesh Renderer::defaultMesh;
Shader Renderer::defaultShader;

vector<Vertex> Renderer::topFace, Renderer::backFace, Renderer::frontFace, Renderer::bottomFace, Renderer::rightFace, Renderer::leftFace;

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
			cout << "[OpenGL] Failed to open GLFW window" << endl;
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
			cout << "[OpenGL] Failed to initialize GLEW" << endl;
		}

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glfwSetCursorPos(window, (double)(windowWidth / 2), (double)(windowHeight / 2)); // Place cursor at center

		// Create VOA
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		openglReady = true;
		cout << "[OpenGL] " << glGetString(GL_VERSION) << endl;
	}
}

void Renderer::LoadDefaultResources()
{
	// Define default vertex buffer layout
	vector<VertexBufferComponent> defaultLayout;
	defaultLayout.push_back(VertexBufferComponent(GL_FLOAT, 3, GL_FALSE));
	defaultLayout.push_back(VertexBufferComponent(GL_FLOAT, 2, GL_FALSE));
	VertexBufferLayout::defaultLayout = defaultLayout;

	// Default mesh
	Mesh mesh;
	mesh.Load("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/suzanne.obj");
	Renderer::defaultMesh = mesh;

	// Default shader
	Texture texture;
	texture.Load("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Textures/bricks.bmp");

	Shader shader;
	shader.Load("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Source/Shaders/vDefault.glsl",
		"E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Source/Shaders/fDefault.glsl");
	shader.UniformTexture(texture);
	Renderer::defaultShader = shader;

	// All faces
	topFace = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/top-face.obj");
	bottomFace = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/bottom-face.obj");
	frontFace = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/front-face.obj");
	backFace = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/back-face.obj");
	rightFace = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/right-face.obj");
	leftFace = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/left-face.obj");
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

		// Wireframe mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void Renderer::Draw(Mesh mesh, Shader shader, vec3 position)
{
	if (openglReady)
	{
		shader.Bind();
		mat4 modelMatrix = translate(mat4(1.0f), position);
		shader.UniformMatrix4fv("modelMatrix", modelMatrix);
		shader.UniformMatrix4fv("viewMatrix", Scene::camera.getViewMatrix());
		shader.UniformMatrix4fv("projMatrix", Scene::camera.getProjMatrix());

		mesh.Bind();

		glDrawElements(GL_TRIANGLES, mesh.GetIndexBufferCount(), GL_UNSIGNED_SHORT, (void*)0);
	}
}

