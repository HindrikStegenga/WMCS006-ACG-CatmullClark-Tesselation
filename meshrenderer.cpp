#include "meshrenderer.h"
#include <iostream>

MeshRenderer::MeshRenderer()
{
    meshIBOSize = 0;
}

MeshRenderer::~MeshRenderer() {
    gl->glDeleteVertexArrays(1, &vao);
    gl->glDeleteVertexArrays(1, &limitVao);
    gl->glDeleteVertexArrays(1, &tesselationVao);

    gl->glDeleteBuffers(1, &meshLimitCoordsBO);
    gl->glDeleteBuffers(1, &meshLimitNormalsBO);

    gl->glDeleteBuffers(1, &tessCoordsBO);
    gl->glDeleteBuffers(1, &tessNormalsBO);

    gl->glDeleteBuffers(1, &meshCoordsBO);
    gl->glDeleteBuffers(1, &meshNormalsBO);
    gl->glDeleteBuffers(1, &meshIndexBO);
}

void MeshRenderer::init(QOpenGLFunctions_4_1_Core* f, Settings* s) {
    gl = f;
    settings = s;

    initShaders();
    initBuffers();
}

void MeshRenderer::initShaders() {
    shaderProg.create();
    shaderProg.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    shaderProg.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");

    shaderProg.link();

    uniModelViewMatrix = gl->glGetUniformLocation(shaderProg.programId(), "modelviewmatrix");
    uniProjectionMatrix = gl->glGetUniformLocation(shaderProg.programId(), "projectionmatrix");
    uniNormalMatrix = gl->glGetUniformLocation(shaderProg.programId(), "normalmatrix");


    tessShaderProg.create();
    tessShaderProg.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/tessVertShader.glsl");
    tessShaderProg.addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/shaders/controlShader.glsl");
    tessShaderProg.addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/shaders/evaluationShader.glsl");
    tessShaderProg.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");

    tessShaderProg.link();

    uniModelViewMatrixTess = gl->glGetUniformLocation(tessShaderProg.programId(), "modelviewmatrix");
    uniProjectionMatrixTess = gl->glGetUniformLocation(tessShaderProg.programId(), "projectionmatrix");
    uniNormalMatrixTess = gl->glGetUniformLocation(tessShaderProg.programId(), "normalmatrix");
}

void MeshRenderer::initBuffers() {

    // Regular drawing
    gl->glGenVertexArrays(1, &vao);
    gl->glBindVertexArray(vao);

    gl->glGenBuffers(1, &meshCoordsBO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, meshCoordsBO);
    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    gl->glGenBuffers(1, &meshNormalsBO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, meshNormalsBO);
    gl->glEnableVertexAttribArray(1);
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    gl->glGenBuffers(1, &meshIndexBO);
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIndexBO);

    gl->glBindVertexArray(0);

    // Limit surface variant
    gl->glGenVertexArrays(1, &limitVao);
    gl->glBindVertexArray(limitVao);

    gl->glGenBuffers(1, &meshLimitCoordsBO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, meshLimitCoordsBO);
    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    gl->glGenBuffers(1, &meshLimitNormalsBO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, meshLimitNormalsBO);
    gl->glEnableVertexAttribArray(1);
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIndexBO);

    gl->glBindVertexArray(0);

    // Tesselated drawing
    gl->glGenVertexArrays(1, &tesselationVao);
    gl->glBindVertexArray(tesselationVao);

    gl->glGenBuffers(1, &tessCoordsBO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, tessCoordsBO);
    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    gl->glGenBuffers(1, &tessNormalsBO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, tessNormalsBO);
    gl->glEnableVertexAttribArray(1);
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    gl->glBindVertexArray(0);

}

QVector<QVector3D> createPlanarMesh(bool normals) {
    QVector<QVector3D> points;

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j){
            if(normals)
                points.push_back(QVector3D(0.0, 1.0, 0.0));
            else
            points.push_back(QVector3D(-1.5 + i, -1.5 + j, 0.0));
        }
    }

    points[5].setZ(2.25);
    points[6].setZ(2.25);
    points[9].setZ(2.25);
    points[10].setZ(2.25);

    return points;
}

void MeshRenderer::updateBuffers(Mesh& currentMesh) {

    qDebug() << ".. updateBuffers";

    //gather attributes for current mesh
    currentMesh.extractAttributes();



    QVector<QVector3D>& vertexCoords = currentMesh.getVertexCoords();
    QVector<QVector3D>& vertexNormals = currentMesh.getVertexNorms();
    QVector<unsigned int>& polyIndices = currentMesh.getPolyIndices();
    QVector<QVector3D>& vertexLimitCoords = currentMesh.getLimitCoords();
    QVector<QVector3D>& vertexLimitNormals = currentMesh.getLimitNorms();

    auto test = createPlanarMesh(false);
    auto test2 = createPlanarMesh(true);

    QVector<QVector3D>& tessVertCoords = test; //currentMesh.getTessVertexCoords();
    QVector<QVector3D>& tessVertNorms = test2; //currentMesh.getTessVertexNorms();


    gl->glBindBuffer(GL_ARRAY_BUFFER, meshCoordsBO);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertexCoords.size(), vertexCoords.data(), GL_DYNAMIC_DRAW);
    qDebug() << " → Updated meshCoordsBO";


    gl->glBindBuffer(GL_ARRAY_BUFFER, meshNormalsBO);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertexNormals.size(), vertexNormals.data(), GL_DYNAMIC_DRAW);

    qDebug() << " → Updated meshNormalsBO";



    gl->glBindBuffer(GL_ARRAY_BUFFER, meshLimitCoordsBO);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertexLimitCoords.size(), vertexLimitCoords.data(), GL_DYNAMIC_DRAW);
    qDebug() << " → Updated meshLimitCoordsBO";


    gl->glBindBuffer(GL_ARRAY_BUFFER, meshLimitNormalsBO);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertexLimitNormals.size(), vertexLimitNormals.data(), GL_DYNAMIC_DRAW);

    qDebug() << " → Updated meshLimitNormalsBO";

    gl->glBindBuffer(GL_ARRAY_BUFFER, tessCoordsBO);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*tessVertCoords.size(), tessVertCoords.data(), GL_DYNAMIC_DRAW);
    qDebug() << " → Updated tesselation coords.";

    gl->glBindBuffer(GL_ARRAY_BUFFER, tessNormalsBO);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*tessVertNorms.size(), tessVertNorms.data(), GL_DYNAMIC_DRAW);

    qDebug() << " → Updated meshLimitNormalsBO";


    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIndexBO);
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*polyIndices.size(), polyIndices.data(), GL_DYNAMIC_DRAW);

    qDebug() << " → Updated meshIndexBO";

    patchCount = currentMesh.patchCount();
    meshIBOSize = polyIndices.size();
}

void MeshRenderer::updateUniforms() {

    shaderProg.bind();
    gl->glUniformMatrix4fv(uniModelViewMatrix, 1, false, settings->modelViewMatrix.data());
    gl->glUniformMatrix4fv(uniProjectionMatrix, 1, false, settings->projectionMatrix.data());
    gl->glUniformMatrix3fv(uniNormalMatrix, 1, false, settings->normalMatrix.data());
    shaderProg.release();
    tessShaderProg.bind();
    gl->glUniformMatrix4fv(uniModelViewMatrixTess, 1, false, settings->modelViewMatrix.data());
    gl->glUniformMatrix4fv(uniProjectionMatrixTess, 1, false, settings->projectionMatrix.data());
    gl->glUniformMatrix3fv(uniNormalMatrixTess, 1, false, settings->normalMatrix.data());

    tessShaderProg.release();
}

void MeshRenderer::draw() {
    if (settings->uniformUpdateRequired) {
        updateUniforms();
        settings->uniformUpdateRequired = false;
    }
    if (settings->tesselation) {
        tesselatedDraw();
    } else {
        regularDraw();
    }

}

void MeshRenderer::regularDraw() {

    shaderProg.bind();
    //enable primitive restart
    gl->glEnable(GL_PRIMITIVE_RESTART);
    gl->glPrimitiveRestartIndex(INT_MAX);

    shaderProg.setUniformValue("materialColour", 0.53, 0.80, 0.87);


    GLint MaxPatchVertices = 0;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
    printf("Max supported patch vertices %d\n", MaxPatchVertices);

    if(settings->limitVertices) {
        // Draw limit surface.
        shaderProg.setUniformValue("materialColour", 0.5, 0.5, 0.5);
        shaderProg.setUniformValue("approxFlatShading", settings->approxFlatShadeLimitSurface);
        if(settings->limitFilledTriangles) {
            gl->glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            gl->glBindVertexArray(limitVao);
            gl->glDrawElements(GL_TRIANGLE_FAN, meshIBOSize, GL_UNSIGNED_INT, 0);
            gl->glBindVertexArray(0);
        } else {
            shaderProg.setUniformValue("approxFlatShading", false);
            gl->glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            gl->glBindVertexArray(limitVao);
            gl->glDrawElements(GL_LINE_LOOP, meshIBOSize, GL_UNSIGNED_INT, 0);
            gl->glBindVertexArray(0);
        }

        // Draw regular variant
        shaderProg.setUniformValue("materialColour", 0.0, 0.0, 1.0);
        shaderProg.setUniformValue("approxFlatShading", false);
        gl->glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
        gl->glBindVertexArray(vao);
        gl->glDrawElements(GL_LINE_LOOP, meshIBOSize, GL_UNSIGNED_INT, 0);
        gl->glBindVertexArray(0);
    } else {
        shaderProg.setUniformValue("materialColour", 0.53, 0.80, 0.87);
        gl->glBindVertexArray(vao);

        if (settings->wireframeMode) {
            shaderProg.setUniformValue("approxFlatShading", false);
            gl->glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            gl->glDrawElements(GL_LINE_LOOP, meshIBOSize, GL_UNSIGNED_INT, 0);
        } else {
            shaderProg.setUniformValue("approxFlatShading", settings->approxFlatShadeSurface);
            gl->glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            gl->glDrawElements(GL_TRIANGLE_FAN, meshIBOSize, GL_UNSIGNED_INT, 0);
        }

        gl->glBindVertexArray(0);
    }

    shaderProg.release();

    //disable it again as you might want to draw something else at some point
    gl->glDisable(GL_PRIMITIVE_RESTART);
}

void MeshRenderer::tesselatedDraw() {
    QOpenGLShaderProgram& shaderProgram = tessShaderProg;

    shaderProgram.bind();
    shaderProgram.setUniformValue("materialColour", 1.0, 0.0, 0.0);
    shaderProgram.setUniformValue("approxFlatShading", false);

    tessShaderProg.setUniformValue("tessInner0", settings->tessLevelInner0);
    tessShaderProg.setUniformValue("tessInner1", settings->tessLevelInner1);
    tessShaderProg.setUniformValue("tessOuter0", settings->tessLevelOuter0);
    tessShaderProg.setUniformValue("tessOuter1", settings->tessLevelOuter1);
    tessShaderProg.setUniformValue("tessOuter2", settings->tessLevelOuter2);
    tessShaderProg.setUniformValue("tessOuter3", settings->tessLevelOuter3);

    gl->glBindVertexArray(tesselationVao);
    std::cout << glGetError() << std::endl;
    gl->glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    std::cout << glGetError() << std::endl;
    gl->glPatchParameteri(GL_PATCH_VERTICES, 16);
    std::cout << glGetError() << std::endl;
    gl->glDrawArrays(GL_PATCHES, 0, 16);
    std::cout << glGetError() << std::endl;

    gl->glBindVertexArray(0);
    shaderProgram.release();
}
