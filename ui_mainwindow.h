/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
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
        tlacitkoSeznamSluzeb->setCheckable(true);
        tlacitkoSeznamSluzeb->setAutoExclusive(true);

        verticalLayout_4->addWidget(tlacitkoSeznamSluzeb);

        tlacitkoHlavni = new QPushButton(centralWidget);
        tlacitkoHlavni->setObjectName(QString::fromUtf8("tlacitkoHlavni"));
        tlacitkoHlavni->setCheckable(true);
        tlacitkoHlavni->setChecked(true);
        tlacitkoHlavni->setAutoExclusive(true);

        verticalLayout_4->addWidget(tlacitkoHlavni);

        tlacitkoCasovac = new QPushButton(centralWidget);
        tlacitkoCasovac->setObjectName(QString::fromUtf8("tlacitkoCasovac"));
        tlacitkoCasovac->setCheckable(true);
        tlacitkoCasovac->setAutoExclusive(true);

        verticalLayout_4->addWidget(tlacitkoCasovac);

        svgTlacitko = new QPushButton(centralWidget);
        svgTlacitko->setObjectName(QString::fromUtf8("svgTlacitko"));

        verticalLayout_4->addWidget(svgTlacitko);

        quitTlacitko = new QPushButton(centralWidget);
        quitTlacitko->setObjectName(QString::fromUtf8("quitTlacitko"));
        quitTlacitko->setCheckable(true);
        quitTlacitko->setAutoExclusive(true);

        verticalLayout_4->addWidget(quitTlacitko);

        refreshTlac = new QPushButton(centralWidget);
        refreshTlac->setObjectName(QString::fromUtf8("refreshTlac"));

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
        QFont font;
        font.setPointSize(30);
        Llinka->setFont(font);
        Llinka->setAutoFillBackground(false);

        horizontalLayout->addWidget(Llinka);

        Lcil = new QLabel(verticalLayoutWidget);
        Lcil->setObjectName(QString::fromUtf8("Lcil"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Lcil->sizePolicy().hasHeightForWidth());
        Lcil->setSizePolicy(sizePolicy3);
        Lcil->setFont(font);
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
        QFont font1;
        font1.setPointSize(70);
        sipka->setFont(font1);
        sipka->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(sipka);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Lnacestna4 = new QLabel(verticalLayoutWidget);
        Lnacestna4->setObjectName(QString::fromUtf8("Lnacestna4"));
        sizePolicy.setHeightForWidth(Lnacestna4->sizePolicy().hasHeightForWidth());
        Lnacestna4->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(20);
        Lnacestna4->setFont(font2);

        verticalLayout_2->addWidget(Lnacestna4);

        Lnacestna3 = new QLabel(verticalLayoutWidget);
        Lnacestna3->setObjectName(QString::fromUtf8("Lnacestna3"));
        sizePolicy.setHeightForWidth(Lnacestna3->sizePolicy().hasHeightForWidth());
        Lnacestna3->setSizePolicy(sizePolicy);
        Lnacestna3->setFont(font2);

        verticalLayout_2->addWidget(Lnacestna3);

        Lnacestna2 = new QLabel(verticalLayoutWidget);
        Lnacestna2->setObjectName(QString::fromUtf8("Lnacestna2"));
        sizePolicy.setHeightForWidth(Lnacestna2->sizePolicy().hasHeightForWidth());
        Lnacestna2->setSizePolicy(sizePolicy);
        Lnacestna2->setFont(font2);

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
        Lnacestna1->setFont(font);
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
        verticalLayoutWidget_3->setGeometry(QRect(60, 110, 160, 80));
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
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy7);
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

        prepinadloStran->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actiontestPolozka->setText(QCoreApplication::translate("MainWindow", "testPolozka", nullptr));
        actionstahnoutXML->setText(QCoreApplication::translate("MainWindow", "stahnoutXML", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        tlacitkoSeznamSluzeb->setText(QCoreApplication::translate("MainWindow", "Seznam \n"
" slu\305\276eb", nullptr));
        tlacitkoHlavni->setText(QCoreApplication::translate("MainWindow", "Hlavn\303\255 obrazovka", nullptr));
        tlacitkoCasovac->setText(QCoreApplication::translate("MainWindow", "\304\214asova\304\215", nullptr));
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
        menunacti->setTitle(QCoreApplication::translate("MainWindow", "nacti", nullptr));
        menukonec->setTitle(QCoreApplication::translate("MainWindow", "konec", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
