# MassiveAttack

What started out as a MonoGame using my 2k16 SOA turned into a return to using OpenGL with C++.  The version 1.0 goal is to provide a cross-platform online only game.  The focus will be on over the top fun with friends or against other gamers.
##Components
- Game Server: C++ coupled with Kafka
- Master Game Server: REST Service NodeJS (TypeScript) with Redis and Kafka
- User Server REST Service: NodeJS (TypeScript) with Redis and Kafka
- Game Client: OpenGL/SDL/C++ cross-platform client

##Compile Instructions
- Client requires SDL 2 and SDL Image 2

##Tested Client Platforms
- Windows 10

However other platforms should compile and run given the usage of SDL 2 and OpenGL 1.1+ to promote compatibility.

##Supported Server Platforms
- OpenSuse (x86/x64)
- FreeBSD (x86/x64)

Windows currently does not have a fairly recent Redis port so while the game server can run, you would need to use another platform that supports a recent version of Redis.

##Internal Testing
I plan to use my Razer Blade Stealth (late 2016) to test primarily
