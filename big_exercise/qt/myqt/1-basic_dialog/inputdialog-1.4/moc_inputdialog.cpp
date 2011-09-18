/****************************************************************************
** Meta object code from reading C++ file 'inputdialog.h'
**
** Created: Sat Sep 3 16:22:41 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inputdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InputDlg[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      21,    9,    9,    9, 0x08,
      31,    9,    9,    9, 0x08,
      41,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InputDlg[] = {
    "InputDlg\0\0slotName()\0slotSex()\0slotAge()\0"
    "slotStature()\0"
};

const QMetaObject InputDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InputDlg,
      qt_meta_data_InputDlg, 0 }
};

const QMetaObject *InputDlg::metaObject() const
{
    return &staticMetaObject;
}

void *InputDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InputDlg))
        return static_cast<void*>(const_cast< InputDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int InputDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotName(); break;
        case 1: slotSex(); break;
        case 2: slotAge(); break;
        case 3: slotStature(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
