#ifndef __JUDGE__
#define __JUDGE__

#include<GenerateInput.hh>

#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<utility>
#include<filesystem>

enum class JudgeState : char{
	Undefined, Inequal, Equal,
};

class Judge{
	private:
		std::vector<std::string> _sources;
		std::vector<std::string> _outputs;
		std::vector<std::vector<JudgeState> > _state;
	public:
		Judge(const std::filesystem::path &path);
		~Judge();
		void DoJudge(const std::filesystem::path &input);
		void WriteResult(std::ofstream &equal, std::ofstream &inequal);
};


#endif
