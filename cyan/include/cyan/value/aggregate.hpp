//
// Created by KHML on 2020/04/25.
//

#ifndef CYAN_VALUE_AGGREGATE_HPP
#define CYAN_VALUE_AGGREGATE_HPP

#include <vector>

#include <cyan/type.hpp>
#include <cyan/value/value.hpp>

namespace cyan
{
    class StructBlock;

    class Aggregate : public Value
    {
    public:
        explicit Aggregate(const Type& type);

        explicit Aggregate(const Type&& type);

        explicit Aggregate(const StructBlock& structBlock);

        ~Aggregate() override;

        std::string value() const override;

        void append(const Value& item);

        void append(Value&& item);

        Aggregate& operator<<(const Value& item);

        Aggregate& operator<<(Value&& item);

        std::unique_ptr<Value> ptr() const override;

    protected:
        std::vector<std::string> items;
    };
}

#endif //CYAN_VALUE_AGGREGATE_HPP
