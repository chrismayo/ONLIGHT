/****************************************************************************
** Meta object code from reading C++ file 'softkeypad.h'
**
** Created: Fri Jul 17 15:25:21 2015
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
static const uint qt_meta_data_SoftKeyPad[] = {

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
      34,   31,   11,   11, 0x08,
      54,   31,   11,   11, 0x08,
      75,   31,   11,   11, 0x08,
     100,   11,   11,   11, 0x08,
     122,   11,   11,   11, 0x08,
     145,   31,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SoftKeyPad[] = {
    "SoftKeyPad\0\0sigOkPressSignal()\0id\0"
    "slotNumPressed(int)\0slotNumReleased(int)\0"
    "slotKeyInputClicked(int)\0slotLeftTurnClicked()\0"
    "slotRightTurnClicked()\0"
    "slotChineseInputClicked(int)\0"
};

void SoftKeyPad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SoftKeyPad *_t = static_cast<SoftKeyPad *>(_o);
        switch (_id) {
        case 0: _t->sigOkPressSignal(); break;
        case 1: _t->slotNumPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotNumReleased((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotKeyInputClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotLeftTurnClicked(); break;
        case 5: _t->slotRightTurnClicked(); break;
        case 6: _t->slotChineseInputClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SoftKeyPad::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SoftKeyPad::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SoftKeyPad,
      qt_meta_data_SoftKeyPad, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SoftKeyPad::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SoftKeyPad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SoftKeyPad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SoftKeyPad))
        return static_cast<void*>(const_cast< SoftKeyPad*>(this));
    return QWidget::qt_metacast(_clname);
}

int SoftKeyPad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SoftKeyPad::sigOkPressSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
