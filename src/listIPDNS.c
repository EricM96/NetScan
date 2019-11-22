//*****************************************************************************
//
// Eric McCullough
// Computer Networks
// Homework 5
// November 26, 2019
// Instructor: Ajay K. Katangur 
//
//*****************************************************************************
#include "stdio.h"
#include "stdlib.h" 
#include "stdbool.h" 
#include "arpa/inet.h"
#include "sys/types.h" 
#include "netdb.h"

//*****************************************************************************
//
// Handle Error Function
//
// This function handles any errors that may be thrown during the program. It 
// prints an error message to the console and exits the program with an error 
// code.
//
// Return Value
// ------------
// void
//
// Value Parameters 
// ----------------
// error_msg    c string    The error message to display to the console 
//
//*****************************************************************************
void handleError(char *error_msg)
{
    printf("Error: %s\n", error_msg);
    exit(EXIT_FAILURE);
}

//*****************************************************************************
//
// Validate Subnet Mask Function
//
// This function receives a subnet mask and ensures that is valid.
//
// Return Value
// ------------
// bool                    True/False if the subnet mask is valid
//
// Value Parameters
// ----------------
// subnet_mask  unsigned 32 bit number      the subnet mask to validate 
// 
//*****************************************************************************
bool validateSubnetMask(uint32_t subnet_mask)
{
    subnet_mask = ntohl(subnet_mask); 
    if (subnet_mask == 0)
    {
        return false; 
    }
    else if (subnet_mask & (~subnet_mask >> 1))
    {
        return false; 
    }
    else
    {
        return true; 
    }  
}

//*****************************************************************************
//
// Main Function
//
// Main execution loop for the program. Receives a subnet mask and ip address
// as command line arguments and ip addresses and hostnames for all hosts on
// the network 
//
// Return Value
// ------------
// int                  0 if success other if not
// 
// Command Line Arugments 
// ----------------------
// string               subnet mask in dotted decimal notation 
// string               ip address in dotted decimal notation 
// 
// Local Variables
// ---------------
// subnet_mask_long     uint32_t        subnet mask in 32 bit int form
// ipaddr_long          uint32_t        ip address in 32 bit int form
// net_addr             uint32_t        network address in 32 bit int form
// net_range            uint32_t        number of devices the network can have
// 
//*****************************************************************************
int main(int argc, char **argv)
{ 
    if (argc != 3)
    {
        handleError("Incorrect usage: listIPDNS <subnet mask> <ip address>");
    }

    uint32_t subnet_mask_long, ipaddr_long, net_addr, net_range;
    char* addr_ptr; 
    struct hostent *hostPtr; 
    struct in_addr *inAddrPointer;

    subnet_mask_long = inet_addr(argv[1]); 
    ipaddr_long = inet_addr(argv[2]);

    if (!validateSubnetMask(subnet_mask_long))
    {
        handleError("Invalid subnet mask");
    }

    net_range = ~subnet_mask_long; 
    net_range = ntohl(net_range);
    net_addr = subnet_mask_long & ipaddr_long;
    for (int i=0; i < net_range; ++i)
    {
        ipaddr_long = ntohl(net_addr) + i; 
        ipaddr_long = htonl(ipaddr_long);  
        addr_ptr = (char*)&ipaddr_long;
        inAddrPointer = (struct in_addr*)&ipaddr_long; 
        hostPtr = gethostbyaddr(addr_ptr, 4, AF_INET); 
        if (hostPtr != NULL)
        {
            printf("IP Address: %s\tHost name: %s\n",
                   inet_ntoa(*inAddrPointer), hostPtr->h_name);
        } 
    }

    return 0; 
}