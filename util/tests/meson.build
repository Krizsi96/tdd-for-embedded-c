test_runner = files('TestRunner.cpp')

mock_includes = include_directories('mocks')

subdir('mocks')

circular_buffer_print_test = executable('circular_buffer_print_test',
                                        include_directories: [mock_includes, include_dir],
                                        sources: [test_runner, format_output_spy_source,
                                        utils_source, circular_buffer_source,
                                        'CircularBufferPrintTest.cpp'],
                                        dependencies: cpputest)
test('circular_buffer_print_test', circular_buffer_print_test)
