#include "GameController.h"
#include "WindowController.h"
#include "MyForm.h"
#include <chrono>

#include <vector>  // To store multiple NPCs
#include <cstdlib> 
#include <ctime> 

// Adding a small delay between key presses to avoid rapid changes
const float debounceTime = 0.2f; // 200ms delay between keypress actions
float lastCameraSwitchTime = 0;
float lastResolutionSwitchTime = 0;

GameController::GameController()
    : cameras{ 
        Camera(Resolution(1024, 768, 45.0f)), 
        Camera(Resolution(800, 600, 60.0f)), 
        Camera(Resolution(1280, 720, 90.0f)) },
    resolutions{ 
            Resolution(1024, 768, 45.0f), 
            Resolution(800, 600, 60.0f), 
            Resolution(1280, 720, 90.0f) 
        },
    currentCameraIndex(0),
    currentResolutionIndex(0) 
{
    shader = {};
    mesh = {};

    // Setting unique camera positions to ensure visual difference
    cameras[0].SetPosition(glm::vec3(0, 0, 50));
    
}

void GameController::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_CULL_FACE);

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 0, 0, 50 }, { 0,0,0 }, { 0,1,0 });

    // Seed the random generator
    std::srand((unsigned int)std::time(nullptr));

    for (int i = 0; i < 10; ++i) {
        Mesh npc;

        float angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f * 3.14159265358979323846f;

        // Generate a random radius between 2 and 10
        float radius = 2.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (10.0f - 2.0f)));

        // Calculate random X and Y positions around the player using the angle and radius
        float randomX = std::cos(angle) * radius; // X position based on angle and radius
        float randomY = std::sin(angle) * radius; // Y position based on angle and radius

        // Adjust Y position to ensure it falls within the range [-10, -2]
        randomY = std::max(randomY, -10.0f); // Ensure randomY is not below -10
        randomY = std::min(randomY, -2.0f);



        npc.CreateNPCS(&shader, 0.0f, 1.0f, 0.0f, 1.0f); // Create NPC with green color
        npc.isTagged = false;
        npc.Move(randomX, randomY); // Set the random position
        npcs.push_back(npc); // Store the NPC in the list
    }
    
    mesh.CreateNPCS(&shader, 0.0f, 1.0f, 0.0f, 1.0f);
    mesh.CreatePlayer(&shader);// The player is red
}

std::vector<Mesh> taggedNpcs;

void GameController::RunGame() {
    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    shader = Shader();
    shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    float moveSpeed = 0.005f;  // How fast the triangle moves
    float npcSpeed = 0.001f;
    float randomMoveRange = 0.0005f; // range of random movement applied to npc

    std::srand((unsigned int)std::time(nullptr));  // Seed the random generator

    while (!glfwWindowShouldClose(win)) {
        // Get the current time for debounce
        float currentTime = (float)glfwGetTime();

        // Movement logic (WASD keys)
        float moveX = 0.0f, moveY = 0.0f;
        if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
            moveX = -moveSpeed;  // Move left
        }
        if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
            moveX = moveSpeed;   // Move right
        }
        if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
            moveY = moveSpeed;   // Move up
        }
        if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
            moveY = -moveSpeed;  // Move down
        }

        // Update the triangle position
        mesh.Move(moveX, moveY);
       
        

        for (auto& npc : npcs) {
            glm::vec3 npcPosition = npc.GetPosition();    // Get the individual NPC's position
            glm::vec3 playerPosition = mesh.GetPosition(); // Get the player's position

            // Calculate the distance between the NPC and the player
            float distance = glm::length(npcPosition - playerPosition);

            glm::vec3 direction;  // Direction to move the NPC (away or towards)
            
            if (distance < 1.0f) {
                npc.isTagged = true;  // Tag the NPC
            }
            // Untag the NPC if player moves away
            
            if (npc.isTagged) {
                // Move tagged NPCs
                if (distance < 10.0f) {
                    // Move NPC away from the player
                    direction = glm::normalize(npcPosition - playerPosition);
                }
                else if (distance > 11.0f) {
                    // Move NPC towards the player
                    direction = glm::normalize(playerPosition - npcPosition);
                }

                npc.Move(direction * npcSpeed); // Apply movement

                // Always face the player
                float angle = std::atan2(playerPosition.y - npcPosition.y, playerPosition.x - npcPosition.x); // Calculate angle to the player
                float angleDegrees = glm::degrees(angle);
                npc.SetRotation(angleDegrees); // Set rotation to face the player
            }
            
            if (distance < 10.0f) {
                    // Move NPC away from the player
                    direction = glm::normalize(npcPosition - playerPosition);
                }
            else if (distance > 11.0f) {
                    // Move NPC towards the player
                    direction = glm::normalize(playerPosition - npcPosition);
                }
            npc.Move(direction * npcSpeed);

            float angle = std::atan2(playerPosition.y - npcPosition.y, playerPosition.x - npcPosition.x); // Calculate the angle in radians
            float angleDegrees = glm::degrees(angle) + 30.0f;
            npc.SetRotation(angleDegrees);

            // Apply small random movement
            float randomMoveX = (static_cast<float>(std::rand()) / RAND_MAX) * 2.0f * randomMoveRange - randomMoveRange;
            float randomMoveY = (static_cast<float>(std::rand()) / RAND_MAX) * 2.0f * randomMoveRange - randomMoveRange;
            npc.Move(glm::vec3(randomMoveX, randomMoveY, 0));  // Add random movement
        }
        
        // Clear screen and render the updated scene
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.Render(cameras[currentCameraIndex].GetProjection() * cameras[currentCameraIndex].GetView());
       
        Mesh taggedNpc;//creating a tagged npc 
        
        for (auto& npc : npcs) {
            if (npc.isTagged) {
                // Create and render the tagged NPC once
                Mesh taggedNpc;
                taggedNpc.CreateNPCS(&shader, 0.0f, 0.0f, 1.0f, 1.0f); // Create a blue tagged NPC
                taggedNpc.Move(npc.GetPosition());
                taggedNpc.Render(cameras[currentCameraIndex].GetProjection() * cameras[currentCameraIndex].GetView());
            }
            else {
                npc.Render(cameras[currentCameraIndex].GetProjection() * cameras[currentCameraIndex].GetView());
            }
        }

       

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
