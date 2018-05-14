#include "ComputationHolder.h"

#include <sstream>

#include <QFile>
#include <QString>
#include <QTextStream>

#include "Processing/Parser.h"
#include "Processing/InputParser.h"

ComputationHolder::ComputationHolder(const QString& filename, const std::string& input_str)
    : comp_descriptor{CreateDescriptor(filename)},
      comp{comp_descriptor, ParseInputs(input_str)}
{
}

Descriptors::Computation ComputationHolder::CreateDescriptor(const QString& filename)
{
    QFile input{filename};
    input.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!input.isOpen())
    {
            throw std::runtime_error{"Error while opening file"};
    }
    auto input_string = QTextStream{&input}.readAll().toStdString();
    Processing::Parser parser{std::make_unique<std::stringstream>(input_string)};
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
