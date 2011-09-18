/****************************************************************************
** Meta object code from reading C++ file 'rubberband.h'
**
** Created: Sat Sep 10 18:54:00 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rubberband.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rubberband.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RubberBand[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_RubberBand[] = {
    "RubberBand\0"
};

const QMetaObject RubberBand::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RubberBand,
      qt_meta_data_RubberBand, 0 }
};

const QMetaObject *RubberBand::metaObject() const
{
    return &staticMetaObject;
}

void *RubberBand::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RubberBand))
        return static_cast<void*>(const_cast< RubberBand*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RubberBand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
