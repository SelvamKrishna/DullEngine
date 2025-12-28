# Todo

- [ ] Use unique ID's (numeric value) to distinguish Layers, Scenes, Nodes
  - Improves Memory efficiency and performance
  - Names to be used for debugging purpose only
  - Similar to ECS

- [ ] Render System implementation
  - Rendering to be done seperately from processing
  - Processing elements provide Render System with needed Render Calls
  - Render Systen to be abstact
  - Allows smooth integration of custom Render Systems into engine
  - Developer is required to write his own Rendering logic (or use pre-existing templates)
  - Eg: SpriteSheet Renderer, UI Renderer, Texture Renderer

- [ ] Render Master implementation
  - App holds a Master Renderer which is a collection of Render Systems
  - Allows smooth integration of multiple Render Systems
