/****************************************************************************
** Meta object code from reading C++ file 'imgprocessor.h'
**
** Created: Fri Sep 9 08:19:05 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "imgprocessor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imgprocessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImgProcessor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x09,
      29,   13,   13,   13, 0x09,
      42,   13,   13,   13, 0x09,
      56,   13,   13,   13, 0x09,
      71,   13,   13,   13, 0x09,
      87,   13,   13,   13, 0x09,
     103,   13,   13,   13, 0x09,
     124,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ImgProcessor[] = {
    "ImgProcessor\0\0slotOpenFile()\0slotZoomIn()\0"
    "slotZoomOut()\0slotRotate90()\0"
    "slotRotate180()\0slotRotate270()\0"
    "slotMirrorVertical()\0slotMirrorHorizontal()\0"
};

const QMetaObject ImgProcessor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ImgProcessor,
      qt_meta_data_ImgProcessor, 0 }
};

const QMetaObject *ImgProcessor::metaObject() const
{
    return &staticMetaObject;
}

void *ImgProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImgProcessor))
        return static_cast<void*>(const_cast< ImgProcessor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ImgProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotOpenFile(); break;
        case 1: slotZoomIn(); break;
        case 2: slotZoomOut(); break;
        case 3: slotRotate90(); break;
        case 4: slotRotate180(); break;
        case 5: slotRotate270(); break;
        case 6: slotMirrorVertical(); break;
        case 7: slotMirrorHorizontal(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
