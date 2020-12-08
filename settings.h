#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMatrix4x4>

class Settings
{
public:
    Settings();

    bool modelLoaded;
    bool wireframeMode;
    bool limitVertices;
    int lastSubdivLevel;

    float FoV;
    float dispRatio;
    float rotAngle;

    bool uniformUpdateRequired;

    QMatrix4x4 modelViewMatrix, projectionMatrix;
    QMatrix3x3 normalMatrix;
};

#endif // SETTINGS_H
