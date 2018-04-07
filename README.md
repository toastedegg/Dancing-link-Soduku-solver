# Dancing-link-Soduku-solver
TEAM MEMBERS:

Tianze shou   52801260             
Yumeng zhang  71169660
Haozhe jiang  68249954               
Jinsheng Zhu  33882845










DLX algorithm based solver:
Extract the files in the tar under the same directory, run:

$ make  

under the directory to generate the executable file solver in the current directory.

To solve a puzzle written in a txt file. run:

$ ./solver filename.txt

There is no input validation so input must be correct. Make sure the txt file is under the same directory as the executable. The terminate will print out the solved puzzle and cpu time spent on the search algorithm and the search states.



CPS algorithm based solver:

We didnt write a makefile for the CSP algorithm, the CSP source code in under the directory /CSP. To compile, run:

g++ -std=c++11 -o ./solver SolveSudoku.cpp Sodoku.cpp

To solve a puzzle written in a txt file. run:

$ ./solver filename.txt


The CSP version will not print out the running time and node explored.
