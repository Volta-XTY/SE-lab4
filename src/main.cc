#include<GenerateInput.hh>
#include<Judge.hh>
#include<filesystem>
#include<fstream>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[]){
	// prepare output files	
	ofstream equalPairs{"equal.csv"};
	ofstream inequalPairs{"inequal.csv"};
	fs::path testsPath{"tests"};
    for(auto const &test: fs::directory_iterator{testsPath}){
		GenerateInput generate{test};
		Judge judge{test};
		for(size_t i = 0; i < 20; i++){
			generate.Generate();
			judge.DoJudge(generate.InputPath());
			judge.WriteResult(equalPairs, inequalPairs);
		}
	}
	cout<<"main() returns\n";
	return 0;
}
