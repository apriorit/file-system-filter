#include "FsFilter.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// This will attach to a DeviceObject that represents a mounted volume

NTSTATUS FsFilterAttachToDevice(
    __in PDEVICE_OBJECT         DeviceObject,
    __out_opt PDEVICE_OBJECT*   pFilterDeviceObject
    )
{
    NTSTATUS                    status              = STATUS_SUCCESS;
    PDEVICE_OBJECT              filterDeviceObject  = NULL;
    PFSFILTER_DEVICE_EXTENSION  pDevExt             = NULL;
    ULONG                       i                   = 0;

    ASSERT(!FsFilterIsAttachedToDevice(DeviceObject));

    //
    //  Create a new device object we can attach with.
    //

    status = IoCreateDevice(
        g_fsFilterDriverObject,
        sizeof(FSFILTER_DEVICE_EXTENSION),
        NULL,
        DeviceObject->DeviceType,
        0,
        FALSE,
        &filterDeviceObject);

    if (!NT_SUCCESS(status)) 
    {
        return status;
    }

    pDevExt = (PFSFILTER_DEVICE_EXTENSION)filterDeviceObject->DeviceExtension;

    //
    //  Propagate flags from Device Object we are trying to attach to.
    //

    if (FlagOn(DeviceObject->Flags, DO_BUFFERED_IO)) 
    {
        SetFlag(filterDeviceObject->Flags, DO_BUFFERED_IO);
    }

    if (FlagOn(DeviceObject->Flags, DO_DIRECT_IO)) 
    {
        SetFlag(filterDeviceObject->Flags, DO_DIRECT_IO);
    }

    if (FlagOn(DeviceObject->Characteristics, FILE_DEVICE_SECURE_OPEN)) 
    {
        SetFlag(filterDeviceObject->Characteristics, FILE_DEVICE_SECURE_OPEN);
    }    

    //
    //  Do the attachment.
    //
    //  It is possible for this attachment request to fail because this device
    //  object has not finished initializing.  This can occur if this filter
    //  loaded just as this volume was being mounted.
    //

    for (i = 0; i < 8; ++i) 
    {
        LARGE_INTEGER interval;

        status = IoAttachDeviceToDeviceStackSafe(
            filterDeviceObject,
            DeviceObject,
            &pDevExt->AttachedToDeviceObject);

        if (NT_SUCCESS(status)) 
        {
            break;
        }

        //
        //  Delay, giving the device object a chance to finish its
        //  initialization so we can try again.
        //

        interval.QuadPart = (500 * DELAY_ONE_MILLISECOND);
        KeDelayExecutionThread(KernelMode, FALSE, &interval);
    }

    if (!NT_SUCCESS(status))
    {
        //
        // Clean up.
        //

        IoDeleteDevice(filterDeviceObject);
        filterDeviceObject = NULL;
    }
    else
    {
        //
        // Mark we are done initializing.
        //

        ClearFlag(filterDeviceObject->Flags, DO_DEVICE_INITIALIZING);

        if (NULL != pFilterDeviceObject)
        {
            *pFilterDeviceObject = filterDeviceObject;
        }        
    }

    return status;
}

void FsFilterDetachFromDevice(
    __in PDEVICE_OBJECT DeviceObject
    )
{    
    PFSFILTER_DEVICE_EXTENSION pDevExt = (PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;
    
    IoDetachDevice(pDevExt->AttachedToDeviceObject);
    IoDeleteDevice(DeviceObject);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This determines whether we are attached to the given device

BOOLEAN FsFilterIsAttachedToDevice(
    __in PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT nextDevObj    = NULL;
    PDEVICE_OBJECT currentDevObj = IoGetAttachedDeviceReference(DeviceObject);
    
    //
    //  Scan down the list to find our device object.
    //

    do 
    {
        if (FsFilterIsMyDeviceObject(currentDevObj)) 
        {
            ObDereferenceObject(currentDevObj);
            return TRUE;
        }

        //
        //  Get the next attached object.
        //

        nextDevObj = IoGetLowerDeviceObject(currentDevObj);

        //
        //  Dereference our current device object, before moving to the next one.
        //

        ObDereferenceObject(currentDevObj);
        currentDevObj = nextDevObj;
    } while (NULL != currentDevObj);

    return FALSE;
}
