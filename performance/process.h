/// <summary>
/// https://www.tenouk.com/ModuleW.html
/// https://manybutfinite.com/post/closures-objects-heap/
/// Process Memory Division Scheme
///  -- the program address resides in the address span between 0 and 2N, N being 32 or 64.
///  -- Linux process virtual memory map 
///		A) The topmost part belonging to the kernel where the process - specific environment variables are stored
///		B) stack : which is used to provide independent space for functions     
///				-- local variables for main
///				-- local variables for other functions.
///		C) Shared Memory : functions from linked dynamic libs
///		D) Heap : on which the dynamic memory allocation is run
///		E) Data sections : carrying the data on which the CPU will operate. separate sections for 
///					 .data section  : initialized global and static variables
///					 .bss section   : uninitialized global and static variables (block started by symbol)
///					 .rdata section : for constant data (read only data)
///										This contains constants and string literals.
/// 		F) .text (Code) section  : This section contains the executable instruction codes 
///								shared among every process running the same binary
///								usually has READ and EXECUTE permissions only. 
///								This section is the one most affected by optimization.
///		
///
/// Normally the C’s program building process involves four stages and utilizes different ‘tools’ such as a preprocessor, compiler, assembler, and linker.
///  1. Preprocessing : first pass of any C compilation. 
///		It processes (hello.i) --> gcc -E hello.c -o hello.i
///			-- include-files
///			-- conditional compilation 
///			-- macros.
///  2. Compilation is the second pass.It takes the output of the preprocessor, and the source code, and generates assembler source code.
///			gcc -S hello.c -o hello.s  (assembly code)
///  3. Assembly is the third stage of compilation.It takes the assembly source code and produces an assembly listing with offsets.The assembler output is stored in an object file.
///			gcc hello.c -o hello.o (object code)
///	 4. Linking is the final stage of compilation.It takes one or more object files or libraries as input and combines them to produce a single(usually executable) file.
///		In doing so, it resolves references to external symbols, assigns final addresses to procedures / functions and variables, and revises code and data to reflect new addresses(a process called relocation).
///	 
///  An object and executable come in several formats 
///		a) Linux   -- ELF (Executable and Linking Format) -- GNU
///		b) Windows -- COFF (Common Object-File Format)
/// 
/// Linkage: 
///  In general, linkage will refer to the visibility of symbols to the linker when processing files. Linkage can be either internal or external.
/// External Linkage : When a symbol (variable or function) is visible to the linker from other files
///			-- extern int x;
///			-- extern void f(const std::string& argument);
///	
/// const global variables have internal linkage by default, 
/// and non-const global variables have external linkage by default. 
/// 
/// 
/// Compiling:
///		a) The input for the compiler is a translation unit. A typical translation unit is a text file containing the source code.
///		b) The output of the compilation is a collection of binary object files, one for each of the input translation units.
///			main.c -> main.o, xyz.c -> xyz.o
///		Stages of compiling
///		 A) Preprocessing
///				-- include/header files into the source files, as specified by the #include keyword.
///				-- Converts the values specified by using #define statements into the constants.
///				-- Converts the macro definitions into code 
///				-- Conditionally includes or excludes certain parts of the code, based on the position of #if, #elif, and #endif directives.
///		only preprocess => 
///					gcc -i main.c -o main.i
///					gcc -E -P -i main.c -o main.i
///		B) Linguistic Analysis :
///				During this stage, source code is lexically analyzed, with the intention of checking whether the program satisfies 
///				the syntax rules of the programming language in which it was written. 
///				If deviations from the syntax rules are detected, errors or warnings are reported. 
///		c) Assembling
///			-- The compiler reaches this stage only after the source code is verified to contain no syntax errors
///			-- the compiler tries to convert the standard language constructs into the constructs specific to the actual CPU instruction set
///			-- Different CPUs feature different functionality treats, and in general different sets of available instructions, registers, interrupts, 
///					which explains the wide variety of compilers for an even wider variety of processors.
///			gcc -S <input file> -o <output assembler file>.s
///		D) Optimization: Once the first assembler version corresponding to the original source code is created, the optimization effort starts, 
///				in which usage of the registers is minimized. Additionally, the analysis may indicate that certain parts of the code do not in fact need to be executed,
///				 and such parts of the code are eliminated.
///		E) Code Emission : Finally, the moment has come to create the compilation output: object files, one for each translation unit.
///			The assembly instructions (written in human-readable ASCII code) are at this stage converted into the binary values of the corresponding machine instructions (opcodes) 
///			and written to the specific locations in the object file(s).
///		 
///		 The gcc compiler may be set to perform the complete compilation (preprocessing and assembling and compiling), a procedure that generates the binary object file (standard extension .o) 
///			whose structure follows the ELF format guidelines.
///		-- In addition to usual overhead (header, tables, etc.), it contains all the pertinent sections (.text, .code, .bss, etc.). 
///			


/// </summary>