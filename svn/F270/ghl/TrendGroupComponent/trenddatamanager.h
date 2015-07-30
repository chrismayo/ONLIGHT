#ifndef TRENDDATAMANAGER_H
#define TRENDDATAMANAGER_H

#include <QObject>
#include <QVector>
#define TREND_BUF_LEN 3000

class TrendDataManager : public QObject
{
    Q_OBJECT
public:
    explicit TrendDataManager(QObject *parent = 0);
    ~TrendDataManager();

signals:

public slots:

private:
    void initialize();
    void release();
    void sigAndSlotConnect();

private:
    QString m_detailStartTime, m_detailEndTime, m_rulerIndicateTime;
    int m_overViewCurrentStartPos, m_overViewCurrentEndPos, m_rulerPos;
    int m_overViewLenth, m_currentRectWidth;
    //下方为绘制相关
    QString m_paper1StartTime, m_paper1EndTime,
                  m_paper2StartTime, m_paper2EndTime,
                  m_paper3StartTime, m_paper3EndTime;
    int m_paperStartPos, m_paperEndPos;
    int m_timeSlice, m_trendPointSlice;


};

#endif // TRENDDATAMANAGER_H
