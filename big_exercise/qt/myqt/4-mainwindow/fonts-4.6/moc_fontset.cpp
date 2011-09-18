/****************************************************************************
** Meta object code from reading C++ file 'fontset.h'
**
** Created: Fri Sep 9 08:41:56 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fontset.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fontset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FontSet[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      27,    8,    8,    8, 0x0a,
      45,    8,    8,    8, 0x0a,
      56,    8,    8,    8, 0x0a,
      69,    8,    8,    8, 0x0a,
      81,    8,    8,    8, 0x0a,
      97,   93,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FontSet[] = {
    "FontSet\0\0slotFont(QString)\0slotSize(QString)\0"
    "slotBold()\0slotItalic()\0slotUnder()\0"
    "slotColor()\0fmt\0"
    "slotCurrentFormatChanged(QTextCharFormat)\0"
};

const QMetaObject FontSet::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FontSet,
      qt_meta_data_FontSet, 0 }
};

const QMetaObject *FontSet::metaObject() const
{
    return &staticMetaObject;
}

void *FontSet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FontSet))
        return static_cast<void*>(const_cast< FontSet*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FontSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotFont((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: slotSize((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: slotBold(); break;
        case 3: slotItalic(); break;
        case 4: slotUnder(); break;
        case 5: slotColor(); break;
        case 6: slotCurrentFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
