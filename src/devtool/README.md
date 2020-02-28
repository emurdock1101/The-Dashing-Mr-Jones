


> Written with [StackEdit](https://stackedit.io/).# Dev Tool

## Compiling and Running
You can compile the dev tool with:

```
make bin/devtool
```

Then, the dev tool can be ran with:

```
bin/devtool
```

## Using the Dev Tool

Feature | Command | Description
--- | --- | ---
Load Scene | `l` | Loads scene from relative filepath, eg `./resources/scenes/Scene1.txt`
Save Scene | `s` | Loads scene from relative filepath, eg `./resources/scenes/NewScene.txt`
Copy | `c` | Copies the selected sprite
Paste | `v` | Pastes the copied sprite one grid tile down, one to the right
Edit sprite | `e` | Edits the id, scale, pivot, and rotation of the selected sprite. Press `n` to keep the same
Add child | `ctrl + click` | Adds the clicked sprite as a child of the selected sprite
Delete | `backspace` | Deletes the selected sprite and its children
Move Selection Menu | `q` and `w` | Moves the top selection menu left or right
Camera | Arrow keys | Moves the viewing window up, down, left, or right
Animations | `a` | Add an Animated Sprite to the screen. You can add as many animation animations as you want. For the basebath, enter the folder that the base image belongs in. For us, this is `./resources/character/`. Don't forget the extra slash on the end. For name, enter the name of each animation as it appears in the file. For the girl character, enter "Idle", "Dead", "Run", etc. In the edit screen, you can stop/start the animation, or change the animation. The sprite will appear at {100,100} and then you can move it wherever you want.


