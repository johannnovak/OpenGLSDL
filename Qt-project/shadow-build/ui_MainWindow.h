/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *OpenGLLayout;
    QVBoxLayout *auxLayout;
    QLabel *sliderLabel;
    QSlider *particleCountSlider;
    QTabWidget *particlesTab;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 801, 531));
        OpenGLLayout = new QHBoxLayout(horizontalLayoutWidget);
        OpenGLLayout->setObjectName(QString::fromUtf8("OpenGLLayout"));
        OpenGLLayout->setContentsMargins(0, 0, 0, 0);
        auxLayout = new QVBoxLayout();
        auxLayout->setObjectName(QString::fromUtf8("auxLayout"));
        auxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        sliderLabel = new QLabel(horizontalLayoutWidget);
        sliderLabel->setObjectName(QString::fromUtf8("sliderLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sliderLabel->sizePolicy().hasHeightForWidth());
        sliderLabel->setSizePolicy(sizePolicy);
        sliderLabel->setAutoFillBackground(false);
        sliderLabel->setAlignment(Qt::AlignCenter);

        auxLayout->addWidget(sliderLabel);

        particleCountSlider = new QSlider(horizontalLayoutWidget);
        particleCountSlider->setObjectName(QString::fromUtf8("particleCountSlider"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(particleCountSlider->sizePolicy().hasHeightForWidth());
        particleCountSlider->setSizePolicy(sizePolicy1);
        particleCountSlider->setMaximum(100);
        particleCountSlider->setValue(50);
        particleCountSlider->setOrientation(Qt::Horizontal);

        auxLayout->addWidget(particleCountSlider);

        particlesTab = new QTabWidget(horizontalLayoutWidget);
        particlesTab->setObjectName(QString::fromUtf8("particlesTab"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(particlesTab->sizePolicy().hasHeightForWidth());
        particlesTab->setSizePolicy(sizePolicy2);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        sizePolicy.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy);
        particlesTab->addTab(tab, QString());
        particlesTab->setTabText(particlesTab->indexOf(tab), QString::fromUtf8("Tab 1"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        particlesTab->addTab(tab_2, QString());
        particlesTab->setTabText(particlesTab->indexOf(tab_2), QString::fromUtf8("Tab 2"));

        auxLayout->addWidget(particlesTab);


        OpenGLLayout->addLayout(auxLayout);

        MainWindow->setCentralWidget(centralwidget);
        horizontalLayoutWidget->raise();
        particlesTab->raise();
        sliderLabel->raise();
        particleCountSlider->raise();
        particlesTab->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        particlesTab->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ParticleSystem Simulator", 0, QApplication::UnicodeUTF8));
        sliderLabel->setText(QApplication::translate("MainWindow", "Particle Count", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
