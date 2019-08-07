
//by duans 2018.6.19
#ifndef _DPX_GEO_ENGINE_H__
#define _DPX_GEO_ENGINE_H__
#pragma once

#include <QObject>
#include "geoengine_global.h"
using namespace  std;
/*
* dpxMap
*/

class  geoEngine : public QObject
{
	Q_OBJECT
public:
    static geoEngine* Instance();

public:

public slots:
    void slotProcessAndLabel(const int& dValue,const QString& sValue);

signals:
    void sigProcessAndLabel(const int& dValue,const QString& sValue);

//私有构造
private:
    geoEngine();
    geoEngine(const geoEngine&){}
    geoEngine& operator=(const geoEngine&){}
private:
};

#endif
