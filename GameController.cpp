#include "GameController.h"
#include "WindowController.h"
#ifdef USE_Tool_WINDOW
    #include "ToolWindow.h"
#endif // USE_Tool_WINDOW


const float debounceTime = 0.2f; // 200ms delay between keypress actions
float lastCameraSwitchTime = 0;
float lastResolutionSwitchTime = 0;

GameController::GameController()
    : cameras{ Camera(Resolution(1024, 768, 45.0f)), Camera(Resolution(800, 600, 60.0f)), Camera(Resolution(1280, 720, 90.0f)) },
    resolutions{ Resolution(1024, 768, 45.0f), Resolution(800, 600, 60.0f), Resolution(1280, 720, 90.0f) },
    currentCameraIndex(0), currentResolutionIndex(0) {
    shaderColor = {};
    shaderDiffuse = {};
    meshLight = {};
    meshBoxes = {};
    /*// Setting unique camera positions to ensure visual difference
    cameras[0].SetPosition(glm::vec3(0, 0, 10));  // First camera position
    cameras[1].SetPosition(glm::vec3(0, 10, 10));  // Second camera position
    cameras[2].SetPosition(glm::vec3(-10, 0, 10)); // Third camera position*/

}


void GameController::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    srand(time(0));

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 5, 5, 5 }, { 0,0,0 }, { 0,1,0 });
}

void GameController::RunGame() {
#ifdef USE_TOOL_WINDOW
    OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
    if (showToolWindows)
    {
        window->Show();
    }
#endif // USE_TOOL_WINDOW

    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    
        Mesh* light = new Mesh();
        light->Create(&shaderColor, "C:/Users/leana/source/repos/OpenGL/Assets/Models/untitled.obj");
        light->SetColor({1.0f, 1.0f, 1.0f});
        light->SetScalo({1.0f, 1.0f, 1.0f});
        light->SetPosition({ 3.0f, 1.0f, 0.0f });
        lights.push_back(light);
    

        Mesh* box = new Mesh();
        box->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/untitled.obj");
        box->SetCameraPosition(camera.GetPosition());
        box->SetScalo({ 1.0f, 1.0f, 1.0f });
        box->SetPosition({0.0f, 0.0f, 0.0f});
        meshBoxes.push_back(box);

    GLFWwindow* win = WindowController::GetInstance().GetWindow();

    float rotationY = 0.0f; // Y-axis rotation angle
    float rotationX = 0.0f; // simalar x-axis
    float rotationSpeed = 0.1f; // Degrees per second

        do
        {
            // Clear screen and render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

