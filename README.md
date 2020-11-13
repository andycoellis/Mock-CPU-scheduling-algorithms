## Operating System Assessment 1
### REDACTED University

Name: Andrew Ellis<br>

#### To Run;
>To first run the project use the provided make file. The below section ```MakeFile```
>includes all instructions on how to build project and run each algorithm.

#### Summary
>The project is based on the requirements of REDACTED. Therfore, it has three 
>scheduling algorithms create, First Come First Serve, Shortest Job First and
>Round Robin. These algorithms all implement a queue constructed on the basis
>of a linked list data structure. The program constructed reads in a list of 
>processes identified as \<process id> \<burst amount> \<arrival time>\, the
>program then processes based on selected algorithm and outputs to a csv with
>appended \<waiting time>, \<turnaroundtime>

#### Code Base:
- ```C``` language

#### MakeFile

- ```make``` builds project
- ```make fcfs``` runs FCFS algorithm
- ```make sjf``` runs SJF algorithm
- ```make RR``` runs RR algorithm
- ```make clean``` removes out and ```.o``` files

#### Files *selective*

- ```list```, ```stdnode```, ```queue``` these files are the basis of the limited linked list


#### Project Structure
```bash
├── FCFS.c
├── FCFS.h
├── RR.c
├── RR.h
├── SJF.c
├── SJF.h
│
├── list.h
├── stdnode.h
├── queue.c
├── queue.h
│
├── main.c
│
├── input
│   ├── processes-3.txt
│
├── output
│   ├── data_fcfs.csv   
│   ├── data_sjf.csv  
│   ├── data_rr.csv 
```