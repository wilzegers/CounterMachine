#include "Model.h"

#include <algorithm>

#include "Transformation/MachineTransformer.h"
#include "Processing/Parser.h"

void Model::OpenComputation(const std::wstring& filename, const std::string& input_str)
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

void Model::TransformFile(const std::wstring& input_file, const std::wstring& output_file, size_t to_set)
{
    Processing::Parser p{input_file};
    p.Parse();
    std::ofstream{output_file} << Transformation::MachineTransformer{}.Transform(to_set, p.GetResultComputation());
}

void Model::Clear()
{
    comp_holder = boost::none;
}
