/****************************************************************************
** Meta object code from reading C++ file 'qtcpcli.h'
**
** Created: Sat Sep 3 15:37:20 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtcpcli.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcpcli.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyTcpCli[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      20,    9,    9,    9, 0x0a,
      37,    9,    9,    9, 0x0a,
      49,    9,    9,    9, 0x0a,
      74,   62,    9,    9, 0x0a,
     116,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyTcpCli[] = {
    "MyTcpCli\0\0process()\0connect_to_ser()\0"
    "send_file()\0connect_ok()\0socketError\0"
    "connect_err(QAbstractSocket::SocketError)\0"
    "do_timer()\0"
};

const QMetaObject MyTcpCli::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyTcpCli,
      qt_meta_data_MyTcpCli, 0 }
};

const QMetaObject *MyTcpCli::metaObject() const
{
    return &staticMetaObject;
}

void *MyTcpCli::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyTcpCli))
        return static_cast<void*>(const_cast< MyTcpCli*>(this));
    if (!strcmp(_clname, "Ui_Form"))
        return static_cast< Ui_Form*>(const_cast< MyTcpCli*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyTcpCli::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: process(); break;
        case 1: connect_to_ser(); break;
        case 2: send_file(); break;
        case 3: connect_ok(); break;
        case 4: connect_err((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: do_timer(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
