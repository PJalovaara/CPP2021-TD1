# Test files

It is a common practice to do unit tests of each class before you integrate it into the project to validate its operation.
In this folder, you can create your own unit test files to validate the operation of your components.

> It might be a good idea to also take some notes about the tests since you are required to 
  report these in the final report.

# Unit Tests

## Test nro 1 of class Game

We start the game with no towers nor enemies to check for memory leaks. We open the window and close the window.

**Involved Classes:** Game

**Test run:** test1

**Results:** A ton of memory leaks which are probably not possible to fix by us. The errors regard the Qt library functionality



## Test nro 1 of class Enemy

We let enemies pass through and get destroyed.

**Involved Classes:** Game

**Test run:** test2

**Results:** Valgrind error: we deleted the enemy too early in the MoveForward function. Fixed by writing the delete this later on in the code.


## Test nro 1 of class Tower

We put up a tower and use the remove functionality

**Involved Classes:** Game

**Test run:** test3

**Results:** Valgrind error: Memory was lost. Possible fix: Implement the destructor for the tower. Fixed by calling the removeItem of the parent.


