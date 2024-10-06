/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "openImage"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "loadImage"
QT_MOC_LITERAL(4, 32, 4), // "path"
QT_MOC_LITERAL(5, 37, 12), // "setupPuzzle1"
QT_MOC_LITERAL(6, 50, 12), // "setupPuzzle2"
QT_MOC_LITERAL(7, 63, 12), // "setupPuzzle3"
QT_MOC_LITERAL(8, 76, 13), // "setCompleted1"
QT_MOC_LITERAL(9, 90, 13), // "setCompleted2"
QT_MOC_LITERAL(10, 104, 13), // "setCompleted3"
QT_MOC_LITERAL(11, 118, 13), // "setCompleted4"
QT_MOC_LITERAL(12, 132, 8), // "showHelp"
QT_MOC_LITERAL(13, 141, 9), // "startGame"
QT_MOC_LITERAL(14, 151, 15), // "startcustomGame"
QT_MOC_LITERAL(15, 167, 15), // "startlevel1Game"
QT_MOC_LITERAL(16, 183, 15), // "startlevel2Game"
QT_MOC_LITERAL(17, 199, 15), // "startlevel3Game"
QT_MOC_LITERAL(18, 215, 9) // "showHelp2"

    },
    "MainWindow\0openImage\0\0loadImage\0path\0"
    "setupPuzzle1\0setupPuzzle2\0setupPuzzle3\0"
    "setCompleted1\0setCompleted2\0setCompleted3\0"
    "setCompleted4\0showHelp\0startGame\0"
    "startcustomGame\0startlevel1Game\0"
    "startlevel2Game\0startlevel3Game\0"
    "showHelp2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    1,   95,    2, 0x0a /* Public */,
       5,    0,   98,    2, 0x0a /* Public */,
       6,    0,   99,    2, 0x0a /* Public */,
       7,    0,  100,    2, 0x0a /* Public */,
       8,    0,  101,    2, 0x08 /* Private */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    0,  109,    2, 0x08 /* Private */,
      17,    0,  110,    2, 0x08 /* Private */,
      18,    0,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
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
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openImage(); break;
        case 1: _t->loadImage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setupPuzzle1(); break;
        case 3: _t->setupPuzzle2(); break;
        case 4: _t->setupPuzzle3(); break;
        case 5: _t->setCompleted1(); break;
        case 6: _t->setCompleted2(); break;
        case 7: _t->setCompleted3(); break;
        case 8: _t->setCompleted4(); break;
        case 9: _t->showHelp(); break;
        case 10: _t->startGame(); break;
        case 11: _t->startcustomGame(); break;
        case 12: _t->startlevel1Game(); break;
        case 13: _t->startlevel2Game(); break;
        case 14: _t->startlevel3Game(); break;
        case 15: _t->showHelp2(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
