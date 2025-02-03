#include "assignment1.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>

using namespace std;

//unordered_map<string, string> dnsMap;
unordered_map<string, pair<string, list<string>::iterator>> dnsMap;
list<string> cacheOrder;
int cacheSize = 5;
int currentCacheSize = 0;

void move_to_front(string domain_name){ 
    cacheOrder.erase(dnsMap[domain_name].second);
    cacheOrder.push_front(domain_name);
    dnsMap[domain_name].second = cacheOrder.begin();
}
void insertDomain(string domain_name, string ip_address){
    if(dnsMap.find(domain_name)!=dnsMap.end()){
        //if exists, you move to front;
        dnsMap[domain_name].first = ip_address;
        move_to_front(domain_name);
        cout<<"you remove something existant "<<domain_name<<endl;
    }else{
        if(dnsMap.size()>=cacheSize){
            //remove LRU element 
            string lru_domain = cacheOrder.back();

            dnsMap.erase(lru_domain);
            cacheOrder.pop_back();
            cout<<"you remove something LRU "<<lru_domain<<endl;
        }
        //insert new entry at the front
        cacheOrder.push_front(domain_name);
        dnsMap[domain_name] = {ip_address, cacheOrder.begin()};
    }
    
}
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
            insertDomain(file_domain_name, ip_address);
            
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
        cout<<"heyyyyyyyyyyyyyyyyyyyy"<<endl;
        move_to_front(domain_name);
        return dnsMap[domain_name].first;
    }
    string ip_address = get_ip_address_from_file(domain_name);
    return ip_address;
}
void print_cache(void) {
    cout << "Cache contents:\n";
    vector<string> keys;

    for (const auto &domain: cacheOrder) {
        cout<< "cache: " << domain << " = " << dnsMap[domain].first << endl;
    }
    
    cout << endl;
}

void clean_up_cache(string filename) { 
    //? filename
    vector<string> to_remove;
    for(auto i = cacheOrder.begin(); i!=cacheOrder.end(); ++i){
        string cache_domain = *i; //value stored at the iterator pos
        string correct_ip = get_ip_address(cache_domain);
        if(correct_ip.empty()){ //means not found in the file
            to_remove.push_back(cache_domain);
        }else if(dnsMap[cache_domain].first != correct_ip){
            cout << "We updated the cache entry"<<cache_domain << " to " << correct_ip<<endl;
            dnsMap[cache_domain].first = correct_ip;
            move_to_front(cache_domain);
        }

    }
    for(const string &domain: to_remove){
        cout << "remove bad cache entry:" << domain << endl;
        cacheOrder.remove(domain);
        dnsMap.erase(domain);
    }
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
    string domain_name, ip_address;
    cout << "Enter domain name: ";
    cin >> domain_name; //get user response domain_name
    cout << "Enter IP address: ";
    cin>> ip_address;

    ifstream file_read(filename);
    if(!file_read.is_open()){
        //if not open
        return;
    }
    vector<string> lines;
    vector<string> newlines;
    bool found = false;
    string line;
    while(getline(file_read, line)){
        size_t pos = line.find('=');
        string file_domain_name = line.substr(0,pos);
        string ip_address = line.substr(pos+1);

        //check if the file domain name is found and if yes return the IP Address
        if(file_domain_name == domain_name){
            lines.push_back(domain_name + "=" +ip_address);
            found = true;
            continue;
        }
        lines.push_back(line); //keep unchanged
    }
    file_read.close();
    if(!found){
        lines.push_back(domain_name + "=" + ip_address); //put at last
    }

    ofstream file_write(filename);
    if(!file_write.is_open()){ //some error
        return;
    }
    for(const string &entry: lines){
        file_write << entry << endl;
    }
    file_write.close();
    clean_up_cache("dns.txt");
}
