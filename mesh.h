#ifndef MESH_H
#define MESH_H

#include <QVector>

#include "patch.h"
#include "vertex.h"
#include "face.h"
#include "halfedge.h"

#include "objfile.h"

//#define MAX_INT ((unsigned int) -1)

class Mesh {

public:
    Mesh();
    Mesh(OBJFile *loadedOBJFile);
    ~Mesh();

    inline QVector<Vertex>& getVertices() { return vertices; }
    inline QVector<HalfEdge>& getHalfEdges() { return halfEdges; }
    inline QVector<Face>& getFaces() { return faces; }

    inline QVector<QVector3D>& getLimitCoords() { return limitCoords; }
    inline QVector<QVector3D>& getVertexCoords() { return vertexCoords; }
    inline QVector<QVector3D>& getTessVertexCoords() { return tessCoords; }
    inline QVector<QVector3D>& getTessVertexNorms() { return tessNormals; }
    inline QVector<QVector3D>& getVertexNorms() { return vertexNormals; }
    inline QVector<QVector3D>& getLimitNorms() { return limitNormals; }
    inline QVector<unsigned int>& getPolyIndices() { return polyIndices; }
    inline QVector<unsigned int>& getTessIndices() { return tessIndices; }

    void setTwins(unsigned int numHalfEdges, unsigned int indexH, QVector<QVector<unsigned int>>& potentialTwins);

    QVector3D facePoint(Face* firstEdge);
    QVector3D edgePoint(HalfEdge* firstEdge, QVector<Vertex>& newVertices);
    QVector3D vertexPoint(HalfEdge* firstEdge, QVector<Vertex>& newVertices);

    void subdivideLoop(Mesh& mesh);

    void extractAttributes();

    //QVector<QVector<unsigned int> > PotentialTwins;

    void setFaceNormal(Face* currentFace);
    QVector3D computeVertexNormal(Vertex* currentVertex);
    QVector3D computeLimitNormal(Vertex* currentVertex);

    // For debugging
    void dispVertInfo(unsigned short vertIndex);
    void dispHalfEdgeInfo(unsigned short edgeIndex);
    void dispFaceInfo(unsigned short faceIndex);

    void static computeLimitMesh(Mesh& mesh);
    void static computeQuadPatches(Mesh& mesh);

    inline int patchCount() { return tessPatches.size(); };
    void subdivideCatmullClark(Mesh& mesh);
    void splitHalfEdges(QVector<Vertex>& newVertices, QVector<HalfEdge>& newHalfEdges);
private:
    QVector<Vertex> vertices;
    QVector<Face> faces;
    QVector<HalfEdge> halfEdges;

    QVector<QVector3D> vertexCoords;
    QVector<QVector3D> limitCoords;
    QVector<QVector3D> limitNormals;

    QVector<QVector3D> vertexNormals;
    QVector<unsigned int> polyIndices;

    QVector<QuadPatch> tessPatches;
    QVector<QVector3D> tessCoords;
    QVector<QVector3D> tessNormals;
    QVector<unsigned int> tessIndices;

};

#endif // MESH_H
