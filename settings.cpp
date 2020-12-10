#include "settings.h"

Settings::Settings()
{
    renderingMode = 0;

    tessLevelInner0 = 0;
    tessLevelInner1 = 0;

    tessLevelOuter0 = 1;
    tessLevelOuter1 = 1;
    tessLevelOuter2 = 1;
    tessLevelOuter3 = 1;

    analyticalNormals = false;
    modelLoaded = false;
    wireframeMode = true;
    approxFlatShading = false;
    uniformUpdateRequired = true;
    lastSubdivLevel = 0;

    rotAngle = 0.0;
    dispRatio = 16.0/9.0;
    FoV = 90.0;
}
