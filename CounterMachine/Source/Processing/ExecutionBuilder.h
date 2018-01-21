#pragma once

#include "BoostIncludes.h"

#include "Descriptors/Computation.h"
#include "Descriptors/Instruction.h"
#include "Exceptions.h"

namespace Processing
{

	class ExecutionBuilder
	{
		size_t reg_count;
		size_t result_reg;
		boost::container::flat_set<size_t> input_regs;
		boost::container::flat_map<size_t, RegisterValue> register_inits;
		std::vector<std::unique_ptr<Descriptors::Instruction>> instructions;
		std::function<LocationInfo()> location_request;

	public:

		ExecutionBuilder(std::function<LocationInfo()> location_request);

		Descriptors::Computation CreateComputation();

		void ActOnRegisterCount(size_t register_count);

		void ActOnInputReg(size_t reg_name);

		void ActOnOutputRegisterName(size_t result_register);

		void ActOnInitPair(size_t register_name, RegisterValue init_value);

		void ActOnInstruction(const std::string& instruction_name, const std::vector<size_t>& arguments);

	private:

		void EnsureRegisterUniqueness(size_t register_name) const;

		template<class Instruction>
		void CreateInstruction(const std::string& instruction_name, const std::vector<size_t>& arguments)
		{
			if (arguments.size() == Instruction::param_no)
			{
				CreateInstructionImpl<Instruction::param_no, Instruction>::Call(*this, arguments);
			}
			else
			{
				throw ExceptionWithLocation(location_request(), Constants::ErrorMessages::argument_error,
					instruction_name, Instruction::param_no, arguments.size());
			}
		}


		template<size_t param_count, class Instruction>
		struct CreateInstructionImpl
		{
		};


		template<class Instruction>
		struct CreateInstructionImpl<0, Instruction>
		{
			static void Call(ExecutionBuilder& builder, const std::vector<size_t>& /*parameters*/)
			{
				builder.AddInstruction<Instruction>();
			}
		};


		template<class Instruction>
		struct CreateInstructionImpl<1, Instruction>
		{
			static void Call(ExecutionBuilder& builder, const std::vector<size_t>& parameters)
			{
				builder.AddInstruction<Instruction>(parameters[0]);
			}
		};


		template<class Instruction>
		struct CreateInstructionImpl<2, Instruction>
		{
			static void Call(ExecutionBuilder& builder, const std::vector<size_t>& parameters)
			{
				builder.AddInstruction<Instruction>(parameters[0], parameters[1]);
			}
		};


		template<class Instruction>
		struct CreateInstructionImpl<3, Instruction>
		{
			static void Call(ExecutionBuilder& builder, const std::vector<size_t>& parameters)
			{
				builder.AddInstruction<Instruction>(parameters[0], parameters[1], parameters[2]);
			}
		};


		template<class Instruction, class... Args>
		void AddInstruction(Args...args)
		{
			instructions.push_back(std::make_unique<Instruction>(args...));
		}
	};

}