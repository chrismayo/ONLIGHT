#include "englishinput.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QButtonGroup>
#include <QPushButton>
EnglishInput::EnglishInput(QWidget *parent)
    : QWidget(parent)
    , centerWidget(NULL)
    , currentWidth(0)
    , currentHeight(0)
    , textEdit(NULL)
    , lineEdit(NULL)
    , groupABC(NULL)
    , inputStr("")
    , upLatter(false)
    , latterStatus(true)
{
    setWindowsSize();
}

QString EnglishInput::getInputStr()
{
    inputStr = lineEdit->text();
    return inputStr;
}

EnglishInput::~EnglishInput()
{

}

void EnglishInput::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(28, 28, 28, 100));
}

void EnglishInput::slotGroupABCClicked(int id)
{
    if (55 == id) { // BS button
        lineEdit->backspace();
    } else if (56 == id) { // DEL button
        lineEdit->del();
    } else if (57 == id) {
        int i = lineEdit->cursorPosition();
        lineEdit->setCursorPosition(--i);
    } else if (58 == id) {
        int i = lineEdit->cursorPosition();
        lineEdit->setCursorPosition(++i);
    } else if (31 == id) {
        if (latterStatus) {
            emit sigEnglishInputOver();
        } else {
            lineEdit->insert(groupABC->button(id)->text());
        }
    } else if ((44 == id) || (53 == id)) {
        if (!upLatter) {
            groupABC->button(44)->setStyleSheet("QPushButton{background-color: "\
                                                "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(50, 255, 215, 150), "\
                                                "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                                "border-style:solid;"\
                                                "font-family:'Microsoft YaHei';font-size:30px}");
            groupABC->button(53)->setStyleSheet("QPushButton{background-color: "\
                                                "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(50, 255, 215, 150), "\
                                                "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                                "border-style:solid;"\
                                                "font-family:'Microsoft YaHei';font-size:30px}");
        } else {
            groupABC->button(44)->setStyleSheet("QPushButton{background-color: "\
                                                "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(100, 224, 230, 80), "\
                                                "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                                "border-style:solid;"\
                                                "font-family:'Microsoft YaHei';font-size:30px}");
            groupABC->button(53)->setStyleSheet("QPushButton{background-color: "\
                                                "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(100, 224, 230, 80), "\
                                                "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                                "border-style:solid;"\
                                                "font-family:'Microsoft YaHei';font-size:30px}");
        }
        upLatter = !upLatter;
        setTextShow();
    } else if (46 == id) {
        lineEdit->insert(" ");
    } else if (6 == id) {
        if (latterStatus) {
            if (upLatter)
                lineEdit->insert("&");
            else
                lineEdit->insert(groupABC->button(id)->text());
        } else {
            lineEdit->insert(groupABC->button(id)->text());
        }
    }else if(7 == id) {
        if (!latterStatus) {
            lineEdit->insert("&");
        } else {
            lineEdit->insert(groupABC->button(id)->text());
        }
    }else if (59 == id) {
        this->close();
    } else if (60 == id) {
        emit sigEnglishInputOver();
    } else if (61 == id) {
        latterStatus = !latterStatus;
        setTextShow();
    } else {
        lineEdit->insert(groupABC->button(id)->text());
    }
}

void EnglishInput::slotGroupABCPressed(int id)
{
    if ((59 == id) || (60 == id)) {
        groupABC->button(id)->setStyleSheet("QPushButton{background-color: "\
                                            "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(10, 255, 255, 255), "\
                                            "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                            "border-style:solid;"\
                                            "font-family:'Microsoft YaHei';font-size:30px}");
    } else if (61 == id) {
        groupABC->button(id)->setStyleSheet("QPushButton{background-color: "\
                                            "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(80, 255, 255, 255), "\
                                            "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                            "border-style:solid;"\
                                            "font-family:'Microsoft YaHei';font-size:30px}");
    } else {
        groupABC->button(id)->setStyleSheet("QPushButton{background-color: "\
                                            "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(50, 255, 215, 150), "\
                                            "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                            "border-style:solid;"\
                                            "font-family:'Microsoft YaHei';font-size:30px}");
    }
}

void EnglishInput::slotGroupABCReleased(int id)
{
    if ((59 == id) || (60 == id)) {
        groupABC->button(id)->setStyleSheet("QPushButton{background-color: "\
                                            "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(150, 255, 255, 255), "\
                                            "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                            "border-style:solid;"\
                                            "font-family:'Microsoft YaHei';font-size:30px}");
    } else if (61 == id) {
        groupABC->button(id)->setStyleSheet("QPushButton{background-color: "\
                                            "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(150, 255, 255, 180), "\
                                            "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                            "border-style:solid;"\
                                            "font-family:'Microsoft YaHei';font-size:30px}");
    } else if (id == 46) {
        groupABC->button(id)->setStyleSheet("QPushButton{background-color: "\
                                            "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(100, 224, 230, 150), "\
                                            "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                            "border-style:solid;"\
                                            "font-family:'Microsoft YaHei';font-size:30px}");
    } else if((id == 31) || (id == 44) || (id == 53)) {
        groupABC->button(id)->setStyleSheet("QPushButton{background-color: "\
                                            "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(100, 224, 230, 80), "\
                                            "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                            "border-style:solid;"\
                                            "font-family:'Microsoft YaHei';font-size:30px}");
    } else {
        groupABC->button(id)->setStyleSheet("QPushButton{background-color: "\
                                            "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(176, 224, 230, 50), "\
                                            "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                            "border-style:solid;"\
                                            "font-family:'Microsoft YaHei';font-size:30px}");
    }
}

void EnglishInput::setWindowsSize()
{
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    currentWidth = QApplication::desktop()->width();
    currentHeight = QApplication::desktop()->height();
    resize(currentWidth, currentHeight);
    centerWidgetLayout();
}

void EnglishInput::centerWidgetLayout()
{
    centerWidget = new QWidget(this);
    centerWidget->setGeometry(0, (int)(0.1416 * currentHeight), currentWidth, (int)(0.8584 * currentHeight));
    centerWidget->setStyleSheet("QWidget{background-color: rgb(255, 255, 255);}");

    textEdit = new QTextEdit(centerWidget);
    textEdit->setGeometry((int)(0.0508 * currentWidth), (int)(0.0326 * currentHeight), (int)(0.7331 * currentWidth), (int)(0.198 * currentHeight));
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setStyleSheet("font-family:'Microsoft YaHei';font-size:25px;");

    lineEdit = new QLineEdit(centerWidget);
    lineEdit->setGeometry((int)(0.0508 * currentWidth + 1), (int)(0.1617 * currentHeight), (int)(0.7331 * currentWidth - 2), (int)(0.0627 * currentHeight));
    lineEdit->setFocus();
    lineEdit->setFrame(false);
    lineEdit->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");


    groupABC = new QButtonGroup;

    int groupABCCount = 0;
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 11; ++j) {
            QPushButton* abcButton = new QPushButton(centerWidget);
            abcButton->setFocusPolicy(Qt::NoFocus);
            abcButton->setGeometry((int)(0.0508 * currentWidth + 0.0827 * currentWidth * j),\
                                   (int)(0.2381 * currentHeight + 0.1028 * currentHeight * i),\
                                   (int)(0.0714 * currentWidth), (int)(0.0952 * currentHeight));
            groupABC->addButton(abcButton, groupABCCount);
            ++groupABCCount;
        }
    for(int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            QPushButton* abcButton = new QPushButton(centerWidget);
            abcButton->setFocusPolicy(Qt::NoFocus);
            abcButton->setGeometry((int)(0.7951 * currentWidth + 0.0827 * currentWidth * j),\
                                   (int)(0.0326 * currentHeight + 0.1028 * currentHeight * i),\
                                   (int)(0.0714 * currentWidth), (int)(0.0952 * currentHeight));
            groupABC->addButton(abcButton, groupABCCount);
            ++groupABCCount;
        }
    QPushButton* canncelButton = new QPushButton(centerWidget);
    canncelButton->setFocusPolicy(Qt::NoFocus);
    canncelButton->setGeometry((int)(0.0508 * currentWidth), (int)(0.7769 * currentHeight),\
                               (int)(0.1165 * currentWidth), (int)(0.0652 * currentHeight));
    groupABC->addButton(canncelButton, groupABCCount);
    ++groupABCCount;

    QPushButton* OKButton = new QPushButton(centerWidget);
    OKButton->setFocusPolicy(Qt::NoFocus);
    OKButton->setGeometry((int)(0.8327 * currentWidth), (int)(0.7769 * currentHeight),\
                          (int)(0.1165 * currentWidth), (int)(0.0652 * currentHeight));
    groupABC->addButton(OKButton, groupABCCount);
    ++groupABCCount;

    QPushButton* showButton = new QPushButton(centerWidget);
    showButton->setFocusPolicy(Qt::NoFocus);
    showButton->setGeometry((int)(0.4418 * currentWidth), (int)(0.7769 * currentHeight),\
                            (int)(0.1165 * currentWidth), (int)(0.0652 * currentHeight));
    groupABC->addButton(showButton, groupABCCount);

    groupABC->button(31)->resize((int)(0.1532 * currentWidth), (int)(0.0952 * currentHeight));
    groupABC->button(32)->setHidden(true);

    groupABC->button(44)->resize((int)(0.1532 * currentWidth), (int)(0.0952 * currentHeight));
    groupABC->button(45)->setHidden(true);

    groupABC->button(46)->resize((int)(0.5677 * currentWidth), (int)(0.0952 * currentHeight));
    groupABC->button(47)->setHidden(true);
    groupABC->button(48)->setHidden(true);
    groupABC->button(49)->setHidden(true);
    groupABC->button(50)->setHidden(true);
    groupABC->button(51)->setHidden(true);
    groupABC->button(52)->setHidden(true);
    groupABC->button(53)->resize((int)(0.1532 * currentWidth), (int)(0.0952 * currentHeight));
    groupABC->button(54)->setHidden(true);

    connect(groupABC, SIGNAL(buttonClicked(int)), this, SLOT(slotGroupABCClicked(int)));
    connect(groupABC, SIGNAL(buttonPressed(int)), this, SLOT(slotGroupABCPressed(int)));
    connect(groupABC, SIGNAL(buttonReleased(int)), this, SLOT(slotGroupABCReleased(int)));
    setDefaultStyle();
    setTextShow();
}

void EnglishInput::setDefaultStyle()
{
    for (int i = 0; i < 59; ++i) {
        groupABC->button(i)->setStyleSheet("QPushButton{background-color: "\
                                           "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(176, 224, 230, 50), "\
                                           "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                           "border-style:solid;"\
                                           "font-family:'Microsoft YaHei';font-size:30px}");
    }

    groupABC->button(59)->setStyleSheet("QPushButton{background-color: "\
                                        "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(150, 255, 255, 255), "\
                                        "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                        "border-style:solid;"\
                                        "font-family:'Microsoft YaHei';font-size:30px}");

    groupABC->button(60)->setStyleSheet("QPushButton{background-color: "\
                                        "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(150, 255, 255, 255), "\
                                        "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                        "border-style:solid;"\
                                        "font-family:'Microsoft YaHei';font-size:30px}");

    groupABC->button(61)->setStyleSheet("QPushButton{background-color: "\
                                        "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(150, 255, 255, 180), "\
                                        "stop:1 rgba(255, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                        "border-style:solid;"\
                                        "font-family:'Microsoft YaHei';font-size:30px}");

    groupABC->button(31)->setStyleSheet("QPushButton{background-color: "\
                                        "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(100, 224, 230, 80), "\
                                        "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                        "border-style:solid;"\
                                        "font-family:'Microsoft YaHei';font-size:30px}");

    groupABC->button(44)->setStyleSheet("QPushButton{background-color: "\
                                        "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(100, 224, 230, 80), "\
                                        "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                        "border-style:solid;"\
                                        "font-family:'Microsoft YaHei';font-size:30px}");

    groupABC->button(46)->setStyleSheet("QPushButton{background-color: "\
                                        "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(100, 224, 230, 150), "\
                                        "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                        "border-style:solid;"\
                                        "font-family:'Microsoft YaHei';font-size:30px}");

    groupABC->button(53)->setStyleSheet("QPushButton{background-color: "\
                                        "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(100, 224, 230, 80), "\
                                        "stop:1 rgba(224, 255, 255, 255)); border-color: rgb(220, 220, 220); border-width:1px; " \
                                        "border-style:solid;"\
                                        "font-family:'Microsoft YaHei';font-size:30px}");
}

void EnglishInput::setTextShow()
{
    if (latterStatus) {
        groupABC->button(37)->setHidden(false);
        groupABC->button(38)->setHidden(false);
        groupABC->button(39)->setHidden(false);
        groupABC->button(40)->setHidden(false);
        groupABC->button(41)->setHidden(false);
        groupABC->button(42)->setHidden(false);
        groupABC->button(43)->setHidden(false);
        groupABC->button(44)->setHidden(false);
        groupABC->button(46)->setHidden(false);
        groupABC->button(53)->setHidden(false);
        groupABC->button(31)->resize((int)(0.1532 * currentWidth), (int)(0.0952 * currentHeight));
        groupABC->button(32)->setHidden(true);
        if (!upLatter) {
            groupABC->button(0)->setText("1");
            groupABC->button(1)->setText("2");
            groupABC->button(2)->setText("3");
            groupABC->button(3)->setText("4");
            groupABC->button(4)->setText("5");
            groupABC->button(5)->setText("6");
            groupABC->button(6)->setText("7");
            groupABC->button(7)->setText("8");
            groupABC->button(8)->setText("9");
            groupABC->button(9)->setText("0");
            groupABC->button(10)->setText("-");
            groupABC->button(11)->setText("q");
            groupABC->button(12)->setText("w");
            groupABC->button(13)->setText("e");
            groupABC->button(14)->setText("r");
            groupABC->button(15)->setText("t");
            groupABC->button(16)->setText("y");
            groupABC->button(17)->setText("u");
            groupABC->button(18)->setText("i");
            groupABC->button(19)->setText("o");
            groupABC->button(20)->setText("p");
            groupABC->button(21)->setText("+");
            groupABC->button(22)->setText("a");
            groupABC->button(23)->setText("s");
            groupABC->button(24)->setText("d");
            groupABC->button(25)->setText("f");
            groupABC->button(26)->setText("g");
            groupABC->button(27)->setText("h");
            groupABC->button(28)->setText("j");
            groupABC->button(29)->setText("k");
            groupABC->button(30)->setText("l");
            groupABC->button(31)->setText("Enter");
            groupABC->button(33)->setText("z");
            groupABC->button(34)->setText("x");
            groupABC->button(35)->setText("c");
            groupABC->button(36)->setText("v");
            groupABC->button(37)->setText("b");
            groupABC->button(38)->setText("n");
            groupABC->button(39)->setText("m");
            groupABC->button(40)->setText(",");
            groupABC->button(41)->setText(".");
            groupABC->button(42)->setText("/");
            groupABC->button(43)->setText("?");
            groupABC->button(44)->setText("Shift");
            groupABC->button(46)->setText("SPACE");
            groupABC->button(53)->setText("Shift");
        } else {
            groupABC->button(0)->setText("!");
            groupABC->button(1)->setText("@");
            groupABC->button(2)->setText("#");
            groupABC->button(3)->setText("$");
            groupABC->button(4)->setText("%");
            groupABC->button(5)->setText("^");
            groupABC->button(6)->setText("&&");
            groupABC->button(7)->setText("*");
            groupABC->button(8)->setText("(");
            groupABC->button(9)->setText(")");
            groupABC->button(10)->setText("-");
            groupABC->button(11)->setText("Q");
            groupABC->button(12)->setText("W");
            groupABC->button(13)->setText("E");
            groupABC->button(14)->setText("R");
            groupABC->button(15)->setText("T");
            groupABC->button(16)->setText("Y");
            groupABC->button(17)->setText("U");
            groupABC->button(18)->setText("I");
            groupABC->button(19)->setText("O");
            groupABC->button(20)->setText("P");
            groupABC->button(21)->setText("=");
            groupABC->button(22)->setText("A");
            groupABC->button(23)->setText("S");
            groupABC->button(24)->setText("D");
            groupABC->button(25)->setText("F");
            groupABC->button(26)->setText("G");
            groupABC->button(27)->setText("H");
            groupABC->button(28)->setText("J");
            groupABC->button(29)->setText("K");
            groupABC->button(30)->setText("L");
            groupABC->button(31)->setText("Enter");
            groupABC->button(33)->setText("Z");
            groupABC->button(34)->setText("X");
            groupABC->button(35)->setText("C");
            groupABC->button(36)->setText("V");
            groupABC->button(37)->setText("B");
            groupABC->button(38)->setText("N");
            groupABC->button(39)->setText("M");
            groupABC->button(40)->setText(",");
            groupABC->button(41)->setText(".");
            groupABC->button(42)->setText("/");
            groupABC->button(43)->setText(":");
            groupABC->button(44)->setText("Shift");
            groupABC->button(46)->setText("SPACE");
            groupABC->button(53)->setText("Shift");
        }
        groupABC->button(61)->setText(tr("Symbol"));
    } else {
        groupABC->button(0)->setText("~");
        groupABC->button(1)->setText("!");
        groupABC->button(2)->setText("@");
        groupABC->button(3)->setText("#");
        groupABC->button(4)->setText("$");
        groupABC->button(5)->setText("%");
        groupABC->button(6)->setText("^");
        groupABC->button(7)->setText("&&");
        groupABC->button(8)->setText("*");
        groupABC->button(9)->setText("(");
        groupABC->button(10)->setText(")");
        groupABC->button(11)->setText("\"");
        groupABC->button(12)->setText("\'");
        groupABC->button(13)->setText(".");
        groupABC->button(14)->setText(":");
        groupABC->button(15)->setText("?");
        groupABC->button(16)->setText("—");
        groupABC->button(17)->setText("=");
        groupABC->button(18)->setText("+");
        groupABC->button(19)->setText("-");
        groupABC->button(20)->setText("/");
        groupABC->button(21)->setText("\\");
        groupABC->button(22)->setText("|");
        groupABC->button(23)->setText("<");
        groupABC->button(24)->setText(">");
        groupABC->button(25)->setText("{");
        groupABC->button(26)->setText("}");
        groupABC->button(27)->setText("[");
        groupABC->button(28)->setText("]");
        groupABC->button(29)->setText("·");
        groupABC->button(30)->setText("。");
        groupABC->button(31)->resize((int)(0.0714 * currentWidth), (int)(0.0952 * currentHeight));
        groupABC->button(32)->setHidden(false);
        groupABC->button(31)->setText("×");
        groupABC->button(32)->setText("÷");
        groupABC->button(33)->setText("￥");
        groupABC->button(34)->setText("±");
        groupABC->button(35)->setText("μ");
        groupABC->button(36)->setText("℃");
        groupABC->button(61)->setText(tr("English"));
        groupABC->button(37)->setHidden(true);
        groupABC->button(38)->setHidden(true);
        groupABC->button(39)->setHidden(true);
        groupABC->button(40)->setHidden(true);
        groupABC->button(41)->setHidden(true);
        groupABC->button(42)->setHidden(true);
        groupABC->button(43)->setHidden(true);
        groupABC->button(44)->setHidden(true);
        groupABC->button(46)->setHidden(true);
        groupABC->button(53)->setHidden(true);
    }
    groupABC->button(59)->setText(tr("Cancel"));
    groupABC->button(60)->setText(tr("OK"));
    groupABC->button(55)->setText("BS");
    groupABC->button(56)->setText("DEL");
    groupABC->button(57)->setText("←");
    groupABC->button(58)->setText("→");

}
