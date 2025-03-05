# ConMIDI


This fork of ConMIDI uses the new cross platform [OmniMIDI](https://github.com/KeppySoftware/OmniMIDIv2) library which is in development.

ConMIDI is a lightweight console MIDI player, being the successor to [SharpMIDI v2.4.1](https://github.com/EmK530/SharpMIDI/releases/tag/v2.4.1).

Written in C to achieve insane performance. Able to achieve around 100M NPS with OmniMIDI on my Ryzen 7 1700 at 3.75GHz

## Contributions

I am a new C programmer, so there can very well be some bad practices used in this program. If you spot anything, feel free to report it!

## Prerequisites

Recommended use with this MIDI player for performance is the [OmniMIDI](https://github.com/KeppySoftware/OmniMIDI/releases) synth.

If you don't have OmniMIDI, you can choose the "WinMM" device.

## New Updates:
- Added -i flag for better midi file path input
- Implemeted debuging functions

## How to build

Install xmake on your environment, configure the project and build it

````
xmake f
xmake
````

## Credits

#### Contributors:

[Lurmog](https://github.com/Lurmog) (File dialog support & Adding header files to fix my terrible code)
