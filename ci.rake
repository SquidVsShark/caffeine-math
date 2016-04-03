
task :ci do |t, args|

  files = [
    "test/unit/main.cpp",
    "test/unit/vec2.cpp",
    "test/unit/vec3.cpp",
  ]

  sh "clang++ #{files} -I ./ -o unit_test && unit_test"

end
