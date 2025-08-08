ENGINE:
    The Dull engine is a game engine template with many modifiable components for specific use cases.
    This engine is a collection of systems which work together to create an Application.

APP:
    The app is the main class responsible for processing all the systems and all other components of this application.
    This is a singleton class ensuring only one instance of an application at a time.
    This class also holds ownership of all systems and nodes of the application.

SYSTEMS:
    The core feautures and functionalities of a game are divided into its own system.
    Eg: Render System, Audio System, Signal System, Time System, etc...
    Some systems can be modifided to perform more optimally to set your use case.
    Such as writing your own grid render system based on tilemaps and coordinates.

NODE: 
    Nodes are the base class for all processing elements of the application.
    Eg: Player, Enemy, Collectibles, etc...
    The node is a data structure which is updated every frame.
    Nodes are collected in groups (Scenes) and processed from within the scene.

SCENE:
    The scene is a collection of nodes.
    All nodes which will be processed at this current instance should be present in the current scene.
    Only one scene can be active at a time.
