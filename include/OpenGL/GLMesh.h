#pragma once
/*

#include "Shader.h"
namespace AtomForge {

	struct Mesh_Quad {
		 float vertices[9] =
		{ 
		  -0.5f, -0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
		  0.0f,  0.5f, 0.0f
		};
	};

	struct Mesh_Cube_Lit {
		//std::vector<GLfloat> vertices = {
		std::vector<GLfloat> verticies = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};
		const int length = 288;
	};

	class Mesh {
	public:
		struct Vertex {
			// position
			glm::vec3 Position;
			// normal
			glm::vec3 Normal;
			// texCoords
			glm::vec2 TexCoords;
			// tangent
			glm::vec3 Tangent;
			// bitangent
			glm::vec3 Bitangent;
		};

		struct Texture {
			unsigned int id;
			std::string type;
			std::string path;
		};

		std::vector<Texture*>* textures;
		std::vector <unsigned int> indices;
		std::vector<Vertex> modelVerticies;
		//std::vector<GLfloat> vertices;
		//GLfloat vertices[]; //convert back to std::vector
		std::vector<GLfloat>* vertices;
		
		unsigned int Vao;
		unsigned int Vbo;
		unsigned int Ebo;

		void SetVerticies(std::vector<GLfloat>* thisVerticies){//std::vector<GLfloat> thisVerticies) {
			vertices = thisVerticies;
		}

		Mesh();
		Mesh(GLfloat thisVerticies[], const std::vector<unsigned int> thisIndices, std::vector<Texture>* thisTextures);
		void SetupMesh(unsigned int thisVAO, unsigned int thisVBO, unsigned int thisEBO);
		~Mesh();


		void Draw(const Shader shader);

		

		void SetVerticyCount(const int thisInt) {
			verticiesCount = thisInt;
		}
		int GetVerticyCount() {
			return verticiesCount;
		}

		

		unsigned int GetVAO() {
			
			return Vao;
		}

		void SetVAO(const unsigned int thisVAO) {
			Vao = thisVAO;
		}

		unsigned int GetVBO() {
			return Vbo;
		}

		void SetVBO(const unsigned int thisVBO) {
			Vbo = thisVBO;
		}
		
		void SetEBO(const unsigned int thisEBO) {
			Ebo = thisEBO;
		}

		unsigned int GetEBO() {
			return Ebo;
		}

		Texture* GetDefaulTexture() {
			return defaultTexture;
		}

		glm::vec3 GetPosition() {
			return position;
		}

		void SetPosition(glm::vec3 thisPosition) {
			position = thisPosition;
		}
		
		Texture* CreateTexture(std::string path);

		void SetDirtyFlag(const bool value) {
			dirtyFlag = value;
		}

		bool GetDirtyFlag() {
			return dirtyFlag;
		}
	private:
		int verticiesCount;
		glm::vec3 position;
		Texture* defaultTexture;
		bool dirtyFlag = true;
		

	};
}
*/