# State reduction
State reduction is a technique to reduce the state count in a state diagram

# Problem statement
Develop a state reduction approach to optimize a state diagram/sequential circuit

# Input file/format 
A state diagram S in the KISS format

# KISS format
.i <num inputs>
.o <num outputs>
.s < num-states>
.p <num-terms>
.r <reset-state>
<input> <current state> <next state> <output>
...
<input> <current state> <next state> <output>
.e
