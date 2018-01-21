#include "Model.h"

#include <algorithm>

#include "Transformation/MachineTransformer.h"
#include "Processing/Parser.h"

Model::Model()
{
    DEBUGFUN();
}

void Model::OpenFile(const std::wstring& filename, const std::string& input_str)
{
    DEBUGFUN();
    comp_holder = std::make_unique<ComputationHolder>(filename, input_str);
    const auto& comp_desc = comp_holder->GetComputationDescriptor();
    instructions.clear();
    instructions.reserve(comp_desc.instructions.size());
    for(const auto& instr : comp_desc.instructions)
    {
	instructions.push_back(instr->ToString());
    }

    emit ProgramLoaded(instructions, comp_desc.register_inits, comp_desc.register_count);
}

void Model::StepProgram()
{
    DEBUGFUN();
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
    DEBUGFUN();
    if(!comp_holder)
	return;

    comp_holder->RunProgramWith([this](const Execution::State& state)
    {
	emit StateChanged(state.GetNextInstruction(), state.GetRegisterValues());
    });
    emit SimulationEnded();
}

void Model::TransformFile(const std::wstring& inputFile, const std::wstring& outputFile, size_t to_set)
{
    DEBUGFUN();
    Processing::Parser p{inputFile};
    p.Parse();
    std::ofstream(outputFile) << Transformation::MachineTransformer().Transform(to_set, p.GetResultComputation());
}

void Model::Clear()
{
    DEBUGFUN();
    instructions.clear();
    comp_holder.release();
    current_instr = 0;
}
