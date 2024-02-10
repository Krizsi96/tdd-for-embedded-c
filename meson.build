project('hello','c', 'cpp')

project_description = 'A simple hello world program'

include_dir = include_directories('include')
source_files = ['src/hello.c', 'src/main.c']
test_files = ['test/hello_test.cpp']

cpputest = dependency('cpputest')

executable('hello', sources: source_files, include_directories: include_dir)

executable('hello_test', sources: test_files, dependencies: cpputest)