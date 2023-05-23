# Terminal Maze with Pursuit and Undo

- **Unit**: Unix and C Programming (`COMP1000` / `UCP1000`) — Assignment 2
- **Study Period**: 2023 Trimester 1A
- **Degree Programme**: Bachelor of Information Technology — Awarded with Distinction by Curtin University
- **Overall Unit Mark**: 90 (High Distinction)

> **README for Assignment Submission**: [README for Assignment Submission](ORIGINAL_README.md)

## Assignment context

The second maze assignment builds on [the first terminal maze](../Terminal-Maze-Darkness-Game/) with a map read from a file, a moving pursuer and a history of actions stored in a generic linked list. The player must obtain the key and reach the exit while avoiding the monster. The project exercises file input, dynamically allocated maps, pointer-based data structures, modular C and terminal interaction.

## Implementation

- `main.c` reads the map, initializes the world and linked-list history, dispatches actions and releases allocated resources.
- `world.c` parses the map header and object positions. `map.txt` is the included playable map.
- `game.c` handles player/key/exit states, pursuer movement, recording actions and restoring the previous state on undo.
- The pursuer chooses among adjacent permitted moves by comparing their Manhattan distances to the player.
- `linkedlist.c` provides a generic linked list using `void *` payloads. History entries store player and monster coordinates and the player's facing direction.
- `linkedlistTest.c` is the separate linked-list demonstration/test program.
- `terminal.c` provides immediate input without requiring Enter for each action.

The Makefile enables `KEEPMOVING` for the game module. Removing that definition selects the alternative movement behavior described in the original submission README.

## Build and play

Use GCC and Make in a Linux or WSL terminal. From this directory:

```bash
make
./maze map.txt
```

The default `all` target builds both `maze` and `linkedlistTest`.

Press any key at the welcome screen. Use lowercase `w`, `a`, `s`, `d` to move, `u` to undo and `q` to quit. The undo history restores previous positions and the corresponding key state.

## Linked-list checks

```bash
./linkedlistTest
```

To inspect a play session with Valgrind, if installed:

```bash
valgrind --leak-check=full ./maze map.txt
```

Use `make clean` to remove build outputs.
