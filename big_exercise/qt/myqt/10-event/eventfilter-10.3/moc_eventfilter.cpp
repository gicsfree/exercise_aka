/****************************************************************************
** Meta object code from reading C++ file 'eventfilter.h'
**
** Created: Sun Sep 11 10:26:23 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "eventfilter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eventfilter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EventFilter[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   18,   13,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EventFilter[] = {
    "EventFilter\0\0bool\0,\0eventFilter(QObject*,QEvent*)\0"
};

const QMetaObject EventFilter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EventFilter,
      qt_meta_data_EventFilter, 0 }
};

const QMetaObject *EventFilter::metaObject() const
{
    return &staticMetaObject;
}

void *EventFilter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EventFilter))
        return static_cast<void*>(const_cast< EventFilter*>(this));
    return QDialog::qt_metacast(_clname);
}

int EventFilter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
