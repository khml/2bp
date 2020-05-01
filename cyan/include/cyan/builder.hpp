//
// Created by KHML on 2020/04/30.
//

#ifndef CYAN_BUILDER_HPP
#define CYAN_BUILDER_HPP

#include <string>
#include <vector>

#include <cyan/container/module.hpp>

namespace cyan
{
    class Builder
    {
    public:
        Builder(const Builder&) = delete;

        Builder& operator=(const Builder&) = delete;

        Builder(Builder&&) = delete;

        Builder& operator=(Builder&&) = delete;

        static Builder& instance();

        bool dump(const Module& module);

        bool build(const std::string& name);

        bool build(std::string&& name);

    protected:
        Builder();

        virtual ~Builder();

        void append(const std::string& name);

        const std::string _dirname = "__cyan__/";
        const std::string _headers = "__cyan__/headers/";
        std::vector<std::string> sources;
        std::vector<std::string> headers;
        std::vector<std::string> objs;
    };
}

#endif //CYAN_BUILDER_HPP
