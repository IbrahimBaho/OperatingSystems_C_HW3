- Multithreaded sorting program, we split the array into two sections, each thread will sort a section, a third thread will merg and sort both sections.
- to run the program from the commandline: 
	1) type 'make' to compile, that will generate an ocject file called cthread 
	2) use this objet file followed by a integer to execute, check the following examples:

fox05:~/courses/Grad_OS/HW3> cthread 5
Original array:
A[0] = 84       A[1] = 40       A[2] = 78       A[3] = 80       A[4] = 91

first half:
A1[0] = 84      A1[1] = 40

second half:
A2[0] = 78      A2[1] = 80      A2[2] = 91

Sorted Array:
A[0] = 40       A[1] = 78       A[2] = 80       A[3] = 84       A[4] = 91

fox05:~/courses/Grad_OS/HW3> cthread 7
Original array:
A[0] = 84       A[1] = 40       A[2] = 78       A[3] = 80       A[4] = 91       A[5] = 20       A[6] = 34

first half:
A1[0] = 84      A1[1] = 40      A1[2] = 78

second half:
A2[0] = 80      A2[1] = 91      A2[2] = 20      A2[3] = 34

Sorted Array:
A[0] = 20       A[1] = 34       A[2] = 40       A[3] = 78       A[4] = 80       A[5] = 84       A[6] = 91

