local function count_file_lines(fpath)
    local count = 0
    for line in io.lines(fpath) do
        count = count + 1
    end
    return count
end

local function count_dir(dirpath)
    local files = dir(dirpath)
    local total = 0
    for i, fname in ipairs(files) do
        if string.match(fname, ".%.[ch]$") then
            local fpath = dirpath .. "/" .. fname
            total = total + count_file_lines(fpath)
        end
    end
    return total
end

local function isdir(dr)
    local x, err = io.open(dr):read(1)
    return x == nil and string.match(err, "directory")
end

function count_all_dirs(dirpath)
    local dirs = dir(dirpath)
    local total = 0
    for i, dr in ipairs(dirs) do
        if isdir(dr) and dr ~= "." and dr ~= ".." then
            local nlines = count_dir(dr)
            print(dr .. " " .. nlines)
            total = total + count_dir(dr)
        end
    end
end

-- print(count_file_lines("ldump.c"))
count_all_dirs(".")
-- print("TOTAL:", total)
