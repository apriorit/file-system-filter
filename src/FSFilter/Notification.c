#include "FsFilter.h"

//////////////////////////////////////////////////////////////////////////
// Prototypes

NTSTATUS FsFilterAttachToFileSystemDevice(
    __in PDEVICE_OBJECT DeviceObject
    );

VOID FsFilterDetachFromFileSystemDevice(
    __in PDEVICE_OBJECT DeviceObject
    );

NTSTATUS FsFilterEnumerateFileSystemVolumes(
    __in PDEVICE_OBJECT DeviceObject
    );

///////////////////////////////////////////////////////////////////////////////////////////////////
// This routine is invoked whenever a file system has either registered or
// unregistered itself as an active file system.

VOID FsFilterNotificationCallback(
    __in PDEVICE_OBJECT DeviceObject,
    __in BOOLEAN        FsActive
    )
{
    //
    //  Handle attaching/detaching from the given file system.
    //

    if (FsActive)
    {
        FsFilterAttachToFileSystemDevice(DeviceObject);
    }
    else
    {
        FsFilterDetachFromFileSystemDevice(DeviceObject);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This will attach to the given file system device object

NTSTATUS FsFilterAttachToFileSystemDevice(
    __in PDEVICE_OBJECT DeviceObject
    )
{
    NTSTATUS        status              = STATUS_SUCCESS;
    PDEVICE_OBJECT  filterDeviceObject  = NULL;

    if (!FsFilterIsAttachedToDevice(DeviceObject))
    {
        status = FsFilterAttachToDevice(DeviceObject, &filterDeviceObject);

        if (!NT_SUCCESS(status)) 
        {
            return status;
        }

        //
        //  Enumerate all the mounted devices that currently exist for this file system and attach to them.
        //

        status = FsFilterEnumerateFileSystemVolumes(DeviceObject);

        if (!NT_SUCCESS(status)) 
        {
            FsFilterDetachFromDevice(filterDeviceObject);
            return status;
        }
    }   

    return STATUS_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This will detach us from the chain

VOID FsFilterDetachFromFileSystemDevice(
    __in PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT device = NULL;

    for (device = DeviceObject->AttachedDevice; NULL != device; device = device->AttachedDevice) 
    {
        if (FsFilterIsMyDeviceObject(device)) 
        {
            //
            //  Detach us from the object just below us. Cleanup and delete the object.
            //

            FsFilterDetachFromDevice(device);

            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Enumerate all the mounted devices that currently exist for the given file
// system and attach to them

NTSTATUS FsFilterEnumerateFileSystemVolumes(
    __in PDEVICE_OBJECT DeviceObject
    )
{
    NTSTATUS        status      = STATUS_SUCCESS;
    ULONG           numDevices  = 0;
    ULONG           i           = 0;
    PDEVICE_OBJECT  devList[DEVOBJ_LIST_SIZE];

    //
    //  Now get the list of devices.
    //

    status = IoEnumerateDeviceObjectList(
        DeviceObject->DriverObject,
        devList,
        sizeof(devList),
        &numDevices);

    if (!NT_SUCCESS(status))
    {
        return status;
    }

    numDevices = min(numDevices, RTL_NUMBER_OF(devList));

    //
    //  Walk the given list of devices and attach to them if we should.
    //

    for (i = 0; i < numDevices; ++i) 
    {        
        //
        //  Do not attach if:
        //      - This is the control device object (the one passed in)
        //      - The device type does not match
        //      - We are already attached to it.
        //

        if (devList[i] != DeviceObject &&
            devList[i]->DeviceType == DeviceObject->DeviceType &&
            !FsFilterIsAttachedToDevice(devList[i])) 
        {
            status = FsFilterAttachToDevice(devList[i], NULL);
        }       

        ObDereferenceObject(devList[i]);
    }

    return STATUS_SUCCESS;
}