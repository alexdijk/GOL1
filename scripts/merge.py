#!/usr/bin/env python3
#
# from: https://gist.github.com/FRex/41b41708daf87d22cf3557766b9dff9b
#
# v20191228
# up2date for imgui vx and imgui-sfml vy
# added libImGui-SFML.a copy to out
# updated stb_xx names to current imstb-xx
#
import os
import os.path
import sys
import shutil

def printf(fmt, *args):
    print(fmt.format(*args), end='')

REPOS = [
    'https://github.com/eliasdaler/imgui-sfml',
    'https://github.com/ocornut/imgui',
    'https://github.com/sfml/sfml'
]

FILES = [
    'imgui-sfml/imconfig-SFML.h',
    'imgui-sfml/imgui-SFML.h',
    'imgui-sfml/imgui-SFML.cpp',
    'imgui/imgui.cpp',
    'imgui/imgui.h',
    'imgui/imgui_demo.cpp',
    'imgui/imgui_draw.cpp',
    'imgui/imgui_internal.h',
    'imgui/imconfig.h',
    'imgui/imstb_rectpack.h',
    'imgui/imstb_textedit.h',
    'imgui/imstb_truetype.h',
]

def ensure_repos():
    for repo in REPOS:
        parts = repo.split('/')
        if not os.path.exists(parts[-1]):
            printf("Cloning {}\n", repo)
            os.system('git clone ' + repo)
            printf("\n")
        else:
            printf("{} already exists, skipping {}\n", parts[-1], repo)

def check_files():
    printf("\nChecking files\n")
    all_files_ok = True
    for file in FILES:
        ok = os.path.exists(file)
        all_files_ok = all_files_ok and ok
        printf("Checking {} exists: {}\n", file, ['no', 'yes'][ok])

    printf("\nAll files OK: {}\n", ['no', 'yes'][all_files_ok])
    return all_files_ok

def concat_files(contents, goalfile, sourcefile):
    goaltext = contents[goalfile]
    sourcestart = '\n//SCRIPT: Concat file {} start\n'.format(sourcefile)
    sourceend = '\n//SCRIPT: Concat file {} end\n'.format(sourcefile)
    sourcetext = sourcestart + contents[sourcefile] + sourceend
    del contents[sourcefile]
    contents[goalfile] = goaltext + sourcetext

def rename_file(contents, file, newname):
    contents[newname] = contents[file]
    del contents[file]

def inline_header(contents, file, header):
    comb = '#include "{}"'.format(header.split('/')[-1])
    pre = '//SCRIPT: Inline {} start\n'.format(header)
    text = contents[header]
    post = '\n//SCRIPT: Inline {} end\n'.format(header)
    contents[file] = contents[file].replace(comb, pre + text + post, 1)
    contents[file] = contents[file].replace(comb, '//SCRIPT: ' + comb)



def create_files():
    contents = {}
    for file in FILES:
        with open(file) as f:
            contents[file] = f.read()

    #prepare the single cpp of imgui and imgui sfml
    imguisfmlcpp = 'imgui-sfml/imgui-SFML.cpp'
    contents[imguisfmlcpp] = contents[imguisfmlcpp].replace('#include <imgui.h>', '//#include <imgui.h>')
    contents[imguisfmlcpp] = contents[imguisfmlcpp].replace('#include "imgui-SFML.h"', '//#include "imgui-SFML.h"')
    concat_files(contents, 'imgui/imgui.cpp', 'imgui/imgui_demo.cpp')
    concat_files(contents, 'imgui/imgui.cpp', 'imgui/imgui_draw.cpp')
    concat_files(contents, 'imgui/imgui.cpp', 'imgui-sfml/imgui-SFML.cpp')

    #patch stb
    inline_header(contents, 'imgui/imgui_internal.h', 'imgui/imstb_textedit.h')
    for file in [x for x in FILES if 'stb_' in x]:
        inline_header(contents, 'imgui/imgui.cpp', file)

    for file in [x for x in FILES if 'stb_' in x]:
        del contents[file]

    #merge sfml imgui files into imgui files
    concat_files(contents, 'imgui/imconfig.h', 'imgui-sfml/imconfig-SFML.h')
    concat_files(contents, 'imgui/imgui.h', 'imgui-sfml/imgui-SFML.h')

    #patch and concat other headers around
    inline_header(contents, 'imgui/imgui.cpp', 'imgui/imgui.h')
    inline_header(contents, 'imgui/imgui.cpp', 'imgui/imgui_internal.h')
    inline_header(contents, 'imgui/imgui.cpp', 'imgui/imconfig.h')
    inline_header(contents, 'imgui/imgui.h', 'imgui/imconfig.h')
    #concat_files(contents, 'imgui/imgui.h', 'imgui/imgui_internal.h')
    if 'imgui/imgui_internal.h' in contents:
        del contents['imgui/imgui_internal.h']

    del contents['imgui/imconfig.h']

    #rename to be distinct from the original
    rename_file(contents, 'imgui/imgui.h', 'single_imgui.hpp')
    rename_file(contents, 'imgui/imgui.cpp', 'single_imgui.cpp')

    contents['single_imgui.hpp'] = '//DO NOT EDIT: THIS FILE IS MACHINE GENRATED\n' + contents['single_imgui.hpp']
    contents['single_imgui.cpp'] = '//DO NOT EDIT: THIS FILE IS MACHINE GENRATED\n' + contents['single_imgui.cpp']

    #write the new files out
    printf("Writing out into dir 'out': {}\n", ", ".join(contents.keys()))

    os.mkdir('out')
    for i, v in contents.items():
        with open('out/' + i.split('/')[-1], 'w', newline='\n') as f:
            f.write(v)

def copy_files():
    if os.path.isfile('imgui-sfml/libImGui-SFML.a'):
        shutil.copy2('imgui-sfml/libImGui-SFML.a', 'out/libImGui-SFML.a')
    else:
        printf("Build the imgui-sfml library first!\n")

def main():
    ensure_repos()
    if not check_files():
        printf("Some files were not OK, quitting\n")
        sys.exit(1)

    create_files()
    copy_files()

if __name__ == '__main__':
    main()
