# NetScan
Subnet scanner written in C. Given a subnet mask and an 
example of an IP address that could be on the network, 
it will display the IP address and hostname of all hosts
on the network. 

## Usage
The scanner runs on unix sockets and therefore will only
run on Linux and MacOS systems.

1. Run `make` in the project root directory
2. Run `./server/listIPDNS.app` in the project root directory 