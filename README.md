WMCS006-ACG-CatmullClark-Tesselation

This is a CatmullClark Tesselation program build as part of the Advanced Computer Graphics course at the RUG.

It includes:
- CatmullClark subdivision inlcuding boundaries. (Provided by lecturer)
- Half Edge datastructure for storing vertices. (Provided by lecturer)

I implemented:
- Computation of limit positions of vertices and appropriate visualization. 
- Code to get all regular quads. (4 verts, surrouned by quads)
- Tesselation Shaders to tesselate the surfacequads as B-Spline surfaces.
- Computation of analytical normals using partial derivatives of B-Spline basis functions.
- Approximate visualization of flat shaded triangle surface of the mesh.
- Tesselation patch tesselation levels configuration.

It uses OpenGL for rendering.
