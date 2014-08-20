ARP-Windows-Service
===================

The goal of this project is to create a windows service, which will detect when a phone - with known MAC or IP address - is connected to the local area network, sending the result over serial every 5 seconds.

##Creating a Windows Service

To investigate the proper form of service creation, the [Windows Service Applications](http://msdn.microsoft.com/en-us/library/y817hyb6(v=vs.110).aspx) is used as a guide.

The Microsoft .NET Framework SDK will be used to create this service package.

##ARP

Ideally, this [linux kernal code](https://www.kernel.org/pub/linux/kernel/people/marcelo/linux-2.4/net/ipv4/arp.c) will be repurposed within the service to enable the detection of the desired network device. 

##Serial COMM

Finally, to communicate with a serial port, the examples given by microsoft on their [serial communications](http://msdn.microsoft.com/en-us/library/ff802693.aspx) page should allow the creation of serial port and the writing of data to that port.

##UPDATES

This page will be updated with links and unpredicted shortcomings as they are encountered.
