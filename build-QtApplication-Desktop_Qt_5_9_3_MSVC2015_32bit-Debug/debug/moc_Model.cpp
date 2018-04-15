/****************************************************************************
** Meta object code from reading C++ file 'Model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtApplication/Model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Model_t {
    QByteArrayData data[26];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Model_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Model_t qt_meta_stringdata_Model = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Model"
QT_MOC_LITERAL(1, 6, 13), // "ProgramLoaded"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(4, 46, 12), // "instructions"
QT_MOC_LITERAL(5, 59, 16), // "RegisterValueMap"
QT_MOC_LITERAL(6, 76, 9), // "reg_inits"
QT_MOC_LITERAL(7, 86, 6), // "size_t"
QT_MOC_LITERAL(8, 93, 9), // "reg_count"
QT_MOC_LITERAL(9, 103, 12), // "StateChanged"
QT_MOC_LITERAL(10, 116, 16), // "next_instruction"
QT_MOC_LITERAL(11, 133, 26), // "std::vector<RegisterValue>"
QT_MOC_LITERAL(12, 160, 9), // "registers"
QT_MOC_LITERAL(13, 170, 15), // "SimulationEnded"
QT_MOC_LITERAL(14, 186, 15), // "OpenComputation"
QT_MOC_LITERAL(15, 202, 12), // "std::wstring"
QT_MOC_LITERAL(16, 215, 8), // "filename"
QT_MOC_LITERAL(17, 224, 11), // "std::string"
QT_MOC_LITERAL(18, 236, 9), // "input_str"
QT_MOC_LITERAL(19, 246, 11), // "StepProgram"
QT_MOC_LITERAL(20, 258, 10), // "RunProgram"
QT_MOC_LITERAL(21, 269, 13), // "TransformFile"
QT_MOC_LITERAL(22, 283, 10), // "input_file"
QT_MOC_LITERAL(23, 294, 11), // "output_file"
QT_MOC_LITERAL(24, 306, 6), // "to_set"
QT_MOC_LITERAL(25, 313, 5) // "Clear"

    },
    "Model\0ProgramLoaded\0\0std::vector<std::string>\0"
    "instructions\0RegisterValueMap\0reg_inits\0"
    "size_t\0reg_count\0StateChanged\0"
    "next_instruction\0std::vector<RegisterValue>\0"
    "registers\0SimulationEnded\0OpenComputation\0"
    "std::wstring\0filename\0std::string\0"
    "input_str\0StepProgram\0RunProgram\0"
    "TransformFile\0input_file\0output_file\0"
    "to_set\0Clear"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Model[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       9,    2,   61,    2, 0x06 /* Public */,
      13,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    2,   67,    2, 0x0a /* Public */,
      19,    0,   72,    2, 0x0a /* Public */,
      20,    0,   73,    2, 0x0a /* Public */,
      21,    3,   74,    2, 0x0a /* Public */,
      25,    0,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 11,   10,   12,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17,   16,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15, 0x80000000 | 7,   22,   23,   24,
    QMetaType::Void,

       0        // eod
};

void Model::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Model *_t = static_cast<Model *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ProgramLoaded((*reinterpret_cast< const std::vector<std::string>(*)>(_a[1])),(*reinterpret_cast< const RegisterValueMap(*)>(_a[2])),(*reinterpret_cast< size_t(*)>(_a[3]))); break;
        case 1: _t->StateChanged((*reinterpret_cast< size_t(*)>(_a[1])),(*reinterpret_cast< const std::vector<RegisterValue>(*)>(_a[2]))); break;
        case 2: _t->SimulationEnded(); break;
        case 3: _t->OpenComputation((*reinterpret_cast< const std::wstring(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 4: _t->StepProgram(); break;
        case 5: _t->RunProgram(); break;
        case 6: _t->TransformFile((*reinterpret_cast< const std::wstring(*)>(_a[1])),(*reinterpret_cast< const std::wstring(*)>(_a[2])),(*reinterpret_cast< size_t(*)>(_a[3]))); break;
        case 7: _t->Clear(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Model::*_t)(const std::vector<std::string> & , const RegisterValueMap & , size_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Model::ProgramLoaded)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Model::*_t)(size_t , const std::vector<RegisterValue> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Model::StateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Model::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Model::SimulationEnded)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Model::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Model.data,
      qt_meta_data_Model,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Model::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Model::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Model.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Model::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Model::ProgramLoaded(const std::vector<std::string> & _t1, const RegisterValueMap & _t2, size_t _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Model::StateChanged(size_t _t1, const std::vector<RegisterValue> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Model::SimulationEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
