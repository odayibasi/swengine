# Samples

  ![SWEngine Logo](/docs/images/swenginesdk.jpg)

## Topics

### Basic Library Usage

 * [Simple Application](#simple-application)
 * [Primitive Rendering](#primitive-rendering)
 * [Primitive Rendering Performance](#primitive-rendering-performance)
 * [Coloring](#coloring)
 * [Rotation](#rotation)
 * [Transparency](#transparency)
 * [Time Dependent Movement](#time-dependent-movement)
 * [Image Rendering](#image-rendering)
 * [Image Clip](#image-clip)
 * [Sprite Rendering](#sprite-rendering)
 * [UV Scrolling](#uv-scrolling)
 * [Text Rendering](#text-rendering)
 * [Point Sprinte Rendering](#point-sprite-rendering)
 * [Listen Keyboard](#listen-keyboard)
 * [Listen Mouse](#listen-mouse)
 * [Cursor](#cursor)
 * [Camera Control](#camera-control)
 * [Audio Play](#audio-play)
 * [GLSL-OpenGL Shader Language](#glsl)
 * [Rendering Target](#rendering-target)
 * [Capture Screenshot](#capture-screen-shot)
  
### Game Library Usage

  * [Animator](#animator)
  * [Interpolator](#interpolator)
  * [Loop Movement](#loop-movement)
  
### GUI Library Usage

   * [Property Window](#property-window)
   * [Simple Window](#simple-window)

### Service Library Usage

   * [Display Mechanism](#display-mechanism)
   * [Culling Operations](#culling-operations)
   * [Control Object Visibilities](#control-object-visibilities)
   * [Layer Mechanism](#layer-mechanism)
   * [Simple Persist App](#simple-persist-app)
   * [Writing Application](#writing-application)
   * [Physiscs World Application](#physiscs-world-application)
   * [Physiscs World With Texture](#physiscs-world-application)
   * [Physiscs World With Box2D Renderer](#physiscs-world-with-box2d-renderer) 


### Math & Physics

   * [Sierpinski Triangle](#sierpinski-triangle)
   * [Simple Plots](#simple-plots)

### Visual FX

   *   [Glow](#glow)
   *   [Shadow](#shadow)
   *   [Fade In-Out](#fade-in-out)
   *   [Metaball](#metaball)
   *   [Metaball2](#metaball2)
   *   [Metaball3](#metaball3)

### Cloud FX with Perlin Noise

   * [Particle System Editor](#particle-system-editor)
   * [Painting Spiral](#painting-spiral)

### Games
   * [Snake](#snake) 
   * [PaintBook](#paintbook)


## Basic Libary Usage

### Simple Application
Basic game mechanism is same for all games.

 * Game initialization function is called first. This function sets up game engine and engine defaults.

 * Game loop function calls every screen refresh. This function executes all game logic. Rendering, Player Interaction, Music, AI, Collision Detection operation. So It's important to balance CPU usage and Time consuming. İf operations takes too long time then your frame rate will be drop.
 
 * Game exit function called before game exit. This function kill engine and release allocated resource.

SWEngine simplifies these operations. It abstracts these mechanism so you don't worry about these things. Below example shows you how can we create simple game mechanism.

  [CoreAPI_SimpleApplication](https://github.com/odayibasi/swengine/tree/master/samples/CoreAPI_SimpleApplication)

  ![Simple Application](/docs/images/samples/simpleApplication.jpg)

### Primitive Rendering

This example shows basic primitive rendering. In SWEngine 5 types of primitive defined. You can use for immediate rendering. It's simple but I don't recommend when you have lots of primitive to render. You should use ArrayList, DisplayList or VBO(Vertex Buffer Obj)

SWEngine defined primitives;
* Point
* Line
* Rectangle
* Elips
* Polygon

[CoreAPI_PrimitifRendering](https://github.com/odayibasi/swengine/tree/master/samples/CoreAPI_PrimitifRendering)

![Primitive Rendering](/docs/images/samples/primitiverendering.jpg)

### Primitive Rendering Performance
This example shows basic primitive rendering. In SWEngine 5 types of primitive defined. You can use for immediate rendering. It's simple but I don't recommend when you have lots of primitive to render. You should use ArrayList, DisplayList or VBO(Vertex Buffer Obj)


[CoreAPI_PrimitifRendering](https://github.com/odayibasi/swengine/tree/master/samples/CoreAPI_PrimitivePerformanceTest)

![Primitive Rendering Performance](/docs/images/samples/performancetest.jpg)


### Coloring
In previous sample we draw basic primitives. Now we want to add background and primitive color.

[CoreAPI_Coloring](https://github.com/odayibasi/swengine/tree/master/samples/CoreAPI_Coloring)

![Coloring](/docs/images/samples/coloring.jpg)


### Rotation
Sometimes we need to rotate primitives. We have two choice.
 * __First technique:__ We calculate edge points according to rotation value and give engine these calculated vertex values. This solution is a bit hard to use.
 * __Second technique:__ We set a rotation value when drawing primitives. SWEngine use this technique. This technique is easy and flexible. You could also give extra weight point for rotation. And SWEngine works with degrees. If you use radians you must convert degrees first. swMath api provides conversion functions between degrees and radians.  

![Rotation](/docs/images/samples/rotation.jpg)


### Transparency
We succeed primitive drawing with color. Now we expand drawing capability and draw transparent objects. Transparent objects can be drawn using OpenGL blending function( glBlendFunc(SRC_FACTOR , DST_FACTOR) ). SRC_FACTOR and DST_FACTOR are predefined OpenGL constants used for blending operation. These can be constants like GL_ONE , GL_SRC_ALPHA etc.. look for your opengl guide for the complete list of this constants and their meanings. SWEngine graphics api provides an abstraction layer on OpenGL. So you don't need to learn OpenGL Blending functions.

![Transparency](/docs/images/samples/transparency.jpg)


### Time Dependent Movement
Previous example we explain how to draw color and transparent primitives. But all of drawing are static. Now we add motion. We move,rotate and scale primitives. In Game Loop function we change position,rotation or size(pos.x+=10 rot+=5) But we have a little problem. Game Loop function call frequency equals to screen refresh. In different PC it will changes. We must fixed refresh rate or attach timer.

Below example we attach movement with SWTimer. In game initialization we define timers.

![Time Dependent Movement](/docs/images/samples/transparency.jpg)


### Image Rendering

Loading image files, bind OpenGL and set texture properties is'nt simple operations. SWEngine simplifies these operations and provides clear API for image rendering. It supports 24/32 bit TGA files

![Image Rendering](/docs/images/samples/imgrendering.jpg)


### Image Clip

Sometimes working with lots of small image files cause performance and management problems. Because lots of small images will increase file access and OpenGL bind operations. The solution of this problem is combine images in one image file and clip when required. Clipping operations executes in GPU so it doesn't take extra cpu time.

Below example shows you how to clip iconset.

__Step1:__ Find count of images in X axis and Y axis
const static int XGRID_SIZE=20;
const static int YGRID_SIZE=14;

__Step 2:__ Find the index of subImage and construct source rectangle. (Assumption:Grid size is same)
swMathSourceCalculate(&source,XGRID_SIZE,YGRID_SIZE,xIndex,yIndex);

__Step 3:__ Selected cell/grid will be drawn to screen.
swGraphicsRenderImg2(imgID,&target,&source);

![Image Clip](/docs/images/samples/imageclip.jpg)


### Sprite Rendering

Animated images are the most important part of 2D Game. All actor, vehicle and other item's behaviour can easily shown with Sprite. Sprite mechanism is very simple technique.For example: Character running animation compose of 20 frame of images. In a defined folder these images consist. Now we access these folder. Navigate all files in folder. Load TGA files and bind with OpenGL. SWEngine do this operation only one function

_spriteID=swGraphicsCreateSprite("XenRunning\\");_

![Sprite Rendering](/docs/images/samples/spriteRendering.jpg)


### UV Scrolling
In Forum Grinder asked me about how can we scroll texture on SWEngine. I show him a simple hack but it's not the real solution. After that I add this capability to SWEngine. I add UVScrolling function to SWGraphics API.

_void swGraphicsSetImgUVScrollable(int imgID,bool bEnabled); //Enable or Disable UVScrolling Capability_
_void swGraphicsSetSpriteUVScrollable(int spriteID,bool bEnabled);_
![UV Scrolling](/docs/images/samples/uvscrolling.jpg)

### Text Rendering

In SWEngine text rendering operation is very simple. First you must define font types. Font data holds the characters in a texture. This texture consist of 256 character which placed in 16x16 grids.

_fontID=swGraphicsCreateFont("Font.tga"); Rendering on screen swGraphicsRenderText(fontID,0,16,200,240,0,"string=%s int=%i float=%1.1f ","SkyWar",5,10.0f);_

![Text Rendering](/docs/images/samples/textrendering0.jpg)
![Text Rendering](/docs/images/samples/textrendering1.jpg)


### Point Sprite Rendering

This sample demonstrates how to use the OpenGL's ARB_point_sprite extensions to create point sprites. Point sprites are hardware-accelerated billboards, which are capable of being textured. Point sprites are ideal for creating high-performance particle systems because you only have to send a single vertex point or point sprite for each particle instead of four vertices for a regular billboarded quad.

SWEngine wraps upper tutorial codes in SWCore.dll. You can access the point sprite api from SWGraphics

![Point Sprite Rendering](/docs/images/samples/pointspriterendering.jpg)


### Listen Keyboard

In PC environment most important input device is keyboard This sample shows you how to listen keyboard keys.

### Listen Mouse

This sample shows how to listen mouse motion and mouse buttons states.
![Listen Mouse](/docs/images/samples/listenmouse.jpg)

### Cursor
How can we display cursor on Screen. How can we access cursor position

1. In Game windows cursor create an ugly display. We should hide windows cursor visibility. Set cursor=false in SWApplication

2. In Game we create our cursor. We define image or sprite cursor. And render to mouse position on screen.

3. You can access mouse position on swMouseState in SWInput api


![Cursor](/docs/images/samples/cursor.jpg)

### Camera Control
Similar to 3D games in 2D games need camera controls for move screen left,right,bottom and up directions. Platform games, side-scrolling shootem-up games and other games based on sliding screen different direction. SWEngine simplifies this operation with camera control functions.



![Camera Control](/docs/images/samples/camcontrol.jpg)

### Audio Play
Loading sound and music files. Trigger them when needed. SWEngine api provides sound fuctions for sound management.


### GLSL
What's GLSL ? Briefly GLSL is an high level languange over graphics card. It provides an abstraction layer on graphics card. If you want to use GLSL codes in your application. you must load, compile and bind to OpenGL. SWEngine simplifies these steps.

#### Sample Usage
GLSL code in SWEngine
_diognalblur=swGraphicsCreateGLSLShader("fixed.vert","diognalblur.frag");_

Pressing keyboard 1,2,3,4,5,6,7,8,9,0 keys actives different shaders.

 * 0=Disabled
 * 1=Diognal Blur
 * 2=Edge Detection
 * 3=Emboss
 * 4=Inverted
 * 5=Bloom
 * 6=Sharpen
 * 7=Multiplier
 * 8=Sampling Coord
 * 9=Sampling Coord Ex

I taked this shader examples from facewound web site. You can access shader details in this web site.

![GLSL Disabled](/docs/images/samples/glsl_disabled.jpg)
![GLSL DiognalBlur](/docs/images/samples/glsl_diognalblur.jpg)
![GLSL Edge Detection](/docs/images/samples/glsl_edgedetection.jpg)
![GLSL Emboss](/docs/images/samples/glsl_emboss.jpg)
![GLSL Inverted](/docs/images/samples/glsl_inverted.jpg)
![GLSL Bloom](/docs/images/samples/glsl_bloom.jpg)
![GLSL Sharpen](/docs/images/samples/glsl_sharpen.jpg)
![GLSL Multiplier](/docs/images/samples/glsl_multiplier.jpg)
![GLSL Sampling Coord](/docs/images/samples/glsl_samplingcoord.jpg)

![GLSL Sampling Coord Extended](/docs/images/samples/glsl_samplingcoordex.jpg)


### Rendering Target

In default, OpenGL renders the output back color buffer in framework and every screen refresh, front and back buffer switch. So last updates displayed on screen. If we want to change rendering target. For example want to render on a texture. What you do.

__OpenGL__
* glCopyTexImage2D
* PBuffer
* FBO(Frame Buffer Object) SWEngine uses this technique

In SWEngine
Define a Rendering Target. Switch to framebuffer -->rendering target. Render screen. Switch to rendering target -->framebuffer, Use rendering target as a texture object, Apply effects and transformation on this.


![Rendering on Texture](/docs/images/samples/renderingontexture.jpg)


### Capture Screen Shot
This sample shows how to capture screen.

## Game Library Usage

### Animator
In 2D games animated objects create by Sprite. But it's not adequate. You should also manage sprite image index. You listen timer and switch image index. The delay of switching operation defines animation speed. And end of sprite you want to return first image. Animator api develop for these purpose. Below example shows you how can animator api use.


![Animator](/docs/images/samples/animator.jpg)


### Interpolator

In Games motion will be define with speed, acceleration, torque etc.. But sometimes we don't want to calculate speed and acc. How can give motion another way. If we define start,end point and time. The objects automatic calculate it's speed. Interpolate. You can use this tecnique any type of value. For example alpha,x,y,width,height,rot, etc..)

_interpID=swInterpolaterCreate(0,1,10);_

### Loop Movement

In games or scene demo coder want to repeat motion or behaviour. SWValueModifier api simplifies these operations.

__For example__
* An item goes and comes between two place.
* Changing alpha value 0-1 range..
* Items rotation repeat
* Items size scale repeat.

## GUI Library Usage

### Property Window
SWPropertyWin= Bean Binding technique + Property Pane Widget

In samples or tools we need to change parameters. But it's harder to make gui all of this parameters. I think about. How can I simplfy. Then I implement very lite windowing system. It only supports INT,FLOAT,DOUBLE,ENUM. And easy to use and code.

__Features__
* Drag-Drop, Expand/Collapse, Scrollable Windowing System.
* You can easily bind parameters or add sub window to main window.
* It provides to control paramerters value. You can inc/decr parameters normal and quickly.
* Parameters changes directly reflect screen.

![Num Propeperty Win](/docs/images/samples/numpropwin.jpg)

### Simple Console

![Simple Console](/docs/images/samples/console.jpg)


## Service Library Usage

### Display Mechanism
First tecnique. Render objects front to back order. For example we make Breakout game. We write code similar below.

```c
void GameLoop(){
        displayBricks()
        displayBall()
        displayPlayer()
}
```
Second tecnique. We give display responsibilities to one component and this component controls layer order. But why we need this component. Why don't we use first tecnique. In small application first tecnique can be used. But in a big game project lots object exist and these object rendering order is serious work. Displaying mechanism component provides this abstraction so you don't worry about ordering. You only set layer then do'nt think anything about displaying.

![Display Manager](/docs/images/samples/displaymanager.jpg)

### Culling Operations
In one level 10 thousand item can be exist. If you will render all of them. It cause performance problem. The solution is filtering items which are outside screen(Culling). Basic you check item boundary in scenario region and if outside cull it. Boundary check for every item in your code is'nt good. SWEngine abstracts this function. You only set scenario region and item boundary. All checks and rendering operation makes in background.

Below example shows how tu use culling function in SWEngine SWDispManager. 2500 item exist but only 45 item rendered.

__DispCullingSupport__

_int swDispManagerAdd(void(*dispFunc)(void*), void *obj,boolean *bEnabled,swRect *rect,int *layer); //4th parameter rect=Boundary referance_

![Culling](/docs/images/samples/culling.jpg)

### Control Object Visibilities
If you want to hide an item on screen. You should write similar to below code.
```c
void GameLoop(){
     if(visible)
         displayItem();
}
```
If you use SWDispManager service you don't check item visibility. Becouse it's item properties. swDispManager checks visibility. swDispManagerAdd(xenDisplay,xen,&xen->bVisible,NULL,NULL); //3rd parameter visibility referance pointer.

![Hide Item](/docs/images/samples/hideitem.jpg)

### Layer Mechanism
In SWEngine there is no Z axis but have a layer mechanism.

swDispManagerAdd(defenderDisplay,defender,NULL,NULL,&defender->layer); 5th parameters is item layer referance. You can configure your layer with changing layer properties. You can take an item front or back.

Sample This example is extreme case. We walk defender around xen. In 3D it's simple operation. But in 2D you must make lot's of setting and calls

__About Code__
* In 3D define a path and move item on path.
* In 2D this operation is a bit harder.
* Create avoid and rotate sprite
* Move with avoid animation in two coordinate. Go..
* When defender access target point. Stop defender move and switch rotate animation
* At the end of rotation mirror defender.
* Resize defender. it will smaller when far away .
* At the end of resize set layer 1.
* Move defender to start point . (It will come back.)
* Resize.
* Rotate
* Mirror
* LOOP ...... I use SWInterpolater api for animated visual.


### Simple Persist App
In save operation for level editing or checkpoint, use below mechanism, SWPersistManager

### Writing Application
![Writing App](/docs/images/samples/writingapp.jpg)


### Physiscs World Application

![Physics World App](/docs/images/samples/physworldapp.jpg)


### Physiscs World With Texture

![Physics World Text](/docs/images/samples/physworldwithtexture.jpg)


### Physiscs World With Box2D Renderer 

![Physiscs World With Box2D Renderer](/docs/images/samples/physworldwithbox2drenderer.jpg)

## Math & Physics

### Sierpinski Triangle
I take this sample from Computer Graphics Using OpenGL. And you can take information from [wiki](#https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle)

![Sierpinski](/docs/images/samples/sierpinskitriangle.jpg)

### Simple Plots

This applications shows you how to draw a function. High school math

_f(x)=e-x.cos(PIx)_
![Simple Plots](/docs/images/samples/simpleplots.jpg)


## Visual FX

### Glow

This sample shows how to create glow effects. In real it's difficult but we have a change 2D. We can use a hack solution. We prepare an image with glow effect by photoshop filter and then use in game. [Photoshop GlowFX](#http://www.idigitalemotion.com/tutorials/glow.html). The disadvantage of this solution more photoshop operation and this glow is valid only spesific image (In short it's static)

![Glow](/docs/images/samples/glowfx.jpg)


### Shadow

In 2D Games shadow creation is simple than 3D. The only thing you must do is render the same objects with gray color and different orientation.

1. Sprite - (0,0,0,0.5) multiply color so the shadow color is halt transparent black color.
2. Sprite - (x+20,y+20,w*2,h*2) Light direction effects shadow coordinate and size.

![Shadow](/docs/images/samples/shadow.jpg)


### Fade In-Out

![FadeIn](/docs/images/samples/fadefx.jpg)
![FadeOut](/docs/images/samples/fadefx1.jpg)


### Metaball
It's an metaball implementation All process mades on CPU.

![Metaball](/docs/images/samples/metaball0.jpg)
![Metaball](/docs/images/samples/metaball1.jpg)

### Metaball2
Previous example we tell glow effect. We prepare with photoshop and render on screen. Now we use two textures with animated opposite direction. When they overlapped a glow effect will create.

![Metaball](/docs/images/samples/metaball2a.jpg)
![Metaball](/docs/images/samples/metaball2b.jpg)
![Metaball](/docs/images/samples/metaball2c.jpg)


### Metaball3

I met this sample in GameDev forum. Finger tells how to create Metaballs on GPU with Texture. Link to Forum Thread.

__Steps__
* Create Rendering Target( 32 bit RGBA 800x600)
* Set Blending Mode Additive
* Set color alpha value 0.45
* Render texture on rendering target
* Enable Alpha Test glEnable(GL_ALPHA_TEST)
* Set glAphaFunc(GL_GREATER,0.5) overlapped pixel.
* Render result on framebuffer
* At last you see. It'a very nice effect

![Metaball](/docs/images/samples/metaball3a.jpg)
![Metaball](/docs/images/samples/metaball3b.jpg)
![Metaball](/docs/images/samples/metaball3c.jpg)


### Cloud FX with Perlin Noise

After googling 2D Cloud rendering. I access Fluid Simulation and Perlin Noise tecnique. Below example shows you perlin tech on CPU Clouds With [Perlin Noise](#https://www.gamedev.net/tutorials/_/technical/game-programming/simple-clouds-part-1-r2085/)

### Particle System Editor
We need particle engine for creation of xenophobic game special fx. I search on Google and access Haaf 2D Game Engine and it's particle editor. I download it's source and apply on SWEngine. I do'nt want to put this code in SWEngine because I couldn't create high quality effects yet. I work on..

![Painting Spiral](/docs/images/samples/haafparticlesystem.jpg)


### Painting Spiral
![Painting Spiral](/docs/images/samples/paintspiral.jpg)

## Games

### Snake
Everyone knows snake game. It is very popular on phone. I try to develop on SWEngine. At first I design game
![Snake](/docs/images/samples/snake.jpg)

__Game Design__
1. Game area consist of 20x20 grid.
2. Snake consist of nodes. Every nodes size equals grid size.
3. Snake could move East,West,South,North direction.
4. Snake moves to selected direction with constant speed.
5. Snake speed will increase when snake takes bonus.
6. Snake control pad is keyboard's Left,Right,Up,Down keys.
7. Bonus increase player score.
8. Snake nodes will increase when snake takes bonus.
9. After bonus taken a new bonus will be created on random position.
10. Snake will be die if it intersect boundary of game area or it's tail



### PaintBook
PaintBook is an simple paint game. Paint picture with different color.

1. First we need an image. I download a sample image from net.
2. After that we process image and throw image data to color buffer (I wrote simple api for image processing SWImgBuffer)
3. And at last implement a boundary fill algorithm for painting (Big picture this tech cause stack over flow exception)
![Paintbook](/docs/images/samples/paintbook.jpg)
