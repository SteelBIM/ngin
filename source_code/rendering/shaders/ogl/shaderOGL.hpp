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
#include <cstdlib>

#include "../../../shaders/shaderHeaders.hpp"
#include "../../../utils/ogl/proxyOGL.hpp"
#include "../shader.hpp"

namespace ms {
	
	#define AMOUNT_SPOT_LIGHT_PROPERTIES 	5
	#define AMOUNT_POINT_LIGHT_PROPERTIES 	3
	
	namespace spotlight {
		
		#define SL_POWER			0
		#define SL_COLOR			1
		#define SL_POSITION			2
		#define SL_ANGLE_DEGREES	3
		#define SL_DIRECTION		4
		
	}
	
	namespace pointlight {
		
		#define PL_POWER			0
		#define PL_COLOR			1
		#define PL_POSITION			2
		
	}
	
}

namespace ms {
    
	class ShaderOGL : public virtual Shader {
		
	public:
		
						ShaderOGL	(std::string vertexShader,
									 std::string tessellationControlShader,
									 std::string tessellationEvaluationShader,
									 std::string geometryShader,
									 std::string fragmentShader);
		
		virtual void 	use			() override;
		virtual void 	load		() override;
		virtual void 	unload		() override;
		virtual 		~ShaderOGL	() = default;
		
	protected:
		
		void 			compile_program();
		void 			compile_shader(GLuint program, GLuint shader, GLenum shaderType, std::string source);
		int				get_shader_status(GLuint shader, GLenum statusType);
		
		std::string 	vertexSource;
		std::string 	tesselationControlSource;
		std::string		tesselationEvalutationSource;
		std::string 	geometrySource;
		std::string 	fragmentSource;
		
		GLuint 			program;
		
	};
    
}

#endif /* shader_ogl_hpp */
