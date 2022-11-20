# Building LUA versioned, local, luarocks

```sh
VV=5.4.4
T=/home/mike/local
V=5.4
wget http://www.lua.org/ftp/lua-$VV.tar.gz
tar xvzf lua-$VV.tar.gz
cd lua-$VV
make clean; make linux-readline    # or linux in earlier versions
make INSTALL_TOP=$T install
mv $T/bin/lua $T/bin/lua$V
mv $T/bin/luac $T/bin/luac$V
$T/bin/lua$V -e 'print("hello, world!")'
```

## Now install luarocks to work with that

```sh
LRV=3.9.1
wget https://luarocks.org/releases/luarocks-$LRV.tar.gz
tar zxpf luarocks-$LRV.tar.gz
cd luarocks-$LRV
./configure --prefix=$T --with-lua=$T --with-lua-interpreter=lua$V
make
make install
mv $T/bin/luarocks $T/bin/luarocks$V
mv $T/bin/luarocks-admin $T/bin/luarocks-admin$V
$T/bin/luarocks$V install penlight
```

## Now to use it

in .profile

```sh
TOP=/home/mike/local
V=5.4
VVV=5_4
export LUA_PATH_$VVV="./?.lua;$TOP/share/lua/$V/?.lua;$TOP/share/lua/$V/?/init.lua;$TOP/lib/lua/$V/?.lua;$TOP/lib/lua/$V/?/init.lua"
export LUA_CPATH_$VVV="./?.so;$TOP/lib/lua/$V/?.so;$TOP/lib/lua/$V/loadall.so"
```

# now to run

```sh
luarocks5.4 install penlight
lua5.4 -e 'require("pl")'
```
