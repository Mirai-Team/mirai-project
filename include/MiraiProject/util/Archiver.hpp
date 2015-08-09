#ifndef MP_ARCHIVER_HPP
#define MP_ARCHIVER_HPP

#include <functional>
#include <string>
#include <vector>

namespace mp {
namespace priv {
template<class T>
bool stringComparaison(T const &a, T const &b) { return a > b; }
} // priv

class Archiver {
public:
    Archiver();

    void createFile(const std::string& outputFile,
        const std::string& directory,
        const std::function<void(void* data, size_t size)>& encryption = nullptr,
        const std::function<void(void* data, size_t size)>& compression = nullptr);

    std::vector<char> loadFile(const std::string& inputFile,
        const std::string& targetFile,
        const std::function<void(void* data, size_t size)>& decryption = nullptr,
        const std::function<void(void* data, size_t size)>& decompression = nullptr);

private:
    void writeHeader(std::fstream* output,
        const std::string& directory);

    void writeBody(std::fstream* output,
        const std::string& directory,
        const std::function<void(void* data, size_t size)>& encryption,
        const std::function<void(void* data, size_t size)>& compression = nullptr);

    std::vector<std::string> fileNames_;
    unsigned int headerLength_;
};
} // mp

#endif // MP_ARCHIVER_HPP
