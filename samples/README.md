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
![Cursor](/docs/images/samples/cursor.jpg)

### Camera Control
![Camera Control](/docs/images/samples/camcontrol.jpg)

### Audio Play


### GLSL

![GLSL Bloom](/docs/images/samples/glsl_bloom.jpg)
![GLSL DiognalBlur](/docs/images/samples/glsl_diognalblur.jpg)
![GLSL Disabled](/docs/images/samples/glsl_disabled.jpg)
![GLSL Edge Detection](/docs/images/samples/glsl_edgedetection.jpg)
![GLSL Emboss](/docs/images/samples/glsl_emboss.jpg)
![GLSL Inverted](/docs/images/samples/glsl_inverted.jpg)
![GLSL Multiplier](/docs/images/samples/glsl_multiplier.jpg)
![GLSL Sampling Coord](/docs/images/samples/glsl_samplingcoord.jpg)

![GLSL Sampling Coord Extended](/docs/images/samples/glsl_samplingcoordex.jpg)

![GLSL Sharpen](/docs/images/samples/glsl_sharpen.jpg)

### Rendering Target



### Capture Screen Shot


## Game Library Usage

### Animator

### Interpolator

### Loop Movement


## GUI Library Usage

### Property Window

### Simple Window

## Service Library Usage

### Display Mechanism

### Culling Operations

### Control Object Visibilities

### Layer Mechanism

### Simple Persist App

### Writing Application

### Physiscs World Application

### Physiscs World With Texture

### Physiscs World With Box2D Renderer 


## Math & Physics

### Sierpinski Triangle

### Simple Plots



## Visual FX

### Glow

### Shadow

### Fade In-Out

### Metaball

### Metaball2

### Metaball3

### Cloud FX with Perlin Noise

### Particle System Editor

### Painting Spiral
![Painting Spiral](/docs/images/samples/paintspiral.jpg)

## Games

### Snake
![Snake](/docs/images/samples/snake.jpg)

### PaintBook
![Paintbook](/docs/images/samples/paintbook.jpg)
