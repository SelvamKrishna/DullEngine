This is a OOPS engine built on top of raylib.

Engine Pipeline:

1. App is started.
2. App processes the current scene.
3. Scene is a tree like structure of nodes.
4. Nodes are processed in level order. root -> leaves.
5. ... TBC.

Core:
  App: The main instance of the Application.
    + scene.
    + systems. (mod)
    * Singleton.
    * Updates the scene once every frame.

  Scene: The collection of Nodes.
    + root of the node tree.
    * Traverses thru the tree and updates them.

  Node: The building block of the application
    + unique name.
    + parent.
    + list of children.
    * A Interface.

Todo:
  Remove the need for Scene Class.