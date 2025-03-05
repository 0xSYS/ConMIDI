#include <stdio.h>
#include <dlfcn.h>
#include "KDMAPI.h"
#include "Sound.h"
#include "../Essentials.h"

void *KDMAPI_libHandle;
KDM_INIT KDMAPI_InitializeKDMAPIStream;
KDM_INIT KDMAPI_TerminateKDMAPIStream;
KDM_INIT KDMAPI_ResetKDMAPIStream;
KDM_SEND KDMAPI_SendDirectData;
KDM_LSEND KDMAPI_SendDirectLongData;
KDM_LSEND KDMAPI_PrepareLongData;
KDM_LSEND KDMAPI_UnprepareLongData;

int KDMAPI_Setup()
{
    // Try to load the KDMAPI library (using .so extension for Linux)
    if ((KDMAPI_libHandle = dlopen("libOmniMIDI.so", RTLD_LAZY)) == NULL)
    {
        err_log(0, "Failed to load KDMAPI: %s", dlerror());
        return 0;
    }

    // Get function pointers using dlsym instead of GetProcAddress
    if ((KDMAPI_InitializeKDMAPIStream = (KDM_INIT)dlsym(KDMAPI_libHandle, "InitializeKDMAPIStream")) == NULL)
    {
        err_log(0, "dlsym() InitializeKDMAPIStream failed: %s", dlerror());
        return 0;
    }
    
    if ((KDMAPI_SendDirectData = (KDM_SEND)dlsym(KDMAPI_libHandle, "SendDirectData")) == NULL)
    {
        err_log(0, "dlysm() SendDirectData failed: %s", dlerror());
        return 0;
    }

    

    success_log("KDMAPI Functional");
    return 1;
}
