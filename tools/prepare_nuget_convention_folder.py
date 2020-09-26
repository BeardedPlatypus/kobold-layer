#!/usr/bin/python3
"""
Prepare the NuGet convention-based folder for the kobold-layer clr package.
"""
__author__ = "Maarten Tegelaers"
__copyright__ = "Copyright 2020"
__version__ = "0.1"
__maintainer__ = "Maarten Tegelaers"
__status__ = "Development"

import argparse
from pathlib import Path
import shutil


IMG_FOLDER_NAME = "images"

RELATIVE_X64_NUGET_PATH = Path("runtimes") / "win10-x64"
RELATIVE_LIB_PATH = RELATIVE_X64_NUGET_PATH / "lib" / "netcoreapp3.1"
RELATIVE_NATIVE_PATH = RELATIVE_X64_NUGET_PATH / "native"


def copy_nuget_data(repo_root: Path, nuget_target_folder: Path) -> None:
    '''
    Copy the nuget data from the repo_path/NuGet to the nuget_target_folder
    
    :param repo_root: The path to the repository root
    :type repo_root: Path
    :param nuget_target_folder: The nuget package folder path
    :type repo_root: Path
    '''
    img_folder = nuget_target_folder / Path(IMG_FOLDER_NAME)
    img_folder.mkdir()

    nuget_data_folder = repo_root / "NuGet"
    
    shutil.copy(nuget_data_folder / "icon.png", img_folder)
    shutil.copy(nuget_data_folder / "kobold-layer.nuspec", nuget_target_folder)


def prepare_folder_structure(nuget_target_folder: Path) -> None:
    '''
    Construct the expected NuGet convention-based directory at the
    specified nuget_target_folder.
    
    :param nuget_target_folder: The nuget package folder path
    :type repo_root: Path
    '''
    lib_folder = nuget_target_folder / RELATIVE_LIB_PATH
    lib_folder.mkdir(parents=True)

    native_folder = nuget_target_folder / RELATIVE_NATIVE_PATH
    native_folder.mkdir(parents=True)


def copy_native_dlls(bin_folder, nuget_target_folder: Path) -> None:
    '''
    Copy the native dlls from the bin_folder to the nuget_target_folder
    
    :param bin_folder: The path to the bin folder
    :type repo_root: Path
    :param nuget_target_folder: The nuget package folder path
    :type repo_root: Path
    '''
    # The list of dlls is currently quite small, as such we just keep it 
    # explicitly. This might need to be refactored in the future if this list
    # grows further.
    native_dlls = ["Ijwhost.dll", "libpng16.dll", "SDL2.dll", "SDL2_image.dll", "zlib1.dll"]

    for dll in native_dlls:
        dll_path = bin_folder / dll
        shutil.copy(dll_path, nuget_target_folder / RELATIVE_NATIVE_PATH)


def copy_managed_dlls(bin_folder: Path, nuget_target_folder: Path) -> None:
    '''
    Copy the managed dlls from the bin_folder to the nuget_target_folder
    
    :param bin_folder: The path to the bin folder
    :type repo_root: Path
    :param nuget_target_folder: The nuget package folder path
    :type repo_root: Path
    '''
    managed_dlls = bin_folder.glob("kobold-layer.clr.*")
    for dll_path in managed_dlls:
        shutil.copy(dll_path, nuget_target_folder / RELATIVE_LIB_PATH)


def run(repo_root: Path, nuget_target_folder: Path) -> None:
    '''
    Prepare the nuget convention-based folder from the (build) repository.

    :param repo_root: The path to the repository root
    :type repo_root: Path
    :param nuget_target_folder: The nuget package folder path
    :type repo_root: Path
    '''
    nuget_target_folder.mkdir(parents=True)
    
    copy_nuget_data(repo_root, nuget_target_folder)
    prepare_folder_structure(nuget_target_folder)

    bin_folder = repo_root / "x64" / "Release" 
    copy_native_dlls(bin_folder, nuget_target_folder)
    copy_managed_dlls(bin_folder, nuget_target_folder)


def get_args():
    """
    Parses and returns the arguments.
    """
    parser = argparse.ArgumentParser(prog="Prepare the kobold-layer convention-based NuGet folder.")
    parser.add_argument("repository_root", 
                        help="Path to the repository root from which the different paths are resolved.")
    parser.add_argument("output_folder", help="Path in which the NuGet convention based folder will be created.")

    return parser.parse_args()

if __name__ == "__main__":
    args = get_args()
    run(Path(args.repository_root), Path(args.output_folder))
