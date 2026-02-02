this was build with the v142 toolset, so use VS2019 to build it (you can use VS2022, so long as you install the right toolset from microsoft)

won't build without first extracting the dependencies into this directory (if you're curious I'm using SDL3 and GLEW)

my implementation of GLSL doesn't work at this point, will be working on that into the summer

if there's a linker error, just build the library (Alkali) before the executable (Toronto)

to be safe, check the log incase there's a memory leak, I should have fixed it but you never know...