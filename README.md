# SM Macro V0.1.0

Target:
- Geometry Dash 2.2081
- Geode 5.10.1
- Android64

This package is **source code**, not a compiled `.geode`.

## Phone-first build

The repository includes a GitHub Actions workflow that can build an Android64 `.geode`
using Geode's official build action. This is intended to make the project usable from a
phone without requiring the Android NDK to be uploaded to the chat.

## Native macro format

SM uses `.sm` as its native macro format.

Magic header: `SM01`

## Local build

If you have a configured Geode development machine:

```text
geode build -p android64
```

The Android build output is placed in the `build-android64` directory.

## Current state

V0.1.0 contains the macro data model, recorder/player foundation, and Pathfinder interface.
Actual Geometry Dash input injection and game-state sampling remain the integration layer
for later tests.
