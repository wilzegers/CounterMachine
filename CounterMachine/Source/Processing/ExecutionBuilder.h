#pragma once

#include "BoostIncludes.h"

#include "Descriptors/Computation.h"
#include "Descriptors/Instruction.h"
#include "Exceptions.h"

namespace Processing
{

    /// A számlálógép-leíró építéséért felelős osztály.
    struct ComputationBuilder
    {

        /// Konstruktor.
        /**
        * \param location_request a jelenlegi helyzet lekérése a parsertől.
        */
        ComputationBuilder(std::function<LocationInfo()> location_request);

        /// A számlálógép-leíró készítése.
        /**
        * \return A számlálógép-leíró.
        */
        Descriptors::Computation CreateComputation();

        /// A regiszterszámra reakció.
        /**
        * \param register_count a regiszterszám.
        */
        void ActOnRegisterCount(size_t register_count);

        /// Bemeneti regiszterre reakció.
        /**
        * \param reg_name a regiszter neve.
        */
        void ActOnInputReg(RegisterName reg_name);

        /// A kimeneti regiszterre reakció.
        /**
        * \param result_register a regiszter neve.
        */
        void ActOnOutputRegisterName(RegisterName result_register);

        /// Reakció regiszter inicializációs értékére.
        /**
        * \param reg_name a regiszter neve.
        * \param init_value a regiszter kezdeti értéke.
        */
        void ActOnInitPair(RegisterName register_name, RegisterValue init_value);

        /// Reakció utasításra.
        /**
        * \param instruction_name az utasítás neve.
        * \param init_value arguments az argumentumok.
        */
        void ActOnInstruction(const std::string& instruction_name, const std::vector<size_t>& arguments);

    private:

        /// Regiszter-egyediség ellenőrzés.
        /**
        * \param register_name a regiszter neve.
        */
        void EnsureRegisterUniqueness(RegisterName register_name) const;

        /// Utasítás-leíró elkészítése.
        /**
        * \tparam Instruction az utasítás-leíró típusa.
        * \param instruction_name az utasítás neve.
        * \param init_value arguments az argumentumok.
        */
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

        /// Segédosztály az utasítás-leírók elkészítéséhez.
        /**
        * \tparam param_count az utasítás paramétereinek a száma.
        * \tparam Instruction az utasítás-leíró típusa.
        */
        template<size_t param_count, class Instruction>
        struct CreateInstructionImpl
        {
        };


        template<class Instruction>
        struct CreateInstructionImpl<0, Instruction>
        {
            static void Call(ComputationBuilder& builder, const std::vector<size_t>& /*parameters*/)
            {
                builder.AddInstruction<Instruction>();
            }
        };


        template<class Instruction>
        struct CreateInstructionImpl<1, Instruction>
        {
            static void Call(ComputationBuilder& builder, const std::vector<size_t>& parameters)
            {
                builder.AddInstruction<Instruction>(parameters[0]);
            }
        };


        template<class Instruction>
        struct CreateInstructionImpl<2, Instruction>
        {
            static void Call(ComputationBuilder& builder, const std::vector<size_t>& parameters)
            {
                builder.AddInstruction<Instruction>(parameters[0], parameters[1]);
            }
        };


        template<class Instruction>
        struct CreateInstructionImpl<3, Instruction>
        {
            static void Call(ComputationBuilder& builder, const std::vector<size_t>& parameters)
            {
                builder.AddInstruction<Instruction>(parameters[0], parameters[1], parameters[2]);
            }
        };

        /// Segédfüggvény egy utasításleíró hozzáadásához az eddigiekhez.
        /**
        * \tparam Instruction az utasítás-leíró típusa.
        * \param args az utasítás-leíró argumentumai.
        */
        template<class Instruction, class... Args>
        void AddInstruction(Args...args)
        {
            instructions.push_back(std::make_unique<Instruction>(args...));
        }

        size_t reg_count; ///< a regiszterek száma.

        RegisterName result_reg; ///< a kimeneti regiszter.

        RegisterNameSet input_regs; ///< a bemeneti regiszterek.

        RegisterValueMap register_inits; ///< a regiszterek kezdeti értékei.

        Descriptors::InstructionVector instructions; ///< az utasításleírok vektora.

        std::function<LocationInfo()> location_request; ///< a jelenlegi helyzet lekérése a tartalmazó parsertől.
    };
}