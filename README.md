# MassiveAttack

What started out as a MonoGame using my 2k16 SOA turned into a return to using OpenGL with C++.  The version 1.0 goal is to provide a cross-platform online deathmatch akin to a 90s shooter.

##Areas to work on
- WebAPI with a Redis and SQL Server backend using ASP.NET Core (C#)
- OpenGL/C++ cross-platform client
- WPF frontend to handle client updates and configuration (will consider GTK# for non-Windows clients)

##Compile Instructions
- Client requires SDL 1.2 and SDL Image 1.2.1 as of 12/31/2016. For those on Windows, the developer binaries on www.libsdl.org does not natively support VS 2015 so you will need to download the source of both and recompile the lib files
- Frontend for Windows requires .NET 4.6.2
