/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiontestPolozka;
    QAction *actionstahnoutXML;
    QAction *action;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QPushButton *tlacitkoSeznamSluzeb;
    QPushButton *tlacitkoHlavni;
    QPushButton *tlacitkoCasovac;
    QPushButton *tlacitkoLed;
    QPushButton *svgTlacitko;
    QPushButton *quitTlacitko;
    QPushButton *refreshTlac;
    QStackedWidget *prepinadloStran;
    QWidget *page_hlavniObrazovka;
    QGridLayout *gridLayout_4;
    QStackedWidget *stackedWidget_obrazovka;
    QWidget *page_hlavni;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *Llinka;
    QLabel *Lcil;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QStackedWidget *stackedWidget_prostredek;
    QWidget *page_hlavni_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *sipka;
    QVBoxLayout *verticalLayout_2;
    QLabel *Lnacestna4;
    QLabel *Lnacestna3;
    QLabel *Lnacestna2;
    QWidget *page_oznameni;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_oznType;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_oznTitle;
    QLabel *label_oznTextCs;
    QLabel *label_oznTextEn;
    QWidget *page_zmenaPasma;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_18;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_pasmo1;
    QLabel *label_21;
    QLabel *label_pasmo2;
    QWidget *page_konecna;
    QWidget *widget;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_20;
    QLabel *label_22;
    QLabel *Lnacestna1;
    QLabel *label_zmena;
    QLabel *label_announcement;
    QWidget *page_verze;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *page_zmenaLinky;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_13;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_16;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_currentStopIndex;
    QLabel *label_locationState;
    QWidget *page_seznamSluzeb;
    QTableWidget *tabulkaSubscriberu;
    QWidget *page_casovac;
    QLabel *label;
    QLabel *labelZbyvajiciVteriny;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QPushButton *tlacitkoNastavVteriny;
    QWidget *page_svg;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_6;
    QGraphicsView *graphicsView;
    QWidget *page_led;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *bocniTabloWrapper;
    QLabel *bocniTabloNazev;
    QHBoxLayout *jenBocniTablo;
    QLabel *labelSideLine;
    QVBoxLayout *pravplka;
    QLabel *labelSideTopRow;
    QLabel *labelSideBottomRow;
    QSpacerItem *horizontalSpacer;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *vnitrniTabloWraper;
    QLabel *predniLabel_3;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelInnerLine;
    QLabel *labelInnerTopRow;
    QLabel *labelInnerBottomRow;
    QWidget *verticalLayoutWidget_9;
    QVBoxLayout *zadniTabloWrapper;
    QLabel *predniLabel_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelRearLine;
    QLabel *predniLabel;
    QFrame *frame;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelFrontLine;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *layoutDvaRadky;
    QLabel *labelFrontTopRow;
    QLabel *labelFrontBottomRow;
    QLabel *labelFrontSingle;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QMenuBar *menuBar;
    QMenu *menunacti;
    QMenu *menukonec;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(834, 484);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(834, 484));
        actiontestPolozka = new QAction(MainWindow);
        actiontestPolozka->setObjectName(QString::fromUtf8("actiontestPolozka"));
        actionstahnoutXML = new QAction(MainWindow);
        actionstahnoutXML->setObjectName(QString::fromUtf8("actionstahnoutXML"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tlacitkoSeznamSluzeb = new QPushButton(centralWidget);
        tlacitkoSeznamSluzeb->setObjectName(QString::fromUtf8("tlacitkoSeznamSluzeb"));
        QFont font;
        font.setPointSize(20);
        tlacitkoSeznamSluzeb->setFont(font);
        tlacitkoSeznamSluzeb->setCheckable(true);
        tlacitkoSeznamSluzeb->setAutoExclusive(true);

        verticalLayout_4->addWidget(tlacitkoSeznamSluzeb);

        tlacitkoHlavni = new QPushButton(centralWidget);
        tlacitkoHlavni->setObjectName(QString::fromUtf8("tlacitkoHlavni"));
        tlacitkoHlavni->setFont(font);
        tlacitkoHlavni->setCheckable(true);
        tlacitkoHlavni->setChecked(true);
        tlacitkoHlavni->setAutoExclusive(true);

        verticalLayout_4->addWidget(tlacitkoHlavni);

        tlacitkoCasovac = new QPushButton(centralWidget);
        tlacitkoCasovac->setObjectName(QString::fromUtf8("tlacitkoCasovac"));
        tlacitkoCasovac->setFont(font);
        tlacitkoCasovac->setCheckable(true);
        tlacitkoCasovac->setAutoExclusive(true);

        verticalLayout_4->addWidget(tlacitkoCasovac);

        tlacitkoLed = new QPushButton(centralWidget);
        tlacitkoLed->setObjectName(QString::fromUtf8("tlacitkoLed"));
        tlacitkoLed->setFont(font);

        verticalLayout_4->addWidget(tlacitkoLed);

        svgTlacitko = new QPushButton(centralWidget);
        svgTlacitko->setObjectName(QString::fromUtf8("svgTlacitko"));
        svgTlacitko->setFont(font);

        verticalLayout_4->addWidget(svgTlacitko);

        quitTlacitko = new QPushButton(centralWidget);
        quitTlacitko->setObjectName(QString::fromUtf8("quitTlacitko"));
        quitTlacitko->setFont(font);
        quitTlacitko->setCheckable(true);
        quitTlacitko->setAutoExclusive(true);

        verticalLayout_4->addWidget(quitTlacitko);

        refreshTlac = new QPushButton(centralWidget);
        refreshTlac->setObjectName(QString::fromUtf8("refreshTlac"));
        refreshTlac->setFont(font);

        verticalLayout_4->addWidget(refreshTlac);


        horizontalLayout_5->addLayout(verticalLayout_4);

        prepinadloStran = new QStackedWidget(centralWidget);
        prepinadloStran->setObjectName(QString::fromUtf8("prepinadloStran"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(prepinadloStran->sizePolicy().hasHeightForWidth());
        prepinadloStran->setSizePolicy(sizePolicy1);
        page_hlavniObrazovka = new QWidget();
        page_hlavniObrazovka->setObjectName(QString::fromUtf8("page_hlavniObrazovka"));
        gridLayout_4 = new QGridLayout(page_hlavniObrazovka);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        stackedWidget_obrazovka = new QStackedWidget(page_hlavniObrazovka);
        stackedWidget_obrazovka->setObjectName(QString::fromUtf8("stackedWidget_obrazovka"));
        sizePolicy1.setHeightForWidth(stackedWidget_obrazovka->sizePolicy().hasHeightForWidth());
        stackedWidget_obrazovka->setSizePolicy(sizePolicy1);
        page_hlavni = new QWidget();
        page_hlavni->setObjectName(QString::fromUtf8("page_hlavni"));
        sizePolicy.setHeightForWidth(page_hlavni->sizePolicy().hasHeightForWidth());
        page_hlavni->setSizePolicy(sizePolicy);
        verticalLayoutWidget = new QWidget(page_hlavni);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 621, 273));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Llinka = new QLabel(verticalLayoutWidget);
        Llinka->setObjectName(QString::fromUtf8("Llinka"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Llinka->sizePolicy().hasHeightForWidth());
        Llinka->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(30);
        Llinka->setFont(font1);
        Llinka->setAutoFillBackground(false);

        horizontalLayout->addWidget(Llinka);

        Lcil = new QLabel(verticalLayoutWidget);
        Lcil->setObjectName(QString::fromUtf8("Lcil"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Lcil->sizePolicy().hasHeightForWidth());
        Lcil->setSizePolicy(sizePolicy3);
        Lcil->setFont(font1);
        Lcil->setAutoFillBackground(false);

        horizontalLayout->addWidget(Lcil);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy4);

        horizontalLayout_2->addWidget(label_6);


        verticalLayout_3->addLayout(horizontalLayout_2);

        stackedWidget_prostredek = new QStackedWidget(verticalLayoutWidget);
        stackedWidget_prostredek->setObjectName(QString::fromUtf8("stackedWidget_prostredek"));
        page_hlavni_2 = new QWidget();
        page_hlavni_2->setObjectName(QString::fromUtf8("page_hlavni_2"));
        gridLayout_2 = new QGridLayout(page_hlavni_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sipka = new QLabel(page_hlavni_2);
        sipka->setObjectName(QString::fromUtf8("sipka"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(sipka->sizePolicy().hasHeightForWidth());
        sipka->setSizePolicy(sizePolicy5);
        sipka->setMaximumSize(QSize(50, 16777215));
        QFont font2;
        font2.setPointSize(70);
        sipka->setFont(font2);
        sipka->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(sipka);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Lnacestna4 = new QLabel(page_hlavni_2);
        Lnacestna4->setObjectName(QString::fromUtf8("Lnacestna4"));
        sizePolicy.setHeightForWidth(Lnacestna4->sizePolicy().hasHeightForWidth());
        Lnacestna4->setSizePolicy(sizePolicy);
        Lnacestna4->setFont(font);

        verticalLayout_2->addWidget(Lnacestna4);

        Lnacestna3 = new QLabel(page_hlavni_2);
        Lnacestna3->setObjectName(QString::fromUtf8("Lnacestna3"));
        sizePolicy.setHeightForWidth(Lnacestna3->sizePolicy().hasHeightForWidth());
        Lnacestna3->setSizePolicy(sizePolicy);
        Lnacestna3->setFont(font);

        verticalLayout_2->addWidget(Lnacestna3);

        Lnacestna2 = new QLabel(page_hlavni_2);
        Lnacestna2->setObjectName(QString::fromUtf8("Lnacestna2"));
        sizePolicy.setHeightForWidth(Lnacestna2->sizePolicy().hasHeightForWidth());
        Lnacestna2->setSizePolicy(sizePolicy);
        Lnacestna2->setFont(font);

        verticalLayout_2->addWidget(Lnacestna2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        stackedWidget_prostredek->addWidget(page_hlavni_2);
        page_oznameni = new QWidget();
        page_oznameni->setObjectName(QString::fromUtf8("page_oznameni"));
        horizontalLayoutWidget_5 = new QWidget(page_oznameni);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(110, 20, 311, 80));
        horizontalLayout_17 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
        label_oznType = new QLabel(horizontalLayoutWidget_5);
        label_oznType->setObjectName(QString::fromUtf8("label_oznType"));

        horizontalLayout_17->addWidget(label_oznType);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        label_oznTitle = new QLabel(horizontalLayoutWidget_5);
        label_oznTitle->setObjectName(QString::fromUtf8("label_oznTitle"));

        verticalLayout_11->addWidget(label_oznTitle);

        label_oznTextCs = new QLabel(horizontalLayoutWidget_5);
        label_oznTextCs->setObjectName(QString::fromUtf8("label_oznTextCs"));

        verticalLayout_11->addWidget(label_oznTextCs);

        label_oznTextEn = new QLabel(horizontalLayoutWidget_5);
        label_oznTextEn->setObjectName(QString::fromUtf8("label_oznTextEn"));

        verticalLayout_11->addWidget(label_oznTextEn);


        horizontalLayout_17->addLayout(verticalLayout_11);

        stackedWidget_prostredek->addWidget(page_oznameni);
        page_zmenaPasma = new QWidget();
        page_zmenaPasma->setObjectName(QString::fromUtf8("page_zmenaPasma"));
        gridLayout_3 = new QGridLayout(page_zmenaPasma);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_18 = new QLabel(page_zmenaPasma);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy6);
        label_18->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_18);

        label_19 = new QLabel(page_zmenaPasma);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_19);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_pasmo1 = new QLabel(page_zmenaPasma);
        label_pasmo1->setObjectName(QString::fromUtf8("label_pasmo1"));
        label_pasmo1->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(label_pasmo1);

        label_21 = new QLabel(page_zmenaPasma);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(label_21);

        label_pasmo2 = new QLabel(page_zmenaPasma);
        label_pasmo2->setObjectName(QString::fromUtf8("label_pasmo2"));
        label_pasmo2->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(label_pasmo2);


        verticalLayout_10->addLayout(horizontalLayout_16);


        gridLayout_3->addLayout(verticalLayout_10, 0, 0, 1, 1);

        stackedWidget_prostredek->addWidget(page_zmenaPasma);
        page_konecna = new QWidget();
        page_konecna->setObjectName(QString::fromUtf8("page_konecna"));
        widget = new QWidget(page_konecna);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(210, 30, 187, 91));
        verticalLayout_12 = new QVBoxLayout(widget);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(widget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_20);

        label_22 = new QLabel(widget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_22);

        stackedWidget_prostredek->addWidget(page_konecna);

        verticalLayout_3->addWidget(stackedWidget_prostredek);

        Lnacestna1 = new QLabel(verticalLayoutWidget);
        Lnacestna1->setObjectName(QString::fromUtf8("Lnacestna1"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(Lnacestna1->sizePolicy().hasHeightForWidth());
        Lnacestna1->setSizePolicy(sizePolicy7);
        Lnacestna1->setFont(font1);
        Lnacestna1->setScaledContents(false);

        verticalLayout_3->addWidget(Lnacestna1);

        label_zmena = new QLabel(verticalLayoutWidget);
        label_zmena->setObjectName(QString::fromUtf8("label_zmena"));

        verticalLayout_3->addWidget(label_zmena);

        label_announcement = new QLabel(verticalLayoutWidget);
        label_announcement->setObjectName(QString::fromUtf8("label_announcement"));

        verticalLayout_3->addWidget(label_announcement);

        stackedWidget_obrazovka->addWidget(page_hlavni);
        page_verze = new QWidget();
        page_verze->setObjectName(QString::fromUtf8("page_verze"));
        verticalLayoutWidget_2 = new QWidget(page_verze);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(220, 120, 160, 80));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_8->addWidget(label_5);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_9->addWidget(label_7);

        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_9->addWidget(label_8);


        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_11 = new QLabel(verticalLayoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_14->addWidget(label_11);

        label_12 = new QLabel(verticalLayoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);


        verticalLayout_8->addLayout(horizontalLayout_14);

        stackedWidget_obrazovka->addWidget(page_verze);
        page_zmenaLinky = new QWidget();
        page_zmenaLinky->setObjectName(QString::fromUtf8("page_zmenaLinky"));
        verticalLayoutWidget_5 = new QWidget(page_zmenaLinky);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(110, 60, 391, 221));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(verticalLayoutWidget_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy6.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy6);
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_13);

        label_14 = new QLabel(verticalLayoutWidget_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_15 = new QLabel(verticalLayoutWidget_5);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        horizontalLayout_15->addWidget(label_15);

        label_17 = new QLabel(verticalLayoutWidget_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        horizontalLayout_15->addWidget(label_17);

        label_16 = new QLabel(verticalLayoutWidget_5);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        horizontalLayout_15->addWidget(label_16);


        verticalLayout_9->addLayout(horizontalLayout_15);

        stackedWidget_obrazovka->addWidget(page_zmenaLinky);

        gridLayout_4->addWidget(stackedWidget_obrazovka, 0, 0, 1, 2);

        label_4 = new QLabel(page_hlavniObrazovka);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 1, 1, 1);

        label_2 = new QLabel(page_hlavniObrazovka);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1);

        label_currentStopIndex = new QLabel(page_hlavniObrazovka);
        label_currentStopIndex->setObjectName(QString::fromUtf8("label_currentStopIndex"));

        gridLayout_4->addWidget(label_currentStopIndex, 2, 0, 1, 1);

        label_locationState = new QLabel(page_hlavniObrazovka);
        label_locationState->setObjectName(QString::fromUtf8("label_locationState"));

        gridLayout_4->addWidget(label_locationState, 2, 1, 1, 1);

        prepinadloStran->addWidget(page_hlavniObrazovka);
        page_seznamSluzeb = new QWidget();
        page_seznamSluzeb->setObjectName(QString::fromUtf8("page_seznamSluzeb"));
        tabulkaSubscriberu = new QTableWidget(page_seznamSluzeb);
        if (tabulkaSubscriberu->columnCount() < 4)
            tabulkaSubscriberu->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabulkaSubscriberu->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabulkaSubscriberu->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tabulkaSubscriberu->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tabulkaSubscriberu->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tabulkaSubscriberu->setObjectName(QString::fromUtf8("tabulkaSubscriberu"));
        tabulkaSubscriberu->setGeometry(QRect(20, 10, 671, 331));
        prepinadloStran->addWidget(page_seznamSluzeb);
        page_casovac = new QWidget();
        page_casovac->setObjectName(QString::fromUtf8("page_casovac"));
        label = new QLabel(page_casovac);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(420, 80, 151, 41));
        labelZbyvajiciVteriny = new QLabel(page_casovac);
        labelZbyvajiciVteriny->setObjectName(QString::fromUtf8("labelZbyvajiciVteriny"));
        labelZbyvajiciVteriny->setGeometry(QRect(420, 140, 231, 121));
        QFont font3;
        font3.setPointSize(60);
        labelZbyvajiciVteriny->setFont(font3);
        verticalLayoutWidget_3 = new QWidget(page_casovac);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(60, 110, 160, 84));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_5->addWidget(label_3);

        lineEdit = new QLineEdit(verticalLayoutWidget_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_5->addWidget(lineEdit);

        tlacitkoNastavVteriny = new QPushButton(verticalLayoutWidget_3);
        tlacitkoNastavVteriny->setObjectName(QString::fromUtf8("tlacitkoNastavVteriny"));

        verticalLayout_5->addWidget(tlacitkoNastavVteriny);

        prepinadloStran->addWidget(page_casovac);
        page_svg = new QWidget();
        page_svg->setObjectName(QString::fromUtf8("page_svg"));
        gridLayout = new QGridLayout(page_svg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        graphicsView = new QGraphicsView(page_svg);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(graphicsView);


        gridLayout->addLayout(verticalLayout_6, 0, 0, 1, 1);

        prepinadloStran->addWidget(page_svg);
        page_led = new QWidget();
        page_led->setObjectName(QString::fromUtf8("page_led"));
        verticalLayoutWidget_4 = new QWidget(page_led);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(9, 146, 521, 141));
        bocniTabloWrapper = new QVBoxLayout(verticalLayoutWidget_4);
        bocniTabloWrapper->setSpacing(0);
        bocniTabloWrapper->setContentsMargins(11, 11, 11, 11);
        bocniTabloWrapper->setObjectName(QString::fromUtf8("bocniTabloWrapper"));
        bocniTabloWrapper->setSizeConstraint(QLayout::SetDefaultConstraint);
        bocniTabloWrapper->setContentsMargins(0, 0, 0, 0);
        bocniTabloNazev = new QLabel(verticalLayoutWidget_4);
        bocniTabloNazev->setObjectName(QString::fromUtf8("bocniTabloNazev"));
        QSizePolicy sizePolicy8(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(bocniTabloNazev->sizePolicy().hasHeightForWidth());
        bocniTabloNazev->setSizePolicy(sizePolicy8);

        bocniTabloWrapper->addWidget(bocniTabloNazev);

        jenBocniTablo = new QHBoxLayout();
        jenBocniTablo->setSpacing(0);
        jenBocniTablo->setObjectName(QString::fromUtf8("jenBocniTablo"));
        labelSideLine = new QLabel(verticalLayoutWidget_4);
        labelSideLine->setObjectName(QString::fromUtf8("labelSideLine"));
        sizePolicy4.setHeightForWidth(labelSideLine->sizePolicy().hasHeightForWidth());
        labelSideLine->setSizePolicy(sizePolicy4);
        labelSideLine->setMinimumSize(QSize(115, 78));
        labelSideLine->setMaximumSize(QSize(115, 78));
        labelSideLine->setBaseSize(QSize(115, 78));
        QFont font4;
        font4.setFamily(QString::fromUtf8("21-PID 8"));
        font4.setPointSize(65);
        labelSideLine->setFont(font4);
        labelSideLine->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelSideLine->setScaledContents(false);
        labelSideLine->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        jenBocniTablo->addWidget(labelSideLine);

        pravplka = new QVBoxLayout();
        pravplka->setSpacing(0);
        pravplka->setObjectName(QString::fromUtf8("pravplka"));
        pravplka->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelSideTopRow = new QLabel(verticalLayoutWidget_4);
        labelSideTopRow->setObjectName(QString::fromUtf8("labelSideTopRow"));
        QSizePolicy sizePolicy9(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(labelSideTopRow->sizePolicy().hasHeightForWidth());
        labelSideTopRow->setSizePolicy(sizePolicy9);
        labelSideTopRow->setMinimumSize(QSize(344, 0));
        labelSideTopRow->setMaximumSize(QSize(344, 37));
        labelSideTopRow->setBaseSize(QSize(344, 0));
        QFont font5;
        font5.setFamily(QString::fromUtf8("21-PID 1"));
        font5.setPointSize(65);
        labelSideTopRow->setFont(font5);
        labelSideTopRow->setAutoFillBackground(false);
        labelSideTopRow->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelSideTopRow->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        pravplka->addWidget(labelSideTopRow);

        labelSideBottomRow = new QLabel(verticalLayoutWidget_4);
        labelSideBottomRow->setObjectName(QString::fromUtf8("labelSideBottomRow"));
        sizePolicy9.setHeightForWidth(labelSideBottomRow->sizePolicy().hasHeightForWidth());
        labelSideBottomRow->setSizePolicy(sizePolicy9);
        labelSideBottomRow->setMinimumSize(QSize(344, 0));
        labelSideBottomRow->setMaximumSize(QSize(344, 41));
        labelSideBottomRow->setBaseSize(QSize(344, 0));
        labelSideBottomRow->setFont(font5);
        labelSideBottomRow->setAutoFillBackground(false);
        labelSideBottomRow->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelSideBottomRow->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        pravplka->addWidget(labelSideBottomRow);


        jenBocniTablo->addLayout(pravplka);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        jenBocniTablo->addItem(horizontalSpacer);


        bocniTabloWrapper->addLayout(jenBocniTablo);

        verticalLayoutWidget_7 = new QWidget(page_led);
        verticalLayoutWidget_7->setObjectName(QString::fromUtf8("verticalLayoutWidget_7"));
        verticalLayoutWidget_7->setGeometry(QRect(10, 290, 561, 85));
        vnitrniTabloWraper = new QVBoxLayout(verticalLayoutWidget_7);
        vnitrniTabloWraper->setSpacing(0);
        vnitrniTabloWraper->setContentsMargins(11, 11, 11, 11);
        vnitrniTabloWraper->setObjectName(QString::fromUtf8("vnitrniTabloWraper"));
        vnitrniTabloWraper->setContentsMargins(0, 0, 0, 0);
        predniLabel_3 = new QLabel(verticalLayoutWidget_7);
        predniLabel_3->setObjectName(QString::fromUtf8("predniLabel_3"));
        sizePolicy2.setHeightForWidth(predniLabel_3->sizePolicy().hasHeightForWidth());
        predniLabel_3->setSizePolicy(sizePolicy2);

        vnitrniTabloWraper->addWidget(predniLabel_3);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(0);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelInnerLine = new QLabel(verticalLayoutWidget_7);
        labelInnerLine->setObjectName(QString::fromUtf8("labelInnerLine"));
        QSizePolicy sizePolicy10(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(labelInnerLine->sizePolicy().hasHeightForWidth());
        labelInnerLine->setSizePolicy(sizePolicy10);
        labelInnerLine->setMinimumSize(QSize(91, 0));
        labelInnerLine->setMaximumSize(QSize(91, 33));
        QFont font6;
        font6.setFamily(QString::fromUtf8("21-PID 3"));
        font6.setPointSize(65);
        labelInnerLine->setFont(font6);
        labelInnerLine->setStyleSheet(QString::fromUtf8("*{color:red;background-color:black;}"));
        labelInnerLine->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        horizontalLayout_10->addWidget(labelInnerLine);

        labelInnerTopRow = new QLabel(verticalLayoutWidget_7);
        labelInnerTopRow->setObjectName(QString::fromUtf8("labelInnerTopRow"));
        sizePolicy10.setHeightForWidth(labelInnerTopRow->sizePolicy().hasHeightForWidth());
        labelInnerTopRow->setSizePolicy(sizePolicy10);
        labelInnerTopRow->setMinimumSize(QSize(464, 0));
        labelInnerTopRow->setMaximumSize(QSize(464, 33));
        labelInnerTopRow->setFont(font6);
        labelInnerTopRow->setAutoFillBackground(false);
        labelInnerTopRow->setStyleSheet(QString::fromUtf8("*{color:red;background-color:black;}"));
        labelInnerTopRow->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        labelInnerTopRow->setMargin(0);

        horizontalLayout_10->addWidget(labelInnerTopRow);


        verticalLayout_14->addLayout(horizontalLayout_10);


        vnitrniTabloWraper->addLayout(verticalLayout_14);

        labelInnerBottomRow = new QLabel(verticalLayoutWidget_7);
        labelInnerBottomRow->setObjectName(QString::fromUtf8("labelInnerBottomRow"));
        sizePolicy10.setHeightForWidth(labelInnerBottomRow->sizePolicy().hasHeightForWidth());
        labelInnerBottomRow->setSizePolicy(sizePolicy10);
        labelInnerBottomRow->setMinimumSize(QSize(555, 0));
        labelInnerBottomRow->setMaximumSize(QSize(555, 33));
        labelInnerBottomRow->setFont(font6);
        labelInnerBottomRow->setAutoFillBackground(false);
        labelInnerBottomRow->setStyleSheet(QString::fromUtf8("*{color:red;background-color:black;}"));
        labelInnerBottomRow->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        vnitrniTabloWraper->addWidget(labelInnerBottomRow);

        verticalLayoutWidget_9 = new QWidget(page_led);
        verticalLayoutWidget_9->setObjectName(QString::fromUtf8("verticalLayoutWidget_9"));
        verticalLayoutWidget_9->setGeometry(QRect(550, 190, 119, 95));
        zadniTabloWrapper = new QVBoxLayout(verticalLayoutWidget_9);
        zadniTabloWrapper->setSpacing(0);
        zadniTabloWrapper->setContentsMargins(11, 11, 11, 11);
        zadniTabloWrapper->setObjectName(QString::fromUtf8("zadniTabloWrapper"));
        zadniTabloWrapper->setContentsMargins(0, 0, 0, 0);
        predniLabel_4 = new QLabel(verticalLayoutWidget_9);
        predniLabel_4->setObjectName(QString::fromUtf8("predniLabel_4"));
        QSizePolicy sizePolicy11(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(predniLabel_4->sizePolicy().hasHeightForWidth());
        predniLabel_4->setSizePolicy(sizePolicy11);

        zadniTabloWrapper->addWidget(predniLabel_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        labelRearLine = new QLabel(verticalLayoutWidget_9);
        labelRearLine->setObjectName(QString::fromUtf8("labelRearLine"));
        QSizePolicy sizePolicy12(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(labelRearLine->sizePolicy().hasHeightForWidth());
        labelRearLine->setSizePolicy(sizePolicy12);
        labelRearLine->setMinimumSize(QSize(115, 78));
        labelRearLine->setMaximumSize(QSize(115, 78));
        labelRearLine->setFont(font4);
        labelRearLine->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelRearLine->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_8->addWidget(labelRearLine);


        zadniTabloWrapper->addLayout(horizontalLayout_8);

        predniLabel = new QLabel(page_led);
        predniLabel->setObjectName(QString::fromUtf8("predniLabel"));
        predniLabel->setGeometry(QRect(10, 10, 49, 16));
        frame = new QFrame(page_led);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(180, 150, 120, 80));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(page_led);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 27, 651, 162));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        labelFrontLine = new QLabel(layoutWidget);
        labelFrontLine->setObjectName(QString::fromUtf8("labelFrontLine"));
        sizePolicy2.setHeightForWidth(labelFrontLine->sizePolicy().hasHeightForWidth());
        labelFrontLine->setSizePolicy(sizePolicy2);
        labelFrontLine->setMinimumSize(QSize(115, 78));
        labelFrontLine->setMaximumSize(QSize(115, 78));
        labelFrontLine->setFont(font4);
        labelFrontLine->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelFrontLine->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_6->addWidget(labelFrontLine);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        layoutDvaRadky = new QVBoxLayout();
        layoutDvaRadky->setSpacing(0);
        layoutDvaRadky->setObjectName(QString::fromUtf8("layoutDvaRadky"));
        labelFrontTopRow = new QLabel(layoutWidget);
        labelFrontTopRow->setObjectName(QString::fromUtf8("labelFrontTopRow"));
        sizePolicy8.setHeightForWidth(labelFrontTopRow->sizePolicy().hasHeightForWidth());
        labelFrontTopRow->setSizePolicy(sizePolicy8);
        labelFrontTopRow->setMinimumSize(QSize(460, 0));
        labelFrontTopRow->setMaximumSize(QSize(460, 37));
        QFont font7;
        font7.setFamily(QString::fromUtf8("21-PID 3"));
        font7.setPointSize(65);
        font7.setBold(false);
        font7.setWeight(50);
        labelFrontTopRow->setFont(font7);
        labelFrontTopRow->setAutoFillBackground(false);
        labelFrontTopRow->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelFrontTopRow->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        layoutDvaRadky->addWidget(labelFrontTopRow);

        labelFrontBottomRow = new QLabel(layoutWidget);
        labelFrontBottomRow->setObjectName(QString::fromUtf8("labelFrontBottomRow"));
        sizePolicy8.setHeightForWidth(labelFrontBottomRow->sizePolicy().hasHeightForWidth());
        labelFrontBottomRow->setSizePolicy(sizePolicy8);
        labelFrontBottomRow->setMinimumSize(QSize(460, 0));
        labelFrontBottomRow->setMaximumSize(QSize(460, 41));
        labelFrontBottomRow->setFont(font6);
        labelFrontBottomRow->setAutoFillBackground(false);
        labelFrontBottomRow->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelFrontBottomRow->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        layoutDvaRadky->addWidget(labelFrontBottomRow);


        verticalLayout_7->addLayout(layoutDvaRadky);

        labelFrontSingle = new QLabel(layoutWidget);
        labelFrontSingle->setObjectName(QString::fromUtf8("labelFrontSingle"));
        labelFrontSingle->setEnabled(false);
        sizePolicy8.setHeightForWidth(labelFrontSingle->sizePolicy().hasHeightForWidth());
        labelFrontSingle->setSizePolicy(sizePolicy8);
        labelFrontSingle->setMinimumSize(QSize(460, 0));
        labelFrontSingle->setMaximumSize(QSize(460, 78));
        QFont font8;
        font8.setFamily(QString::fromUtf8("21-PID 5"));
        font8.setPointSize(65);
        labelFrontSingle->setFont(font8);
        labelFrontSingle->setLayoutDirection(Qt::LeftToRight);
        labelFrontSingle->setAutoFillBackground(false);
        labelFrontSingle->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelFrontSingle->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_7->addWidget(labelFrontSingle);


        horizontalLayout_6->addLayout(verticalLayout_7);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        prepinadloStran->addWidget(page_led);

        horizontalLayout_5->addWidget(prepinadloStran);


        verticalLayout->addLayout(horizontalLayout_5);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        horizontalLayout_4->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 834, 21));
        menuBar->setNativeMenuBar(false);
        menunacti = new QMenu(menuBar);
        menunacti->setObjectName(QString::fromUtf8("menunacti"));
        menukonec = new QMenu(menuBar);
        menukonec->setObjectName(QString::fromUtf8("menukonec"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        sizePolicy11.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy11);
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(false);
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menunacti->menuAction());
        menuBar->addAction(menukonec->menuAction());
        menunacti->addAction(actiontestPolozka);
        menunacti->addAction(actionstahnoutXML);
        menunacti->addAction(action);

        retranslateUi(MainWindow);

        prepinadloStran->setCurrentIndex(0);
        stackedWidget_obrazovka->setCurrentIndex(0);
        stackedWidget_prostredek->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VDV301Display", nullptr));
        actiontestPolozka->setText(QCoreApplication::translate("MainWindow", "testPolozka", nullptr));
        actionstahnoutXML->setText(QCoreApplication::translate("MainWindow", "stahnoutXML", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        tlacitkoSeznamSluzeb->setText(QCoreApplication::translate("MainWindow", "Seznam \n"
" slu\305\276eb", nullptr));
        tlacitkoHlavni->setText(QCoreApplication::translate("MainWindow", "Hlavn\303\255 \n"
" obrazovka", nullptr));
        tlacitkoCasovac->setText(QCoreApplication::translate("MainWindow", "\304\214asova\304\215", nullptr));
        tlacitkoLed->setText(QCoreApplication::translate("MainWindow", "LED", nullptr));
        svgTlacitko->setText(QCoreApplication::translate("MainWindow", "SVG", nullptr));
        quitTlacitko->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        refreshTlac->setText(QCoreApplication::translate("MainWindow", "refresh", nullptr));
        Llinka->setText(QCoreApplication::translate("MainWindow", "741", nullptr));
        Lcil->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#3465a4;\">Sportovni hala</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        sipka->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        Lnacestna4->setText(QCoreApplication::translate("MainWindow", "Dalsi 3", nullptr));
        Lnacestna3->setText(QCoreApplication::translate("MainWindow", "Dalsi 2", nullptr));
        Lnacestna2->setText(QCoreApplication::translate("MainWindow", "Dalsi 1", nullptr));
        label_oznType->setText(QCoreApplication::translate("MainWindow", "obrazek", nullptr));
        label_oznTitle->setText(QCoreApplication::translate("MainWindow", "Nadpis", nullptr));
        label_oznTextCs->setText(QCoreApplication::translate("MainWindow", "TextCZ", nullptr));
        label_oznTextEn->setText(QCoreApplication::translate("MainWindow", "TextEN", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Pros\303\255m pozor! Zm\304\233na tarifn\303\255ho p\303\241sma.", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Attention please! Change of fare zone.", nullptr));
        label_pasmo1->setText(QCoreApplication::translate("MainWindow", "Pasmo1", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "->", nullptr));
        label_pasmo2->setText(QCoreApplication::translate("MainWindow", "Pasmo2", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Kone\304\215n\303\241 zast\303\241vka, pros\303\255me, vystupte.", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Final stop, please leave the bus.", nullptr));
        Lnacestna1->setText(QCoreApplication::translate("MainWindow", "PristiZastavka", nullptr));
        label_zmena->setText(QCoreApplication::translate("MainWindow", "zmena", nullptr));
        label_announcement->setText(QCoreApplication::translate("MainWindow", "announcement", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "PID", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "FW version:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "XX.YYZZ", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "SW version:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "XX.YYZZ", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Pros\303\255m pozor! Zm\304\233na \304\215\303\255sla linky.", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Attention please! Line number change.", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Linka1", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "->", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Linka2", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "LocationState", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "CurrentStopIndex", nullptr));
        label_currentStopIndex->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_locationState->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tabulkaSubscriberu->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "N\303\241zev slu\305\276by", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tabulkaSubscriberu->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Verze", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tabulkaSubscriberu->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "IP Adresa", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tabulkaSubscriberu->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "port", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Zb\303\275vaj\303\255c\303\255 \304\215as (s)", nullptr));
        labelZbyvajiciVteriny->setText(QCoreApplication::translate("MainWindow", "xx s", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Pole pro zad\303\241n\303\255 intervalu", nullptr));
        tlacitkoNastavVteriny->setText(QCoreApplication::translate("MainWindow", "Nastav interval", nullptr));
        bocniTabloNazev->setText(QCoreApplication::translate("MainWindow", "Bo\304\215n\303\255 tablo", nullptr));
        labelSideLine->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        labelSideTopRow->setText(QCoreApplication::translate("MainWindow", "DestinationSideName", nullptr));
        labelSideBottomRow->setText(QCoreApplication::translate("MainWindow", "StopSideName", nullptr));
        predniLabel_3->setText(QCoreApplication::translate("MainWindow", "vnit\305\231n\303\255 tablo", nullptr));
        labelInnerLine->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        labelInnerTopRow->setText(QCoreApplication::translate("MainWindow", "DestinationSideName", nullptr));
        labelInnerBottomRow->setText(QCoreApplication::translate("MainWindow", "StopSideName", nullptr));
        predniLabel_4->setText(QCoreApplication::translate("MainWindow", "Zadn\303\255 tablo", nullptr));
        labelRearLine->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        predniLabel->setText(QCoreApplication::translate("MainWindow", "P\305\231edn\303\255 tablo", nullptr));
        labelFrontLine->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        labelFrontTopRow->setText(QCoreApplication::translate("MainWindow", "Dest.FrontNameTop", nullptr));
        labelFrontBottomRow->setText(QCoreApplication::translate("MainWindow", "Dest.FrontNameBtm", nullptr));
        labelFrontSingle->setText(QCoreApplication::translate("MainWindow", "DestinationFrontSingle", nullptr));
        menunacti->setTitle(QCoreApplication::translate("MainWindow", "nacti", nullptr));
        menukonec->setTitle(QCoreApplication::translate("MainWindow", "konec", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
