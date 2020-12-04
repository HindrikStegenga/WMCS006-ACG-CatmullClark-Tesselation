#include "settings.h"

Settings::Settings()
{
    modelLoaded = false;
    wireframeMode = true;
    uniformUpdateRequired = true;

    rotAngle = 0.0;
    dispRatio = 16.0/9.0;
    FoV = 120.0;
}
