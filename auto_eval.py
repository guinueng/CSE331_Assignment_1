import sys
import subprocess
from pathlib import Path

def run_elf_multiple_times():
    if len(sys.argv) != 3:
        print("Usage: python elf_runner.py <elf_path> <num_runs>")
        sys.exit(1)
    
    elf_path = Path(sys.argv[1])
    num_runs = int(sys.argv[2])
    
    if not elf_path.exists():
        print(f"Error: ELF file not found at {elf_path}")
        sys.exit(1)
    
    for i in range(1, num_runs + 1):
        output_file = f"output_run_{i}.txt"
        try:
            with open(output_file, 'w') as f:
                result = subprocess.run(
                    [str(elf_path)],
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    text=True
                )
                f.write(result.stdout)
                if result.returncode != 0:
                    f.write(f"\nProcess exited with code {result.returncode}")
                print(f"Run {i} completed -> {output_file}")
        except Exception as e:
            print(f"Error in run {i}: {str(e)}")

if __name__ == "__main__":
    run_elf_multiple_times()
