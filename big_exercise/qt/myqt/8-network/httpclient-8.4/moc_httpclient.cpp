/****************************************************************************
** Meta object code from reading C++ file 'httpclient.h'
**
** Created: Sun Sep 11 09:57:56 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "httpclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HttpClient[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      27,   11,   11,   11, 0x0a,
      40,   11,   11,   11, 0x0a,
      53,   51,   11,   11, 0x0a,
      83,   51,   11,   11, 0x0a,
     113,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HttpClient[] = {
    "HttpClient\0\0slotDownload()\0slotCancel()\0"
    "slotExit()\0,\0httpRequestFinished(int,bool)\0"
    "httpDataReadProgress(int,int)\0"
    "httpResponseHeaderReceived(QHttpResponseHeader)\0"
};

const QMetaObject HttpClient::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_HttpClient,
      qt_meta_data_HttpClient, 0 }
};

const QMetaObject *HttpClient::metaObject() const
{
    return &staticMetaObject;
}

void *HttpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HttpClient))
        return static_cast<void*>(const_cast< HttpClient*>(this));
    return QDialog::qt_metacast(_clname);
}

int HttpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotDownload(); break;
        case 1: slotCancel(); break;
        case 2: slotExit(); break;
        case 3: httpRequestFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: httpDataReadProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: httpResponseHeaderReceived((*reinterpret_cast< const QHttpResponseHeader(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
