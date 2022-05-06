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
    QWidget *page;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *Llinka;
    QLabel *Lcil;
    QHBoxLayout *horizontalLayout_3;
    QLabel *sipka;
    QVBoxLayout *verticalLayout_2;
    QLabel *Lnacestna4;
    QLabel *Lnacestna3;
    QLabel *Lnacestna2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Lnacestna1;
    QLabel *label_6;
    QLabel *label_zmena;
    QLabel *label_announcement;
    QWidget *page_2;
    QTableWidget *tabulkaSubscriberu;
    QWidget *page_3;
    QLabel *label;
    QLabel *labelZbyvajiciVteriny;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QPushButton *tlacitkoNastavVteriny;
    QWidget *page_4;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_6;
    QGraphicsView *graphicsView;
    QWidget *page_5;
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
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayoutWidget = new QWidget(page);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 811, 371));
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
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Lcil->sizePolicy().hasHeightForWidth());
        Lcil->setSizePolicy(sizePolicy3);
        Lcil->setFont(font1);
        Lcil->setAutoFillBackground(false);

        horizontalLayout->addWidget(Lcil);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sipka = new QLabel(verticalLayoutWidget);
        sipka->setObjectName(QString::fromUtf8("sipka"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(sipka->sizePolicy().hasHeightForWidth());
        sipka->setSizePolicy(sizePolicy4);
        sipka->setMaximumSize(QSize(50, 16777215));
        QFont font2;
        font2.setPointSize(70);
        sipka->setFont(font2);
        sipka->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(sipka);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Lnacestna4 = new QLabel(verticalLayoutWidget);
        Lnacestna4->setObjectName(QString::fromUtf8("Lnacestna4"));
        sizePolicy.setHeightForWidth(Lnacestna4->sizePolicy().hasHeightForWidth());
        Lnacestna4->setSizePolicy(sizePolicy);
        Lnacestna4->setFont(font);

        verticalLayout_2->addWidget(Lnacestna4);

        Lnacestna3 = new QLabel(verticalLayoutWidget);
        Lnacestna3->setObjectName(QString::fromUtf8("Lnacestna3"));
        sizePolicy.setHeightForWidth(Lnacestna3->sizePolicy().hasHeightForWidth());
        Lnacestna3->setSizePolicy(sizePolicy);
        Lnacestna3->setFont(font);

        verticalLayout_2->addWidget(Lnacestna3);

        Lnacestna2 = new QLabel(verticalLayoutWidget);
        Lnacestna2->setObjectName(QString::fromUtf8("Lnacestna2"));
        sizePolicy.setHeightForWidth(Lnacestna2->sizePolicy().hasHeightForWidth());
        Lnacestna2->setSizePolicy(sizePolicy);
        Lnacestna2->setFont(font);

        verticalLayout_2->addWidget(Lnacestna2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Lnacestna1 = new QLabel(verticalLayoutWidget);
        Lnacestna1->setObjectName(QString::fromUtf8("Lnacestna1"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(Lnacestna1->sizePolicy().hasHeightForWidth());
        Lnacestna1->setSizePolicy(sizePolicy5);
        Lnacestna1->setFont(font1);
        Lnacestna1->setScaledContents(false);

        horizontalLayout_2->addWidget(Lnacestna1);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy6);

        horizontalLayout_2->addWidget(label_6);


        verticalLayout_3->addLayout(horizontalLayout_2);

        label_zmena = new QLabel(verticalLayoutWidget);
        label_zmena->setObjectName(QString::fromUtf8("label_zmena"));

        verticalLayout_3->addWidget(label_zmena);

        label_announcement = new QLabel(verticalLayoutWidget);
        label_announcement->setObjectName(QString::fromUtf8("label_announcement"));

        verticalLayout_3->addWidget(label_announcement);

        prepinadloStran->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        tabulkaSubscriberu = new QTableWidget(page_2);
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
        prepinadloStran->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        label = new QLabel(page_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(420, 80, 151, 41));
        labelZbyvajiciVteriny = new QLabel(page_3);
        labelZbyvajiciVteriny->setObjectName(QString::fromUtf8("labelZbyvajiciVteriny"));
        labelZbyvajiciVteriny->setGeometry(QRect(420, 140, 231, 121));
        QFont font3;
        font3.setPointSize(60);
        labelZbyvajiciVteriny->setFont(font3);
        verticalLayoutWidget_3 = new QWidget(page_3);
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

        prepinadloStran->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        gridLayout = new QGridLayout(page_4);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        graphicsView = new QGraphicsView(page_4);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(graphicsView);


        gridLayout->addLayout(verticalLayout_6, 0, 0, 1, 1);

        prepinadloStran->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        verticalLayoutWidget_4 = new QWidget(page_5);
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
        QSizePolicy sizePolicy7(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(bocniTabloNazev->sizePolicy().hasHeightForWidth());
        bocniTabloNazev->setSizePolicy(sizePolicy7);

        bocniTabloWrapper->addWidget(bocniTabloNazev);

        jenBocniTablo = new QHBoxLayout();
        jenBocniTablo->setSpacing(0);
        jenBocniTablo->setObjectName(QString::fromUtf8("jenBocniTablo"));
        labelSideLine = new QLabel(verticalLayoutWidget_4);
        labelSideLine->setObjectName(QString::fromUtf8("labelSideLine"));
        sizePolicy6.setHeightForWidth(labelSideLine->sizePolicy().hasHeightForWidth());
        labelSideLine->setSizePolicy(sizePolicy6);
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
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(labelSideTopRow->sizePolicy().hasHeightForWidth());
        labelSideTopRow->setSizePolicy(sizePolicy8);
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
        sizePolicy8.setHeightForWidth(labelSideBottomRow->sizePolicy().hasHeightForWidth());
        labelSideBottomRow->setSizePolicy(sizePolicy8);
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

        verticalLayoutWidget_7 = new QWidget(page_5);
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
        QSizePolicy sizePolicy9(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(labelInnerLine->sizePolicy().hasHeightForWidth());
        labelInnerLine->setSizePolicy(sizePolicy9);
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
        sizePolicy9.setHeightForWidth(labelInnerTopRow->sizePolicy().hasHeightForWidth());
        labelInnerTopRow->setSizePolicy(sizePolicy9);
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
        sizePolicy9.setHeightForWidth(labelInnerBottomRow->sizePolicy().hasHeightForWidth());
        labelInnerBottomRow->setSizePolicy(sizePolicy9);
        labelInnerBottomRow->setMinimumSize(QSize(555, 0));
        labelInnerBottomRow->setMaximumSize(QSize(555, 33));
        labelInnerBottomRow->setFont(font6);
        labelInnerBottomRow->setAutoFillBackground(false);
        labelInnerBottomRow->setStyleSheet(QString::fromUtf8("*{color:red;background-color:black;}"));
        labelInnerBottomRow->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        vnitrniTabloWraper->addWidget(labelInnerBottomRow);

        verticalLayoutWidget_9 = new QWidget(page_5);
        verticalLayoutWidget_9->setObjectName(QString::fromUtf8("verticalLayoutWidget_9"));
        verticalLayoutWidget_9->setGeometry(QRect(550, 190, 119, 95));
        zadniTabloWrapper = new QVBoxLayout(verticalLayoutWidget_9);
        zadniTabloWrapper->setSpacing(0);
        zadniTabloWrapper->setContentsMargins(11, 11, 11, 11);
        zadniTabloWrapper->setObjectName(QString::fromUtf8("zadniTabloWrapper"));
        zadniTabloWrapper->setContentsMargins(0, 0, 0, 0);
        predniLabel_4 = new QLabel(verticalLayoutWidget_9);
        predniLabel_4->setObjectName(QString::fromUtf8("predniLabel_4"));
        QSizePolicy sizePolicy10(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(predniLabel_4->sizePolicy().hasHeightForWidth());
        predniLabel_4->setSizePolicy(sizePolicy10);

        zadniTabloWrapper->addWidget(predniLabel_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        labelRearLine = new QLabel(verticalLayoutWidget_9);
        labelRearLine->setObjectName(QString::fromUtf8("labelRearLine"));
        QSizePolicy sizePolicy11(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(labelRearLine->sizePolicy().hasHeightForWidth());
        labelRearLine->setSizePolicy(sizePolicy11);
        labelRearLine->setMinimumSize(QSize(115, 78));
        labelRearLine->setMaximumSize(QSize(115, 78));
        labelRearLine->setFont(font4);
        labelRearLine->setStyleSheet(QString::fromUtf8("*{color:orange;background-color:black;}"));
        labelRearLine->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_8->addWidget(labelRearLine);


        zadniTabloWrapper->addLayout(horizontalLayout_8);

        predniLabel = new QLabel(page_5);
        predniLabel->setObjectName(QString::fromUtf8("predniLabel"));
        predniLabel->setGeometry(QRect(10, 10, 49, 16));
        frame = new QFrame(page_5);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(180, 150, 120, 80));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(page_5);
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
        sizePolicy7.setHeightForWidth(labelFrontTopRow->sizePolicy().hasHeightForWidth());
        labelFrontTopRow->setSizePolicy(sizePolicy7);
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
        sizePolicy7.setHeightForWidth(labelFrontBottomRow->sizePolicy().hasHeightForWidth());
        labelFrontBottomRow->setSizePolicy(sizePolicy7);
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
        sizePolicy7.setHeightForWidth(labelFrontSingle->sizePolicy().hasHeightForWidth());
        labelFrontSingle->setSizePolicy(sizePolicy7);
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

        prepinadloStran->addWidget(page_5);

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
        sizePolicy10.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy10);
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
        sipka->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        Lnacestna4->setText(QCoreApplication::translate("MainWindow", "Dalsi 3", nullptr));
        Lnacestna3->setText(QCoreApplication::translate("MainWindow", "Dalsi 2", nullptr));
        Lnacestna2->setText(QCoreApplication::translate("MainWindow", "Dalsi 1", nullptr));
        Lnacestna1->setText(QCoreApplication::translate("MainWindow", "PristiZastavka", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        label_zmena->setText(QCoreApplication::translate("MainWindow", "zmena", nullptr));
        label_announcement->setText(QCoreApplication::translate("MainWindow", "announcement", nullptr));
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
