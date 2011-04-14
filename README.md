xEngine
==================

[xEngine] is "wheel-invent" attempt to write multi-platform 3D game engine in C++, which supports modern graphical API, like DirectX 10 and OpenGL 3.4.

Generate project files with [Premake][1]

Graphical API
-------------
   * DirectX 10
   * OpenGL 3.4
   
Multi Platform
-------------
   * Windows
   * Linux
   
Dependencies
-------------
 [pcre][2] Perl Compatible Regular Expressions

Bad solutions
-------------
 * Using pImpl idiom wasn't good idea
 * Selfmaded containers, test-system is fun to write, usefull for learning, but useless in fact

   
[1]: http://industriousone.com/premake "Premake"
[2]: http://www.pcre.org/ "PCRE"