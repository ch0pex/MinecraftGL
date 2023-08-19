# C++ and OpenGL Minecraft Project

This project is an implementation of the popular game Minecraft using the C++ programming language and the OpenGL graphics library. The main objective is to recreate the original game reforcing my knownledge in OpenGl and recreate the experience using my own implementations and algorithms. For educational purposes only. (Work in progress)

Some screen captures of the actual state of the project! 
It could not look so spectacular but there are many things happening there under the hood. Frustum culling, deltaTime , basic diffuse lighting, world_ building optimizations, etc.

![image](https://github.com/ch0pex/MinecraftGL/assets/78793330/81935146-e157-44fa-a4ee-3d6255a87131) 
Separete shaders, for solid and water. 
![image](https://github.com/ch0pex/MinecraftGL/assets/78793330/2ad924db-d608-4459-964a-a11e4ac353d0)
World height map is still very basic, will implement noise map generator. 
![image](https://github.com/ch0pex/MinecraftGL/assets/78793330/4c819ee9-e407-49a4-8b56-a8d993271a38) 
First, stone is generated following a height map, then the corresponding stone is replaced by soil and, finally, water is added to 60 blocks high. 
![image](https://github.com/ch0pex/MinecraftGL/assets/78793330/8a62a0cc-5cd3-480d-b3a4-2b52f9cb999a)
The inner faces are neither constructed nor rendered, fps 🚀
