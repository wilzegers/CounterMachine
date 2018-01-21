#include <QFileDialog>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(std::make_unique<Ui::MainWindow>())
{

    DEBUGFUN();
    ui->setupUi(this);
    ui->instructionTableWidget->setEnabled(false);

    connect(ui->loadButton, SIGNAL(released()), this, SLOT(SimulationLoadButtonClicked()));
    connect(ui->transformButton, SIGNAL(released()), this, SLOT(TransformationStartButtonClicked()));
    connect(ui->stepButton, SIGNAL(released()), this, SLOT(StepButtonClicked()));
    connect(ui->runButton, SIGNAL(released()), this, SLOT(RunButtonClicked()));
    connect(ui->instructionTableWidget, SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),
	    this, SLOT(InstructionTable_CurrentItemChanged(QTableWidgetItem*,QTableWidgetItem*)));

    connect(&model, SIGNAL(SimulationEnded()), this, SLOT(EndSimulation()));
    connect(&model, SIGNAL(ProgramLoaded(std::vector<std::string>,RegisterValueMap, size_t)),
	    this, SLOT(SimulationLoaded(std::vector<std::string>,RegisterValueMap, size_t)));
    connect(&model, SIGNAL(StateChanged(size_t,std::vector<RegisterValue>)),
	this, SLOT(ChangeSimulationState(size_t,std::vector<RegisterValue>)));

    SetupFileInputConnection(ui->fileNameLineEdit, ui->browseButton);
    SetupFileInputConnection(ui->fileNameLineEdit_2, ui->browseButton_2);
}

MainWindow::~MainWindow()
{
    DEBUGFUN();
}

void MainWindow::SimulationLoaded(const std::vector<std::string>& instructions,
				  const RegisterValueMap& reg_inits,
				  size_t reg_count)
{
    DEBUGFUN();
    ui->runButton->setEnabled(true);
    ui->stepButton->setEnabled(true);

    instruction_strings = instructions;
    SetupInstructionTableContent();
    SetupRegisterTableContentFrom([this, &reg_inits](const size_t i)
    {
	auto result = reg_inits.find(i);
	return result == reg_inits.end() ? "?" : QString::number(result->second);
    }, reg_count);
}

void MainWindow::ChangeSimulationState(size_t next_instruction, const std::vector<RegisterValue>& registers)
{
    DEBUGFUN();

    ui->instructionTableWidget->setCurrentCell(next_instruction, 0);

    register_values = registers;

    SetupRegisterTableContentFrom([this](const size_t i)
    {
	return QString::number(register_values[i]);
    }, register_values.size());
}

void MainWindow::EndSimulation()
{

    DEBUGFUN();
    ui->runButton->setEnabled(false);
    ui->stepButton->setEnabled(false);
}

void MainWindow::InstructionTable_CurrentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    DEBUGFUN();
    if(previous)
    {
	previous->setBackground(Qt::GlobalColor::white);
	previous->setTextColor(Qt::GlobalColor::black);
    }
    ui->instructionTableWidget->scrollToItem(current);
    current->setBackground(Qt::GlobalColor::black);
    current->setTextColor(Qt::GlobalColor::white);
}

void MainWindow::SimulationLoadButtonClicked()
{
    DEBUGFUN();
    std::wstring filename{ ui->fileNameLineEdit->text().toStdWString() };
    std::string input_str{ ui->inputParamsLineEdit->text().toStdString() };

    CallSafely([&](){
	model.OpenFile(filename, input_str);
    });
}

void MainWindow::TransformationStartButtonClicked()
{
    DEBUGFUN();
    std::wstring inputFile{ ui->fileNameLineEdit_2->text().toStdWString() };
    size_t set = ui->group1Selector->isChecked() ? 1 :
	(ui->group2Selector->isChecked() ? 2 : 3);
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    std::wstring outputFile = dialog.getSaveFileName(NULL, "Create New File","","").toStdWString();

    CallSafely([&](){
	model.TransformFile(inputFile, outputFile, set);
    });
}
void MainWindow::StepButtonClicked()
{
    DEBUGFUN();
    CallSafely([&](){
	model.StepProgram();
    });
}
void MainWindow::RunButtonClicked()
{
    DEBUGFUN();
    CallSafely([&](){
	model.RunProgram();
    });
}

void MainWindow::SetupInstructionTableContent()
{

    DEBUGFUN();
    ui->instructionTableWidget->setRowCount(instruction_strings.size());
    ui->instructionTableWidget->setColumnCount(1);

    for (size_t i = 0; i < instruction_strings.size(); ++i)
    {
	auto item = new QTableWidgetItem{ QString::number(i) + ". " + QString::fromStdString(instruction_strings[i]) };
	item->setBackground(Qt::GlobalColor::white);
	item->setTextColor(Qt::GlobalColor::black);
	ui->instructionTableWidget->setItem(i, 0, item);
    }

    ui->instructionTableWidget->setCurrentCell(0, 0);
}

void MainWindow::SetupFileInputConnection(QLineEdit *fileNameBox, QPushButton *browseButton)
{

    DEBUGFUN();
    connect(browseButton, &QPushButton::released,
	[fileNameBox]()
	{
	    QFileDialog dialog;
	    dialog.setFileMode(QFileDialog::ExistingFile);
	    QString outputFile{ dialog.getOpenFileName(NULL, "Open Program","","") };
	    fileNameBox->setText(outputFile);
	});
}
