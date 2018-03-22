/*
 *  coast_lines.h
 *  
 *  This is a utility function adapted from the instructions on the 
 *  Apple Developer's website on how to create a 
 *  Frame Buffer Object. 
 *  It creates a FBO and draws the coastlines into and loads it as a texture.
 *
 *  Created by Sarah Block on 2/26/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */
#define GLEW_STATIC
#include "glew.h"
#include "colorbar.h"
#include "map_builder.h"
#include <FL/fl_ask.H>

#ifdef __APPLE__
#include <unistd.h>
#endif

/**
 * This is adapted from the sample code for E234 Spring 2007
 * http://courses.dce.harvard.edu/~cscie234/
 */
#define EXTENSION_NAMES                         \
    FUNC(GLEW_ARB_depth_texture),               \
    FUNC(GLEW_ARB_fragment_program),            \
    FUNC(GLEW_ARB_fragment_shader),             \
    FUNC(GLEW_ARB_multisample),                 \
    FUNC(GLEW_ARB_occlusion_query),             \
    FUNC(GLEW_ARB_shader_objects),              \
    FUNC(GLEW_ARB_shading_language_100),        \
    FUNC(GLEW_ARB_shadow),                      \
    FUNC(GLEW_ARB_texture_cube_map),            \
    FUNC(GLEW_ARB_vertex_buffer_object),        \
    FUNC(GLEW_ARB_vertex_program),              \
    FUNC(GLEW_ARB_vertex_shader),               \
    FUNC(GLEW_ARB_draw_buffers),                \
    FUNC(GLEW_ATI_texture_float),               \
    FUNC(GLEW_EXT_blend_minmax),                \
    FUNC(GLEW_EXT_framebuffer_object),          \
    FUNC(GLEW_EXT_texture_rectangle),           \
    FUNC(GLEW_NV_occlusion_query),				\
	FUNC(GLEW_EXT_framebuffer_object)
	
//----List of extensions supported by the GL driver
#define FUNC(x) x
static int extensionsPresent[] = {
	EXTENSION_NAMES,
};
#undef FUNC

//----List of extension names
#define FUNC(x) #x
static const char *extensionNames[] = {
	EXTENSION_NAMES,
};
#undef FUNC
bool draw_coastlines(const char *filename, int w, int h);

/**
 * This code was adapted from the code on the Apple website for creating a frame buffer
 * object in Mac OSX: 
 * Apple Developer Website: Frame Buffer Objects (2007)
 * http://developer.apple.com/documentation/GraphicsImaging/Conceptual/
 * OpenGL-MacProgGuide/opengl_offscreen/chapter_5_section_5.html
 *
 * It creates a FBO and draws the coastlines into and loads it as a texture.
 *
 */
bool init_coastlines(const char *filename, int w, int w);

/**
 * This method is a way to create the coastlines on a system that
 * doesn't support FBO's
 */
void plot_coastlines(int w, int h);
	
