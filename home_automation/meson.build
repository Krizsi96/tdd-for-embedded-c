project('home_automation','c', 'cpp')

project_description = 'Home Automation Project from Test Driven Development for Embedded C by James W. Grenning'

include_dir = include_directories('include')
source_files = ['src/LightScheduler.c']

cpputest = dependency('cpputest')

source_files = ['src/LightScheduler.c']
test_double_file = ['test/FakeTimeService.c',
                    'test/LightControllerSpy.c']
test_runner_file =   ['test/TestRunner.cpp']

fake_time_service_test = executable('fake_time_service_test', 
                                    include_directories: include_dir, 
                                    sources: [source_files, test_double_file, test_runner_file, 'test/FakeTimeServiceTest.cpp'], 
                                    dependencies: cpputest)
test('fake_time_service_test', fake_time_service_test)

light_controller_spy_test = executable('light_controller_spy_test', 
                                        include_directories: include_dir, 
                                        sources: [source_files, test_double_file, test_runner_file, 'test/LightControllerSpyTest.cpp'], 
                                        dependencies: cpputest)
test('light_controller_spy_test', light_controller_spy_test)

light_scheduler_test = executable('light_scheduler_test', 
                                    include_directories: include_dir, 
                                    sources: [source_files, test_double_file, test_runner_file, 'test/LightSchedulerTest.cpp'], 
                                    dependencies: cpputest)
test('light_scheduler_test', light_scheduler_test)