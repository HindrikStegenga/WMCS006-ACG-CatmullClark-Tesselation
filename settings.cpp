#include "settings.h"

Settings::Settings()
{
    limitVertices = false;
    modelLoaded = false;
    wireframeMode = true;
    limitFilledTriangles = false;
    uniformUpdateRequired = true;
    lastSubdivLevel = 0;

    rotAngle = 0.0;
    dispRatio = 16.0/9.0;
    FoV = 90.0;
}
