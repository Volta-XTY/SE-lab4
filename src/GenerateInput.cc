#include<GenerateInput.hh>

using namespace std;
namespace fs = std::filesystem;

GenerateInput::GenerateInput(const fs::path &test) : 
    _inputSpec{},
    _inputPath{test/"input.in"}
{
    for(auto const &entry : fs::directory_iterator{test}){
        if(entry.path().filename().compare("stdin_format.txt") == 0){
            _parseFormat(entry.path());
            break;
        }
    }
}

void GenerateInput::Generate(){
    cout<<"Generate()\n";
    ofstream file(_inputPath);
    default_random_engine rng;
    uniform_int_distribution<int> char_dist(0, 51/* 26 * 2 -1 */);
    bool newline = true;
    for(auto const &item : _inputSpec){
        cout<<"Generate() iteration\n";
        if(!newline) file << ' ';
        switch(item.type){
            case InputSpecType::Int:{
                cout<<"InputSpecType::Int "<<item.arg.first<<" "<<item.arg.second<<"\n";
                uniform_int_distribution<int> int_dist{get<0>(item.arg), get<1>(item.arg)};
                int ii = int_dist(rng);
                cout << ii << "\n";
                file << ii;
                break;
            }
            case InputSpecType::Char:{
                file << char_dist(rng);
                break;
            }
            case InputSpecType::String:{
                cout<<"InputSpecType::String "<<item.arg.first<<" "<<item.arg.second<<"\n";
                uniform_int_distribution<int> str_int_dist{get<0>(item.arg), get<1>(item.arg)};
                int len = str_int_dist(rng);
                cout<<len<<"\n";
                for(int i = 0; i < len; i++) file << static_cast<char>(_chars[char_dist(rng)]);
                break;
            }
            case InputSpecType::Space:{
                file << " ";
                break;
            }
            case InputSpecType::Newline:{
                newline = true;
                file << "\n";
                break;
            }
        }
    }
    file.close();
}

void GenerateInput::_parseFormat(const fs::path &path){
    cout << "_parseFormat()\n";
    ifstream file(path);
    cout<<"path: "<<path<<"\n";
    char buf[BUFFER_SIZE]={};
    char ch;
    int a, b;
    while(!file.eof()){
        cout<<"_parseFormat(): iteration\n";
        file.get(ch);
        switch(ch){
            case 'i':   // int
                cout<<"_parseFormat(): int";
                file.ignore(3);                     // i|nt(|
                file.get(buf, BUFFER_SIZE, ',');    // i|nt(|some number,|
                file.ignore(1);
                cout<<" "<<buf;
                a = _parseInt(buf, BUFFER_SIZE);
                file.get(buf, BUFFER_SIZE, ')');    // i|nt(|some number,|some number)|
                cout<<" "<<buf;
                file.ignore(1);
                b = _parseInt(buf, BUFFER_SIZE);
                cout<<"\n";
                _inputSpec.push_back({InputSpecType::Int, {a, b}});
            break;
            case 'c':   // char
                file.ignore(3);                     // c|har|
                cout<<"_parseFormat(): char\n";
                _inputSpec.push_back({InputSpecType::Char, {0, 0}});
            break;
            case 's':   // string
                cout<<"_parseFormat(): str \n";
                file.ignore(6);                     // s|tring(|
                file.get(buf, BUFFER_SIZE, ',');    // s|tring(|some number,|
                file.ignore(1);
                a = _parseInt(buf, BUFFER_SIZE);
                file.get(buf, BUFFER_SIZE, ')');    // s|tring(|some number,|some number)|
                file.ignore(1);
                b = _parseInt(buf, BUFFER_SIZE);
                _inputSpec.push_back({InputSpecType::String, {a, b}});
            break;
            case '\n':  // newline
                cout<<"_parseFormat(): '\\n'\n";// do nothing
                _inputSpec.push_back({InputSpecType::Newline, {0, 0}});
            break;
            case ' ':   // space
                cout<<"_parseFormat(): ' '\n";// do nothing
                _inputSpec.push_back({InputSpecType::Space, {0, 0}});
            break;
            default:
                cout<<"_parseFormat(): "<<ch<<"\n";// do nothing
        }
    }
}

int GenerateInput::_parseInt(char *start, size_t max_len){
    size_t i = 0;
    int a = 0;
    while(*start && i < max_len){
        a *= 10;
        a += (*start - '0');
        *start='\0';
        start++;
    }
    return a;
}

GenerateInput::~GenerateInput(){
    cout<<"GenerateInput::~GenerateInput()\n";
    if(system(("rm "+_inputPath.string()).c_str()) != 0){
        cerr << "should not reach here!\n";
    }
}
