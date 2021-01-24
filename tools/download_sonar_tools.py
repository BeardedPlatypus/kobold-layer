import requests 
import zipfile
import shutil

from pathlib import Path


def download_file(url: str, save_path: Path, chunk_size=128) -> None:
    r = requests.get(url, stream=True)
    with save_path.open('wb') as fd:
        for chunk in r.iter_content(chunk_size=chunk_size):
            fd.write(chunk)


def unzip_file(zip_file_path: Path, unzip_directory: Path) -> None:
    with zipfile.ZipFile(str(zip_file_path), 'r') as zip_ref:
        zip_ref.extractall(str(unzip_directory))


def get_build_wrapper(save_dir: Path) -> None:
    url = "https://sonarcloud.io/static/cpp/build-wrapper-win-x86.zip"
    save_path = save_dir / Path("build-wrapper-win-x86.zip")

    print(save_path)
    download_file(url, save_path)
    unzip_file(save_path, save_dir)


if __name__ == "__main__":
    save_dir = Path(".") / Path(".sonar")
    save_dir.mkdir(exist_ok=True)
    print(str(save_dir))

    get_build_wrapper(save_dir)
