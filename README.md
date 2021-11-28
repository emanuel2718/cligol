<h1 align="center" style="font-size: 3rem;">
Cligol
</h1>

&nbsp;

Simple Conway's Game of Life (cli edition) simulation using C++ with ncurses.


# How to run:


### Clone repository

``` sh
git clone https://github.com/emanuel2718/cligol.git
cd cligol/
```

### Build cligol

``` sh
mkdir build/ && cd build
cmake ..
```

### Run cligol

``` sh
make && ../bin/cligol
```



# Useful keybinds:

* `ESC` : quit application
* `q`   : quit application
* `h`   : show keybind help menu
* `b`   : go back
* `p`   : toogle pause/play
* `UP`  : increase simulation speed
* `DOWN`: decrease simulation speed



# TODOLIST:

- [ ] add simulation preview
- [ ] refactor the way map handling works completely
- [ ] maybe make a map generator
- [ ] make the keybind menu work in the running simulation?
- [x] add speed button
- [x] change the round reference ---> generation
- [x] add +1 to speed number so that 1 is the lowest speed
- [x] if simulation is paused; changing speeds triggers generation update
- [x] add documentation to README
- [x] refactor enum classes to camelCase and values to NON-CAPS (avoid conflict with macros)
