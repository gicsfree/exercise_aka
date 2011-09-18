/****************************************************************************
** Meta object code from reading C++ file 'progress.h'
**
** Created: Thu Sep 1 15:22:55 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "progress.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'progress.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Progress[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Progress[] = {
    "Progress\0\0slotStart()\0"
};

const QMetaObject Progress::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Progress,
      qt_meta_data_Progress, 0 }
};

const QMetaObject *Progress::metaObject() const
{
    return &staticMetaObject;
}

void *Progress::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Progress))
        return static_cast<void*>(const_cast< Progress*>(this));
    return QDialog::qt_metacast(_clname);
}

int Progress::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotStart(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
