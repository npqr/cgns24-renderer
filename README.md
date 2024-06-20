# cgns24-renderer
This repository contains the source files for the 3D Renderer implemented under the Summer 2024 Offering of the Computer Graphics and Shaders Project under Game Development Club, SnT Council, IIT Kanpur.

## Task-1

- [ ] Modify Input Detection such that pressing <kbd>R</kbd> key rotates the figure towards right and pressing <kbd>L</kbd> key rotates it towards left.
- [ ] **Color Morphing Rectangle:**
  - [ ] Draw a rectangle with four different colors at its corners (loaded via color vertex data).
  - [ ] Define multiple color sets for the corners of the rectangle.
  - [ ] Define a time period for a complete cycle $T$ and the current time in the cycle $t$.
  - [ ] Load all the variables (colors, time period $T$, current time $t$ as `uniform`s to the shader.
  - [ ] Use [bilinear interpolation](https://en.wikipedia.org/wiki/Bilinear_interpolation) to smoothly transition between the colors based on the current time.
  - [ ] Allow the user to control the morphing speed via a UI slider.
  - [ ] The end result should be something like:
    - At $t = 0$, corners are colored with set 1: $(C_1, C_2, C_3, C_4)$
    - At $t = \dfrac{T}{2}$, corners are colored with set 2: $(C_5, C_6, C_7, C_8)$
    - At$t = T$, corners are colored back to set 1: $(C_1, C_2, C_3, C_4)$
- [ ] ShaderToy : 
  - [ ] Make a checker-board in shadertoy/or simple `.fs` file
- [ ] Texture : 
  - [ ] Load an image of your choice and render it on the rectangle.
- [ ] UI : 
  - [ ] Make a new UI window.
  - [ ] Make two check box variables 'Draw Triangle' and 'Draw Rectangle', checking either of which draws that respective shape.
  - [ ] Provide a means to change texture of rectangle at runtime.
  - [ ] Make another checkbox for showing/hiding frame rate in that window.
  - [ ] Make one more checkbox for [VSync](https://en.wikipedia.org/wiki/Screen_tearing).

### Instructions for submissions:
- Fork this repo if you have not already.
- Clone YOUR forked repo to your local machine.
- Checkout to the Task-1 branch.
- Finish tasks given above and commit.
- Push the commits to the Task-1 branch of YOUR origin
- Send a PR to the Task-1 branch of upstream. (upstream is the original repo)

### The final output should somewhat look like this


### **Note** : The following samples are shown for the original figure as triangle, you need to do it with a rectangle in this task. 

| Plain colour | Color cycle | Rotation |
| :-: | :-: | :-: |
| ![1](https://github.com/npqr/cgns24-renderer/assets/96120993/d13e8dc5-4d71-4e8f-86b3-8cfae8f30d42)| ![2](https://github.com/npqr/cgns24-renderer/assets/96120993/ba3bda27-5aa2-40b9-a721-5e82a6101dad)|![3](https://github.com/npqr/cgns24-renderer/assets/96120993/25c3b9d0-60e7-40fe-9018-7e3718fada19)|
| Triangle | Rectange | Tri + Rect |
|![4](https://github.com/npqr/cgns24-renderer/assets/96120993/89b15b53-1c50-4822-bc92-c4e6539bb94d)| ![5](https://github.com/npqr/cgns24-renderer/assets/96120993/6cc4ac7c-1d17-4142-b8cd-9645f9ad8491)| ![6](https://github.com/npqr/cgns24-renderer/assets/96120993/d0bf58fb-89fb-4357-8502-b063c7fb549b)|
|  Multi-texture  |  VSync  |   .  |
|![7](https://github.com/npqr/cgns24-renderer/assets/96120993/c2361697-b643-4126-8dfd-f5a3eb72cb80)|![8](https://github.com/npqr/cgns24-renderer/assets/96120993/77546420-c33b-486c-ae0f-cf469ed4cbc9)
  |  .   |
| t = 0 ->T/3 | t = T/3 -> 2T/3 | t = 2T/3 -> T |
| ![9](https://github.com/npqr/cgns24-renderer/assets/96120993/3b668722-bf66-466a-a060-5e602e6e52e4) | ![10](https://github.com/npqr/cgns24-renderer/assets/96120993/7d4ffe0d-39b0-4bf2-9203-276b23a003a7)| ![11](https://github.com/npqr/cgns24-renderer/assets/96120993/3de59dbd-5db3-4fde-80bb-948f886bcdbc)|
