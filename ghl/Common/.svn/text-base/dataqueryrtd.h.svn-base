#ifndef DATAQUERYRTD_H
#define DATAQUERYRTD_H

#include <QObject>
#include "../GlobalData/cfgGlobalDef.h"

class DataQueryRTD : public QObject
{
    Q_OBJECT
public:
    static DataQueryRTD *instance();
    bool getTempValRTD(AI_Range_RTD type, float data, float *pDest);

private:
    explicit DataQueryRTD(QObject *parent = 0);

signals:

public slots:

};

#endif // DATAQUERYRTD_H
