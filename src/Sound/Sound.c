#include <stdio.h>
#include "KDMAPI.h"
#include "Sound.h"
#include "../Essentials.h"

void (*SendDirectDataPtr)(unsigned long int a);
int (*SendDirectLongDataPtr)(MIDIHDR *a, unsigned int b);
int (*PrepareLongDataPtr)(MIDIHDR *a, unsigned int b);
int (*UnprepareLongDataPtr)(MIDIHDR *a, unsigned int b);

int usable = 0;

void Sound_Setup()
{
    if (KDMAPI_Setup() == 1)
    {
        usable = 1;
        info_log("KDMAPI available");
    }
    else
    {
        err_log(0, "No sound system is available");
    }
}

int Sound_Init()
{
    if (usable)
    {
        int res = KDMAPI_InitializeKDMAPIStream();
        if (res == 1)
        {
            success_log("KDMAPI Init");
            SendDirectDataPtr = KDMAPI_SendDirectData;
            SendDirectLongDataPtr = KDMAPI_SendDirectLongData;
            PrepareLongDataPtr = KDMAPI_PrepareLongData;
            UnprepareLongDataPtr = KDMAPI_UnprepareLongData;
            return 1;
        }
        else
        {
            err_log(0, "KDMAPI Failed to initialise");
            return 0;
        }
    }
    else
    {
        info_log("KDMAPI is unavailable");
        return 0;
    }
}
