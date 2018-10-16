#pragma once
/*
TCP Echo server example in winsock
Live Server on port 8888
*/
#pragma warning(disable:4996) 
#include<stdio.h>
#include<winsock2.h>
//https://jvns.ca/blog/2017/06/03/async-io-on-linux--select--poll--and-epoll/
/// <summary>
/// select, poll and epoll  alternative for handling multiple concurrent sockets 
/// epoll and poll are better than select because program does not have to inspect each socket for events of interest. 
/// program performs an action on an asynchronous socket and is immediately notified as to whether that action succeeded or failed. 
/// Since asynchronous sockets are non-blocking, there is no need for multiple threads of execution. 
/// This single-threaded approach comes with its own challenges, but can be a good choice for many programs. 
/// It can also be combined with the multi-threaded approach: asynchronous sockets using a single thread can be used for the networking component of a server, and threads can be used to access other blocking resources, e.g. databases.
/// 
/// </summary>


/// <summary>
/// Programs using epoll often perform actions in this sequence:
///		1. Create an epoll object
///		2. Tell the epoll object to monitor specific events on specific sockets
///		3. Ask the epoll object which sockets may have had the specified event since the last query
///		4. Perform some action on those sockets
///		5. Tell the epoll object to modify the list of sockets and/or events to monitor
///		6. Repeat steps 3 through 5 until finished
///		7. Destroy the epoll object
/// 
///	epoll has two modes of operation
///		a. edge-triggered - call to epoll will return an event on a socket only once after the read or write event
///						 occurred on that socket. The calling program must process all of the data associated with that
///						 event without further notifications on subsequent calls to epoll.poll().
///		b. level-triggered -repeated calls to epoll will result in repeated notifications of the event of interest, 
///						until all data associated with that event has been processed.
/// </summary>

/// <summary>
///  We can use select() and poll() to monitor file descriptors for regular files, terminals, pseudoterminals, pipes, FIFOs, sockets
/// 
/// SELECT
///		The select() system call blocks until one or more of a set of file descriptors becomes ready
///			-- int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
///			-- Returns number of ready file descriptors, 0 on timeout, or –1 on error
///			-- fd_set data type is implemented as a bit mask
///			-- all manipulation of file descriptor sets is done via four macros : FD_ZERO(), FD_SET(), FD_CLR(), and FD_ISSET()
///			-- A file descriptor set has a maximum size FD_SETSIZE = 1024
///			-- Since these structures are modified by the call, we must ensure that we reinitialize them if we are repeatedly 
///				calling select() from within a loop.
/// 
/// 
/// POLL
///			-- The poll() system call performs a similar task to select(). The major difference between the two system calls lies 
///				in how we specify the file descriptors to be monitored.
///			-- int poll(struct pollfd fds[], nfds_t nfds, int timeout);
///			-- The implementation of the poll() system call involves calling the kernel poll routine for each file descriptor 
///					and placing the resulting information in the corresponding revents field.
///			-- To implement select(), a set of macros is used to convert the information returned by the kernel poll routines
///				 into the corresponding event types returned by select() :
///			-- poll() places no intrinsic limit on the range of file descriptors that can be monitored. (select - 1024)
///			-- Because the fd_set arguments of select() are value-result, we must reinitialize them if making repeated select() 
///				calls from within a loop.By using separate events(input) and revents(output) fields, poll() avoids this requirement.
///		
/// Performance
///			-- The performance of poll() and select() is similar when
///					--The range of file descriptors to be monitored is small 
///					--A large number of file descriptors are being monitored, but they are densely packed
///			-- the performance of poll() is better than select when set of file descriptors to be monitored is sparse; 
///				  only one or a few descriptors in the range 0 to N are being monitored.
/// 
/// Problems with select() and poll()
///			-- On each call to select() or poll(), the kernel must check all of the specified file descriptors to see if they are ready.
///			-- In each call to select() or poll(), the program must pass a data structure to the kernel describing all of the file descriptors 
///				to be monitored, and, after checking the descriptors, the kernel returns a modified version of this data structure to the program. 
///				the task of copying it from user to kernel space and back again consumes a noticeable amount of CPU time 
///			--  After the call to select() or poll(), the program must inspect every element of the 	returned data structure to see which file descriptors are ready.
///	-- This creates problems for programs that monitor large numbers of file descriptors. (poor scalability)
/// 
/// EPOLL (Linux only) : The performance of epoll scales much better than select() and poll() when monitoring large numbers of file descriptors
///		The epoll API permits either level-triggered or edge-triggered notification. By contrast, select() and poll() provide only level - triggered notification
/// 
/// The epoll API consists of three system calls:
///		 -- int epoll_create(int size); 	The size argument specifies number of file descriptors that we expect to monitor via the epoll instance
///		 -- int epoll_ctl(int epfd, int op, int fd, struct epoll_event *ev);
///					-- The fd argument identifies which of the file descriptors in the interest list is to have its settings modified
///					-- The epoll_wait() system call returns  information about ready file descriptors from the epoll instance referred to by the file descriptor epfd.
/// 
/// Performance : number of file descriptors
/// For the purposes of this test, FD_SETSIZE was changed to 16,384 in the glibc header files
///		-- By contrast,the performance of epoll hardly declines as N grows large. (time in seconds)
/// -------------------------------------------------------------------------------------------
/// Number of descriptors monitored(N)			poll()			select()		epoll()
/// -------------------------------------------------------------------------------------------
/// 10												0.61			0.73			0.41
/// 100												2.9				3.0				0.42
///	1000											35				35				0.53
/// 10000											990				930				0.66
/// 
/// 
/// 1. Each time we call select() or poll(), we pass a data structure to the kernel that identifies all of the file descriptors that are to be monitored,
///  and, on return, the kernel passes back a data structure describing the readiness of all of these descriptors.
/// 2. epoll, we use epoll_ctl() to build up a data structure in kernel space that lists the set of file descriptors to be monitored. Once this data 
///		structure has been built, each later call to epoll_wait() doesn’t need to pass any information about file descriptors to the kernel, and the call 
///		returns information about only those descriptors that are ready.
/// 3. select/poll perform poorly when N is greater than 100..
/// </summary>

#pragma comment(lib, "ws2_32.lib") //Winsock Library

int testSelect(int argc, char *argv[])
{
	WSADATA wsa;
	SOCKET master, new_socket, client_socket[30], s;
	struct sockaddr_in server, address;
	int max_clients = 30, activity, addrlen, i, valread;
	char message[] = "ECHO Daemon v1.0 \r\n";

	//size of our receive buffer, this is string length.
	int MAXRECV = 1024;
	//set of socket descriptors
	fd_set readfds;
	//1 extra for null character, string termination
	char *buffer;
	buffer = (char*)malloc((MAXRECV + 1) * sizeof(char));

	for (i = 0; i < 30; i++)
	{
		client_socket[i] = 0;
	}

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	printf("Initialised.\n");

	//Create a socket
	if ((master = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if (bind(master, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	puts("Bind done");

	//Listen to incoming connections
	listen(master, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");

	addrlen = sizeof(struct sockaddr_in);

	while (TRUE)
	{
		//clear the socket fd set
		FD_ZERO(&readfds);

		//add master socket to fd set
		FD_SET(master, &readfds);

		//add child sockets to fd set
		for (i = 0; i < max_clients; i++)
		{
			s = client_socket[i];
			if (s > 0)
			{
				FD_SET(s, &readfds);
			}
		}

		//wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
		activity = select(0, &readfds, NULL, NULL, NULL);

		if (activity == SOCKET_ERROR)
		{
			printf("select call failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(master, &readfds))
		{
			if ((new_socket = accept(master, (struct sockaddr *)&address, (int *)&addrlen))<0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}

			//inform user of socket number - used in send and receive commands
			printf("New connection , socket fd is %d , ip is : %s , port : %d \n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

			//send new connection greeting message
			if (send(new_socket, message, strlen(message), 0) != strlen(message))
			{
				perror("send failed");
			}

			puts("Welcome message sent successfully");

			//add new socket to array of sockets
			for (i = 0; i < max_clients; i++)
			{
				if (client_socket[i] == 0)
				{
					client_socket[i] = new_socket;
					printf("Adding to list of sockets at index %d \n", i);
					break;
				}
			}
		}

		//else its some IO operation on some other socket :)
		for (i = 0; i < max_clients; i++)
		{
			s = client_socket[i];
			//if client presend in read sockets             
			if (FD_ISSET(s, &readfds))
			{
				//get details of the client
				getpeername(s, (struct sockaddr*)&address, (int*)&addrlen);

				//Check if it was for closing , and also read the incoming message
				//recv does not place a null terminator at the end of the string (whilst printf %s assumes there is one).
				valread = recv(s, buffer, MAXRECV, 0);

				if (valread == SOCKET_ERROR)
				{
					int error_code = WSAGetLastError();
					if (error_code == WSAECONNRESET)
					{
						//Somebody disconnected , get his details and print
						printf("Host disconnected unexpectedly , ip %s , port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

						//Close the socket and mark as 0 in list for reuse
						closesocket(s);
						client_socket[i] = 0;
					}
					else
					{
						printf("recv failed with error code : %d", error_code);
					}
				}
				if (valread == 0)
				{
					//Somebody disconnected , get his details and print
					printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

					//Close the socket and mark as 0 in list for reuse
					closesocket(s);
					client_socket[i] = 0;
				}

				//Echo back the message that came in
				else
				{
					//add null character, if you want to use with printf/puts or other string handling functions
					buffer[valread] = '\0';
					printf("%s:%d - %s \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port), buffer);
					send(s, buffer, valread, 0);
				}
			}
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}