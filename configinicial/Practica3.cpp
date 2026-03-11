//Practica3		                                                             Hernández Juárez Fernando 	
//Fecha de entrega  22 de febrero de 2026                                    320115448

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecciones y transformaciones basicas Hernandez Juarez Fernando", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

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




	// use with Perspective Projection

	float vertices[] = {
		// Posiciones (x, y, z)      // Colores (R, G, B)

		// --- FRONT face: "SYNTHWAVE SUNSET" (Naranja fuego a Magenta neón) ---
		// El degradado va de abajo hacia arriba.
		-0.5f, -0.5f,  0.5f,   1.0f, 0.2f, 0.0f, // Abajo: Naranja quemado intenso
		 0.5f, -0.5f,  0.5f,   1.0f, 0.2f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f, // Arriba: Magenta fucsia brillante
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 0.2f, 0.0f,

		// --- BACK face: "DEEP CYBERSPACE" (Indigo oscuro a Cian eléctrico) ---
		// Contraste frío para la parte trasera. Abajo a arriba.
		-0.5f, -0.5f, -0.5f,   0.1f, 0.0f, 0.3f, // Abajo: Violeta profundo casi negro
		 0.5f, -0.5f, -0.5f,   0.1f, 0.0f, 0.3f,
		 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f, // Arriba: Cian láser cegador
		 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.1f, 0.0f, 0.3f,

		// --- RIGHT face: "TOXIC ACID" (Verde lima radiactivo a Amarillo puro) ---
		// Un lado muy brillante y ácido. Abajo a arriba.
		 0.5f, -0.5f,  0.5f,   0.4f, 1.0f, 0.0f, // Abajo: Verde lima tóxico
		 0.5f, -0.5f, -0.5f,   0.4f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // Arriba: Amarillo puro
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.4f, 1.0f, 0.0f,

		 // --- LEFT face: "BLOOD NEON" (Rojo carmesí a Rosa intenso) ---
		 // El lado agresivo. Abajo a arriba.
		 -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.5f, // Arriba: Rosa neón "hot pink"
		 -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.5f,
		 -0.5f, -0.5f, -0.5f,   0.7f, 0.0f, 0.0f, // Abajo: Rojo sangre oscuro
		 -0.5f, -0.5f, -0.5f,   0.7f, 0.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,   0.7f, 0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.5f,

		 // --- BOTTOM face: "THE VOID" (Degradado oscuro diagonal) ---
		 // La base debe ser oscura. Degradado de esquina a esquina (negro a morado oscuro).
		 -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f, // Esquina trasera-izq: Negro puro
		  0.5f, -0.5f, -0.5f,   0.2f, 0.0f, 0.2f, // Esquina trasera-der: Morado muy oscuro
		  0.5f, -0.5f,  0.5f,   0.4f, 0.0f, 0.4f, // Esquina frontal-der: Morado medio
		  0.5f, -0.5f,  0.5f,   0.4f, 0.0f, 0.4f,
		 -0.5f, -0.5f,  0.5f,   0.2f, 0.0f, 0.2f, // Esquina frontal-izq: Morado muy oscuro
		 -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,

		 // --- TOP face: "VAPORWAVE SKY" (Degradado diagonal Azul a Rosa) ---
		 // La tapa superior tiene un degradado cruzado para que se vea dinámico desde arriba.
		 // Los vértices "traseros" (z=-0.5) son azules, los "frontales" (z=0.5) son rosas.
		 -0.5f,  0.5f, -0.5f,   0.0f, 0.5f, 1.0f, // Atrás-Izq: Azul cielo neón
		  0.5f,  0.5f, -0.5f,   0.0f, 0.5f, 1.0f, // Atrás-Der: Azul cielo neón
		  0.5f,  0.5f,  0.5f,   1.0f, 0.4f, 0.7f, // Frente-Der: Rosa pastel brillante
		  0.5f,  0.5f,  0.5f,   1.0f, 0.4f, 0.7f, // Frente-Der: Rosa pastel brillante
		 -0.5f,  0.5f,  0.5f,   1.0f, 0.4f, 0.7f, // Frente-Izq: Rosa pastel brillante
		 -0.5f,  0.5f, -0.5f,   0.0f, 0.5f, 1.0f, // Atrás-Izq: Azul cielo neón
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -13.0f));
		model = glm::rotate(model, 45.0f, glm::vec3(0.1f, 1.0f, 0.0f)); // use to compare orthographic and perspective projection
		model = glm::scale(model, glm::vec3(-1.0f, -1.0f, -1.0f));
		//view = glm::translate( view, glm::vec3( screenWidth / 2, screenHeight / 30,-100.0f ) ); // use with orthographic projection

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);
		model = glm::translate(view, glm::vec3(0.0f, -1.0f, 12.5f));
		model = glm::rotate(model, 45.0f, glm::vec3(0.0f, -1.0f, 0.0f)); // use to compare orthographic and perspective projection
		model = glm::scale(model, glm::vec3(-0.9f, -0.9f, -0.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1);
		model = glm::translate(view, glm::vec3(0.0f, -1.8f, 13.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // use to compare orthographic and perspective projection
		model = glm::scale(model, glm::vec3(-0.8f, -0.8f, -0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1);
		model = glm::translate(view, glm::vec3(0.0f, -3.0f, 12.5f));
		model = glm::rotate(model, glm::radians(195.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(-1.3f, -1.3f, -1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1);
		model = glm::translate(view, glm::vec3(0.0f, -4.3f, 12.5f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // 2. Inclinación frontal
		model = glm::scale(model, glm::vec3(-0.8f, -0.8f, -0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1);
		model = glm::translate(view, glm::vec3(0.0f, -5.0f, 12.5f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.2334f, 0.2334f)); 
		model = glm::scale(model, glm::vec3(-0.5f, -0.5f, -0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1);
		model = glm::translate(view, glm::vec3(0.0f, -5.6f, 12.5f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, -0.2334f, -0.2334f));
		model = glm::scale(model, glm::vec3(-0.8f, -0.8f, -0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1);
		model = glm::translate(view, glm::vec3(0.0f, 1.0f, 12.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, -0.50f, 0.20f));
		model = glm::scale(model, glm::vec3(-1.2f, -1.2f, -1.2f));
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


