#SWEngine
========
  ![SWEngine Logo](/docs/images/swenginesdk.jpg)



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

## swTypes

### swPoint
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


### swColor
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

## swDimension
It holds dimension value (Width,Height)
```c
//Structure
typedef struct _swDimension{
   float w;
   float h;
}swDimension;
 
//Functions
swDimension*         swDimensionCreate(float w,float h);
void                 swDimensionDestroy(swDimension *dimension);
void                 swDimensionSet(swDimension *p,float w,float h);
void                 swDimensionCopy(swDimension *copy,swDimension *real);
swDimension*         swDimensionClone(swDimension *real);
bool                 swDimensionEquals(swDimension *dimension1,swDimension *dimension2);
```

### swRect
It holds rectangle data. This data structure is very important for texture rendering so you usually use this data structure.
```c
//Structure
typedef struct _swRect{
   float x;
   float y;
   float w; //width
   float h; //height
}swRect;
 
//Functions
swRect*   swRectCreate(float x,float y,float w,float h);
void      swRectDestroy(swRect *rect);
void      swRectSet(swRect *rect,float x,float y,float w,float h);
void      swRectCopy(swRect *copy,swRect *real);
swRect*   swRectClone(swRect *real);
bool      swRectEquals(swRect *rect1,swRect *rect2);
float     swRectMidX(swRect *rect);  //rect.x+rect.w/2
float     swRectMidY(swRect *rect);  //rect.y+rect.h/2
float     swRectYPlusH(swRect *rect);//rect.y+rect.h
float     swRectXPlusW(swRect *rect);//rect.x+rect.w
```

### swPolygon
It holds polygon data.

```c
//Structure
typedef struct _swPolygon{
   int count;
   swPoint pointS[25]; 
}swPolygon;
```


### swVec2
It hold 2D vector data...

```c
//Structure
typedef swPoint swVec2;
 
//Functions
swVec2* swVec2Create(float x,float y);
void    swVec2Destroy(swVec2 *v);
void    swVec2Set(swVec2 *v,float x,float y);
void    swVec2Copy(swVec2 *copy,swVec2 *real);
swVec2* swVec2Clone(swVec2 *real);
bool    swVec2Equals(swVec2 *v1,swVec2 *v2);
swVec2* swVec2Add(swVec2 *v1,swVec2 *v2);
swVec2* swVec2Sub(swVec2 *v1,swVec2 *v2);
swVec2* swVec2Mult(swVec2 *v,float val);
swVec2* swVec2Div(swVec2 *v,float val);
float   swVec2Length(swVec2 *v);
float   swVec2Angle(swVec2 *v1,swVec2 *v2);
swVec2* swVec2Normal(swVec2 *v);
swVec2* swVec2Abs(swVec2 *v);
swVec2* swVec2Reflect(swVec2 *normal,swVec2 *light);
swVec2* swVec2CrossX(swVec2 *v,float s);
swVec2* swVec2CrossY(swVec2 *v,float s);
swVec2* swVec2MultMat22(swMat22 *m, swVec2 *v);
```

### swArg
Generic argument types. These are bool(true/false),int,float,string

```c
//Structure
typedef enum _swArgType{
   SW_ARG_BOOL,
   SW_ARG_INT,
   SW_ARG_FLOAT,
   SW_ARG_STRING,
}swArgType;
 
 
typedef struct _swArg{
   swArgType type;
   union{
      bool  bVal;
      int   iVal;
      float fVal;
      char  sVal[16];
   }arg;
}swArg;
```


## swUtil

### swMath
Utility functions for math operations

```c
//Constants
define SW_MATH_PI 3.14678f
 
//Functions
float  swMathCos(angle)  //degree
float  swMathSin(angle)  //degree
float  swMathDegreeToRadian(float degree);
float  swMathRadianToDegree(float radian);
float  swMathDegree(float x0,float y0,float x1,float y1);
float  swMathDistance(float x0,float y0,float x1,float y1);
float  swMathMax(float val1, float val2);
float  swMathMin(float val1, float val2);
float  swMathAbs(float val);
float  swMathSign(float val);
bool   swMathIsPowerTwo(float val);
bool   swMathIsInRangeInt(int val,int minVal,int maxVal);
bool   swMathIsInRangeFloat(float val,float minVal,float maxVal);
int    swMathClampInt(int val,int minVal,int maxVal);
float  swMathClampFloat(float val,float minVal,float maxVal);
float  swMathRandom(float minVal,float maxVal);
float  swMathRandomFloat(float minVal,float maxVal);
int    swMathRandomInt(int minVal,int maxVal);
void   swMathSetSeed(int randomSeed);
void   swMathSourceCalculate(swRect *rect,int xGridSize,int yGridSize,int xGridIndex,int yGridIndex);
```

### swString
Utility function for String operations

```c
//Functions
int   swStringGetLength(char *str);
char* swStringGetChrAdress(char *str,int ch);
int   swStringGetChrPosition(char *str,char ch);
bool  swStringEquals(char *str1, char *str2);
bool  swStringContains(char *str,char *searchStr);
char* swStringConcat(char *p1,char *p2); //Don't use in loop it allocate mem for all call
void  swStringConcat1(char *p1,char *p2);
char* swStringConcatEx(char *str1, int start1,int end1,char *str2, int start2,int end2); //Don't use in loop it allocate mem for all call
void  swStringCopy(char *str1,char *str2);
void  swStringCopyEx(char *str1,char *str2,int start,int stop);
void  swStringReplaceChrInString(char *str,char oldchr,char *newchr);
void  swString2LowerCase(char *str);
void  swString2UpperCase(char *str);
void  swString2Float(char *p,float *f);
int   swString2Int(char *p);
bool  swString2Bool(char *p);
void  swStringParse(char *str,char separator,char *val,char *remaining);
```

### swLinkedList 
Linked List Implementation.

```c
//Functions
int    swLinkedListCreate();
void   swLinkedListDestroy(int listID);
void   swLinkedListAdd(int listID, void *obj);
void   swLinkedListDel(int listID,void *obj);
void*  swLinkedListGet(int listID,int index);
void*  swLinkedListGetFirst(int listID);
void*  swLinkedListGetLast(int listID);
void*  swLinkedListGetNext(int listID);
void*  swLinkedListGetPrev(int listID);
int    swLinkedListSize(int listID);
void   swLinkedListIterate(int listID,void(*func)(void*));
void   swLinkedListClear(int listID);
bool   swLinkedListContains(int listID,void *obj);
```

### swStack
Stack Implementation.

```c
//Functions
int   swStackCreate();
void  swStackDestroy(int stackID);
void  swStackPush(int stackID, void *obj);
void* swStackPop(int stackID);
void* swStackPeek(int stackID);
bool  swStackIsEmpty(int stackID);
int   swStackSize(int stackID);
```

### swIntersection
Utility functions for collision detection. This utility function for simple usage. In real simulation collision you should use SWPhys API

```c
//Functions
bool swIntersectionLineAndLine(swPoint *line0Start,swPoint *line0End,swPoint *line1Start,swPoint *line1End);
bool swIntersectionLineAndPoint(swPoint *lineStart,swPoint *lineEnd,swPoint *point);
bool swIntersectionCircleAndPoint(swPoint *center,float radious,swPoint *point);
bool swIntersectionCircleAndLine(swPoint *center,float radious,swPoint *line0Start,swPoint *line0End);
bool swIntersectionCircleAndCircle(swPoint *center0,float radious0,swPoint *center1,float radious1);
bool swIntersectionRectAndPoint(swRect *rect,swPoint *point);
bool swIntersectionRectAndPoint2(swRect *rect,float x,float y);
bool swIntersectionRectAndLine(swRect *rect,swPoint *line0Start,swPoint *line0End);
bool swIntersectionBoundaryAndBoundary(swPolygon *b1,swPolygon *b2);
bool swIntersectionBoundaryAndPoint(swPolygon *b1,swPoint *pos);
bool swIntersectionBoundaryAndLine(swPolygon *b1,swPoint *line0Start,swPoint *line0End);
bool swIntersectionBoundaryAndRect(swPolygon *boundary,swRect *rect);
bool swIntersectionRectAndRect(swRect *r0,swRect *r1);
```

### swLogger
Util functions for logging
//Functions
FILE* swLoggerOpen();
void  swLoggerClose();
void  swLoggerLog(const char* log,...);

### swTimer
Timer implementation like Java swing.Timer class. You first register a function and set delay seconds for triggering callback functions
```c
//Functions
int  swTimerCreate(float delaySeconds,void *obj,void(*callBack)(void *));
void swTimerDestroy(int timerID);
void swTimerStart(int timerID);
void swTimerStop(int timerID);
bool swTimerIsRunning(int timerID);
```

## swCore

### swGraphics
OpenGL and GSLS Rendering functions

```c
//Scene Control
void swGraphicsBeginScene();  
void swGraphicsEndScene();

//Query
bool swGraphicsIsSupportGLSL();
bool swGraphicsIsSupportRectTex();
bool swGraphicsIsSupportPointSprite();
bool swGraphicsIsSupportFBOSupport();

//Blending
typedef enum{
  SW_BLENDING_MODE_NONE,
  SW_BLENDING_MODE_ADDITIVE,
  SW_BLENDING_MODE_SOLID,
  SW_BLENDING_MODE_SKETCH,
}swBlendingMode;
void             swGraphicsSetBlendingMode(swBlendingMode mode);
swBlendingMode   swGraphicsGetBlendingMode();


//Rendering Target
#define SW_RENDERING_TARGET_DEFAULT -1      
int        swGraphicsCreateRenderingTarget(int width, int height, int iBytesPerPixel);
void        swGraphicsDestroyRenderingTarget(int targetID);
void        swGraphicsSetRenderingTarget(int targetID);
void        swGraphicsClearRenderingTarget();
int        swGraphicsRenderingTargetGetImgID(int targetID);

//Shader
#define SW_DISABLED_SHADER_ID 0
int  swGraphicsCreateGLSLShader(char *pathVertShader,char *pathFragShader);
void swGraphicsActiveGLSLShader(int shaderID);
void swGraphicsSetGLSLShaderIntAttrb(int program, char *name,int value);
void swGraphicsSetGLSLShaderFloatAttrb(int program, char *name,float value);
void swGraphicsSetGLSLShaderVec2Attrb(int program, char *name,swVec2 vec2);
void swGraphicsSetGLSLShaderPointAttrb(int program, char *name,swPoint point);
void swGraphicsSetGLSLShaderDimensionAttrb(int program, char *name,swDimension dim);
void swGraphicsSetGLSLShaderColorAttrb(int program, char *name,swColor color);
void swGraphicsSetGLSLShaderRectAttrb(int program, char *name,swRect rect);


//Coloring 
void swGraphicsSetBgColor0(float r,float g,float b);
void swGraphicsSetBgColor1(float r,float g,float b,float a);
void swGraphicsSetBgColor2(swColor *bgColor);
void swGraphicsSetColor0(float r,float g,float b,float a);
void swGraphicsSetColor1([[swColor]] *c);

//Camera
#define SW_CAM_DEFAULT -1   
int   swGraphicsCreateCam();
void  swGraphicsDestroyCam(int camID);
void  swGraphicsSetCam(int camID,float x,float y,float rot,float zoom);
void  swGraphicsSetCamPos(int camID,float x,float y);
void  swGraphicsSetCamPosX(int camID,float x);
void  swGraphicsSetCamPosY(int camID,float y);
void  swGraphicsSetCamRot(int camID,float rot);
void  swGraphicsSetCamZoom(int camID,float zoom);
void  swGraphicsAddCamPosX(int camID,float dX);
void  swGraphicsAddCamPosY(int camID,float dY);
void  swGraphicsAddCamRot (int camID,float dR);
void  swGraphicsAddCamZoom(int camID,float dZ);
float swGraphicsGetCamPosX(int camID);
float swGraphicsGetCamPosY(int camID);
float swGraphicsGetCamRot(int camID);
float swGraphicsGetCamZoom(int camID);
void  swGraphicsActiveCam(int camID);


//Primitive Rendering
void swGraphicsRenderPoint0(float x,float y,float size);
void swGraphicsRenderPoint1(swPoint *point,float size);
void swGraphicsRenderLine0(float x0,float y0,float x1,float y1,float width);
void swGraphicsRenderLine1(swPoint *startP,swPoint* endP,float width);
void swGraphicsRenderLine2(swPoint *startP,swPoint* endP,float width,float rot);
void swGraphicsRenderLine3(swPoint *startP,swPoint* endP,float width,float rot,swPoint *weight);
void swGraphicsRenderPointRect0(float x,float y,float w,float h,float size);
void swGraphicsRenderPointRect1(swPoint *pos,swDimension *dim,float size);
void swGraphicsRenderPointRect2(swRect *rect,float size);
void swGraphicsRenderPointRect3(swRect *rect,float size,float rot);
void swGraphicsRenderPointRect4(swRect *rect,float size,float rot,swPoint *weight);
void swGraphicsRenderLineRect0(float x,float y,float w,float h,float width);
void swGraphicsRenderLineRect1(swPoint *pos,swDimension *dim,float width);
void swGraphicsRenderLineRect2(swRect *rect,float width);
void swGraphicsRenderLineRect3(swRect *rect,float width,float rot);
void swGraphicsRenderLineRect4(swRect *rect,float width,float rot,swPoint *weight);
void swGraphicsRenderSolidRect0(float x,float y,float w,float h);
void swGraphicsRenderSolidRect1(swPoint *pos,swDimension *dim);
void swGraphicsRenderSolidRect2(swRect *rect);
void swGraphicsRenderSolidRect3(swRect *rect,float rot);
void swGraphicsRenderSolidRect4(swRect *rect,float rot,swPoint *weight);
void swGraphicsRenderPointElips0(float x,float y,float w,float h,int count,float size);
void swGraphicsRenderPointElips1(swPoint *pos,swDimension *dim,int count,float size);
void swGraphicsRenderPointElips2(swPoint *pos,swDimension *dim,int count,float size,float rot);
void swGraphicsRenderPointElips3(swPoint *pos,swDimension *dim,int count, float size, float rot,swPoint *weight);
void swGraphicsRenderLineElips0(float x,float y,float w,float h,int count,float width);
void swGraphicsRenderLineElips1(swPoint *pos,swDimension *dim,int count,float width);
void swGraphicsRenderLineElips2(swPoint *pos,swDimension *dim,int count,float width,float rot);
void swGraphicsRenderLineElips3(swPoint *pos,swDimension *dim,int count, float width,float rot, swPoint *weight);
void swGraphicsRenderSolidElips0(float x,float y,float w,float h,int count);
void swGraphicsRenderSolidElips1(swPoint *pos,swDimension *dim,int count);
void swGraphicsRenderSolidElips2(swPoint *pos,swDimension *dim,int count,float rot);
void swGraphicsRenderSolidElips3(swPoint *pos,swDimension *dim,int count, float rot, swPoint *weight);
void swGraphicsRenderPointPolygon0(int count,swPoint *pointS,float size);
void swGraphicsRenderPointPolygon1(int pointLinkedListID,float size);
void swGraphicsRenderPointPolygon2(swPolygon *polygon,float size);
void swGraphicsRenderLinePolygon0(int count,swPoint *pointS,float width);
void swGraphicsRenderLinePolygon1(int pointLinkedListID,float width);
void swGraphicsRenderLinePolygon2(swPolygon *polygon,float width);
void swGraphicsRenderSolidPolygon0(int count,swPoint *pointS);
void swGraphicsRenderSolidPolygon1(int pointLinkedListID);
void swGraphicsRenderSolidPolygon2(swPolygon *polygon);

 
//Image Rendering
//t=Rendering Target s=Texture Target weight=Rotation Weight
int   swGraphicsCreateImg(char *filePath); 
void  swGraphicsDestroyImg(int imgID);  
void  swGraphicsRenderImg0(int imgID,swRect *t);
void  swGraphicsRenderImg1(int imgID,swRect *t,float rot);
void  swGraphicsRenderImg2(int imgID,swRect *t,swRect *s);
void  swGraphicsRenderImg3(int imgID,swRect *t,swRect *s,float rot);
void  swGraphicsRenderImg4(int imgID,swRect *t,float rot, swPoint *weight);
void  swGraphicsRenderImg5(int imgID,swRect *t,swRect *s,float rot, swPoint *weight);
//Enable or Disable UVScrolling Capability
void  swGraphicsSetImgUVScrollable(int imgID,bool bEnabled); 

//Sprite Rendering
//index= Image no in index t=Rendering Target s=Texture Target weight=Rotation Weight
int   swGraphicsCreateSprite(char *folderPath);  
void  swGraphicsDestroySprite(int spriteID);
int   swGraphicsGetCountOfImgInSprite(int spriteID);
void  swGraphicsRenderSprite0(int spriteID,int index,swRect *t);
void  swGraphicsRenderSprite1(int spriteID,int index,swRect *t,float rot);
void  swGraphicsRenderSprite2(int spriteID,int index,swRect *t,swRect *s);
void  swGraphicsRenderSprite3(int spriteID,int index,swRect *t,swRect *s,float rot);
void  swGraphicsRenderSprite4(int spriteID,int index,swRect *t,float  rot, swPoint *weight);
void  swGraphicsRenderSprite5(int spriteID,int index,swRect *t,swRect *s,float rot, swPoint *weight);

//Text Rendering
int  swGraphicsCreateFont(char *filePath);  
void swGraphicsDestroyFont(int fontID);  
void swGraphicsRenderText(int fontID,int set,float size,float x,float y,float rot,char *string,...);
void swGraphicsSetSpriteUVScrollable(int spriteID,bool bEnabled)


//Point Sprite Rendering
typedef struct _swPointSprite{
   swPoint pos;
   swColor color;
}swPointSprite;
int  swGraphicsCreatePointSprite(char *filePath); 
void swGraphicsDestroyPointSprite(int pSpriteID); 
void swGraphicsRenderPointSprite(int pSpriteID,float pSize,int count,swColor *cS,swPoint* pS); 
void swGraphicsRenderPointSprite1(int pSpriteID,float pSize,int count,swPointSprite *pSprites); 
void swGraphicsRenderPointSprite2(int pSpriteID,float pSize,int pointSpriteListID);
```

### swAudio
swAudio api setup over OpenAL api. Support Ogg and Wav files.

```c
//Audio Buffer
typedef enum _swAudioBufferType{
   SW_AUDIO_BUFFER_TYPE_WAV,
   SW_AUDIO_BUFFER_TYPE_OGG,
   SW_AUDIO_BUFFER_TYPE_OGG_STREAM,
}swAudioBufferType;
 
int      swAudioCreateBuffer(char *path, swAudioBufferType bufferType);
void      swAudioDestroyBuffer(int bufferID);
 
 
//Audio Source
typedef enum _swAudioSourceState{
  SW_AUDIO_SOURCE_STATE_NOBUFFER,
  SW_AUDIO_SOURCE_STATE_INITIAL,
  SW_AUDIO_SOURCE_STATE_PLAYING,
  SW_AUDIO_SOURCE_STATE_PAUSE,
  SW_AUDIO_SOURCE_STATE_STOP,
}swAudioSourceState;
 
 
int                swAudioCreateSource();
void               swAudioDestroySource(int sourceID);
void               swAudioBindSourceAndBuffer(int sourceID,int bufferID);
void               swAudioPlaySource(int sourceID);
void               swAudioPauseSource(int sourceID);
void               swAudioStopSource(int sourceID);
void               swAudioRewindSource(int sourceID);
swAudioSourceState swAudioGetSourceState(int sourceID);
char*              swAudioGetSourceStateText(int sourceID);
void               swAudioSetSourcePosition(int sourceID,float x,float y,float z);
void               swAudioSetSourcePitch(int sourceID,float pitch);
void               swAudioSetSourceGain(int sourceID,float gain);
void               swAudioSetSourceLoop(int sourceID,bool loop);
 
 
//Audio Listener
void               swAudioSetListenerPosition(float x,float y,float z);
```

### swInput
SWEngine provides keyboard and mouse listen functions so developer can easily handle user interactions.

```c

//Functions
void swInputListenKeyboard(swKeyboardState *state);
void swInputListenMouse(swMouseState *state);
 
//Keyboard State
typedef struct _swKeyboardState{
  BOOL keyESCAPE,key1,key2,key3,key4,key5,key6,key7,key8,key9,key0,keyMINUS,keyEQUALS,keyBACK,keyTAB,keyQ;
  BOOL keyW,keyE,keyR,keyT,keyY,keyU,keyI,keyO,keyP,keyLBRACKET,keyRBRACKET,keyRETURN,keyLCONTROL,keyA;
  BOOL keyS,keyD,keyF,keyG,keyH,keyJ,keyK,keyL,keySEMICOLON,keyAPOSTROPHE,keyGRAVE,keyLSHIFT,keyBACKSLASH,keyZ,keyX;
  BOOL keyC,keyV,keyB,keyN,keyM,keyCOMMA,keyPERIOD,keySLASH,keyRSHIFT,keyMULTIPLY,keyLMENU,keySPACE,keyCAPITAL,keyF1;
  BOOL keyF2,keyF3,keyF4,keyF5,keyF6,keyF7,keyF8,keyF9,keyF10,keyNUMLOCK,keySCROLL,keyNUMPAD7,keyNUMPAD8,keyNUMPAD9;
  BOOL keySUBTRACT,keyNUMPAD4,keyNUMPAD5,keyNUMPAD6,keyADD,keyNUMPAD1,keyNUMPAD2,keyNUMPAD3,keyNUMPAD0;
  BOOL keyDECIMAL,keyOEM_102,keyF11,keyF12,keyF13,keyF14,keyF15,keyKANA,keyABNT_C1,keyCONVERT,keyNOCONVERT;
  BOOL keyYEN,keyABNT_C2,keyNUMPADEQUALS,keyPREVTRACK,keyAT,keyCOLON,keyUNDERLINE,keyKANJI,keySTOP,keyAX,keyUNLABELED;
  BOOL keyNEXTTRACK,keyNUMPADENTER,keyRCONTROL,keyMUTE,keyCALCULATOR,keyPLAYPAUSE,keyMEDIASTOP,keyVOLUMEDOWN,keyVOLUMEUP;
  BOOL keyWEBHOME,keyNUMPADCOMMA,keyDIVIDE,keySYSRQ,keyRMENU,keyPAUSE,keyHOME,keyUP,keyPRIOR,keyLEFT,keyRIGHT;
  BOOL keyEND,keyDOWN,keyNEXT,keyINSERT,keyDELETE,keyLWIN,keyRWIN,keyAPPS,keyPOWER,keySLEEP,keyWAKE,keyWEBSEARCH;
  BOOL keyWEBFAVORITES,keyWEBREFRESH,keyWEBSTOP,keyWEBFORWARD,keyWEBBACK,keyMYCOMPUTER,keyMAIL,keyMEDIASELECT;
}swKeyboardState;
 
//Mouse State
typedef struct _swMouseState{
  BOOL btnLEFT,btnRIGHT,btnMIDDLE;
  float dX,dY;
  float x,y;
}swMouseState;
```

### swSystem
It provides information about running application
```c
//Functions
float swSystemGetElapsedSeconds(); // Return total time after application start.
void  swSystemCaptureScreen(char *path,swImgType type); //Save ScreenShot to spesific path
```

### swFileSystem
This api provides file system control functions on Windows.
```c
//Functions
void  swFileSystemSetResourcePath(char *name);
char* swFileSystemGetProgramWorkingPath();
char* swFileSystemGetResourcePath();
FILE* swFileSystemOpenFile(char *path,char *mode);
void  swFileSystemQueryFiles(char *folderPath,int fileLinkedListID,char *extensionFilter)
```

### swImgBuffer
This api for detail image operations on TGA, BMP, PNG, JPEG , GIF image formats
```c
//Functions
typedef enum _swImgType{
  SW_IMGTYPE_TGA,
}swImgType;
void        swImgBufferLoad(char *path, swImgType imgType);
void        swImgBufferLoadTGA(char *path);
void        swImgBufferFree();
int        swImgBufferGetWidth();
int        swImgBufferGetHeight();
void        swImgBufferGetPixel(int x,int y,swColor *color);
```


## swServices

### swDispManager
In games, object display process is very important for performance utilization and display capability.

* Culling mechanism, filters objects which are out side screen. 
* Layer Mechanism, sorts objects from background to foreground.
* Item Display Control, manages item visiblities..
  
```c
//Functions
int   swDispManagerAdd(void(*dispFunc)(void*), void *obj,boolean *bEnabled,swRect *rect,int *layer); 
void  swDispManagerDel(int id);
//This function should call between swGraphicsBeginDisplay()/swGraphicsEndDisplay() 
void  swDispManagerExecute(); 
int   swDispManagerSizeOfAll();
int   swDispManagerSizeOfRendered();
```

### swExecManager

In games, object display process is very important for performance utilization and display capability.

 * Culling mechanism, filters objects which are out side screen.
 * Layer Mechanism, sorts objects from background to foreground.
 * Item Display Control, manages item visiblities..

```c
//Functions
int   swExecManagerAdd(void(*execFunc)(void*), void *obj,bool *bEnabled);
void  swExecManagerDel(int id);
void  swExecManagerExecute();
```

### swInteractionManager
```c
//Functions
void  swInteractionManagerInit();
void  swInteractionManagerDeInit();
int   swInteractionManagerAdd(void(*intrFunc)(void*,swKeyboardState *,swMouseState *), void *obj,boolean *bEnabled);
void  swInteractionManagerExecute(swKeyboardState *keybState,swMouseState *mousState);
void  swInteractionManagerDel(int id);
```

### swPersistManager
PersistManager is a mechanism for saving game objects to file system. SOA (Service Oriented Architecture)

```c
//Functions
int   swPersistManagerAdd(void(*saveFunc)(FILE *,void*), void *obj);
void  swPersistManageDel(int id);
void  swPersistManagerExecute(FILE *file);
```

### swScheduledManager
It provides an api that's time dependent trigger. You can register your function and set trigger time. Or after an operator you register and say trigger my function 5 second after.

 * In demo first service provide time band trigger mechanism. You only register you callback functions when demo initialize.
 * In game second service provide to set wating time in operations.

```c
//Functions
void  swScheduledManagerAdd0(void(*scheduledFunc)(void*), void *obj,float triggerTime);
void  swScheduledManagerAdd1(void(*scheduledFunc)(void*), void *obj,float waitingTime);
```

### swPhys
Rigid body simulation on Box2D. This api support Body, Joints and Contact.

```c
//World
void swPhysWorldSetMeterOfPixelRatio(float ratio);
void swPhysWorldCreate(swRect *AABB, swVec2 *gravity,bool doSleep);
void swPhysWorldDestroy();
void swPhysWorldUpdate();
void swPhysWorldSetGravity(swVec2 *gravity);
 
//Renderer
typedef enum _swPhysRenderedItemEnum{
  SW_PHYS_RENDERED_SHAPE,
  SW_PHYS_RENDERED_JOINTS,
  SW_PHYS_RENDERED_CORESHAPES,
  SW_PHYS_RENDERED_AABBs,
  SW_PHYS_RENDERED_OBBs,
  SW_PHYS_RENDERED_PAIRS,
  SW_PHYS_RENDERED_CONTACTPOINTS,
  SW_PHYS_RENDERED_CONTACTNORMALS,
  SW_PHYS_RENDERED_CONTACTFORCES,
  SW_PHYS_RENDERED_FRICTIONFORCES,
  SW_PHYS_RENDERED_CENTEROFMASSES,
  SW_PHYS_RENDERED_STATISTICS,
}swPhysRenderedItemEnum;
 
 
void swPhysRendererSetEnabled(swPhysRenderedItemEnum type, boolean bVisible);
void swPhysRendererExecute();
 
 
//BodyDef
void  swPhysBodyDefSetPos(float x,float y);
void  swPhysBodyDefSetAngle(float angle);
void  swPhysBodyDefSetRectShapeType(float w,float h);
void  swPhysBodyDefSetCircleShapeType(float radious);
void  swPhysBodyDefSetLinearDamping(float damping);
void  swPhysBodyDefSetDensity(float density);
void  swPhysBodyDefSetFriction(float friction);
void  swPhysBodyDefSetRestitution(float restitution);
void  swPhysBodyDefSetFixedRotation(bool bfixedRot);
void  swPhysBodyDefSetBullet(bool isBullet);
void  swPhysBodyDefSetFilterGroupIndex(int index);
void  swPhysBodyDefSetPosListener(float *xListener,float *yListener);
void  swPhysBodyDefSetAngleListener(float *angleListener);
 
//Body
int   swPhysBodyCreate();
void  swPhysBodyDestroy(int bodyID);
void  swPhysBodySetUserData(int bodyID, void *userData);
void  swPhysBodyApplyForce(int bodyID, swVec2 force,swPoint pos);
void  swPhysBodyApplyForce1(int bodyID, float fx, float fy,float x,float y);
void  swPhysBodySetLinearVelocity(int bodyID, swVec2 vel);
void  swPhysBodySetLinearVelocity1(int bodyID, float x, float y);
void  swPhysBodySetLinearVelocityY(int bodyID, float y);
void  swPhysBodySetLinearVelocityX(int bodyID, float x);
void  swPhysBodySetXForm(int bodyID, swVec2 pos,float rot);
void  swPhysBodySetXForm1(int bodyID, float x, float y,float rot);
void  swPhysBodySetBullet(int bodyID,bool isBullet);
void  swPhysBodyWakeUp(int bodyID);
void  swPhysBodyPutToSleep(int bodyID);
 
//Query
float swPhysBodyGetMass(int bodyID);
bool  swPhysBodyIsBullet(int bodyID);
bool  swPhysBodyIsStatic(int bodyID);
bool  swPhysBodyIsDynamic(int bodyID);
bool  swPhysBodyIsFrozen(int bodyID);
bool  swPhysBodyIsSleeping(int bodyID);
 
//Joints
int  swPhysDistJointCreate(int bodyID1,swPoint anchor1,float bodyID2,swPoint anchor2,bool collideConneted);
int  swPhysRevoJointCreate(int bodyID1,float bodyID2,swPoint anchor,
                           float lowerAngle, float upperAngle, bool enableLimit, 
                           float maxMotorTorque, float motorSpeed, bool enableMotor);
 
int  swPhysPrisJointCreate(int bodyID1,float bodyID2,swPoint anchor,
                           swPoint axis,float lowerTrans, float upperTrans, 
                           bool enableLimit, float maxMotorForce, float motorSpeed, bool enableMotor);
 
int  swPhysPullJointCreate(int bodyID1,float bodyID2,swPoint gAnchor1,swPoint gAnchor2,
                           swPoint anchor1,swPoint anchor2, 
                           float ratio,float maxLength1, float maxLength2);
 
int  swPhysGearJointCreate(int bodyID1,float bodyID2,int joint1,int joint2,float ratio);
void swPhysJointDestroy(int jointID);
```

### swMousBehaviour
This api provides to listen mouse behaviour

```c
//Structure
typedef struct _swMousBehaviourListener{
  void (*pressed)(float,float);
  void (*released)(float,float);
  void (*dragging)(float,float);
  void (*moving)(float,float);
}swMousBehaviourListener;
 
//Functions
void  swMousBehaviourInit();
void  swMousBehaviourDeInit();
void  swMousBehaviourAdd(swMousBehaviourListener *listener);
void  swMousBehaviourDel(swMousBehaviourListener *listener);
void  swMousBehaviourExecute(swMouseState *mousState);
```

### swKeybBehaviour
It's responsible to notify keyTyped. In textbox, console, etc.. we need to listen keyboard events and convert to Unicode. This class gives you typed char. So you can easily write your textbox or console app..

```c
//Structure
typedef struct _swKeybBehaviourListener{
   void (*typed)(char c);
   void (*pressed)(swKeyEnum key);
   void (*released)(swKeyEnum key);
}swKeybBehaviourListener;
 
//Functions
void  swKeybBehaviourSetTypedSleepTime(float dTime);
void  swKeybBehaviourAdd(swKeybBehaviourListener *listener);
void  swKeybBehaviourDel(swKeybBehaviourListener *listener);
void  swKeybBehaviourExecute(swKeyboardState *keybState);
```

### swDSL
Domain Spesific Language

```c
//Functions
void  swDSLRegisterCommand(void(*cmdFunc)(int,swArg *cArgs),char *cmdName,int count,swArg *cArgs);
bool  swDSLExecuteCommand(char *fullCmd);
```




