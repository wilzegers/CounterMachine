#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "Model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void SimulationLoaded(const std::vector<std::string>& instructions,
		       const boost::container::flat_map<size_t, RegisterValue>& reg_inits,
		       size_t reg_count);
    void ChangeSimulationState(size_t next_instruction, const std::vector<RegisterValue>& registers);
    void EndSimulation();
    void InstructionTable_CurrentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private slots:
    void SimulationLoadButtonClicked();
    void TransformationStartButtonClicked();
    void StepButtonClicked();
    void RunButtonClicked();


private:
    void SetupFileInputConnection(QLineEdit* fileNameBox, QPushButton* browseButton);
    void SetupInstructionTableContent();

    template<typename SourceFunT>
    void SetupRegisterTableContentFrom(SourceFunT source_fun, size_t source_size)
    {

	DEBUGFUN();
	ui->registerTableWidget->setRowCount(std::ceil(source_size / 3.0));
	ui->registerTableWidget->setColumnCount(6);
	size_t name_width = ui->registerTableWidget->horizontalHeader()->width()/ 9;
	size_t value_width = name_width * 2;

	for (size_t i = 0; i < 6; i += 2)
	{
	    ui->registerTableWidget->setColumnWidth(i, name_width);
	    ui->registerTableWidget->setColumnWidth(i + 1, value_width);
	}
	for(size_t i = 0; i < source_size; ++i)
	{
	    auto name = new QTableWidgetItem{ QString::number(i) };
	    name->setBackground(Qt::GlobalColor::lightGray);
	    auto value = new QTableWidgetItem{ source_fun(i) };
	    ui->registerTableWidget->setItem(i / 3, (i % 3) * 2, name);
	    ui->registerTableWidget->setItem(i / 3, (i % 3) * 2 + 1, value);
	}
    }

    template <typename Function>
    void CallSafely(Function fun)
    {
	try
	{
	    fun();
	}
	catch(std::exception& e)
	{
	    const char* s = e.what();
	    QString message = s;
	    QMessageBox messageBox;
	    messageBox.setIcon(QMessageBox::Critical);
	    messageBox.setText(message);
	    messageBox.exec();

	    model.Clear();
	    instruction_strings.clear();
	    register_values.clear();
	    EndSimulation();
	}
    }

    std::unique_ptr<Ui::MainWindow> ui;

    std::vector<std::string> instruction_strings;
    std::vector<RegisterValue> register_values;

    Model model;
};

#endif // MAINWINDOW_H
