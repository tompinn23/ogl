#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "glad/glad.h"
#include "glm.hpp"

#include "GLFW/glfw3.h"




void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

int create_vertex_shader(std::string vertexShaderSource)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* c_str = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &c_str, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::VERTEX_SHADER" << infoLog << "\n";
		return -1;
	}
	return vertexShader;
}

unsigned int create_frag_shader(std::string fragShaderSource)
{
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* c_str = fragShaderSource.c_str();
	glShaderSource(fragShader, 1, &c_str, NULL);
	glCompileShader(fragShader);
	int success;
	char infoLog[512];
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::FRAG_SHADER" << infoLog << "\n";
		return -1;
	}
	return fragShader;
}

class SpriteRenderer {
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void DrawSprite(Texture2D &texture, glm::vec2 position,
				glm::vec2 size, GLFloat rotate = 0.0f,
				glm::vec3 color = glm::vec3(1.0f));
	private:
		GLuint quadVAO;

		void initRenderData();
};


void SpriteRenderer::initRenderData()
{
	GLuint VBO;
	GLFloat vertices[] = {
		// POS      TEX
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position,
		glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	glm::mat4 model;

}

int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL,NULL);
	glfwMakeContextCurrent(window);
	if(window == NULL)
	{
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize opengl context\n";
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
		
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	
	std::ifstream v("shader.vs");
	std::ifstream f("shader.fg");

	std::string vertexSrc = std::string((std::istreambuf_iterator<char>(v)),
										 std::istreambuf_iterator<char>());
	std::string fragSrc = std::string((std::istreambuf_iterator<char>(f)),
										 std::istreambuf_iterator<char>());

	auto vertex = create_vertex_shader(vertexSrc);
	auto frag = create_frag_shader(fragSrc);

	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, frag);
	glLinkProgram(shaderProgram);


	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << "\n";
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

