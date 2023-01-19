# engicalc
Calculator for Engineers
## Mechanics
The Fundamental Theorem of Engineering

e = 3

pi = 3

4 = 3

sin(x) = x

cos(x) = 1

If it is close enough, then it is good enough.
## Compilation
Run the following commands in your terminal.
```
clang -std=c99 -O3 -c engi.c eval.c math.c
clang -o engi.out engi.o eval.o math.o -lm
```
Or, if GNU Make is present, run `make` command.
## Installation
Binary installers may be present in Releases, if you followed instructions to compile, then.
```
mv engi.out /usr/local/bin/engicalc
```
Or if GNU Make is present, run `make install` command.

If you get a permission error, you may need to run the command as superuser by appending sudo in front of it.

If you are using Windows, you will need to use Windows Subsystem for Linux.
Alternatively, you may port this program to Windows and submit a pull request.
## Usage
Type a number to enter a number, type these following keys to use a mathematical operation.
This program is case insensitive.

q to quit

= or RETURN to evaluate the result

backspace to undo last action that was not a backspace

+, -, \*, / for addition, subtraction, multiplication, and division respectively

n to negate the current number

a for square root

d for cube root

** or ^ for exponentiation

s for sin

c for cos

t for tan

r for cot

y for sec

u for csc

e for the base of all natural logarithms

p for the ratio between the semicircumference and the radius of a circle
