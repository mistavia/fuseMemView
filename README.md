# fuseMemView
A simple ncurses-based memory view for developing with the Fuse emulator

This is a c-based project for running on Unix-based computers. It should compile on all flavours of Unix that support the GLIB, GIO and NCURSES libraries, although it's only been tested so far on Ubuntu.

** Note this first version only supports the memory map of the 48k Spectrum and as it's an alpha release, it's not been tested properly at all!

# Compiling
The project should compile pretty easily using the make command, but you will need the glib-2.0, gio-2.0 and ncurses libraries to be installed.

# How it works
This tool essentially receives 6 character TCP-based packets from a modified FUSE application (see below). The bytes (all sent as hex chrs) are a 2-byte memory location, followed by a single byte value. As the packet is sent as a text representation (for ease of debugging), each representation of a byte actually takes 2 characters - hence a change to the first byte of the screen memory (16384) would be sent as '4000XX', where XX is the value.

#Connecting
This version only supports connections on the same machine (127.0.0.1) and hasn't been tested running across a network, but you could in theory by changing the IP address in both socket.c and socketFuse.c and compiling both applications.

# Setting up FUSE
To make this work with FUSE, you will need to download a copy of the FUSE source code from https://sourceforge.net/projects/fuse-emulator/files/fuse/. It is recommended that you ensure you can build the project before making any modifications - note you will need the libspectrum libraries to compile the source code (see the readme on the sourceforge page).

Add the source files socketFuse.c and socketFuse.h to the project and then open memory_pages.c and add an #include for socketFuse.h and then find the writeByte function (it's about half-way down the code). After the line which reads 'writebyte_internal( address, b );', add the line 'socket_send_packet(address, b);'. This will send the byte via TCP.

# Performance
This packet does place a very small overhead on the FUSE emulator, but it shouldn't be noticeable. If you do see a slight slow-down then up the emulator of the CPU from 100% slightly.

# Using
There are two screens available, which are accessed via their initial letter: [m]emory and [w]atch:

[m]emory
This shows a complete memory map on the left-hand side of the various memory blocks available for the currently selected machine. Pressing the <tab> key will cycle through these blocks. To the right of the map is a full memory map for the selected block. You can navigate around the map using the arrow keys, or press the +/- keys to jump a full screen up and down. Pressing the [t] key will add or remove a watch toggle for the byte the cursor currently has highlighted. As you navigate around the memory details of the selected byte are shown on the left below the memory map. These details include the selected location (in hex and decimal), the current value (in hex, decimal and binary), an indication of if a watch is toggled on and if the value has changed.

[w]atch
This shows the last 1024 changes made to a specific byte. In order to see a watch you must have toggles a byte on in the memory screen - you can check if a toggle is on by moving to the byte and checking the flag on the left - watched bytes also appear in yellow on the memory map. On the left you will see a list of watched bytes and their current value (in hex and decimal), these can be cycled through using the <tab> key. The history of that byte will be changed for the currently selected watch. Note that the watch only updates if the value is different to the last watch value and if the watch list reaches 1024 then it will reset to zero.

[q]uit
To exit the app, press the q button - note it doesn't offer any confirmation at the moment so be careful!

# ToDo
- Implement all Spectrum machine types and have the app auto detect which is detected in Fuse
- Confirm on quit
- Option to save/export data
