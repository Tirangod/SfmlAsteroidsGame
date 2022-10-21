from pathlib import Path
import os

def traverse(path):
    path_list = []

    for dir in Path(path).iterdir():
        if dir.is_dir():
            path_list.extend(traverse(dir))
        else:
            path_list.append(str(dir))

    return path_list

def concat(ls):
    str = ""
    for el in ls:
        str += el + " "
        print(el)
    
    return str


import toml

t = toml.load("make.config.toml")

cc = t["Build"]["cc"]
src = t["Build"]["src"]
mainfile = t["Build"]["mainfile"]
outfile = t["Build"]["outfile"]
flags = t["Build"]["flags"]
modules = t["Build"]["modules"]

exec = cc + " -O3 " + concat(traverse(src)) + " " + mainfile + " -o " + outfile + " " + ' '.join(flags) + " " + ' '.join(modules)
print(exec)
os.system(exec)

if Path(outfile).exists():
    os.system(outfile)