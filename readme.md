# Another-Kawaii-Chip-8-Emulator
AKCemu for short, is a Chip-8 emulator made with C++ using OpenGL 3.3 as its graphics backend, it also uses SFML audio module for sounds, and GLFW for windowing and input handling
## Usage
From terminal opened inside "bin" folder run:
```
./akcemu ../<your rom name>.ch8
```
or if you want to specify a resolution
```
./akcemu <height> <width> <your rom name>.ch8
```
if any errors occured, a log file will auto-generate containing what error happened
## Runtime Prerequisites
- [GLFW](https://www.glfw.org/) runtime libraries
- [GLEW](http://glew.sourceforge.net/) runtime libraries
- [SFML](https://www.sfml-dev.org/) audio runtime libraries
## Building
### Prerequisites
- [GLFW](https://www.glfw.org/) dev libraries
- [GLEW](http://glew.sourceforge.net/) dev libraries
- [SFML](https://www.sfml-dev.org/) audio dev libraries

With Meson Build System and prerequisites installed on your machine, run:
```
meson builddir --buildtype=release
cd builddir
ninja
```
## Contribution
Feel free to fork, create issues or make a pull request, I'll do my best to check them out.
## License
This project is under MIT License.
```
Copyright (c) 2021 Mohammad Issawi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
Audio "beeping" file was downloaded from [Zapslat](https://www.zapsplat.com/)
### Made with love and 8-bit kittens :)
