/****************************************************************************
** Meta object code from reading C++ file 'DesktopWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/shell/DesktopWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DesktopWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DesktopWindow_t {
    QByteArrayData data[9];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DesktopWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DesktopWindow_t qt_meta_stringdata_DesktopWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DesktopWindow"
QT_MOC_LITERAL(1, 14, 7), // "openApp"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "appId"
QT_MOC_LITERAL(4, 29, 11), // "showDesktop"
QT_MOC_LITERAL(5, 41, 13), // "onDockClicked"
QT_MOC_LITERAL(6, 55, 6), // "dockId"
QT_MOC_LITERAL(7, 62, 13), // "onPageChanged"
QT_MOC_LITERAL(8, 76, 5) // "index"

    },
    "DesktopWindow\0openApp\0\0appId\0showDesktop\0"
    "onDockClicked\0dockId\0onPageChanged\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DesktopWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    0,   37,    2, 0x08 /* Private */,
       5,    1,   38,    2, 0x08 /* Private */,
       7,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void DesktopWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DesktopWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openApp((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->showDesktop(); break;
        case 2: _t->onDockClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DesktopWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_DesktopWindow.data,
    qt_meta_data_DesktopWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DesktopWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DesktopWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DesktopWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DesktopWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
