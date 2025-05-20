MicroProfiler 
====

# Want to locate the bottlenecks of your app right when it suffers them?

MicroProfiler offers unique ability to perform analysis and deliver it in real-time. You will not have to endlessly re-run your application to gather statistics for use cases your are interested in - you will simply see performance profile as you go. Like in the video below:

[![](https://raw.githubusercontent.com/tyoma/micro-profiler/master/content/micro-profiler_at_work.jpg)](https://www.youtube.com/embed/GZDVWJ-7Jc0?mute=1&autoplay=1)

# Wish to keep it useful while profiling?

MicroProfiler grounds on the idea that the application being profiled must remain usable, that is its performance must not degrade much. Comparison is worth million words:

![](https://raw.githubusercontent.com/tyoma/micro-profiler/master/content/profiled-7-zip-performance.png)

and

![](https://raw.githubusercontent.com/tyoma/micro-profiler/master/content/relative-profilers-performance.png)

# Prefer Swiss Army knives over machine guns?

MicroProfiler comes with installer that is smaller than 1MB, but is packed with tools you need to go:

*   Call tracer/analyzer - attaches to the process being profiled;
*   Frontend UI - displays overall function statistics with ability to sort and drill down to parent/children calls right in the runtime;
*   VisualStudio extension that includes frontend UI and allows you to switch profiling support for a project in just a single click.

MicroProfiler will not clog your hard drive with unnecessary raw data, while other profilers may store tens of gigabytes of garbage.

It has no dependencies, therefore, you can profile on a clean machine - just the symbol files (.pdb) on Windows and symbol names debug-info on Linux for the binary images being profiled are required.

Good news for folks maintaining legacy software: MicroProfiler runs on Microsoft Windows XP!



# Usage Guidelines

VisualStudio integration makes it pretty simple to start using MicroProfiler. Just follow these steps:

1. Right-click the project your want to profile in the solution tree and check 'Enable Profiling'. Please note, that this will force the environment to rebuild your project;
2. Build the project;
3. Run the project;
4. Profiler frontend will show-up automatically inside the Visual Studio instance you used to run the project or in a standalone mode (if standalone version is installed).

You may want to set the scope you wish to profile. In order to do this uncheck the 'Enable Profiling' menu item and add manually a pair of command line options to C/C++ compiler ```/GH /Gh``` for .cpp files of interest.

To profile a static library you may follow the similar steps: enable and then disable profiling on the image (dll/exe) project containing the library and manually add ```/GH /Gh``` for the library of interest.

To remove the instrumentation and profiling support click 'Remove Profiling Support' in the context menu for the project.

## Manual Configuration for a Profiled Build

1. (Linux) Build the application with ```-finstrument-functions``` flag on. Link with ```micro-profiler_<platform>```. The shared objects are located in MicroProfiler's installation directory;
2. (Windows, MSVC) Build the application with ```/GH /Gh``` flags on. Link with ```micro-profiler_<platform>.lib```;

## Windows Services Profiling

In order to profile Windows Service or other application running with credentials different than interactive user you may need to manually setup MicroProfiler. Follow these steps to do so:

1. Make sure you have profiler's directory in PATH environment variable for System;
2. Add another system environment variable: ```MICROPROFILERFRONTEND="sockets|127.0.0.1:6100"```. Port number (#6100 by default) is autoconfigured on Visual Studio startup with MicroProfiler extension enabled. If you're running standalone version - the first frontend application instance will have port configured to #6100, following runs will increment it;
3. Make sure you've compiled your program for profiling (see above);
4. Run the application.

## Remote/Linux Profiling

The steps are much like the ones above.

1. Copy profiler's collector ```[lib]micro-profiler_<platform>.{dll|so}``` to the directory next to the executable / dynamic library you're profiling. You may need to chmod the binaries so that they are executable;
2. (Linux) You'll may need to add current directory ('.') to the LD_LIBRARY_PATH using this command: ```export LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH}```. Sometimes, the profiled application or a shared object may not link the profiler's hook functions resulting in a missing profiler statistics. To remedy this, please use 'preload trick' - run your executable with an LD_PRELOAD: ```LD_PRELOAD=<path_to_profiler.so> <your_app_executable>```;
3. Set the frontend's host variable: ```export MICROPROFILERFRONTEND="sockets|<frontend_machine_ip>:6100"```;
4. Run the application.

