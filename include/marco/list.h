/* 
 * File:   list.h
 * Author: liuqing
 *
 * Created on 2014年5月26日, 下午6:01
 */

#ifndef MARCO_LIST_H
#define	MARCO_LIST_H

#include "common.h"

#define _NUM_ARGS(X7, X6, X5, X4, X3, X2, X1, N, ...)   N

#define NUM_ARGS(...) _NUM_ARGS(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1)
#define EXPAND(X)       X
#define FIRSTARG(X, ...)    (X)
#define RESTARGS(X, ...)    (__VA_ARGS__)
#define FOREACH(MACRO, LIST)    FOREACH_(NUM_ARGS LIST, MACRO, LIST)
#define FOREACH_(N, M, LIST)    FOREACH__(N, M, LIST)
#define FOREACH__(N, M, LIST)   FOREACH_##N(M, LIST)

// try define more if you need.
#define FOREACH_1(M, LIST)  M LIST
#define FOREACH_2(M, LIST)  EXPAND(M FIRSTARG LIST) FOREACH_1(M, RESTARGS LIST)
#define FOREACH_3(M, LIST)  EXPAND(M FIRSTARG LIST) FOREACH_2(M, RESTARGS LIST)
#define FOREACH_4(M, LIST)  EXPAND(M FIRSTARG LIST) FOREACH_3(M, RESTARGS LIST)
#define FOREACH_5(M, LIST)  EXPAND(M FIRSTARG LIST) FOREACH_4(M, RESTARGS LIST)
#define FOREACH_6(M, LIST)  EXPAND(M FIRSTARG LIST) FOREACH_5(M, RESTARGS LIST)
#define FOREACH_7(M, LIST)  EXPAND(M FIRSTARG LIST) FOREACH_6(M, RESTARGS LIST)

#define __STRINGIFY_ALL(...) FOREACH(__STRINGIFY, (__VA_ARGS__))

#endif	/* MARCO_LIST_H */
