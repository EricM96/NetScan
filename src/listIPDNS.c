#include "stdio.h"
#include "stdlib.h" 
#include "stdbool.h" 
#include "arpa/inet.h"
#include "sys/types.h" 
#include "netdb.h"

void handleError(char *error_msg)
{
    printf("Error: %s\n", error_msg);
    exit(-1);
}

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

int main(int argc, char **argv)
{ 
    if (argc != 3)
    {
        handleError("Incorrect usage: listIPDNS <subnet mask> <ip address>");
        exit(EXIT_FAILURE); 
    }

    uint32_t subnet_mask_long, ipaddr_long, net_addr;
    char* addr_ptr; 
    struct hostent *hostPtr; 

    subnet_mask_long = inet_addr(argv[1]); 
    ipaddr_long = inet_addr(argv[2]);

    if (!validateSubnetMask(subnet_mask_long))
    {
        handleError("Invalid subnet mask");
        exit(EXIT_FAILURE);
    }

    net_addr = subnet_mask_long & ipaddr_long;

    for (int i=1; i < 255; ++i)
    {
        ipaddr_long = net_addr + i; 
        addr_ptr = (char*)&ipaddr_long;
        hostPtr = gethostbyaddr(addr_ptr, 4, AF_INET); 
        if (hostPtr != NULL)
        {
            printf("Host name: %s\n", hostPtr->h_name);
        } 
    }

    return 0; 
}