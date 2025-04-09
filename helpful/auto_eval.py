import sys
import subprocess
import time
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
                # 프로세스 시작 시간 기록
                start_time = time.time()
                
                # Popen을 사용해 비동기 실행
                proc = subprocess.Popen(
                    [str(elf_path)],
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    text=True
                )
                
                # 주기적으로 상태 체크 (무한 대기 허용)
                while True:
                    if proc.poll() is not None:  # 프로세스 종료 확인
                        break
                    elapsed_time = time.time() - start_time
                    print(f"Run {i}: Running for {int(elapsed_time // 60)} minutes...")
                    time.sleep(30)  # 30초마다 상태 확인
                    
                # 프로세스 출력 읽기
                output, _ = proc.communicate()
                f.write(output)
                
                if proc.returncode != 0:
                    f.write(f"\nProcess exited with code {proc.returncode}")
                    
                print(f"Run {i} completed -> {output_file}")
                
        except Exception as e:
            print(f"Error in run {i}: {str(e)}")

if __name__ == "__main__":
    run_elf_multiple_times()
