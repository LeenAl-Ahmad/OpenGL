#include "GameController.h"
#include "WindowController.h"
#ifdef USE_Tool_WINDOW
    #include "ToolWindow.h"
#endif // USE_Tool_WINDOW



// Adding a small delay between key presses to avoid rapid changes
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
    camera.LookAt({ 1, 1, 1 }, { 0,0,0 }, { 0,1,0 });
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

    meshLight = new Mesh();
    meshLight->Create(&shaderColor);
    meshLight->SetPosition({ 0.5f, 0.0f, -0.5f });
    meshLight->SetScalo({ 0.1f, 0.1f, 0.1f });

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
            {
                Mesh* box = new Mesh();
                box->Create(&shaderDiffuse);
                box->SetLightColor({ 1.0f, 1.0f, 1.0f });
                box->SetLightPosition(meshLight->GetPosition());
                box->SetCameraPosition(camera.GetPosition());
                box->SetScalo({ 0.1f, 0.1f, 0.1f });
                box->SetPosition({ 0.0f, -0.5f +(float)row/10.0f, -0.2f + (float)col /10.0f});
                meshBoxes.push_back(box);
            }
    }
    

    GLFWwindow* win = WindowController::GetInstance().GetWindow();

    float rotationY = 0.0f; // Y-axis rotation angle
    float rotationX = 0.0f; // simalar x-axis
    float rotationSpeed = 0.1f; // Degrees per second

    while (!glfwWindowShouldClose(win)) {
#ifdef USE_TOOL_WINDOW
        System::Window::Forms::Application::DoEvents();

        GLuint loc = 0;
        loc = glGetUniformLocation(shader.GetProgramID(), "RenderRedChannel");
        glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
        loc = glGetUniformLocation(shader.GetProgramID(), "RenderGreenChannel");
        glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
        loc = glGetUniformLocation(shader.GetProgramID(), "RenderBlueChannel");
        glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);
#endif // USE_TOOL_WINDOW
        /*// Get the current time for debounce
        float currentTime = (float)glfwGetTime();

        // Poll for key input to switch cameras and resolutions
        if (glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS && currentTime - lastCameraSwitchTime > debounceTime) {
            CyCamera();
            lastCameraSwitchTime = currentTime; // Reset the debounce timer
        }
        if (glfwGetKey(win, GLFW_KEY_V) == GLFW_PRESS && currentTime - lastResolutionSwitchTime > debounceTime) {
            CyResolution();
            lastResolutionSwitchTime = currentTime; // Reset the debounce timer
        }
        if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
            rotationY += rotationSpeed * (float)glfwGetTime(); // Rotate left
        }
        if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
            rotationY -= rotationSpeed * (float)glfwGetTime(); // Rotate right
        }
        if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
            rotationX += rotationSpeed * (float)glfwGetTime(); // Rotate up
        }
        if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
            rotationX -= rotationSpeed * (float)glfwGetTime(); // Rotate down
        }*/
        /*float currentTime = (float)glfwGetTime();

        // Move camera position
        if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) {
            cameraPosition.z -= cameraSpeed; // Move forward
        }
        if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) {
            cameraPosition.z += cameraSpeed; // Move backward
        }
        if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS) {
            cameraPosition.x -= cameraSpeed; // Move left
        }
        if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            cameraPosition.x += cameraSpeed; // Move right
        }
        if (glfwGetKey(win, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
            cameraPosition.y += cameraSpeed; // Move up
        }
        if (glfwGetKey(win, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
            cameraPosition.y -= cameraSpeed; // Move down
        }

        // Adjust LookAt target
        if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
            lookAtTarget.y += cameraSpeed; // Look up
        }
        if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
            lookAtTarget.y -= cameraSpeed; // Look down
        }
        if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
            lookAtTarget.x -= cameraSpeed; // Look left
        }
        if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
            lookAtTarget.x += cameraSpeed; // Look right
        }

        // Update the camera view matrix
        camera.LookAt(cameraPosition, lookAtTarget, { 0.0f, 1.0f, 0.0f });*/
        

        
        // Clear screen and render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        meshLight->Render(camera.GetProjection() * camera.GetView());
        for (auto box : meshBoxes)
        {
            box->Render(camera.GetProjection() * camera.GetView());
        }
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    meshLight->Cleanup();
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

