/****************************************************************************
** Meta object code from reading C++ file 'cursor.h'
**
** Created: Sun Sep 11 10:37:14 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cursor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cursor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Cursor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      20,    7,    7,    7, 0x08,
      31,    7,    7,    7, 0x08,
      47,    7,    7,    7, 0x08,
      59,    7,    7,    7, 0x08,
      75,    7,    7,    7, 0x08,
      86,    7,    7,    7, 0x08,
      99,    7,    7,    7, 0x08,
     111,    7,    7,    7, 0x08,
     126,    7,    7,    7, 0x08,
     140,    7,    7,    7, 0x08,
     152,    7,    7,    7, 0x08,
     164,    7,    7,    7, 0x08,
     176,    7,    7,    7, 0x08,
     188,    7,    7,    7, 0x08,
     202,    7,    7,    7, 0x08,
     215,    7,    7,    7, 0x08,
     226,    7,    7,    7, 0x08,
     242,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Cursor[] = {
    "Cursor\0\0slotArrow()\0slotBusy()\0"
    "slotCloseHand()\0slotCross()\0slotForbidden()\0"
    "slotHand()\0slotHSplit()\0slotIbeam()\0"
    "slotOpenHand()\0slotSizeAll()\0slotSizeB()\0"
    "slotSizeF()\0slotSizeH()\0slotSizeV()\0"
    "slotUpArrow()\0slotVSplit()\0slotWait()\0"
    "slotWhatsThis()\0slotCustom()\0"
};

const QMetaObject Cursor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Cursor,
      qt_meta_data_Cursor, 0 }
};

const QMetaObject *Cursor::metaObject() const
{
    return &staticMetaObject;
}

void *Cursor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Cursor))
        return static_cast<void*>(const_cast< Cursor*>(this));
    return QDialog::qt_metacast(_clname);
}

int Cursor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotArrow(); break;
        case 1: slotBusy(); break;
        case 2: slotCloseHand(); break;
        case 3: slotCross(); break;
        case 4: slotForbidden(); break;
        case 5: slotHand(); break;
        case 6: slotHSplit(); break;
        case 7: slotIbeam(); break;
        case 8: slotOpenHand(); break;
        case 9: slotSizeAll(); break;
        case 10: slotSizeB(); break;
        case 11: slotSizeF(); break;
        case 12: slotSizeH(); break;
        case 13: slotSizeV(); break;
        case 14: slotUpArrow(); break;
        case 15: slotVSplit(); break;
        case 16: slotWait(); break;
        case 17: slotWhatsThis(); break;
        case 18: slotCustom(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
