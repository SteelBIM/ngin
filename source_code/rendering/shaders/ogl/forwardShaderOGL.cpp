//
//  forwardShaderOGL.cpp
//  ngin
//
//  Created by Mateusz Stompór on 06/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include "forwardShaderOGL.hpp"

ms::ForwardShaderOGL::ForwardShaderOGL(std::string vSS, std::string fSS) : ms::ShaderOGL(vSS, "", "", "", fSS) { }

void  ms::ForwardShaderOGL::load () {
	ShaderOGL::load();
	
	mglUseProgram(program);
	
	GLint diffuseTextureLocation = mglGetUniformLocation(program, "diffuseTexture");
	mglUniform1i(diffuseTextureLocation, 0);
	
	GLint specularTextureLocation = mglGetUniformLocation(program, "specularTexture");
	mglUniform1i(specularTextureLocation, 1);
	
	mglUseProgram(0);
	
}

void ms::ForwardShaderOGL::set_projection_matrix (const math::mat4 & proj) {
	GLint persp = mglGetUniformLocation(program, "perspectiveProjection");
	mglUniformMatrix4fv(persp, 1, GL_FALSE, proj.c_array());
}

void ms::ForwardShaderOGL::set_camera_transformation (const math::mat4 & transf) {
	GLint cam = mglGetUniformLocation(program, "cameraTransformation");
	mglUniformMatrix4fv(cam, 1, GL_FALSE, transf.c_array());
}

void ms::ForwardShaderOGL::set_model_transformation (const math::mat4 & modelTransf) {
	GLint model = mglGetUniformLocation(program, "modelTransformation");
	mglUniformMatrix4fv(model, 1, GL_FALSE, modelTransf.c_array());
}

void ms::ForwardShaderOGL::set_has_directional_light (bool doesItHave) {
	GLint hasLight = mglGetUniformLocation(program, "hasDirLight");
	mglUniform1i(hasLight, doesItHave == true ? 1 : 0);
}

void ms::ForwardShaderOGL::set_amount_of_point_lights (int amount) {
	GLint amountLocation = mglGetUniformLocation(program, "pointLightsAmount");
	mglUniform1i(amountLocation, amount);
}

void ms::ForwardShaderOGL::set_point_light_power (unsigned int index, float power) {
	std::string name = "pointLights[" + std::to_string(index) + "].power";
	GLint powerLocation = mglGetUniformLocation(program, name.c_str());
	mglUniform1f(powerLocation, power);
}

void ms::ForwardShaderOGL::set_point_light_color (unsigned int index, const math::vec4 & color) {
	std::string name = "pointLights[" + std::to_string(index) + "].color";
	GLint colorLocation = mglGetUniformLocation(program, name.c_str());
	mglUniform4fv(colorLocation, 1, color.c_array());
}

void ms::ForwardShaderOGL::set_point_light_position (unsigned int index, const math::vec3 & position) {
	std::string name = "pointLights[" + std::to_string(index) + "].position";
	GLint positionLocation = mglGetUniformLocation(program, name.c_str());
	mglUniform3fv(positionLocation, 1, position.c_array());
}

void ms::ForwardShaderOGL::set_amount_of_spot_lights (int amount) {
	GLint amountLocation = mglGetUniformLocation(program, "spotLightsAmount");
	mglUniform1i(amountLocation, amount);
}

void ms::ForwardShaderOGL::set_spot_light_power (unsigned int index, float power) {
	std::string name = "spotLights[" + std::to_string(index) + "].power";
	GLint powerLocation = mglGetUniformLocation(program, name.c_str());
	mglUniform1f(powerLocation, power);
}

void ms::ForwardShaderOGL::set_spot_light_color (unsigned int index, const math::vec4 & color) {
	std::string name = "spotLights[" + std::to_string(index) + "].color";
	GLint colorLocation = mglGetUniformLocation(program, name.c_str());
	mglUniform4fv(colorLocation, 1, color.c_array());
}

void ms::ForwardShaderOGL::set_spot_light_position (unsigned int index, const math::vec3 & position) {
	std::string name = "spotLights[" + std::to_string(index) + "].position";
	GLint positionLocation = mglGetUniformLocation(program, name.c_str());
	glUniform3fv(positionLocation, 1, position.c_array());
}

void ms::ForwardShaderOGL::set_spot_light_angle (unsigned int index, float angle) {
	std::string name = "spotLights[" + std::to_string(index) + "].angleDegrees";
	GLint angleLocation = mglGetUniformLocation(program, name.c_str());
	mglUniform1f(angleLocation, angle);
}

void ms::ForwardShaderOGL::set_spot_light_direction (unsigned int index, const math::vec3 direction) {
	std::string name = "spotLights[" + std::to_string(index) + "].direction";
	GLint directionLocation = mglGetUniformLocation(program, name.c_str());
	mglUniform3fv(directionLocation, 1, direction.c_array());
}

void ms::ForwardShaderOGL::set_directional_light_dir (const math::vec3 & dir) {
	GLint direction = mglGetUniformLocation(program, "dirLight.direction");
	mglUniform3fv(direction, 1, dir.c_array());
}

void ms::ForwardShaderOGL::set_directional_light_color (const math::vec4 & color) {
	GLint colorLocation = mglGetUniformLocation(program, "dirLight.color");
	mglUniform4fv(colorLocation, 1, color.c_array());
}

void ms::ForwardShaderOGL::set_has_material (bool doesItHave) {
	GLint hasMaterialLocation = mglGetUniformLocation(program, "hasMaterial");
	mglUniform1i(hasMaterialLocation, doesItHave == true ? 1 : 0);
}

void ms::ForwardShaderOGL::set_material_ambient_color (const math::vec3 & ambient) {
	GLint ambientLocation = mglGetUniformLocation(program, "material.ambient");
	mglUniform3fv(ambientLocation, 1, ambient.c_array());
}

void ms::ForwardShaderOGL::set_material_diffuse_color (const math::vec3 & diffuse) {
	GLint diffuseLocation = mglGetUniformLocation(program, "material.diffuse");
	mglUniform3fv(diffuseLocation, 1, diffuse.c_array());
}

void ms::ForwardShaderOGL::set_material_specular_color (const math::vec3 & specular) {
	GLint specularLocation = mglGetUniformLocation(program, "material.specular");
	mglUniform3fv(specularLocation, 1, specular.c_array());
}

void ms::ForwardShaderOGL::set_material_opacity (float opacity) {
	GLint opacityLocation = mglGetUniformLocation(program, "material.opacity");
	mglUniform1f(opacityLocation, opacity);
}

void ms::ForwardShaderOGL::set_material_shininess (float shininess) {
	GLint shininessLocation = mglGetUniformLocation(program, "material.shininess");
	mglUniform1f(shininessLocation, shininess);
}

void ms::ForwardShaderOGL::set_has_diffuse_texture (bool doesItHave) {
	GLint hasDiffuseTextureLocation = mglGetUniformLocation(program, "hasDiffuseTexture");
	mglUniform1i(hasDiffuseTextureLocation, doesItHave == true ? 1 : 0);
}

void ms::ForwardShaderOGL::set_has_specular_texture (bool doesItHave) {
	GLint hasSpecularTextureLocation = mglGetUniformLocation(program, "hasSpecularTexture");
	mglUniform1i(hasSpecularTextureLocation, doesItHave == true ? 1 : 0);
}
