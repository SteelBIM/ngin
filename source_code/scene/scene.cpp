//
//  scene.cpp
//  ngin
//
//  Created by Mateusz Stompór on 06/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include "scene.hpp"

ms::Scene::Scene (float nearPlan, float farPlan, float fovDegress, float cameraAspect) : 	directionalLight(nullptr),
																							nodes(std::vector<std::shared_ptr<Drawable>>()),
																							materials(std::map<std::string, std::shared_ptr<Material>>()){
																								
	cam = std::make_unique<PerspectiveCamera>(nearPlan, farPlan, fovDegress, cameraAspect);
																								
}

ms::Camera & ms::Scene::get_camera() const {
	return *this->cam;
}

const std::vector<std::shared_ptr<ms::SpotLight>> & ms::Scene::get_spot_lights() const {
	return this->spotLights;
}

const std::vector<std::shared_ptr<ms::PointLight>> & ms::Scene::get_point_lights() const {
	return this->pointLights;
}

ms::DirectionalLight * ms::Scene::get_directional_light() const {
	return this->directionalLight.get();
}

void ms::Scene::set_directional_light(float power, math::vec3 color, math::vec3 direction) {
	directionalLight = std::make_unique<DirectionalLight>(color, direction);
}

const std::vector<std::shared_ptr<ms::Drawable>> & ms::Scene::get_nodes() const {
	return this->nodes;
}

