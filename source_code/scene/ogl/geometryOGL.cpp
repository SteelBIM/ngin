//
//  geometryOGL.cpp
//  ngin
//
//  Created by Mateusz Stompór on 04/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include "geometryOGL.hpp"

void ms::GeometryOGL::load() {
	
	load_vector_to_buffer(vertices, &verticesBuffer);
//	load_vector_to_buffer(normals, &normalsBuffer);
	
	isLoaded = true;
	
	Resource::load();
	
}

void ms::GeometryOGL::use_normals () {
//	if(!isLoaded) {
//		load();
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
}

void ms::GeometryOGL::use_vertices () {
	if(!isLoaded) {
		load();
	}
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
}

void ms::GeometryOGL::load_vector_to_buffer(const std::vector<float> & v, GLuint* b) {
	glGenBuffers(1, b);
	glBindBuffer(GL_ARRAY_BUFFER, *b);
//	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), nullptr, GL_STATIC_DRAW);
	
	glBufferData(
				 GL_ARRAY_BUFFER,
				 v.size() * sizeof(float),
				 &v[0],
				 GL_STATIC_DRAW
				 );
	
	
//	float* vBuf = /*reinterpret_cast<float*>*/(float*)(glMapBufferRange(GL_ARRAY_BUFFER, 0, v.size() * sizeof(float),  GL_MAP_WRITE_BIT));
//
//	for (unsigned long long i = 0; i < v.size(); ++i) {
//		*(vBuf + i) = v[i];
//	}
//
//	glUnmapBuffer(GL_ARRAY_BUFFER);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ms::GeometryOGL::unload() {
	
	glDeleteBuffers(1, &verticesBuffer);
	glDeleteBuffers(1, &normalsBuffer);
	
	isLoaded = false;
	
	Resource::unload();
	
}
