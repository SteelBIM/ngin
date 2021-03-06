//
//  textureOGL.cpp
//  ngin
//
//  Created by Mateusz Stompór on 10/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include "textureOGL.hpp"

ms::TextureOGL::TextureOGL 	(Texture::Type 	type,
							 Format			format,
							 AssociatedType	associatedType,
							 unsigned int 	width,
							 unsigned int 	height) : TextureOGL(type,
																 "",
																 format,
																 associatedType,
																 width,
																 height) { }

ms::TextureOGL::TextureOGL (Texture::Type 	type,
							std::string	name,
							Format			format,
							AssociatedType	associatedType,
							unsigned int 	width,
							unsigned int 	height) : TextureOGL(type,
																 name,
																 format,
																 associatedType,
																 MinFilter::nearest,
																 MagFilter::nearest,
																 Wrapping::repeat,
																 Wrapping::repeat,
																 0,
																 width,
																 height) { }

ms::TextureOGL::TextureOGL	(Texture::Type 	textype,
							std::string		name,
							Format			internalF,
							AssociatedType	typ,
							MinFilter 		minFilter,
							MagFilter 		magFilter,
							Wrapping 		sWrapping,
							Wrapping 		tWrapping,
							unsigned int 	mipMapLevel,
							unsigned int 	wid,
							unsigned int 	hei) : 	ms::Texture(textype,
																name,
																internalF,
																typ,
																minFilter,
																magFilter,
																sWrapping,
																tWrapping,
																mipMapLevel,
																wid,
																hei) {
	
	
	target = to_ogl(textype);
	type = TextureOGL::to_ogl(typ);
	colorFormat = TextureOGL::to_ogl(internalF);
	internalFormat = underlying_type();
	this->texture = 0;
}

void ms::TextureOGL::_load () {
		mglGenTextures(1, &this->texture);
		
		mglBindTexture(this->target, this->texture);

		mglTexImage2D(this->target, this->mipMapLevel, this->internalFormat, width, height, 0, this->colorFormat, this->type, rawData);
		delete [] this->rawData;
		rawData = nullptr;
		mglTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, to_ogl(this->minFilter));
		mglTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, to_ogl(this->magFilter));
		mglTexParameteri(this->target, GL_TEXTURE_WRAP_S, to_ogl(this->sWrapping));
		mglTexParameteri(this->target, GL_TEXTURE_WRAP_T, to_ogl(this->tWrapping));
		
		mglBindTexture(this->target, 0);
}

void ms::TextureOGL::use () {
	if(!is_loaded())
		load();
	
	mglBindTexture(this->target, this->texture);
}

void ms::TextureOGL::_unload () {
	mglDeleteTextures(1, &this->texture);
	this->texture = 0;
}

GLenum ms::TextureOGL::to_ogl (MinFilter minFilter) {
	switch (minFilter) {
		case Texture::MinFilter::nearest:
			return GL_NEAREST;
		case Texture::MinFilter::linear:
			return GL_LINEAR;
		case Texture::MinFilter::nearest_mipmap_nearest:
			return GL_NEAREST_MIPMAP_NEAREST;
		case Texture::MinFilter::linear_mipmap_nearest:
			return GL_LINEAR_MIPMAP_NEAREST;
		case Texture::MinFilter::nearest_mipmap_linear:
			return GL_NEAREST_MIPMAP_LINEAR;
		case Texture::MinFilter::linear_mipmap_linear:
			return GL_LINEAR_MIPMAP_LINEAR;
		default:
			//critical error
			assert(false);
			break;
	}
}

GLenum ms::TextureOGL::to_ogl (MagFilter magFilter) {
	switch (magFilter) {
		case Texture::MagFilter::linear:
			return GL_LINEAR;
		case Texture::MagFilter::nearest:
			return GL_NEAREST;
		default:
			//critical error
			std::cerr << "Filter type not supported" << std::endl;
			assert(false);
			break;
	}
}

GLenum ms::TextureOGL::to_ogl (Wrapping wrapping) {
	switch (wrapping) {
		case Texture::Wrapping::mirrored_repeat:
			return GL_MIRRORED_REPEAT;
		case Texture::Wrapping::repeat:
			return GL_REPEAT;
		case Texture::Wrapping::clamp_to_edge:
			return GL_CLAMP_TO_EDGE;
			
	//DOESNT RUN ON IOS
	#ifndef ios_build
		case Texture::Wrapping::clamp_to_border:
			return GL_CLAMP_TO_BORDER;
	#endif
			
		default:
			//critical error
			std::cerr << "Wrapping type not supported" << std::endl;
			assert(false);
			break;
	}
}

GLenum	ms::TextureOGL::to_ogl (Texture::Type type) {
	
	switch (type) {
		case ms::Texture::Type::tex_2d:
			return GL_TEXTURE_2D;
		case ms::Texture::Type::tex_cube_map:
			return GL_TEXTURE_CUBE_MAP;
		default:
			break;
	}
	
	std::cerr << "Texture type not supported" << std::endl;
	assert(false);
}

const GLuint ms::TextureOGL::get_underlying_id () const {
	return this->texture;
}

GLenum ms::TextureOGL::to_ogl (Format wrapping) {
	switch (wrapping) {
		case Format::rgb_8_8_8:
			return GL_RGB;
		case Format::rgb_16_16_16:
			return GL_RGB;
		case Format::rgba_8_8_8_8:
			return GL_RGBA;
		case Format::r_8:
			return GL_RED;
		default:
			std::cerr << "format not supported" << std::endl;
			assert(false);
			break;
	}
}

GLenum ms::TextureOGL::to_ogl (AssociatedType type) {
	switch (type) {
		case Texture::AssociatedType::FLOAT:
			return GL_FLOAT;
			break;
		case Texture::AssociatedType::UNSIGNED_BYTE:
			return GL_UNSIGNED_BYTE;
		default:
			std::cerr << "format not supported" << std::endl;
			assert(false);
			break;
	}
}

std::string ms::TextureOGL::get_class () {
	return "ms::TextureOGL";
}

GLenum ms::TextureOGL::underlying_type () const {
	if (this->associatedType == AssociatedType::FLOAT) {
		if (this->format == Texture::Format::rgb_16_16_16) {
			return GL_RGB16F;
		}
	} else if (this->associatedType == AssociatedType::UNSIGNED_BYTE) {
		if (this->format == Texture::Format::rgba_8_8_8_8) {
			return GL_RGBA8;
		} else if (this->format == Texture::Format::rgb_8_8_8) {
			return GL_RGB8;
		} else if (this->format == Texture::Format::r_8) {
			return GL_R8;
		}
	}
		
	std::cerr << "Format not supported" << std::endl;
	assert(false);
}

