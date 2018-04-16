#include <QFileDialog>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    ui.instructionTableWidget->setEnabled(false);

    connect(ui.loadButton, SIGNAL(released()), this, SLOT(SimulationLoadButtonClicked()));
    connect(ui.transformButton, SIGNAL(released()), this, SLOT(TransformationStartButtonClicked()));
    connect(ui.stepButton, SIGNAL(released()), this, SLOT(StepButtonClicked()));
    connect(ui.runButton, SIGNAL(released()), this, SLOT(RunButtonClicked()));
    connect(ui.instructionTableWidget, SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),
        this, SLOT(InstructionTable_CurrentItemChanged(QTableWidgetItem*,QTableWidgetItem*)));

    connect(&model, SIGNAL(SimulationEnded()), this, SLOT(EndSimulation()));
    connect(&model, SIGNAL(ProgramLoaded(std::vector<std::string>,RegisterValueMap, size_t, size_t)),
        this, SLOT(SimulationLoaded(std::vector<std::string>,RegisterValueMap, size_t, size_t)));
    connect(&model, SIGNAL(StateChanged(size_t,std::vector<RegisterValue>)),
        this, SLOT(ChangeSimulationState(size_t,std::vector<RegisterValue>)));

    SetupFileInputConnection(ui.fileNameLineEdit, ui.browseButton);
    SetupFileInputConnection(ui.fileNameLineEdit_2, ui.browseButton_2);
}

void MainWindow::SimulationLoaded(const std::vector<std::string>& instructions,
                  const RegisterValueMap& reg_inits,
                  size_t reg_count,
                  size_t result_reg)
{
    ui.runButton->setEnabled(true);
    ui.stepButton->setEnabled(true);

    result_register = result_reg;
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
    ui.instructionTableWidget->setCurrentCell(next_instruction, 0);

    register_values = registers;
    SetupRegisterTableContentFrom([this](const size_t i)
    {
        return QString::number(register_values[i]);
    }, register_values.size());
}

void MainWindow::EndSimulation()
{
    ui.runButton->setEnabled(false);
    ui.stepButton->setEnabled(false);
}

void MainWindow::InstructionTable_CurrentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if (previous)
    {
        previous->setBackground(Qt::GlobalColor::white);
        previous->setTextColor(Qt::GlobalColor::black);
    }
    ui.instructionTableWidget->scrollToItem(current);
    current->setBackground(Qt::GlobalColor::black);
    current->setTextColor(Qt::GlobalColor::white);
}

void MainWindow::SimulationLoadButtonClicked()
{

    std::wstring filename{ ui.fileNameLineEdit->text().toStdWString() };
    std::string input_str{ ui.inputParamsLineEdit->text().toStdString() };

    CallSafely([&](){
        model.OpenComputation(filename, input_str);
    });
}

void MainWindow::TransformationStartButtonClicked()
{

    std::wstring inputFile{ ui.fileNameLineEdit_2->text().toStdWString() };
    size_t set = ui.group1Selector->isChecked() ? 1 :
    (ui.group2Selector->isChecked() ? 2 : 3);
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    std::wstring outputFile = dialog.getSaveFileName(NULL, "Create New File","","").toStdWString();

    CallSafely([&](){
        model.TransformFile(inputFile, outputFile, set);
    });
}
void MainWindow::StepButtonClicked()
{

    CallSafely([this](){
        model.StepProgram();
    });
}
void MainWindow::RunButtonClicked()
{

    CallSafely([this](){
        model.RunProgram();
    });
}

void MainWindow::SetupInstructionTableContent()
{


    ui.instructionTableWidget->setRowCount(instruction_strings.size());
    ui.instructionTableWidget->setColumnCount(1);

    for (size_t i = 0; i < instruction_strings.size(); ++i)
    {
        auto item = new QTableWidgetItem{ QString::number(i) + ". " + QString::fromStdString(instruction_strings[i]) };
        item->setBackground(Qt::GlobalColor::white);
        item->setTextColor(Qt::GlobalColor::black);
        ui.instructionTableWidget->setItem(i, 0, item);
    }

    ui.instructionTableWidget->setCurrentCell(0, 0);
}

void MainWindow::SetupFileInputConnection(QLineEdit *fileNameBox, QPushButton *browseButton)
{


    connect(browseButton, &QPushButton::released,
    [fileNameBox]()
    {
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::ExistingFile);
        QString outputFile{ dialog.getOpenFileName(NULL, "Open Program","","") };
        fileNameBox->setText(outputFile);
    });
}
