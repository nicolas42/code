8 bit Arithmetic and Logic Unit (ALU)
------------------------------------------

Open the .circ file in logisim to use http://www.cburch.com/logisim/

8 bit ALU implements addition, subtraction, bitwise and, bitwise or, or inverting of one input.

There two 8-bit input registers A and B
and one 8-bit output register Sout

There's also an input carry bit and an output carry bit.  

Instruction Set

So, the full instructions are actually like this

00110 and
01110 or
10110 not B
11110 add
11011 subtract

Explanation

There are two function bits, an enable bit for A and an enable bit for B and an invert A bit.  
F0 F1 enA enB invA

F0 F1 = 00 for and
F0 F1 = 01 for or
F0 F1 = 10 for not B
F0 F1 = 11 full adder

To use these functions, make sure to enable A and B by switching on those bits.
For not B it doesn't matter.
For subtraction, switch enable A to invert A (enA=0, invA=1)


Bug
---------------
There seems to be a bug whereby subtracting one number from another gives the wrong Cout value.  
