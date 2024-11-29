#include "GameController.h"
#include "WindowController.h"
#ifdef USE_Tool_WINDOW
    #include "ToolWindow.h"
#endif // USE_Tool_WINDOW
#include "Font.h"
#include "GameClass.h"

void GameController::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
        light->SetColor({1.0f, 1.0f, 1.0f});
        light->SetScalo({0.1f, 0.1f, 0.1f});
        light->SetPosition({ 0.0f, 0.8f, 1.0f });
        lights.push_back(light);
    
        
       /**Mesh* mesh = nullptr;
        mesh = new Mesh();
        mesh->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Fighter.obj");
        mesh->SetCameraPosition(camera.GetPosition());
        mesh->SetScalo({ 0.002f, 0.002f, 0.002f });
        mesh->SetPosition({0.0f, 0.0f, 0.0f});
        meshes.push_back(mesh);*/ 
#pragma region Cube
        Mesh* mesh = new Mesh();
        mesh->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Cube.obj");
        mesh->SetCameraPosition(camera.GetPosition());
        mesh->SetScalo({ 1.0f, 1.0f, 1.0f });
        mesh->SetPosition({ 0.0f, 0.0f, 0.0f });
        meshes.push_back(mesh);
#pragma endregion 

        Font* arialFont = new Font();
        arialFont->Create(&shaderFont, "C:/Users/leana/source/repos/OpenGL/Assets/Fonts/arial.ttf", 100);

/*
#pragma region Skybox Setup
        skybox = new SkyBox();
        skybox->Create(&shaderSkybox, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Skybox.obj", 
            { "C:/Users/leana/source/repos/OpenGL/Assets/Textures/Skybox/right.jpg", 
            "C:/Users/leana/source/repos/OpenGL/Assets/Textures/Skybox/left.jpg", 
            "C:/Users/leana/source/repos/OpenGL/Assets/Textures/Skybox/top.jpg", 
            "C:/Users/leana/source/repos/OpenGL/Assets/Textures/Skybox/bottom.jpg", 
            "C:/Users/leana/source/repos/OpenGL/Assets/Textures/Skybox/front.jpg", 
            "C:/Users/leana/source/repos/OpenGL/Assets/Textures/Skybox/back.jpg"});
#pragma endregion*/
        GameTime::GetInstance().Intialize();
    GLFWwindow* win = WindowController::GetInstance().GetWindow(); 

        do
        {
            GameTime::GetInstance().Update();
            // Clear screen and render
            glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

            //camera.Rotate();
            //glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
            //skybox->Render(camera.GetProjection() * view);

            for (auto light : lights)
            {
                light->Render(camera.GetProjection() * camera.GetView());
            }

            glm::vec3 rotationspeed = { 0.0f, 0.05f, 0.0f };
            for (auto mesh : meshes)
            {
                mesh->SetRotation(mesh->GetRotation() + rotationspeed);
                mesh->Render(camera.GetProjection() * camera.GetView());
            }

            arialFont->RenderText(std::to_string(GameTime::GetInstance().Fps()), 100, 100, 0.5f, {1.0f, 1.0f, 0.0f});

            glfwSwapBuffers(win);
            glfwPollEvents();

        }

        while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);

    for (auto light : lights)
    {
        light->Cleanup();
        delete light;
    }
    
    for (auto box : meshes)
    {
        box->Cleanup();
        delete box;
    }
    
    shaderFont.Cleanup();
    shaderColor.Cleanup();
    shaderDiffuse.Cleanup();
}


