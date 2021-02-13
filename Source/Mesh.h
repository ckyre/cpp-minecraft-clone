#include <iostream>
#include <vector>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
using namespace Assimp;
#include <glm.hpp>
using namespace glm;
#pragma once
class Mesh
{
	public:
		Mesh(const char* path);
		bool Load(const char* path);

		vector<vec3> GetVerticesPositions();
		vector<vec3> GetVerticesUVs();
		vector<vec3> GetVerticesNormals();
	private:
		vector<vec3> positions;
		vector<vec3> uvs;
		vector<vec3> normals;

};

