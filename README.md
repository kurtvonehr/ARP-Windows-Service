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


