#include <iostream>
#include <fstream>
#include "assignment1.h"
int main() { 
// Fill the cache to its maximum capacity 
std::cout << "IP address for www.example.com: " << 
get_ip_address("www.example.com") << std::endl; 
//print_cache(); 
std::cout << "IP address for www.google.com: " << 
get_ip_address("www.google.com") << std::endl; 
//print_cache(); 
std::cout << "IP address for www.github.com: " << 
get_ip_address("www.github.com") << std::endl; 
//print_cache(); 
std::cout << "IP address for www.stackoverflow.com: " << 
get_ip_address("www.stackoverflow.com") << std::endl; 
//print_cache(); 
std::cout << "IP address for www.reddit.com: " << 
get_ip_address("www.reddit.com") << std::endl; 
// Print the cache contents 
cout<< "CACHE WITH example, google, github, stackoverflow, reddit"<< endl;
print_cache(); 
//it should have:
/* example, google, github, stackoverflow, reddit */

    // Access an existing entry to update its position in the LRU list 
    //this work
    std::cout << "UPDATE THIS www.google.com: " << 
    get_ip_address("www.google.com") << std::endl; 
 
    print_cache(); 

    //this work
    // Add a new entry, which should evict the least recently used entry 
    std::cout << "REMOVE LAST USED IP address for www.twitter.com: " << 
    get_ip_address("www.twitter.com") << std::endl; 
    
    // Print the cache contents again to verify the eviction 
    cout<<"previous before change for clean_up"<<endl;
    print_cache(); 
 
    // Modify the DNS file to simulate changes 
    std::ofstream dnsFile("dns.txt", std::ios::trunc); 
    dnsFile << "www.example.com=192.168.1.101" << std::endl; 
    dnsFile << "www.google.com=8.8.8.8" << std::endl; 
    dnsFile << "www.github.com=192.30.255.113" << std::endl; 
    dnsFile << "www.stackoverflow.com=151.101.1.69" << std::endl; 
    dnsFile << "www.reddit.com=151.101.1.70" << std::endl; 
    dnsFile.close(); 
    cout<< "after update"<<endl;
    print_cache();
    cout << "cleaning up cache"<<endl;
    // Clean up the cache 
    clean_up_cache("dns.txt"); 
    cout<<"it should be: google, reddit, stackoverflow, github"<<endl;
    // Print the cache contents again to verify the cleanup 
    print_cache(); 
 
    // Print the contents of the DNS file 
    print_dns_file("dns.txt"); 
 
    // Test the add_update function 
    add_update("dns.txt"); 
    
    cout<<"it should be: google, reddit=1.1.1.1, stackoverflow, github"<<endl;
    // Print the cache and DNS file contents again to verify the changes 
    print_cache(); 
    print_dns_file("dns.txt"); 
    
 
    return 0; 
}