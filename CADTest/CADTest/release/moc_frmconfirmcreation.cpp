/****************************************************************************
** Meta object code from reading C++ file 'frmconfirmcreation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../frmconfirmcreation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmconfirmcreation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FrmConfirmCreation_t {
    QByteArrayData data[7];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FrmConfirmCreation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FrmConfirmCreation_t qt_meta_stringdata_FrmConfirmCreation = {
    {
QT_MOC_LITERAL(0, 0, 18), // "FrmConfirmCreation"
QT_MOC_LITERAL(1, 19, 25), // "on_txtFactorA_textChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 4), // "arg1"
QT_MOC_LITERAL(4, 51, 25), // "on_txtFactorB_textChanged"
QT_MOC_LITERAL(5, 77, 16), // "on_btnOK_clicked"
QT_MOC_LITERAL(6, 94, 20) // "on_btnCancel_clicked"

    },
    "FrmConfirmCreation\0on_txtFactorA_textChanged\0"
    "\0arg1\0on_txtFactorB_textChanged\0"
    "on_btnOK_clicked\0on_btnCancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FrmConfirmCreation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       5,    0,   40,    2, 0x08 /* Private */,
       6,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FrmConfirmCreation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FrmConfirmCreation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_txtFactorA_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_txtFactorB_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_btnOK_clicked(); break;
        case 3: _t->on_btnCancel_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FrmConfirmCreation::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_FrmConfirmCreation.data,
    qt_meta_data_FrmConfirmCreation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FrmConfirmCreation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrmConfirmCreation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FrmConfirmCreation.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FrmConfirmCreation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
