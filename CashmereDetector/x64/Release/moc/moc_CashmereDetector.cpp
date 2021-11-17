/****************************************************************************
** Meta object code from reading C++ file 'CashmereDetector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CashmereDetector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CashmereDetector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CashmereDetector_t {
    QByteArrayData data[13];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CashmereDetector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CashmereDetector_t qt_meta_stringdata_CashmereDetector = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CashmereDetector"
QT_MOC_LITERAL(1, 17, 27), // "on_openFileAction_triggered"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 7), // "checked"
QT_MOC_LITERAL(4, 54, 26), // "on_pushButton_pick_clicked"
QT_MOC_LITERAL(5, 81, 32), // "on_pushButton_autoDetect_clicked"
QT_MOC_LITERAL(6, 114, 27), // "on_pushButton_reset_clicked"
QT_MOC_LITERAL(7, 142, 30), // "on_pushButton_saveCurr_clicked"
QT_MOC_LITERAL(8, 173, 34), // "on_pushButton_scalesDetect_cl..."
QT_MOC_LITERAL(9, 208, 32), // "on_pushButton_areaSelect_clicked"
QT_MOC_LITERAL(10, 241, 27), // "on_spin_rotate_valueChanged"
QT_MOC_LITERAL(11, 269, 3), // "val"
QT_MOC_LITERAL(12, 273, 16) // "on_timer_timeout"

    },
    "CashmereDetector\0on_openFileAction_triggered\0"
    "\0checked\0on_pushButton_pick_clicked\0"
    "on_pushButton_autoDetect_clicked\0"
    "on_pushButton_reset_clicked\0"
    "on_pushButton_saveCurr_clicked\0"
    "on_pushButton_scalesDetect_clicked\0"
    "on_pushButton_areaSelect_clicked\0"
    "on_spin_rotate_valueChanged\0val\0"
    "on_timer_timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CashmereDetector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    0,   62,    2, 0x0a /* Public */,
       5,    0,   63,    2, 0x0a /* Public */,
       6,    0,   64,    2, 0x0a /* Public */,
       7,    0,   65,    2, 0x0a /* Public */,
       8,    0,   66,    2, 0x0a /* Public */,
       9,    0,   67,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x0a /* Public */,
      12,    0,   71,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,

       0        // eod
};

void CashmereDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CashmereDetector *_t = static_cast<CashmereDetector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_openFileAction_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_pick_clicked(); break;
        case 2: _t->on_pushButton_autoDetect_clicked(); break;
        case 3: _t->on_pushButton_reset_clicked(); break;
        case 4: _t->on_pushButton_saveCurr_clicked(); break;
        case 5: _t->on_pushButton_scalesDetect_clicked(); break;
        case 6: _t->on_pushButton_areaSelect_clicked(); break;
        case 7: _t->on_spin_rotate_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_timer_timeout(); break;
        default: ;
        }
    }
}

const QMetaObject CashmereDetector::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CashmereDetector.data,
      qt_meta_data_CashmereDetector,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CashmereDetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CashmereDetector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CashmereDetector.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CashmereDetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
