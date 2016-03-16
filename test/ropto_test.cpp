#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <cassert>
#include <map>

#include "../include/unittest.h"
#include "../include/ropto.hpp"
#include "../include/ropto/Service.hpp"

using namespace ropto;

struct employee
{
    static constexpr unsigned int type_id = 0x01;
    int number;
    std::string name;
    double salary;
};

struct department
{
    static constexpr unsigned int type_id = 0x02;
    optional<std::string> title;
    std::map<int, employee> people;
};

template<>
class serializer<employee>
{
public:
    static employee from_bytes(byte_stream& stream)
    {
        employee value;
        stream >> value.number >> value.name >> value.salary;
        return value;
    }
    
    static void to_bytes(const employee& value, byte_stream& stream)
    {
        stream << value.number << value.name << value.salary;
    }
};

template<>
class serializer<department>
{
public:
    static department from_bytes(byte_stream& stream)
    {
        department value{};
        read(stream, value.people, value.title);
        return value;
    }
    
    static void to_bytes(const department& value, byte_stream& stream)
    {
        write(stream, value.people, value.title);
    }
};

TestCase(ropto_test)
{
    byte_stream stream;
    
    department x {
        {},
        {
            {1, {1, "Kimmy", 1200.00}},
            {2, {2, "Joey", 1500.00}}
        }
    };
    
    std::vector<employee> emp {};
    int v = 0;
    std::generate_n(back_inserter(emp), 100000, [&v](){
        return employee{v++, "Angi", 1700.0 * v};
    });
    
    
    write(emp, stream);
    
    
    byte_stream stm;
    
    stm.iterate() = stream.iterate();
    
    std::vector<employee> emp2 {};
    
    read(stm, emp2);
    
    std::cout<< emp2.size();
}
