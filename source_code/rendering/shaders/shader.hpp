//
//  shader.hpp
//  ngin
//
//  Created by Mateusz Stompór on 02/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include "../../resources/resource.hpp"
#include "../../scene/texture.hpp"

namespace ms {
    
	class Shader : public Resource {
		
	public:
		
			virtual void 			bind_texture	(unsigned int 	index,
													 Texture & 		texture) = 0;
		
			virtual void 			use 			() = 0;
	inline 	virtual std::string		get_class		() = 0;
			virtual 				~Shader			() = default;
    };
    
}

std::string ms::Shader::get_class () {
	return "ms::Shader";
}

#endif /* shader_hpp */
