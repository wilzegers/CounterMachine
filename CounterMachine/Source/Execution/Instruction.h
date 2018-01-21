#pragma once

#include "Execution/State.h"
#include "Constants.h"

#include "Descriptors/Instruction.h"

namespace Execution
{

	class Instruction
	{
	public:
		void Execute(State& state)
		{
			ChangeRegisters(state);
			ToNextInstruction(state);
		}

		virtual void ChangeRegisters(State&/* state*/) {}

		virtual void ToNextInstruction(State& state)
		{
			++state.GetNextInstruction();
		}
	};



	class Increase : public Instruction
	{

		RegisterName register_name;
	public:

		Increase(RegisterName register_name) : register_name{ register_name }
		{
		}

		virtual void ChangeRegisters(State& state) override
		{
			++state.GetRegisterValue(register_name);
		}
	};

	class Decrease : public Instruction
	{

		RegisterName register_name;
	public:

		Decrease(RegisterName register_name) : register_name{ register_name }
		{
		}

		virtual void ChangeRegisters(State& state) override
		{
			--state.GetRegisterValue(register_name);
		}
	};

	class Clear : public Instruction
	{

		RegisterName register_name;
	public:

		Clear(RegisterName register_name) : register_name{ register_name }
		{
		}

		virtual void ChangeRegisters(State& state) override
		{
			state.GetRegisterValue(register_name) = 0;
		}
	};

	class Copy : public Instruction
	{

		RegisterName from_register;
		RegisterName to_register;
	public:

		Copy(RegisterName from_register, RegisterName to_register) : from_register{ from_register }, to_register{ to_register }
		{
		}

		virtual void ChangeRegisters(State& state) override
		{
			state.GetRegisterValue(to_register) = state.GetRegisterValue(from_register);
		}
	};

	class JumpIfZero : public Instruction
	{

		RegisterName register_name;
		size_t jump_destination;
	public:

		JumpIfZero(RegisterName register_name, size_t jump_destination) : register_name{ register_name }, jump_destination{ jump_destination }
		{
		}

		virtual void ToNextInstruction(State& state) override
		{
			if (state.GetRegisterValue(register_name) == 0)
			{
				state.GetNextInstruction() = jump_destination;
			}
			else
			{
				Instruction::ToNextInstruction(state);
			}
		}
	};

	class JumpIfEqual : public Instruction
	{

		RegisterName register_a;
		RegisterName register_b;
		size_t jump_destination;
	public:

		JumpIfEqual(RegisterName register_a, RegisterName register_b, size_t jump_destination)
			: register_a{ register_a }, register_b{ register_b }, jump_destination{ jump_destination }
		{
		}

		virtual void ToNextInstruction(State& state) override
		{
			if (state.GetRegisterValue(register_a) == state.GetRegisterValue(register_b))
			{
				state.GetNextInstruction() = jump_destination;
			}
			else
			{
				Instruction::ToNextInstruction(state);
			}
		}
	};


	class Halt : public Instruction
	{

	public:

		Halt() {}

		virtual void ToNextInstruction(State& state) override
		{
			state.Halt();
		}
	};

}