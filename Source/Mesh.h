#include <iostream>
#include <vector>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace Assimp;
#include <glm/glm.hpp>
using namespace glm;
#pragma once
class Mesh
{
	public:
		Mesh(const char* path);
		bool Load(const char* path);

		GLfloat* GetVerticesPositions();
		GLfloat* GetVerticesUVs();
		GLfloat* GetVerticesNormals();
		int GetPositionsCount();
		int GetUVsCount();
	private:
		vector<GLfloat> positions;
		vector<GLfloat> uvs;
		vector<GLfloat> normals;

		void Clear();

};

