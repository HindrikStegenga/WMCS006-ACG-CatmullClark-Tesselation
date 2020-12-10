#version 410

layout(quads, equal_spacing, ccw) in;

in vec3 tess_vertcoords_camera_fs[];
in vec3 tess_vertnormal_camera_fs[];

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;

uniform bool analyticalNormals;

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

// Partial derivatives
float pd_b0(float t) {
    return (- 3.0 * (1.0 - t) * (1.0 - t)) / 6.0;
}

float pd_b1(float t) {
    return (t * (3.0 * t - 4.0)) / 2.0;
}

float pd_b2(float t) {
    return (- 9.0 * t * t + 6.0 * t + 3.0) / 6.0;
}

float pd_b3(float t) {
    return (t * t) / 2.0;
}

void main() {

    vec4 p00 = gl_in[ 0].gl_Position;
    vec4 p01 = gl_in[ 1].gl_Position;
    vec4 p02 = gl_in[ 2].gl_Position;
    vec4 p03 = gl_in[ 3].gl_Position;
    vec4 p04 = gl_in[ 4].gl_Position;
    vec4 p05 = gl_in[ 5].gl_Position;
    vec4 p06 = gl_in[ 6].gl_Position;
    vec4 p07 = gl_in[ 7].gl_Position;
    vec4 p08 = gl_in[ 8].gl_Position;
    vec4 p09 = gl_in[ 9].gl_Position;
    vec4 p10 = gl_in[10].gl_Position;
    vec4 p11 = gl_in[11].gl_Position;
    vec4 p12 = gl_in[12].gl_Position;
    vec4 p13 = gl_in[13].gl_Position;
    vec4 p14 = gl_in[14].gl_Position;
    vec4 p15 = gl_in[15].gl_Position;

    vec3 pc00 = tess_vertcoords_camera_fs[ 0];
    vec3 pc01 = tess_vertcoords_camera_fs[ 1];
    vec3 pc02 = tess_vertcoords_camera_fs[ 2];
    vec3 pc03 = tess_vertcoords_camera_fs[ 3];
    vec3 pc04 = tess_vertcoords_camera_fs[ 4];
    vec3 pc05 = tess_vertcoords_camera_fs[ 5];
    vec3 pc06 = tess_vertcoords_camera_fs[ 6];
    vec3 pc07 = tess_vertcoords_camera_fs[ 7];
    vec3 pc08 = tess_vertcoords_camera_fs[ 8];
    vec3 pc09 = tess_vertcoords_camera_fs[ 9];
    vec3 pc10 = tess_vertcoords_camera_fs[10];
    vec3 pc11 = tess_vertcoords_camera_fs[11];
    vec3 pc12 = tess_vertcoords_camera_fs[12];
    vec3 pc13 = tess_vertcoords_camera_fs[13];
    vec3 pc14 = tess_vertcoords_camera_fs[14];
    vec3 pc15 = tess_vertcoords_camera_fs[15];

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // use basis functions to compute position of the vertex using tensor product.
    gl_Position = b0(u) * ( b0(v) * p00 + b1(v) * p04 + b2(v) * p08 + b3(v) * p12 )
                + b1(u) * ( b0(v) * p01 + b1(v) * p05 + b2(v) * p09 + b3(v) * p13 )
                + b2(u) * ( b0(v) * p02 + b1(v) * p06 + b2(v) * p10 + b3(v) * p14 )
                + b3(u) * ( b0(v) * p03 + b1(v) * p07 + b2(v) * p11 + b3(v) * p15 );

    // Apply projectionmatrix and modelviewmatrix
    gl_Position = projectionmatrix * modelviewmatrix * gl_Position;


    // Repeat this process for vertcoords_camera_fs
    vertcoords_camera_fs = b0(u) * ( b0(v) * pc00 + b1(v) * pc04 + b2(v) * pc08 + b3(v) * pc12 )
                         + b1(u) * ( b0(v) * pc01 + b1(v) * pc05 + b2(v) * pc09 + b3(v) * pc13 )
                         + b2(u) * ( b0(v) * pc02 + b1(v) * pc06 + b2(v) * pc10 + b3(v) * pc14 )
                         + b3(u) * ( b0(v) * pc03 + b1(v) * pc07 + b2(v) * pc11 + b3(v) * pc15 );

    // Apply model view matrix
    vertcoords_camera_fs = vec3(modelviewmatrix * vec4(vertcoords_camera_fs, 1.0));



    if (analyticalNormals == false) {

        vec3 pn00 = tess_vertnormal_camera_fs[ 0];
        vec3 pn01 = tess_vertnormal_camera_fs[ 1];
        vec3 pn02 = tess_vertnormal_camera_fs[ 2];
        vec3 pn03 = tess_vertnormal_camera_fs[ 3];
        vec3 pn04 = tess_vertnormal_camera_fs[ 4];
        vec3 pn05 = tess_vertnormal_camera_fs[ 5];
        vec3 pn06 = tess_vertnormal_camera_fs[ 6];
        vec3 pn07 = tess_vertnormal_camera_fs[ 7];
        vec3 pn08 = tess_vertnormal_camera_fs[ 8];
        vec3 pn09 = tess_vertnormal_camera_fs[ 9];
        vec3 pn10 = tess_vertnormal_camera_fs[10];
        vec3 pn11 = tess_vertnormal_camera_fs[11];
        vec3 pn12 = tess_vertnormal_camera_fs[12];
        vec3 pn13 = tess_vertnormal_camera_fs[13];
        vec3 pn14 = tess_vertnormal_camera_fs[14];
        vec3 pn15 = tess_vertnormal_camera_fs[15];

        // Repeat the aforementioned process for vertnormal_camera_fs
        vertnormal_camera_fs = b0(u) * ( b0(v) * pn00 + b1(v) * pn04 + b2(v) * pn08 + b3(v) * pn12 )
                             + b1(u) * ( b0(v) * pn01 + b1(v) * pn05 + b2(v) * pn09 + b3(v) * pn13 )
                             + b2(u) * ( b0(v) * pn02 + b1(v) * pn06 + b2(v) * pn10 + b3(v) * pn14 )
                             + b3(u) * ( b0(v) * pn03 + b1(v) * pn07 + b2(v) * pn11 + b3(v) * pn15 );

        // And apply the normalization and normalmatrix multiply.
        vertnormal_camera_fs = normalize(normalmatrix * vertnormal_camera_fs);

    } else {
        // use derivatives of the basis functions to compute analytical normal of the vertex using tensor product.
        // I chose to just do the normal computation in world space for the vertices, since the position
        // doesn't matter for computing a normal anyway.

        // Tangent vector in u direction
        vec4 dpdu =   pd_b0(u) * ( b0(v) * p00 + b1(v) * p04 + b2(v) * p08 + b3(v) * p12 )
                    + pd_b1(u) * ( b0(v) * p01 + b1(v) * p05 + b2(v) * p09 + b3(v) * p13 )
                    + pd_b2(u) * ( b0(v) * p02 + b1(v) * p06 + b2(v) * p10 + b3(v) * p14 )
                    + pd_b3(u) * ( b0(v) * p03 + b1(v) * p07 + b2(v) * p11 + b3(v) * p15 );

        // Tangent vector in v direction
        vec4 dpdv =   b0(u) * ( pd_b0(v) * p00 + pd_b1(v) * p04 + pd_b2(v) * p08 + pd_b3(v) * p12 )
                    + b1(u) * ( pd_b0(v) * p01 + pd_b1(v) * p05 + pd_b2(v) * p09 + pd_b3(v) * p13 )
                    + b2(u) * ( pd_b0(v) * p02 + pd_b1(v) * p06 + pd_b2(v) * p10 + pd_b3(v) * p14 )
                    + b3(u) * ( pd_b0(v) * p03 + pd_b1(v) * p07 + pd_b2(v) * p11 + pd_b3(v) * p15 );

        // Cross, normalize and multiply with the normals matrix (and another normalize) to get analytical normal.
        // This normal is then interpolated in the fragment shader automatically.
        vec3 normal = normalize(cross(dpdu.xyz, dpdv.xyz));
        vertnormal_camera_fs = normalize(normalmatrix * normal);
    }
}
