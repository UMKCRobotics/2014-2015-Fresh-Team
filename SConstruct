import subprocess

#add debug and release builds
AddOption('--d',action='store_true',help='build a debug build',default=False)
AddOption('--r',action='store_true',help='build a release build',default=False)


#Sets up an environment object
env = Environment()

#define some directories and common files
bins = "bins/"
srcs = "src/"
libs = "lib/"
build = "build/"
arduino = "build/program/Arduino/"
SConscript_name = "SConscript"
framework_name = "2014-2015-Framework/"

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
#library_build_dir = build + 'framework/'
#env.VariantDir(library_build_dir,libs+framework_name+srcs)

#program_build_dir = build + 'program/'
#env.VariantDir(program_build_dir,'src') 


#add the cpp path
env.Append(CPPPATH = ['../framework/'])


#i can't find a better way to do this
def copyanything(src, dst):
	subprocess.check_call(['rsync','-r',src,dst])
	
copyanything(srcs,build+"program/")
copyanything(libs+framework_name+srcs,build+"framework/")

#build the library
library_objects = SConscript(build+'framework/'+SConscript_name, exports = 'env')
env.Library(bins + 'framework',library_objects)

#actually build the program
program_objects = SConscript(build+'program/'+SConscript_name, exports= 'env')
env.Program(target = 'robot_program',source=program_objects,libs=[bins +'framework'],variant_dir=build+"program")
