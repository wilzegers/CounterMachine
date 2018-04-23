#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "Model.h"
#include "ui_MainWindow.h"

/// A QT applikáció nézet objektuma. Ez felelős a model és a
/// felhasználó közti kommunikációért //TODO: [citation needed]
struct MainWindow : public QMainWindow
{
    explicit MainWindow(QWidget *parent = 0);

public slots:

    /// A számlálógép betöltésekor végrehajtandó metódus. Felépíti a szimuláció
    /// megjelenítését, és elérhetővé teszi a futtatással kapcsolatos gombokat.
    /**
     * \param instructions az utasítások megjelenítendő szövege.
     * \param reg_inits a fix regiszterek kezdőértéke
     * \param reg_count az összes regiszterszám.
     * \param result_reg az eredményt tartalmazó regiszter címe.
     */
    void SimulationLoaded(const std::vector<std::string>& instructions,
                       const RegisterValueMap& reg_inits, size_t reg_count, size_t result_reg);

    /// A számlálógép állapot-változásakor végrehajtandó metódus.
    /// Frissíti a szimuláció megjelenítését.
    /**
     * \param next_instruction a következő utasítás sorszáma.
     * \param registers a frissített regiszterértékek.
     */
    void ChangeSimulationState(size_t next_instruction, const std::vector<RegisterValue>& registers);

    /// A számlálógép-szimuláció végekor végrehajtandó metódus.
    /// Kikapcsolja a szimulációval kapcsolatos gombokat.
    void EndSimulation();

    /// A jelenlegi utasítás frissítésekor végrehajtandó metódus. Beállítja a jelenlegi
    /// utasítás cellájának a kinézetét.
    /**
     * \param current mutató a jelenlegi utasításra.
     * \param previous mutató az előző utasításra.
     */
    void InstructionTable_CurrentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private slots:
    /// A Load gombra kattintáskor végrehajtandó metódus. A modellel
    /// betölteti a megadott számlálógépet.
    void SimulationLoadButtonClicked();

    /// A Transform gombra kattintskor végrehajtandó metódus. A modellel
    /// elvégezteti a számlálógép-átalakítást.
    void TransformationStartButtonClicked();

    /// A Step gombra kattintáskor végrehajtandó metódus. A modellel
    /// léptet egyet a számlálógépen.
    void StepButtonClicked();

    /// A Run gombra kattintáskor végrehajtandó metódus. A modellel
    /// befejezteti a számlálógép futását.
    void RunButtonClicked();


private:
    Q_OBJECT

    /// Fájlbekérő UI-elemek összekapcsolása. A gomb megnyomásával a számítógép
    /// fájlrendszerét böngészve kiválaszthatunk egy fájlt, aminek az elérési útjával
    /// automatikusan feltöltődik a szövegdoboz.
    /**
     * \param fileNameBox a file elérési útját tartalmazó szövegdoboz mutatója.
     * \param browseButton a fileböngészést elindító gomb.
     */
    void SetupFileInputConnection(QLineEdit* fileNameBox, QPushButton* browseButton);

    /// Az utasításokat tartalmazó táblázat feltöltése.
    void SetupInstructionTableContent();

    /// A regiszterértékek feltöltése, vagy felülírása.
    /**
     * \tparam SourceFunT QString(size_t)-ként viselkedő hívható típus.
     * \param source_fun a regiszterértékek forrásául szolgáló funktor.
     * \param source_size a kapott regiszterértékek száma.
     */
    template<typename SourceFunT>
    void SetupRegisterTableContentFrom(SourceFunT source_fun, int source_size)
    {
        ui.registerTableWidget->setRowCount(std::ceil(source_size / 3.0));
        ui.registerTableWidget->setColumnCount(6);
        auto name_width = ui.registerTableWidget->horizontalHeader()->width()/ 9;
        auto value_width = name_width * 2;

        for (auto i = 0; i < 6; i += 2)
        {
            ui.registerTableWidget->setColumnWidth(i, name_width);
            ui.registerTableWidget->setColumnWidth(i + 1, value_width);
        }

        for(auto i = 0; i < source_size; ++i)
        {
            auto name = new QTableWidgetItem{ QString::number(i) };
            name->setBackground(Qt::GlobalColor::lightGray);
            auto value = new QTableWidgetItem{ source_fun(i) };
            ui.registerTableWidget->setItem(i / 3, (i % 3) * 2, name);
            ui.registerTableWidget->setItem(i / 3, (i % 3) * 2 + 1, value);
        }
        ui.registerTableWidget->item(result_register / 3, (result_register % 3) * 2)
                ->setBackground(Qt::GlobalColor::darkGray);
    }

    /// Hibajelentéses függvényhívás.
    /** Ha a paraméterként megkapott hívható obbjektum
     * hívásakor hiba történik, az felugró ablakban jelenik meg,
     * majd leáll a szimuláció.
     * \tparam paraméterek nélkül hívható típus.
     * \param fun a meghívandó hívható objektum.
     */
    template <typename Function>
    void CallSafely(Function fun)
    {
        try
        {
            fun();
        }
        catch(std::exception& e)
        {
            QMessageBox::critical(this, "Error", e.what());

            model.Clear();
            instruction_strings.clear();
            register_values.clear();
            EndSimulation();
        }
    }

    Ui::MainWindow ui;

    std::vector<std::string> instruction_strings; ///< A szimulált utasítás-sorozat szövegesen.
    std::vector<RegisterValue> register_values; ///< A szimuláció regiszter-értékei.
    size_t result_register;

    Model model; ///< A model objektum.
};

#endif // MAINWINDOW_H
