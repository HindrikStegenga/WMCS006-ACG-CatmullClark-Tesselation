#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <QOpenGLShaderProgram>

#include "renderer.h"
#include "mesh.h"

class MeshRenderer : public Renderer
{
public:
    MeshRenderer();
    ~MeshRenderer();

    void init(QOpenGLFunctions_4_1_Core* f, Settings* s);

    void initShaders();
    void initBuffers();

    void updateUniforms();

    void updateBuffers(Mesh& m);
    void draw();


    void regularDraw();
    void tesselatedDraw();
private:

    GLuint vao, limitVao, tesselationVao;
    GLuint meshCoordsBO, meshNormalsBO, meshIndexBO,
           meshLimitCoordsBO, meshLimitNormalsBO, tessIndexBO;
    unsigned int meshIBOSize;
    unsigned int patchCount;
    QOpenGLShaderProgram shaderProg;
    QOpenGLShaderProgram tessShaderProg;

    // Uniforms
    GLint uniModelViewMatrix, uniProjectionMatrix, uniNormalMatrix;
    GLint uniModelViewMatrixTess, uniProjectionMatrixTess, uniNormalMatrixTess;
};

#endif // MESHRENDERER_H
