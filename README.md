ARP-Windows-Service
===================

The goal of this project is to create a windows service, which will detect when a phone - with known MAC or IP address - is connected to the local area network, sending the detection result over a serial port to the MSP430 Launchpad. Code for this will be in a separate repository.

###Creating a Windows Service

To investigate the proper form of service creation, the [Windows Service Applications](http://msdn.microsoft.com/en-us/library/y817hyb6(v=vs.110).aspx) is used as a guide.

The Microsoft .NET Framework SDK will be used to create this service package.

###ARP

Ideally, this [linux kernal code](https://www.kernel.org/pub/linux/kernel/people/marcelo/linux-2.4/net/ipv4/arp.c) will be repurposed within the service to enable the detection of the desired network device. 

###Serial COMM

Finally, to communicate with a serial port, the examples given by microsoft on their [serial communications](http://msdn.microsoft.com/en-us/library/ff802693.aspx) page should allow the creation of serial port and the writing of data to that port.

###UPDATES

This page will be updated with links and unpredicted shortcomings as they are encountered.


###Issues in Developement - 8/21/14

This README will serve as a journal of sorts to document my methodology in approaching unknown projects. The extent of my programming experience thus far has been: Windows command prompt based applications in C, basic serial and GUI programming in C++ using Visual Studio, Java programming I and II - basic to semi-advanced ideas in OO programming, basic programming in C for microcontrollers (MSP430 and ATMega644p targets), MIPS using MARS emulation plaform and basic webprogramming (PHP, HTML, CSS, MySQL, JavaScript).

*This being said, a project such as this may be mildly overkill for the end application, but that will be determined along the way.*

###Issues in Developement - 8/22/14

Resolved several issues. 

Instructions for creating a windows service with timed event:

http://blogs.msdn.com/b/bclteam/archive/2005/03/15/396428.aspx

Instructions for compiling C# without using Visual Studio. Poor mans version to develope for .NET - works well!

http://news.kynosarges.org/2013/02/13/programming-net-4-5-without-vs2012/

Currently struggling with the issue of ARP cache not updating after the device is disconnected. The 'arp -a' is easily parsed in C# using a substring compare with the MAC address of choice. Unsure of whether the cached should be deleted everytime I call 'arp' or if a solution using the ping library can be obtained. I do not want to degrade the rest of my networking applications by doing this. After pinging the device, the arp cache is updated, but if I ping every device on my network, the default ping options take very long to complete. Ping class will be investigated further.

As for the ARP code suggested in the original project proposal, .NET SDK does not contain compiler for C, addtionally C# contains all of the libraries neccessary for this project, therefore the original idea of using the C code from the linux kernel will be scrapped.




