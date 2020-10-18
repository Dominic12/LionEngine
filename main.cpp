#include "main.h"

int main(int argc, char* argv[]) {

    if(argc < 2){
        std::cout << "Please provide a js file to run" << std::endl;
        return -1;
    }


    std::cout << "Opening file " << argv[1] << std::endl;

    std::ifstream jsinput(argv[1]);


    std::string inputStr;


    if(jsinput.is_open()){
        std::string line;
        while ( getline (jsinput,line) )
        {
            inputStr += line + '\n';
        }
    }else{
        std::cout << "Couldn't read input file" << std::endl;
        return -1;
    }


    Tokenizer tokenizer(inputStr);

    auto *tokens = tokenizer.Tokenitze();
    Parser parser(tokens);
    parser.Parse();

    return 0;
}
