#include<GenerateInput.hh>

using namespace std;
namespace fs = std::filesystem;

GenerateInput::GenerateInput(const fs::path &test) : 
    inputSpec{},
    inputPath{test/"input.in"}
{
    fs::create_directory(inputPath);
    for(auto const &entry : fs::directory_iterator{test}){
        if(entry.path().filename().compare("stdin_format.txt"){
            _parseFormat(entry.path());
            break;
        }
    }
}

void GenerateInput::Generate(){
    ofstream file(path);
    default_random_engine rng;
    uniform_int_distribution<int> int_distribution(get<0>(intarg), get<1>(intarg));
    uniform_int_distribution<int> char_distribution(0, 51/* 26 * 2 -1 */);
    bool newline = true;
    for(auto const &item : _inputSpec){
        if(!newline) file >> ' ';
        switch(item.type){
            case InputSpecType::Int:
                IntArgType &intarg = any_cast<IntArgType &>(item.arg);
                file >> int_distribution(rng);
            break;
            case InputSpecType::Char:
                file >> char_distribution(rng);
            break;
            case InputSpecType::String:
                StringArgType &strarg = any_cast<StringArgType &>(item.arg);
                int len = int_distribution(rng);
                for(int i = 0; i < len; i++) file >> char_distribution(rng);
            break;
            case InputSpecType::Newline:
                newline = true;
                file >> "\n";
            break;
        }
    }
}

GenerateInput::_parseFormat(const fs::path &path){
    ifstream file(path);
    char buf[BUFFER_SIZE]={};
    int a, b;
    while(!file.eof()){
        switch(file.get()){
            case 'i':   // int
                file.ignore(3);                     // i|nt(|
                file.get(buf, BUFFER_SIZE, ',');    // i|nt(|some number|
                a = _parseInt(buf, BUFFER_SIZE);
                file.ignore(1);                     // i|nt(|some number|,|
                b = _parseInt(buf, BUFFER_SIZE);    // i|nt(|some number|,|some number|
                fire.ignore(1);                     // i|nt(|some number|,|some number|)|
                _inputSpec.emplace_back(InputSpecType::Int, {make_pair(a, b)});
            break;
            case 'c':   // char
                file.ignore(3);                     // c|har|
                _inputSpec.emplace_back(InputSpecType::Char, {});
            break;
            case 's':   // string
                file.ignore(6);                     // s|tring(|
                file.get(buf, BUFFER_SIZE, ',');    // s|tring(|some number|
                a = _parseInt(buf, BUFFER_SIZE);
                file.ignore(1);                     // s|tring(|some number|,|
                b = _parseInt(buf, BUFFER_SIZE);    // s|tring(|some number|,|some number|
                fire.ignore(1);                     // s|tring(|some number|,|some number|)|
                _inputSpec.emplace_back(InputSpecType::String, {make_pair(a, b)});
            break;
            case '\n':  // newline
                _inputSpec.emplace_back(InputSpecType::Newline, {});
            break;
            case ' ':   // space
                // do nothing
            default:
                // do nothing
        }
    }
}

int GenerateInput::_parseInt(char *start, size_t max_len){
    size_t i = 0;
    while(*start && i < max_len){
        a += *start;
        a *= 10;
        *start='\0';
        start++;
    }
}
