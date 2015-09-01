#ifndef SELECTCOLOR_H
#define SELECTCOLOR_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QList>
class QPushButton;
class QButtonGroup;
class QLabel;
class QDockWidget;
class QSlider;
class SelectColor : public QWidget
{
    Q_OBJECT

public:
    SelectColor(QWidget *parent = 0);
    ~SelectColor();

signals:
    void sigColorSelect();
protected:
    /*
     * 重写paintEvent事件.
     */
    void paintEvent(QPaintEvent *);


private slots:
    void slotOpenWindow();
    void slotCloseWindow();
    void slotlabelCustom();
    void slotlabelCurrentColorShow();
    void slotCancelClicked();
    void slotOkClicked();

    void slotsliderRedChange(int num);
    void slotsliderGreenChange(int num);
    void slotsliderBlueChange(int num);
    void slotGroupClicked(int id);
    void slotGroupNumPressed(int id);
    void slotGroupNumReleased(int id);
    void slotGroupNumClicked(int id);
    void slotGroupRGBClicked(int id);
    void slotCancelPressed();
    void slotCacelReleased();
    void slotOKPressed();
    void slotOKReleased();

private:
    enum {
        Red = 0,
        ThinGreen,
        Ironcyanosis,
        BalladDrama,
        Brown,
        Citrus,
        ThinHongmei,
        MeiDye,
        Green,
        DewGrass,
        Yellow,
        BlackIron,
        PeonyColor,
        BustardColor,
        Ivory,
        RattanColor,
        Olivine,
        WeakGreen,
        SkyBlue,
        Milky,
        Purper,
        MengCong,
        ThinckGreen,
        LightBlue,
        RecentColorOne,
        RecentColorTwo,
        RecentColorThree,
        RecentColorFour,
        RecentColorFive,
        RecentColorSix
    };

    enum {
        NumZero = 0,
        NumOne,
        NumTwo,
        NumThree,
        NumFour,
        NumFive,
        NumSix
    };

    enum {
        FoucusR = 0,
        FoucusG,
        FoucusB
    };

    void setSizeOfWindows();       // 根据当前屏幕的分辨率设置窗体的大小
    void initialization();          // 控件初始化
    void defaultStatus();
    void setRGBColor();
    void connectFunC();
    void connectDatabase();
    void addGroupSimple();
    void addGroupDetail();
    void recentUseColorShow();
    void addGroupNum();
    void setNumDefaultStyle();



private:
    int colorWindosWidth;
    int colorWindosHeigh;
    QWidget*  simpleColorSelect;
    QWidget*  detailColorSelect;

    QPushButton* labelRedS;         // #d71345
    QPushButton* labelThinGreenS;   // #1d953f
    QPushButton* labelIroncyanosisS;// #181d4b
    QPushButton* labelBalladDramaS; // #2a5caa
    QPushButton* labelBrownS;       // #843900
    QPushButton* labelCitrusS;      // #f58220
    QPushButton* labelThinHongmeiS; // #f391a9
    QPushButton* labelMeiDyeS;      // #987165
    QPushButton* labelGreenS;       // #45b97c
    QPushButton* labelDewGrassS;    // #33a3dc
    QPushButton* labelYellowS;      // #ffd400
    QPushButton* labelBlackIronS;   // #281f1d
    QPushButton* labelPeonyColorS; // #ea66a6
    QPushButton* labelBustardColorS;// #f7acbc
    QPushButton* labelIvoryS;       // #f2eada
    QPushButton* labelRattanColorS; // #afb4db
    QPushButton* labelOlivineS;     // #b2d235
    QPushButton* labelWeakGreenS;   // #7fb80e
    QPushButton* labelSkyBlueS;     // #90d7ec
    QPushButton* labelMilkyS;       // #d3d7d4
    QPushButton* labelPurperS;      // #8552a1
    QPushButton* labelMengCongS;    // #006c54
    QPushButton* labelThinckGreenS; // #005831
    QPushButton* labelLightBlueS;    // #00FF00

    QPushButton* labelRedD;         // #d71345
    QPushButton* labelThinGreenD;   // #1d953f
    QPushButton* labelIroncyanosisD;// #181d4b
    QPushButton* labelBalladDramaD; // #2a5caa
    QPushButton* labelBrownD;       // #843900
    QPushButton* labelCitrusD;      // #f58220
    QPushButton* labelThinHongmeiD; // #f391a9
    QPushButton* labelMeiDyeD;      // #987165
    QPushButton* labelGreenD;       // #45b97c
    QPushButton* labelDewGrassD;    // #33a3dc
    QPushButton* labelYellowD;      // #ffd400
    QPushButton* labelBlackIronD;   // #281f1d
    QPushButton* labelPeonyColorD; // #ea66a6
    QPushButton* labelBustardColorD;// #f7acbc
    QPushButton* labelIvoryD;       // #f2eada
    QPushButton* labelRattanColorD; // #afb4db
    QPushButton* labelOlivineD;     // #b2d235
    QPushButton* labelWeakGreenD;   // #7fb80e
    QPushButton* labelSkyBlueD;     // #90d7ec
    QPushButton* labelMilkyD;       // #d3d7d4
    QPushButton* labelPurperD;      // #8552a1
    QPushButton* labelMengCongD;    // #006c54
    QPushButton* labelThinckGreenD; // #005831
    QPushButton* labelLightBlueD;    // #00FF00

    QPushButton* recentUseColor1;
    QPushButton* recentUseColor2;
    QPushButton* recentUseColor3;
    QPushButton* recentUseColor4;
    QPushButton* recentUseColor5;
    QPushButton* recentUseColor6;
    QPushButton* buttonCancelD;
    QPushButton* buttonCancelS;
    QPushButton* buttonOKD;
    QPushButton* buttonOKS;
    QPushButton* labelCurrentColorShow;

    QPushButton* buttonNumOne;
    QPushButton* buttonNumTwo;
    QPushButton* buttonNumThree;
    QPushButton* buttonNumFour;
    QPushButton* buttonNumFive;
    QPushButton* buttonNumSix;
    QPushButton* buttonNumSeven;
    QPushButton* buttonNumEight;
    QPushButton* buttonNumNine;
    QPushButton* buttonNumZero;
    QPushButton* buttonClear;

    QButtonGroup* groupSimple;
    QButtonGroup* groupDetail;
    QButtonGroup* groupNum;
    QButtonGroup* groupRGBShow;

    QLabel* labelTextS;
    QLabel* labelTextD;
    QLabel* labelRecentUser;
    QLabel* labelCurrentColor;
    QPushButton* labelCustomS;
    QPushButton* labelCustomD;
    QPushButton* labelRColor;
    QPushButton* labelGColor;
    QPushButton* labelBColor;
    QPushButton* buttonOpenDetailS;
    QPushButton* buttonOpenDetailD;

    QSlider* sliderRed;
    QSlider* sliderGreen;
    QSlider* sliderBlue;
    QList<int> listRed;
    QList<int> listGreen;
    QList<int> listBlue;
    QSqlDatabase db;    // 定义数据库
    QSqlQuery query;    // 数据库执行
    QString numValue;
    int numR;
    int numG;
    int numB;
    int currentNum;
    int currenRGBChoice;
};

#endif // SELECTCOLOR_H
