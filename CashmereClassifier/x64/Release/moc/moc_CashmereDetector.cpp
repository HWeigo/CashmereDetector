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
struct qt_meta_stringdata_WorkerThread_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerThread_t qt_meta_stringdata_WorkerThread = {
    {
QT_MOC_LITERAL(0, 0, 12) // "WorkerThread"

    },
    "WorkerThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void WorkerThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject WorkerThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WorkerThread.data,
      qt_meta_data_WorkerThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WorkerThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int WorkerThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_CashmereDetector_t {
    QByteArrayData data[28];
    char stringdata0[667];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CashmereDetector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CashmereDetector_t qt_meta_stringdata_CashmereDetector = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CashmereDetector"
QT_MOC_LITERAL(1, 17, 33), // "on_openFileAction_image_trigg..."
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 7), // "checked"
QT_MOC_LITERAL(4, 60, 33), // "on_openFileAction_video_trigg..."
QT_MOC_LITERAL(5, 94, 30), // "on_activate_software_triggered"
QT_MOC_LITERAL(6, 125, 26), // "on_pushButton_pick_clicked"
QT_MOC_LITERAL(7, 152, 32), // "on_pushButton_autoDetect_clicked"
QT_MOC_LITERAL(8, 185, 34), // "on_pushButton_videoProcess_cl..."
QT_MOC_LITERAL(9, 220, 34), // "on_pushButton_loadCropImgs_cl..."
QT_MOC_LITERAL(10, 255, 27), // "on_pushButton_reset_clicked"
QT_MOC_LITERAL(11, 283, 30), // "on_pushButton_saveCurr_clicked"
QT_MOC_LITERAL(12, 314, 34), // "on_pushButton_scalesDetect_cl..."
QT_MOC_LITERAL(13, 349, 26), // "on_pushButton_next_clicked"
QT_MOC_LITERAL(14, 376, 26), // "on_pushButton_back_clicked"
QT_MOC_LITERAL(15, 403, 30), // "on_pushButton_autoNext_clicked"
QT_MOC_LITERAL(16, 434, 30), // "on_pushButton_autoBack_clicked"
QT_MOC_LITERAL(17, 465, 30), // "on_pushButton_autoStop_clicked"
QT_MOC_LITERAL(18, 496, 32), // "on_pushButton_areaSelect_clicked"
QT_MOC_LITERAL(19, 529, 27), // "on_spin_rotate_valueChanged"
QT_MOC_LITERAL(20, 557, 3), // "val"
QT_MOC_LITERAL(21, 561, 33), // "on_spin_selectorSize_valueCha..."
QT_MOC_LITERAL(22, 595, 16), // "on_timer_timeout"
QT_MOC_LITERAL(23, 612, 10), // "wheelEvent"
QT_MOC_LITERAL(24, 623, 12), // "QWheelEvent*"
QT_MOC_LITERAL(25, 636, 5), // "event"
QT_MOC_LITERAL(26, 642, 13), // "keyPressEvent"
QT_MOC_LITERAL(27, 656, 10) // "QKeyEvent*"

    },
    "CashmereDetector\0on_openFileAction_image_triggered\0"
    "\0checked\0on_openFileAction_video_triggered\0"
    "on_activate_software_triggered\0"
    "on_pushButton_pick_clicked\0"
    "on_pushButton_autoDetect_clicked\0"
    "on_pushButton_videoProcess_clicked\0"
    "on_pushButton_loadCropImgs_clicked\0"
    "on_pushButton_reset_clicked\0"
    "on_pushButton_saveCurr_clicked\0"
    "on_pushButton_scalesDetect_clicked\0"
    "on_pushButton_next_clicked\0"
    "on_pushButton_back_clicked\0"
    "on_pushButton_autoNext_clicked\0"
    "on_pushButton_autoBack_clicked\0"
    "on_pushButton_autoStop_clicked\0"
    "on_pushButton_areaSelect_clicked\0"
    "on_spin_rotate_valueChanged\0val\0"
    "on_spin_selectorSize_valueChanged\0"
    "on_timer_timeout\0wheelEvent\0QWheelEvent*\0"
    "event\0keyPressEvent\0QKeyEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CashmereDetector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x0a /* Public */,
       4,    1,  122,    2, 0x0a /* Public */,
       5,    1,  125,    2, 0x0a /* Public */,
       6,    0,  128,    2, 0x0a /* Public */,
       7,    0,  129,    2, 0x0a /* Public */,
       8,    0,  130,    2, 0x0a /* Public */,
       9,    0,  131,    2, 0x0a /* Public */,
      10,    0,  132,    2, 0x0a /* Public */,
      11,    0,  133,    2, 0x0a /* Public */,
      12,    0,  134,    2, 0x0a /* Public */,
      13,    0,  135,    2, 0x0a /* Public */,
      14,    0,  136,    2, 0x0a /* Public */,
      15,    0,  137,    2, 0x0a /* Public */,
      16,    0,  138,    2, 0x0a /* Public */,
      17,    0,  139,    2, 0x0a /* Public */,
      18,    0,  140,    2, 0x0a /* Public */,
      19,    1,  141,    2, 0x0a /* Public */,
      21,    1,  144,    2, 0x0a /* Public */,
      22,    0,  147,    2, 0x0a /* Public */,
      23,    1,  148,    2, 0x0a /* Public */,
      26,    1,  151,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 27,   25,

       0        // eod
};

void CashmereDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CashmereDetector *_t = static_cast<CashmereDetector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_openFileAction_image_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_openFileAction_video_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_activate_software_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_pick_clicked(); break;
        case 4: _t->on_pushButton_autoDetect_clicked(); break;
        case 5: _t->on_pushButton_videoProcess_clicked(); break;
        case 6: _t->on_pushButton_loadCropImgs_clicked(); break;
        case 7: _t->on_pushButton_reset_clicked(); break;
        case 8: _t->on_pushButton_saveCurr_clicked(); break;
        case 9: _t->on_pushButton_scalesDetect_clicked(); break;
        case 10: _t->on_pushButton_next_clicked(); break;
        case 11: _t->on_pushButton_back_clicked(); break;
        case 12: _t->on_pushButton_autoNext_clicked(); break;
        case 13: _t->on_pushButton_autoBack_clicked(); break;
        case 14: _t->on_pushButton_autoStop_clicked(); break;
        case 15: _t->on_pushButton_areaSelect_clicked(); break;
        case 16: _t->on_spin_rotate_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_spin_selectorSize_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_timer_timeout(); break;
        case 19: _t->wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 20: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
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
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
