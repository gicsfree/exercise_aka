/****************************************************************************
** Meta object code from reading C++ file 'qtcpser.h'
**
** Created: Thu Sep 1 18:11:24 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtcpser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcpser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyTcpServer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      22,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyTcpServer[] = {
    "MyTcpServer\0\0accept()\0process()\0"
};

const QMetaObject MyTcpServer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyTcpServer,
      qt_meta_data_MyTcpServer, 0 }
};

const QMetaObject *MyTcpServer::metaObject() const
{
    return &staticMetaObject;
}

void *MyTcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyTcpServer))
        return static_cast<void*>(const_cast< MyTcpServer*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyTcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: accept(); break;
        case 1: process(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
