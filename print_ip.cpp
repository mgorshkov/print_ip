/**
 * @file print_ip.cpp
 *
 * Methods for printing ip addresses of different representations.
 */
#include <iostream>
#include <type_traits>
#include <list>
#include <vector>
#include <tuple>

/**
 * @brief Prints out content of an ip address represented as an integral type.
 */
template <typename T>
static std::enable_if_t<std::is_integral_v<T>, void> PrintIp(T value)
{
    while (true)
    {
        std::cout << (value & 0xFF);
        value >>= 8;
        if (value == 0)
        {
            std::cout << std::endl;
            break;
        }
        else
            std::cout << ".";
    }
}

std::ostream& operator << (std::ostream& stream, const std::string& str)
{
    return stream << str.c_str();
}

/**
 * @brief Prints out contents of an ip address represented as a vector or a list.
 */
template <typename T>
static std::enable_if_t<!std::is_integral_v<T>, void> PrintIp(const T& container)
{
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        std::cout << *it;
        if (it != std::prev(container.end()))
            std::cout << ".";
    }
    std::cout << std::endl;
}

/**
 * \defgroup Helper structs for printing tuples of same types.
 */
/**@{*/
template <size_t I>
struct PrintTuple
{
    template <typename Type0, typename... Types>
    static constexpr void Print(const std::tuple<Type0, Types...>& tuple)
    {
        auto element = std::get<sizeof...(Types) + 1 - I>(tuple);
        static_assert (std::is_same_v<Type0, decltype(element)>, "different types in tuple!");

        std::cout << element;
        if (I > 1)
            std::cout << ".";

        PrintTuple<I - 1>::Print(tuple);
    }
};

template <>
struct PrintTuple<0>
{
    template <typename... Types>
    static constexpr void Print(const std::tuple<Types...>&) {}
};
/**@}*/

/**
 * @brief Prints out contents of an ip address represented as a tuple.
 */
template <typename... Types>
static void PrintIp(const std::tuple<Types...>& tuple)
{
    PrintTuple<sizeof...(Types)>::Print(tuple);
    std::cout << std::endl;
}

/**
 * @brief Main function with ip printine demo.
 */
int main(int, char const **)
{
    try
    {
        PrintIp(0);
        PrintIp(1);
        PrintIp(255);
        PrintIp(256);
        PrintIp(1234567890);
        PrintIp(1234567890123456);

        PrintIp(std::list<int>{0, 1, 2, 3});

        PrintIp(std::vector<std::string>{"abc", "def", "gij", "klm", "nop", "rst"});

        PrintIp(std::tuple<int, int, int, int>{127, 0, 0, 1});
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
