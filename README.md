# State reduction
State reduction is a technique to reduce the state count in a state diagram

# Problem statement
Develop a state reduction approach to optimize a state diagram/sequential circuit

# Input file/format 
A state diagram S in the KISS format

# KISS format
.i < num-inputs >  
.o < num-outputs >  
.s < num-states >  
.p < num-terms >  
.r < reset-state >  
< input > < current-state > < next-state > < output >    
...  
< input > < current-state > < next-state > < output >  
.e

e.g.  
.i 2  
.o 1  
.s 6  
.p 11  
.r s0  
00 s0 s1 0  
01 s0 s2 1  
10 s0 s3 1  
11 s1 s2 0  
01 s1 s5 0  
10 s2 s4 0  
00 s2 s3 0  
01 s3 s4 1  
11 s3 s5 1  
01 s4 s5 0  
11 s5 s0 0  
.e  

# Output format
An optimized state diagram S’ in the KISS format

# Comments
* In the beginning of the file, a “ “#” begins a comment that extends to the end of the current line 
* Comments give a brief description of the circuit  

# Example
#This is a comment  
.i 2  
.o 1  
.s 6  
.p 11  
.r s0  
00 s0 s1 0  
01 s0 s2 1  
10 s0 s3 1  
11 s1 s2 0  
01 s1 s5 0  
10 s2 s4 0  
00 s2 s3 0  
01 s3 s4 1  
11 s3 s5 1  
01 s4 s5 0  
11 s5 s0 0  
.e  
![image](https://github.com/eric900324/State-Reduction-for-Sequential-Circuits/blob/main/1663595258028.jpg)

