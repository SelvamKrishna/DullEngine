# Todo

---

## impl: Audio System

**Goal :**

Holds a buffer of sound effects and music streams. Must provide flexibile sound resource loading.

---

## refactor: Event System

**Goal :**

- Typed events

```cpp
// instead of
Event e {"OnDamage"};
e.setData("amount", 10);
// Do
struct DamageEvent {
  int amount;
  EntityID target;
};
// Then
Event<DamageEvent> onDamage;
onDamage.bind([](const DamageEvent& e) {
  ...
});
```

---

## impl: Render System

Processing elements provide Render System with needed Render Calls. Render Systen should support abstaction
similar to Nodes allowing smooth integration of custom Render Calls into engine. Developer is
required to write their own Render System (or use pre-existing templates).

Eg: SpriteSheet Renderer, UI Renderer, Texture Renderer.

---
