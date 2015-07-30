#include "dataquerytc.h"


DataQueryTC *DataQueryTC::instance()
{
    static DataQueryTC data;
    return &data;
}

bool DataQueryTC::getTempValTC(AI_Range_TC type, float data, float *pDest)
{

}

DataQueryTC::DataQueryTC(QObject *parent) :
    QObject(parent)
{
}
