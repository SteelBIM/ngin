//
//  shaderOGL.hpp
//  ngin
//
//  Created by Mateusz Stompór on 03/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef shader_ogl_hpp
#define shader_ogl_hpp

#include <memory>
#include <iostream>

#ifdef __WIN32__

	#include <glad/glad.h>

#endif

	#if __APPLE__

	#ifdef ios_build

		#import <OpenGLES/ES3/gl.h>
		#import <OpenGLES/ES3/glext.h>

	#elif mac_build

		#include <OpenGL/gl3.h>
		#include <OpenGL/gl.h>

	#endif

#endif

#include "../shader.hpp"

namespace ms {
    
	class ShaderOGL : public virtual Shader {
		
	protected:
		
		typedef std::shared_ptr<std::string> str_ptr;
		
	public:
		
		ShaderOGL(str_ptr vertexSource, str_ptr tessellationControl, str_ptr tessellationEvaluation, str_ptr geometry, str_ptr fragment);
		
		virtual void 	use			() override;
		virtual void 	load		() override;
		virtual void 	unload		() override;
		virtual 		~ShaderOGL	() = 0;
		
	protected:
		
		void 			compile_program();
		void 			compile_shader(GLuint program, GLuint shader, GLenum shaderType, str_ptr source);
		int				get_shader_status(GLuint shader, GLenum statusType);
		
		str_ptr 		vertexSource;
		str_ptr 		tesselationControlSource;
		str_ptr 		tesselationEvalutationSource;
		str_ptr 		geometrySource;
		str_ptr 		fragmentSource;
		
		GLuint 			program;
		
	};
    
}

#endif /* shader_ogl_hpp */
