#SWEngine
========

SWEngine is a next generation 2D Game API on Windows OS (XP, Vista) . The API’s primary purpose is to allow developers high level access to game domains so they don’t need to learn lots of game development details..

* SWEngine is a free 2D Game Engine for C/C++ developers
* SWEngine is a powerful library which provides high level abstraction over Game Concepts;
  * Application Framework (Application Settings, Game Loop, Time Synchronization)
  * Display Mechanism (Renderer, Layer Mechanism, Culling, Camera Control, GPU Programming, Item Display Control)
  * Audio Mechanism (Sound and Music Controls)
  * User Interaction Handling (Keyboard, Mouse, GamePad support)
  * Resource Handling (TGA, Shader and music files management)
  * Physics Mechanism (Fluid Simulation, Particle Systems, Rigid Body Simulation)
  * Game Helpers (Animators, Compositors, Sprite, Behavior Controllers, Paths)
  * Windowing System (Automatic Window Generation, Cursor, Toolbar..)
  * Utility Functions (String, Math, Formatters, etc..)

* SWEngine use next generation technologies in it's framework;
  * Win32 (Window, FileSystem, HighResTimer)
  * OpenGL, Glew, GLSL (Renderer)
  * DirectX (Input)
  * OpenAL(Audio, Music)
  
  
  ![SWEngine Overview](/docs/images/overview.jpg)



# Api Docs

Consist of 7 parts

* __SWTypes:__ Common data types defined (swPoint, swColor, swDimension,, swRect, swPolygon, swVec2, swArg)
* __SWUtil:__ Utility functions for games (swMath, swString, swLinkedList, swStack, swIntersection, swLogger, swTimer)
* __SWCore:__ It's the core part of SWEngine. It contains basic functions for game development (swGraphics, swAudio, swInput, swSystem, swFileSystem, swImgBuffer)
* __SWServices:__ It provides high level services for game mechanism (swDispManager, swExecManager, swInteractionManager, swPersistManager, swScheduledManager, swPhys, swMousBehaviour, swKeybBehaviour, swDSL)
* __SWGame:__ Game component's behaviour controls (swAnimator, swLinker, swInterpolator, swValueModifier)
* __SWGui:__ Gui components and functions (swNumPropWin, swConsole)
* __SWEngine:__ Initialize and Setup application (swEngine, swApplication)


## swPoint
It holds x,y coordinate. You could define location or coordinate of something.
```c
//Structure
typedef struct _swPoint{
	float x;
	float y;
}swPoint;

//Functions
swPoint*   swPointCreate(float x,float y);
void       swPointDestroy(swPoint *point);
void       swPointSet(swPoint *p,float x,float y);
void       swPointCopy(swPoint *copy,swPoint *real);
swPoint*   swPointClone(swPoint *real);
bool       swPointEquals(swPoint *point1,swPoint *point2);
```


## swColor
It holds color values (Red,Green,Blue,Alpha). Color values defined [0,1] range.

```c
//Structure
typedef struct _swColor{
   float r;
   float g;
   float b;
   float a; 
}swColor;

//Functions
swColor*         swColorCreate(float r,float g,float b,float a);
void             swColorDestroy(swColor *color);
void             swColorSet(swColor *color,float x,float y,float w,float h);
void             swColorCopy(swColor *copy,swColor *real);
swColor*         swColorClone(swColor *real);

//Constant Colors
static swColor SWCOLOR_BLACK={0,0,0,1};
static swColor SWCOLOR_GRAY={0.5,0.5,0.5,1};
static swColor SWCOLOR_WHITE={1,1,1,1};
static swColor SWCOLOR_RED={1,0,0,1};
static swColor SWCOLOR_BLUE={0,0,1,1};
static swColor SWCOLOR_GREEN={0,1,0,1};
 
//Extends...
static swColor SWCOLOR_AIR_FORCE_BLUE={0.365f,0.541f,0.659f,1.000f};
static swColor SWCOLOR_ALICE_BLUE={0.941f,0.973f,1.000f,1.000f};
static swColor SWCOLOR_ALIZARIN={0.890f,0.149f,0.212f,1.000f};
static swColor SWCOLOR_AMARANTH={0.898f,0.169f,0.314f,1.000f};
static swColor SWCOLOR_AMARANTH_PINK={0.945f,0.612f,0.733f,1.000f};
static swColor SWCOLOR_AMBER={1.000f,0.749f,0.000f,1.000f};
static swColor SWCOLOR_AMBER_SAE_ECE={1.000f,0.494f,0.000f,1.000f};
static swColor SWCOLOR_AMETHYST={0.600f,0.400f,0.800f,1.000f};
static swColor SWCOLOR_APRICOT={0.984f,0.808f,0.694f,1.000f};
static swColor SWCOLOR_AQUA={0.000f,1.000f,1.000f,1.000f};
static swColor SWCOLOR_AQUAMARINE={0.498f,1.000f,0.831f,1.000f};
static swColor SWCOLOR_ARMY_GREEN={0.294f,0.325f,0.125f,1.000f};
static swColor SWCOLOR_ARSENIC={0.231f,0.267f,0.294f,1.000f};
static swColor SWCOLOR_ASPARAGUS={0.482f,0.627f,0.357f,1.000f};
static swColor SWCOLOR_ATOMIC_TANGERINE={1.000f,0.600f,0.400f,1.000f};
static swColor SWCOLOR_AUBURN={0.427f,0.208f,0.102f,1.000f};
static swColor SWCOLOR_AZURE_COLOR_WHEEL={0.000f,0.498f,1.000f,1.000f};
static swColor SWCOLOR_AZURE_WEB={0.941f,1.000f,1.000f,1.000f};
static swColor SWCOLOR_BABY_BLUE={0.878f,1.000f,1.000f,1.000f};
static swColor SWCOLOR_BEIGE={0.961f,0.961f,0.863f,1.000f};
static swColor SWCOLOR_BISTRE={0.239f,0.169f,0.122f,1.000f};
static swColor SWCOLOR_BLUE_PIGMENT={0.200f,0.200f,0.600f,1.000f};
static swColor SWCOLOR_BLUE_RYB={0.008f,0.278f,0.996f,1.000f};
static swColor SWCOLOR_BLUE_GREEN={0.000f,0.867f,0.867f,1.000f};
static swColor SWCOLOR_BLUE_VIOLET={0.541f,0.169f,0.886f,1.000f};
static swColor SWCOLOR_BOLE={0.475f,0.267f,0.231f,1.000f};
static swColor SWCOLOR_BONDI_BLUE={0.000f,0.584f,0.714f,1.000f};
static swColor SWCOLOR_BRANDEIS_BLUE={0.000f,0.439f,1.000f,1.000f};
static swColor SWCOLOR_BRASS={0.710f,0.651f,0.259f,1.000f};
static swColor SWCOLOR_BRIGHT_GREEN={0.400f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_BRIGHT_PINK={1.000f,0.000f,0.498f,1.000f};
static swColor SWCOLOR_BRIGHT_TURQUOISE={0.031f,0.910f,0.871f,1.000f};
static swColor SWCOLOR_BRILLIANT_ROSE={1.000f,0.333f,0.639f,1.000f};
static swColor SWCOLOR_BRINK_PINK={0.984f,0.376f,0.498f,1.000f};
static swColor SWCOLOR_BRITISH_RACING_GREEN={0.000f,0.259f,0.145f,1.000f};
static swColor SWCOLOR_BRONZE={0.804f,0.498f,0.196f,1.000f};
static swColor SWCOLOR_BROWN={0.588f,0.294f,0.000f,1.000f};
static swColor SWCOLOR_BUFF={0.941f,0.863f,0.510f,1.000f};
static swColor SWCOLOR_BURGUNDY={0.502f,0.000f,0.125f,1.000f};
static swColor SWCOLOR_BURNT_ORANGE={0.800f,0.333f,0.000f,1.000f};
static swColor SWCOLOR_BURNT_SIENNA={0.914f,0.455f,0.318f,1.000f};
static swColor SWCOLOR_BURNT_UMBER={0.541f,0.200f,0.141f,1.000f};
static swColor SWCOLOR_BYZANTIUM={0.439f,0.161f,0.388f,1.000f};
static swColor SWCOLOR_CAMBRIDGE_BLUE={0.639f,0.757f,0.678f,1.000f};
static swColor SWCOLOR_CAMOUFLAGE_GREEN={0.471f,0.525f,0.420f,1.000f};
static swColor SWCOLOR_CAPUT_MORTUUM={0.349f,0.153f,0.125f,1.000f};
static swColor SWCOLOR_CARDINAL={0.769f,0.118f,0.227f,1.000f};
static swColor SWCOLOR_CARMINE={0.588f,0.000f,0.094f,1.000f};
static swColor SWCOLOR_CARMINE_PINK={0.922f,0.298f,0.259f,1.000f};
static swColor SWCOLOR_CARNATION_PINK={1.000f,0.651f,0.788f,1.000f};
static swColor SWCOLOR_CARNELIAN={0.702f,0.106f,0.106f,1.000f};
static swColor SWCOLOR_CAROLINA_BLUE={0.600f,0.729f,0.890f,1.000f};
static swColor SWCOLOR_CARROT_ORANGE={0.929f,0.569f,0.129f,1.000f};
static swColor SWCOLOR_CELADON={0.675f,0.882f,0.686f,1.000f};
static swColor SWCOLOR_CERISE={0.871f,0.192f,0.388f,1.000f};
static swColor SWCOLOR_CERISE_PINK={0.925f,0.231f,0.514f,1.000f};
static swColor SWCOLOR_CERULEAN={0.000f,0.482f,0.655f,1.000f};
static swColor SWCOLOR_CERULEAN_BLUE={0.165f,0.322f,0.745f,1.000f};
static swColor SWCOLOR_CHAMPAGNE={0.969f,0.906f,0.808f,1.000f};
static swColor SWCOLOR_CHARCOAL={0.275f,0.275f,0.275f,1.000f};
static swColor SWCOLOR_CHARTREUSE_TRADITIONAL={0.875f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_CHARTREUSE_WEB={0.498f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_CHERRY_BLOSSOM_PINK={1.000f,0.718f,0.773f,1.000f};
static swColor SWCOLOR_CHESTNUT={0.804f,0.361f,0.361f,1.000f};
static swColor SWCOLOR_CHOCOLATE={0.482f,0.247f,0.000f,1.000f};
static swColor SWCOLOR_CINNABAR={0.890f,0.259f,0.204f,1.000f};
static swColor SWCOLOR_CINNAMON={0.824f,0.412f,0.118f,1.000f};
static swColor SWCOLOR_COBALT={0.000f,0.278f,0.671f,1.000f};
static swColor SWCOLOR_COLUMBIA_BLUE={0.608f,0.867f,1.000f,1.000f};
static swColor SWCOLOR_COPPER={0.722f,0.451f,0.200f,1.000f};
static swColor SWCOLOR_COPPER_ROSE={0.600f,0.400f,0.400f,1.000f};
static swColor SWCOLOR_CORAL={1.000f,0.498f,0.314f,1.000f};
static swColor SWCOLOR_CORAL_PINK={0.973f,0.514f,0.475f,1.000f};
static swColor SWCOLOR_CORAL_RED={1.000f,0.251f,0.251f,1.000f};
static swColor SWCOLOR_CORDOVAN={0.537f,0.247f,0.271f,1.000f};
static swColor SWCOLOR_CORN={0.984f,0.925f,0.365f,1.000f};
static swColor SWCOLOR_CORNFLOWER_BLUE={0.392f,0.584f,0.929f,1.000f};
static swColor SWCOLOR_COSMIC_LATTE={1.000f,0.973f,0.906f,1.000f};
static swColor SWCOLOR_CREAM={1.000f,0.992f,0.816f,1.000f};
static swColor SWCOLOR_CRIMSON={0.863f,0.078f,0.235f,1.000f};
static swColor SWCOLOR_CYAN={0.000f,1.000f,1.000f,1.000f};
static swColor SWCOLOR_CYAN_PROCESS={0.000f,0.718f,0.922f,1.000f};
static swColor SWCOLOR_DARK_BLUE={0.000f,0.000f,0.545f,1.000f};
static swColor SWCOLOR_DARK_BROWN={0.396f,0.263f,0.129f,1.000f};
static swColor SWCOLOR_DARK_CERULEAN={0.031f,0.271f,0.494f,1.000f};
static swColor SWCOLOR_DARK_CHESTNUT={0.596f,0.412f,0.376f,1.000f};
static swColor SWCOLOR_DARK_CORAL={0.804f,0.357f,0.271f,1.000f};
static swColor SWCOLOR_DARK_GOLDENROD={0.722f,0.525f,0.043f,1.000f};
static swColor SWCOLOR_DARK_GREEN={0.004f,0.196f,0.125f,1.000f};
static swColor SWCOLOR_DARK_KHAKI={0.741f,0.718f,0.420f,1.000f};
static swColor SWCOLOR_DARK_MAGENTA={0.545f,0.000f,0.545f,1.000f};
static swColor SWCOLOR_DARK_PASTEL_GREEN={0.012f,0.753f,0.235f,1.000f};
static swColor SWCOLOR_DARK_PINK={0.906f,0.329f,0.502f,1.000f};
static swColor SWCOLOR_DARK_SCARLET={0.337f,0.012f,0.098f,1.000f};
static swColor SWCOLOR_DARK_SALMON={0.914f,0.588f,0.478f,1.000f};
static swColor SWCOLOR_DARK_SLATE_GRAY={0.184f,0.310f,0.310f,1.000f};
static swColor SWCOLOR_DARK_SPRING_GREEN={0.090f,0.447f,0.271f,1.000f};
static swColor SWCOLOR_DARK_TAN={0.569f,0.506f,0.318f,1.000f};
static swColor SWCOLOR_DARK_TURQUOISE={0.000f,0.808f,0.820f,1.000f};
static swColor SWCOLOR_DARK_VIOLET={0.580f,0.000f,0.827f,1.000f};
static swColor SWCOLOR_DAVYS_GREY={0.333f,0.333f,0.333f,1.000f};
static swColor SWCOLOR_DEEP_CARMINE_PINK={0.937f,0.188f,0.220f,1.000f};
static swColor SWCOLOR_DEEP_CERISE={0.855f,0.196f,0.529f,1.000f};
static swColor SWCOLOR_DEEP_CHESTNUT={0.725f,0.306f,0.282f,1.000f};
static swColor SWCOLOR_DEEP_FUCHSIA={0.757f,0.329f,0.757f,1.000f};
static swColor SWCOLOR_DEEP_LILAC={0.600f,0.333f,0.733f,1.000f};
static swColor SWCOLOR_DEEP_MAGENTA={0.804f,0.000f,0.800f,1.000f};
static swColor SWCOLOR_DEEP_PEACH={1.000f,0.796f,0.643f,1.000f};
static swColor SWCOLOR_DEEP_PINK={1.000f,0.078f,0.576f,1.000f};
static swColor SWCOLOR_DEEP_SAFFRON={1.000f,0.600f,0.200f,1.000f};
static swColor SWCOLOR_DENIM={0.082f,0.376f,0.741f,1.000f};
static swColor SWCOLOR_DESERT_SAND={0.929f,0.788f,0.686f,1.000f};
static swColor SWCOLOR_DODGER_BLUE={0.118f,0.565f,1.000f,1.000f};
static swColor SWCOLOR_DUKE_BLUE={0.000f,0.000f,0.612f,1.000f};
static swColor SWCOLOR_ECRU={0.761f,0.698f,0.502f,1.000f};
static swColor SWCOLOR_EGYPTIAN_BLUE={0.063f,0.204f,0.651f,1.000f};
static swColor SWCOLOR_EGGPLANT={0.380f,0.251f,0.318f,1.000f};
static swColor SWCOLOR_ELECTRIC_BLUE={0.490f,0.976f,1.000f,1.000f};
static swColor SWCOLOR_ELECTRIC_GREEN_X11_GREEN={0.000f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_ELECTRIC_INDIGO={0.400f,0.000f,1.000f,1.000f};
static swColor SWCOLOR_ELECTRIC_LIME={0.800f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_ELECTRIC_PURPLE={0.749f,0.000f,1.000f,1.000f};
static swColor SWCOLOR_EMERALD={0.314f,0.784f,0.471f,1.000f};
static swColor SWCOLOR_FALLOW={0.757f,0.604f,0.420f,1.000f};
static swColor SWCOLOR_FALU_RED={0.502f,0.094f,0.094f,1.000f};
static swColor SWCOLOR_FELDGRAU={0.302f,0.365f,0.325f,1.000f};
static swColor SWCOLOR_FERN_GREEN={0.310f,0.475f,0.259f,1.000f};
static swColor SWCOLOR_FIREBRICK={0.698f,0.133f,0.133f,1.000f};
static swColor SWCOLOR_FIRE_ENGINE_RED={0.808f,0.086f,0.125f,1.000f};
static swColor SWCOLOR_FLAX={0.933f,0.863f,0.510f,1.000f};
static swColor SWCOLOR_FOREST_GREEN={0.133f,0.545f,0.133f,1.000f};
static swColor SWCOLOR_FRENCH_ROSE={0.965f,0.290f,0.541f,1.000f};
static swColor SWCOLOR_FUCHSIA={1.000f,0.000f,1.000f,1.000f};
static swColor SWCOLOR_FUCHSIA_PINK={1.000f,0.467f,1.000f,1.000f};
static swColor SWCOLOR_GAMBOGE={0.894f,0.608f,0.059f,1.000f};
static swColor SWCOLOR_GOLD_METALLIC={0.831f,0.686f,0.216f,1.000f};
static swColor SWCOLOR_GOLD_WEB_GOLDEN={1.000f,0.843f,0.000f,1.000f};
static swColor SWCOLOR_GOLDEN_BROWN={0.600f,0.396f,0.082f,1.000f};
static swColor SWCOLOR_GOLDEN_POPPY={0.988f,0.761f,0.000f,1.000f};
static swColor SWCOLOR_GOLDEN_YELLOW={1.000f,0.875f,0.000f,1.000f};
static swColor SWCOLOR_GOLDENROD={0.855f,0.647f,0.125f,1.000f};
static swColor SWCOLOR_GRAY_ASPARAGUS={0.275f,0.349f,0.271f,1.000f};
static swColor SWCOLOR_UNRELIABLE_SOURCE={0.000f,0.000f,0.000f,1.000f};
static swColor SWCOLOR_GREEN_COLOR_WHEEL_X11_GREEN={0.000f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_GREEN_HTML_CSS_GREEN={0.000f,0.502f,0.000f,1.000f};
static swColor SWCOLOR_GREEN_PIGMENT={0.000f,0.647f,0.314f,1.000f};
static swColor SWCOLOR_GREEN_RYB={0.400f,0.690f,0.196f,1.000f};
static swColor SWCOLOR_GREEN_YELLOW={0.678f,1.000f,0.184f,1.000f};
static swColor SWCOLOR_HAN_BLUE={0.322f,0.094f,0.980f,1.000f};
static swColor SWCOLOR_HAN_PURPLE={0.322f,0.094f,0.980f,1.000f};
static swColor SWCOLOR_HARLEQUIN={0.247f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_HELIOTROPE={0.875f,0.451f,1.000f,1.000f};
static swColor SWCOLOR_HOLLYWOOD_CERISE={0.957f,0.000f,0.631f,1.000f};
static swColor SWCOLOR_HOT_MAGENTA={1.000f,0.000f,0.800f,1.000f};
static swColor SWCOLOR_HOT_PINK={1.000f,0.412f,0.706f,1.000f};
static swColor SWCOLOR_HUNTER_GREEN={0.208f,0.369f,0.231f,1.000f};
static swColor SWCOLOR_INDIA_GREEN={0.075f,0.533f,0.031f,1.000f};
static swColor SWCOLOR_INDIGO_DYE={0.000f,0.255f,0.416f,1.000f};
static swColor SWCOLOR_INDIGO_WEB={0.294f,0.000f,0.510f,1.000f};
static swColor SWCOLOR_INTERNATIONAL_KLEIN_BLUE={0.000f,0.184f,0.655f,1.000f};
static swColor SWCOLOR_INTERNATIONAL_ORANGE={1.000f,0.310f,0.000f,1.000f};
static swColor SWCOLOR_ISLAMIC_GREEN={0.000f,0.565f,0.000f,1.000f};
static swColor SWCOLOR_IVORY={1.000f,1.000f,0.941f,1.000f};
static swColor SWCOLOR_JADE={0.000f,0.659f,0.420f,1.000f};
static swColor SWCOLOR_JUNGLE_GREEN={0.161f,0.671f,0.529f,1.000f};
static swColor SWCOLOR_KELLY_GREEN={0.298f,0.733f,0.090f,1.000f};
static swColor SWCOLOR_KHAKI={0.765f,0.690f,0.569f,1.000f};
static swColor SWCOLOR_KHAKI_X11_LIGHT_KHAKI={0.941f,0.902f,0.549f,1.000f};
static swColor SWCOLOR_LAVA={0.812f,0.063f,0.125f,1.000f};
static swColor SWCOLOR_LAVENDER_FLORAL={0.710f,0.494f,0.863f,1.000f};
static swColor SWCOLOR_LAVENDER_WEB={0.902f,0.902f,0.980f,1.000f};
static swColor SWCOLOR_LAVENDER_BLUE={0.800f,0.800f,1.000f,1.000f};
static swColor SWCOLOR_LAVENDER_BLUSH={1.000f,0.941f,0.961f,1.000f};
static swColor SWCOLOR_LAVENDER_GRAY={0.769f,0.765f,0.816f,1.000f};
static swColor SWCOLOR_LAVENDER_INDIGO={0.580f,0.341f,0.922f,1.000f};
static swColor SWCOLOR_LAVENDER_MAGENTA={0.933f,0.510f,0.933f,1.000f};
static swColor SWCOLOR_LAVENDER_PINK={0.984f,0.682f,0.824f,1.000f};
static swColor SWCOLOR_LAVENDER_PURPLE={0.588f,0.482f,0.714f,1.000f};
static swColor SWCOLOR_LAVENDER_ROSE={0.984f,0.627f,0.890f,1.000f};
static swColor SWCOLOR_LAWN_GREEN={0.486f,0.988f,0.000f,1.000f};
static swColor SWCOLOR_LEMON={0.992f,0.914f,0.063f,1.000f};
static swColor SWCOLOR_LEMON_CHIFFON={1.000f,0.980f,0.804f,1.000f};
static swColor SWCOLOR_LIGHT_BLUE={0.678f,0.847f,0.902f,1.000f};
static swColor SWCOLOR_LIGHT_PINK={1.000f,0.714f,0.757f,1.000f};
static swColor SWCOLOR_LIGHT_THULIAN_PINK={0.902f,0.561f,0.675f,1.000f};
static swColor SWCOLOR_LILAC={0.784f,0.635f,0.784f,1.000f};
static swColor SWCOLOR_LIME_COLOR_WHEEL={0.749f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_LIME_WEB_X11_GREEN={0.000f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_LIME_GREEN={0.196f,0.804f,0.196f,1.000f};
static swColor SWCOLOR_LINEN={0.980f,0.941f,0.902f,1.000f};
static swColor SWCOLOR_LIVER={0.325f,0.294f,0.310f,1.000f};
static swColor SWCOLOR_MAGENTA={1.000f,0.000f,1.000f,1.000f};
static swColor SWCOLOR_MAGENTA_DYE={0.792f,0.082f,0.482f,1.000f};
static swColor SWCOLOR_MAGENTA_PROCESS={1.000f,0.000f,0.565f,1.000f};
static swColor SWCOLOR_MAGIC_MINT={0.667f,0.941f,0.820f,1.000f};
static swColor SWCOLOR_MAGNOLIA={0.973f,0.957f,1.000f,1.000f};
static swColor SWCOLOR_MAHOGANY={0.753f,0.251f,0.000f,1.000f};
static swColor SWCOLOR_MAIZE={0.984f,0.925f,0.369f,1.000f};
static swColor SWCOLOR_MAJORELLE_BLUE={0.376f,0.314f,0.863f,1.000f};
static swColor SWCOLOR_MALACHITE={0.043f,0.855f,0.318f,1.000f};
static swColor SWCOLOR_MAROON_HTML_CSS={0.502f,0.000f,0.000f,1.000f};
static swColor SWCOLOR_MAROON_X11={0.690f,0.188f,0.376f,1.000f};
static swColor SWCOLOR_MAUVE={0.878f,0.690f,1.000f,1.000f};
static swColor SWCOLOR_MAUVE_TAUPE={0.569f,0.373f,0.427f,1.000f};
static swColor SWCOLOR_MAYA_BLUE={0.451f,0.761f,0.984f,1.000f};
static swColor SWCOLOR_MEDIUM_BLUE={0.000f,0.000f,0.804f,1.000f};
static swColor SWCOLOR_MEDIUM_CARMINE={0.686f,0.251f,0.208f,1.000f};
static swColor SWCOLOR_MEDIUM_LAVENDER_MAGENTA={0.800f,0.600f,0.800f,1.000f};
static swColor SWCOLOR_MEDIUM_PURPLE={0.576f,0.439f,0.859f,1.000f};
static swColor SWCOLOR_MEDIUM_SPRING_GREEN={0.000f,0.980f,0.604f,1.000f};
static swColor SWCOLOR_MEDIUM_TAUPE={0.404f,0.298f,0.278f,1.000f};
static swColor SWCOLOR_MIDNIGHT_BLUE={0.098f,0.098f,0.439f,1.000f};
static swColor SWCOLOR_MIDNIGHT_GREEN_EAGLE_GREEN={0.000f,0.286f,0.325f,1.000f};
static swColor SWCOLOR_MINT_GREEN={0.596f,1.000f,0.596f,1.000f};
static swColor SWCOLOR_MISTY_ROSE={1.000f,0.894f,0.882f,1.000f};
static swColor SWCOLOR_MOSS_GREEN={0.678f,0.875f,0.678f,1.000f};
static swColor SWCOLOR_MOUNTBATTEN_PINK={0.600f,0.478f,0.553f,1.000f};
static swColor SWCOLOR_MUSTARD={1.000f,0.859f,0.345f,1.000f};
static swColor SWCOLOR_MYRTLE={0.129f,0.259f,0.118f,1.000f};
static swColor SWCOLOR_MSU_GREEN={0.000f,0.400f,0.200f,1.000f};
static swColor SWCOLOR_NAVAJO_WHITE={1.000f,0.871f,0.678f,1.000f};
static swColor SWCOLOR_NAVY_BLUE={0.000f,0.000f,0.502f,1.000f};
static swColor SWCOLOR_OCHRE={0.800f,0.467f,0.133f,1.000f};
static swColor SWCOLOR_OFFICE_GREEN={0.000f,0.502f,0.000f,1.000f};
static swColor SWCOLOR_OLD_GOLD={0.812f,0.710f,0.231f,1.000f};
static swColor SWCOLOR_OLD_LACE={0.992f,0.961f,0.902f,1.000f};
static swColor SWCOLOR_OLD_LAVENDER={0.475f,0.408f,0.471f,1.000f};
static swColor SWCOLOR_OLD_ROSE={0.753f,0.502f,0.506f,1.000f};
static swColor SWCOLOR_OLIVE={0.502f,0.502f,0.000f,1.000f};
static swColor SWCOLOR_OLIVE_DRAB={0.420f,0.557f,0.137f,1.000f};
static swColor SWCOLOR_OLIVINE={0.604f,0.725f,0.451f,1.000f};
static swColor SWCOLOR_ORANGE_COLOR_WHEEL={1.000f,0.498f,0.000f,1.000f};
static swColor SWCOLOR_ORANGE_RYB={0.984f,0.600f,0.008f,1.000f};
static swColor SWCOLOR_ORANGE_WEB={1.000f,0.647f,0.000f,1.000f};
static swColor SWCOLOR_ORANGE_PEEL={1.000f,0.627f,0.000f,1.000f};
static swColor SWCOLOR_ORANGE_RED={1.000f,0.271f,0.000f,1.000f};
static swColor SWCOLOR_ORCHID={0.855f,0.439f,0.839f,1.000f};
static swColor SWCOLOR_PALE_BLUE={0.686f,0.933f,0.933f,1.000f};
static swColor SWCOLOR_PALE_BROWN={0.596f,0.463f,0.329f,1.000f};
static swColor SWCOLOR_PALE_CARMINE={0.686f,0.251f,0.208f,1.000f};
static swColor SWCOLOR_PALE_CHESTNUT={0.867f,0.678f,0.686f,1.000f};
static swColor SWCOLOR_PALE_CORNFLOWER_BLUE={0.671f,0.804f,0.937f,1.000f};
static swColor SWCOLOR_PALE_MAGENTA={0.976f,0.518f,0.898f,1.000f};
static swColor SWCOLOR_PALE_PINK={0.980f,0.855f,0.867f,1.000f};
static swColor SWCOLOR_PALE_RED_VIOLET={0.859f,0.439f,0.576f,1.000f};
static swColor SWCOLOR_PALE_TAUPE={0.737f,0.596f,0.494f,1.000f};
static swColor SWCOLOR_PAPAYA_WHIP={1.000f,0.937f,0.835f,1.000f};
static swColor SWCOLOR_PASTEL_GREEN={0.467f,0.867f,0.467f,1.000f};
static swColor SWCOLOR_PASTEL_PINK={1.000f,0.820f,0.863f,1.000f};
static swColor SWCOLOR_PAYNES_GREY={0.251f,0.251f,0.282f,1.000f};
static swColor SWCOLOR_PEACH={1.000f,0.898f,0.706f,1.000f};
static swColor SWCOLOR_PEACH_ORANGE={1.000f,0.800f,0.600f,1.000f};
static swColor SWCOLOR_PEACH_YELLOW={0.980f,0.875f,0.678f,1.000f};
static swColor SWCOLOR_PEAR={0.820f,0.886f,0.192f,1.000f};
static swColor SWCOLOR_PERIWINKLE={0.800f,0.800f,1.000f,1.000f};
static swColor SWCOLOR_PERSIAN_BLUE={0.110f,0.224f,0.733f,1.000f};
static swColor SWCOLOR_PERSIAN_GREEN={0.000f,0.651f,0.576f,1.000f};
static swColor SWCOLOR_PERSIAN_INDIGO={0.196f,0.071f,0.478f,1.000f};
static swColor SWCOLOR_PERSIAN_ORANGE={0.851f,0.565f,0.345f,1.000f};
static swColor SWCOLOR_PERSIAN_RED={0.800f,0.200f,0.200f,1.000f};
static swColor SWCOLOR_PERSIAN_PINK={0.969f,0.498f,0.745f,1.000f};
static swColor SWCOLOR_PERSIAN_ROSE={0.996f,0.157f,0.635f,1.000f};
static swColor SWCOLOR_PERSIMMON={0.925f,0.345f,0.000f,1.000f};
static swColor SWCOLOR_PINE_GREEN={0.004f,0.475f,0.435f,1.000f};
static swColor SWCOLOR_PINK={1.000f,0.753f,0.796f,1.000f};
static swColor SWCOLOR_PINK_ORANGE={1.000f,0.600f,0.400f,1.000f};
static swColor SWCOLOR_PLATINUM={0.898f,0.894f,0.886f,1.000f};
static swColor SWCOLOR_PLUM_WEB={0.800f,0.600f,0.800f,1.000f};
static swColor SWCOLOR_PORTLAND_ORANGE={1.000f,0.353f,0.212f,1.000f};
static swColor SWCOLOR_POWDER_BLUE_WEB={0.690f,0.878f,0.902f,1.000f};
static swColor SWCOLOR_PUCE={0.800f,0.533f,0.600f,1.000f};
static swColor SWCOLOR_PRUSSIAN_BLUE={0.000f,0.192f,0.325f,1.000f};
static swColor SWCOLOR_PSYCHEDELIC_PURPLE={0.867f,0.000f,1.000f,1.000f};
static swColor SWCOLOR_PUMPKIN={1.000f,0.459f,0.094f,1.000f};
static swColor SWCOLOR_PURPLE_HTML_CSS={0.498f,0.000f,0.498f,1.000f};
static swColor SWCOLOR_PURPLE_X11={0.627f,0.361f,0.941f,1.000f};
static swColor SWCOLOR_PURPLE_TAUPE={0.314f,0.251f,0.302f,1.000f};
static swColor SWCOLOR_RASPBERRY={0.890f,0.043f,0.361f,1.000f};
static swColor SWCOLOR_RAW_UMBER={0.451f,0.290f,0.071f,1.000f};
static swColor SWCOLOR_RAZZMATAZZ={0.890f,0.145f,0.420f,1.000f};
static swColor SWCOLOR_RED_PIGMENT={0.929f,0.110f,0.141f,1.000f};
static swColor SWCOLOR_RED_RYB={0.996f,0.153f,0.071f,1.000f};
static swColor SWCOLOR_RED_VIOLET={0.780f,0.082f,0.522f,1.000f};
static swColor SWCOLOR_RICH_CARMINE={0.843f,0.000f,0.251f,1.000f};
static swColor SWCOLOR_ROBIN_EGG_BLUE={0.000f,0.800f,0.800f,1.000f};
static swColor SWCOLOR_ROSE={1.000f,0.000f,0.498f,1.000f};
static swColor SWCOLOR_ROSE_MADDER={0.890f,0.149f,0.212f,1.000f};
static swColor SWCOLOR_ROSE_PINK={1.000f,0.400f,0.800f,1.000f};
static swColor SWCOLOR_ROSE_QUARTZ={0.667f,0.596f,0.663f,1.000f};
static swColor SWCOLOR_ROSE_TAUPE={0.565f,0.365f,0.365f,1.000f};
static swColor SWCOLOR_ROYAL_BLUE={0.255f,0.412f,0.882f,1.000f};
static swColor SWCOLOR_ROYAL_PURPLE={0.420f,0.247f,0.627f,1.000f};
static swColor SWCOLOR_RUBY={0.878f,0.067f,0.373f,1.000f};
static swColor SWCOLOR_RUSSET={0.502f,0.275f,0.106f,1.000f};
static swColor SWCOLOR_RUST={0.718f,0.255f,0.055f,1.000f};
static swColor SWCOLOR_SAFETY_ORANGE_BLAZE_ORANGE={1.000f,0.400f,0.000f,1.000f};
static swColor SWCOLOR_SAFFRON={0.957f,0.769f,0.188f,1.000f};
static swColor SWCOLOR_SALMON={1.000f,0.549f,0.412f,1.000f};
static swColor SWCOLOR_SALMON_PINK={1.000f,0.569f,0.643f,1.000f};
static swColor SWCOLOR_SANDY_BROWN={0.957f,0.643f,0.376f,1.000f};
static swColor SWCOLOR_SANGRIA={0.573f,0.000f,0.039f,1.000f};
static swColor SWCOLOR_SAPPHIRE={0.031f,0.145f,0.404f,1.000f};
static swColor SWCOLOR_SCARLET={1.000f,0.141f,0.000f,1.000f};
static swColor SWCOLOR_SCHOOL_BUS_YELLOW={1.000f,0.847f,0.000f,1.000f};
static swColor SWCOLOR_SEA_GREEN={0.180f,0.545f,0.341f,1.000f};
static swColor SWCOLOR_SEAL_BROWN={0.196f,0.078f,0.078f,1.000f};
static swColor SWCOLOR_SEASHELL={1.000f,0.961f,0.933f,1.000f};
static swColor SWCOLOR_SELECTIVE_YELLOW={1.000f,0.729f,0.000f,1.000f};
static swColor SWCOLOR_SEPIA={0.439f,0.259f,0.078f,1.000f};
static swColor SWCOLOR_SHAMROCK_GREEN={0.000f,0.620f,0.376f,1.000f};
static swColor SWCOLOR_SHOCKING_PINK={0.988f,0.059f,0.753f,1.000f};
static swColor SWCOLOR_SIENNA={0.627f,0.322f,0.180f,1.000f};
static swColor SWCOLOR_SILVER={0.753f,0.753f,0.753f,1.000f};
static swColor SWCOLOR_SKY_BLUE={0.529f,0.808f,0.922f,1.000f};
static swColor SWCOLOR_SLATE_GRAY={0.439f,0.502f,0.565f,1.000f};
static swColor SWCOLOR_SMALT_DARK_POWDER_BLUE={0.000f,0.200f,0.600f,1.000f};
static swColor SWCOLOR_SPRING_BUD={0.655f,0.988f,0.000f,1.000f};
static swColor SWCOLOR_SPRING_GREEN={0.000f,1.000f,0.498f,1.000f};
static swColor SWCOLOR_STEEL_BLUE={0.275f,0.510f,0.706f,1.000f};
static swColor SWCOLOR_TAN={0.824f,0.706f,0.549f,1.000f};
static swColor SWCOLOR_TANGERINE={0.949f,0.522f,0.000f,1.000f};
static swColor SWCOLOR_TANGERINE_YELLOW={1.000f,0.800f,0.000f,1.000f};
static swColor SWCOLOR_TAUPE={0.282f,0.235f,0.196f,1.000f};
static swColor SWCOLOR_TAUPE_GRAY={0.545f,0.522f,0.537f,1.000f};
static swColor SWCOLOR_TEA_GREEN={0.816f,0.941f,0.753f,1.000f};
static swColor SWCOLOR_TEA_ROSE_ORANGE={0.973f,0.514f,0.475f,1.000f};
static swColor SWCOLOR_TEA_ROSE_ROSE={0.957f,0.761f,0.761f,1.000f};
static swColor SWCOLOR_TEAL={0.000f,0.502f,0.502f,1.000f};
static swColor SWCOLOR_TENNÉ_TAWNY={0.804f,0.341f,0.000f,1.000f};
static swColor SWCOLOR_TERRA_COTTA={0.886f,0.447f,0.357f,1.000f};
static swColor SWCOLOR_THISTLE={0.847f,0.749f,0.847f,1.000f};
static swColor SWCOLOR_THULIAN_PINK={0.871f,0.435f,0.631f,1.000f};
static swColor SWCOLOR_TOMATO={1.000f,0.388f,0.278f,1.000f};
static swColor SWCOLOR_TURQUOISE={0.188f,0.835f,0.784f,1.000f};
static swColor SWCOLOR_TYRIAN_PURPLE={0.400f,0.008f,0.235f,1.000f};
static swColor SWCOLOR_ULTRAMARINE={0.071f,0.039f,0.561f,1.000f};
static swColor SWCOLOR_ULTRA_PINK={1.000f,0.435f,1.000f,1.000f};
static swColor SWCOLOR_UNITED_NATIONS_BLUE={0.357f,0.573f,0.898f,1.000f};
static swColor SWCOLOR_UPSDELL_RED={0.682f,0.086f,0.125f,1.000f};
static swColor SWCOLOR_VEGAS_GOLD={0.773f,0.702f,0.345f,1.000f};
static swColor SWCOLOR_VENETIAN_RED={0.784f,0.031f,0.082f,1.000f};
static swColor SWCOLOR_VERMILION={0.890f,0.259f,0.200f,1.000f};
static swColor SWCOLOR_VIOLET={0.545f,0.000f,1.000f,1.000f};
static swColor SWCOLOR_VIOLET_WEB={0.933f,0.510f,0.933f,1.000f};
static swColor SWCOLOR_VIOLET_RYB={0.008f,0.278f,0.212f,1.000f};
static swColor SWCOLOR_VIRIDIAN={0.251f,0.510f,0.427f,1.000f};
static swColor SWCOLOR_WHEAT={0.961f,0.871f,0.702f,1.000f};
static swColor SWCOLOR_WISTERIA={0.788f,0.627f,0.863f,1.000f};
static swColor SWCOLOR_XANADU={0.451f,0.525f,0.471f,1.000f};
static swColor SWCOLOR_YALE_BLUE={0.059f,0.302f,0.573f,1.000f};
static swColor SWCOLOR_YELLOW={1.000f,1.000f,0.000f,1.000f};
static swColor SWCOLOR_YELLOW_PROCESS={1.000f,0.937f,0.000f,1.000f};
static swColor SWCOLOR_YELLOW_RYB={0.996f,0.996f,0.200f,1.000f};
```

