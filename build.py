# build.py
#
# Copyright (c) 2013 Ahmed M. Hussein (amhussein4@gmail.com)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import os.path
import sys

sources = ["Random.c","BLAS.c","Matrix.c","Regression.c","Image.c","Complex.c"]

compiler = "gcc"
include_dirs = ["include","exclude"]
src_dir = "src"
include_arg = ""
for idir in include_dirs:
	include_arg = include_arg + "-I" + idir + " "


output = "libcascore.so"

object_extension = ".o"

print_only = False

def NeedToCompile(sourcefile,objectfile):
	# check if object file exists
	if(os.path.isfile(objectfile)):
		# check its time signature
		sourcetime = os.path.getmtime(sourcefile)
		objecttime = os.path.getmtime(objectfile)
		# leave a tolerance of 10 seconds to avoid any inaccurate time reporting
		if(sourcetime < (objecttime - 10)):
			return False
	return True

def Execute(command):
	if(print_only):
		print(command)
	else:
		print(command)
		os.system(command)

def GetObjectName(sourcename):
	objectname = sourcename[0:sourcename.rfind('.')] + object_extension
	return objectname

def CompileSource(sourcefile,debug):
	if(NeedToCompile(sourcefile,GetObjectName(sourcefile))):
		if(debug):	compile_string = compiler + " -c -fPIC -Wall -Wextra -pedantic " + include_arg + " " + sourcefile
		else:		compile_string = compiler + " -c -fPIC -Wall -Wextra -pedantic -O2 " + include_arg + " " + sourcefile
		Execute(compile_string)
		return True
	return False

def CompileSources(debug):
	for source in sources:
		CompileSource(src_dir + "/" + source,debug)

def Compile(debug):
	CompileSources(debug)

def Link():
	# delete any existing libraries before creating a new one
	remove_command = "rm -f " + output
	Execute(remove_command)
	#link_command = "ar -cvq " + output + " "
	link_command = compiler + " "
	for source in sources:
		link_command = link_command + GetObjectName(source) + " "
	link_command = link_command + "-shared -o " + output
	Execute(link_command)

clean = False
debug = False

for i in range(1,len(sys.argv)):
	if(sys.argv[i] == "clean"):
		clean = True
	elif(sys.argv[i] == "debug"):
		debug = True

if(clean):
	Execute("rm *.o")
	Execute("rm " + output)

Compile(debug)
Link()


