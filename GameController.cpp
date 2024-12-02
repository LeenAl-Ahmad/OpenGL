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
    glDisable(GL_CULL_FACE);
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
    light->SetColor({ red,green,blue });
    light->SetRed(red);
    light->SetGreen(green);
    light->SetBlue(blue);
    light->SetPosition(lastLightPosition);  // Light at {0, 0, 4}
    light->SetScalo({ 0.1f, 0.1f, 0.1f });
    light->SetSpecularStrength(4.0f);
    lights.push_back(light);

    // Suzanne with Hat Position (can use a custom model like "Monkey.obj" or another model)
    suzanne = new Mesh();
    suzanne->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Monkey.obj");
    suzanne->SetPosition({ 0.0f, 0.0f, 0.0f });
    suzanne->SetRotationObj({ 0.0f, 0.0f, 0.0f });
    //suzanne->SetColor({});
    suzanne->SetSpecularStrength(specularStrength);
    meshes.push_back(suzanne);

    sphere = new Mesh();
    sphere->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Sphere1.obj");
    sphere->SetPosition({ 0.0f, 0.0f, 0.0f });
    sphere->SetScalo({ 0.5f, 0.5f, 0.5f });
    sphere->SetColor({ 1.0f, 0.5f, 0.0f }); // Example color
    sphere->SetLightDirection({ 1.0f, 1.0f, 1.0f });
    meshes.push_back(sphere);

    int cubeCount = glm::linearRand(10, 20); // Random number of cubes
    for (int i = 0; i < cubeCount; ++i) {
        glm::vec3 randomOffset = glm::vec3(
            glm::linearRand(-5.0f, 5.0f),
            glm::linearRand(-5.0f, 5.0f),
            glm::linearRand(-5.0f, 5.0f)
        );
        glm::vec3 cubePosition = sphere->GetPosition() + randomOffset;
        newCube = new Mesh();
        newCube->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/Cube.obj");
        newCube->SetPosition(cubePosition);
        newCube->SetScalo({ 0.5f, 0.5f, 0.5f });
        newCube->SetLightDirection({ 1.0f, 1.0f, 1.0f });
        meshes.push_back(newCube);
        cubes.push_back(newCube); // Track cubes
    }
    
}

void GameController::RunGame() {
    // Set up the shaders and window as usual
    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
    shaderPixel = Shader();
    //shaderPixel.LoadShaders("pixel.vertexShader", "pixel.fragmentshader");

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

        float currentTime = (float)glfwGetTime();


        if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            HandleMouseClick(win);
        }

        if (moveLight) {  // moveLight flag is set from the checkbox in MyForm
            double mouseX, mouseY;
            glfwGetCursorPos(win, &mouseX, &mouseY);  // Get mouse position
            UpdateObjToMouse(mouseX, mouseY);  // Update light position based on mouse

            std::string mousePositionText = "Mouse Position: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")";
            arialFont->RenderText(mousePositionText, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });
        }
        if (colorPosition) {  // moveLight flag is set from the checkbox in MyForm
            suzanne->SetcolorPos(colorPosition);

            // Handle mouse click and update the object position
            double mouseX, mouseY;
            glfwGetCursorPos(win, &mouseX, &mouseY);
            UpdateObj(mouseX, mouseY);

            // Render text showing the mouse position (optional)
            std::string mousePositionText = "Mouse Position: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")";
            arialFont->RenderText(mousePositionText, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });
            
        }
        else {
            // Normal rendering mode, use the default shader
            glUseProgram(shaderDiffuse.GetProgramID());  // Use the default diffuse shader for regular rendering
        }
        
        if (moveCube)
        {
            UpdateScene(win, cube);
            if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                HandleMouseClick(win);
            }
        }
        if (UpdatedRed || UpdatedGreen || UpdatedBlue) {
            light->SetColor({ red, green, blue });
        }
        // Render lights
        for (auto light : lights) {
            light->Render(camera.GetProjection() * camera.GetView());
        }

        for (auto mesh : meshes) {
            if (mesh == light) {
                mesh->Render(camera.GetProjection() * camera.GetView());
            }
            
        }
        if (clickL)
        {
            if(light){
                ResetLightPos();
            }
            
        }
        if (clickO)
        {
            if (suzanne)
            {
                ResetObjPos();
            }

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
    glm::vec3 offset = glm::vec3(0.3f, 0.0f, 3.0f); // Offset slightly to the right
    targetPosition += offset;

    // Update the light's position and store the new position
    if (light)
    {
        light->SetPosition(targetPosition);
        lastLightPosition = targetPosition;  // Store the updated position
    }
    
}

void GameController::UpdateObj(double mX, double mY) {
    // Convert mouse position to NDC
    float x = (2.0f * mX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mY) / screenHeight;  // Flip Y-axis

    glm::vec4 ndcCoords = glm::vec4(x, y, 0.0f, 1.0f);

    // Transform NDC to world space
    glm::vec4 worldCoords = glm::inverse(projMatrix * viewMatrix) * ndcCoords;
    worldCoords /= worldCoords.w;  // Normalize coordinates

    glm::vec3 cameraPos = camera.GetPosition();
    glm::vec3 worldPos = glm::vec3(worldCoords);
    glm::vec3 rayDir = glm::normalize(worldPos - cameraPos);

    // Fixed depth to determine new position
    float depth = 7.0f;  // Adjustable depth value
    glm::vec3 targetPosition = cameraPos + rayDir * depth;

    if (suzanne) {
        suzanne->SetPosition(targetPosition);
        lastObjPosition = targetPosition;  // Store updated position
    }
}

void GameController::UpdateScene(GLFWwindow* window, Mesh* NewCube) {
    static bool isMousePressed = false; // Tracks the mouse button state

    // Update Suzanne and light positions
    if (suzanne) suzanne->SetPosition({ 5, 5, 5 });
    if (light) light->SetPosition({ 4, 4, 4 });

    // Render the sphere
    if (sphere) {
        sphere->Render(camera.GetProjection() * camera.GetView());
    }

    // Check for left mouse button click
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!isMousePressed) { // Only trigger on a fresh press
            isMousePressed = true;

            glm::vec3 randomOffset = glm::vec3(
                glm::linearRand(-5.0f, 5.0f),
                glm::linearRand(-5.0f, 5.0f),
                glm::linearRand(-5.0f, 5.0f)
            );

            // Spawn a new cube
            glm::vec3 cubePosition = sphere->GetPosition() + randomOffset;
            newCube = new Mesh(); // Create a new cube instance
            newCube->SetPosition(cubePosition);
            cubes.push_back(newCube); // Add new cube to the list
        }
    }
    else {
        isMousePressed = false; // Reset when the button is released
    }

    // Update and render all cubes
    auto it = cubes.begin();
    while (it != cubes.end()) {
        Mesh* cube = *it;

        // Move the cube toward the sphere
        glm::vec3 direction = glm::normalize(sphere->GetPosition() - cube->GetPosition());
        glm::vec3 newPosition = cube->GetPosition() + direction * cubeSpeed * deltaTime;
        cube->SetPosition(newPosition);
        cube->Render(camera.GetProjection() * camera.GetView());

        // Check if the cube reaches the sphere's center
        if (glm::length(newPosition - sphere->GetPosition()) <= sphereRadius) {
            delete cube;  // Clean up memory
            it = cubes.erase(it); // Remove cube from the list
        }
        else {
            ++it;
        }
    }

    // Optional: Display the current number of cubes
    std::cout << "Cubes remaining: " << cubes.size() << std::endl;
}



bool GameController::ResetObjPos() {
    if (suzanne) {
        suzanne->SetPosition({0,0,0}); 
        return clickO = false;
    }
}


bool GameController::ResetLightPos() {
    // Ensure the lastLightPosition has the correct values
    if (light) {
        light->SetPosition({0,0,4});
        return clickL = false;
    }
}


void GameController::HandleMouseClick(GLFWwindow* window) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);  // Get mouse position

    // Convert mouse position to normalized device coordinates (NDC)
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;  // Invert Y-axis
    glm::vec4 ndcCoords = glm::vec4(x, y, 0.0f, 1.0f);

    // Determine quadrant and adjust light position
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    glm::vec3 direction = glm::normalize(light->GetPosition() - glm::vec3(centerX, centerY, 0.0f));
    float distance = glm::distance(glm::vec2(mouseX, mouseY), glm::vec2(centerX, centerY));
    float maxDistance = glm::distance(glm::vec2(0, 0), glm::vec2(screenWidth, screenHeight));
    float speedFactor = (distance / maxDistance);  // Calculate speed based on distance

    if (mouseX < centerX && mouseY > centerY) {
        // Top-left
        light->SetPosition(light->GetPosition() + direction * speedFactor);
    }
    else if (mouseX >= centerX && mouseY > centerY) {
        // Top-right
        light->SetPosition(light->GetPosition() + direction * speedFactor);
    }
    else if (mouseX < centerX && mouseY <= centerY) {
        // Bottom-left
        light->SetPosition(light->GetPosition() + direction * speedFactor);
    }
    else {
        // Bottom-right
        light->SetPosition(light->GetPosition() + direction * speedFactor);
    }
}
