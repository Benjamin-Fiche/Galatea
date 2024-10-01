# Galatea alpha: Release notes

## Installation

### Galatea API

1) Start the Visual solution (.sln) from Galatea folder

2) Compile in Debug x64 mode if you want to use the editor or just compile in DebugExe x64 to play the simulation directly

### Galatea Editor

3) Start the Visual solution (.sln) from Editor folder

4) Press Local Windows Debugger (F5) to start the editor in Debug x64

5) To start the game simulation, press the play button in the editor or press F5, to pause the simulation press the pause button or press F6 and f5 again if you want to stop the game

## New features

- Physics:
  - Add capsule collider
  - Add customization options in RigidBody
  - Rework Get/Set in RigidBody to not recreate a physX actor everytime
  - Add trigger
  - Add overlap event (enter/exit)
- Engine :
  - Add Quad2D
  - Improvement in multiple classes
  - Multiple correction
- Sounds
  - 3D sounds with multiple customization functions
- Editor
  - Play/Stop with F5
  - Pause/Resume with F6
  - Project file browser in Editor
- Gameplay
  - Doors opening when player has the same gravity (playing a sound)
  - Improve Level Design
  - Interactable Object's color changing according to it's gravity
  - Interactable Objects are freezable
  - Gun model added (he cannot harm you don't worry)

## Bugs fixed

- Bug in the save where some data doesn't save correctly (may not come directly from the save methods but before that)
- Change data in the inspector doesn't change the data
- Player not moving correctly when he change his gravity (not implemented yet)

## Bugs

- Compilation with Release Not Working
- Custom Component not implemented yet

## Credits

### Programmers

Alexandre CAZIER, Benjamin FICHE, Adrien TELLIER, Rémi VINCENT

### Producers

Vincent LAFON, Stéphane PONTADIT

### Special thanks to
  - Isabelle POTTIER from Graphic Id for the Galatea's logo
