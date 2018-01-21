#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include <vector>
#include <string>

#include "ComputationHolder.h"

class Model : public QObject
{
    Q_OBJECT
public:
    Model();

public slots:
    void OpenFile(const std::wstring& filename, const std::string& input_str);
    void StepProgram();
    void RunProgram();
    void TransformFile(const std::wstring& inputFile, const std::wstring& outputFile, size_t to_set);
    void Clear();

signals:
    void ProgramLoaded(const std::vector<std::string>& instructions,
		       const RegisterValueMap& reg_inits,
		       size_t reg_count);

    void StateChanged(size_t next_instruction, const std::vector<RegisterValue>& registers);

    void SimulationEnded();

private:
    std::vector<std::string> instructions;
    std::unique_ptr<ComputationHolder> comp_holder;
    size_t current_instr;
};

#endif // MODEL_H
