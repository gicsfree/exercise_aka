/****************************************************************************
** Meta object code from reading C++ file 'messagebox.h'
**
** Created: Sat Sep 3 20:35:04 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "messagebox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'messagebox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MessageBox[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      27,   11,   11,   11, 0x0a,
      45,   11,   11,   11, 0x0a,
      59,   11,   11,   11, 0x0a,
      74,   11,   11,   11, 0x0a,
      86,   11,   11,   11, 0x0a,
     100,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MessageBox[] = {
    "MessageBox\0\0slotQuestion()\0slotInformation()\0"
    "slotWarning()\0slotCritical()\0slotAbout()\0"
    "slotAboutQt()\0slotCustom()\0"
};

const QMetaObject MessageBox::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MessageBox,
      qt_meta_data_MessageBox, 0 }
};

const QMetaObject *MessageBox::metaObject() const
{
    return &staticMetaObject;
}

void *MessageBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MessageBox))
        return static_cast<void*>(const_cast< MessageBox*>(this));
    return QDialog::qt_metacast(_clname);
}

int MessageBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotQuestion(); break;
        case 1: slotInformation(); break;
        case 2: slotWarning(); break;
        case 3: slotCritical(); break;
        case 4: slotAbout(); break;
        case 5: slotAboutQt(); break;
        case 6: slotCustom(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
