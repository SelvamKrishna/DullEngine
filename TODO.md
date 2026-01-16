# Todo

---

## refactor: Event System

Event System has been refactored to use Event Channels. Event Channels provide better
abstraction and decoupling between event producers and consumers.

- Improve Event Listener storage.

- Goal:

---

## impl: Render System

Processing elements provide Render System with needed Render Calls. Render Systen should support abstaction
similar to Nodes allowing smooth integration of custom Render Calls into engine. Developer is
required to write their own Render System (or use pre-existing templates).

Eg: SpriteSheet Renderer, UI Renderer, Texture Renderer.

---
