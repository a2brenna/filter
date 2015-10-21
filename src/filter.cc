#include <iostream>
#include <sstream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include "median_filter.h"

namespace po = boost::program_options;

size_t COLUMN = 1;
size_t WINDOW_SIZE = 3;
bool INTEGER_DATA = false;

void get_config(int argc, char *argv[]) {
  po::options_description desc("Options");
  desc.add_options()
      ("window_size", po::value<size_t>(&WINDOW_SIZE), "Size of filter window")
      ("column", po::value<size_t>(&COLUMN), "Column of data to filter")
      ("integers", po::value<bool>(&INTEGER_DATA), "Whether or not data is integer")
      ;

    assert(COLUMN >= 1);
    assert(WINDOW_SIZE >= 3);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
}

template <typename T>
T lexical_cast(const std::string& str)
{
    T var;
    std::istringstream iss;
    iss.str(str);
    iss >> var;
    return var;
}

template <typename T>
void process(){

    Median_Filter<T> filter(WINDOW_SIZE);

    std::string input;
    std::vector<std::string> tokens;
    while(std::getline(std::cin, input)){
        split(tokens, input, boost::is_any_of(" "), boost::token_compress_on);
        assert(tokens.size() >= COLUMN);
        const T foo = lexical_cast<T>(tokens[COLUMN - 1]);
        filter.append(foo);
        tokens[COLUMN - 1] = std::to_string(filter());
        std::string output;
        for(size_t i = 0; i < tokens.size() - 1; i++){
            output = output + tokens[i] + " ";
        }
        output = output + tokens[tokens.size() - 1];
        std::cout << output << std::endl;
    }

}

int main(int argc, char *argv[]){
    get_config(argc, argv);

    if(INTEGER_DATA){
        process<long long>();
    }
    else{
        process<double>();
    }

    return 0;
}
