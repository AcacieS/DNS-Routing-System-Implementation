#ifndef ASSIGNMENT1_H
#define ASSIGNMENT1_H

#include <string>
using namespace std;

std::string get_ip_address(const string& domain_name);
void print_cache();
void clean_up_cache(string filename);
void print_dns_file(string filename);
void add_update(string filename);

#endif