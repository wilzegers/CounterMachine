/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *simulationTab;
    QTableWidget *instructionTableWidget;
    QTableWidget *registerTableWidget;
    QLabel *label_2;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QPushButton *stepButton;
    QPushButton *runButton;
    QLabel *label;
    QPushButton *browseButton;
    QPushButton *loadButton;
    QLineEdit *fileNameLineEdit;
    QLineEdit *inputParamsLineEdit;
    QWidget *tranformationTab;
    QLabel *label_3;
    QGroupBox *groupBox;
    QRadioButton *group1Selector;
    QRadioButton *group2Selector;
    QRadioButton *group3Selector;
    QPushButton *browseButton_2;
    QPushButton *transformButton;
    QLineEdit *fileNameLineEdit_2;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(531, 376);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(531, 376));
        MainWindow->setMaximumSize(QSize(531, 376));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 541, 331));
        simulationTab = new QWidget();
        simulationTab->setObjectName(QStringLiteral("simulationTab"));
        instructionTableWidget = new QTableWidget(simulationTab);
        instructionTableWidget->setObjectName(QStringLiteral("instructionTableWidget"));
        instructionTableWidget->setGeometry(QRect(10, 10, 171, 291));
        instructionTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instructionTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instructionTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        instructionTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        instructionTableWidget->setShowGrid(false);
        instructionTableWidget->setWordWrap(false);
        instructionTableWidget->setCornerButtonEnabled(false);
        instructionTableWidget->horizontalHeader()->setVisible(false);
        instructionTableWidget->horizontalHeader()->setHighlightSections(false);
        instructionTableWidget->horizontalHeader()->setStretchLastSection(true);
        instructionTableWidget->verticalHeader()->setVisible(false);
        instructionTableWidget->verticalHeader()->setHighlightSections(false);
        registerTableWidget = new QTableWidget(simulationTab);
        registerTableWidget->setObjectName(QStringLiteral("registerTableWidget"));
        registerTableWidget->setGeometry(QRect(200, 150, 321, 151));
        registerTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        registerTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        registerTableWidget->setWordWrap(false);
        registerTableWidget->setCornerButtonEnabled(false);
        registerTableWidget->horizontalHeader()->setVisible(false);
        registerTableWidget->horizontalHeader()->setHighlightSections(false);
        registerTableWidget->horizontalHeader()->setStretchLastSection(true);
        registerTableWidget->verticalHeader()->setVisible(false);
        registerTableWidget->verticalHeader()->setHighlightSections(false);
        label_2 = new QLabel(simulationTab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(200, 50, 91, 31));
        line = new QFrame(simulationTab);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(180, -20, 20, 331));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(simulationTab);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(190, 130, 331, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(simulationTab);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(190, 81, 331, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        stepButton = new QPushButton(simulationTab);
        stepButton->setObjectName(QStringLiteral("stepButton"));
        stepButton->setGeometry(QRect(310, 100, 101, 31));
        runButton = new QPushButton(simulationTab);
        runButton->setObjectName(QStringLiteral("runButton"));
        runButton->setGeometry(QRect(420, 100, 101, 31));
        label = new QLabel(simulationTab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 10, 81, 31));
        browseButton = new QPushButton(simulationTab);
        browseButton->setObjectName(QStringLiteral("browseButton"));
        browseButton->setGeometry(QRect(440, 10, 81, 31));
        loadButton = new QPushButton(simulationTab);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setGeometry(QRect(200, 100, 101, 31));
        fileNameLineEdit = new QLineEdit(simulationTab);
        fileNameLineEdit->setObjectName(QStringLiteral("fileNameLineEdit"));
        fileNameLineEdit->setGeometry(QRect(250, 10, 181, 31));
        inputParamsLineEdit = new QLineEdit(simulationTab);
        inputParamsLineEdit->setObjectName(QStringLiteral("inputParamsLineEdit"));
        inputParamsLineEdit->setGeometry(QRect(290, 50, 231, 31));
        tabWidget->addTab(simulationTab, QString());
        tranformationTab = new QWidget();
        tranformationTab->setObjectName(QStringLiteral("tranformationTab"));
        label_3 = new QLabel(tranformationTab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 81, 31));
        groupBox = new QGroupBox(tranformationTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(170, 90, 181, 91));
        group1Selector = new QRadioButton(groupBox);
        group1Selector->setObjectName(QStringLiteral("group1Selector"));
        group1Selector->setGeometry(QRect(40, 20, 131, 17));
        group1Selector->setChecked(true);
        group2Selector = new QRadioButton(groupBox);
        group2Selector->setObjectName(QStringLiteral("group2Selector"));
        group2Selector->setGeometry(QRect(40, 40, 111, 17));
        group3Selector = new QRadioButton(groupBox);
        group3Selector->setObjectName(QStringLiteral("group3Selector"));
        group3Selector->setGeometry(QRect(40, 60, 111, 17));
        browseButton_2 = new QPushButton(tranformationTab);
        browseButton_2->setObjectName(QStringLiteral("browseButton_2"));
        browseButton_2->setGeometry(QRect(440, 10, 81, 31));
        transformButton = new QPushButton(tranformationTab);
        transformButton->setObjectName(QStringLiteral("transformButton"));
        transformButton->setGeometry(QRect(210, 220, 101, 31));
        fileNameLineEdit_2 = new QLineEdit(tranformationTab);
        fileNameLineEdit_2->setObjectName(QStringLiteral("fileNameLineEdit_2"));
        fileNameLineEdit_2->setGeometry(QRect(90, 10, 341, 31));
        tabWidget->addTab(tranformationTab, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 531, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CounterMachine application", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Input Parameters", Q_NULLPTR));
        stepButton->setText(QApplication::translate("MainWindow", "Step", Q_NULLPTR));
        runButton->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Filename", Q_NULLPTR));
        browseButton->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        loadButton->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(simulationTab), QApplication::translate("MainWindow", "Simulation", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Inputfile name", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Sets", Q_NULLPTR));
        group1Selector->setText(QApplication::translate("MainWindow", "DEC, INC, JZ", Q_NULLPTR));
        group2Selector->setText(QApplication::translate("MainWindow", "CLR, INC, JE", Q_NULLPTR));
        group3Selector->setText(QApplication::translate("MainWindow", "CPY, INC, JE", Q_NULLPTR));
        browseButton_2->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        transformButton->setText(QApplication::translate("MainWindow", "Transform", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tranformationTab), QApplication::translate("MainWindow", "Transformation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
