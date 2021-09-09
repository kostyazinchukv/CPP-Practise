#include <iostream>
#include <sstream>

class Slot{
    public:
        Slot(): state("never used"){

        }
        Slot(const Slot&) = delete;
        Slot operator=(const Slot&) = delete;

        std::string get_state() const{
            return state;
        }
        std::string get_key() const{
            return key;
        }
        void set_state(const std::string& st){
            state = st;
        }
        void set_key(const std::string& k){
            key = k;
        }
    private:
        std::string state;
        std::string key;
};

class HashTable{
    public:
        static const int size = 26;
    public:
        HashTable() = default;

        int get_index(const std::string& key){
            return static_cast<int>(key.back()) - static_cast<int>('a');
        }

        bool search(const std::string& key){
            short counter = 1;
            int index = get_index(key);
            while(true){
                if(slots[index].get_key() == key)
                    return true;
                if(slots[index].get_state() == "never used")
                    return false;
                if(slots[index].get_state() == "occupied" || slots[index].get_state() == "tombstone")
                    index = (index + 1) % size;
                if(counter++ > size){
                    return false;
                }
            }
        }

        void delete_key(const std::string& key){
            if(!search(key)){
                return;
            }
            else{
                int index = get_index(key);
                while(true){
                    if(slots[index].get_key() == key)
                    {
                        slots[index].set_state("tombstone");
                        break;
                    }
                    else
                        index = (index + 1) % size;
                }
            }
        }
        void insert(const std::string& key){
            if(!search(key)){
                int index = get_index(key);
                while(true){
                    if(slots[index].get_state() == "never used" || slots[index].get_state() == "tombstone"){
                        slots[index].set_key(key);
                        slots[index].set_state("occupied");
                        break;
                    }
                    else{
                        index = (index + 1) % size;
                    }
                }
            }
            else{
                return;
            }
        }

        void print_consistance()
        {
            for(int i = 0; i<size; i++)
            {
                std::cout<<"Slot "<< i+1;
                std::cout<<": Data - "<<slots[i].get_key() << "| State ( " << slots[i].get_state() << " )"<<std::endl;
            }
        }
    
    private:
        Slot slots[26];
};

int main(){
    HashTable table;

    std::string input;
    getline(std::cin, input);
    std::stringstream ss(input);

    while(ss.good()){

        std::string token;
        ss >> token;
        if(token.size() > 10)
            continue;
        std::string token_key = token.substr(1);

        if(token[0] == 'A')
        {
            std::cout<<"Add "<<token_key<<std::endl;
            table.insert(token_key);
        }
        else if(token[0] == 'D')
        {
            std::cout<<"Delete "<<token_key<<std::endl;
            table.delete_key(token_key);
        }
    }
    table.print_consistance();

    return 0;
}