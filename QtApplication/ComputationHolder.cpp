#include "ComputationHolder.h"

#include "Processing/Parser.h"
#include "Processing/ArgParser.h"

ComputationHolder::ComputationHolder(const std::wstring& filename, const std::string& input_str)
    : comp_descriptor{CreateDescriptor(filename)},
      comp{comp_descriptor, ParseInputs(input_str)}
{
    DEBUGFUN();
}

Descriptors::Computation ComputationHolder::CreateDescriptor(const std::wstring& filename)
{
    DEBUGFUN();
    Processing::Parser parser{filename};
    parser.Parse();
    return parser.GetResultComputation();
}

boost::container::flat_map<size_t, RegisterValue> ComputationHolder::ParseInputs(const std::string& input_str)
{
    DEBUGFUN();
    Processing::ArgParser arg_parser{input_str};
    arg_parser.Parse();
    auto result = arg_parser.GetInits();
    return result;
}

const Descriptors::Computation& ComputationHolder::GetComputationDescriptor()
{
    DEBUGFUN();
    return comp_descriptor;
}
