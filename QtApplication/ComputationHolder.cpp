#include "ComputationHolder.h"

#include "Processing/Parser.h"
#include "Processing/InputParser.h"

ComputationHolder::ComputationHolder(const std::wstring& filename, const std::string& input_str)
    : comp_descriptor{CreateDescriptor(filename)},
      comp{comp_descriptor, ParseInputs(input_str)}
{
}

Descriptors::Computation ComputationHolder::CreateDescriptor(const std::wstring& filename)
{
    Processing::Parser parser{filename};
    parser.Parse();
    return parser.GetResultComputation();
}

RegisterValueMap ComputationHolder::ParseInputs(const std::string& input_str)
{
    Processing::InputParser input_parser{input_str};
    input_parser.Parse();
    return input_parser.GetInits();
}

const Descriptors::Computation& ComputationHolder::GetComputationDescriptor()
{
    return comp_descriptor;
}
