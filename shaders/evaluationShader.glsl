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
    //return (1 - t) * (1 - t) * (1 - t); //Bezier

    return ((1.0 - t) * (1.0 - t) * (1.0 - t)) / 6.0; //B-Spline
}

float b1(float t) {
    //return 3 * (1-t) * (1-t) * t; //Bezier

    return (4.0 - (6.0 * t * t) + (3.0 * t * t * t)) / 6.0; //B-Spline
}

float b2(float t) {
    //return 3 * (1-t) * t * t; //Bezier

    return (1.0 + (3.0 * t) + (3.0 * t * t) - (3.0 * t * t * t)) / 6.0; //B-Spline
}

float b3(float t) {
    //return t * t * t; //Bezier

    return (t * t * t) / 6.0; //B-Spline
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

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;


    vec4 p1 = mix(gl_in[6].gl_Position,gl_in[5].gl_Position,gl_TessCoord.x);
    vec4 p2 = mix(gl_in[10].gl_Position,gl_in[9].gl_Position,gl_TessCoord.x);
    gl_Position = mix(p1, p2, gl_TessCoord.y);



//    gl_Position = b0(u) * ( b0(v) * p00 + b1(v) * p01 + b2(v) * p02 + b3(v) * p03 )
//                + b1(u) * ( b0(v) * p10 + b1(v) * p11 + b2(v) * p12 + b3(v) * p13 )
//                + b2(u) * ( b0(v) * p20 + b1(v) * p21 + b2(v) * p22 + b3(v) * p23 )
//                + b3(u) * ( b0(v) * p30 + b1(v) * p31 + b2(v) * p32 + b3(v) * p33 );

    gl_Position = projectionmatrix * modelviewmatrix * gl_Position;

    vertcoords_camera_fs = tess_vertcoords_camera_fs[0];
    vertnormal_camera_fs = tess_vertnormal_camera_fs[0];
}
