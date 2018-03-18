//
//  deferredRenderOGL.cpp
//  ngin
//
//  Created by Mateusz Stompór on 06/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include "deferredRenderOGL.hpp"

namespace ms {
	
	typedef unsigned int ui;
	
	#define G_BUF_ALBEDO 		"G_BUF_ALBEDO"
	#define G_BUF_POSITIONS 	"G_BUF_POSITIONS"
	#define G_BUF_NORMALS 		"G_BUF_NORMALS"
	
}

ms::DeferredRenderOGL::DeferredRenderOGL (std::string gVS,
										  std::string gFS,
										  std::string lVS,
										  std::string lFS,
										  unsigned int sW,
										  unsigned int sH,
										  unsigned int fbW,
										  unsigned int fbH) :

ms::DeferredRender(sW, sH, fbW, fbH, gVS, gFS, lVS, lFS), gFrameBuffer(0), gRenderBuffer(0), quadVAO(0), quadVBO(0), defaultFBO(0) {
	gShader = std::unique_ptr<DeferredShader>(new DeferredShaderOGL(gVS, gFS));
	lightingShader = std::unique_ptr<DeferredLightingShader>(new DeferredLightingShaderOGL(lVS, lFS));
	
	
	gPosition = std::unique_ptr<Texture>(new TextureOGL(GL_TEXTURE_2D,
														G_BUF_POSITIONS,
														Texture::Format::rgb_16_16_16,
														Texture::AssociatedType::FLOAT,
														Texture::MinFilter::linear,
														Texture::MagFilter::linear,
														Texture::Wrapping::clamp_to_edge,
														Texture::Wrapping::clamp_to_edge,
														0, frameBufferWidth, frameBufferHeight));
	
	gNormal = std::unique_ptr<Texture>(new TextureOGL(	GL_TEXTURE_2D,
														G_BUF_NORMALS,
														Texture::Format::rgb_16_16_16,
														Texture::AssociatedType::FLOAT,
														Texture::MinFilter::linear,
														Texture::MagFilter::linear,
														Texture::Wrapping::clamp_to_edge,
														Texture::Wrapping::clamp_to_edge,
														0, frameBufferWidth, frameBufferHeight));
	
	gAlbedo = std::unique_ptr<Texture>(new TextureOGL(	GL_TEXTURE_2D,
														G_BUF_ALBEDO,
													  	Texture::Format::rgba_8_8_8_8,
														Texture::AssociatedType::UNSIGNED_BYTE,
														Texture::MinFilter::linear,
														Texture::MagFilter::linear,
														Texture::Wrapping::clamp_to_edge,
														Texture::Wrapping::clamp_to_edge,
														0, frameBufferWidth, frameBufferHeight));
	
}

void ms::DeferredRenderOGL::use () {
	if(!gShader->is_loaded() || !lightingShader->is_loaded()) {
		gShader->load();
		lightingShader->load();
	}

	gShader->use();
}

void ms::DeferredRenderOGL::clear_frame () {
	mglBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer);
	mglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ms::DeferredRenderOGL::draw (SceneNode * node, const Scene * scene) {

	gShader->set_camera_transformation(scene->get_camera().get_transformation());
	gShader->set_projection_matrix(scene->get_camera().get_projection_matrix());
	gShader->set_model_transformation(node->modelTransformation.get_transformation());

	node->use();
	
	auto material = scene->materials.find(node->geometry->get_material_name());
		
	if (material != scene->materials.end()) {
		gShader->set_has_material(true);
		
		if(material->second->diffuseTexturesNames.size() > 0) {
			
			auto textureIt = scene->textures.find(material->second->diffuseTexturesNames[0]);
			
			if ( textureIt != scene->textures.end()) {
				mglActiveTexture(GL_TEXTURE0);
				textureIt->second->use();
				gShader->set_has_diffuse_texture(true);
			} else {
				gShader->set_has_diffuse_texture(false);
			}
			
		} else {
			gShader->set_has_diffuse_texture(false);
		}
		
		if(material->second->specularTexturesNames.size() > 0) {
			auto textureIt = scene->textures.find(material->second->specularTexturesNames[0]);
			if ( textureIt != scene->textures.end()) {
				mglActiveTexture(GL_TEXTURE1);
				textureIt->second->use();
				gShader->set_has_specular_texture(true);

			} else {
				gShader->set_has_specular_texture(false);
			}
			
		} else {
			gShader->set_has_specular_texture(false);
		}
		
		
		gShader->set_material_ambient_color(material->second->ambientColor);
		gShader->set_material_diffuse_color(material->second->diffuseColor);
		gShader->set_material_specular_color(material->second->specularColor);
		gShader->set_material_opacity(material->second->opacity);
		gShader->set_material_shininess(material->second->shininess);
	} else {
		gShader->set_has_material(false);
	}
	
	node->geometry->use_indicies();
	
	mglDrawElements(GL_TRIANGLES, node->geometry->amount_of_indices(), GL_UNSIGNED_INT, nullptr);

}

void ms::DeferredRenderOGL::load () {
	
	if (!is_loaded()) {
		this->gShader->load();
		this->lightingShader->is_loaded();
		
		mglGenFramebuffers(1, &gFrameBuffer);
		mglBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer);
		
		gPosition->load();
		gNormal->load();
		gAlbedo->load();
		
		gPosition->use();
		mglFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (dynamic_cast<TextureOGL*>(gPosition.get()))->get_underlying_id(), 0);
		
		gNormal->use();
		mglFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, (dynamic_cast<TextureOGL*>(gNormal.get()))->get_underlying_id(), 0);

		gAlbedo->use();
		mglFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, (dynamic_cast<TextureOGL*>(gAlbedo.get()))->get_underlying_id(), 0);

		GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		
		mglDrawBuffers(3, attachments);

		mglGenRenderbuffers(1, &gRenderBuffer);
		mglBindRenderbuffer(GL_RENDERBUFFER, gRenderBuffer);

		//TODO Set depth component to 16 in order to see image distortion
		#ifdef ios_build
		mglRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, frameBufferWidth, frameBufferHeight);
		#else
		mglRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, frameBufferWidth, frameBufferHeight);
		#endif

		mglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gRenderBuffer);


		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "Framebuffer not complete!" << std::endl;
		}
		

		mglBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);

		//setup quad
		mglGenVertexArrays(1, &quadVAO);
		mglBindVertexArray(quadVAO);

		mglGenBuffers(1, &quadVBO);
		mglBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		mglBufferData(GL_ARRAY_BUFFER, sizeof(quad::vertices) + sizeof(quad::textureCoordinates), nullptr, GL_STATIC_DRAW);
		mglBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad::vertices), quad::vertices);
		mglBufferSubData(GL_ARRAY_BUFFER, sizeof(quad::vertices), sizeof(quad::textureCoordinates), quad::textureCoordinates);

		//vertices
		mglVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
		mglEnableVertexAttribArray(0);

		//texturecoordinates
		mglVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(18 * sizeof(GL_FLOAT)));
		mglEnableVertexAttribArray(1);

		mglBindBuffer(GL_ARRAY_BUFFER, 0);
		mglBindVertexArray(0);

		//end

		mglViewport(0, 0, screenWidth, screenHeight);
		mglEnable(GL_DEPTH_TEST);
		mglDepthFunc(GL_LEQUAL);

		Resource::load();
	}
}

void ms::DeferredRenderOGL::setup_uniforms (const Scene * scene) {
	
}

bool ms::DeferredRenderOGL::is_loaded () {
	return this->gShader->is_loaded();
}

void ms::DeferredRenderOGL::unload () {
	if (is_loaded()) {
		
		mglDeleteFramebuffers(1, &gFrameBuffer);
		mglDeleteRenderbuffers(1, &gRenderBuffer);
		mglDeleteVertexArrays(1, &quadVAO);
		mglDeleteBuffers(1, &quadVBO);
		
		
		this->gAlbedo->unload();
		this->gNormal->unload();
		this->gPosition->unload();
		this->gShader->unload();
		this->lightingShader->unload();
		Resource::unload();
	}
}

void ms::DeferredRenderOGL::set_default_FBO (GLuint defFBO) {
	defaultFBO = defFBO;
}

void ms::DeferredRenderOGL::perform_light_pass (const Scene * scene) {
	mglBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
	
	mglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	lightingShader->use();
	
	lightingShader->set_rendering_mode(this->renderMode);
	
	if(auto dirLight = scene->get_directional_light()) {
		lightingShader->set_has_directional_light(true);
		lightingShader->set_directional_light_dir(dirLight->direction);
		lightingShader->set_directional_light_color(dirLight->color);
	} else {
		lightingShader->set_has_directional_light(false);
	}
	
	{
		const std::vector<SpotLight> & spotLights = scene->get_spot_lights();
		lightingShader->set_amount_of_spot_lights(static_cast<int>(spotLights.size()));
		for(unsigned int index = 0; index < spotLights.size(); ++index) {
			lightingShader->set_spot_light_power(index, spotLights[index].power);
			lightingShader->set_spot_light_color(index, spotLights[index].color);
			lightingShader->set_spot_light_position(index, spotLights[index].position);
			lightingShader->set_spot_light_angle(index, spotLights[index].lightingAngleDegrees);
			lightingShader->set_spot_light_direction(index, spotLights[index].direction);
		}
	}
	
	{
		const std::vector<PointLight> & pointLights = scene->get_point_lights();
		lightingShader->set_amount_of_point_lights(static_cast<int>(pointLights.size()));
		for(unsigned int index = 0; index < pointLights.size(); ++index) {
			lightingShader->set_point_light_color(index, pointLights[index].color);
			lightingShader->set_point_light_power(index, pointLights[index].power);
			lightingShader->set_point_light_position(index, pointLights[index].position);
		}
	}
	
	mglBindVertexArray(quadVAO);
	
	mglActiveTexture(GL_TEXTURE0);
	gPosition->use();
	
	mglActiveTexture(GL_TEXTURE1);
	gNormal->use();
	
	mglActiveTexture(GL_TEXTURE2);
	gAlbedo->use();
	
	mglDrawArrays(GL_TRIANGLES, 0, 6);
	
	mglBindFramebuffer(GL_READ_FRAMEBUFFER, gFrameBuffer);
	mglBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFBO);
	mglBlitFramebuffer(0, 0, frameBufferWidth, frameBufferHeight, 0, 0, frameBufferWidth, frameBufferHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	mglBindFramebuffer(GL_FRAMEBUFFER, 0);
}

