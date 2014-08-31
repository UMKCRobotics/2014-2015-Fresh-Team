
#add debug and release builds
AddOption('--d',action='store_true',help='build a debug build',default=False)
AddOption('--r',action='store_true',help='build a release build',default=False)


#Sets up an environment object
env = Environment()


#the default flags for all builds
flags = "-Wall "
#set up some differences between debug and release
if GetOption('d'):
	flags += "-g"
if GetOption('r'):
	flags += "-O3"
env.Append(CCFLAGS=flags)

#setting the output dir to be build instead, 
#also making it so it doesn't copy the files
env.VariantDir('build/','src/',duplicate=0) 


#files for the framework library
framework_files = "./2014-2015-Framework/lib/*.cpp"

#build the library 
env.Library('framework',Glob(framework_files))
#files for the specific build.
#NOTE: in order to use a different directory for the build ouput you 
#actually have to specify the files are from there
build_files = "./build/*.cpp"
files = Glob(build_files)

#add the cpp path
env.Append(CPPPATH = ['./2014-2015-Framework/lib'])

#actually build the program
env.Program('robot_program',files,libs=['framework'])
