#ifndef __GENERATE_INPUT__
#define __GENERATE_INPUT__

#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<utility>
#include<filesystem>

#include<InputSpecItem.hh>

class GenerateInput{
    private:
        static const size_t BUFFER_SIZE{256};
        constexpr static const char _chars[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        std::vector<InputSpecItem> _inputSpec;
        std::filesystem::path _inputPath;
        
        void _parseFormat(const std::filesystem::path &path);
        int _parseInt(char *start, size_t max_len);

    public:
        // Initialize and read input spec from {test : path}.
        GenerateInput(const std::filesystem::path &test);

        // Returns the path to which the object will write the generated input.
        const std::filesystem::path &InputPath(){ return _inputPath; }

        // Generate one test case.
        void Generate();
        ~GenerateInput();
};

#endif
