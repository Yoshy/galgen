# Galaxy generation library for C++

This is a simple library for generating random galaxy-like structures.
It generates an array of points in 3D, roughly resembling star arrangement in real-world regular spiral galaxies.

The library has no dependencies, except for standard C++ libraries.

In order to build galaxy viewer Urho3D (https://urho3d.github.io/) is required.

# Building

Use CMake Build Process &#8482

One can build only library without a viewer. To do so, CMake it on a source directory `src/libgalgen`.

# Examples

## Regular spiral galaxy

### 100 stars
![r_100.png](https://github.com/Yoshy/galgen/raw/master/examples/r_100.png)

### 5000 stars
![r_5000.png](https://github.com/Yoshy/galgen/raw/master/examples/r_5000.png)

## Toon spiral galaxy

### 50 stars, 8 arms, no deviation
![t50_8.png](https://github.com/Yoshy/galgen/raw/master/examples/t50_8.png)

### 150 stars, 3 arms, no deviation
![t150_3.png](https://github.com/Yoshy/galgen/raw/master/examples/t150_3.png)

### 300 stars, 6 arms, average deviation
![t300_6.png](https://github.com/Yoshy/galgen/raw/master/examples/t300_6.png)
