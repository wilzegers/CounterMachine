#pragma once

#include "Utility.h"
#include "Constants.h"

#include <string>

enum class InstructionType
{
	Increase,
	Decrease,
	Clear,
	Copy,
	JumpIfZero,
	JumpIfEqual,
	Halt
};

#define REAL_INSTRUCTION_DESCRIPTOR(Name) \
	CLONEABLE(Name, Instruction) \
	InstructionType GetType() const override \
	{ \
		return InstructionType::Name; \
	} \
	static constexpr InstructionType type_enum = InstructionType::Name; \

namespace Descriptors
{

	struct Instruction
	{

		CLONEABLE_BASE(Instruction)

		virtual InstructionType GetType() const = 0;
		template <class ActualInstruction>
		bool IsA() const
		{
			return ActualInstruction::type_enum == GetType();
		}

		template <class ActualInstruction>
		ViewPtr<const ActualInstruction> const As() const
		{
			if (!IsA<ActualInstruction>())
			{
				throw InternalError("Invalid Instruction cast");
			}
				return static_cast<ViewPtr<const ActualInstruction>>(this);
		}

		template <class ActualInstruction>
		ViewPtr<ActualInstruction> As()
		{
			if (!IsA<ActualInstruction>())
			{
				throw InternalError("Invalid Instruction cast");
			}
			return static_cast<ViewPtr<ActualInstruction>>(this);
		}

		virtual std::string ToString() const = 0;

		bool operator==(const Instruction& other) const
		{
			return this->ToString() == other.ToString();
		}
	};

	struct Increase : public Instruction
	{
		size_t reg_name;
		static constexpr size_t param_no{ 1 };

		Increase(const size_t& reg_name)
			: reg_name{ reg_name }
		{
		}

		REAL_INSTRUCTION_DESCRIPTOR(Increase)

		std::string ToString() const override
		{
			return Constants::Instructions::increase
				+ ("(" + std::to_string(reg_name) + ")");
		}
	};

	struct Decrease : public Instruction
	{
		size_t reg_name;
		static constexpr size_t param_no{ 1 };

		Decrease(const size_t& reg_name)
			: reg_name{ reg_name }
		{
		}

		REAL_INSTRUCTION_DESCRIPTOR(Decrease)

		std::string ToString() const override
		{
			return Constants::Instructions::decrease
				+ ("(" + std::to_string(reg_name) + ")");
		}
	};

	struct Clear : public Instruction
	{	
		size_t reg_name;
		static constexpr size_t param_no{ 1 };
		
		Clear(const size_t& reg_name)
			: reg_name{ reg_name }
		{
		}

		REAL_INSTRUCTION_DESCRIPTOR(Clear)
		
		std::string ToString() const override
		{
			return Constants::Instructions::clear
				+ ("(" + std::to_string(reg_name) + ")");
		}
	};

	struct Copy : public Instruction
	{
		size_t from_register;
		size_t to_register;
		static constexpr size_t param_no{ 2 };

		Copy(const size_t& from_register, const size_t& to_register)
			: from_register{ from_register },
			to_register{ to_register }
		{
		}

		REAL_INSTRUCTION_DESCRIPTOR(Copy)

		std::string ToString() const override
		{
			return Constants::Instructions::copy
				+ ("(" + std::to_string(from_register) + "," + std::to_string(to_register) + ")");
		}
	};

	struct JumpIfZero : public Instruction
	{
		size_t register_name;
		size_t jump_destination;
		static constexpr size_t param_no{ 2 };

		JumpIfZero(const size_t& register_name, const size_t& jump_destination)
			: register_name{ register_name },
			jump_destination{ jump_destination }
		{
		}

		REAL_INSTRUCTION_DESCRIPTOR(JumpIfZero)

		std::string ToString() const override
		{
			return Constants::Instructions::jump_if_zero
				+ ("(" + std::to_string(register_name) + "," + std::to_string(jump_destination) + ")");
		}
	};

	struct JumpIfEqual : public Instruction
	{
		size_t register_a;
		size_t register_b;
		size_t jump_destination;
		static constexpr size_t param_no{ 3 };

		JumpIfEqual(const size_t& register_a, const size_t& register_b, const size_t& jump_destination)
			: register_a{ register_a },
			register_b{ register_b },
			jump_destination{ jump_destination }
		{
		}

		REAL_INSTRUCTION_DESCRIPTOR(JumpIfEqual)

		std::string ToString() const override
		{
			return Constants::Instructions::jump_if_equal
				+ ("(" + std::to_string(register_a) + "," + std::to_string(register_b) + "," + std::to_string(jump_destination) + ")");
		}
	};

	struct Halt : public Instruction
	{
		static constexpr size_t param_no{ 0 };

		REAL_INSTRUCTION_DESCRIPTOR(Halt)

		std::string ToString() const override
		{
			return Constants::Instructions::halt + std::string{ "()" };
		}
	};
}