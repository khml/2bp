//
// Created by KHML on 2020/03/28.
//

#ifndef BLUEPRINT_FILEREADER_HPP
#define BLUEPRINT_FILEREADER_HPP

#include <string>
#include <vector>

namespace io
{
    std::vector<std::string> readFile(const std::string& filename);

    class FileReader
    {
    public:
        explicit FileReader(const std::string& filename);

        FileReader(const FileReader& orig);

        virtual ~FileReader();

        std::vector<std::string> lines();

    protected:
        const std::string filename;
        std::vector<std::string> _lines;

    };
}

#endif //BLUEPRINT_FILEREADER_HPP
