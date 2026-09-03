export module Functions;
#ifdef TEST_NEW_INTERFACE
    export import :NewInterface;
#else
    export import :Interface;
#endif
export import :QueryFunctions;
