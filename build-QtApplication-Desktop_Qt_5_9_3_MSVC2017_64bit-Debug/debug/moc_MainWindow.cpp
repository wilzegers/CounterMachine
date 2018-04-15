/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtApplication/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[368];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "SimulationLoaded"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(4, 54, 12), // "instructions"
QT_MOC_LITERAL(5, 67, 16), // "RegisterValueMap"
QT_MOC_LITERAL(6, 84, 9), // "reg_inits"
QT_MOC_LITERAL(7, 94, 6), // "size_t"
QT_MOC_LITERAL(8, 101, 9), // "reg_count"
QT_MOC_LITERAL(9, 111, 21), // "ChangeSimulationState"
QT_MOC_LITERAL(10, 133, 16), // "next_instruction"
QT_MOC_LITERAL(11, 150, 26), // "std::vector<RegisterValue>"
QT_MOC_LITERAL(12, 177, 9), // "registers"
QT_MOC_LITERAL(13, 187, 13), // "EndSimulation"
QT_MOC_LITERAL(14, 201, 35), // "InstructionTable_CurrentItemC..."
QT_MOC_LITERAL(15, 237, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(16, 255, 7), // "current"
QT_MOC_LITERAL(17, 263, 8), // "previous"
QT_MOC_LITERAL(18, 272, 27), // "SimulationLoadButtonClicked"
QT_MOC_LITERAL(19, 300, 32), // "TransformationStartButtonClicked"
QT_MOC_LITERAL(20, 333, 17), // "StepButtonClicked"
QT_MOC_LITERAL(21, 351, 16) // "RunButtonClicked"

    },
    "MainWindow\0SimulationLoaded\0\0"
    "std::vector<std::string>\0instructions\0"
    "RegisterValueMap\0reg_inits\0size_t\0"
    "reg_count\0ChangeSimulationState\0"
    "next_instruction\0std::vector<RegisterValue>\0"
    "registers\0EndSimulation\0"
    "InstructionTable_CurrentItemChanged\0"
    "QTableWidgetItem*\0current\0previous\0"
    "SimulationLoadButtonClicked\0"
    "TransformationStartButtonClicked\0"
    "StepButtonClicked\0RunButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x0a /* Public */,
       9,    2,   61,    2, 0x0a /* Public */,
      13,    0,   66,    2, 0x0a /* Public */,
      14,    2,   67,    2, 0x0a /* Public */,
      18,    0,   72,    2, 0x08 /* Private */,
      19,    0,   73,    2, 0x08 /* Private */,
      20,    0,   74,    2, 0x08 /* Private */,
      21,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 11,   10,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,   16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SimulationLoaded((*reinterpret_cast< const std::vector<std::string>(*)>(_a[1])),(*reinterpret_cast< const RegisterValueMap(*)>(_a[2])),(*reinterpret_cast< size_t(*)>(_a[3]))); break;
        case 1: _t->ChangeSimulationState((*reinterpret_cast< size_t(*)>(_a[1])),(*reinterpret_cast< const std::vector<RegisterValue>(*)>(_a[2]))); break;
        case 2: _t->EndSimulation(); break;
        case 3: _t->InstructionTable_CurrentItemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTableWidgetItem*(*)>(_a[2]))); break;
        case 4: _t->SimulationLoadButtonClicked(); break;
        case 5: _t->TransformationStartButtonClicked(); break;
        case 6: _t->StepButtonClicked(); break;
        case 7: _t->RunButtonClicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
