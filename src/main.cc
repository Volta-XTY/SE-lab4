#include<GenerateInput.hh>
#include<Judge.hh>
#include<CompareOutput.hh>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[]){

	fs::path testPath{"tests/50A"};
	GenerateInput gInput{testPath};
	gInput.Generate();
}
