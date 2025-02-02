#include <iostream>
#include <fstream>
#include "assignment1.h"
int main() { 
// Fill the cache to its maximum capacity 
std::cout << "IP address for www.example.com: " << 
get_ip_address("www.example.com") << std::endl; 
std::cout << "IP address for www.google.com: " << 
get_ip_address("www.google.com") << std::endl; 
std::cout << "IP address for www.github.com: " << 
get_ip_address("www.github.com") << std::endl; 
std::cout << "IP address for www.stackoverflow.com: " << 
get_ip_address("www.stackoverflow.com") << std::endl; 
std::cout << "IP address for www.reddit.com: " << 
get_ip_address("www.reddit.com") << std::endl; 
// Print the cache contents 
print_cache(); 
 
    // Access an existing entry to update its position in the LRU list 
    std::cout << "IP address for www.google.com: " << 
get_ip_address("www.google.com") << std::endl; 
 
    // Add a new entry, which should evict the least recently used entry 
    std::cout << "IP address for www.twitter.com: " << 
get_ip_address("www.twitter.com") << std::endl; 
 
    // Print the cache contents again to verify the eviction 
    print_cache(); 
 
    // Modify the DNS file to simulate changes 
    std::ofstream dnsFile("dns.txt", std::ios::trunc); 
    dnsFile << "www.example.com=192.168.1.101" << std::endl; 
    dnsFile << "www.google.com=8.8.8.8" << std::endl; 
    dnsFile << "www.github.com=192.30.255.113" << std::endl; 
    dnsFile << "www.stackoverflow.com=151.101.1.69" << std::endl; 
    dnsFile << "www.reddit.com=151.101.1.70" << std::endl; 
    dnsFile.close(); 
 
    // Clean up the cache 
    clean_up_cache("dns.txt"); 
 
    // Print the cache contents again to verify the cleanup 
    print_cache(); 
 
    // Print the contents of the DNS file 
    print_dns_file("dns.txt"); 
 
    // Test the add_update function 
    add_update("dns.txt"); 
 
    // Print the cache and DNS file contents again to verify the changes 
    print_cache(); 
    print_dns_file("dns.txt"); 
 
    return 0; 
}