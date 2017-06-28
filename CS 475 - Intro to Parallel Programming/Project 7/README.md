Project #7A

OpenCL / OpenGL Particle System

Use OpenCL and OpenGL together to make a cool particle system

1. Design your 3D environment (have at least two "bumpers" in it for the particles to bounce off of. Each bumper needs to be geometrically designed such that, given a particle's XYZ, you can quickly tell if that particle is inside or outside the bumper)
2. Create OpenGL buffer objects to hold the particles' XYZW positions and RGBA colors as an array-of-structures
3. Perform the same array multiply as in #1, but this time with a reduction, benchmark it against input array size
4. Create a C++ array-of-structures to hold the particles' XYZ velocities
5. Create two OpenCL buffers from the position and color OpenGL buffers
6. Vary the total number of particles and measure the performance

The program can be executed by opening the solution in Visual Studio or simply running the executable.

