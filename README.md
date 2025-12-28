# Dull Engine

## Overview

**Dull Engine** is a lightweight engine structured around a central application loop and a hierarchical processing model.

## Workflow

- The `App` class is the main application entry point and lifecycle manager.
- `App` is responsible for initializing and shutting down all required engine systems.
- Runtime logic is driven through the `IProcessor` interface, which defines the engine’s update phases.
- The active processor implementation can be configured via `dull::config::Processor`.

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

- **`Scene`**
  - Holds references to a collection of `Layer` objects.
  - Processes only the layers that are currently active.
  - Does not own layers; it only tracks and orchestrates them.

- **`World`**
  - Owns multiple `Scene` instances.
  - Only one scene is processed at any given time.

Any of the above processors can be used in `dull::config::Processor`.

## Development Features

- Use `misc::LayerBuilder` for easier Layer creation.
- Use `misc::SceneBuilder` for easier Scene creation.
- Create `core::App` class before handling other engine features.
