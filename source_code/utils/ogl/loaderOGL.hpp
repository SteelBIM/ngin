//
//  loaderOGL.hpp
//  ngin
//
//  Created by Mateusz Stompór on 12/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef loaderOGL_hpp
#define loaderOGL_hpp

#include "../loader.hpp"
#include "../../scene/ogl/geometryOGL.hpp"
#include "../../scene/ogl/textureOGL.hpp"

namespace ms {

	class LoaderOGL : public Loader {
	
	public:
		
	protected:
		
		inline virtual std::shared_ptr<Geometry> 		get_geometry	() override;
		inline virtual std::shared_ptr<Texture> 		get_texture		(std::string				name,
																		 Texture::Format			format,
																		 Texture::AssociatedType	associatedType,
																		 Texture::MinFilter			minFilter,
																		 Texture::MagFilter			magFilter,
																		 Texture::Wrapping			sWrapping,
																		 Texture::Wrapping			tWrapping,
																		 unsigned int 				mipMapLevel,
																		 unsigned int 				width,
																		 unsigned int 				height) override;
	};
	
}

std::shared_ptr<ms::Geometry> ms::LoaderOGL::get_geometry() {
	return std::shared_ptr<ms::Geometry>(new GeometryOGL());
}

std::shared_ptr<ms::Texture> ms::LoaderOGL::get_texture (std::string				name,
														 Texture::Format			format,
														 Texture::AssociatedType	associatedType,
														 Texture::MinFilter			minFilter,
														 Texture::MagFilter			magFilter,
														 Texture::Wrapping			sWrapping,
														 Texture::Wrapping			tWrapping,
														 unsigned int 				mipMapLevel,
														 unsigned int 				width,
														 unsigned int 				height) {
	
	return std::shared_ptr<ms::Texture>(new TextureOGL(GL_TEXTURE_2D,
													   name,
													   format,
													   associatedType,
													   minFilter,
													   magFilter,
													   sWrapping,
													   tWrapping,
													   mipMapLevel,
													   width,
													   height));
	
}

#endif /* loaderOGL_hpp */