
#include "geoEngine.h"

geoEngine* geoEngine::Instance()
{
    static geoEngine instance;
	return &instance;
}

geoEngine::geoEngine()
{
}

void geoEngine::slotProcessAndLabel(const int& dValue,const QString& sValue)
{
    emit sigProcessAndLabel(dValue,sValue);
}
