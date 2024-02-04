#include <map>
#include <ll/api/memory/Hook.h>

std::map<void*, void*> cache{};

extern "C" {
_declspec(dllexport) int DobbyHook(void* address, void* fake_func, void** out_origin_func) {
    int result = ll::memory::hook(address, fake_func, out_origin_func, ll::memory::HookPriority::Normal);
    if (result != 0) {
        return -1;
    }
    cache[address] = fake_func;
    return result;
}
_declspec(dllexport) int DobbyDestroy(void* address) {
    bool result = ll::memory::unhook(address, cache[address]);
    if (!result) {
        return -1;
    }
    cache.erase(address);
    return 0;
}
}
