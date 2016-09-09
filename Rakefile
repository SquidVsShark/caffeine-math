
task :ci do |t, args|

  files = [
    "test/unit_tests/main.cpp",
    "test/unit_tests/vec2.cpp",
    "test/unit_tests/vec3.cpp",
    "test/unit_tests/vec4.cpp",
    
    "test/unit_tests/vec2_sse.cpp",
    "test/unit_tests/vec3_sse.cpp",
    "test/unit_tests/vec4_sse.cpp",
    
    "test/unit_tests/quat.cpp",
  ]

  sh "g++-5 -std=c++11 -Wall #{files.join(' ')} -I ./ -I ./test/ -o unit_test && ./unit_test"

end
