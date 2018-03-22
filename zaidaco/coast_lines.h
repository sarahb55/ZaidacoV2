/*
 *  coast_lines.h
 *  COLOR
 *
 *  Created by Sarah Block on 2/26/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#define GLEW_STATIC
#include "glew.h"
#include "colorbar.h"
#include "map_builder.h"


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

void init_coastlines();
