local ldes = require "ldes"

local passwd = "toor"
local salt = "a8"

local hash = ldes.crypt(passwd, salt)

print(hash) -- a8kQIzA4687P.

