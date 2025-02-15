//Name: Acacie Song
//ID: 261182381
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

std::string get_ip_address(const string& domain_name);
void print_cache();
void clean_up_cache(string filename);
void print_dns_file(string filename);
void add_update(string filename);
void insertDomain(string file_domain_name, string ip_address);
void move_to_front(string domain_name);

//global var
//Q4
//unordered_map is efficient to look up
//key: domain
//pair: 
//first element: still get the IP address of the domain
//second element: stores the iterator pointing to position of the domain in the cacheOrder like i = 1
unordered_map<string, pair<string, list<string>::iterator>> dnsMap; //cache
//list to maintains the order list<domain_name>
list<string> cacheOrder;
int cacheSize = 5;

int main() { 
    //with a basic dns.txt
    cout<<"A basic dns "<<endl;
    std::ofstream dnsBasicFile("dns.txt", std::ios::trunc); 
    dnsBasicFile << "www.example.com=2.2.2.2" << std::endl; 
    dnsBasicFile << "www.google.com=8.8.8.8" << std::endl; 
    dnsBasicFile << "www.github.com=3.3.3.3" << std::endl; 
    dnsBasicFile << "www.stackoverflow.com=4.4.4.4" << std::endl; 
    dnsBasicFile << "www.reddit.com=151.101.1.70" << std::endl; 
    dnsBasicFile << "www.twitter.com=1.1.1.1" << std::endl; 
    dnsBasicFile.close();
    print_dns_file("dns.txt");

    cout<<endl;
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
    cout<< "Cache with: (last) example, google, github, stackoverflow, reddit (first)"<< endl;
    print_cache(); 
    

   
    // Access an existing entry to update its position in the LRU list 
    std::cout << "IP address for www.google.com: " << get_ip_address("www.google.com") << std::endl; 
    
    cout<< "Cache with: (last) example, github, stackoverflow, reddit, google (first)"<< endl;
    print_cache();
    // Add a new entry, which should evict the least recently used entry 
    std::cout << "IP address for www.twitter.com: " << get_ip_address("www.twitter.com") << std::endl; 
    
    cout<< "Cache with: (last) github, stackoverflow, reddit, google, twitter (first)"<< endl;
    // Print the cache contents again to verify the eviction 
    print_cache(); 
    
    cout<<"Modifying the dns file simulate change"<<endl;
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
    cout << "Cache with: (last) github, stackoverflow, reddit, google (first)" <<endl;
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



void move_to_front(string domain_name){  
    //remove domain from position in the cacheOrder list
    cacheOrder.erase(dnsMap[domain_name].second);

    //add it that to the front as Most recently used
    cacheOrder.push_front(domain_name);

    //Update iterator in the dnsMap
    dnsMap[domain_name].second = cacheOrder.begin();
}

void insertDomain(string domain_name, string ip_address){

    //if exists, you move to front and update IP;
    if(dnsMap.find(domain_name)!=dnsMap.end()){ 

        dnsMap[domain_name].first = ip_address;
        move_to_front(domain_name);
        cout<<"you remove something existant "<<domain_name<<endl;
    }else{

        if(dnsMap.size()>=cacheSize){ //if full

            //remove LRU domain
            string lru_domain = cacheOrder.back();
            dnsMap.erase(lru_domain);
            cacheOrder.pop_back();
            
            //cout<<"you remove something LRU "<<lru_domain<<endl;
        }

        //insert new domain at the front
        cacheOrder.push_front(domain_name);
        dnsMap[domain_name] = {ip_address, cacheOrder.begin()};
    }
    
}

//Q1
string get_ip_address_from_file(const string& domain_name) {

    //read the file dns.txt
    ifstream readfile;
    readfile.open("dns.txt");

    if(readfile.is_open()){

        string line; 
        while(getline(readfile, line)){ //read file line by line
            size_t pos = line.find('='); //split line by delimiter '='
            
            //key-value pairs: file_domain_name and ip_address
            string file_domain_name = line.substr(0,pos);
            string ip_address = line.substr(pos+1);

            //check if the file domain name is found and if yes return the IP Address
            if(file_domain_name == domain_name){
                //cout << file_domain_name << endl;
                insertDomain(file_domain_name, ip_address); //insert the domain in the cache
                readfile.close();
                return ip_address;
            }
        }
    }
    readfile.close();
    return ""; //cannot be opened or not found
}

//Q2
string get_ip_address(const string& domain_name){

    //if requested domain is present in the cache.
    if(dnsMap.find(domain_name)!=dnsMap.end()){
        //cout<<"found"<<endl;
        move_to_front(domain_name);
        return dnsMap[domain_name].first;
    }
    //cout<<" didn't find"<<endl;
    string ip_address = get_ip_address_from_file(domain_name);
    return ip_address;
}

//Q3
void print_cache(void) {
    
    cout << "\nCache contents:"<<endl;

    for (const auto &domain: cacheOrder) {
        cout<< "cache: " << domain << " = " << dnsMap[domain].first << endl;
    }
    
    cout << endl; //more space between
}
//Q5
void clean_up_cache(string filename) { 

    //choose this as it is easy to check if the data in the cache is in the dns
    unordered_map<string, string> dnsNewData;

    ifstream readfile;
    readfile.open(filename);

    //get each line of the file
    if(readfile.is_open()){
        string line; 
        while(getline(readfile, line)){ 
            size_t pos = line.find('=');
            string domain_name = line.substr(0,pos);
            string ip_address = line.substr(pos+1);

            //when find domain in the cache, change its IP to the one in the DNS
            if(dnsMap.find(domain_name) != dnsMap.end()){
                dnsMap[domain_name].first = ip_address;
            }

            //get the data of the dns file in a map 
            dnsNewData.insert({domain_name, ip_address});
        }
    }

    for (auto i = cacheOrder.begin(); i != cacheOrder.end(); ) {
        //if you can't find the domain of the cache in the dnsNewData, remove it
        if (dnsNewData.find(*i) == dnsNewData.end()) { 
            //cout << "erase cache: " << *i << " = " << dnsMap[*i].first << endl;
            dnsMap.erase(*i); 
            i = cacheOrder.erase(i);  // erase from list, also update the iterator
        } else {
            //cout << "?cache: " << *i << " = " << dnsMap[*i].first << endl;
            ++i;  // Only ++increment, if not removed
        }
    }
   
    readfile.close();
    return; //cannot be opened or not found
}

void print_dns_file(string filename) {

    //read the file
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "The File can't be open"<< endl;
        return;
    }

    cout << "Here is the DNS file contents:"<<endl;
    string line;
    while (getline(file, line)) { //print each line of DNS file
        cout << line << endl;
    }
    file.close();
}

//Q6
void add_update(string filename) {

    //ask user about domain_name and ip_address
    string new_domain_name, new_ip_address;
    cout << "Enter domain name: ";
    cin >> new_domain_name; //get user response domain_name
    cout << "Enter IP address: ";
    cin>> new_ip_address; //get user ip_address 
    
    //The new line
    string new_line = new_domain_name+"="+new_ip_address;
    cout<<"We Update/add this: " << new_line <<endl;

    //used this data structure as it has an order so you can rewrite it and also insertion time doesn't need O(1)
    list<string> lines; 

    //read the file to get if the domain_ip exist
    //if exist don't include
    ifstream file_read(filename);
    if(!file_read.is_open()){ //if not open
        cerr << "Error open file for read\n";
        return;
    }
    
    string line;
    while(getline(file_read, line)){
        size_t pos = line.find('=');
        string domain_name = line.substr(0,pos);
        string ip_address = line.substr(pos+1);

        if(domain_name!=new_domain_name){ // if exist don't include that line
            lines.push_back(line);
        }
    }
    //new update/add line
    lines.push_back(new_line);
    file_read.close();

    //rewrite the entire file
    ofstream file_write(filename);
    if(!file_write.is_open()){ //if not open
        cerr << "Error open file for write\n";
        return;
    }
    //rewrite the dns with the new line
    for(const string &eachLine: lines){
        file_write<< eachLine <<endl;
    }

    file_write.close();

    //clean cache so if update IP, it is also same in the cache
    clean_up_cache(filename);
}
