/****************************************************************************
** Meta object code from reading C++ file 'handwrite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "handwrite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'handwrite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HandWrite_t {
    QByteArrayData data[9];
    char stringdata[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HandWrite_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HandWrite_t qt_meta_stringdata_HandWrite = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 17),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 2),
QT_MOC_LITERAL(4, 32, 24),
QT_MOC_LITERAL(5, 57, 23),
QT_MOC_LITERAL(6, 81, 18),
QT_MOC_LITERAL(7, 100, 14),
QT_MOC_LITERAL(8, 115, 20)
    },
    "HandWrite\0slotSelectPalette\0\0id\0"
    "slotPaletteButtonClicked\0"
    "slotCancelButtonClicked\0slotIndividualSave\0"
    "slotCommonSave\0slotPenButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HandWrite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    0,   47,    2, 0x08 /* Private */,
       5,    0,   48,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HandWrite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HandWrite *_t = static_cast<HandWrite *>(_o);
        switch (_id) {
        case 0: _t->slotSelectPalette((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slotPaletteButtonClicked(); break;
        case 2: _t->slotCancelButtonClicked(); break;
        case 3: _t->slotIndividualSave(); break;
        case 4: _t->slotCommonSave(); break;
        case 5: _t->slotPenButtonClicked(); break;
        default: ;
        }
    }
}

const QMetaObject HandWrite::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HandWrite.data,
      qt_meta_data_HandWrite,  qt_static_metacall, 0, 0}
};


const QMetaObject *HandWrite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HandWrite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HandWrite.stringdata))
        return static_cast<void*>(const_cast< HandWrite*>(this));
    return QWidget::qt_metacast(_clname);
}

int HandWrite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
