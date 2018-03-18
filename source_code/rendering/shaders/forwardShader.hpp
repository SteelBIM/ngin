//
//  forwardShader.hpp
//  ngin
//
//  Created by Mateusz Stompór on 06/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef forward_shader_hpp
#define forward_shader_hpp

#include "shader.hpp"
#include "../../../libs/source/glMath.h"

namespace ms {
	
	class ForwardShader : public virtual Shader {
		
	public:
		
		virtual void	set_projection_matrix		(const math::mat4 & proj) 							= 0;
		virtual void	set_camera_transformation	(const math::mat4 & transf) 						= 0;
		virtual void	set_model_transformation	(const math::mat4 & transf) 						= 0;
		
		virtual void 	set_amount_of_point_lights	(int amount) 										= 0;
		virtual void 	set_point_light_power		(unsigned int index, float power) 					= 0;
		virtual void 	set_point_light_color		(unsigned int index, const math::vec4 & color) 		= 0;
		virtual void 	set_point_light_position	(unsigned int index, const math::vec3 & position) 	= 0;
		
		virtual void 	set_amount_of_spot_lights	(int amount)										= 0;
		virtual void 	set_spot_light_power		(unsigned int index, float power) 					= 0;
		virtual void 	set_spot_light_color		(unsigned int index, const math::vec4 & color) 		= 0;
		virtual void 	set_spot_light_position		(unsigned int index, const math::vec3 & position)	= 0;
		virtual void 	set_spot_light_angle		(unsigned int index, float angle) 					= 0;
		virtual void 	set_spot_light_direction	(unsigned int index, const math::vec3 direction) 	= 0;
		
		virtual void	set_has_directional_light	(bool doesItHave) 									= 0;
		virtual void	set_directional_light_dir	(const math::vec3 & dir) 							= 0;
		virtual void	set_directional_light_color	(const math::vec4 & color) 							= 0;
		
		virtual void	set_has_material			(bool doesItHave)	 								= 0;
		virtual void	set_material_ambient_color	(const math::vec3 & ambient)						= 0;
		virtual void	set_material_diffuse_color	(const math::vec3 & diffuse)						= 0;
		virtual void	set_material_specular_color	(const math::vec3 & specular)						= 0;
		virtual void	set_material_opacity		(float opacity)										= 0;
		virtual void	set_material_shininess		(float shininess)									= 0;
		
		virtual void	set_has_diffuse_texture		(bool doesItHave)	 								= 0;
		virtual void	set_has_specular_texture	(bool doesItHave)	 								= 0;
		
		virtual 		~ForwardShader()																= default;

	};
	
}

#endif /* forward_shader_hpp */
