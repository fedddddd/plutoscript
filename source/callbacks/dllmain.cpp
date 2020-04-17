#include "stdinc.hpp"
#include "callbacks.hpp"

DLL_EXPORT void on_initialize_context(const char* script, chaiscript::ChaiScript* chai)
{
    callbacks::set_context(chai);
    callbacks::cleanup();
    chai->add(chaiscript::fun(callbacks::add_callback_startup_game), "add_callback_startup_game");
    chai->add(chaiscript::fun(callbacks::add_callback_player_connect), "add_callback_player_connect");
    chai->add(chaiscript::fun(callbacks::add_callback_player_disconnect), "add_callback_player_disconnect");
    chai->add(chaiscript::fun(callbacks::add_callback_player_damage), "add_callback_player_damage");
    chai->add(chaiscript::fun(callbacks::add_callback_player_killed), "add_callback_player_killed");

    chai->add(chaiscript::user_type<plutoscript::Vec3>(), "Vec3");
    chai->add(chaiscript::constructor<plutoscript::Vec3()>(), "Vec3");
    chai->add(chaiscript::constructor<plutoscript::Vec3(const float[3])>(), "Vec3");
    chai->add(chaiscript::constructor<plutoscript::Vec3(const float, const float, const float)>(), "Vec3");
    chai->add(chaiscript::constructor<plutoscript::Vec3(const plutoscript::Vec3&)>(), "Vec3");
    chai->add(chaiscript::fun(&plutoscript::Vec3::x), "x");
    chai->add(chaiscript::fun(&plutoscript::Vec3::y), "y");
    chai->add(chaiscript::fun(&plutoscript::Vec3::z), "z");
    chai->add(chaiscript::fun(&plutoscript::Vec3::operator std::string), "to_string");
}

DLL_EXPORT void on_script_loaded(const char* script, chaiscript::ChaiScript* chai)
{

}

DLL_EXPORT void on_script_unloaded(const char* script, chaiscript::ChaiScript* chai)
{

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        callbacks::init();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
