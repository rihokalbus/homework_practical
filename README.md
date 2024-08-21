# Practical part of the homework
## Description
In this homework, a project with a dynamically extensible structure has been implemented. Assuming that the number
of developers and modules under development will be small to medium, I decided to stick with one repository project with
a flat structure.\
All modules belonging to the project are in separate subdirectories. In addition, an include subdirectory is defined,
which contains project-wide header files. A CMake macro, defined in the main directory's CMakeListtxt file, scans
through the subdirectories of the project and automatically adds the directories in which CMakeListtxt exists.\
As a demonstration, four subprojects have been implemented during the project - one library and three modules
(drive, power pack and cooling) that implement simple ping pong over UDP according to the task description:
* Drive will send out ping, cooling and powerpack will respond.
* Drive will write to standard output:
  * On receiving pong (source and measured ping time).
  * On communication error or on timeout.
* Cooling and powerpack will write to standard output:
  * On receiving ping.
## Building project
In the main directory:
```
cmake .
cmake --build .
```
## Installation
```
cmake --install . --prefix "/path/to/destination/directory"
```
## Running project
```
cd /path/to/destination/directory
./cooling
./powerpack
./drive
```