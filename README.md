path-tracer
===========

Little global illumination Monte Carlo path tracer

[![Build Status](https://semaphoreapp.com/api/v1/projects/f17e953b-83a4-4364-a2e3-04e1f126be21/317820/shields_badge.svg)](https://semaphoreapp.com/sdao/path-tracer)

Dependencies
------------
If you're on OS X, I suggest using [Homebrew](http://brew.sh/) to get the right
dependencies. If you're on Linux, you can use your package manager.

* [Eigen](http://eigen.tuxfamily.org/)
  (template library)
* [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/)
  (links with libtbb)
* [OpenEXR libraries](http://openexr.com/)
  (links with libIlmImf and libHalf)
* [Open Asset Import Library](http://assimp.sourceforge.net/)
  (links with libassimp)
* [Boost](http://www.boost.org/)
  (template libraries; also links with libboost_program_options)
* [Intel Embree](http://embree.github.io/)
  (links with libembree)
  * Note: Embree is not available from Homebrew. A quick-and-dirty Homebrew
    formula for installing the Embree binaries is available
    [here](https://gist.github.com/sdao/5d51acc7b1f983a7a063).
  * If you'd like to do things yourself, you can download binaries from
    [http://embree.github.io/](http://embree.github.io/) or compile from
    source. Prebuilt x64 binaries are available for Windows, Mac OS X, and
    Linux.

Reference
---------
Some of the comments make reference to Pharr and Humphreys' text
[*Physically Based Rendering*](pbrt.org), 2nd edition (Morgan Kaufmann, 2010).
This excellent resource describes the `pbrt` renderer in a literate
programming style.

My renderer is also influenced by Kevin Beason's
[smallpt](http://www.kevinbeason.com/smallpt/) path tracer.

Renderings
----------
![Cornell box](https://raw.githubusercontent.com/wiki/sdao/path-tracer/pathtracer_dragon_800iters_30min.png)
![Spheres with depth of field](https://raw.githubusercontent.com/wiki/sdao/path-tracer/pathtracer_spheres_800iters_20min.png)
