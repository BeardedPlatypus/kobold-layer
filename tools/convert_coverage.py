import argparse
from pathlib import Path
import subprocess
from typing import Sequence
import shutil


def get_coverage_exe_path() -> Path:
    """
    Get the codecoverage.exe

    Returns:
        (Path) The path to the codecoverage.exe
    """
    base_path = Path("C:\\PROGRA~2\\Microsoft Visual Studio\\2019\\Enterprise")
    return next(base_path.glob("**/codecoverage.exe"))


def find_coverage_files(src_path: Path) -> Sequence:
    """
    Find the coverage files within the specified src_path.

    Parameters:
        src_path (Path): The path in which to look for the .coverage files.
    
    Returns:
        (Sequence) The set of .coverage files within the specified folder.
    """
    return Path(src_path).glob("**/*.coverage")


def convert_coverage_to_xml(code_coverage_exe: Path,
                            coverage_path: Path) -> None:
    """
    Convert the specified coverage_path to xml, and return the newly
    generated Path.

    Parameters:
        coverage_path (Path): .coverage file to convert located in the current folder.
        output_path (Path): Path to the output .xml file to create.

    Remarks:
        If a coverage_path is provided other than the current working directory,
        the behaviour is undefined.
    """
    output_file_path = coverage_path.with_suffix(".xml")
    coverage_convert_cmd = f'"{str(code_coverage_exe)}" analyze /output:{output_file_path.name} {coverage_path.name}'
    print(f"##[debug] coverage path:\n  {coverage_convert_cmd}")

    encoding = "utf-8"
    p = subprocess.run(coverage_convert_cmd,
                       shell=True,
                       encoding=encoding,
                       stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE)

    print("##[debug] stdout:")
    print(f"##[debug] {str(p.stdout)}\n")

    print("##[debug] stderr:")
    print(f"##[debug] {str(p.stderr)}\n")


def run() -> None:
    """
    Convert the .coverage files within the current working directory to .xml files.
    """
    coverage_exe = get_coverage_exe_path()

    cwd_coverage_files = find_coverage_files(".")

    print("##[debug] Src coverage files:")
    for coverage_path in cwd_coverage_files:
        print(f"##[Debug] {str(coverage_path)}")
        convert_coverage_to_xml(coverage_exe, coverage_path)


if __name__ == "__main__":
    run()