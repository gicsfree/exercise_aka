/****************************************************************************
** Meta object code from reading C++ file 'udpserver.h'
**
** Created: Sun Sep 11 09:38:02 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "udpserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UdpServer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      37,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UdpServer[] = {
    "UdpServer\0\0PushButtonStart_clicked()\0"
    "timeout()\0"
};

const QMetaObject UdpServer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UdpServer,
      qt_meta_data_UdpServer, 0 }
};

const QMetaObject *UdpServer::metaObject() const
{
    return &staticMetaObject;
}

void *UdpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UdpServer))
        return static_cast<void*>(const_cast< UdpServer*>(this));
    return QDialog::qt_metacast(_clname);
}

int UdpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: PushButtonStart_clicked(); break;
        case 1: timeout(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
