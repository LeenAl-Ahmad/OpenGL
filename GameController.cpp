#include "GameController.h"
#include "WindowController.h"
#ifdef USE_Tool_WINDOW
    #include "ToolWindow.h"
#endif // USE_Tool_WINDOW
#include "Font.h"

void GameController::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_O)
    srand(time(0));

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 5,5,5 }, { 0,0,0 }, { 0,1,0 });
}

void GameController::RunGame() 
{
#ifdef USE_TOOL_WINDOW
    OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
    if (showToolWindows)
    {
        window->Show();
    }
#endif // USE_TOOL_WINDOW

#pragma region Shader Setup
    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
    //shaderSkybox = Shader();
    //shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");
#pragma endregion

#pragma region Model setup
        Mesh* light = new Mesh();
        light->Create(&shaderColor, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Sphere1.obj");
        light->SetColor({ 1.0f, 1.0f, 1.0f});
        light->SetScalo({0.1f, 0.1f, 0.1f});
        light->SetPosition({ 3.0f, 1.0f, 0.0f });
        lights.push_back(light);
    
        
        Mesh* box = new Mesh();
        box->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Monkey.obj");
        box->SetCameraPosition(camera.GetPosition());
        box->SetScalo({ 1.0f, 1.0f, 1.0f });
        box->SetPosition({0.0f, 0.0f, 0.0f});
        meshBoxes.push_back(box);
        Mesh* box1 = new Mesh();
        box1->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Cube.obj");
        box1->SetCameraPosition(camera.GetPosition());
        box1->SetScalo({ 1.0f, 1.0f, 1.0f });
        box1->SetPosition({ 0.0f, 0.0f, 0.0f });
        meshBoxes.push_back(box1);
#pragma endregion 

        Font arialFont = Font();
        arialFont.Create(&shaderFont, "C:/Users/leana/source/repos/OpenGL/Assets/Fonts/arial.ttf", 100);

    GLFWwindow* win = WindowController::GetInstance().GetWindow(); 

        do
        {
#pragma region Winfrom (ifdef USE_TOOL_WINDOW used)
#ifdef USE_TOOL_WINDOW
            System::Windows::Forms::Applicatioin::DoEvents();

            GLuint loc = 0;
            loc = glGetUniformLocation(shader.GetProgramID(), "RenderRedChannel");
            glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
            loc = glGetUniformLocation(shader.GetProgramID(), "RenderGreenChannel");
            glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
            loc = glGetUniformLocation(shader.GetProgramID(), "RenderBLueChannel");
            glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);
#endif
#pragma endregion
            // Clear screen and render
            glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/ );

            //camera.Rotate();
            //glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
            //skybox->Render(camera.GetProjection() * view);
        
            for (auto light : lights)
            {
                light->Render(camera.GetProjection() * camera.GetView());
            }
            glm::vec3 rotationspeed = { 0.0f, 0.005f, 0.0f };
            for (auto box : meshBoxes)
            {
                box->SetRotation( box->GetRotation()+ rotationspeed);
                box->Render(camera.GetProjection() * camera.GetView());
                box1->Render(camera.GetProjection() * camera.GetView());
            }
            
            arialFont.RenderText("Hello World", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });
            glfwSwapBuffers(win);
            glfwPollEvents();

        }while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(win) == 0);

    for (auto light : lights)
    {
        light->Cleanup();
        delete light;
    }
    
    for (auto box : meshBoxes)
    {
        box->Cleanup();
        delete box;
    }
    
    shaderFont.Cleanup();
    shaderColor.Cleanup();
    shaderDiffuse.Cleanup();
}


