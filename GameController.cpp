#include "GameController.h"
#include "WindowController.h"
#ifdef USE_TOOL_WINDOW
    #include"MyForm.h"
#define USE_TOOL_WINDOW

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
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(0));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Camera setup
    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 0, 0, 5 }, { 0, 0, 0 }, { 0, 1, 0 }); // Camera at {0, 0, 5}

    screenWidth = WindowController::GetInstance().GetResolution().width;
    screenHeight = WindowController::GetInstance().GetResolution().height;

    projMatrix = camera.GetProjection();
    viewMatrix = camera.GetView();

    lastLightPosition = glm::vec3(0.0f, 0.0f, 4.0f);
    // Light setup
    light = new Mesh();
    light->Create(&shaderColor, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Sphere1.obj");  // Use sphere object for the light
    light->SetColor({ 3.0f, 1.0f, 1.0f });
    light->SetPosition(lastLightPosition);  // Light at {0, 0, 4}
    light->SetScalo({ 0.1f, 0.1f, 0.1f });
    light->SetSpecularStrength(4.0f);
    lights.push_back(light);

    // Suzanne with Hat Position (can use a custom model like "Monkey.obj" or another model)
    suzanne = new Mesh();
    suzanne->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Monkey.obj");
    suzanne->SetPosition({ 0.0f, 0.0f, 0.0f });
    suzanne->SetRotationObj({ 0.0f, 0.0f, 0.0f });
    suzanne->SetSpecularStrength(4.0f);
    meshes.push_back(suzanne);

    // Cube with Specular Strength and Color
    /*Mesh* sphere = new Mesh();
    sphere->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Sphere1.obj");
    sphere->SetPosition({ 0.0f, 0.0f, 0.0f });
    sphere->SetScalo({ 0.5f, 0.5f, 0.5f });
    sphere->SetColor({ 1.0f, 0.5f, 0.0f });  // Example color
    sphere->SetLightDirection({ 1.0f, 1.0f, 1.0f });
    //sphere->SetSpecularStrength(4.0f);
    meshes.push_back(sphere);
    Mesh* cube = new Mesh();
    cube->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Cube.obj");
    cube->SetPosition({ 0.0f, 0.0f, 0.0f });
    cube->SetScalo({ 1.0f, 1.0f, 1.0f });
    cube->SetColor({ 1.0f, 0.0f, 0.0f });  // Example color
    cube->SetLightDirection({ 1.0f, 1.0f, 1.0f });  // Set specular light direction
    meshes.push_back(cube);*/

}

void GameController::RunGame() {
    // Set up the shaders and window as usual
    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

    Font* arialFont = new Font();
    arialFont->Create(&shaderFont, "C:/Users/leana/source/repos/OpenGL/Assets/Fonts/arial.ttf", 48);

    // Initialize GameTime
    GameTime::GetInstance().Intialize();

    GLFWwindow* win = WindowController::GetInstance().GetWindow();

#ifdef USE_TOOL_WINDOW
    OpenGL::MyForm^ window = gcnew OpenGL::MyForm();
        window->Show();
#endif // USE_TOOL_WINDOW

    do {
        System::Windows::Forms::Application::DoEvents();

        GameTime::GetInstance().Update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            HandleMouseClick(win);
        }

        // Mouse input and other UI updates (as before)
        if (moveLight) {  // moveLight flag is set from the checkbox in MyForm
            double mouseX, mouseY;
            glfwGetCursorPos(win, &mouseX, &mouseY);  // Get mouse position
            UpdateObjToMouse(mouseX, mouseY);  // Update light position based on mouse

            std::string mousePositionText = "Mouse Position: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")";
            arialFont->RenderText(mousePositionText, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });
        }
        
        
        // Render lights
        for (auto light : lights) {
            light->Render(camera.GetProjection() * camera.GetView());
        }

        for (auto mesh : meshes) {
            if (mesh == light) {  // Exclude the light from being rendered again as a mesh
                mesh->Render(camera.GetProjection() * camera.GetView());
            }
        }
        if (clicked)
        {
            ResetLightPos();
            clicked = false;
        }
        // Continuous rotation for objects
        glm::vec3 rotationspeed = { 0.0f, 0.05f, 0.0f };  // Rotate 0.05 radians per frame around Y-axis
        for (auto mesh : meshes) 
        {
            if (mesh == suzanne) {
                // Accumulate rotation
                glm::vec3 currentRotation = mesh->GetRotation1();
                mesh->SetRotationObj(currentRotation + rotationspeed);

                // Update specular strength from trackbar (already assumed you have dynamic `specularStrength` value)
                mesh->SetSpecularStrength(specularStrength);

                // Render Suzanne
                mesh->Render(camera.GetProjection() * camera.GetView());
            }
        }

        glfwSwapBuffers(win);
        glfwPollEvents();

    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);

    // Cleanup
    for (auto light : lights) {
        light->Cleanup();
        delete light;
    }
    lights.clear();

    for (auto mesh : meshes) {
        mesh->Cleanup();
        delete mesh;
    }
    meshes.clear();

    shaderFont.Cleanup();
    shaderColor.Cleanup();
    shaderDiffuse.Cleanup();
}


// GameController.cpp
// Update the light position based on mouse movement
void GameController::UpdateObjToMouse(double mX, double mY)
{
    // Convert mouse position to Normalized Device Coordinates (NDC)
    float x = (2.0f * mX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mY) / screenHeight; // Invert Y-axis

    glm::vec4 ndcCoords = glm::vec4(x, y, 0.0f, 1.0f); // Z = 0 for the near plane

    // Unproject NDC coordinates to world space using camera's projection and view matrix
    glm::vec4 worldCoords = glm::inverse(projMatrix * viewMatrix) * ndcCoords;
    worldCoords /= worldCoords.w; // Perspective divide to normalize

    // Compute direction vector from camera to mouse position in world space
    glm::vec3 cameraPos = camera.GetPosition();
    glm::vec3 worldPos = glm::vec3(worldCoords);
    glm::vec3 rayDir = glm::normalize(worldPos - cameraPos);

    // Set a fixed depth (distance from camera)
    float depth = 7.0f; // You can adjust this value to control how far the light moves
    glm::vec3 targetPosition = cameraPos + rayDir * depth;

    // Apply an offset to move the light slightly to the right of the mouse position
    glm::vec3 offset = glm::vec3(0.3f, 0.0f, 0.0f); // Offset slightly to the right
    targetPosition += offset;

    // Update the light's position and store the new position
    if (light)
    {
        light->SetPosition(targetPosition);
        lastLightPosition = targetPosition;  // Store the updated position
    }
}



void GameController::ResetLightPos() {
    // Ensure the lastLightPosition has the correct values
    if (light) {
        std::cout << "Resetting light position to: "
            << lastLightPosition.x << ", "
            << lastLightPosition.y << ", "
            << lastLightPosition.z << std::endl; // Debug print

        light->SetPosition(lastLightPosition);  // Use the stored position
    }
}

void GameController::HandleMouseClick(GLFWwindow* window) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);  // Get mouse position

    // Convert mouse position to screen space coordinates
    float x = static_cast<float>(mouseX);
    float y = static_cast<float>(mouseY);
    glm::vec3 moveDirection(0.0f, 0.0f, 0.0f);
    float speed = 0.1f;  // Speed of light movement

    // Get screen width and height
    float screenWidth = static_cast<float>(WindowController::GetInstance().GetResolution().width);
    float screenHeight = static_cast<float>(WindowController::GetInstance().GetResolution().height);

    // Determine which quadrant of the screen was clicked
    if (x < screenWidth / 2 && y < screenHeight / 2) {  // Top-left quadrant
        moveDirection = glm::vec3(-1.0f, 1.0f, 0.0f);  // Move light to the top-left
    }
    else if (x >= screenWidth / 2 && y < screenHeight / 2) {  // Top-right quadrant
        moveDirection = glm::vec3(1.0f, 1.0f, 0.0f);  // Move light to the top-right
    }
    else if (x < screenWidth / 2 && y >= screenHeight / 2) {  // Bottom-left quadrant
        moveDirection = glm::vec3(-1.0f, -1.0f, 0.0f);  // Move light to the bottom-left
    }
    else if (x >= screenWidth / 2 && y >= screenHeight / 2) {  // Bottom-right quadrant
        moveDirection = glm::vec3(1.0f, -1.0f, 0.0f);  // Move light to the bottom-right
    }

    // Move the light based on the direction and how far into the quadrant you clicked
    moveDirection *= speed * glm::length(glm::vec3(x - screenWidth / 2, y - screenHeight / 2, 0.0f));
    lastLightPosition += moveDirection;

    // Update the light position
    light->SetPosition(lastLightPosition);
}


