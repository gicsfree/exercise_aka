/****************************************************************************
** Meta object code from reading C++ file 'palette.h'
**
** Created: Wed Sep 7 11:35:46 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "palette.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'palette.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Palette[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      22,    8,    8,    8, 0x0a,
      39,    8,    8,    8, 0x0a,
      52,    8,    8,    8, 0x0a,
      69,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Palette[] = {
    "Palette\0\0slotWindow()\0slotWindowText()\0"
    "slotButton()\0slotButtonText()\0slotBase()\0"
};

const QMetaObject Palette::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Palette,
      qt_meta_data_Palette, 0 }
};

const QMetaObject *Palette::metaObject() const
{
    return &staticMetaObject;
}

void *Palette::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Palette))
        return static_cast<void*>(const_cast< Palette*>(this));
    return QDialog::qt_metacast(_clname);
}

int Palette::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotWindow(); break;
        case 1: slotWindowText(); break;
        case 2: slotButton(); break;
        case 3: slotButtonText(); break;
        case 4: slotBase(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
