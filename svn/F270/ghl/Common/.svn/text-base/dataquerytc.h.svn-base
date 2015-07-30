#ifndef DATAQUERYTC_H
#define DATAQUERYTC_H

#include <QObject>
#include "../GlobalData/cfgGlobalDef.h"

class DataQueryTC : public QObject
{
    Q_OBJECT
public:
    static DataQueryTC *instance();
    bool getTempValTC(AI_Range_TC type, float data, float *pDest);

private:
    explicit DataQueryTC(QObject *parent = 0);

signals:

public slots:

};

#endif // DATAQUERYTC_H
