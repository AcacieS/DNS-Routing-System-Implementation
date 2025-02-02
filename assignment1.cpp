#include "assignment1.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>

using namespace std;

unordered_map<string, string> dnsMap;
int cacheSize = 5;

string get_ip_address_from_file(const string& domain_name) {

    //open the file
    ifstream readfile;
    readfile.open("dns.txt");
    if(readfile.is_open()){
        string line; 
        while(getline(readfile, line)){ //read file line by line
            size_t pos = line.find('='); //split line by the delimiter '='
            //key value pairs
            string file_domain_name = line.substr(0,pos);
            string ip_address = line.substr(pos+1);
            // dnsMap[file_domain_name]=ip_address;
            dnsMap.insert({file_domain_name, ip_address});
            //check if the file domain name is found and if yes return the IP Address
            if(file_domain_name == domain_name){
                readfile.close();
                return ip_address;
            }
        }
    }
    readfile.close();
    return ""; //cannot be opened or not found
}
string get_ip_address(const string& domain_name){
    //if requested domain is present in the cache.
    if(dnsMap.find(domain_name)!=dnsMap.end()){
        return dnsMap[domain_name];
    }
    string ip_address = get_ip_address_from_file(domain_name);
    // if(!ip_address.empty()){ 
    //     dnsMap[domain_name]=ip_address;
    // }
    return ip_address;
}
void print_cache(void) {
    cout << "Cache contents:\n";
    vector<string> keys;

    for (auto i = dnsMap.begin(); i!=dnsMap.end(); ++i) {
        cout<< "cache: " << i->first << " = " << i->second << endl;
    }
    
    cout << endl;
}

void clean_up_cache(string filename) {
    // dnsMap.clear();
    // cout << "Cache cleared" <<endl;
}

void print_dns_file(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "The File can't be open\n";
        return;
    }
    cout << "Here is the DNS file contents:\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void add_update(string filename) {
    
}
