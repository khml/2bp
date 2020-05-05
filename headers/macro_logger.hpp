//
// Created by KHML on 2020/01/19.
//

#ifndef BLUEPRINT_MACROLOGGER_HPP
#define BLUEPRINT_MACROLOGGER_HPP

#ifdef DEBUG
#include <iostream>
#if DEBUG == 0
#define LOG_DEBUG(value) std::cerr << value << std::endl
#else
#define LOG_DEBUG(value)
#endif

#if DEBUG <= 1
#define LOG_INFO(value) std::cerr << value << std::endl
#else
#define LOG_INFO(value)
#endif

#if DEBUG <= 2
#define LOG_WARN(value) std::cerr << value << std::endl
#else
#define LOG_WARN(value)
#endif

#if DEBUG <= 3
#define LOG_ERROR(value) std::cerr << value << std::endl
#else
#define LOG_ERROR(value)
#endif

#ifdef DEBUG2
#define LOG2(value) std::cerr << value << std::endl
#else
#define LOG2(value)
#endif
#else
#define LOG_DEBUG(value)
#define LOG_INFO(value)
#define LOG_WARN(value)
#define LOG_ERROR(value)
#endif

#define STD_LOG(value) std::cout << value << std::endl
#define STD_ERR_LOG(value) std::cerr << value << std::endl

#endif //BLUEPRINT_MACROLOGGER_HPP
