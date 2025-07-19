# 2D Platformer Engine

> This project is currently in **early development**. Expect of course incomplete features and heavily unoptimized code.

A lightweight 2D platformer engine built in C++ using the SDL2 Media Library.
---

## Features (Planned)

- [x] Entity-based architecture with player support
- [x] Sprite rendering via SDL2
- [x] Basic 2D physics engine (gravity, velocity, acceleration)
- [x] AABB collision detection & resolution
- [x] Scene / level loading
- [ ] Animation system (in progress)
- [ ] Tilemap support
- [ ] Sound and music support
- [ ] Controller input

---

##  Build Instructions

### Requirements

- C++17 or later
- [SDL2](https://www.libsdl.org/) (image, mixer, ttf if needed)
- CMake (recommended)
- Linux / macOS / Windows
- Patience and / or having a liking to see horrible code

### 🧱 Building

```bash
git clone https://github.com/your-username/your-repo-name.git
cd your-repo-name
mkdir build && cd build
cmake ..
make
./GameExecutableName
