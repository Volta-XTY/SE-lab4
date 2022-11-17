#include<fstream>
#include<string>
#include<random>
#include<utility>
#include<filesystem>

#include<InputSpecItem>

class GenerateInput{
    private:
        static size_t BUFFER_SIZE = 256;
        static char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        std::vector<InputSpecItem> _inputSpec;
        std::filesystem::path _inputPath;
        
        void GenerateInput::_parseFormat(const fs::path &path);
        int GenerateInput::_parseInt(char *start, size_t max_len);

    public:
        // Initialize and read input spec from {test : path}.
        GenerateInput(const std::filesystem::path &test);

        // Returns the path to which the object will write the generated input.
        const std::filesystem::path &InputPath(){ return inputPath; }

        // Generate one test case.
        void Generate();
}
