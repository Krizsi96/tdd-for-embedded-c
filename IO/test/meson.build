test_runner = files('TestRunner.cpp')

mock_include = include_directories('mocks')
subdir('mocks')

flash_test = executable(
    'flash_test', 
    include_directories: [include_dir, mock_include],
    sources: [test_runner, mock_io_source, fake_micro_time_source, flash_source, 'FlashTest.cpp'],
    dependencies: cpputest
)

test('flash_test', flash_test)