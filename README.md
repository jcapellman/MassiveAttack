# MassiveAttack

What started out as a MonoGame using my 2k16 SOA turned into a return to using OpenGL with C++.  The version 1.0 goal is to provide a cross-platform online deathmatch akin to a 90s shooter.

##Components
- Game Server using SDLnet and C++ coupled with Redis
- Master Game Server REST Service NodeJS with Redis
- OpenGL/SDL/C++ cross-platform client
- WPF Level Editor

##Compile Instructions
- Client requires SDL 1.2 and SDL Image 1.2.1 as of 12/31/2016. For those on Windows, the developer binaries on www.libsdl.org does not natively support VS 2015 so you will need to download the source of both and recompile the lib files
- Level Editor for Windows requires .NET 4.6.2

##Supported Client Platforms
- Windows 7, 8, 8.1, 10, Server 2008/2008R2/2012/2016
- IRIX 6.5.22 (Machines with Texture Mapping support are recommended such as an O2, Octane MXE/Vpro, Fuel, Tezro)
- Mac OS X (PPC)
- OpenSuse (x86)

However other platforms should compile and run given the usage of SDL 1.2 and OpenGL 1.1 to promote compatibility.

##Supported Server Platforms
- OpenSuse (x86/x64)
- FreeBSD (x86/x64)

Windows currently does not have a fairly recent Redis port so while the game server can run, you would need to use another platform that supports a recent version of Redis.

##Internal Testing
I plan to use my Razer Blade Stealth (late 2016), SGI Fuel (V10) and Apple G5 Quad to test.
