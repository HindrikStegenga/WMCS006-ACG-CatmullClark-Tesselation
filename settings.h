#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMatrix4x4>

class Settings
{
public:
    Settings();

    bool modelLoaded;
    int renderingMode;
    bool wireframeMode;
    bool approxFlatShading;
    int lastSubdivLevel;
    bool showNonTesselatedWireframe;
    bool analyticalNormals;

    int tessLevelInner0, tessLevelInner1, tessLevelOuter0, tessLevelOuter1, tessLevelOuter2, tessLevelOuter3;

    float FoV;
    float dispRatio;
    float rotAngle;

    bool uniformUpdateRequired;

    QMatrix4x4 modelViewMatrix, projectionMatrix;
    QMatrix3x3 normalMatrix;
};

#endif // SETTINGS_H
