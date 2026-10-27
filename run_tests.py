from pathlib import Path
import os, subprocess, tempfile
root=Path(__file__).resolve().parents[1]
with tempfile.TemporaryDirectory() as temp:
    executable=Path(temp)/('tests.exe' if os.name=='nt' else 'tests')
    subprocess.run([os.environ.get('CXX','g++'),'-std=c++17','-Wall','-Wextra','-Werror','-pedantic','-I',str(root),str(root/'tests/test_logic.cpp'),'-o',str(executable)],check=True)
    subprocess.run([str(executable)],check=True)
