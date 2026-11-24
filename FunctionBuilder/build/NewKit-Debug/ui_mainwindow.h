/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graphcanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAddFunction;
    QAction *actionResetScale;
    QAction *actionSettings;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QWidget *functionPanel;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *addButton;
    QToolButton *deleteButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *functionsLayout;
    QSpacerItem *functionsBottomSpacer;
    GraphCanvas *graphCanvas;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1178, 798);
        actionAddFunction = new QAction(MainWindow);
        actionAddFunction->setObjectName("actionAddFunction");
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("list-add")));
        actionAddFunction->setIcon(icon);
        QFont font;
        actionAddFunction->setFont(font);
        actionAddFunction->setMenuRole(QAction::MenuRole::NoRole);
        actionResetScale = new QAction(MainWindow);
        actionResetScale->setObjectName("actionResetScale");
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("view-refresh")));
        actionResetScale->setIcon(icon1);
        actionResetScale->setMenuRole(QAction::MenuRole::NoRole);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName("actionSettings");
        QIcon icon2(QIcon::fromTheme(QString::fromUtf8("document-properties")));
        actionSettings->setIcon(icon2);
        actionSettings->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setMaximumSize(QSize(16777215, 16777215));
        splitter->setOrientation(Qt::Orientation::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(false);
        functionPanel = new QWidget(splitter);
        functionPanel->setObjectName("functionPanel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(functionPanel->sizePolicy().hasHeightForWidth());
        functionPanel->setSizePolicy(sizePolicy1);
        functionPanel->setMinimumSize(QSize(320, 0));
        verticalLayout_2 = new QVBoxLayout(functionPanel);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(12, 12, 12, 12);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(functionPanel);
        label->setObjectName("label");
        label->setEnabled(true);

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(148, 35, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addButton = new QToolButton(functionPanel);
        addButton->setObjectName("addButton");

        horizontalLayout->addWidget(addButton);

        deleteButton = new QToolButton(functionPanel);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setEnabled(false);

        horizontalLayout->addWidget(deleteButton);


        verticalLayout_2->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(functionPanel);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 296, 610));
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8("\n"
"/* \320\232\320\260\321\200\321\202\320\276\321\207\320\272\320\260 \321\204\321\203\320\275\320\272\321\206\320\270\320\270 */\n"
"QFrame#functionRow {\n"
"    background-color: #2B3039;\n"
"    border: 1px solid #343D49;\n"
"    border-radius: 9px;\n"
"}\n"
"\n"
"QFrame#functionRow:hover {\n"
"    border-color: #455162;\n"
"}\n"
"\n"
"QFrame#functionRow QLabel { color: #CBD5E1; background: transparent; border: none; }\n"
"\n"
"/* \320\250\320\265\321\201\321\202\321\214 \321\202\320\276\321\207\320\265\320\272 */\n"
"QToolButton#functionDrag {\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 0px;\n"
"}\n"
"\n"
"/* \320\223\320\260\320\273\320\276\321\207\320\272\320\260 \320\262\320\270\320\264\320\270\320\274\320\276\321\201\321\202\320\270 */\n"
"QToolButton#functionVisibility {\n"
"    background-color: #202936;\n"
"    color: transparent;\n"
"    border: 1px solid #46546A;\n"
"    border-radius: 6px;\n"
"    font-size: 19px;\n"
"    font-weight: bold;\n"
"    padding: 0px;\n"
""
                        "}\n"
"\n"
"QToolButton#functionVisibility:checked {\n"
"    background-color: #2D83F5;\n"
"    border: 1px solid #2879E5;\n"
"    color: white;\n"
"}\n"
"\n"
"/* \320\237\320\276\320\273\320\265 \320\262\320\262\320\276\320\264\320\260 \320\262\321\213\321\200\320\260\320\266\320\265\320\275\320\270\321\217 */\n"
"QLineEdit#functionExpression {\n"
"    background-color: #191F28;\n"
"    color: #E9EDF4;\n"
"    border: 2px solid #424F60;\n"
"    border-radius: 7px;\n"
"    padding: 4px 11px;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 16px;\n"
"    selection-background-color: #347BF5;\n"
"}\n"
"\n"
"QLineEdit#functionExpression:focus {\n"
"    border-color: #64748B;\n"
"}\n"
"\n"
"/* \320\232\320\275\320\276\320\277\320\272\320\260 \321\203\320\264\320\260\320\273\320\265\320\275\320\270\321\217 */\n"
"QToolButton#functionRemove {\n"
"    background: transparent;\n"
"    color: #C8CDD5;\n"
"    border: none;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 27px;\n"
"    padding: 0px;\n"
"}\n"
"\n"
""
                        "QToolButton#functionRemove:hover {\n"
"    color: #F05262;\n"
"}\n"
""));
        functionsLayout = new QVBoxLayout(scrollAreaWidgetContents);
        functionsLayout->setSpacing(8);
        functionsLayout->setObjectName("functionsLayout");
        functionsLayout->setContentsMargins(3, 6, 3, 6);
        functionsBottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        functionsLayout->addItem(functionsBottomSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        splitter->addWidget(functionPanel);
        graphCanvas = new GraphCanvas(splitter);
        graphCanvas->setObjectName("graphCanvas");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(3);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphCanvas->sizePolicy().hasHeightForWidth());
        graphCanvas->setSizePolicy(sizePolicy2);
        graphCanvas->setMinimumSize(QSize(440, 0));
        splitter->addWidget(graphCanvas);

        verticalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1178, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setEnabled(false);
        statusbar->setVisible(true);
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setMovable(false);
        toolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        toolBar->addAction(actionAddFunction);
        toolBar->addSeparator();
        toolBar->addAction(actionResetScale);
        toolBar->addSeparator();
        toolBar->addAction(actionSettings);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Graphing Calculator", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "/* Graphing Calculator \342\200\224 dark Qt Widgets form */\n"
"QMainWindow { background: #171C24; color: #F1F5F9; }\n"
"QWidget#centralwidget { background: #171C24; }\n"
"QWidget#functionPanel { background: #1E2530; border: none; }\n"
"QLabel#label { background: transparent; color: #F1F5F9; font-size: 18px; font-weight: 700; }\n"
"QToolBar { background: #252D39; border: 0; border-bottom: 1px solid #394454; padding: 7px; spacing: 8px; }\n"
"QToolBar QToolButton { background: transparent; color: #F1F5F9; padding: 8px 11px; border: 0; border-radius: 6px; font-size: 13px; }\n"
"QToolBar QToolButton:hover { background: #364254; }\n"
"QToolBar QToolButton:pressed { background: #3478F6; }\n"
"QToolBar::separator { background: #465367; width: 1px; margin: 5px 8px; }\n"
"QToolButton#addButton, QToolButton#deleteButton { background: #303A49; color: #F1F5F9; border: 1px solid #465367; border-radius: 6px; padding: 5px; min-width: 24px; min-height: 24px; }\n"
"QToolButton#addButton:hover { background: #3478F6; border-colo"
                        "r: #3478F6; }\n"
"QToolButton#deleteButton:hover { background: #B83B4B; border-color: #B83B4B; }\n"
"QScrollArea#scrollArea, QWidget#scrollAreaWidgetContents { background: #1E2530; border: none; }\n"
"QFrame[functionRow=\"true\"] { background: #2B3442; border: 1px solid #394454; border-radius: 8px; }\n"
"QFrame[functionRow=\"true\"] QLabel { color: #94A3B8; background: transparent; border: none; }\n"
"QFrame[functionRow=\"true\"] QLineEdit { background: #19212C; color: #F1F5F9; border: 1px solid #465367; border-radius: 5px; padding: 7px; font-size: 14px; }\n"
"QFrame[functionRow=\"true\"] QLineEdit:focus { border-color: #3478F6; }\n"
"QFrame[functionRow=\"true\"] QCheckBox { background: transparent; border: none; }\n"
"QFrame[functionRow=\"true\"] QToolButton { color: #F1F5F9; background: transparent; border: none; border-radius: 5px; font-size: 18px; }\n"
"QFrame[functionRow=\"true\"] QToolButton:hover { background: #B83B4B; }\n"
"QScrollBar:vertical { background: #1E2530; width: 9px; border: none; margin: 0;"
                        " }\n"
"QScrollBar::handle:vertical { background: #465367; min-height: 24px; border-radius: 4px; }\n"
"QScrollBar::handle:vertical:hover { background: #64748B; }\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; border: none; }\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }\n"
"QSplitter::handle:horizontal { background: #394454; width: 5px; }\n"
"QSplitter::handle:horizontal:hover { background: #3478F6; }\n"
"QWidget#graphCanvas { background: #111923; border: none; }\n"
"QWidget#bottomBar { background: #252D39; border-top: 1px solid #394454; }\n"
"QWidget#bottomBar QLabel { background: transparent; color: #DCE4EF; border: none; font-size: 12px; }\n"
"QMenuBar { background: #252D39; color: #F1F5F9; }\n"
"QMenuBar::item:selected { background: #364254; }\n"
"QStatusBar { background: #252D39; color: #F1F5F9; }", nullptr));
        actionAddFunction->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\204\321\203\320\275\320\272\321\206\320\270\321\216", nullptr));
        actionResetScale->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214 \320\274\320\260\321\201\321\210\321\202\320\260\320\261", nullptr));
        actionSettings->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\244\321\203\320\275\320\272\321\206\320\270\320\270", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
#if QT_CONFIG(tooltip)
        deleteButton->setToolTip(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\321\216\321\216 \320\272\320\260\321\200\321\202\320\276\321\207\320\272\321\203", nullptr));
#endif // QT_CONFIG(tooltip)
        deleteButton->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
