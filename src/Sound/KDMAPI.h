#ifndef KDMAPI_H
#define KDMAPI_H

#include "Sound.h"

typedef int (*KDM_INIT)();
typedef void (*KDM_SEND)(unsigned long int);
typedef int (*KDM_SF_LIST)(char* path);
typedef int (*KDM_LSEND)(MIDIHDR*, unsigned int);
typedef void (*KDM_FUNC_OUT)();
typedef void (*KDM_FUNC_INPUT)();
typedef void (*KDM_DRV_SETTING)(unsigned int setting, unsigned int mode, void* value, unsigned int cbValue);
typedef int (*KDM_INT_RET)();
typedef float (*KDM_FLOAT_RET)();
typedef void**(*KDM_TEST)();

extern KDM_INIT KDMAPI_InitializeKDMAPIStream;
extern KDM_INIT KDMAPI_TerminateKDMAPIStream;
extern KDM_SEND KDMAPI_ResetKDMAPIStream;
extern KDM_SEND KDMAPI_SendDirectData;
extern KDM_LSEND KDMAPI_SendDirectLongData;
extern KDM_LSEND KDMAPI_PrepareLongData;
extern KDM_LSEND KDMAPI_UnprepareLongData;
extern KDM_SF_LIST KDMAPI_LoadCustomSoundFontsList;
extern KDM_FLOAT_RET KDMAPI_GetRenderingTime;
extern KDM_INT_RET KDMAPI_GetActiveVoices;
extern KDM_INIT KDMAPI_IsKDMAPIAvailable;
extern KDM_DRV_SETTING KDMAPI_DriverSettings;


int KDMAPI_Setup();

#endif
