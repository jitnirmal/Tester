#pragma once

/// <summary>
/// https://www.solarflare.com/Media/Default/PDFs/SF-117079-AN-LATEST_Solarflare_TCPDirect_White_Paper.pdf
/// - TCPDirect is a new user-space, kernel bypass application library implementing TCP and UDP over IP
/// - TCPDirect is focused on minimizing network stack overhead and hence offering applications requiring it
///			the absolutely lowest possible latency between the application and the network
///  - TCP/IP protocol going via the kernel imposes
///			a) system calls
///			b) context switches 
///			c) interrupts which have a negative impact on latency
///  With Solarflare’s kernel bypass architecture TCP / IP stack resides in the address space of the user mode application
///	TCPDirect provides
///		a) optimized zero-copy proprietary API ( need to copy packet payloads as part of sending or receiving)
///	
/// Latency comparison		
///			1/ Kernel 1500 ns 
///			2/ Onload 300 ns
///			3/ TCPDirect 20 ns
/// 
/// 
/// OpenOnload(R) is a high performance user-level network stack, which delivers absolutely the best performance 
///		to applications using the BSD sockets API.
/// 
/// </summary>


/// <summary>
///		L1     5 ns
///		L2    7 ns
///		Main mem 100 ns

/// 		1) NEVER configure 1 NIC for both market data and order flow.
///			-- A spike in 1 may significantly impact latencies in the other
///			2) Use NICs with built in Kernel Bypass  (SolarFlare & Mellanox, exablaze)
///				A) Ether Fabric Virtual Interface ef_vi is an API that gives applications access to the network adapter's datapath
///			3) Set up accurate time stamps – PTP or NTP
///				--NTP – sync software is inferior to PTP\
///			4) Lscpu – cpu arch info from sysfs & /proc/cpuinfo
/// Isolcpus
/// Tuna – control processor and scheduler affinity 
///		Options: Isolate sockets from user space, push to socket 0
/// </summary>
