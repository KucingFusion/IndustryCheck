/****************************************************************************
** Meta object code from reading C++ file 'IndustryCheck.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/IndustryCheck.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IndustryCheck.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSIndustryCheckENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSIndustryCheckENDCLASS = QtMocHelpers::stringData(
    "IndustryCheck",
    "slot_connect_Device",
    "",
    "slot_capture_Mode",
    "slot_trigger_Mode",
    "slot_capture_State",
    "slot_setTemp_ROI",
    "slot_tempMarch_ROI",
    "slot_process_State",
    "slot_binarization_parameters",
    "index",
    "slot_morphology_operation",
    "slot_canny_detrction",
    "slot_filtered_contours",
    "slot_geometric_detection",
    "slot_geometric_calculation"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSIndustryCheckENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x08,    1 /* Private */,
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    0,   95,    2, 0x08,    4 /* Private */,
       6,    0,   96,    2, 0x08,    5 /* Private */,
       7,    0,   97,    2, 0x08,    6 /* Private */,
       8,    0,   98,    2, 0x08,    7 /* Private */,
       9,    1,   99,    2, 0x08,    8 /* Private */,
      11,    1,  102,    2, 0x08,   10 /* Private */,
      12,    0,  105,    2, 0x08,   12 /* Private */,
      13,    0,  106,    2, 0x08,   13 /* Private */,
      14,    0,  107,    2, 0x08,   14 /* Private */,
      15,    0,  108,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject IndustryCheck::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSIndustryCheckENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSIndustryCheckENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSIndustryCheckENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<IndustryCheck, std::true_type>,
        // method 'slot_connect_Device'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_capture_Mode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_trigger_Mode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_capture_State'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_setTemp_ROI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_tempMarch_ROI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_process_State'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_binarization_parameters'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'slot_morphology_operation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'slot_canny_detrction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_filtered_contours'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_geometric_detection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_geometric_calculation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void IndustryCheck::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IndustryCheck *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_connect_Device(); break;
        case 1: _t->slot_capture_Mode(); break;
        case 2: _t->slot_trigger_Mode(); break;
        case 3: _t->slot_capture_State(); break;
        case 4: _t->slot_setTemp_ROI(); break;
        case 5: _t->slot_tempMarch_ROI(); break;
        case 6: _t->slot_process_State(); break;
        case 7: _t->slot_binarization_parameters((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->slot_morphology_operation((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->slot_canny_detrction(); break;
        case 10: _t->slot_filtered_contours(); break;
        case 11: _t->slot_geometric_detection(); break;
        case 12: _t->slot_geometric_calculation(); break;
        default: ;
        }
    }
}

const QMetaObject *IndustryCheck::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IndustryCheck::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSIndustryCheckENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int IndustryCheck::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
