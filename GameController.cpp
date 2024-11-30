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

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 5,5,5 }, { 0,0,0 }, { 0,1,0 });

    screenWidth = WindowController::GetInstance().GetResolution().width;
    screenHeight = WindowController::GetInstance().GetResolution().height;

    projMatrix = camera.GetProjection(); // Retrieve projection matrix from the camera
    viewMatrix = camera.GetView();       // Retrieve view matrix from the camera
}

void GameController::RunGame() 
{
    
#ifdef USE_TOOL_WINDOW
    OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
    window->Show();
    
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
        light = new Mesh();
        light->Create(&shaderColor, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Sphere1.obj");
        light->SetColor({3.0f, 1.0f, 1.0f});
        light->SetPosition({ 3.0f, 3.8f, 3.0f });
        light->SetScalo({ 0.1f, 0.1f, 0.1f });
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
        mesh->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Monkey.obj", 1);
        mesh->SetCameraPosition(camera.GetPosition());
        mesh->SetScalo({ 1.0f, 1.1f, 1.1f });
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
            System::Windows::Forms::Application::DoEvents();

           
            GameTime::GetInstance().Update();
            // Clear screen and render
            glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

            //mouse
            double mouseX, mouseY;
            glfwGetCursorPos(win, &mouseX, &mouseY);
            UpdateObjToMouse(mouseX, mouseY);

            // Convert mouse position to string
            std::string mousePositionText = "Mouse Position: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")";

            // Render mouse position on screen
            arialFont->RenderText(mousePositionText, 100, 100, 1.0f, { 1.0f, 1.0f, 0.0f });

            //camera.Rotate();
            //glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
            //mesh->Render(camera.GetProjection() * view);

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

void GameController::UpdateObjToMouse(double mX, double mY)
{
    // Convert mouse position to Normalized Device Coordinates (NDC)
    float x = (2.0f * mX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mY) / screenHeight; // Invert Y-axis

    glm::vec4 ndcCoords = glm::vec4(x, y, 0.0f, 1.0f); // Z = 0 for the near plane

    // Unproject NDC coordinates to world space
    glm::vec4 worldCoords = glm::inverse(projMatrix * viewMatrix) * ndcCoords;
    worldCoords /= worldCoords.w; // Divide by W for perspective correction

    // Compute direction vector from camera to mouse position in world space
    glm::vec3 cameraPos = camera.GetPosition();
    glm::vec3 worldPos = glm::vec3(worldCoords);
    glm::vec3 rayDir = glm::normalize(worldPos - cameraPos);

    // Set a fixed depth (distance from camera)
    float depth = 7.0f; // You can adjust this value to control distance
    glm::vec3 targetPosition = cameraPos + rayDir * depth;

    // Apply an offset to move the light slightly to the right
    glm::vec3 offset = glm::vec3(0.3f, 0.0f, 0.0f); // Offset 3 units to the right
    targetPosition += offset;

    // Update the light object's position
    if (light)
    {
        light->SetPosition(targetPosition);
    }
}




