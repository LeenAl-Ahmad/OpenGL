#include "GameController.h"
#include "WindowController.h"
#include "MyForm.h"

GameController::GameController()
{
	// Could initialize the shader and mesh objects if required
	shader = {};
	mesh = {};
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	OpenGL::MyForm^ window = gcnew OpenGL::MyForm;
	window->Show();
	
	

	shader = Shader();
	shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	mesh = Mesh();
	mesh.Create(&shader);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		System::Windows::Forms::Application::DoEvents();
		GLint loc = 0;
		loc = glGetUniformLocation(shader.GetProgramID(), "rendRed");
		glUniform1i(loc, (int)OpenGL::MyForm::rendRed);
		loc = glGetUniformLocation(shader.GetProgramID(), "rendGreen");
		glUniform1i(loc, (int)OpenGL::MyForm::rendGreen);
		loc = glGetUniformLocation(shader.GetProgramID(), "rendBlue");
		glUniform1i(loc, (int)OpenGL::MyForm::rendBlue);
		

		glClear(GL_COLOR_BUFFER_BIT);
		mesh.Render(camera.GetProjection()* camera.GetView());
		glfwSwapBuffers(win);
		glfwPollEvents();
	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);

	mesh.Cleanup();
	shader.Cleanup();
}

