#ifndef MACHINELOGIC_H
#define MACHINELOGIC_H

#include "BoostIncludes.h"
#include "Utility.h"

#include "Execution/Computation.h"

#include <iostream>

#define DEBUGFUN() DebugHelper __helper{__FUNCTION__}

struct DebugHelper
{
    const char* str;

    size_t& GetIndent()
    {
	static size_t i = 0;
	return i;
    }

    DebugHelper(const char* str) : str{ str }
    {
	std::cerr << std::string(GetIndent() * 2, ' ') << str << "{\n";
	++GetIndent();
    }

    ~DebugHelper()
    {
	--GetIndent();
	std::cerr << std::string(GetIndent() * 2, ' ') << "}\n";
    }
};


class ComputationHolder
{
public:
    ComputationHolder(const std::wstring& filename, const std::string& input_str);
    const Descriptors::Computation& GetComputationDescriptor();

    template<typename Func>
    void ComputationHolder::StepProgramWith(Func func)
    {
	DEBUGFUN();
	comp.StepWith(func);
    }

    template<typename Func>
    void ComputationHolder::RunProgramWith(Func func)
    {
	DEBUGFUN();
	comp.RunWith(func);
    }

private:
    Descriptors::Computation CreateDescriptor(const std::wstring& filename);
    RegisterValueMap ParseInputs(const std::string& input_str);

    Descriptors::Computation comp_descriptor;
    Execution::Computation comp;
};

#endif // MACHINELOGIC_H
