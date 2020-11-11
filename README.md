# GameofLife
C++ code for the game of life

Modes:
1. Regular
2. Donut
3. Mirror

Rules to the game:
  1. A location that has one or fewer neighbors will be empty in the next generation. If a cell was in that location, it dies of loneliness.
  2. A location with two neighbors remains stable. If there was a cell, there’s still a cell. If it was empty, it’s still empty.
  3. A location with three neighbors will contain a cell in the next generation. If it currently has a cell, the cell lives on. If it’s empty, a new cell is born.
  4.A location with four or more neighbors will be empty in the next generation due to overcrowding.
