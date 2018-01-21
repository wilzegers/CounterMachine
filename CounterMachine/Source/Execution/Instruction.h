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

		size_t register_name;
	public:

		Increase(size_t register_name) : register_name{ register_name }
		{
		}

		virtual void ChangeRegisters(State& state) override
		{
			++state.GetRegisterValue(register_name);
		}
	};

	class Decrease : public Instruction
	{

		size_t register_name;
	public:

		Decrease(size_t register_name) : register_name{ register_name }
		{
		}

		virtual void ChangeRegisters(State& state) override
		{
			--state.GetRegisterValue(register_name);
		}
	};

	class Clear : public Instruction
	{

		size_t register_name;
	public:

		Clear(size_t register_name) : register_name{ register_name }
		{
		}

		virtual void ChangeRegisters(State& state) override
		{
			state.GetRegisterValue(register_name) = 0;
		}
	};

	class Copy : public Instruction
	{

		size_t from_register;
		size_t to_register;
	public:

		Copy(size_t from_register, size_t to_register) : from_register{ from_register }, to_register{ to_register }
		{
		}

		virtual void ChangeRegisters(State& state) override
		{
			state.GetRegisterValue(to_register) = state.GetRegisterValue(from_register);
		}
	};

	class JumpIfZero : public Instruction
	{

		size_t register_name;
		size_t jump_destination;
	public:

		JumpIfZero(size_t register_name, size_t jump_destination) : register_name{ register_name }, jump_destination{ jump_destination }
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

		size_t register_a;
		size_t register_b;
		size_t jump_destination;
	public:

		JumpIfEqual(size_t register_a, size_t register_b, size_t jump_destination)
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