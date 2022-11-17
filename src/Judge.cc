#include<Judge.hh>

using namespace std;
namespace fs = std::filesystem;

void Judge::DoJudge(const fs::path &input){
	cout<<"Judge::DoJudge input: "<<input<<"\n";
	if(_sources.size() < 2) return;
	//string sh_cmd0 = "timeout 1 1 <" + input.string() + " &>o1";
	//string sh_cmd1 = "timeout 1 2 <" + input.string() + " &>o2";
	//string sh_cmp = "diff o1 o2 > cmpres";
	for(size_t i = 0; i < _outputs.size(); i++){
		for(size_t j = i + 1; j < _outputs.size(); j++){
			if(_state[i][j] != JudgeState::Equal) continue;
			//cout<<"first: "<<_outputs[i]<<" second: "<<_outputs[j]<<"\n";
			auto &state = _state[i][j];
			// Runtime Error -> Undefined (as is specified)
			if(system(("timeout 1 "+_outputs[i]+" < "+input.string()+" > o1").c_str()) != 0) { cout<<"err1\n"; state = JudgeState::Undefined; continue; }
			if(system(("timeout 1 "+_outputs[j]+" < "+input.string()+" > o2").c_str()) != 0) { cout<<"err2\n"; state = JudgeState::Undefined; continue; }
			switch(system("diff o1 o2 > cmpres")){
				case 0:
					break;
				case 1:
					break;
				default:
					;
			}
			ifstream resultFile{"cmpres"};
			resultFile.seekg(0, resultFile.end);
			cout<<"resultFile.tellg() = "<<resultFile.tellg()<<"\n";
			if(resultFile.tellg() > 0) state = JudgeState::Inequal;
		}
	}
	if(system("rm o1 o2 cmpres") != 0) cout<<"Judge: should not reach here\n";
}

void Judge::WriteResult(ofstream &equal, ofstream &inequal){
	if(_sources.size() < 2) return;
	for(size_t i = 0; i < _sources.size(); i++){
		for(size_t j = i + 1; j < _sources.size(); j++){
			switch(_state[i][j]){
				case JudgeState::Equal:
					equal << _sources[i] <<","<< _sources[j] <<"\n";
					break;
				case JudgeState::Inequal:
					inequal << _sources[i] <<","<< _sources[j] <<"\n";
					break;
				default:
					;
			}
		}
	}
}

Judge::Judge(const fs::path &path) :
	_sources{},
	_state{}
{
	cout<<"Judge::Judge() path: "<<path.string();
    for(auto const &entry : fs::directory_iterator{path}){
		auto const &extension = entry.path().extension();
        if((extension.compare(".cpp") == 0) ||
		   (extension.compare(".cc")  == 0) ||
		   (extension.compare(".c")   == 0)){
			_sources.push_back(entry.path().string());
			_outputs.push_back(entry.path().stem().string());
        }
    }
	for(size_t i = 0; i < _sources.size(); i++){
		if(system(("g++ " + _sources[i] + " -o " + _outputs[i]).c_str()) != 0){
			cerr << "NOT TESTED. should not reach here.\n";
		}
	}
	cout<<" source files: "<<_sources.size()<<"\n";
	_state.assign(_sources.size(), vector<JudgeState>(_sources.size(), JudgeState::Equal));
}

Judge::~Judge(){
	cout<<"Judge::~Judge()\n";
	for(size_t i = 0; i < _sources.size(); i++){
		if(system(("rm "+_outputs[i]).c_str()) != 0){
			cerr << "Judge: should not REACH here.\n";
		}
	}
}
