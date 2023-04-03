# Big Integer Arithmetic 

## Introduction

This program takes two arguments <infile> <outfile> and does some large number arthmetic
printing the results to a file. To run use ./Arthimetic <infile> <outfile>. The infile
must be correctly formatted. Line 1 should be a number with either a +, -, or neither
at the front. Line 2 must be blank. Line 3 must contain the second number with either
+, -, or neither. Outfile will have the following equations seperated by a newline.
𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴𝐵, 𝐴^2, 𝐵^2, 9𝐴^4 + 16𝐵^5.

## Building

To make the Shuffle.c use the following command.

> `make` or `make Arithmetic`

To make the ListTest Binary use the following command.

> `make ListTest`

To make the BigIntegerTest Binary use the following command.

> `make BigIntegerTest`

## Running

### Arithmetic

To run Arithmetic first make the binary, then run with the following command. Note that <infile> should be correctly formatted.

> `./Arithmetic <infile> <outfile>`

### ListTest

To run ListTest use the following command. The results to the test are comments inside ListTest.c

> `./ListTest`

### BigIntegerTest

To run BigIntegerTest use the following command. The results to the test are comments inside BigIntegerTest.c

> `./BigIntegerTest`

## Contributing

List.h, List.cpp, BigIntegerTest.cpp, ListTest.cpp, Arithmetic.cpp, BigInteger.ccp, BigInteger.h, README, MakeFile - Nicholas Barsi-Rhyne
