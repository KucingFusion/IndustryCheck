
#ifndef _MV_ERROR_DEFINE_H_
#define _MV_ERROR_DEFINE_H_

#include "MvISPErrorDefine.h"

/********************************************************************/
///  \~chinese
///  \name ???????
///  @{
///  \~english
///  \name Definition of correct code
///  @{
#define MV_OK                       0x00000000  ///< \~chinese ??????????             \~english Successed, no error
/// @}

/********************************************************************/
///  \~chinese
///  \name ??????????:??��0x80000000-0x800000FF
///  @{
///  \~english
///  \name Definition of General error code
///  @{
#define MV_E_HANDLE                 0x80000000  ///< \~chinese ???????��????         \~english Error or invalid handle
#define MV_E_SUPPORT                0x80000001  ///< \~chinese ?????????             \~english Not supported function
#define MV_E_BUFOVER                0x80000002  ///< \~chinese ????????                 \~english Buffer overflow
#define MV_E_CALLORDER              0x80000003  ///< \~chinese ??????????????         \~english Function calling order error
#define MV_E_PARAMETER              0x80000004  ///< \~chinese ????????               \~english Incorrect parameter
#define MV_E_RESOURCE               0x80000006  ///< \~chinese ??????????             \~english Applying resource failed
#define MV_E_NODATA                 0x80000007  ///< \~chinese ??????                   \~english No data
#define MV_E_PRECONDITION           0x80000008  ///< \~chinese ???????????????��?????????��   \~english Precondition error, or running environment changed
#define MV_E_VERSION                0x80000009  ///< \~chinese ?��?????               \~english Version mismatches
#define MV_E_NOENOUGH_BUF           0x8000000A  ///< \~chinese ????????????       \~english Insufficient memory
#define MV_E_ABNORMAL_IMAGE         0x8000000B  ///< \~chinese ????????????????????????   \~english Abnormal image, maybe incomplete image because of lost packet
#define MV_E_LOAD_LIBRARY           0x8000000C  ///< \~chinese ???????DLL???          \~english Load library failed
#define MV_E_NOOUTBUF               0x8000000D  ///< \~chinese ??��?????????         \~english No Avaliable Buffer
#define MV_E_ENCRYPT                0x8000000E  ///< \~chinese ???????                 \~english Encryption error
#define MV_E_OPENFILE               0x8000000F  ///< \~chinese ????????????         \~english open file error
#define MV_E_UNKNOW                 0x800000FF  ///< \~chinese ��??????               \~english Unknown error
/// @}

/********************************************************************/
///  \~chinese
///  \name GenICam??��???:??��0x80000100-0x800001FF
///  @{
///  \~english
///  \name GenICam Series Error Codes: Range from 0x80000100 to 0x800001FF
///  @{
#define MV_E_GC_GENERIC             0x80000100  ///< \~chinese ??????                 \~english General error
#define MV_E_GC_ARGUMENT            0x80000101  ///< \~chinese ???????                 \~english Illegal parameters
#define MV_E_GC_RANGE               0x80000102  ///< \~chinese ???????��               \~english The value is out of range
#define MV_E_GC_PROPERTY            0x80000103  ///< \~chinese ????                     \~english Property
#define MV_E_GC_RUNTIME             0x80000104  ///< \~chinese ???��?????????           \~english Running environment error
#define MV_E_GC_LOGICAL             0x80000105  ///< \~chinese ???????                 \~english Logical error
#define MV_E_GC_ACCESS              0x80000106  ///< \~chinese ??????????????         \~english Node accessing condition error
#define MV_E_GC_TIMEOUT             0x80000107  ///< \~chinese ???                     \~english Timeout
#define MV_E_GC_DYNAMICCAST         0x80000108  ///< \~chinese ?????                 \~english Transformation exception
#define MV_E_GC_UNKNOW              0x800001FF  ///< \~chinese GenICam��?????          \~english GenICam unknown error
/// @}

/********************************************************************/
///  \~chinese
///  \name GigE_STATUS??????????:??��0x80000200-0x800002FF
///  @{
///  \~english
///  \name GigE_STATUS Error Codes: Range from 0x80000200 to 0x800002FF
///  @{
#define MV_E_NOT_IMPLEMENTED        0x80000200  ///< \~chinese ???????��???         \~english The command is not supported by device
#define MV_E_INVALID_ADDRESS        0x80000201  ///< \~chinese ????????????????     \~english The target address being accessed does not exist
#define MV_E_WRITE_PROTECT          0x80000202  ///< \~chinese ?????????��           \~english The target address is not writable
#define MV_E_ACCESS_DENIED          0x80000203  ///< \~chinese ?��????????           \~english No permission
#define MV_E_BUSY                   0x80000204  ///< \~chinese ?��???????????       \~english Device is busy, or network disconnected
#define MV_E_PACKET                 0x80000205  ///< \~chinese ????????????           \~english Network data packet error
#define MV_E_NETER                  0x80000206  ///< \~chinese ??????????             \~english Network error
#define MV_E_KEY_VERIFICATION       0x8000020F  ///< \~chinese ???��?????              \~english SwitchKey error
#define MV_E_IP_CONFLICT            0x80000221  ///< \~chinese ?��IP???               \~english Device IP conflict
/// @}

/********************************************************************/
///  \~chinese
///  \name USB_STATUS??????????:??��0x80000300-0x800003FF
///  @{
///  \~english
///  \name USB_STATUS Error Codes: Range from 0x80000300 to 0x800003FF
///  @{
#define MV_E_USB_READ               0x80000300  ///< \~chinese ??usb????                \~english Reading USB error
#define MV_E_USB_WRITE              0x80000301  ///< \~chinese ��usb????                \~english Writing USB error
#define MV_E_USB_DEVICE             0x80000302  ///< \~chinese ?��??                 \~english Device exception
#define MV_E_USB_GENICAM            0x80000303  ///< \~chinese GenICam??????          \~english GenICam error
#define MV_E_USB_BANDWIDTH          0x80000304  ///< \~chinese ????????                 \~english Insufficient bandwidth
#define MV_E_USB_DRIVER             0x80000305  ///< \~chinese ????????????��?????   \~english Driver mismatch or unmounted drive
#define MV_E_USB_UNKNOW             0x800003FF  ///< \~chinese USB��??????            \~english USB unknown error
/// @}

/********************************************************************/
///  \~chinese
///  \name ???????????????:??��0x80000400-0x800004FF
///  @{
///  \~english
///  \name Upgrade Error Codes: Range from 0x80000400 to 0x800004FF
///  @{
#define MV_E_UPG_FILE_MISMATCH      0x80000400  ///< \~chinese ????????????           \~english Firmware mismatches
#define MV_E_UPG_LANGUSGE_MISMATCH  0x80000401  ///< \~chinese ???????????????       \~english Firmware language mismatches
#define MV_E_UPG_CONFLICT           0x80000402  ///< \~chinese ??????????��???????????????????????????????? \~english Upgrading conflicted (repeated upgrading requests during device upgrade)
#define MV_E_UPG_INNER_ERR          0x80000403  ///< \~chinese ??????��??????????   \~english Camera internal error during upgrade
#define MV_E_UPG_UNKNOW             0x800004FF  ///< \~chinese ?????��?????           \~english Unknown error during upgrade
/// @}

#endif //_MV_ERROR_DEFINE_H_
