#version 410

layout(quads, equal_spacing, ccw) in;

in vec3 tess_vertcoords_camera_fs[];
in vec3 tess_vertnormal_camera_fs[];

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;

out vec3 vertcoords_camera_fs;
out vec3 vertnormal_camera_fs;

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


    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // the basis functions:
    float bu0 = (1.-u) * (1.-u) * (1.-u);
    float bu1 = 3. * u * (1.-u) * (1.-u);
    float bu2 = 3. * u * u * (1.-u);
    float bu3 = u * u * u;
    float dbu0 = -3. * (1.-u) * (1.-u);
    float dbu1 =  3. * (1.-u) * (1.-3.*u);
    float dbu2 =  3. * u *      (2.-3.*u);
    float dbu3 =  3. * u *      u;
    float bv0 = (1.-v) * (1.-v) * (1.-v);
    float bv1 = 3. * v * (1.-v) * (1.-v);
    float bv2 = 3. * v * v * (1.-v);
    float bv3 = v * v * v;
    float dbv0 = -3. * (1.-v) * (1.-v);
    float dbv1 =  3. * (1.-v) * (1.-3.*v);
    float dbv2 =  3. * v *      (2.-3.*v);
    float dbv3 =  3. * v *      v;

    gl_Position = bu0 * ( bv0*p00 + bv1*p01 + bv2*p02 + bv3*p03 )
            + bu1 * ( bv0*p10 + bv1*p11 + bv2*p12 + bv3*p13 )
            + bu2 * ( bv0*p20 + bv1*p21 + bv2*p22 + bv3*p23 )
            + bu3 * ( bv0*p30 + bv1*p31 + bv2*p32 + bv3*p33 );

    vertcoords_camera_fs = vec3(modelviewmatrix * gl_Position);
    gl_Position = projectionmatrix * modelviewmatrix * gl_Position;


    vertnormal_camera_fs = tess_vertnormal_camera_fs[0];
}
