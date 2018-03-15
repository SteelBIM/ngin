//
//  texture.hpp
//  ngin
//
//  Created by Mateusz Stompór on 10/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <memory>
#include <vector>
#include <cstdint>
#include <string>

#include "../resources/resource.hpp"

//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//
//		parameters (x,y,z) in texture coordinates are called (s,t,r)	//
//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//

namespace ms {
	
	class Texture : public Resource {
		
		typedef unsigned char byte;
		
	public:
		
		enum class MinFilter;
		enum class MagFilter;
		enum class Wrapping;
		enum class Format;
		enum class AssociatedType;
		
		 inline 		Texture		(std::string			name,
									 Format					format,
									 AssociatedType			associatedType,
									 MinFilter 				minFilter,
									 MagFilter 				magFilter,
									 Wrapping 				sWrapping,
									 Wrapping 				tWrapping,
									 unsigned int 			mipMapLevel,
									 unsigned int 			width,
									 unsigned int 			height
									 );
		
		inline void		copy_data	(byte* data, size_t size);
		
		Texture &		operator = 	(const Texture &) = delete;
						Texture		(const Texture &) = delete;
		virtual void 	use			() = 0;
		inline virtual 	~Texture	();
		
	public:
	
		std::string								name;
		Format									format;
		AssociatedType							associatedType;
		MinFilter 								minFilter;
		MagFilter 								magFilter;
		Wrapping 								sWrapping;
		Wrapping 								tWrapping;
		unsigned int 							mipMapLevel;
		unsigned int 							width;
		unsigned int 							height;
		byte *									rawData;
		
	};
	
}

enum class ms::Texture::MinFilter {
	nearest,
	linear,
	nearest_mipmap_nearest,
	linear_mipmap_nearest,
	nearest_mipmap_linear,
	linear_mipmap_linear
};

enum class ms::Texture::MagFilter {
	nearest,
	linear
};

enum class ms::Texture::Wrapping {
	repeat,
	mirrored_repeat,
	clamp_to_edge,
	clamp_to_border
};

enum class ms::Texture::Format {
	rgb_16_16_16,
	rgb_8_8_8,
	rgba_8_8_8_8
};

enum class ms::Texture::AssociatedType {
	FLOAT,
	UNSIGNED_BYTE
};

ms::Texture::Texture (std::string nam,  Format f, AssociatedType aT,MinFilter minF, MagFilter magF,
					  Wrapping sWrap, Wrapping tWrap, unsigned int mipMapL, unsigned int wid, unsigned int hei) :
																																			minFilter(minF),
																																			magFilter(magF),
																																			sWrapping(sWrap),
																																			tWrapping(tWrap),
																																			mipMapLevel(mipMapL),
																																			width(wid),
																																			height(hei),
																																			name(nam),
																																			format(f),
																																			associatedType(aT),
																																			rawData(nullptr){ }

void ms::Texture::copy_data (byte* data, size_t size) {
	delete [] rawData;
	rawData = new byte [size];
	std::memcpy(rawData, data, size);
}

ms::Texture::~Texture() {
	delete [] rawData;
}

#endif /* texture_hpp */