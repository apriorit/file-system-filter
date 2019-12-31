#include "FsMinifilter.h"

//
// Global minifilter handle
//
extern PFLT_FILTER g_minifilterHandle;

NTSTATUS FLTAPI InstanceFilterUnloadCallback(_In_ FLT_FILTER_UNLOAD_FLAGS Flags)
{
    //
    // This is called before a filter is unloaded.
    // If a NULL is specified for this routine then the filter can never be unloaded.
    //

    UNREFERENCED_PARAMETER(Flags);

    if (NULL != g_minifilterHandle)
    {
        FltUnregisterFilter(g_minifilterHandle);
    }

    return STATUS_SUCCESS;
}

NTSTATUS FLTAPI InstanceSetupCallback(
    _In_ PCFLT_RELATED_OBJECTS  FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS  Flags,
    _In_ DEVICE_TYPE  VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE  VolumeFilesystemType)
{
    //
    // This is called to see if a filter would like to attach an instance to the given volume.
    // If a NULL is specified for this routine, the attachment is always made.
    //

    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    UNREFERENCED_PARAMETER(VolumeDeviceType);
    UNREFERENCED_PARAMETER(VolumeFilesystemType);

    return STATUS_SUCCESS;
}

NTSTATUS FLTAPI InstanceQueryTeardownCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
)
{
    //
    // This is called to see if the filter wants to detach from the given
    // volume. This is only called for manual detach requests.
    // If a NULL is specified for this routine, then instances can never be manually detached.
    //

    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);

    return STATUS_SUCCESS;
}

FLT_PREOP_CALLBACK_STATUS FLTAPI PreOperationCreate(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
)
{
    //
    // Pre-create callback to get file info during creation or opening
    //

    UNREFERENCED_PARAMETER(Data);
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    DbgPrint("%wZ\n", &Data->Iopb->TargetFileObject->FileName);

    return FLT_PREOP_SUCCESS_NO_CALLBACK;
}
