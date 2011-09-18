/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created: Sat Sep 10 18:16:31 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWidget[] = {

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
      60,   11,   11,   11, 0x0a,
      78,   11,   11,   11, 0x0a,
      94,   11,   11,   11, 0x0a,
     111,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWidget[] = {
    "MainWidget\0\0slotShape(int)\0slotPenWidth(int)\0"
    "slotPenColor()\0slotPenStyle(int)\0"
    "slotPenCap(int)\0slotPenJoin(int)\0"
    "slotBrush(int)\0"
};

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget,
      qt_meta_data_MainWidget, 0 }
};

const QMetaObject *MainWidget::metaObject() const
{
    return &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotShape((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: slotPenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: slotPenColor(); break;
        case 3: slotPenStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: slotPenCap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: slotPenJoin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: slotBrush((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
