#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <ncurses.h>
#include <pthread.h>

#include "Essentials.h"
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
char midiPath[260];
bool isMidiPath = FALSE;


char cli_help[] =
"Play a midi file in real time using OmniMIDI\n"
"\n\n\n"
"-i | --input </path/to/midi/file.mid>\n"
"-cp\n\n"
"-sm | --show-meta\n"
"Hide meta text events\n\n"
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
"\n"
"\n"
"\n"
"\n"
"\n";




void* startMidiPlayer(void* arg) {
    info_log("Started midi player. Thread: %d\n", *(int*)arg);
     
    unsigned int bufSize = 64;
    info_log("Loading MIDI File...");
    LoadMIDI(midiPath, bufSize);
    return NULL;
}



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
    
    // Idk what's the use of this, it seems useless
    title = concat("ConMIDI ", version);
    prgTitle = title;
    // Check for sound engines
    Sound_Setup();

    
    // Start sound selection if more than one sound engine is available otherwise auto load only available engine
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
              err_log(0, "\"%s\" Does not exists !");
          }
          else
          {

              int t1 = 1;
              int t2 = 2;
              
              // Run the key listener function on a separated thread so it won't mess up with the player thread.
              pthread_create(&keyHandle, NULL, keyListener, &t1);
              pthread_create(&midiPlayerThr, NULL, startMidiPlayer, &t2);
              
              pthread_join(midiPlayerThr, NULL);
              pthread_join(keyHandle, NULL);

              
              // unsigned int bufSize = 64;
              // info_log("Loading MIDI File...");
              // LoadMIDI(midiPath, bufSize);
          }
        }
    // endwin();
    return 0;
}
