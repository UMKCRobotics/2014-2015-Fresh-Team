import subprocess
import os
import sys

#add debug and release builds
AddOption('--d',action='store_true',help='build a debug build',default=False)
AddOption('--r',action='store_true',help='build a release build',default=False)
AddOption('--g',action='store_true',help='fetch newest from git and build that',default=False)
AddOption('--ocv',action='store_true',help='build with opencv',default=False)

if GetOption('g'):
	subprocess.check_call(['git','fetch'])
	subprocess.check_call(['git','submodule','foreach','git','fetch'])


##SETTING UP COLORS
colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

#If the output is not a terminal, remove the colors
if not sys.stdout.isatty():
   for key, value in colors.iteritems():
      colors[key] = ''

compile_source_message = '%sCompiling %s \t\t\t ==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

compile_shared_source_message = '%sCompiling shared %s \t==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

link_program_message = '%sLinking Program %s \t\t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_library_message = '%sLinking Static Library %s \t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

ranlib_library_message = '%sRanlib Library %s \t\t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_shared_library_message = '%sLinking Shared Library %s \t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

java_library_message = '%sCreating Java Archive %s \t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

env = Environment(
  CXXCOMSTR = compile_source_message,
  CCCOMSTR = compile_source_message,
  SHCCCOMSTR = compile_shared_source_message,
  SHCXXCOMSTR = compile_shared_source_message,
  ARCOMSTR = link_library_message,
  RANLIBCOMSTR = ranlib_library_message,
  SHLINKCOMSTR = link_shared_library_message,
  LINKCOMSTR = link_program_message,
  JARCOMSTR = java_library_message,
  JAVACCOMSTR = compile_source_message
)
##END COLORIZER
bins = "bins/"

class ProgramBuilder:
	def __init__(self, name, src_dir,env):
		self.name = name
		self.src_dir = src_dir
		self.object_creator = ObjectCreator(src_dir)
		self.env = env
	def build(self):
		self.build_link([])
	def build_link(self,libs):
		print(" I am " + self.name + " " + str(libs))
		self.env.Program(self.name,self.object_creator.get_objects(),LIBS=libs,LIBPATH=bins)
class LibraryBuilder:
	def __init__(self,name,src_dir,env):
		self.name = name
		self.src_dir =src_dir
		self.object_creator = ObjectCreator(src_dir)
		self.env = env
	def build(self):
		self.env.Append(CPPPATH = ['../'+self.src_dir])
		self.env.Library(self.name,self.object_creator.get_objects())


class ObjectCreator:
	build = "build/"
	def __init__(self,src_dir):
		self.src_dir = src_dir
		self.build_dir = ObjectCreator.build + src_dir
	
	def get_objects(self):
		return self.get_objects_alt_scons("SConscript")

	def get_objects_alt_scons(self,scons_file):
		self._copy_to_build_dir()
		return SConscript(self.build_dir+scons_file,exports='env')

	def _copy_to_build_dir(self):
		def make_build_dir(dir):
			subprocess.check_call(["mkdir","--parents",dir])
		def copyanytree(src, dst):
			subprocess.check_call(['rsync','-i','-r',src,dst])
		make_build_dir(self.build_dir)
		copyanytree(self.src_dir ,self.build_dir)



#Sets up an environment object

flags = "-Wall -std=c++11"
#set up some differences between debug and release
if GetOption('d'):
	flags += "-g"
if GetOption('r'):
	flags += "-O3"
env.Append(CCFLAGS=flags)




framework = LibraryBuilder(bins+'framework',"lib/2014-2015-Framework/src/",env)
program = ProgramBuilder('robot_program','src/',env)

OPENCV_FORMATTED_LIBS = []
if GetOption('ocv'):
	#incoming hacky stuff to make openCV link
	OPENCV_FLAGS=subprocess.check_output(['pkg-config','--cflags','opencv'])
	OPENCV_LIBS=subprocess.check_output(['pkg-config','--libs-only-l','opencv'])
	OPENCV_LIBPATH=subprocess.check_output(['pkg-config','--libs-only-L','opencv'])
	env.Append(CCFLAGS=OPENCV_FLAGS)
	env.Append(LIBPATH=OPENCV_FLAGS)

	#this is a mess but it needs to be this way because i haev no better way for
	#string manipulation
	OPENCV_FORMATTED_LIBS = map(lambda a:  a[2:],OPENCV_LIBS.split(" ")[:-2]) + ['tesseract']
	#openCV hacky linking over

if GetOption("clean"):
	subprocess.check_call(['rm','-rf',bins])
	subprocess.check_call(['rm','-rf',"build/"])

if not GetOption("clean"):
	print('Building PROGRAM...')
	program.build()

