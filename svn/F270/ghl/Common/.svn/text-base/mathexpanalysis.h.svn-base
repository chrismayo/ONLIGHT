#ifndef MATHEXPANALYSIS_H
#define MATHEXPANALYSIS_H

#include <QList>

typedef enum Tlog_type_enum {
    Tlog_type_none = 0,
    Tlog_type_sum,
    Tlog_type_max,
    Tlog_type_min,
    Tlog_type_ave,
    Tlog_type_p2p,
}Tlog_type;

class MathExpAnalysis
{
public:
    MathExpAnalysis();
    qreal getMathExpValue();

public:
    static QList<MathExpAnalysis *> m_mathExplist; //有效运算式链表

    quint32         m_index;                    //运算式索引值

    Tlog_type      m_tlog_type;             //运算式中是否包含TLOG运算以及其类型
    quint32         m_tlog_channel;       //运算式中关联的TLOG运算对象的通道编码

    quint32        m_tlog_count;          //TLOG运算计数
    qreal             m_tlog_sum;            //运算式中关联的TLOG运算值SUM
    qreal             m_tlog_max;            //运算式中关联的TLOG运算值Max
    qreal             m_tlog_min;            //运算式中关联的TLOG运算值Min
    qreal             m_tlog_ave;            //运算式中关联的TLOG运算值Ave
    qreal             m_tlog_p2p;            //运算式中关联的TLOG运算值P2P

    qreal             m_tlog_value;         //运算式关联TLOG运算类型的最终结果值，与MATH配置相关
};

#endif // MATHEXPANALYSIS_H
