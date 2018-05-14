#include "Model.h"

#include <algorithm>

#include <QFile>
#include <QTextStream>
#include <QString>

#include "Transformation/MachineTransformer.h"
#include "Processing/Parser.h"

template<typename T>
QTextStream& operator<<(QTextStream& s, T&& t)
{
    std::stringstream ss;
    ss << t;
    return s << ss.str().data();
}

void Model::OpenComputation(const QString& filename, const std::string& input_str)
{
    comp_holder.emplace(filename, input_str);
    const auto& comp_desc = comp_holder->GetComputationDescriptor();

    std::vector<std::string> instructions;
    boost::range::transform(comp_desc.instructions, std::back_inserter(instructions),
        [](auto& instr){return instr->ToString();}
    );

    emit ProgramLoaded(instructions, comp_desc.register_inits,
                       comp_desc.register_count, comp_desc.result_reg);
}

void Model::StepProgram()
{
    if(!comp_holder)
        return;

    comp_holder->StepProgramWith([this](const Execution::State& state)
    {
        emit StateChanged(state.GetNextInstruction(), state.GetRegisterValues());
        if (state.IsDone())
        {
            emit SimulationEnded();
        }
    });
}

void Model::RunProgram()
{
    if(!comp_holder)
        return;

    comp_holder->RunProgramWith([this](const Execution::State& state)
    {
        emit StateChanged(state.GetNextInstruction(), state.GetRegisterValues());
    });
    emit SimulationEnded();
}

void Model::TransformFile(const QString& input_file, const QString& output_file, size_t to_set)
{
    QFile input{input_file};
    input.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!input.isOpen())
    {
            throw std::runtime_error("Error while opening file");
    }
    auto input_string = QTextStream{&input}.readAll().toStdString();
    Processing::Parser p{ std::make_unique<std::stringstream>(input_string) };
    p.Parse();
    QFile output(output_file);
    input.close();
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!output.isOpen())
    {
            throw std::runtime_error{"Error while writing file"};
    }
    QTextStream stream(&output);
    stream << Transformation::MachineTransformer{}.Transform(to_set, p.GetResultComputation());
}

void Model::Clear()
{
    comp_holder = boost::none;
}
