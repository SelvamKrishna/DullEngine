# Todo

---

## [x] impl: Unique ID

**Goal :**

Using numeric ID instead name improves memory efficiency and performance.
Names can be stored externally for the sake of debugging and completely ignored in Release Build.

**Target :**

- [x] Unique ID for processors stored within respective processor
- [x] Unique ID Generation w/ ID Generator
- [x] Name property seperation from processors
- [x] Name property stored within Identified class (auto evict on Release)
- ~~[ ] Make ID generation a templated trait for Buffer~~
- ~~[ ] Store Name within a Dynamic List inside respective Buffer~~
- ~~[ ] Unique ID Generation and assignment logic w/ Buffers~~

**Notes :**

ID generation is done by Identfied class. Every unique identifiable element now inherits Identified Class.
Buffer intakes Data which inherits from Identified and stores them in ascending order (using ID).

---

## [ ] impl: Render System

**Goal :**

Processing elements provide Render System with needed Render Calls. Render Systen to be abstact
similar to Nodes allowing smooth integration of custom Render Systems into engine. Developer is
required to write their own Render System (or use pre-existing templates).

Eg: SpriteSheet Renderer, UI Renderer, Texture Renderer.
