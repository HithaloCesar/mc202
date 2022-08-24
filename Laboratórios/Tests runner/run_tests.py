from os import listdir, path, system
from typing import Tuple, List


def test_c(
        lab_n: str,
        lab_dir: str,
        test_dir: str,
        test_n: str,
        inp: str) -> Tuple[str, str]:
    exe = path.join(".", f"\"{lab_dir}", f"lab{lab_n}.exe\"")
    out = path.join(".", f"\"{lab_dir}", test_dir, f"{test_n}-c.out\"")
    system(exe + " < " + inp + " > " + out)
    return exe, out


def test_py(
        exe: str,
        inp: str,
        out: str) -> None:
    exe = "\"" + exe.replace(".exe", ".py").replace("\"", "", 1)
    out = out.replace("-c", "-py")
    system("python " + exe + " < " + inp + " > " + out)


def perform_test(
        lab_n: str,
        lab_dir: str,
        test_dir: str,
        test_n: str,
        test_in: str) -> None:
    inp = path.join(".", f"\"{lab_dir}", test_dir, f"{test_in}\"")
    exe, out = test_c(lab_n, lab_dir, test_dir, test_n, inp)
    test_py(exe, inp, out)


def get_files(lab_n: str) -> Tuple[str, str, List[str]]:
    labs = listdir(".")
    lab_dir = [file for file in labs if file.startswith(f"Lab {lab_n}")].pop()
    test_dir = "Testes"
    test_files = listdir(f"./{lab_dir}/{test_dir}")
    in_files = [file for file in test_files if file.endswith(".in")]
    return lab_dir, test_dir, in_files


def main() -> None:
    lab_n = input("Enter lab number: ").zfill(2)
    lab_dir, test_dir, in_files =  get_files(lab_n)
    for test_n, test_in in enumerate(in_files, 1):
        test_n = str(test_n).zfill(2)
        perform_test(lab_n, lab_dir, test_dir, test_n, test_in)


if __name__ == "__main__":
    main()
