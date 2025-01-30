#pragma once 

#define ZZ_CAT_(x,y) x ## y  
#define ZH_CAT(x,y) ZZ_CAT_(x,y)  
#define ZZ_STR_(x) #x  
#define ZH_STR(x) ZZ_STR_(x)  
#define ZH_WSTR(x) ZH_CAT(L,ZH_STR(x))

#define ZH_GET_VARIABLE_NAME(Var) (#Var)