/****************************************************************************
** Meta object code from reading C++ file 'gameobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gameobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameObject_t {
    QByteArrayData data[3];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameObject_t qt_meta_stringdata_GameObject = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameObject"
QT_MOC_LITERAL(1, 11, 14), // "updateLocation"
QT_MOC_LITERAL(2, 26, 0) // ""

    },
    "GameObject\0updateLocation\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void GameObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameObject *_t = static_cast<GameObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateLocation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GameObject::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GameObject.data,
      qt_meta_data_GameObject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GameObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameObject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GameObject.stringdata0))
        return static_cast<void*>(const_cast< GameObject*>(this));
    return QWidget::qt_metacast(_clname);
}

int GameObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_IllusoryObject_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IllusoryObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IllusoryObject_t qt_meta_stringdata_IllusoryObject = {
    {
QT_MOC_LITERAL(0, 0, 14) // "IllusoryObject"

    },
    "IllusoryObject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IllusoryObject[] = {

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

void IllusoryObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject IllusoryObject::staticMetaObject = {
    { &GameObject::staticMetaObject, qt_meta_stringdata_IllusoryObject.data,
      qt_meta_data_IllusoryObject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *IllusoryObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IllusoryObject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_IllusoryObject.stringdata0))
        return static_cast<void*>(const_cast< IllusoryObject*>(this));
    return GameObject::qt_metacast(_clname);
}

int IllusoryObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GameObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_RealObject_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RealObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RealObject_t qt_meta_stringdata_RealObject = {
    {
QT_MOC_LITERAL(0, 0, 10) // "RealObject"

    },
    "RealObject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RealObject[] = {

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

void RealObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject RealObject::staticMetaObject = {
    { &GameObject::staticMetaObject, qt_meta_stringdata_RealObject.data,
      qt_meta_data_RealObject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RealObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RealObject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RealObject.stringdata0))
        return static_cast<void*>(const_cast< RealObject*>(this));
    return GameObject::qt_metacast(_clname);
}

int RealObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GameObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_LineBarrier_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LineBarrier_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LineBarrier_t qt_meta_stringdata_LineBarrier = {
    {
QT_MOC_LITERAL(0, 0, 11) // "LineBarrier"

    },
    "LineBarrier"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LineBarrier[] = {

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

void LineBarrier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject LineBarrier::staticMetaObject = {
    { &RealObject::staticMetaObject, qt_meta_stringdata_LineBarrier.data,
      qt_meta_data_LineBarrier,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LineBarrier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LineBarrier::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LineBarrier.stringdata0))
        return static_cast<void*>(const_cast< LineBarrier*>(this));
    return RealObject::qt_metacast(_clname);
}

int LineBarrier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RealObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Role_t {
    QByteArrayData data[1];
    char stringdata0[5];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Role_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Role_t qt_meta_stringdata_Role = {
    {
QT_MOC_LITERAL(0, 0, 4) // "Role"

    },
    "Role"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Role[] = {

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

void Role::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Role::staticMetaObject = {
    { &RealObject::staticMetaObject, qt_meta_stringdata_Role.data,
      qt_meta_data_Role,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Role::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Role::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Role.stringdata0))
        return static_cast<void*>(const_cast< Role*>(this));
    return RealObject::qt_metacast(_clname);
}

int Role::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RealObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE