#pragma once

/// <summary>
/// Tasks performed by the kernel
///			a. Process scheduling:
///			b. Memory management
///			c. Creation and termination of processes:
///			d. Networking: receives network messages (packets) on behalf of user processes
///			e. Provision of a system call application programming interface (System call)
/// 
/// Kernel mode :  In Kernel mode, the executing code has complete and unrestricted access to the underlying hardware. 
///					It can execute any CPU instruction and reference any memory address. 
///					Kernel mode is generally reserved for the lowest-level, most trusted functions of the operating system. 
///					Crashes in kernel mode are catastrophic; they will halt the entire PC.
/// user mode : executing code has no ability to directly access hardware or reference memory
///				-  Code running in user mode must delegate to system APIs to access hardware or memory.
///				- Due to the protection afforded by this sort of isolation, crashes in user mode are always recoverable.
/// 
/// A system call changes the processor state from user mode to kernel mode, so that the CPU can access protected kernel memory.
///			The calling user function must make all of the system call arguments available to the system call trap handling routine.
///			-- brk(), sbrk() for malloc
///			-- shmat(), shmdt() for shared memory
/// 
/// Process creation and program execution
///				- A process can create a new process using the fork() system call
///				- The kernel creates the child process by making a duplicate of the parent process.
///					The child inherits copies of the parent’s data, stack, and heap segments, 
///					which it may then modify independently of the parent’s copies
///				- Each process has a unique integer process identifier (PID).
/// 
/// IPC
///	signals : which are used to indicate that an event has occurred;
/// pipes	:  FIFOs, which can be used to transfer data between processes,  ps -eaf| grep GCE
///	sockets : which can be used to transfer data from one process to another, either on the same host computer or on different hosts connected by a network;
/// message queues : which are used to exchange messages (packets of data) between processes
/// semaphores : which are used to synchronize the actions of processes
/// shared memory : which allows two or more processes to share a piece of memory
/// 
/// TIme : Real time is measured from some fixed point, typically the start, in the life of a process(elapsed or wall clock 	time).
/// Process time, also called CPU time, is the total amount of CPU time that a process has used since starting.
///			
/// </summary>