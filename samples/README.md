# Samples

  ![SWEngine Logo](/docs/images/swenginesdk.jpg)

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



