#include "../OGLRender/Program.h"
#include "UtilGL/Texture.h"
#include "PlayerFPS/Camera.h"
#include "World/World.h"
#include "Chunk/Chunk.h"
#include "Util/FPS.h"
#include "IO/InputHandler.h"

//Check for Memory Leaks
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// third-party libraries
#include <Windows.h>
#include <Windows.h>
#include <ObjBase.h>
#include <WinBase.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <time.h>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const glm::vec2 SCREEN_SIZE(1200, 900);

struct Light {
    glm::vec3 position;
    glm::vec3 intensities;
	float attenuation;
    float ambientCoefficient;
};

Light gLight;

Program* _program(NULL);
FPS* fps;

static std::string ResourcePath(std::string fileName) {
    char executablePath[1024] = {'\0'};
    DWORD charsCopied = GetModuleFileName(NULL, executablePath, 1024);
    if(charsCopied > 0 && charsCopied < 1024) {
        return std::string(executablePath) + "\\..\\" + fileName;
	} else {
        throw std::runtime_error("GetModuleFileName failed a bit");
	}
}

void init() {
	srand (time(NULL));

	if(!glfwInit()) {
        throw std::runtime_error("glfwInit failed");
		return;
	}
    
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_FALSE);
	if(!glfwOpenWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, 8, 8, 8, 8, 16, 0, GLFW_WINDOW)) {
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");
		return;
	}

	glfwSetWindowPos(400, 100);

    //GLFW settings.
	glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetMousePos(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2);
    glfwSetMouseWheel(0);
	
	glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        throw std::runtime_error("glewInit failed");
		return;
	}

	while(glGetError() != GL_NO_ERROR) {}    
	
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    if(!GLEW_VERSION_3_2) {
        throw std::runtime_error("OpenGL 3.2 API is not available.");
		return;
	}
}

void AppMain() {
	//Init everything in the game.
		fps = new FPS(glfwGetTime());

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		std::vector<Shader> shaders;
		shaders.push_back(Shader::shaderFromFile(ResourcePath("vertex-shader.txt"), GL_VERTEX_SHADER));
		shaders.push_back(Shader::shaderFromFile(ResourcePath("fragment-shader.txt"), GL_FRAGMENT_SHADER));
		_program = new Program(shaders);

		World* world = new World();
		world->generateWorld(_program);

		gLight.position = world->_player->_camera->position();
		gLight.intensities = glm::vec3(1, 1, 1);
		gLight.attenuation = 0.00f; /* 0.01f; */
		gLight.ambientCoefficient = 0.01f;

	//Run the game.
    while(glfwGetWindowParam(GLFW_OPENED)) {
		//update
		fps->_thisTime = glfwGetTime(); {
			world->update(fps->_thisTime - fps->_lastTime);
			
			gLight.position = world->_player->_camera->position();
			if(glfwGetKey('1'))
				gLight.intensities = glm::vec3(0,0,1); //blue
			if(glfwGetKey('2'))
				gLight.intensities = glm::vec3(1,0,0); //red
			else if(glfwGetKey('3'))
				gLight.intensities = glm::vec3(0,1,0); //green
			else if(glfwGetKey('4'))
				gLight.intensities = glm::vec3(1,1,1); //white
		} fps->_lastTime = fps->_thisTime;
		
		//render
        _program->use(); {
			glClearColor(0.2, 0.2, 0.2, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
			_program->setUniform("camera", world->_player->_camera->matrix());
			_program->setUniform("light.position", gLight.position);
			_program->setUniform("light.intensities", gLight.intensities);
			_program->setUniform("light.attenuation", gLight.attenuation);
			_program->setUniform("light.ambientCoefficient", gLight.ambientCoefficient);
		
			world->render();
		} _program->stopUsing();

		fps->update(glfwGetTime());

		if(glfwGetKey(GLFW_KEY_ESC) || (fps->_fps < 5.0 && fps->_counter > 5)) {
            glfwCloseWindow();
		}

		//Display.
		glfwSwapBuffers();
    }

	//It's time to close, KILL EVERYTHING!!! MUHAHAHA!!!
	delete world;
	delete _program;
	delete fps;

    glfwTerminate();
}

int main(int argc, char *argv[]) {
	//Initializes everything that isn't game content.
	init();
	
	//Start the game.
	AppMain();

	//Checks for Memory Leaks
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	if (_CrtDumpMemoryLeaks() == 0) {
		std::cout << std::endl << "NO Memory Leaks!!! Be Proud!!!!" << std::endl;
	}

	getchar();

	return 0;
}