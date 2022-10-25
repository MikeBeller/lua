#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <error.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

static int lua_dir_list(lua_State *L)
{
    struct dirent *entry;

    const char *path = luaL_checkstring(L, 1);
    DIR *dr = opendir(path);
    if (!dr)
    {
        lua_pushnil(L);
        lua_pushstring(L, "diropen");
        lua_pushinteger(L, errno);
    }

    lua_newtable(L);

    int i = 1;
    while ((entry = readdir(dr)) != NULL)
    {
        lua_pushstring(L, entry->d_name);
        lua_rawseti(L, -2, i);
        i++;
    }

    closedir(dr);

    lua_pushvalue(L, -1);
    return 1;
}

int main(int argc, char **argv)
{
    char buff[256];
    lua_State *L = lua_open();
    luaL_openlibs(L);

    lua_pushcfunction(L, lua_dir_list);
    lua_setglobal(L, "dir");

    if (argc < 2)
    {
        error(1, 0, "usage: %s <scriptpath>", argv[0]);
    }

    if (luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0))
    {
        error(1, errno, "cannot run file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
    return 0;
}
