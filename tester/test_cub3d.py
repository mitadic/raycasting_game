import os
import sys
import subprocess
import pytest

OK = 0
MEMORY_LEAK = 1
INVALID_READWRITEFREE = 2
UNINITIALISED_VALUE = 3

VALGRIND_TIMEOUT = 0  # 'timeout' caps the runtime for us, translates to 'OK'
MISSING_ERROR = 1
MANDATORY_RUNTIME_ERROR_STRING = "Error:\n"

CUB3D_PATH = "../cub3d"
CUB3DBONUS_PATH = "../cub3d_bonus"
TEST_FILES_GOOD = "test_files/good/"
TEST_FILES_BAD = "test_files/bad/"

def binary_exists():
    return os.path.isfile(CUB3D_PATH)

def run_valgrind_with_binary(file_path: str):
    """
    run valgrind with the cub3d binary in a subprocess.
    Note: valgrind reports are written entirely to stderr.
    """
    try:
        result = subprocess.run(["valgrind", CUB3D_PATH, file_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=1)
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
    Ensure that 'Error:\n' is printed by cub3d when it should be
    """
    if MANDATORY_RUNTIME_ERROR_STRING in stderr_printout:
        return OK
    return MISSING_ERROR

def test_binary_exists():
    if not binary_exists():
        sys.exit(0)
    assert binary_exists() == True
    

def test_unexisting_file():
    stderr_printout, exit_status = run_valgrind_with_binary("gfewgf")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_map_too_small():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "toosmall.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_one_char():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "1char.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_airpocket():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "airpocket.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_all_walls():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "allwalls.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_bad_filename():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "badfilename.cubs")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_bamboozle():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "bamboozle.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_empty_file():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "emptyfile.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_illegal_chars():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "illegalchars.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_illegal_chars2():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "illegalchars2.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_illegal_chars3():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "illegalchars3.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_illegal_chars4():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "illegalchars4.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_leaky():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "leaky.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_leaky2():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "leaky2.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_no_pl():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "nopl.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_player_in_wall():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "player_in_wall.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_smallest_extra_complex():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "smallest_extra_complex.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_too_many_player_symbols():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "toomanypl.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_too_many_players_plus_airpockets():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "toomanypl_airpockets.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_tricky():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "tricky.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK


def test_whitespace_newline_trails():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "whitespace_newline_trails.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_parsing_floor_over_255():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "parsing_f_over_255.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_parsing_negative_floor():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "parsing_neg_f.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

def test_parsing_illegal_b4_identifier():
    stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + "parsing_illegal_b4_identifier.cub")
    valgrind_issue = parse_valgrind_output(stderr_printout)
    assert exit_status > 0
    assert valgrind_issue == OK
    assert confirm_runtime_error_reported(stderr_printout) == OK

# def test_():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + ".cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status > 0
#     assert valgrind_issue == OK
#     assert confirm_runtime_error_reported(stderr_printout) == OK

# def test_():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + ".cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status > 0
#     assert valgrind_issue == OK
#     assert confirm_runtime_error_reported(stderr_printout) == OK

# def test_():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + ".cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status > 0
#     assert valgrind_issue == OK
#     assert confirm_runtime_error_reported(stderr_printout) == OK

# def test_():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_BAD + ".cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status > 0
#     assert valgrind_issue == OK
#     assert confirm_runtime_error_reported(stderr_printout) == OK

##############################################

# def test_tron_legit():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_GOOD + "tron.cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status == 0
#     assert valgrind_issue == OK

# def test_irrshape_legit():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_GOOD + "irrshape_validmap.cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status == 0
#     assert valgrind_issue == OK

# def test_parsing_no_newline_b4_map():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_GOOD + "parsing_no_newline_b4_map.cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status == 0
#     assert valgrind_issue == OK

# def test_parsing_space_b4_identifier():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_GOOD + "parsing_space_b4_identifier.cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status == 0
#     assert valgrind_issue == OK

# def test_parsing_tab_b4_identifier():
#     stderr_printout, exit_status = run_valgrind_with_binary(TEST_FILES_GOOD + "parsing_tab_b4_identifier.cub")
#     valgrind_issue = parse_valgrind_output(stderr_printout)
#     assert exit_status == 0
#     assert valgrind_issue == OK


if __name__ == "__main__":
    pytest.main()
