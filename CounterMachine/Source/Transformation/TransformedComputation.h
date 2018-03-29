#pragma once

#include <algorithm>
#include <vector>

#include "BoostIncludes.h"

#include "Descriptors/Computation.h"


namespace Transformation
{
    /// Segédosztály az átírási szabályokhoz.
    /**
    * Az osztály egy olyan regiszterként funkcionál, ami addig van használatban, amíg a
    * RegisterReference objektum életben van. Amikor az megsemmisül, az regiszter visszakerül
    * a szabadon használhatóak közé.
    */
    struct RegisterReference
    {
        /// Az újra használhatóságról gondoskodó destruktor.
        ~RegisterReference();

        /// Automatikus konverzió a regiszter címére.
        operator RegisterName() const;

        /// Az osztály nem másolható.
        RegisterReference(const RegisterReference&) = delete;
        
        /// Move konstruktor.
        /**
        * \param other a forrásobjektum.
        */
        RegisterReference(RegisterReference&& other);

        /// Konstruktor.
        /**
        * \param free_custom_registers a regiszter-konténer, amelybe visszahelyezendő a cím.
        */
        RegisterReference(std::vector<RegisterName>& free_custom_registers);

    private:
        RegisterName reg_name; ///< A regiszter címe.
        bool to_unreg{ true }; ///< Igaz, ha megsemmisüléskor használhatóvá kell tenni a regisztert.
        std::vector<RegisterName>& free_helper_registers; ///< A regiszterkonténer-referencia, amelybe visszahelyezendő a cím.
    };

    /// A transzformáláshoz használt számlálógép osztály.
    struct TransformedComputation
    {
        /// Getter az utasítás-leírók vektorához.
        /**
        * \return Referencia az utasítás-leírók vektorára.
        */
        Descriptors::InstructionVector& GetInstructions();

        /// Getter az utasítás-leírók konstans vektorához.
        /**
        * \return Konstans referencia az utasítás-leírók vektorára.
        */
        const Descriptors::InstructionVector& GetInstructions() const;

        /// Üres konstruktor.
        TransformedComputation() = default;

        /// Másoló konstruktor.
        TransformedComputation(const Descriptors::Computation& descriptor);

        /// Move értékadás operátor.
        TransformedComputation& operator=(TransformedComputation&& other);

        /// Move konstruktor.
        TransformedComputation(TransformedComputation&& other);

        /// Regiszterek lemásolása másik objektumtól.
        void ReadRegistersFrom(const TransformedComputation& other);

        /// Regiszterek számának a lekérése.
        /**
        * \return A jelenleg használt regiszterek száma.
        */
        size_t GetRegisterCount() const;

        /// Egy jelenleg nem használt segédregiszter lekérése.
        /**
        * \return Regiszterként funkcionáló objektum, amely megsemmisüléskor újra használaton kívülinek állítja magát.
        */
        RegisterReference RequestHelperRegister();

        /// A konstans 0 értékű regiszter lekérése.
        /**
        * \return a konstans 0 regiszter címe.
        */
        RegisterName RequestZeroRegister();

        /// Utasítás hozzáadása.
        /**
        * \param instr senki által nem birtokolt utasítás-mutató.
        */
        template<typename InstructionType>
        void Add(InstructionType* instr)
        {
            ++currently_added_lines;
            instructions.push_back(std::unique_ptr<InstructionType>(instr));
        }

        /// Már az átalakítás előtt is létező ugrás hozzáadása.
        /**
        * \param instr senki által nem birtokolt ugrásutasítás-mutató.
        */
        template<typename InstructionType>
        void AddOuterJump(InstructionType* instr)
        {
            jumps_to_update.push_back(instructions.size());
            Add<InstructionType>(instr);
        }

        /// Szabály elejét jelző metódus, a soreltolódások jegyzését kezdi el.
        void StartRule();

        /// Szabály végét jelző metódus, regisztrálja a történt soreltolódásokat.
        void EndRule();

        /// Átalakításra nem szoruló utasítás hozzáadása.
        /**
        * \param instr utasítás-mutató.
        */
        void SkipInstruction(std::unique_ptr<Descriptors::Instruction>&& instr);

        /// A teljes utasítássorozat átalakításának végét jelző metódus, frissíti az ugrások célját.
        void FinishedTransformationIteration();

    private:

        /// Egy ugrás-célpont frissítése.
        /**
        * \param jump_destination az ugrás célpontjára referencia.
        */
        void UpdateJumpDestination(size_t& jump_destination) const;

        Descriptors::InstructionVector instructions; ///< A számlálógép utasítássorozat-leírója.
        std::vector<RegisterName> free_helper_registers; ///< A jelenleg szabad segédregiszterek.
        size_t register_count; ///< Az összes regiszter száma.
        bool has_zero_register; ///< Igaz, ha a számlálógépnek már van dedikált nullregisztere.
        RegisterName zero_register_name; ///< A nullregiszter címe.
        std::vector<size_t> new_line_locations{ { 0 } }; ///< A vector i. eleme az i-re mutató ugrások új célpontja lesz.
        std::vector<size_t> jumps_to_update; ///< A frissítendő ugrások sorszáma.
        size_t currently_added_lines{ 0 }; ///< A jelenlegi utasítás helyett hozzáadott utasítás-szám.
        RegisterName result_reg; ///< A végeredményt tartalmazó regiszter címe.
    };

    /// Segédosztály az átírási szabályokhoz.
    /**
    * Az osztály azért felelős, hogy a referenciaként eltárolt TransformedComputation objektum
    * StartRule() metódusát konstruáláskor, Endrule() metódusát pedig destruáláskor automatikusan meghívja.
    */
    struct RuleGuard
    {
        /// A konstruktor felelős a szabály elkezdéséért.
        /**
        * \param comp a jelenleg átírás alatt álló számlálógép.
        */
        RuleGuard(TransformedComputation& comp);

        /// A konstruktor felelős a szabály befejezéséért.
        ~RuleGuard();
    private:
        TransformedComputation& comp; ///< A jelenleg átírás alatt álló számlálógép.
    };
}
