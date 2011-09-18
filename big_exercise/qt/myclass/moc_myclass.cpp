/****************************************************************************
** Meta object code from reading C++ file 'myclass.h'
**
** Created: Tue Aug 30 16:49:44 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myclass.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myclass[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      26,   20,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,    8,    8,    8, 0x0a,
      55,    8,    8,    8, 0x0a,
      69,   20,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myclass[] = {
    "myclass\0\0mysignal()\0value\0int_mysignal(int)\0"
    "do_print()\0do_mysignal()\0int_myslot(int)\0"
};

const QMetaObject myclass::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_myclass,
      qt_meta_data_myclass, 0 }
};

const QMetaObject *myclass::metaObject() const
{
    return &staticMetaObject;
}

void *myclass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myclass))
        return static_cast<void*>(const_cast< myclass*>(this));
    return QObject::qt_metacast(_clname);
}

int myclass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mysignal(); break;
        case 1: int_mysignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: do_print(); break;
        case 3: do_mysignal(); break;
        case 4: int_myslot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void myclass::mysignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void myclass::int_mysignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
