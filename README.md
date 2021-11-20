<h1 align="center" style="font-size: 3rem;">
Cligol
</h1>

&nbsp;

Simple Conway's Game of Life (cli edition) simulation using C++ with ncurses.


# How to run:

``` sh
git clone https://github.com/emanuel2718/cligol.git
cd cligol/
make -k && ./cligol
```

# Preview:

https://user-images.githubusercontent.com/55965894/142735706-cdee3617-c2c2-4c66-8025-8f4aab44cace.mp4


# Useful keybinds:

    * `ESC` : quit application
    * `q`   : quit application
    * `h`   : show keybind help menu
    * `b`   : go back
    * `p`   : toogle pause/play
    * `UP`  : increase simulation speed
    * `DOWN`: decreas



# TODOLIST:

- [ ] add documentation to README
- [ ] refactor enum classes to camelCase and values to NON-CAPS (avoid conflict with macros)
- [ ] refactor the way map handling works completely
- [ ] maybe make a map generator
- [ ] make the keybind menu work in the running simulation?
- [ ] add button info on screen instead of debug coordinates
- [x] add speed button
- [x] change the round reference ---> generation
- [x] add +1 to speed number so that 1 is the lowest speed
- [x] if simulation is paused; changing speeds triggers generation update
