/****************************************************************************
** Meta object code from reading C++ file 'monitorbackend.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../monitorbackend.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monitorbackend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMonitorBackendENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMonitorBackendENDCLASS = QtMocHelpers::stringData(
    "MonitorBackend",
    "updated",
    "",
    "availabilityChanged",
    "pollIntervalChanged",
    "refresh",
    "onNvidiaFinished",
    "cpuUsage",
    "memUsage",
    "gpuUsage",
    "cpuTemp",
    "gpuTemp",
    "netDownSpeed",
    "netUpSpeed",
    "gpuAvailable",
    "cpuTempAvailable",
    "gpuTempAvailable",
    "pollInterval",
    "netInterfaces"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMonitorBackendENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
      12,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,   13 /* Public */,
       3,    0,   45,    2, 0x06,   14 /* Public */,
       4,    0,   46,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   47,    2, 0x08,   16 /* Private */,
       6,    0,   48,    2, 0x08,   17 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
       7, QMetaType::Double, 0x00015801, uint(0), 0,
       8, QMetaType::Double, 0x00015801, uint(0), 0,
       9, QMetaType::Double, 0x00015801, uint(0), 0,
      10, QMetaType::Double, 0x00015801, uint(0), 0,
      11, QMetaType::Double, 0x00015801, uint(0), 0,
      12, QMetaType::Double, 0x00015801, uint(0), 0,
      13, QMetaType::Double, 0x00015801, uint(0), 0,
      14, QMetaType::Bool, 0x00015801, uint(1), 0,
      15, QMetaType::Bool, 0x00015801, uint(1), 0,
      16, QMetaType::Bool, 0x00015801, uint(1), 0,
      17, QMetaType::Int, 0x00015903, uint(2), 0,
      18, QMetaType::QStringList, 0x00015c01, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject MonitorBackend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSMonitorBackendENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMonitorBackendENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMonitorBackendENDCLASS_t,
        // property 'cpuUsage'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'memUsage'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'gpuUsage'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'cpuTemp'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'gpuTemp'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'netDownSpeed'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'netUpSpeed'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'gpuAvailable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'cpuTempAvailable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'gpuTempAvailable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'pollInterval'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'netInterfaces'
        QtPrivate::TypeAndForceComplete<QStringList, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MonitorBackend, std::true_type>,
        // method 'updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'availabilityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pollIntervalChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refresh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNvidiaFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MonitorBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MonitorBackend *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->availabilityChanged(); break;
        case 2: _t->pollIntervalChanged(); break;
        case 3: _t->refresh(); break;
        case 4: _t->onNvidiaFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MonitorBackend::*)();
            if (_t _q_method = &MonitorBackend::updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MonitorBackend::*)();
            if (_t _q_method = &MonitorBackend::availabilityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MonitorBackend::*)();
            if (_t _q_method = &MonitorBackend::pollIntervalChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MonitorBackend *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->cpuUsage(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->memUsage(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->gpuUsage(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->cpuTemp(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->gpuTemp(); break;
        case 5: *reinterpret_cast< double*>(_v) = _t->netDownSpeed(); break;
        case 6: *reinterpret_cast< double*>(_v) = _t->netUpSpeed(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->gpuAvailable(); break;
        case 8: *reinterpret_cast< bool*>(_v) = _t->cpuTempAvailable(); break;
        case 9: *reinterpret_cast< bool*>(_v) = _t->gpuTempAvailable(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->pollInterval(); break;
        case 11: *reinterpret_cast< QStringList*>(_v) = _t->netInterfaces(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MonitorBackend *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 10: _t->setPollInterval(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *MonitorBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MonitorBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMonitorBackendENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MonitorBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MonitorBackend::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MonitorBackend::availabilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MonitorBackend::pollIntervalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
