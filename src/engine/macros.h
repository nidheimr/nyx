#pragma once

#ifdef DEBUG_MODE
    #define RESOURCE(path) "res/" path
#else
    #define RESOURCE(path) path
#endif
