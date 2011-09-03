/****************************************************************************
** Meta object code from reading C++ file 'myform.h'
**
** Created: Sat Sep 3 10:43:51 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myForm[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      18,    7,    7,    7, 0x0a,
      35,    7,    7,    7, 0x0a,
      47,    7,    7,    7, 0x0a,
      72,   60,    7,    7, 0x0a,
     114,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myForm[] = {
    "myForm\0\0process()\0connect_to_ser()\0"
    "send_file()\0connect_ok()\0socketError\0"
    "connect_err(QAbstractSocket::SocketError)\0"
    "do_timer()\0"
};

const QMetaObject myForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_myForm,
      qt_meta_data_myForm, 0 }
};

const QMetaObject *myForm::metaObject() const
{
    return &staticMetaObject;
}

void *myForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myForm))
        return static_cast<void*>(const_cast< myForm*>(this));
    if (!strcmp(_clname, "Ui_Form"))
        return static_cast< Ui_Form*>(const_cast< myForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int myForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: process(); break;
        case 1: connect_to_ser(); break;
        case 2: send_file(); break;
        case 3: connect_ok(); break;
        case 4: connect_err((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: do_timer(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
