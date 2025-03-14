#include <stdio.h>
#include <sys/ucontext.h>
#include <unistd.h>
#include <stdbool.h>
#include <ncurses.h>
#include <pthread.h>

#include "Essentials.h"
#include "Sound/KDMAPI.h"
#include "Sound/Sound.h"
#include "MIDI/LoadMIDI.h"
#include "Playback/MIDIClock.h"
#include "Playback/MainPlayer.h"
#include "termanip.h"



#define FALSE 0
#define TRUE 1



FILE *file_ptr;
char version[] = "v2.0.9";
char *title;
// char midiPath[260];
bool isMidiPath = FALSE;
bool isSfList = FALSE;


char cli_help[] =
"Play a midi file in real time using OmniMIDI\n"
"\n\n\n"
"-i | --input </path/to/midi/file.mid>\n"
"-cp\n\n"
"-sm | --show-meta\n"
"Hide meta text events\n\n"
"\n"
"\n"
"--custom-sf-list <path/to/SoundfontList.json>\n"
"Use a different soundfont list other than the OmniMIDI's default list.\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n";






int main(int argc, char *argv[])
{
    printf("ConMIDI %s\n\n", version);


    
    if (argc > 1)
    {
        int mode = 0;
        for (int i = 1; i < argc; i++)
        {
            switch (mode)
            {
            case 0:
            {
                char *read = argv[i];
                if (strcmp(read, "-cp") == 0 || strcmp(read, "--set-console-codepage") == 0)
                {
                    mode = 1;
                }
                else if(strcmp(read, "-h") == 0 || strcmp(read, "--help") == 0)
                {
                    printf("%s", cli_help);
                }
                else if(strcmp(read, "--no-ncurses") == 0)
                {
                    ncursesMode = FALSE;
                }
                else if(strcmp(read, "--custom-sf-list") == 0)
                {
                    isSfList = TRUE;
                    strcat(customSfList, argv[i + 1]);    
                }
                else if(strcmp(read, "-i") == 0 || strcmp(read, "--input") == 0)
                {
                    isMidiPath = TRUE;
                    printf("MIDI Path: %s\n", argv[i+1]);
                    strcat(midiPath, argv[i+1]);
                }
                /*
                else if (strcmp(read, "-hm") == 0 || strcmp(read, "-hidemeta") == 0)
                {
                    for (int a = 0; a < 10; a++)
                    {
                        metaAllow[a] = FALSE;
                    }
                }
                */
                else if (strcmp(read, "-sm") == 0 || strcmp(read, "--show-meta") == 0)
                {
                    for (int a = 0; a < 10; a++)
                    {
                        metaAllow[a] = TRUE;
                    }
                }
                else if (strcmp(read, "-em") == 0)
                {
                    mode = 2;
                }
                else if (strcmp(read, "-dm") == 0)
                {
                    mode = 3;
                }
                // Useless
                else if (strcmp(read, "-fps") == 0)
                {
                    showFpsOutsideLag = TRUE;
                }
                break;
            }
            case 1:
            {
                unsigned int b;
                sscanf(argv[i], "%u", &b);
                mode = 0;
                break;
            }
            case 2:
            {
                unsigned int b;
                sscanf(argv[i], "%u", &b);
                if (b > 9)
                {
                    err_log(1, "CLI Error, -em must not exceed 9! (current value: %d)", b);
                }
                metaAllow[b] = TRUE;
                mode = 0;
                break;
            }
            case 3:
            {
                unsigned int b;
                sscanf(argv[i], "%u", &b);
                if (b > 9)
                {
                    err_log(1, "CLI Error, -dm must not exceed 9 (current value: %d)", b);
                    exit(0);
                }
                metaAllow[b] = FALSE;
                mode = 0;
                break;
            }
            }
        }
    }
    
    // This was used to set the console title on windows
    title = concat("ConMIDI ", version);
    prgTitle = title;
    // Check for sound engines
    Sound_Setup();

    
    // Start sound selection if more than one sound engine is available otherwise auto load only available engine
    // Sound_Init(1);
    
    // Apply custom sounsfont list from CLI Options
    if(isSfList)
    {
        info_log("Soundfont list path: %s", customSfList);
        KDMAPI_LoadCustomSoundFontsList(customSfList);
    }

    Sound_Init(1);    

    // File path input
    // char path[260];
    // char fixedPath[260];
    // Not the proper way to do that
    //
    /*
    while (TRUE)
    {

            memset(path, 0, sizeof(path));
            printf("\nEnter file path: ");
            scanf("%260[^\n]", path); // UUUuhhhhh so unsafe...
            fflush(stdin);
        
        removeSymbol(path, '\"', fixedPath);
   }
*/
        if(isMidiPath == TRUE)
        {
          if (access(midiPath, F_OK) == -1)
          {
              err_log(1, "\"%s\" Does not exists !");
          }
          else
          {
              unsigned int bufSize = 64;
              info_log("Loading MIDI File...");
              LoadMIDI(midiPath, bufSize);
          }
        }
    // endwin();
    return 0;
}
    
