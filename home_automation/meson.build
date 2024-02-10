project('home_automation','c', 'cpp')

project_description = 'Home Automation Project from Test Driven Development for Embedded C by James W. Grenning'

include_dir = include_directories('include')
source_files = ['src/LightScheduler.c']

cpputest = dependency('cpputest')

source_files_fake_time_service_test =   ['test/TestRunner.cpp', 
                                        'test/FakeTimeServiceTest.cpp',
                                        'test/FakeTimeService.c',
                                        'src/LightScheduler.c']
fake_time_service_test = executable('fake_time_service_test', 
                                    include_directories: include_dir, 
                                    sources: source_files_fake_time_service_test, 
                                    dependencies: cpputest)
test('fake_time_service_test', fake_time_service_test)

source_files_light_controller_spy_test =    ['test/TestRunner.cpp', 
                                            'test/LightControllerSpyTest.cpp',
                                            'test/LightControllerSpy.c']
light_controller_spy_test = executable('light_controller_spy_test', 
                                        include_directories: include_dir, 
                                        sources: source_files_light_controller_spy_test, 
                                        dependencies: cpputest)
test('light_controller_spy_test', light_controller_spy_test)

source_files_light_scheduler_test = ['test/TestRunner.cpp', 
                                    'test/LightSchedulerTest.cpp',
                                    'src/LightScheduler.c',
                                    'test/LightControllerSpy.c',
                                    'test/FakeTimeService.c']
light_scheduler_test = executable('light_scheduler_test', 
                                    include_directories: include_dir, 
                                    sources: source_files_light_scheduler_test, 
                                    dependencies: cpputest)
test('light_scheduler_test', light_scheduler_test)