# AudioBox
An app for VJ's that attempts to detect the beat of music in realtime

AudioBox was created back in the 2000's when I was an active VJ.  I very much liked the ability to trigger video clips synchronised to the beat and wondered if it would be possible to have a small helper application that monitored an incoming live music signal, detected the beat, and sent a MIDI signal to synchronise to the music automatically.

This is what AudioBoxBaby does - an almost commercial project that I never fully released because - it turns out - that accurate beat detection is difficult.  Once you get the algorithm tuned for a certain style of music, it often performs less well on other kinds.  Basically, it's a tinkering nightmare and I spent so many weeks working on this, tweaking and testing and never really satisfied with the result, which is why I never progressed with it.

The full version of AudioBox was going to send out all sorts of realtime MIDI data based on various analysis of the incoming signal including FFT bands and the like.  AudioBoxBaby is the most basic version of the AudioBox family, with 'VJ Junior' and 'VJ Pro' versions planned that had more signals.  Almost all the signals are in the code, so if you want to externalise them they are there.

The version here is the most up to date (I believe) copy I could find on my backups.  It is dated April 1st 2009.  I haven't tried compiling it - it's here because Meier Hans asked for it and it's better out in public than rusting on my hard drive.

I haven't even tried to compile it, but all the files should be there.  It's written in C++ using the wxWidgets framework (before I switched over to Qt some years later), which you can find at https://www.wxwidgets.org/

I used an app called DialogBlocks to create the interface, which I think is still available at http://www.dialogblocks.com/

Am pretty sure the project files are Visual Studio 2008.

There is a page on my website about it:

https://www.bigfug.com/software/audiobox/

I'm happy to answer questions about the code if you get stuck.
