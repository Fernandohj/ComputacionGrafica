//Practica 4                                                 Hernández Juárez Fernando 
//Fecha de entrega : 1 de marzo de 2026                      320115448

#include <iostream>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;

int main() {
    glfwInit();

    //Verificación de compatibilidad 
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico Hernandez Juarez Fernando", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    //Verificación de errores de creacion  ventana
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    //Verificación de errores de inicialización de glew
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define las dimensiones del viewport
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    // enable alpha support
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Build and compile our shader program
    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // ==============================================================================
    // ARREGLO DE VÉRTICES (Los 5 colores calibrados para el Squirtle Voxel)
    // ==============================================================================
    float vertices[] = {
        // =======================================================
        // CUBO 1: AZUL PASTEL (Cuerpo) - Índices 0 al 35
        // =======================================================
        // --- FRONT face (Z+) ---
        -0.5f, -0.5f,  0.5f,   0.59f, 0.80f, 0.92f,
         0.5f, -0.5f,  0.5f,   0.59f, 0.80f, 0.92f,
         0.5f,  0.5f,  0.5f,   0.59f, 0.80f, 0.92f,
         0.5f,  0.5f,  0.5f,   0.59f, 0.80f, 0.92f,
        -0.5f,  0.5f,  0.5f,   0.59f, 0.80f, 0.92f,
        -0.5f, -0.5f,  0.5f,   0.59f, 0.80f, 0.92f,
        // --- BACK face (Z-) ---
        -0.5f, -0.5f, -0.5f,   0.49f, 0.70f, 0.82f,
         0.5f, -0.5f, -0.5f,   0.49f, 0.70f, 0.82f,
         0.5f,  0.5f, -0.5f,   0.49f, 0.70f, 0.82f,
         0.5f,  0.5f, -0.5f,   0.49f, 0.70f, 0.82f,
        -0.5f,  0.5f, -0.5f,   0.49f, 0.70f, 0.82f,
        -0.5f, -0.5f, -0.5f,   0.49f, 0.70f, 0.82f,
        // --- RIGHT face (X+) ---
         0.5f, -0.5f,  0.5f,   0.54f, 0.75f, 0.87f,
         0.5f, -0.5f, -0.5f,   0.54f, 0.75f, 0.87f,
         0.5f,  0.5f, -0.5f,   0.54f, 0.75f, 0.87f,
         0.5f,  0.5f, -0.5f,   0.54f, 0.75f, 0.87f,
         0.5f,  0.5f,  0.5f,   0.54f, 0.75f, 0.87f,
         0.5f, -0.5f,  0.5f,   0.54f, 0.75f, 0.87f,
         // --- LEFT face (X-) ---
        -0.5f,  0.5f,  0.5f,   0.54f, 0.75f, 0.87f,
        -0.5f,  0.5f, -0.5f,   0.54f, 0.75f, 0.87f,
        -0.5f, -0.5f, -0.5f,   0.54f, 0.75f, 0.87f,
        -0.5f, -0.5f, -0.5f,   0.54f, 0.75f, 0.87f,
        -0.5f, -0.5f,  0.5f,   0.54f, 0.75f, 0.87f,
        -0.5f,  0.5f,  0.5f,   0.54f, 0.75f, 0.87f,
        // --- BOTTOM face (Y-) ---
       -0.5f, -0.5f, -0.5f,   0.39f, 0.60f, 0.72f,
        0.5f, -0.5f, -0.5f,   0.39f, 0.60f, 0.72f,
        0.5f, -0.5f,  0.5f,   0.39f, 0.60f, 0.72f,
        0.5f, -0.5f,  0.5f,   0.39f, 0.60f, 0.72f,
       -0.5f, -0.5f,  0.5f,   0.39f, 0.60f, 0.72f,
       -0.5f, -0.5f, -0.5f,   0.39f, 0.60f, 0.72f,
       // --- TOP face (Y+) ---
      -0.5f,  0.5f, -0.5f,   0.65f, 0.86f, 0.98f,
       0.5f,  0.5f, -0.5f,   0.65f, 0.86f, 0.98f,
       0.5f,  0.5f,  0.5f,   0.65f, 0.86f, 0.98f,
       0.5f,  0.5f,  0.5f,   0.65f, 0.86f, 0.98f,
      -0.5f,  0.5f,  0.5f,   0.65f, 0.86f, 0.98f,
      -0.5f,  0.5f, -0.5f,   0.65f, 0.86f, 0.98f,

      // =======================================================
      // CUBO 2: BLANCO (Ojos y Borde del caparazón) - Índices 36 al 71
      // =======================================================
      // --- FRONT face (Z+) --- (Blanco puro)
      -0.5f, -0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
       0.5f, -0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
       0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
       0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
      -0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
      -0.5f, -0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
      // --- BACK face (Z-) --- 
      -0.5f, -0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
       0.5f, -0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
       0.5f,  0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
       0.5f,  0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
      -0.5f,  0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
      -0.5f, -0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
      // --- RIGHT face (X+) --- 
       0.5f, -0.5f,  0.5f,   0.90f, 0.90f, 0.90f,
       0.5f, -0.5f, -0.5f,   0.90f, 0.90f, 0.90f,
       0.5f,  0.5f, -0.5f,   0.90f, 0.90f, 0.90f,
       0.5f,  0.5f, -0.5f,   0.90f, 0.90f, 0.90f,
       0.5f,  0.5f,  0.5f,   0.90f, 0.90f, 0.90f,
       0.5f, -0.5f,  0.5f,   0.90f, 0.90f, 0.90f,
       // --- LEFT face (X-) --- 
      -0.5f,  0.5f,  0.5f,   0.90f, 0.90f, 0.90f,
      -0.5f,  0.5f, -0.5f,   0.90f, 0.90f, 0.90f,
      -0.5f, -0.5f, -0.5f,   0.90f, 0.90f, 0.90f,
      -0.5f, -0.5f, -0.5f,   0.90f, 0.90f, 0.90f,
      -0.5f, -0.5f,  0.5f,   0.90f, 0.90f, 0.90f,
      -0.5f,  0.5f,  0.5f,   0.90f, 0.90f, 0.90f,
      // --- BOTTOM face (Y-) --- 
     -0.5f, -0.5f, -0.5f,   0.75f, 0.75f, 0.75f,
      0.5f, -0.5f, -0.5f,   0.75f, 0.75f, 0.75f,
      0.5f, -0.5f,  0.5f,   0.75f, 0.75f, 0.75f,
      0.5f, -0.5f,  0.5f,   0.75f, 0.75f, 0.75f,
     -0.5f, -0.5f,  0.5f,   0.75f, 0.75f, 0.75f,
     -0.5f, -0.5f, -0.5f,   0.75f, 0.75f, 0.75f,
     // --- TOP face (Y+) ---
    -0.5f,  0.5f, -0.5f,   1.00f, 1.00f, 1.00f,
     0.5f,  0.5f, -0.5f,   1.00f, 1.00f, 1.00f,
     0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
     0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
    -0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
    -0.5f,  0.5f, -0.5f,   1.00f, 1.00f, 1.00f,

    // =======================================================
    // CUBO 3: NEGRO (Ojos) - Índices 72 al 107
    // =======================================================
    // --- FRONT face (Z+) --- 
    -0.5f, -0.5f,  0.5f,   0.10f, 0.10f, 0.10f,
     0.5f, -0.5f,  0.5f,   0.10f, 0.10f, 0.10f,
     0.5f,  0.5f,  0.5f,   0.10f, 0.10f, 0.10f,
     0.5f,  0.5f,  0.5f,   0.10f, 0.10f, 0.10f,
    -0.5f,  0.5f,  0.5f,   0.10f, 0.10f, 0.10f,
    -0.5f, -0.5f,  0.5f,   0.10f, 0.10f, 0.10f,
    // --- BACK face (Z-) --- 
    -0.5f, -0.5f, -0.5f,   0.00f, 0.00f, 0.00f,
     0.5f, -0.5f, -0.5f,   0.00f, 0.00f, 0.00f,
     0.5f,  0.5f, -0.5f,   0.00f, 0.00f, 0.00f,
     0.5f,  0.5f, -0.5f,   0.00f, 0.00f, 0.00f,
    -0.5f,  0.5f, -0.5f,   0.00f, 0.00f, 0.00f,
    -0.5f, -0.5f, -0.5f,   0.00f, 0.00f, 0.00f,
    // --- RIGHT face (X+) --- 
     0.5f, -0.5f,  0.5f,   0.05f, 0.05f, 0.05f,
     0.5f, -0.5f, -0.5f,   0.05f, 0.05f, 0.05f,
     0.5f,  0.5f, -0.5f,   0.05f, 0.05f, 0.05f,
     0.5f,  0.5f, -0.5f,   0.05f, 0.05f, 0.05f,
     0.5f,  0.5f,  0.5f,   0.05f, 0.05f, 0.05f,
     0.5f, -0.5f,  0.5f,   0.05f, 0.05f, 0.05f,
     // --- LEFT face (X-) --- 
    -0.5f,  0.5f,  0.5f,   0.05f, 0.05f, 0.05f,
    -0.5f,  0.5f, -0.5f,   0.05f, 0.05f, 0.05f,
    -0.5f, -0.5f, -0.5f,   0.05f, 0.05f, 0.05f,
    -0.5f, -0.5f, -0.5f,   0.05f, 0.05f, 0.05f,
    -0.5f, -0.5f,  0.5f,   0.05f, 0.05f, 0.05f,
    -0.5f,  0.5f,  0.5f,   0.05f, 0.05f, 0.05f,
    // --- BOTTOM face (Y-) --- 
   -0.5f, -0.5f, -0.5f,   0.02f, 0.02f, 0.02f,
    0.5f, -0.5f, -0.5f,   0.02f, 0.02f, 0.02f,
    0.5f, -0.5f,  0.5f,   0.02f, 0.02f, 0.02f,
    0.5f, -0.5f,  0.5f,   0.02f, 0.02f, 0.02f,
   -0.5f, -0.5f,  0.5f,   0.02f, 0.02f, 0.02f,
   -0.5f, -0.5f, -0.5f,   0.02f, 0.02f, 0.02f,
   // --- TOP face (Y+) --- 
  -0.5f,  0.5f, -0.5f,   0.15f, 0.15f, 0.15f,
   0.5f,  0.5f, -0.5f,   0.15f, 0.15f, 0.15f,
   0.5f,  0.5f,  0.5f,   0.15f, 0.15f, 0.15f,
   0.5f,  0.5f,  0.5f,   0.15f, 0.15f, 0.15f,
  -0.5f,  0.5f,  0.5f,   0.15f, 0.15f, 0.15f,
  -0.5f,  0.5f, -0.5f,   0.15f, 0.15f, 0.15f,

  // =======================================================
  // CUBO 4: AMARILLO CREMA (Vientre) - Índices 108 al 143
  // =======================================================
  // --- FRONT face (Z+) --- 
  -0.5f, -0.5f,  0.5f,   0.94f, 0.90f, 0.55f,
   0.5f, -0.5f,  0.5f,   0.94f, 0.90f, 0.55f,
   0.5f,  0.5f,  0.5f,   0.94f, 0.90f, 0.55f,
   0.5f,  0.5f,  0.5f,   0.94f, 0.90f, 0.55f,
  -0.5f,  0.5f,  0.5f,   0.94f, 0.90f, 0.55f,
  -0.5f, -0.5f,  0.5f,   0.94f, 0.90f, 0.55f,
  // --- BACK face (Z-) ---
  -0.5f, -0.5f, -0.5f,   0.80f, 0.76f, 0.41f,
   0.5f, -0.5f, -0.5f,   0.80f, 0.76f, 0.41f,
   0.5f,  0.5f, -0.5f,   0.80f, 0.76f, 0.41f,
   0.5f,  0.5f, -0.5f,   0.80f, 0.76f, 0.41f,
  -0.5f,  0.5f, -0.5f,   0.80f, 0.76f, 0.41f,
  -0.5f, -0.5f, -0.5f,   0.80f, 0.76f, 0.41f,
  // --- RIGHT face (X+) ---
   0.5f, -0.5f,  0.5f,   0.88f, 0.84f, 0.49f,
   0.5f, -0.5f, -0.5f,   0.88f, 0.84f, 0.49f,
   0.5f,  0.5f, -0.5f,   0.88f, 0.84f, 0.49f,
   0.5f,  0.5f, -0.5f,   0.88f, 0.84f, 0.49f,
   0.5f,  0.5f,  0.5f,   0.88f, 0.84f, 0.49f,
   0.5f, -0.5f,  0.5f,   0.88f, 0.84f, 0.49f,
   // --- LEFT face (X-) ---
  -0.5f,  0.5f,  0.5f,   0.88f, 0.84f, 0.49f,
  -0.5f,  0.5f, -0.5f,   0.88f, 0.84f, 0.49f,
  -0.5f, -0.5f, -0.5f,   0.88f, 0.84f, 0.49f,
  -0.5f, -0.5f, -0.5f,   0.88f, 0.84f, 0.49f,
  -0.5f, -0.5f,  0.5f,   0.88f, 0.84f, 0.49f,
  -0.5f,  0.5f,  0.5f,   0.88f, 0.84f, 0.49f,
  // --- BOTTOM face (Y-) ---
 -0.5f, -0.5f, -0.5f,   0.70f, 0.66f, 0.31f,
  0.5f, -0.5f, -0.5f,   0.70f, 0.66f, 0.31f,
  0.5f, -0.5f,  0.5f,   0.70f, 0.66f, 0.31f,
  0.5f, -0.5f,  0.5f,   0.70f, 0.66f, 0.31f,
 -0.5f, -0.5f,  0.5f,   0.70f, 0.66f, 0.31f,
 -0.5f, -0.5f, -0.5f,   0.70f, 0.66f, 0.31f,
 // --- TOP face (Y+) ---
-0.5f,  0.5f, -0.5f,   1.00f, 0.96f, 0.61f,
 0.5f,  0.5f, -0.5f,   1.00f, 0.96f, 0.61f,
 0.5f,  0.5f,  0.5f,   1.00f, 0.96f, 0.61f,
 0.5f,  0.5f,  0.5f,   1.00f, 0.96f, 0.61f,
-0.5f,  0.5f,  0.5f,   1.00f, 0.96f, 0.61f,
-0.5f,  0.5f, -0.5f,   1.00f, 0.96f, 0.61f,

// =======================================================
// CUBO 5: NARANJA CAPARAZÓN - Índices 144 al 179
// =======================================================
// --- FRONT face (Z+) ---
-0.5f, -0.5f,  0.5f,   0.88f, 0.30f, 0.05f,
 0.5f, -0.5f,  0.5f,   0.88f, 0.30f, 0.05f,
 0.5f,  0.5f,  0.5f,   0.88f, 0.30f, 0.05f,
 0.5f,  0.5f,  0.5f,   0.88f, 0.30f, 0.05f,
-0.5f,  0.5f,  0.5f,   0.88f, 0.30f, 0.05f,
-0.5f, -0.5f,  0.5f,   0.88f, 0.30f, 0.05f,
// --- BACK face (Z-) --- 
-0.5f, -0.5f, -0.5f,   0.75f, 0.18f, 0.02f,
 0.5f, -0.5f, -0.5f,   0.75f, 0.18f, 0.02f,
 0.5f,  0.5f, -0.5f,   0.75f, 0.18f, 0.02f,
 0.5f,  0.5f, -0.5f,   0.75f, 0.18f, 0.02f,
-0.5f,  0.5f, -0.5f,   0.75f, 0.18f, 0.02f,
-0.5f, -0.5f, -0.5f,   0.75f, 0.18f, 0.02f,
// --- RIGHT face (X+) --- 
 0.5f, -0.5f,  0.5f,   0.80f, 0.23f, 0.03f,
 0.5f, -0.5f, -0.5f,   0.80f, 0.23f, 0.03f,
 0.5f,  0.5f, -0.5f,   0.80f, 0.23f, 0.03f,
 0.5f,  0.5f, -0.5f,   0.80f, 0.23f, 0.03f,
 0.5f,  0.5f,  0.5f,   0.80f, 0.23f, 0.03f,
 0.5f, -0.5f,  0.5f,   0.80f, 0.23f, 0.03f,
 // --- LEFT face (X-) --- 
-0.5f,  0.5f,  0.5f,   0.80f, 0.23f, 0.03f,
-0.5f,  0.5f, -0.5f,   0.80f, 0.23f, 0.03f,
-0.5f, -0.5f, -0.5f,   0.80f, 0.23f, 0.03f,
-0.5f, -0.5f, -0.5f,   0.80f, 0.23f, 0.03f,
-0.5f, -0.5f,  0.5f,   0.80f, 0.23f, 0.03f,
-0.5f,  0.5f,  0.5f,   0.80f, 0.23f, 0.03f,
// --- BOTTOM face (Y-) ---
-0.5f, -0.5f, -0.5f,   0.60f, 0.12f, 0.00f,
 0.5f, -0.5f, -0.5f,   0.60f, 0.12f, 0.00f,
 0.5f, -0.5f,  0.5f,   0.60f, 0.12f, 0.00f,
 0.5f, -0.5f,  0.5f,   0.60f, 0.12f, 0.00f,
-0.5f, -0.5f,  0.5f,   0.60f, 0.12f, 0.00f,
-0.5f, -0.5f, -0.5f,   0.60f, 0.12f, 0.00f,
// --- TOP face (Y+) --- 
-0.5f,  0.5f, -0.5f,   0.95f, 0.35f, 0.08f,
 0.5f,  0.5f, -0.5f,   0.95f, 0.35f, 0.08f,
 0.5f,  0.5f,  0.5f,   0.95f, 0.35f, 0.08f,
 0.5f,  0.5f,  0.5f,   0.95f, 0.35f, 0.08f,
-0.5f,  0.5f,  0.5f,   0.95f, 0.35f, 0.08f,
-0.5f,  0.5f, -0.5f,   0.95f, 0.35f, 0.08f,

    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Enlazar  Vertex Array Object
    glBindVertexArray(VAO);

    //2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 4. Despues colocamos las caracteristicas de los vertices
    //Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::mat4(1);
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
    {
        Inputs(window);
        glfwPollEvents();

        // Render
        glClearColor(0.15f, 0.15f, 0.15f, 0.15f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);

        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        //cabeza
        //primer nivel
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.5f));
        model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //segundo nivel
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.7f));
        model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.65f, 0.1f, 0.5f));
        model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //tercer nivel
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.65f, 0.1f, 0.7f));
        model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.8f, 0.1f, 0.5f));
        model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.6f));
        model = glm::translate(model, glm::vec3(0.0f, 2.0f, -0.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //cara frontal
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.65f, 0.4f, 0.1f));
        model = glm::translate(model, glm::vec3(0.0f, -0.11f, 3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.1f));
        model = glm::translate(model, glm::vec3(0.0f, -0.11f, 4.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Ojo izquierdo
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.34f, 0.09f, 0.19f));
        model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 36, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.34f, -0.03f, 0.19f));
        model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 72, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.34f, -0.09f, 0.19f));
        model = glm::scale(model, glm::vec3(0.12f, 0.06f, 0.12f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 72, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.34f, -0.186f, 0.19f));
        model = glm::scale(model, glm::vec3(0.126f, 0.122f, 0.122f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //Ojo derecho
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.34f, 0.09f, 0.19f));
        model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 36, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.34f, -0.03f, 0.19f));
        model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 72, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.34f, -0.09f, 0.19f));
        model = glm::scale(model, glm::vec3(0.12f, 0.06f, 0.12f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 72, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.34f, -0.186f, 0.19f));
        model = glm::scale(model, glm::vec3(0.126f, 0.122f, 0.122f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //cara derecha
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.1f, 0.44f, 0.379f));
        model = glm::translate(model, glm::vec3(-3.5f, -0.05f, -0.16f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Cara izquierda
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.1f, 0.44f, 0.379f));
        model = glm::translate(model, glm::vec3(3.5f, -0.05f, -0.16f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Cara trasera 
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 0.4f, 0.1f));
        model = glm::translate(model, glm::vec3(0.0f, -0.1f, -3.7f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.65f, 0.4f, 0.1f));
        model = glm::translate(model, glm::vec3(0.0f, -0.1f, -3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //base de la cabeza 
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.35f));
        model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.213f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.65f, 0.1f, 0.25f));
        model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.6f, 0.1f, 0.5f));
        model = glm::translate(model, glm::vec3(0.0f, -1.9f, -0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Torso
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.2f));
        model = glm::scale(model, glm::vec3(0.5f, 0.4f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 108, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.1f));
        model = glm::scale(model, glm::vec3(0.65f, 0.4f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 108, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.525f, -0.025f));
        model = glm::scale(model, glm::vec3(0.65f, 0.45f, 0.15f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 108, 36); 

        //Pierna derecha 
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.25f));
        model = glm::translate(model, glm::vec3(-2.669f, -5.0f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.15, 0.08f, 0.2f));
        model = glm::translate(model, glm::vec3(-2.669f, -10.8f, 0.7f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Pierna iaquierda
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(-0.15f, 0.15f, 0.25f));
        model = glm::translate(model, glm::vec3(-2.669f, -5.0f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(-0.15, 0.08f, 0.2f));
        model = glm::translate(model, glm::vec3(-2.669f, -10.8f, 0.7f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Caparazon 
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.375f, -0.46f, -0.05f));
        model = glm::scale(model, glm::vec3(0.1f, 0.43f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 36, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.375f, -0.46f, -0.05f));
        model = glm::scale(model, glm::vec3(0.1f, 0.43f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 36, 36); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.375f, -0.625f, -0.15f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 36, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.375f, -0.625f, -0.15f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 36, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.7f, -0.15f));
        model = glm::scale(model, glm::vec3(0.65f, 0.1f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 36, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.28f, -0.15f));
        model = glm::scale(model, glm::vec3(0.65f, 0.1f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 36, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.49f, -0.15f));
        model = glm::scale(model, glm::vec3(0.65f, 0.32f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 144, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.49f, -0.25f));
        model = glm::scale(model, glm::vec3(0.65f, 0.32f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 144, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.49f, -0.35f));
        model = glm::scale(model, glm::vec3(0.45f, 0.32f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 144, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.49f, -0.35f));
        model = glm::scale(model, glm::vec3(0.65f, 0.16f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 144, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.49f, -0.45f));
        model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 144, 36);

        //Cola
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.8f, -0.15f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.75f, -0.35f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.7f, -0.5f));
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.60f, -0.70f));
        model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.60f, -0.70f));
        model = glm::scale(model, glm::vec3(0.40f, 0.2f, 0.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Mano derecha 
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(-0.15, 0.08f, 0.15f));
        model = glm::translate(model, glm::vec3(2.669f, -6.5f, 0.85f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(-0.15, 0.08f, 0.15f));
        model = glm::translate(model, glm::vec3(2.669f, -5.5f, 0.35f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Mano izquierda
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.15, 0.08f, 0.15f));
        model = glm::translate(model, glm::vec3(2.669f, -6.5f, 0.85f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.15, 0.08f, 0.15f));
        model = glm::translate(model, glm::vec3(2.669f, -5.5f, 0.35f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movX += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movX -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        movY += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        movY -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movZ -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movZ += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot += 0.4f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot -= 0.4f;
}