//
//  textureOGL.hpp
//  ngin
//
//  Created by Mateusz Stompór on 10/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef textureOGL_hpp
#define textureOGL_hpp

#include <cassert>

#include "../../utils/ogl/proxyOGL.hpp"
#include "../texture.hpp"

namespace ms {
	
	class TextureOGL : public Texture {
		
	public:
		
						TextureOGL			(	GLenum 			target,
												GLint			internalFormat,
												GLenum			format,
											 	GLenum 			type,
												MinFilter 		minFilter,
												MagFilter 		magFilter,
												Wrapping 		sWrapping,
												Wrapping 		tWrapping,
												unsigned int 	mipMapLevel,
												unsigned int 	width,
												unsigned int 	height
											 );
		
		const GLuint	get_underlying_id	() const;
		
		virtual void    load  				() override;
		virtual void 	unload 				() override;
		virtual void 	use					() override;
						~TextureOGL			() = default;
		
		static GLenum	to_ogl				(MinFilter 		minFilter);
		static GLenum	to_ogl				(MagFilter 		magFilter);
		static GLenum	to_ogl				(Wrapping 		wrapping);
		
	protected:
		
		GLint			internalFormat;
		GLenum			colorFormat;
		GLenum			type;
		GLenum			target;
		GLuint			texture;
		
	};
	
}

#endif /* textureOGL_hpp */
