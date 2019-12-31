#include "FsMinifilter.h"

//
// The minifilter handle that results from a call to FltRegisterFilter
// NOTE: this handle must be passed to FltUnregisterFilter during minifilter unloading
//
PFLT_FILTER g_minifilterHandle = NULL;

//
// Constant FLT_REGISTRATION structure for our filter. This
// initializes the callback routines our filter wants to register for. 
// This is only used to register with the filter manager
//
CONST FLT_OPERATION_REGISTRATION g_callbacks[] =
{
    {
        IRP_MJ_CREATE,
        0,
        PreOperationCreate,
        0
    },

    { IRP_MJ_OPERATION_END }
};

//
// The FLT_REGISTRATION structure is used to provide information about
// a file system minifilter to the filter manager.
//
CONST FLT_REGISTRATION g_filterRegistration =
{
    sizeof(FLT_REGISTRATION),      //  Size
    FLT_REGISTRATION_VERSION,      //  Version
    0,                             //  Flags
    NULL,                          //  Context Registration
    g_callbacks,                   //  Operation callbacks
    InstanceFilterUnloadCallback,  //  FilterUnload
    InstanceSetupCallback,         //  InstanceSetup
    InstanceQueryTeardownCallback, //  InstanceQueryTeardown
    NULL,                          //  InstanceTeardownStart
    NULL,                          //  InstanceTeardownComplete
    NULL,                          //  GenerateFileName
    NULL,                          //  GenerateDestinationFileName
    NULL                           //  NormalizeNameComponent
};

EXTERN_C DRIVER_INITIALIZE DriverEntry;

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);
    NTSTATUS status = STATUS_SUCCESS;
	
    //
    // register minifilter driver
    //
    status = FltRegisterFilter(DriverObject, &g_filterRegistration, &g_minifilterHandle);
    if (!NT_SUCCESS(status))
    {
        return status;
    }
	
    //
    // start minifilter driver
    //
    status = FltStartFiltering(g_minifilterHandle);
    if (!NT_SUCCESS(status))
    {
        FltUnregisterFilter(g_minifilterHandle);
    }
	
    return status;
}
