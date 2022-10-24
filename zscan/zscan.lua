local find = string.find
local byte = string.byte
local sub = string.sub
local unpack = unpack or table.unpack
local NUM, STR, SKIP = byte("nsx", 1, -1)
local inspect = require "inspect"

-- 700K lines/sec in lua 5.4
-- 2M lines/sec in luajit

function zscan(fmt, str, sep)
    local sep = sep or " "
    local offset = 1
    local result = {}
    for i = 1, #fmt do
        local s, e = find(str, sep, offset, true)
        if not s then
            if offset == #str then
                return nil, "scan past end"
            end
            s, e = #str, #str
        end
        local ty = byte(fmt, i)
        if ty == SKIP then
        else
            local tok = sub(str, offset, s - 1)
            if ty == NUM then
                local n = tonumber(tok)
                if n == nil then
                    return nil, "invalid number in string"
                end
                result[#result + 1] = n
            elseif ty == STR then
                result[#result + 1] = tok
            else
                error("Invalid format in zscan")
            end
        end
        offset = e + 1
    end
    return unpack(result)
end

function test1()
    local x, y, z = zscan("snxn", "foo,18,33,5.0", ",")
    assert(x == "foo" and y == 18 and z == 5.0, "test1")
end

function test2()
    for line in io.lines("/home/mike/tmp/2019.csv") do
        local sta, dat, typ = zscan("xnsn", line, ',')
    end
end

function test3()
    local r = {}
    for line in io.lines("/home/mike/tmp/2019.csv") do
        local typ, val = zscan("xxsn", line, ',')
        if typ then
            r[typ] = (r[typ] or 0) + val
        end
    end
    print(inspect(r))
end

test3()
