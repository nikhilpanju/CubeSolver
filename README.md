# CubeSolver

An application which solves any state of a Rubik's cube (and other puzzles) based on text input or GUI input

## Download
Install CubeSolver 2.5 using the CubeSolverSetup.exe file in the /Setup folder

## Instructions
#### GUI:
Colour the cube using the palette provided, select the **GUI Input** radio button and click **Solve** to get a solution.
(Note: Square-1 state cannot be set using GUI)
Twisted corners, flipped edges, incorrectly coloured block are **unsolveable** and hence a solution will not be provided

#### Scramble:
Provide a scramble text, select the **Scramble Input** radio button and click **Solve** to get a solution.
Scrambles must be of the format "F' L' B R U L2 B' L' D R L2 U2 F2 B' L2 U2 D2 B U2 F2 U2" where `'` and `2` indicate 90 degree counterclockwise turns and 180 degree turns respectively. There must be no space between a Letter and it's turn suffix.

For pyramix, lowercase letters signify tip rotation.

For square 1, the scramble must be of the format `(<U turn>, <D turn>)/`
For example: `(3, 2)/(3, 6)/(6, 0)/(-5, -5)/(-4, 0)/` (Space is included only after a comma)

#### Provide Scramble & View Scramble:
You can also choose to provide a scramble and the app will generate a scramble for you. Click on the **Provide Scramble** button to do so.
Click the **View Scramble** button to view your textual scramble.

#### Clear:
Clicking on the **Clear** button will clear all data
