format_output_spy_source = files('FormatOutputSpy.c')

format_output_spy_test = executable('format_output_spy_test',
                                    include_directories: include_dir,
                                    sources: [format_output_spy_source, test_runner, utils_source, 'FormatOutputSpyTest.cpp'],
                                    dependencies: cpputest)
test('format_output_spy_test', format_output_spy_test)