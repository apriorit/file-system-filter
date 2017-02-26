#pragma once
#include <ntifs.h>

//////////////////////////////////////////////////////////////////////////
// Defines

#define DELAY_ONE_MICROSECOND   (-10)
#define DELAY_ONE_MILLISECOND   (DELAY_ONE_MICROSECOND * 1000)
#define DELAY_ONE_SECOND        (DELAY_ONE_MILLISECOND * 1000)

#define DEVOBJ_LIST_SIZE        64

//  Macro to test if FAST_IO_DISPATCH handling routine is valid
#define VALID_FAST_IO_DISPATCH_HANDLER(_FastIoDispatchPtr, _FieldName) \
    (((_FastIoDispatchPtr) != NULL) && \
    (((_FastIoDispatchPtr)->SizeOfFastIoDispatch) >= \
    (FIELD_OFFSET(FAST_IO_DISPATCH, _FieldName) + sizeof(void *))) && \
    ((_FastIoDispatchPtr)->_FieldName != NULL))

//////////////////////////////////////////////////////////////////////////
// Structures

typedef struct _FSFILTER_DEVICE_EXTENSION
{
    PDEVICE_OBJECT AttachedToDeviceObject;
} FSFILTER_DEVICE_EXTENSION, *PFSFILTER_DEVICE_EXTENSION;

//////////////////////////////////////////////////////////////////////////
// General Functions

NTSTATUS FsFilterDispatchPassThrough(
    __in PDEVICE_OBJECT DeviceObject, 
    __in PIRP           Irp
    );

NTSTATUS FsFilterDispatchCreate(
    __in PDEVICE_OBJECT DeviceObject,
    __in PIRP           Irp
    );

NTSTATUS FsFilterAttachToDevice(
    __in PDEVICE_OBJECT         DeviceObject,
    __out_opt PDEVICE_OBJECT*   pFilterDeviceObject
    );

VOID FsFilterDetachFromDevice(
    __in PDEVICE_OBJECT DeviceObject
    );

BOOLEAN FsFilterIsAttachedToDevice(
    __in PDEVICE_OBJECT DeviceObject
    );

BOOLEAN FsFilterIsMyDeviceObject(
    __in PDEVICE_OBJECT DeviceObject
    );

VOID FsFilterNotificationCallback(
    __in PDEVICE_OBJECT DeviceObject,
    __in BOOLEAN        FsActive
    );

//////////////////////////////////////////////////////////////////////////
// Fast-IO Handlers

BOOLEAN FsFilterFastIoCheckIfPossible(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in BOOLEAN            Wait,
    __in ULONG              LockKey,
    __in BOOLEAN            CheckForReadOperation,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoRead(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in BOOLEAN            Wait,
    __in ULONG              LockKey,
    __out PVOID             Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoWrite(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in BOOLEAN            Wait,
    __in ULONG              LockKey,
    __in PVOID              Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoQueryBasicInfo(
    __in PFILE_OBJECT       FileObject,
    __in BOOLEAN            Wait,
    __out PFILE_BASIC_INFORMATION Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoQueryStandardInfo(
    __in PFILE_OBJECT       FileObject,
    __in BOOLEAN            Wait,
    __out PFILE_STANDARD_INFORMATION Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoLock(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in PLARGE_INTEGER     Length,
    __in PEPROCESS          ProcessId,
    __in ULONG              Key,
    __in BOOLEAN            FailImmediately,
    __in BOOLEAN            ExclusiveLock,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoUnlockSingle(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in PLARGE_INTEGER     Length,
    __in PEPROCESS          ProcessId,
    __in ULONG              Key,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoUnlockAll(
    __in PFILE_OBJECT       FileObject,
    __in PEPROCESS          ProcessId,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoUnlockAllByKey(
    __in PFILE_OBJECT       FileObject,
    __in PVOID              ProcessId,
    __in ULONG              Key,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoDeviceControl(
    __in PFILE_OBJECT       FileObject,
    __in BOOLEAN            Wait,
    __in_opt PVOID          InputBuffer,
    __in ULONG              InputBufferLength,
    __out_opt PVOID         OutputBuffer,
    __in ULONG              OutputBufferLength,
    __in ULONG              IoControlCode,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

VOID FsFilterFastIoDetachDevice(
    __in PDEVICE_OBJECT     SourceDevice,
    __in PDEVICE_OBJECT     TargetDevice
    );

BOOLEAN FsFilterFastIoQueryNetworkOpenInfo(
    __in PFILE_OBJECT       FileObject,
    __in BOOLEAN            Wait,
    __out PFILE_NETWORK_OPEN_INFORMATION Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoMdlRead(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in ULONG              LockKey,
    __out PMDL*             MdlChain,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoMdlReadComplete(
    __in PFILE_OBJECT       FileObject,
    __in PMDL               MdlChain,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoPrepareMdlWrite(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in ULONG              LockKey,
    __out PMDL*             MdlChain,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoMdlWriteComplete(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in PMDL               MdlChain,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoReadCompressed(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in ULONG              LockKey,
    __out PVOID             Buffer,
    __out PMDL*             MdlChain,
    __out PIO_STATUS_BLOCK  IoStatus,
    __out struct _COMPRESSED_DATA_INFO* CompressedDataInfo,
    __in ULONG              CompressedDataInfoLength,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoWriteCompressed(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in ULONG              LockKey,
    __in PVOID              Buffer,
    __out PMDL*             MdlChain,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in struct _COMPRESSED_DATA_INFO*  CompressedDataInfo,
    __in ULONG              CompressedDataInfoLength,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoMdlReadCompleteCompressed(
    __in PFILE_OBJECT       FileObject,
    __in PMDL               MdlChain,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoMdlWriteCompleteCompressed(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in PMDL               MdlChain,
    __in PDEVICE_OBJECT     DeviceObject
    );

BOOLEAN FsFilterFastIoQueryOpen(
    __in PIRP               Irp,
    __out PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
    __in PDEVICE_OBJECT     DeviceObject
    );

//////////////////////////////////////////////////////////////////////////
// Global data

extern PDRIVER_OBJECT g_fsFilterDriverObject;
