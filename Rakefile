
task :ci do |t, args|

  files = [
    "test/unit_tests/main.cpp",
    "test/unit_tests/vec2.cpp",
    "test/unit_tests/vec3.cpp",
  ]

  sh "g++ #{files.join(' ')} -I ./ -I ./test/ -std=c++14 -o unit_test && unit_test"

end
