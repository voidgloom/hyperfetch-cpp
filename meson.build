project('hyperfetch', 'cpp')
if host_machine.system() == 'windows'
    dependencies = []
    add_global_arguments('-lws2_32', language : 'c')
else
    dependencies = []
endif

incdir = include_directories('src')

main_target_name = 'hyperfetch'
sources = ['src/main.cpp', 'src/module.cpp', 'src/kernel.cpp', 'src/shell.cpp', 'src/model.cpp', 'src/title.cpp', 'src/utils/osrelease.cpp', 'src/distro.cpp', 'src/ascii.cpp', 'src/uptime.cpp',
           'src/wm.cpp', 'src/package.cpp', 'src/utils/cpuid.cpp', 'src/cpu.cpp', 'src/ram.cpp', 'src/utils/trim.cpp', 'src/disk.cpp', 'src/utils/bar.cpp', 'src/de.cpp', 'src/osinfo.cpp', 'src/gpu.cpp',
           'src/terminal.cpp', 'src/utils/fs.cpp', 'src/utils/utils.cpp']
executable(main_target_name, sources, dependencies: dependencies, include_directories: incdir)

