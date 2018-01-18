/**
 * @file print_ip.cpp
 *
 * Methods for printing ip addresses represented in different ways.
 */
#include <iostream>
#include <type_traits>
#include <list>
#include <vector>
#include <tuple>
#include <string>

static const char OctetSeparator = '.';

/**
 * @brief Prints out contents of an ip address represented as an integral type.
 */
template <typename T>
static std::enable_if_t<std::is_integral_v<T>, void> PrintIp(T value)
{
    static const size_t constexpr SizeInOctets = sizeof(T);
    for (size_t i = SizeInOctets; i--;)
    {
        std::cout << (value >> (i << 3) & 0xFF);
        if (i > 0)
            std::cout << OctetSeparator;
    }
    std::cout << std::endl;
}

/**
 *  @brief Prints out contents of an ip address represented as a string.
 */
static void PrintIp(const std::string& value)
{
    std::cout << value << std::endl;
}

/**
 * @brief Helper struct. Determines whether T is std::vector or std::list.
 */
template <typename>
struct is_std_vector_or_list : std::false_type {};

template <typename T, typename... Args>
struct is_std_vector_or_list<std::vector<T, Args...>> : std::true_type {};

template <typename T, typename... Args>
struct is_std_vector_or_list<std::list<T, Args...>> : std::true_type {};

/**
 * @brief Prints out contents of an ip address represented as a vector or a list.
 */
template <typename T>
static void PrintIp(std::enable_if_t<is_std_vector_or_list<T>::value, const T&> container)
{
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        std::cout << *it;
        if (it != std::prev(container.end()))
            std::cout << OctetSeparator;
    }
    std::cout << std::endl;
}

/**
 * \defgroup helpers
 * Helper structs for printing ip addresses as tuples of same types.
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
            std::cout << OctetSeparator;

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
 * @brief Main function with ip printing demo.
 */
int main(int, char const **)
{
    try
    {
        char addrChar{-1};
        PrintIp(addrChar);

        short addrShort{0};
        PrintIp(addrShort);

        int addrInt{2130706433};
        PrintIp(addrInt);

        long addrLong{8875824491850138409};
        PrintIp(addrLong);

        PrintIp("123.45.67.89.12.34.56");

        using IntList = std::list<int>;
        IntList l{0, 1, 2, 3};
        PrintIp<IntList>(l);

        using StringVector = std::vector<std::string>;
        StringVector v{"abc", "def", "gij", "klm", "nop", "rst"};
        PrintIp<StringVector>(v);

        std::tuple<int, int, int, int> t{127, 0, 0, 1};
        PrintIp(t);

        std::tuple<std::string, std::string, std::string> tStr{"abc", "def", "gij"};
        PrintIp(tStr);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
