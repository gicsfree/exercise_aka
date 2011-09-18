/****************************************************************************
** Meta object code from reading C++ file 'fileviewer.h'
**
** Created: Sun Sep 11 10:15:10 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fileviewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fileviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileViewer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x0a,
      51,   47,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FileViewer[] = {
    "FileViewer\0\0item\0slotShowDir(QListWidgetItem*)\0"
    "dir\0slotShow(QDir)\0"
};

const QMetaObject FileViewer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FileViewer,
      qt_meta_data_FileViewer, 0 }
};

const QMetaObject *FileViewer::metaObject() const
{
    return &staticMetaObject;
}

void *FileViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileViewer))
        return static_cast<void*>(const_cast< FileViewer*>(this));
    return QDialog::qt_metacast(_clname);
}

int FileViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotShowDir((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: slotShow((*reinterpret_cast< QDir(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
