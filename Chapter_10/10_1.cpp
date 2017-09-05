//EOPI Problem 10.1
#include <iostream>
#include <string>
#include <limits>

unsigned int hash(std::string in){
    unsigned int hash=1;
    for (int i=0; i<in.length(); i++){
        //multiplicatibe hash = \prod_i^n a_i \bmod max_hash_size
        hash = hash * in[i] % std::numeric_limits<unsigned int>::max();
    }
    return hash;
}

int main(int argc, char** argv){
    if (argc != 2){
        std::cout << "Usage : ./hash <input_word>\n";
        return 0;
    }

    std::cout << hash(argv[1]) << std::endl;
}
