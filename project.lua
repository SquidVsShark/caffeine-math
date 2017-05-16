#!lua

--[[
  Math Project Description
]]--

table.insert(
  projects,
  {
    name     = "Math",
    kind     = "StaticLib",
    language = "C++",
    location = make.get_proj_root(),
    no_link  = true,

    src_files = {
      -- Headers
      make.get_proj_root() .. "math/**.hpp",
      make.get_proj_root() .. "math/**.h",

      -- Doc
      make.get_proj_root() .. "math/**.md",
      make.get_proj_root() .. "math/**.txt",
    },

    inc_dirs = {
      make.get_proj_root() .. "./",
    },
  }
)
