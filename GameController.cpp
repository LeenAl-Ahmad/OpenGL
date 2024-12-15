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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    srand(time(0));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Camera setup
    camera.LookAt({ 0, 0, 5 }, { 0, 0, 0 }, { 0, 1, 0 }); // Camera at {0, 0, 5}

    screenWidth = WindowController::GetInstance().GetResolution().width;
    screenHeight = WindowController::GetInstance().GetResolution().height;

    projMatrix = camera.GetProjection();
    viewMatrix = camera.GetView();
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
    shaderPost = Shader();
    shaderPost.LoadShaders("pp.vertexshader", "pp.fragmentshader");

#pragma region Post processor
    pP = PostProcessor();
    pP.Create(&shaderPost);
#pragma endregion

#pragma region create
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
    suzanne->SetRotation({ 0.0f, 0.0f, 0.0f });
    suzanne->SetScalo({ 1,1,1 });
    suzanne->SetSpecularStrength(specularStrength);
    meshes.push_back(suzanne);


    Mesh* fish = new Mesh();
    fish->Create(&shaderDiffuse, "C:/Users/leana/source/repos/OpenGL/Assets/Models/fish.ase");
    fish->Setanswer(waterScene);
    fish->Setfrequency(frequency);
    fish->setAmplitude(amplitude);
    fish->SetPosition({ 0.0f, 0.0f, 0.0f });
    fish->SetScalo({ 1,1,1 });
    fish->SetSpecularStrength(specularStrength);
    meshes.push_back(fish);

    float currentTime = static_cast<float>(glfwGetTime());
    // mesh->SetTime(currentTime);
#pragma endregion

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

        pP.Start();

        float currentTime = (float)glfwGetTime();

        if (moveLight == true) {  // moveLight flag is set from the checkbox in MyForm
            double mouseX, mouseY;
            glfwGetCursorPos(win, &mouseX, &mouseY);  // Get mouse position
            UpdateObjToMouse(mouseX, mouseY, win, light);  // Update light position based on mouse

            std::string mousePositionText = "Mouse Position: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")";
            arialFont->RenderText(mousePositionText, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });
        }
        if (Transform)
        {
            double mouseX, mouseY;
            glfwGetCursorPos(win, &mouseX, &mouseY);
            UpdateObjToMouse(mouseX, mouseY, win, suzanne);  // Update light position based on mouse

            std::string mousePositionText = "Mouse Position: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")";
            arialFont->RenderText(mousePositionText, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });

        }
        if (waterScene)
        {
            // Update Suzanne and light positions
            if (suzanne) suzanne->SetPosition({ 5, 5, 5 });
            if (light) light->SetPosition({ 4, 4, 4 });
            camera.LookAt({ 0, 0, 50 }, { 0, 0, 0 }, { 0, 1, 0 }); // Camera at {0, 0, 5}

            glm::vec3 rotationSpeed = { 0,1,0 };
            for (auto fish : meshes) 
            {
                fish->Render(camera.GetProjection() * camera.GetView());
            }

        }
        if (space) {

        }
        else {
            // Normal rendering mode, use the default shader
            glUseProgram(shaderDiffuse.GetProgramID());  // Use the default diffuse shader for regular rendering
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
            light->ResetLightPos(light);
        }
        if (clickT)
        {
            suzanne->ResetObjPos(suzanne);
        }
        

        // Continuous rotation for objects
        glm::vec3 rotationspeed  { 0.0f, 5.0f, 0.0f };

        double t = GameTime::GetInstance().DeltaTime();
        for (auto mesh : meshes)
        {
            if (mesh == suzanne) {
                // Accumulate rotation
                
                mesh->SetRotation(mesh -> GetRotation() + (rotationspeed * (float)t));

                // Update specular strength from trackbar (already assumed you have dynamic `specularStrength` value)
                mesh->SetSpecularStrength(specularStrength);

                // Render Suzanne
                mesh->Render(camera.GetProjection() * camera.GetView());
            }
        }
        
        pP.End();

        glfwSwapBuffers(win);
        glfwPollEvents();

    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
    pP.Cleanup();
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

    shaderPost.Cleanup();
    shaderFont.Cleanup();
    shaderColor.Cleanup();
    shaderDiffuse.Cleanup();
}

void GameController::UpdateObjToMouse(double mX, double mY, GLFWwindow* window, Mesh* mesh)
{
    if (moveLight)
    {
        static bool mouseWasPressed = false; // Track the state of the mouse click

        // Check if the left mouse button is clicked (pressed)
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

            mouseWasPressed = true; // Mark the mouse as pressed

            // Convert mouse position to NDC
            float x = (2.0f * mX) / screenWidth - 1.0f;
            float y = 1.0f - (2.0f * mY) / screenHeight; // Flip Y-axis
            glm::vec4 ndcCoords = glm::vec4(x, y, 0.0f, 1.0f);

            // Transform NDC to world space
            glm::vec4 worldCoords = glm::inverse(projMatrix * viewMatrix) * ndcCoords;
            worldCoords /= worldCoords.w; // Normalize coordinates

            glm::vec3 cameraPos = camera.GetPosition();
            glm::vec3 worldPos = glm::vec3(worldCoords.x, worldCoords.y, 4.0f);
            glm::vec3 rayDir = glm::normalize(worldPos - cameraPos);

            // Fixed depth to determine new position
            float depth = 5.0f;  // Adjustable depth value
            glm::vec3 targetPosition = cameraPos + rayDir * depth;
            targetPosition.z = 4.0f;

            // Update the position of the mesh
            if (mesh == light) {
                glm::vec3 location = targetPosition;
                light->SetPosition(location); // Store the updated position
            }
            if (mesh == suzanne) {
                suzanne->SetPosition(targetPosition);
                lastObjPosition = targetPosition; // Store the updated position
            }

        }
        else {
            mouseWasPressed = false; // Reset the flag when the mouse button is released
        }
    }

    if (Transform) {
        static double prevMouseX = mX, prevMouseY = mY; // Track previous mouse position

        // Calculate mouse deltas
        double deltaX = mX - prevMouseX;
        double deltaY = mY - prevMouseY;

        // Update previous mouse position
        prevMouseX = mX;
        prevMouseY = mY;

        // Check which mouse button is pressed
        bool isLeftButtonPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
        bool isMiddleButtonPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

        // Modify transformation based on input
        if (isLeftButtonPressed) {
            // Manipulate translation, rotation, and scale on the XY axes
            if (translate) {
                glm::vec3 currentPosition = suzanne->GetPosition();
                glm::vec3 translation = glm::vec3(deltaX * 0.01f, -deltaY * 0.01f, 0.0f); // Adjust translation speed
                suzanne->SetPosition(currentPosition + translation);
            }
            if (rotate) {
                glm::vec3 currentRotation = suzanne->GetRotation();
                glm::vec3 rotation = glm::vec3(-deltaY * 0.1f, deltaX * 0.1f, 0.0f); // Rotate on XY
                suzanne->SetRotation(currentRotation + rotation);
            }
            if (scale) {
                glm::vec3 currentScale = suzanne->GetScale();
                float scaleChange = deltaY * 0.01f; // Scale on Y
                glm::vec3 newScale = currentScale + glm::vec3(scaleChange, scaleChange, 0.0f); // XY scaling
                newScale = glm::clamp(newScale, glm::vec3(0.1f), glm::vec3(10.0f)); // Clamp scale
                suzanne->SetScalo(newScale);
            }
        }

        if (isMiddleButtonPressed) {
            // Manipulate translation, rotation, and scale on the Z axis
            if (translate) {
                glm::vec3 currentPosition = suzanne->GetPosition();
                glm::vec3 translation = glm::vec3(0.0f, 0.0f, deltaY * 0.01f); // Adjust Z-axis translation speed
                suzanne->SetPosition(currentPosition + translation);
            }
            if (rotate) {
                glm::vec3 currentRotation = suzanne->GetRotation();
                glm::vec3 rotation = glm::vec3(0.0f, 0.0f, deltaY * 0.1f); // Rotate on Z
                suzanne->SetRotationObj(currentRotation + rotation);
            }
            if (scale) {
                glm::vec3 currentScale = suzanne->GetScale();
                float scaleChange = deltaY * 0.01f; // Scale on Z
                glm::vec3 newScale = currentScale + glm::vec3(0.0f, 0.0f, scaleChange); // Z scaling
                newScale = glm::clamp(newScale, glm::vec3(0.1f), glm::vec3(10.0f)); // Clamp scale
                suzanne->SetScalo(newScale);
            }
        }
    }
}


