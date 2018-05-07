#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include <vector>
#include <string>

#include "ComputationHolder.h"

/// A QT alkalmazás model objektuma. Minden logikai művelet ebben az osztályban történik.
struct Model : public QObject
{
public slots:
    /// A számlálógép megnyitását végző objektum.
    /**
     * \param filename a számlálógépet leíró fájl neve.
     * \param input_str a bemeneti paraméterek szövege.
    */
    void OpenComputation(const std::wstring& filename, const std::string& input_str);

    /// A következő utasítás végrehajtása.
    void StepProgram();

    /// A számlálógép futtatása.
    void RunProgram();

    /// A számlálógépet leíró fájl átalakítása másik fájlba.
    /**
     * \param input_file az átalakítandó számlálógépet leíró fájl neve.
     * \param output_file az átalakítás eredményeként kapott fájl neve.
     * \param to_set a célhalmaz.
     */
    void TransformFile(const std::wstring& input_file, const std::wstring& output_file, size_t to_set);

    /// A model kiürítése.
    void Clear();

signals:

    /// Jel arról, hogy a számlálógép betöltésre került.
    /**
     * \param instructions az utasítások megjelenítendő szövege.
     * \param reg_inits a fix regiszterek kezdőértéke.
     * \param reg_count az összes regiszterszám.
     * \param result_register az eredményt tartalmazó regisztercím.
     */
    void ProgramLoaded(const std::vector<std::string>& instructions,
                       const RegisterValueMap& reg_inits,
                       size_t reg_count, size_t result_register);

    /// Jel arról, hogy a számlálógép állapota változott.
    /**
     * \param next_instruction a következő utasítás sorszáma.
     * \param registers a frissített regiszterértékek.
     */
    void StateChanged(size_t next_instruction, const std::vector<RegisterValue>& registers);

    /// A számlálógép-szimuláció végét jelző jel.
    void SimulationEnded();

private:
    Q_OBJECT

    boost::optional<ComputationHolder> comp_holder; ///< A számlálógépet kezelő objektum.
};

#endif // MODEL_H
