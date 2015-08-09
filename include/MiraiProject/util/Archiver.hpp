////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com),
//                         BOULMIER Jérôme (jerome.boulmier@outlook.fr)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

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
