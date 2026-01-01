# Todo

---

## [ ] impl: Unique ID

**Goal :**

Using numeric ID instead name improves memory efficiency and performance.
Names can be stored externally for the sake of debugging and completely ignored in Release Build.
The respective Buffers are now responsible to generating and assigning ID to elements.
Because Nodes are unique among each layer we use a static NodeIDGenerator.

**Target :**

- [ ] Unique ID for processors stored within respective processor
- [ ] Unique ID generation and assignment logic w/ Buffers
- [ ] Name property seperation from processors
- [ ] Store Name within a Dynamic List inside respective Buffer
- [ ] Make ID generation a templated trait for Buffer

**Notes :**

- *Nodes are stored in sorted order within a Layer.*

| Operation | Complexity | Description |
| --------- | ---------- | ----------- |
| Lookup | O(log n) | Binary search on sorted nodes |
| Insertion | O(n) | Requires shifting elements |
| Deletion | O(n) | Requires shifting elements |

This design prioritized lookups (done every frame) over insertion and deletion (not so often).

- *ID generation within Buffer*

Buffer's take in *ID generator* as a templated argument. This change helps smooth integration of
Nodes (which has it's own unique ID generation) into Layers.

---

## [ ] impl: Render System

**Goal :**

Processing elements provide Render System with needed Render Calls. Render Systen to be abstact
similar to Nodes allowing smooth integration of custom Render Systems into engine. Developer is
required to write their own Render System (or use pre-existing templates).

Eg: SpriteSheet Renderer, UI Renderer, Texture Renderer.
