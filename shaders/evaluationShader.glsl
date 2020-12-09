#version 410

layout(quads, equal_spacing, ccw) in;

in vec3 tess_vertcoords_camera_fs[];
in vec3 tess_vertnormal_camera_fs[];

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;

out vec3 vertcoords_camera_fs;
out vec3 vertnormal_camera_fs;


// Basis functions for B-Spline surface.
float b0(float t) {
    return ((1.0 - t) * (1.0 - t) * (1.0 - t)) / 6.0;
}

float b1(float t) {
    return (4.0 - (6.0 * t * t) + (3.0 * t * t * t)) / 6.0;
}

float b2(float t) {
    return (1.0 + (3.0 * t) + (3.0 * t * t) - (3.0 * t * t * t)) / 6.0;
}

float b3(float t) {
    return (t * t * t) / 6.0;
}

void main() {

    vec4 p00 = gl_in[ 0].gl_Position;
    vec4 p10 = gl_in[ 1].gl_Position;
    vec4 p20 = gl_in[ 2].gl_Position;
    vec4 p30 = gl_in[ 3].gl_Position;
    vec4 p01 = gl_in[ 4].gl_Position;
    vec4 p11 = gl_in[ 5].gl_Position;
    vec4 p21 = gl_in[ 6].gl_Position;
    vec4 p31 = gl_in[ 7].gl_Position;
    vec4 p02 = gl_in[ 8].gl_Position;
    vec4 p12 = gl_in[ 9].gl_Position;
    vec4 p22 = gl_in[10].gl_Position;
    vec4 p32 = gl_in[11].gl_Position;
    vec4 p03 = gl_in[12].gl_Position;
    vec4 p13 = gl_in[13].gl_Position;
    vec4 p23 = gl_in[14].gl_Position;
    vec4 p33 = gl_in[15].gl_Position;

    vec3 pc00 = tess_vertcoords_camera_fs[ 0];
    vec3 pc10 = tess_vertcoords_camera_fs[ 1];
    vec3 pc20 = tess_vertcoords_camera_fs[ 2];
    vec3 pc30 = tess_vertcoords_camera_fs[ 3];
    vec3 pc01 = tess_vertcoords_camera_fs[ 4];
    vec3 pc11 = tess_vertcoords_camera_fs[ 5];
    vec3 pc21 = tess_vertcoords_camera_fs[ 6];
    vec3 pc31 = tess_vertcoords_camera_fs[ 7];
    vec3 pc02 = tess_vertcoords_camera_fs[ 8];
    vec3 pc12 = tess_vertcoords_camera_fs[ 9];
    vec3 pc22 = tess_vertcoords_camera_fs[10];
    vec3 pc32 = tess_vertcoords_camera_fs[11];
    vec3 pc03 = tess_vertcoords_camera_fs[12];
    vec3 pc13 = tess_vertcoords_camera_fs[13];
    vec3 pc23 = tess_vertcoords_camera_fs[14];
    vec3 pc33 = tess_vertcoords_camera_fs[15];

    vec3 pn00 = tess_vertnormal_camera_fs[ 0];
    vec3 pn10 = tess_vertnormal_camera_fs[ 1];
    vec3 pn20 = tess_vertnormal_camera_fs[ 2];
    vec3 pn30 = tess_vertnormal_camera_fs[ 3];
    vec3 pn01 = tess_vertnormal_camera_fs[ 4];
    vec3 pn11 = tess_vertnormal_camera_fs[ 5];
    vec3 pn21 = tess_vertnormal_camera_fs[ 6];
    vec3 pn31 = tess_vertnormal_camera_fs[ 7];
    vec3 pn02 = tess_vertnormal_camera_fs[ 8];
    vec3 pn12 = tess_vertnormal_camera_fs[ 9];
    vec3 pn22 = tess_vertnormal_camera_fs[10];
    vec3 pn32 = tess_vertnormal_camera_fs[11];
    vec3 pn03 = tess_vertnormal_camera_fs[12];
    vec3 pn13 = tess_vertnormal_camera_fs[13];
    vec3 pn23 = tess_vertnormal_camera_fs[14];
    vec3 pn33 = tess_vertnormal_camera_fs[15];

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // use basis functions to compute position of the vertex.
    gl_Position = b0(u) * ( b0(v) * p00 + b1(v) * p01 + b2(v) * p02 + b3(v) * p03 )
                + b1(u) * ( b0(v) * p10 + b1(v) * p11 + b2(v) * p12 + b3(v) * p13 )
                + b2(u) * ( b0(v) * p20 + b1(v) * p21 + b2(v) * p22 + b3(v) * p23 )
                + b3(u) * ( b0(v) * p30 + b1(v) * p31 + b2(v) * p32 + b3(v) * p33 );

    gl_Position = projectionmatrix * modelviewmatrix * gl_Position;

    vertcoords_camera_fs = b0(u) * ( b0(v) * pc00 + b1(v) * pc01 + b2(v) * pc02 + b3(v) * pc03 )
                         + b1(u) * ( b0(v) * pc10 + b1(v) * pc11 + b2(v) * pc12 + b3(v) * pc13 )
                         + b2(u) * ( b0(v) * pc20 + b1(v) * pc21 + b2(v) * pc22 + b3(v) * pc23 )
                         + b3(u) * ( b0(v) * pc30 + b1(v) * pc31 + b2(v) * pc32 + b3(v) * pc33 );

    vertcoords_camera_fs = vec3(modelviewmatrix * vec4(vertcoords_camera_fs, 1.0));

    vertnormal_camera_fs = b0(u) * ( b0(v) * pn00 + b1(v) * pn01 + b2(v) * pn02 + b3(v) * pn03 )
                              + b1(u) * ( b0(v) * pn10 + b1(v) * pn11 + b2(v) * pn12 + b3(v) * pn13 )
                              + b2(u) * ( b0(v) * pn20 + b1(v) * pn21 + b2(v) * pn22 + b3(v) * pn23 )
                              + b3(u) * ( b0(v) * pn30 + b1(v) * pn31 + b2(v) * pn32 + b3(v) * pn33 );

    vertnormal_camera_fs = normalize(normalmatrix * vertnormal_camera_fs);
}
