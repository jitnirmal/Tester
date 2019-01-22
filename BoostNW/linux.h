#pragma once
//https://tampub.uta.fi/bitstream/handle/10024/96864/GRADU-1428493916.pdf
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
/// Process vs Threads
///  -- A process is a running program, which consists of an executable object code
///	 -- threads, is light - weight processes
///  -- every process consists of at least one thread
///  -- Each thread has its own id (thread id or TID), program counter, process stack and a set of registers
///	 -- Thread share an address space between each other, avoiding any kind of IPC(Inter Process Communication) channel(pipes, sockets, etc.) to communicate
///	 -- Execution flows can share information by using, say, global variables or data structures, declared in the same.text segment.
///  -- As threads are in the same address space, a thread context switch is inexpensive and fast.
///  -- . In fact, creation of a thread uses the same system call as fork() does, only with different flags :
///  
/// Thread advantage over process
/// -- They only need a stack and storage for registers therefore, threads are cheap to create. (VM, FS, FILES, SIGHAND)
/// -- Context switching are fast when working with threads. The reason is that we only have to save and/or restore PC, SP and registers.
/// -- Because threads can share common data, they do not need to use interprocess communication.
/// 
///  Thread creation system call -
///		clone(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, 0); 
///     the address space (VM), file system information (FS), open files (FILES) and signal handlers along with blocked signals(SIGHAND) will be shared.
///  
///  Process fork goes like this:
///		clone(SIGCHLD, 0);
/// 
///  Kernel vs User threads
///		Kernel -All thread operations are implemented in the kernel and the OS schedules all threads in the system.
///			Solaris: Lightweight processes(LWP).
///		-- Instead of thread table in each process, the kernel has a thread table that keeps track of all threads in the system.
///		-- In addition, the kernel also maintains the traditional process table to keep track of processes.
///		-- Operating Systems kernel provides system call to create and manage threads.
///		Advantage
///			--  Because kernel has full knowledge of all threads, Scheduler may decide to give more time to a process having large number of threads than process having small number of threads.
///		disadvantage
///			-- The kernel-level threads are slow and inefficient. For instance, threads operations are hundreds of times slower than that of user-level threads.
///				Thread operations still require system calls. 
///	 User level thread
///		User-Level threads are managed entirely by the run-time system (user-level library)
///		The kernel knows nothing about user-level threads and manages them as if they were single-threaded processes.
///		User-Level threads are small and fast, each thread is represented by a PC,register,stack, and small thread control block. 
///		Creating a new thread, switiching between threads, and synchronizing threads are done via procedure call. i.e no kernel involvement.
///		User-Level threads are hundred times faster than Kernel-Level threads.
/// 
///  OS can make poor decisions like scheduling a process with idle threads, blocking a process whose thread initiated an I/O 
///		even though the process has other threads that can run and unscheduling a process with a thread holding a lock. 
///		-- There is a lack of coordination between threads and operating system kernel. Therefore, process as whole gets
///		 one time slice irrespect of whether process has one thread or 1000 threads within. It is up to each thread to relinquish control to other threads
/// 
/// 
/// , Linux schedules threads, not processes, So, a thread is the smallest schedulable entity in the kernel
///		Inside the Linux kernel, each process is represented as structure - task_struct (also called process descriptor)
///     -- the process’s priority, whether it is running on a CPU or blocked on an event, what address space has been assigned to it, which files it is allowed to address, and so on.
///		-- contains all the information for process 
///				- process id, state, parent process, children, siblings, processor registers, opened files, address space, etc
///				- The system uses a circular doubly linked list to store all the process descriptors.
/// 
/// Schedular
///		A scheduler chooses the next task to be run, and maintains the order, which all the processes on the system should be run in, as well
///		Linux implements preemptive multitasking. Preemptions are caused by timer interrupts, the clock ticks 1000 times a second
///		Linux tends to provide CPU bound processes with longer “uninterrupted” slices in a row	
///			-- cpus_allowed is a type-struct, containing bit field, which indicates a task’s affinity —binding to a particular set of CPU core(s)
///			 -- Can be set from user - space by using the sched_setaffinity system call.
///		Policies
///		 - SCHED_NORMAL: the scheduling policy that is used for regular tasks;
///		 - SCHED_BATCH : does not preempt nearly to make better use of caches - CPU bound jobs
///		 - SCHED_IDLE : this is even weaker than nice 19 
///		 - SCHED_FIFO and SCHED_RR are for soft real - time processes.Handled by real - time scheduler in <kernel / sched / rt.c> 
/// 
/// Process priority
///		Each task is assigned a nice value, which is an integer from -20 to 19 with default being 0
///			- -20 is highest, 19 is lowest
///		The higher niceness, the lower the priority of a task — it is “nice” to others 
///			$ ps -Al (s all processes with nice (NI column) values.)
///			nice -n increment prog -- change prioity before start
///			renice -n priority -p PID
/// 
/// Process State
///		TASK_RUNNING (0): The task is either executing or contending for CPU in the scheduler run-queue.
///		TASK_INTERRUPTIBLE (1): The task is in an interruptible wait state; it remains in wait until an awaited condition becomes true, 
///				such as the availability of mutual exclusion locks, device ready for I/O.While in this wait state, any signals generated
///				 for the process are delivered, causing it to wake up before the wait condition is met.
///		TASK_ STOPPED (4): The task has received a STOP signal. It will be back to running on receiving the continue signal (SIGCONT).
///		EXIT_ZOMBIE (32): The process is terminated, but its resources are not yet reclaimed.
/// 
/// ----------------------------------------------------------------------------------
///					process descriptor fields
/// ---------------------------------------------------------------------------------
///		PID - the default maximum number PIDs is 32,768
///		tgid -  thread group id
///			when a new process is created, its PID and TGID are the same, as the process happens to be the only thread
///			When the process spawns a new thread, the new child gets a unique PID but inherits the TGID from the parent
///		thread info - This field holds processor-specific state information
///		exit_code and exit_signal - 
///			These fields contain the exit value of the task and details of the signal that caused the termination.
///			These fields are to be accessed by the parent process through wait() on termination of the child.
///		ptrace - his field is enabled and set when the process is put into trace mode using the ptrace() system call.
///		prio - this field holds static priority of the process within the range 1 to 99
///			-For normal processes, this field holds a dynamic priority derived from the nice value.
///		cpus_allowed - on which CPU(s) the process is eligible to be scheduled 
///		policy - information about the scheduling policy of the process - helps to determine prioirty
///		Process limits- to ensure fair allocation of system resources among contending processes
///			#define RLIMIT_CPU        0       /* CPU time in sec */
///			#define RLIMIT_FSIZE      1       /* Maximum filesize */
///			#define RLIMIT_DATA       2       /* max data size */
///			#define RLIMIT_STACK      3       /* max stack size */
///			#define RLIMIT_CORE       4       /* max core file size */
///		File descriptor table 
///			files - file descriptor table contains pointers to all the files that a process opens
///		Signal descriptor 
///			For processes to handle signals, the task structure has various elements that determine how the signals must be handled.
///			struct sighand_struct, which contains all signal handlers associated with the process.
///			sigset_t blocked - blocked signals
/// 
/// 
/// 
/// ----------------------------------------------------------------------------------
///					Process creation
/// ---------------------------------------------------------------------------------
/// -- During kernel boot, a kernel thread called init is spawned,
/// -- The init (pid 1) process then carry out various initialization operations specified through configuration files, creating multiple processes.
/// -- The shell, which is one such process, becomes the interface for users to create user processes, when programs are called for execution
/// -- Fork, vfork, exec, clone, wait and exit are the core kernel interfaces for the creation and control of new process. 
///			These operations are invoked through corresponding user-mode APIs.
///		Fork - When fork() succeeds, the new process is created (referred to as child) by duplicating the caller's address space and task structure.
///				--- both caller (parent) and new process (child) resume executing instructions from the same code segment which was duplicated under copy-on-write	
///				--- Most resource entries of the parent's task structure such as memory descriptor, file descriptor table, signal descriptors, and scheduling attributes are inherited by the child
///				--- few attributes such as memory locks, pending signals, active timers, and file record locks not inherited
///				---  A child process is assigned a unique pid and will refer to its parent's pid through the ppid field of its task structure
///		exec - exec replaces the existing program in a process with a new executable binary:
///			--- Command-line user-interface programs such as shell use the exec interface to launch user-requested program binaries.
///			--- The execve is the system call that executes the program binary file, passed as the first argument to it. 
///				The second and third arguments are null-terminated arrays of arguments and environment strings, to be passed to a new program as command-line arguments.
///		vfork() - creates a child process and blocks the parent, the parent process is temporarily suspended until the child exits or call exec().
///		clone() - clone() is a Linux-specific system call to create a new process; it is considered a generic version of the fork() system call, offering finer controls to customize its functionality through the flags argument:
///		wait() - For processes and threads created by a parent, it might be functionally useful for the parent to know the execution status of the child process/thread
///		exit() -Process termination is done either by the process calling exit() or when the main function returns.

/// 
///  ----------------------------------------------------------------------------------
///					Control groups (cgroups)
/// ---------------------------------------------------------------------------------
/// Cgroups are kernel mechanisms to restrict and measure resource allocations to each process group. Using cgroups,
///		 you can allocate resources such as CPU time, network, and memory.
/// Applying cgroups on namespaces results in isolation of processes into containers within a system, where resources are managed distinctly.
///  Each container is a lightweight virtual machine, all of which run as individual entities and are oblivious of other entities within the same system.
/// 
/// Signals
///		Signals are short messages delivered to a process or a process group. 
///		The kernel uses signals to notify processes about the occurrence of a system event; signals are also used for communication between processes. 
///		-- Upon generation of a signal, the kernel delivers the signal event to the destination process, 
///			which in turn can respond to the signal as per the configured action
/// 
/// Kernel handler: The kernel implements a default handler for each signal. 
///			These handlers are available to a process through the signal handler table of its task structure. 
///			Upon reception of a signal, a process can request execution of the appropriate signal handler. 
/// 
/// Process defined handler: A process is allowed to implement its own signal handlers, and set them up to be executed in response to a signal event. 
///		This is made possible through the appropriate system call interface, which allows the process to bind its handler routine with a signal. 
///		On occurrence of a signal, the process handler would be invoked asynchronously.
/// 
/// Ignore: A process is also allowed to ignore the occurrence of a signal, 
///		but it needs to announce its intent to ignore by invoking the appropriate system call.
/// 
/// Kernel-defined default handler routines can execute any of the following actions:
///  - Ignore: Nothing happens.
///  - Terminate: Kill the process
///  - Coredump: Write a core dump file describing all threads
///  - Stop: Stop all the threads in the group
/// 
/// 
/// 
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
/// 
/// The program execution under the user’s control typically happens through a shell ( sh, bash, and tcsh.)
/// shell tries to locate the executable in each of the folders specified by the PATH environment variable.
///  -- first action of the shell is to create a clone of itself by forking the identical child process
///  -- this way the shell effectively passes all of its environment variables to the new process
/// Kernel Role
///	 -- the kernel reacts by invoking a function from the exec family of functions
///  -- to identify the executable format / ELF  (Executable and Linkable Format)
///  -- ELF is common format for  executable files, object code, shared libraries, and core dumps
///	 -- After the executable format is identified, it completely wipe off most of the memory map
///	 -- Immediately after, it will delegate to the loader the process of populating the wiped off memory map
///		 with the data read from the new program’s binary executable
/// 
/// ///  ----------------------------------------------------------------------------------
///					Program Loader 
/// ---------------------------------------------------------------------------------
/// The Loader Finds the Entry Point
/// The role of the _start function is to prepare the input arguments for the __libc_start_main function that will be called next.
/// __libc_start_main( ) Function
///		-- key player in the process of preparing the environment for the program to run
///		-- Starts up the program’s threading.
///		-- Calls the _init() function, which performs initializations required to be completed before the main() function starts
///		-- Registers the _fini() and _rtld_fini() functions to be called to cleanup after the program terminates. 
///		-- Finally, after all the prerequisite actions have been completed, the __libc_start_main() calls the main() function, thus making your program run.