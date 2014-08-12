
#include "tpl.h"
#include "unittest.h"
#include <typeinfo>
#include <iostream>

using namespace std;

using namespace tpl::nat;
using namespace tpl::nat::relation;
using namespace tpl::list;
using namespace tpl::list::util;
using namespace tpl::list::iter;

template<class Num>
struct addone{
    using value = succ<Num>;
};



TestCase(TPL_THE_TEMPLATE_PROGRAMMING_LIBRARY){
    /// equal
    cout<<typeid(is_equal<one,one>::value).name()<<endl;
    cout<<typeid(is_equal<one,two::pred>::value).name()<<endl;

    /// add mul
    cout<<typeid(is_equal<add<one, two>::value,three>::value).name()<<endl;
    cout<<typeid(is_equal<mul<five, two>::value,ten>::value).name()<<endl;

    /// less_than
    cout<<typeid(is_less_than<mul<two,three>::value,add<two,five>::value>::value).name()<<endl;
    cout<<typeid(is_less_equal<mul<two,three>::value,add<one,five>::value>::value).name()<<endl;

    /// decimal
    cout<<typeid(is_equal<decimal<one,one>::value,add<one,ten>::value>::value).name()<<endl;
    cout<<typeid(is_equal<decimal<one,zero,zero>::value, mul<ten,ten>::value>::value).name() << endl;
    cout<<typeid(is_equal<sub<three,one>::value, two>::value).name() << endl;

    ///  10 / 3 == 3 ... 1
    cout<<typeid(eq<div<i10,i3>::value,i3>::value).name()<<endl;
    cout<<typeid(eq<div<i10,i3>::rem,i1>::value).name()<<endl;

    ///  10 / 100 == 0 ... 10
    cout<<typeid(eq<div<i10,i100>::value,i0>::value).name()<<endl;
    cout<<typeid(eq<div<i10,i100>::rem,i10>::value).name()<<endl;

    /// length / first / rest / concat
    cout<<typeid(eq<typename list<i1,i2,i3>::length, three>::value).name() <<endl;
    cout<<typeid(eq<typename list<i1,i2,i3>::value::rest::rest::first, three>::value).name() <<endl;
    cout<<typeid(eq<typename list<i1,i2,i3>::value, concat<list<i1,i2,i3>::value,nil>::value>::value).name() <<endl;
    cout<<typeid(eq<
                        typename list<i1,i2,i5,i6>::length,
                        concat<
                                list<i1,i2,i5,i6>::value,
                                nil
                            >::length
                    >::value).name() <<endl;

    /// take
    cout<<typeid(eq<typename list<i1,i2,i3>::value, take<i3,list<i1,i2,i3,i4>::value>::value>::value).name() <<endl;
    cout<<typeid(eq<typename list<i1,i2,i3>::length, take<i3,list<i1,i2,i4,i3>::value>::length>::value).name() <<endl;

    /// map
    cout<<typeid(eq<
                        typename list<i2,i3,i4>::value,
                        map<addone, typename list<i1,i2,i3>::value >::value
                    >::value).name() <<endl;
    /// reduce
    cout<<typeid(eq<
                        typename reduce<add, i0, typename list<i1,i2,i3,i4>::value> :: value,
                        i10
                 >::value).name()<<endl;
    cout<<typeid(eq<
                        typename reduce<mul, i1, typename list<i1,i2,i3,i4>::value> :: value,
                        typename mul<i8, i3>::value
                 >::value).name()<<endl;
}
