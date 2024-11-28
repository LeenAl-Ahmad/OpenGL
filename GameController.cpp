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
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(0));

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 0,0,0 }, { 0,0,0 }, { 0,1,0 });
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
    shaderSkybox = Shader();
    shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");
#pragma endregion

#pragma region Model setup
        Mesh* light = new Mesh();
        light->Create(&shaderColor, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Sphere1.obj");
        light->SetColor({1.0f, 1.0f, 1.0f});
        light->SetScalo({1.0f, 1.0f, 1.0f});
        light->SetPosition({ 5.0f, 1.0f, 0.0f });
        lights.push_back(light);
    
        
        Mesh* box = new Mesh();
        box->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Cube.obj");
        box->SetCameraPosition(camera.GetPosition());
        box->SetScalo({ 1.0f, 1.0f, 1.0f });
        box->SetPosition({5.0f, 0.0f, 5.0f});
        meshBoxes.push_back(box);

        Mesh* plane = new Mesh();
        plane->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Plane.obj");
        plane->SetCameraPosition(camera.GetPosition());
        plane->SetScalo({ 1.0f, 1.0f, 1.0f });
        plane->SetPosition({ -1.0f, -1.0f, -1.0f });
        meshBoxes.push_back(plane);

        Mesh* windowMesh = new Mesh();
        windowMesh->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Window.obj");
        windowMesh->SetCameraPosition(camera.GetPosition());
        windowMesh->SetScalo({ 1.0f, 1.0f, 1.0f });
        windowMesh->SetPosition({ 0.0f, 0.0f, 0.0f });
        meshBoxes.push_back(windowMesh);
#pragma endregion 

        Font* arialFont = new Font();
        arialFont->Create(&shaderFont, "C:/Users/leana/source/repos/OpenGL/Assets/Fonts/arial.ttf", 100);

#pragma region Skybox Setup
        skybox = new SkyBox();
        skybox->Create(&shaderSkybox, "../Assets/Models/Skybox.obj", 
            { "../Assets/Textures/Skybox/right.jpg", 
            "../Assets/Textures/Skybox/left.jpg", 
            "../Assets/Textures/Skybox/top.jpg", 
            "../Assets/Textures/Skybox/bottom.jpg", 
            "../Assets/Textures/Skybox/front.jpg", 
            "../Assets/Textures/Skybox/back.jpg"});
#pragma endregion

    GLFWwindow* win = WindowController::GetInstance().GetWindow(); 

        do
        {
            // Clear screen and render
            glClear(GL_COLOR_BUFFER_BIT /* | GL_DEPTH_BUFFER_BIT*/);

            camera.Rotate();
            glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
            skybox->Render(camera.GetProjection() * view);

            for (auto light : lights)
            {
                light->Render(camera.GetProjection() * camera.GetView());
            }
            glm::vec3 rotationspead = { 0.0f, 0.005f, 0.0f };
            for (auto box : meshBoxes)
            {
                box->SetRotation1(box->GetRotation1() + rotationspead);
                box->Render(camera.GetProjection() * camera.GetView());
            }

            arialFont->RenderText("Hello World", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });
            glfwSwapBuffers(win);
            glfwPollEvents();

        }

        while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);

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
/*void GameController::CyCamera() {
    // Cycle through the cameras array
    currentCameraIndex = (currentCameraIndex + 1) % cameras.size();

    // You could log the camera change here, if needed
    std::cout << "Switched to Camera " << currentCameraIndex + 1 << std::endl;
}*/

/*void GameController::CyResolution() {
    // Cycle through the resolutions array
    currentResolutionIndex = (currentResolutionIndex + 1) % resolutions.size();

    // Re-initialize the cameras with the new resolution
    for (auto& camera : cameras) {
        camera.UpdateProjection(resolutions[currentResolutionIndex]);
    }

    std::cout << "Switched to Resolution: "
        << resolutions[currentResolutionIndex].width << "x"
        << resolutions[currentResolutionIndex].height << " FoV: "
        << resolutions[currentResolutionIndex].FoV << std::endl;
}*/

