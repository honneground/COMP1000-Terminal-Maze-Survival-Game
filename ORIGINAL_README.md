#
#Student Name: YE Hongran
#Student ID: [REDACTED]
#

## Synopsis
Assignment-02 of UCP

## Overview
A simple ASCII-based game where the player moves through a maze map while collecting the key. The game is played in a terminal window and relies on continuous input without the need for the Enter key.

## Syntax
Usage: ./maze <map_file_name>
- You can optimize the monster's path choice by ending the focusing movement 
  (allow the monster to be stuck if there is no closer path) at each step in the makefile
  , just replace the "CONDITION= -DKEEPMOVING" with "CONDITION=" in line 6.

## Contents
maze:
Executable file of the game.
linkedlistTest:
Executable file of the linked list test cases.
main.c: 
Initialises the game and passes data between modules.
game.c: 
Handles player movement, provides a quick reference to player coordinates, modifies the map data, and manages the game state.
map.c: 
Handles the translation and printing of map data.
algorithm.c: 
provides utility functions to determine the minimum and maximum values of two given integers.
terminal.c: 
Enables continuous input without the need for the Enter key. Downloaded from assessment attachments, no comments made.
world.c: 
Generates the map data. Downloaded from assessment attachments, no comments made.
linkedlist.c: 
The generic linked list implementation.
linkedlistTest.c: 
The generic linked list implementation test.

## Memory Leak Detecting
valgrind --leak-check=full ./program

## Dependencies
YE Hongran Assignment-01 of UCP

## Version information
23/05/2023  - final version of Assignment 01 maze game programs

