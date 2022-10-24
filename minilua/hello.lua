local x = 17
local y = 3
io.stdout:write(x + y)
io.stdout:write("Hello, World!\n")

function print(x)
    io.stdout:write(x)
    io.stdout:write("\n")
end

while true do
    line = io.stdin:read("*l")
    fcn = loadstring(line, "stdin")
    res = fcn()
    if res ~= nil then print(res) end
end
