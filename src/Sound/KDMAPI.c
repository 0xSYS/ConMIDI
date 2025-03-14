#include <stdio.h>
#include <dlfcn.h>
#include "KDMAPI.h"
#include "Sound.h"
#include "../Essentials.h"

void *KDMAPI_libHandle;
KDM_INIT KDMAPI_InitializeKDMAPIStream;
KDM_INIT KDMAPI_TerminateKDMAPIStream;
KDM_SEND KDMAPI_ResetKDMAPIStream;
KDM_SEND KDMAPI_SendDirectData;
KDM_LSEND KDMAPI_SendDirectLongData;
KDM_LSEND KDMAPI_PrepareLongData;
KDM_LSEND KDMAPI_UnprepareLongData;
KDM_SF_LIST KDMAPI_LoadCustomSoundFontsList;
KDM_INT_RET KDMAPI_GetActiveVoices;
KDM_INIT KDMAPI_IsKDMAPIAvailable;
KDM_DRV_SETTING KDMAPI_DriverSettings;
KDM_FLOAT_RET KDMAPI_GetRenderingTime;

int KDMAPI_Setup()
{
    // Try to load the KDMAPI library (using .so extension for Linux)
    if ((KDMAPI_libHandle = dlopen("libOmniMIDI.so", RTLD_LAZY)) == NULL)
    {
        err_log(1, "Failed to load KDMAPI: %s", dlerror());
        return 0;
    }

    // Get function pointers using dlsym instead of GetProcAddress
    if ((KDMAPI_InitializeKDMAPIStream = (KDM_INIT)dlsym(KDMAPI_libHandle, "InitializeKDMAPIStream")) == NULL)
    {
        err_log(1, "dlsym() failed to retrieve library symbol InitializeKDMAPIStream. Returned error: %s", dlerror());
        return 0;
    }
    
    if ((KDMAPI_SendDirectData = (KDM_SEND)dlsym(KDMAPI_libHandle, "SendDirectData")) == NULL)
    {
        err_log(1, "dlysm() failed to retrieve library symbol SendDirectData. Returned error: %s", dlerror());
        return 0;
    }

    if((KDMAPI_TerminateKDMAPIStream = (KDM_INIT)dlsym(KDMAPI_libHandle, "TerminateKDMAPIStream")) == NULL)
    {
        err_log(1, "dlsym() failed to retrieve library symbol TerminateKDMAPIStream. Returned error: %s", dlerror());
        return 0;
    }

    if((KDMAPI_ResetKDMAPIStream = (KDM_SEND)dlsym(KDMAPI_libHandle, "ResetKDMAPIStream")) == NULL)
    {
        err_log(1, "dlsym() failed to retrieve library symbol ResetKDMAPIStream. Returned error: &s", dlerror());
        return 0;
    }

    if((KDMAPI_LoadCustomSoundFontsList = (KDM_SF_LIST)dlsym(KDMAPI_libHandle, "LoadCustomSoundFontsList")) == NULL)
    {
        err_log(1, "dlsym() failed to retrieve library symbol LoadCustomSoundFontList. Returned error: %s", dlerror());
        return 0;
    }

     if((KDMAPI_GetRenderingTime = (KDM_FLOAT_RET)dlsym(KDMAPI_libHandle, "GetRenderingTime")) == NULL)
     {
         err_log(1, "dlsym() failed to retrieve library symbol GetRenderingTime. Returnned error: %s", dlerror());
         return 0;
     }

     if((KDMAPI_GetActiveVoices = (KDM_INT_RET)dlsym(KDMAPI_libHandle, "GetActiveVoices")) == NULL)
     {
         err_log(1, "dlsym() failed to retrieve library symbol GetActiveVoices. Returned error: %s", dlerror());
         return 0;
     }

     if((KDMAPI_IsKDMAPIAvailable = (KDM_INIT)dlsym(KDMAPI_libHandle, "IsKDMAPIAvailable")) == NULL)
     {
         err_log(1, "dlsym() failed to retrieve library symbol IsKDMAPIAvailable. Returned error: %s", dlerror());
         return 0;
     }

    if((KDMAPI_DriverSettings = (KDM_DRV_SETTING)dlsym(KDMAPI_libHandle, "DriverSettings")) == NULL)
    {
        err_log(1, "dlsym() failed to retrieve library symbol DriverSettings. Returned Error: %s", dlerror());
        return 0;
    }

    /*
    To import next:
    GetActiveVoices
    IsKDMAPIAvailable
    DriverSettings
    */

    

    success_log("KDMAPI Functional");
    return 1;
}
