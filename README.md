ABCg
======

Development framework accompanying the course MCTA008-17 Computer Graphics at [UFABC](https://www.ufabc.edu.br/).

----

### Eduardo's modifications

This repository also includes my (Eduardo's) modifications to the
`abcg` framework, developed as projects during the course.

Currently, you can find the following projects in the `examples` folder:

- *GL-Ball*: A simple Arkanoid clone, with some influences from the
  `DX-Ball` DOS game and the `One More Brick` mobile game. [live demo](https://renesto.netlify.app/courses/cg/gl-ball) [report](./reports/a1.gl-ball.pdf)
- *A Completely Normal Tour of Sponza*: A demo loading and rendering
  the Crytek Sponza scene, using an ECS architecture, with lazy
  loading. For now it doesn't load textures, it uses the vertex
  normals as the colors instead. [live demo](https://renesto.netlify.app/courses/cg/sponza) [report](./reports/a2.sponza.pdf)
- *A Very Shaded Tour of Sponza*: An improvement of the previous
  project, implements a fully deferred rendering pipeline, with
  textures and multiple light sources. [live demo](https://renesto.netlify.app/courses/cg/sponza-pretty) [report](./reports/a3.sponza-pretty.pdf)
  
### Reports

The above modifications have corresponding written reports, explaining
their development. They are written in Markdown + LaTeX, and converted
to PDF using Pandoc. Both the sources and the resulting PDF files can be
found in the `reports` folder.

### Credits

Developed by Harlen Batagelo.

### License

ABCg is licensed under the MIT License. See [LICENSE](https://github.com/hbatagelo/abcg/blob/main/LICENSE) for more information.
