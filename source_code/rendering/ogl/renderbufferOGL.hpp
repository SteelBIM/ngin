//
//  renderbufferOGL.hpp
//  ngin
//
//  Created by Mateusz Stompór on 22/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef renderbufferOGL_hpp
#define renderbufferOGL_hpp

#include <iostream>
#include <cassert>

#include "../../utils/ogl/proxyOGL.hpp"
#include "../renderbuffer.hpp"

namespace ms {
	
	class RenderbufferOGL : public Renderbuffer {
		
	public:
		
						RenderbufferOGL		(Texture::Format			format,
											Texture::AssociatedType	associatedType,
											unsigned int 				mipMapLevel,
											unsigned int 				width,
											unsigned int 				height
											);
		virtual void 	use					() override;
		virtual void    load  				() override;
		virtual void 	unload 				() override;
				GLuint	get_underlying_id	();
		
	protected:
		static GLenum	get_internal_format	(Texture::Format format, Texture::AssociatedType associatedType);
		
		GLenum			internalFormat;
		GLuint			renderBuffer;
		
	};
	
}

#endif /* renderbufferOGL_hpp */