/****************************************************************************
** Meta object code from reading C++ file 'softkeypad.h'
**
** Created: Thu Jul 16 11:49:01 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "softkeypad.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'softkeypad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_softKeyPad[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   28,   11,   11, 0x08,
      47,   28,   11,   11, 0x08,
      64,   28,   11,   11, 0x08,
      85,   11,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     122,   28,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_softKeyPad[] = {
    "softKeyPad\0\0okPressSignal()\0id\0"
    "numPressed(int)\0numReleased(int)\0"
    "keyInputClicked(int)\0leftTurnClicked()\0"
    "rightTurnClicked()\0chineseInputClicked(int)\0"
};

void softKeyPad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        softKeyPad *_t = static_cast<softKeyPad *>(_o);
        switch (_id) {
        case 0: _t->okPressSignal(); break;
        case 1: _t->numPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->numReleased((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->keyInputClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->leftTurnClicked(); break;
        case 5: _t->rightTurnClicked(); break;
        case 6: _t->chineseInputClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData softKeyPad::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject softKeyPad::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_softKeyPad,
      qt_meta_data_softKeyPad, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &softKeyPad::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *softKeyPad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *softKeyPad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_softKeyPad))
        return static_cast<void*>(const_cast< softKeyPad*>(this));
    return QWidget::qt_metacast(_clname);
}

int softKeyPad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void softKeyPad::okPressSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
