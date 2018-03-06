//
//  forwardShaderOGL.cpp
//  ngin
//
//  Created by Mateusz Stompór on 06/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include "forwardShaderOGL.hpp"

ms::ForwardShaderOGL::ForwardShaderOGL(str_ptr vSS, str_ptr fSS) : ms::ShaderOGL(vSS, nullptr, nullptr, nullptr, fSS) {
	
}

void ms::ForwardShaderOGL::set_projection_matrix (math::mat4 proj) {
	GLint persp = glGetUniformLocation(program, "perspectiveProjection");
	glUniformMatrix4fv(persp, 1, GL_FALSE, proj.c_array());
}

void ms::ForwardShaderOGL::set_camera_transformation (math::mat4 transf) {
	GLint cam = glGetUniformLocation(program, "cameraTransformation");
	glUniformMatrix4fv(cam, 1, GL_FALSE, transf.c_array());
}

void ms::ForwardShaderOGL::set_model_transformation (math::mat4 modelTransf) {
	GLint model = glGetUniformLocation(program, "modelTransformation");
	glUniformMatrix4fv(model, 1, GL_FALSE, modelTransf.c_array());
}

void ms::ForwardShaderOGL::set_has_directional_light (bool doesItHave) {
	GLint hasLight = glGetUniformLocation(program, "hasDirLight");
	glUniform1i(hasLight, doesItHave == true ? 1 : 0);
}

void ms::ForwardShaderOGL::set_directional_light_dir (math::vec3 dir) {
	GLint direction = glGetUniformLocation(program, "dirLight.direction");
	glUniform3fv(direction, 1, dir.c_array());
}

void ms::ForwardShaderOGL::set_directional_light_color (math::vec4 color) {
	GLint colorLocation = glGetUniformLocation(program, "dirLight.color");
	glUniform4fv(colorLocation, 1, color.c_array());
}

void ms::ForwardShaderOGL::set_directional_light_pow (float power) {
	GLint powerLocation = glGetUniformLocation(program, "dirLight.power");
	glUniform1f(powerLocation, power);
}

