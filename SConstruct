import os

env = Environment(CXX='g++', CCFLAGS='-std=c++11')  

env.Append(CPPPATH=['.'])  

sources = Glob('src/*.cpp')
tests = Glob('test/*.cpp')
target_dir = 'bin'  
  
if not os.path.exists(target_dir):  
    os.makedirs(target_dir)  

for test in tests:  
    target = os.path.join(target_dir, os.path.splitext(test.name)[0])  
    env.Program(target=target, source=sources+[test])