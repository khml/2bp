//
// Created by KHML on 2020/05/02.
//

#ifndef CYAN_IMPL_UTILITIES_HPP
#define CYAN_IMPL_UTILITIES_HPP

namespace cyan
{
    template<typename T>
    constexpr void mergeVector(std::vector<T>& to, std::vector<T>& from)
    {
        to.reserve(to.size() + from.size());
        std::move(from.begin(), from.end(), std::back_inserter(to));
    }

    template <typename T>
    constexpr void mergeVector(std::vector<T>& to, std::vector<T>&& from)
    {
        mergeVector(to, from);
    }
}

#endif //CYAN_IMPL_UTILITIES_HPP
