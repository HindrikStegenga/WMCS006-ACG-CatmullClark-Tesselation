#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_world_vs;
layout (location = 1) in vec3 vertnormal_world_vs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;

layout (location = 0) out vec3 vertcoords_camera_fs;
layout (location = 1) out vec3 vertnormal_camera_fs;

void main() {
    // We simply pass through our values since we want to do the computations later in the TES.
    gl_Position = vec4(vertcoords_world_vs, 1.0);
    vertcoords_camera_fs = vertcoords_world_vs;
    vertnormal_camera_fs = vertnormal_world_vs;
}
