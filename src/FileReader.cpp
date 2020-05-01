//
// Created by KHML on 2020/03/28.
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <utility>

#include "FileReader.hpp"

namespace io
{
    std::vector<std::string> readFile(const std::string& filename)
    {
        std::ifstream file(filename);
        std::vector<std::string> lines;

        if (file.fail())
            throw std::runtime_error("Failed to open file : " + filename);

        std::string line;
        while (getline(file, line))
            lines.emplace_back(line);

        return std::move(lines);
    }

    FileReader::FileReader(const std::string& filename) :filename(filename)
    {
        std::ifstream file(filename);

        if (file.fail())
            throw std::runtime_error("Failed to open file : " + filename);

        std::string line;
        while (getline(file, line))
            _lines.emplace_back(line);
    }

    FileReader::FileReader(const io::FileReader& orig): filename(orig.filename), _lines(orig._lines)
    {}

    FileReader::~FileReader()
    = default;

    std::vector<std::string> FileReader::lines()
    {
        return _lines;
    }
}
