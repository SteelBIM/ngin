//
//  Created by Mateusz Stompór on 03/03/2018.
//  Copyright © 2017 Mateusz Stompór. All rights reserved.
//

#ifdef __WIN32__
	#include <glad/glad.h>
	#include "../../third-party-libs/renderdoc.h"
#endif

#include <GLFW/glfw3.h>
#include <cstring>
#include <string>
#include <memory>
#include <iostream>
#include <cassert>

#include "../../source_code/umbrellaHeader.hpp"
#include "controlls.hpp"
#include "utils.hpp"

std::unique_ptr<ms::NGin> engine 	= nullptr;
unsigned int usedPointLightIndex 	= 0;
unsigned int usedSpotLightIndex 	= 0;

using namespace ms;
using namespace math;
using namespace transform;

namespace ms {
    const std::string libInitializationError        = "Cannot initialize GLFW3";
    const std::string windowCreationError           = "Cannot create window";
    const std::string windowName                    = "NGIN";
    const std::string contextInitializationFailure  = "Failed to initialize OpenGL context";
}

int main(int argc, const char * argv[]) { {

	
	// pass path to scene with building as first param
	// pass path to nanosuit as second param
	// pass path to cone as third param
	// pass path to sphere as fourth param
	
	bool useCommandLineArguments = argc == 5;

	int width = 1000;
	int height = 1000;
	int actualScreenWidth;
	int actualScreenHeight;
	int framebufferWidth;
	int framebufferHeight;
	
	prepareRenderDoc();
	
	if(glfwInit()==0) {
		std::cerr<<ms::libInitializationError<<std::endl;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwSwapInterval(1);
	
	GLFWwindow *window = glfwCreateWindow(width, height, ms::windowName.c_str(), nullptr, nullptr);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	
	actualScreenWidth = framebufferWidth;
	actualScreenHeight = framebufferHeight;
	
	//Configure rendering resoultion here
    framebufferWidth /= 2;
    framebufferHeight /= 2;
    
	
	if(window == nullptr){
		std::cerr << ms::windowCreationError << std::endl;
		glfwTerminate();
	}
	
	glfwMakeContextCurrent(window);
	
#ifdef __WIN32__
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << ms::contextInitializationFailure << std::endl;
		return -1;
	}
#endif
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	engine = std::make_unique<NGinOGL>(actualScreenWidth, actualScreenHeight, framebufferWidth, framebufferHeight, 0.01f, 100, 90, float(framebufferWidth)/framebufferHeight);
		
	engine->load_model(useCommandLineArguments ? argv[1] : "./sponza/sponza.obj");

	engine->scene->set_directional_light(50, ms::math::vec3{ 1.0f, 1.0f, 1.0f}, ms::math::vec3{ 1.0f, 1.0f, -1.0f });

	mat4 scaleMat = scale<float, 4> ({0.05f, 0.05f, 0.05f});

	for (int i = 0; i < 2; ++i) {
		auto translation = ms::math::transform::translate<float, 4>({-6 + (i * 1.0f), 1.0f, 0.0f});
		auto lightColor = vec3{1.0f, 1.0f, 1.0f};
		auto lightPower = 50.0f;
		
		engine->load_point_light(lightPower, lightColor, get_position(translation), useCommandLineArguments ? argv[4] : "./sphere/sphere.obj");
		engine->scene->pointLights[i]->modelTransformation.pre_transform(translation * scaleMat);
	}

    for (int i = 0; i < 5; ++i) {
        auto translation = ms::math::transform::translate<float, 4>({-4.0f + (i * 2.0f), 3.0f, 0.0f});
        auto lightColor = vec3{1.0f, 1.0f, 1.0f};
        auto lightingDir = vec3{0.0f, -1.0f, 0.0f};
        auto lightPower = 50.0f;
        auto spotLightAngle = 50.0f;

        engine->load_spot_light(lightPower, lightColor, get_position(translation), spotLightAngle, lightingDir, useCommandLineArguments ? argv[3] : "./cone/cone.obj");
        engine->scene->spotLights[i]->modelTransformation.pre_transform(translation * scaleMat);
    }

	for(int i = 0; i < engine->scene->get_nodes().size(); ++i) {
		engine->scene->get_nodes()[i]->modelTransformation.pre_transform(ms::math::transform::scale<float, 4>({0.02f, 0.02f, 0.02f}));
	}

	engine->load_model(useCommandLineArguments ? argv[2] : "./nanosuit/nanosuit.obj");
	
	engine->load();
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	glfwSetKeyCallback(window, key_callback);
	
	while(!glfwWindowShouldClose(window)) {
		
		glfwPollEvents();
		
		//////////////////////////////////////////////////////////////////////////////////////////
		
		engine->draw_scene();
		
		//////////////////////////////////////////////////////////////////////////////////////////
		
		glfwSwapBuffers(window);
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////

	engine->unload();

	engine = nullptr;	
	
	std::cout<<get_allocation_statistics()<<std::endl;
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	glfwTerminate();
	
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	ms::ResourceCoordinator::destroy_shared_instance();
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
    return 0;
}
