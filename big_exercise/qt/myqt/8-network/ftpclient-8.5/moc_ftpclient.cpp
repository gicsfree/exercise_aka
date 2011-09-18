/****************************************************************************
** Meta object code from reading C++ file 'ftpclient.h'
**
** Created: Sun Sep 11 10:04:14 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ftpclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FtpClient[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      23,   10,   10,   10, 0x0a,
      33,   10,   10,   10, 0x0a,
      49,   43,   10,   10, 0x0a,
      77,   71,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FtpClient[] = {
    "FtpClient\0\0slotLogin()\0slotPut()\0"
    "slotGet()\0state\0slotStateChanged(int)\0"
    "error\0slotDone(bool)\0"
};

const QMetaObject FtpClient::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FtpClient,
      qt_meta_data_FtpClient, 0 }
};

const QMetaObject *FtpClient::metaObject() const
{
    return &staticMetaObject;
}

void *FtpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FtpClient))
        return static_cast<void*>(const_cast< FtpClient*>(this));
    return QDialog::qt_metacast(_clname);
}

int FtpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotLogin(); break;
        case 1: slotPut(); break;
        case 2: slotGet(); break;
        case 3: slotStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: slotDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
