#include "FsFilter.h"

/////////////////////////////////////////////////////////////////////////////
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
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoCheckIfPossible)) 
    {
        return (fastIoDispatch->FastIoCheckIfPossible)(
            FileObject,
            FileOffset,
            Length,
            Wait,
            LockKey,
            CheckForReadOperation,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoRead(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in BOOLEAN            Wait,
    __in ULONG              LockKey,
    __out PVOID             Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoRead)) 
    {
        return (fastIoDispatch->FastIoRead)(
            FileObject,
            FileOffset,
            Length,
            Wait,
            LockKey,
            Buffer,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoWrite(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in BOOLEAN            Wait,
    __in ULONG              LockKey,
    __in PVOID              Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoWrite)) 
    {
        return (fastIoDispatch->FastIoWrite)(
            FileObject,
            FileOffset,
            Length,
            Wait,
            LockKey,
            Buffer,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoQueryBasicInfo(
    __in PFILE_OBJECT       FileObject,
    __in BOOLEAN            Wait,
    __out PFILE_BASIC_INFORMATION Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoQueryBasicInfo)) 
    {

        return (fastIoDispatch->FastIoQueryBasicInfo)(
            FileObject,
            Wait,
            Buffer,
            IoStatus,
            nextDeviceObject);
    }
    
    return FALSE;
}

BOOLEAN FsFilterFastIoQueryStandardInfo(
    __in PFILE_OBJECT       FileObject,
    __in BOOLEAN            Wait,
    __out PFILE_STANDARD_INFORMATION Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoQueryStandardInfo)) 
    {
        return (fastIoDispatch->FastIoQueryStandardInfo)(
            FileObject,
            Wait,
            Buffer,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

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
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoLock)) 
    {
        return (fastIoDispatch->FastIoLock)(
            FileObject,
            FileOffset,
            Length,
            ProcessId,
            Key,
            FailImmediately,
            ExclusiveLock,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoUnlockSingle(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in PLARGE_INTEGER     Length,
    __in PEPROCESS          ProcessId,
    __in ULONG              Key,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoUnlockSingle)) 
    {
        return (fastIoDispatch->FastIoUnlockSingle)(
            FileObject,
            FileOffset,
            Length,
            ProcessId,
            Key,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoUnlockAll(
    __in PFILE_OBJECT       FileObject,
    __in PEPROCESS          ProcessId,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoUnlockAll)) 
    {
        return (fastIoDispatch->FastIoUnlockAll)(
            FileObject,
            ProcessId,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoUnlockAllByKey(
    __in PFILE_OBJECT       FileObject,
    __in PVOID              ProcessId,
    __in ULONG              Key,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoUnlockAllByKey))
    {
        return (fastIoDispatch->FastIoUnlockAllByKey)(
            FileObject,
            ProcessId,
            Key,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

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
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoDeviceControl)) 
    {
        return (fastIoDispatch->FastIoDeviceControl)(
            FileObject,
            Wait,
            InputBuffer,
            InputBufferLength,
            OutputBuffer,
            OutputBufferLength,
            IoControlCode,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

VOID FsFilterFastIoDetachDevice(
    __in PDEVICE_OBJECT     SourceDevice,
    __in PDEVICE_OBJECT     TargetDevice
    )
{
    //
    //  Detach from the file system's volume device object.
    //

    IoDetachDevice(TargetDevice);
    IoDeleteDevice(SourceDevice);
}

BOOLEAN FsFilterFastIoQueryNetworkOpenInfo(
    __in PFILE_OBJECT       FileObject,
    __in BOOLEAN            Wait,
    __out PFILE_NETWORK_OPEN_INFORMATION Buffer,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoQueryNetworkOpenInfo)) 
    {
        return (fastIoDispatch->FastIoQueryNetworkOpenInfo)(
            FileObject,
            Wait,
            Buffer,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoMdlRead(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in ULONG              LockKey,
    __out PMDL*             MdlChain,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, MdlRead)) 
    {
        return (fastIoDispatch->MdlRead)(
            FileObject,
            FileOffset,
            Length,
            LockKey,
            MdlChain,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoMdlReadComplete(
    __in PFILE_OBJECT       FileObject,
    __in PMDL               MdlChain,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, MdlReadComplete)) 
    {
        return (fastIoDispatch->MdlReadComplete)(
            FileObject,
            MdlChain,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoPrepareMdlWrite(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in ULONG              Length,
    __in ULONG              LockKey,
    __out PMDL*             MdlChain,
    __out PIO_STATUS_BLOCK  IoStatus,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, PrepareMdlWrite)) 
    {
        return (fastIoDispatch->PrepareMdlWrite)(
            FileObject,
            FileOffset,
            Length,
            LockKey,
            MdlChain,
            IoStatus,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoMdlWriteComplete(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in PMDL               MdlChain,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, MdlWriteComplete)) 
    {
        return (fastIoDispatch->MdlWriteComplete)(
            FileObject,
            FileOffset,
            MdlChain,
            nextDeviceObject);
    }

    return FALSE;
}

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
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoReadCompressed)) 
    {
        return (fastIoDispatch->FastIoReadCompressed)(
            FileObject,
            FileOffset,
            Length,
            LockKey,
            Buffer,
            MdlChain,
            IoStatus,
            CompressedDataInfo,
            CompressedDataInfoLength,
            nextDeviceObject);
    }

    return FALSE;
}

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
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoWriteCompressed)) 
    {
        return (fastIoDispatch->FastIoWriteCompressed)(
            FileObject,
            FileOffset,
            Length,
            LockKey,
            Buffer,
            MdlChain,
            IoStatus,
            CompressedDataInfo,
            CompressedDataInfoLength,
            nextDeviceObject );
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoMdlReadCompleteCompressed(
    __in PFILE_OBJECT       FileObject,
    __in PMDL               MdlChain,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, MdlReadCompleteCompressed)) 
    {
        return (fastIoDispatch->MdlReadCompleteCompressed)(
            FileObject,
            MdlChain,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoMdlWriteCompleteCompressed(
    __in PFILE_OBJECT       FileObject,
    __in PLARGE_INTEGER     FileOffset,
    __in PMDL               MdlChain,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, MdlWriteCompleteCompressed)) 
    {
        return (fastIoDispatch->MdlWriteCompleteCompressed)(
            FileObject,
            FileOffset,
            MdlChain,
            nextDeviceObject);
    }

    return FALSE;
}

BOOLEAN FsFilterFastIoQueryOpen(
    __in PIRP               Irp,
    __out PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
    __in PDEVICE_OBJECT     DeviceObject
    )
{
    //
    //  Pass through logic for this type of Fast I/O
    //

    PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
    PFAST_IO_DISPATCH fastIoDispatch   = nextDeviceObject->DriverObject->FastIoDispatch;

    if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoQueryOpen)) 
    {
        BOOLEAN result;
        PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );

        //
        //  Before calling the next filter, we must make sure their device
        //  object is in the current stack entry for the given IRP
        //

        irpSp->DeviceObject = nextDeviceObject;

        result = (fastIoDispatch->FastIoQueryOpen)(
            Irp,
            NetworkInformation,
            nextDeviceObject);

        //
        //  Always restore the IRP back to our device object
        //

        irpSp->DeviceObject = DeviceObject;
        return result;
    }

    return FALSE;
}