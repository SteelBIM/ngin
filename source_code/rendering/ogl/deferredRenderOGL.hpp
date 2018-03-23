//
//  deferredRenderOGL.hpp
//  ngin
//
//  Created by Mateusz Stompór on 06/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef deferred_render_ogl_hpp
#define deferred_render_ogl_hpp

#include "../../utils/ogl/proxyOGL.hpp"
#include "../deferredRender.hpp"
#include "../shaders/ogl/deferredShaderOGL.hpp"
#include "../shaders/ogl/deferredLightingShaderOGL.hpp"
#include "../reusableGeometry.hpp"
#include "../../utils/ogl/utilsOGL.hpp"
#include "../../scene/ogl/textureOGL.hpp"
#include "framebufferOGL.hpp"
#include "renderbufferOGL.hpp"

namespace ms {
	
	class DeferredRenderOGL : public DeferredRender {
		
		public:
		
			DeferredRenderOGL					(unsigned int maximalAmountOfLights,
												 std::string gBufferVertexShaderSource,
												 std::string gBufferFragmentShaderSource,
												 std::string lightingVertexShaderSource,
												 std::string lightingFragmentShaderSource,
												 std::shared_ptr<Framebuffer> framebuffer);
		
			void	use     					() 												override;
			void 	clear_frame					()												override;
			void 	draw						(Drawable * node, const Scene * scene) 			override;
			void	load						() 												override;
			bool	is_loaded					() 												override;
			void 	unload						() 												override;
			void 	perform_light_pass			(const Scene * scene) 							override;
			virtual	~DeferredRenderOGL 			() = default;
		
		protected:
				
			GLuint						quadVAO;
			GLuint						quadVBO;
		
	};
	
}

#endif /* deferred_render_ogl_hpp */
