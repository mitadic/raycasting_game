

import subprocess
import pytest

OK = 0
MEMORY_LEAK = 1
INVALID_READWRITEFREE = 2
UNINITIALISED_VALUE = 3

VALGRIND_TIMEOUT = 0  # timeout caps the runtime for us, translates to 'OK'
MISSING_ERROR = 1
MANDATORY_RUNTIME_ERROR_STRING = "Error:\n"

CUB3D_PATH = "../cub3d"
CUB3DBONUS_PATH = "../cub3d_bonus"

def run_valgrind_with_binary(file_path: str):
    """
    run valgrind with the cub3d binary in a subprocess.
    Note: valgrind reports are written entirely to stderr.
    """
    try:
        result = subprocess.run(["valgrind", CUB3D_PATH, file_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=2)
        return result.stderr.decode(), result.returncode
    except subprocess.TimeoutExpired:
        return "", VALGRIND_TIMEOUT

def parse_valgrind_output(stderr_printout: str) -> int:
    """
    strcmp for indicators of significant errors in valgrind report
    """ 
    if "definitely lost" in stderr_printout:
        return MEMORY_LEAK
    if "Invalid" in stderr_printout:
        return INVALID_READWRITEFREE
    if "uninitialised value" in stderr_printout:
        return UNINITIALISED_VALUE
    return OK

def confirm_runtime_error_reported(stderr_printout: str) -> int:
    """
    Make sure 'Error:\n' is printed by cub3d when it should be
    """
    if MANDATORY_RUNTIME_ERROR_STRING in stderr_printout:
        return OK
    return MISSING_ERROR
    

def test_unexisting_file():
    stderr_printout, exit_status = run_valgrind_with_binary("gfewgf")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK

def test_map_too_small():
    stderr_printout, exit_status = run_valgrind_with_binary("toosmall.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK
    print("map_too_small: ok")

if __name__ == "__main__":
    pytest.main()
