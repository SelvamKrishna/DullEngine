# Todo

---

## refactor: Event System

- Events are now inherited from Identified making each event object possess a uniqe ID.
- IEvent is an interface which automates the ID generation property of Events
- EventSystem now stores Event::ID -> List of all Listeners

---

## impl: Render System

Processing elements provide Render System with needed Render Calls. Render Systen should support abstaction
similar to Nodes allowing smooth integration of custom Render Calls into engine. Developer is
required to write their own Render System (or use pre-existing templates).

Eg: SpriteSheet Renderer, UI Renderer, Texture Renderer.

---
