
#include "../include/tpl.h"
#include "../include/unittest.h"
#include "../include/tpl/debug.h"

using namespace tpl;
using namespace tpl::prop;

class A{};
class B{};
class C{};
class D{};

TestCase(tpl_prop){
    AssertTrue<
        typename $eval< $env<$var<A>, $false>, $exists<$var<A>, $true>>::value
    >();

    AssertAll<
        typename $eval<$env<>, $true>::value, /// T
        typename $eval<$env<>, $not<$false>>::value,    /// !F
        typename $eval<$env<>, $or<$false,$true>>::value,  /// F || T
        typename $eval<$env<>, $implies<$false,$true>>::value, /// F => T
        typename $eval<$env<>, $iff<$false,$false>>::value,    /// F <=> F
        typename $eval<$env<$var<A>, $false>, $not<$var<A>>>::value, /// A = F, !A

        /// A = T, !A => A
        typename $eval<$env<$var<A>, $true>,  $implies<$not<$var<A>>, $var<A>>>::value,

        /// forall A, T
        typename $eval<$env<>, $forall<$var<A>, $true>>::value,
        /// exists A, !A
        typename $eval<$env<>, $exists<$var<A>, $not<$var<A>>>>::value
    >();
}
