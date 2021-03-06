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

def find_trx_files(src_path: Path) -> Sequence:
    """
    Find the coverage files within the specified src_path.

    Parameters:
        src_path (Path): The path in which to look for the .coverage files.
    
    Returns:
        (Sequence) The set of .coverage files within the specified folder.
    """
    return Path(src_path).glob("**/*.trx")


def copy_files_to_cwd(coverage_files: Sequence, suffix: str) -> None:
    """
    Copy the Sequence of coverage files to the current working 
    directory as coverage_<n>.coverage.

    Parameters:
        coverage_files (Sequence): Sequence of Paths to copy to the working directory
    """
    i = 0
    new_coverage_name_template = "coverage_{}{}"

    for cov_path in coverage_files:
        new_name = new_coverage_name_template.format(i, suffix)
        goal_path = Path(new_name)

        shutil.copy(str(cov_path), str(goal_path))

        i += 1


def convert_coverage_to_xml(code_coverage_exe: Path,
                            coverage_path: Path) -> None:
    """
    Convert the specified coverage_path to xml, and return the newly 
    generated Path.

    Parameters:
        coverage_path (Path): .coverage file to convert located in the current folder
        output_path (Path): Path to the output .xml file to create. 

    Remarks:
        If a coverage_path is provided other than the current working directory,
        the behaviour is undefined.
    """
    output_file_path = coverage_path.with_suffix(".xml")
    coverage_convert_cmd = '"{}" analyze /output:"{}" "{}"'.format(str(code_coverage_exe),
                                                                   output_file_path.name, 
                                                                   coverage_path.name)
    print("##[debug] coverage command:\n  {}".format(coverage_convert_cmd))

    encoding = "utf-8"
    p = subprocess.run(coverage_convert_cmd, 
                       shell=True, 
                       encoding=encoding,
                       stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE)

    print("##[debug] stdout:")
    print("##[debug] {}\n".format(str(p.stdout)))

    print("##[debug] stderr:")
    print("##[debug] {}\n".format(str(p.stderr)))


def run(coverage_dir: Path) -> None:
    """
    Convert the .coverage files within coverage_dir to .xml files.

    Parameters:
        coverage_dir (Path): the root directory in which to find the .coverage
                             files.
    """
    coverage_exe = get_coverage_exe_path()

    print("##[debug] " + str(coverage_dir))
    src_coverage_files = find_coverage_files(coverage_dir)
    copy_files_to_cwd(src_coverage_files, ".coverage")

    src_trx_files = find_trx_files(coverage_dir)
    copy_files_to_cwd(src_trx_files, ".trx")

    cwd_coverage_files = find_coverage_files(".")

    print("##[debug] src coverage files:")
    for coverage_path in cwd_coverage_files:
        print(f"##[Debug] {str(coverage_path)}")
        convert_coverage_to_xml(coverage_exe, coverage_path)


def parse_arguments():
    """
    Parse the arguments provided to this script.
    """
    parser = argparse.ArgumentParser("Convert .coverage to .xml.")
    parser.add_argument("coverage_folder", help="The folder containing the coverage files.")
    return parser.parse_args()


if __name__ == "__main__":
    args = parse_arguments()

    coverage_dir = Path(args.coverage_folder)
    run(coverage_dir)