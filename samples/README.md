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

   * Display Mechanism
   * Culling Operations
   * Control Object Visibilities
   * Layer Mechanism
   * Simple Persist App
   * Writing Application
   * Physiscs World Application
   * Physiscs World With Texture
   * Physiscs World With Box2D Renderer 


### Math & Physics

   * Sierpinski Triangle
   * Simple Plots

### Visual FX

   *   Glow
   *   Shadow
   *   Fade In-Out
   *   Metaball
   *   Metaball2
   *   Metaball3

### Cloud FX with Perlin Noise

   * Particle System Editor
   * Painting Spiral

### Games
   * Snake
   * PaintBook


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



### Transparency


### Time Dependent Movement


### Image Rendering


### Image Clip


### Sprite Rendering

### UV Scrolling

### Text Rendering

### Point Sprite Rendering


### Listen Keyboard


### Listen Mouse

### Cursor

### Camera Control

### Audio Play

### GLSL

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


## Games

### Snake

### PaintBook
