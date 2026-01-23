# Dull Engine

- The `core::App` class is the main application entry point and lifecycle manager.
- `core::App` is responsible for initializing and shutting down all required engine systems.
- Runtime logic is driven through the `IProcessor` interface, which defines the engine’s update phases.
- The active processor implementation can be configured via `config::Processor`.
- Create `core::App` class before handling other engine features.

## Processor

The `IProcessor` interface defines the core update hooks used by the engine.

- `iStart()` — called once at initialization.
- `iProcess()` — called every frame.
- `iFixedProcess()` — called at a fixed timestep.

- **`Direct`**
  - A simple processor
  - Used for basic logic processing

- **`Node`**
  - An absract processor class.
  - Must be inherited to add custom logic.

- **`Layer`**
  - owns and processes a collection of `Node` instances.
  - Acts as a logical grouping of related nodes.
  - Use `misc::LayerBuilder` for easier Layer creation.

- **`Scene`**
  - Holds references to a collection of `Layer` objects.
  - Processes only the layers that are currently active.
  - Does not own layers; it only tracks and orchestrates them.
  - Use `misc::SceneBuilder` for easier Scene creation.

- **`World`**
  - Owns multiple `Scene` instances.
  - Only one scene is processed at any given time.

Any of the above processors can be used in `config::Processor`, except `Node`.

## AudioSystem

Responsible for loading, managing, and updating all sound and music resources in the engine.

- Built on top of **raylib’s audio module**.
- Manages **Sound** and **Music** resources via ID-based lookup.
- Centralized access through `DULL_CTX.audio_sys`.
- Logging can be enabled via `config::SHOULD_LOG_AUDIO_SYS`.
- For better performance reserve Buffers using `AudioSystem::reserveSoundBuffer()` & `AudioSystem::reserveMusicBuffer()`.

- **`util::Sound`/`util::Music`**
  - *`util::Sound`:* Fully loaded audio clip (e.g. sound effects).
  - *`util::Music`:* Streamed audio (e.g. background music).
  - Wrapper for `rl::Sound` & `rl::Music` respectively.
  - *Load*, *Unload*, *Access* and *Modify* using `DULL_CTX.audio_sys`.

- **`component::Sound`/`component::Music`**
  - Handle for `util::Sound` & `util::Music` respectively.
  - Can be created directly within a Node.
  - Does the underlying loading (created with path) / copying (created with ID).

## EventSystem

Responsible for managing and dispatching events throughout the engine.

- Centralized access through `DULL_CTX.event_sys`.
- Logging can be enabled via `config::SHOULD_LOG_EVENT_SYS`.
- Events are identified by types, Any data type can be used as event data.
- Listeners can be function pointers, functors, or lambda expressions.
- Listeners can be binded to `EventT` using `EventChannel<EventT>::subscribe()`.
- Listeners can be unbinded to `EventT` using `EventChannel<EventT>::unsubscribe()`.
- Events can be dispatched using `EventSystem::emit<EventT>()`.

## RenderSystem

Responsible for managing and updating all render calls throughout the engine.

- Centralized access through `DULL_CTX.render_sys`.
- For better performance reserve Buffers using `RenderSystem::reserveOneFrameBuffer()` & `RenderSystem::reservePermanentBuffer()`.

- **`misc::IRenderCall`**
  - Interface for render calls.
  - Must be inherited to add custom render calls.
  - `misc::IRenderCall::iDraw()` is called every frame.

- **Permanent/One-Frame Render Calls**
  - Permanent render calls are stored until removed.
  - One frame render calls are removed after each frame.
  - `RenderSystem::addPermanentCall()` & `RenderSystem::addOneFrameCall()` are used to add render calls.
  - Remove permanent render calls using `RenderSystem::removePermanentCall()`.

- **`misc::PermanentRenderCall`**
  - Wrapper for `misc::IRenderCall` reference.
  - Manages the active state of a render call.
  - `misc::PermanentRenderCall::setActive(bool)` can be used to bind the render call to the render system.
  - *Warning*: The underlying render call must outlive the `misc::PermanentRenderCall`.
