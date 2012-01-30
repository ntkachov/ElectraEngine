# Electra Engine for Android 
##Example of OpenGL 2.0 inside the NDK

This was a few weeks worth of work to try my hand at a 3D c++ rendering engine for android.
It currently supports textures, specularity. There are no plans to finish developing this. 


Feel free to use it as a learning tool for getting started with android 3d. I really couldn't 
find too many things online about how to make a 3D rendere with android using the NDK so I wrote this
using some Obj C tuts and managed to get it running on android.

Requires NDK.

Code quality is crap and documentation is non-existant so ill do my best to explain as much as I can here.
Hopefully this will be enough to get you going. Also this code isn't made to be copy-pasted but more 
as a learning resource for people trying to learn NDK/C++/GL2

##Touch Handleing

Electra uses the android native touch handleing to pass screen coordinates every frame down to 
the NDK/C++. 

Inside GL2JNIView.java -> Renderer class -> onDrawFrame() the it passes the rotate vec and the translate vector to the ndk
It gets these vectors from the GL2JNIView.Java->onTouchEvent() when it passes any touch events to the camera class.

Once the touches are converted into vectors they are handed off into C++ and the C++ handles them inside glcode.cpp. The function setUniformMVP converts the vectors into a model view projection matrix that is used within the whole scene. Though in this case the models are done seperatly and ONLY the projection and view matrix is calculated.

##Model Loading

Electra supports loading of different models (currently only in .obj, with triangulation, normals, and texture coords). The model loading happens in Java (see ModelLoader.java) and sends the raw data to the NDK.

The arguments that the Model loader needs are as follows:
-A List of verticies that have 3 floats per vert
-A list of normals that have 3 floats per vert
-A list of UVs that have 2 floats per vert
-The number of verticies * 3 that were passed in. (aka the number of vert floats we passed in)
-The poly groups that each vert belongs to
-The rotation OF THE WHOLE MODEL (3 floats)
-The translation OF THE WHOLE MODEL (3 floats)

All of these lists should be synced. That is to say that verts[1] corresponds to UVs[1], Normals[1], polygroups[1]. 

Once passed down to the JNI Scene/Model.cpp handles the rest and generates the propper vertex buffers.
The OnDraw method of the model class is called by the Scene to draw the whole model.

##Scene Management.
A very simple scene manager exists to load a model at a specific point and rotation. 
It initializes the scene and thats about it.
You can see an example of a simple scene under Assets/scene.scene
basically the file format of the scene is defined under src/scene/ModelDef.java

The scene gets passed into the JNI and is handled by Scene/Scene.cpp where we can add models and lights.

##Rendering.

Once everything gets loaded into the engin we Render by calling scene.draw(); That calls the individual draw calls of each model. 

I'm not going to go into detail about how to render in OpenGL in a readme. take a look at the draw code and a few tutorials on opengl to get a feel for how rendering happens. OpenGL is more of a standard than anything else so OpenGL ES 2.0 is going to be faily close to OpenGl 2.0.

##Lighting.

I was in the middle of recreating the lighting engine when I stoped working on this project. 
Lighting works as it is inside the fragshader (under assets/frag.shader) 

I will leave it as an excersize to the reader as to how to hook up the lights to the scene. It's not too much work.


###Final Thoughs.
Take everything writen here with a bucket of salt. This project was more of my excersize in opengl es 2.0 than it was a full tutorial or even a project to be extended off but with so little out there in the way of android ndk i figured i would post this as a bace starting block for anyone wanting to take a look at how I did it.  
I wrote some tutorials on my blog thedailynerd.com you can take a look some more in depth explinations of rendering and lighting there.  
