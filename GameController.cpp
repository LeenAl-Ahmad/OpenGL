#include "GameController.h"
#include "WindowController.h"
#include "MyForm.h"
#include <chrono>

// Adding a small delay between key presses to avoid rapid changes
const float debounceTime = 0.2f; // 200ms delay between keypress actions
float lastCameraSwitchTime = 0;
float lastResolutionSwitchTime = 0;

GameController::GameController()
    : cameras{ Camera(Resolution(1024, 768, 45.0f)), Camera(Resolution(800, 600, 60.0f)), Camera(Resolution(1280, 720, 90.0f)) },
    resolutions{ Resolution(1024, 768, 45.0f), Resolution(800, 600, 60.0f), Resolution(1280, 720, 90.0f) },
    currentCameraIndex(0), currentResolutionIndex(0) {
    shader = {};
    mesh = {};

    // Setting unique camera positions to ensure visual difference
    cameras[0].SetPosition(glm::vec3(4, 3, 3));  // First camera position
    cameras[1].SetPosition(glm::vec3(0, 5, 5));  // Second camera position
    cameras[2].SetPosition(glm::vec3(-4, 3, 3)); // Third camera position
}

void GameController::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void GameController::RunGame() {
    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    shader = Shader();
    shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    mesh = Mesh();
    mesh.Create(&shader);

    while (!glfwWindowShouldClose(win)) {
        // Get the current time for debounce
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

        // Clear screen and render
        glClear(GL_COLOR_BUFFER_BIT);
        mesh.Render(cameras[currentCameraIndex].GetProjection() * cameras[currentCameraIndex].GetView());
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    mesh.Cleanup();
    shader.Cleanup();
}

void GameController::CyCamera() {
    // Cycle through the cameras array
    currentCameraIndex = (currentCameraIndex + 1) % cameras.size();

    // You could log the camera change here, if needed
    std::cout << "Switched to Camera " << currentCameraIndex + 1 << std::endl;
}

void GameController::CyResolution() {
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
}
