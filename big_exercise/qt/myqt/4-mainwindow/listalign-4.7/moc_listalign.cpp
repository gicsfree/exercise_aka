/****************************************************************************
** Meta object code from reading C++ file 'listalign.h'
**
** Created: Fri Sep 9 08:51:59 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "listalign.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listalign.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ListAlign[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      35,   10,   10,   10, 0x0a,
      49,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ListAlign[] = {
    "ListAlign\0\0slotAlignment(QAction*)\0"
    "slotList(int)\0slotCursorPositionChanged()\0"
};

const QMetaObject ListAlign::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ListAlign,
      qt_meta_data_ListAlign, 0 }
};

const QMetaObject *ListAlign::metaObject() const
{
    return &staticMetaObject;
}

void *ListAlign::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ListAlign))
        return static_cast<void*>(const_cast< ListAlign*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ListAlign::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotAlignment((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: slotList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: slotCursorPositionChanged(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
