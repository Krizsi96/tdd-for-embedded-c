project('home_automation','c', 'cpp')

project_description = 'Home Automation Project from Test Driven Development for Embedded C by James W. Grenning'

include_dir = include_directories('include')

cpputest = dependency('cpputest')

subdir('src')
subdir('test')

fake_time_service_test = executable('fake_time_service_test', 
                                    include_directories: include_dir, 
                                    sources: [source_files, test_doubles, test_runner, fake_time_service_tests], 
                                    dependencies: cpputest)
test('fake_time_service_test', fake_time_service_test)

light_controller_spy_test = executable('light_controller_spy_test', 
                                        include_directories: include_dir, 
                                        sources: [source_files, test_doubles, test_runner, light_controller_spy_tests], 
                                        dependencies: cpputest)
test('light_controller_spy_test', light_controller_spy_test)

light_scheduler_test = executable('light_scheduler_test', 
                                    include_directories: include_dir, 
                                    sources: [source_files, test_doubles, test_runner, light_scheduler_tests], 
                                    dependencies: cpputest)
test('light_scheduler_test', light_scheduler_test)