/****************************************************************************
** Meta object code from reading C++ file 'mqtt_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/apps/mqtt/mqtt_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mqtt_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mqtt_client_t {
    QByteArrayData data[18];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mqtt_client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mqtt_client_t qt_meta_stringdata_mqtt_client = {
    {
QT_MOC_LITERAL(0, 0, 11), // "mqtt_client"
QT_MOC_LITERAL(1, 12, 16), // "applyConnectSlot"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "onConnectedSlot"
QT_MOC_LITERAL(4, 46, 18), // "onDisconnectedSlot"
QT_MOC_LITERAL(5, 65, 18), // "onErrorChangedSlot"
QT_MOC_LITERAL(6, 84, 24), // "QMqttClient::ClientError"
QT_MOC_LITERAL(7, 109, 5), // "error"
QT_MOC_LITERAL(8, 115, 12), // "addTopicSlot"
QT_MOC_LITERAL(9, 128, 14), // "publishMsgSlot"
QT_MOC_LITERAL(10, 143, 18), // "subscribeTopicSlot"
QT_MOC_LITERAL(11, 162, 21), // "onMessageReceivedSlot"
QT_MOC_LITERAL(12, 184, 7), // "message"
QT_MOC_LITERAL(13, 192, 14), // "QMqttTopicName"
QT_MOC_LITERAL(14, 207, 5), // "topic"
QT_MOC_LITERAL(15, 213, 24), // "onFilterTopicChangedSlot"
QT_MOC_LITERAL(16, 238, 9), // "topicName"
QT_MOC_LITERAL(17, 248, 21) // "on_btn_cancel_clicked"

    },
    "mqtt_client\0applyConnectSlot\0\0"
    "onConnectedSlot\0onDisconnectedSlot\0"
    "onErrorChangedSlot\0QMqttClient::ClientError\0"
    "error\0addTopicSlot\0publishMsgSlot\0"
    "subscribeTopicSlot\0onMessageReceivedSlot\0"
    "message\0QMqttTopicName\0topic\0"
    "onFilterTopicChangedSlot\0topicName\0"
    "on_btn_cancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mqtt_client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    1,   67,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    2,   73,    2, 0x08 /* Private */,
      15,    1,   78,    2, 0x08 /* Private */,
      17,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 13,   12,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,

       0        // eod
};

void mqtt_client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mqtt_client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->applyConnectSlot(); break;
        case 1: _t->onConnectedSlot(); break;
        case 2: _t->onDisconnectedSlot(); break;
        case 3: _t->onErrorChangedSlot((*reinterpret_cast< QMqttClient::ClientError(*)>(_a[1]))); break;
        case 4: _t->addTopicSlot(); break;
        case 5: _t->publishMsgSlot(); break;
        case 6: _t->subscribeTopicSlot(); break;
        case 7: _t->onMessageReceivedSlot((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QMqttTopicName(*)>(_a[2]))); break;
        case 8: _t->onFilterTopicChangedSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_btn_cancel_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttClient::ClientError >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttTopicName >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mqtt_client::staticMetaObject = { {
    &IAppPage::staticMetaObject,
    qt_meta_stringdata_mqtt_client.data,
    qt_meta_data_mqtt_client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mqtt_client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mqtt_client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mqtt_client.stringdata0))
        return static_cast<void*>(this);
    return IAppPage::qt_metacast(_clname);
}

int mqtt_client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IAppPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
