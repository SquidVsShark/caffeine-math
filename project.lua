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
      make.add_headers(make.get_proj_root()),
      make.add_doc(make.get_proj_root()),
    },

    inc_dirs = {
      make.get_proj_root() .. "./",
    },
  }
)
