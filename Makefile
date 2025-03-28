# 컴파일러 및 플래그 정의
SANFLAGS = -fsanitize=address
CXXFLAGS += -Wall -O2 -std=c++23 -g $(SANFLAGS)
LDFLAGS += $(SANFLAGS)

# LDFLAGS1 = $(LDFLAGS) + -Wl -stack_size 0x10000000

# quick_sort: LDFLAGS += -Wl,-stack_size,0x10000000 # 256MB

# quick_sort: LDFLAGS += -Wl,-z,stack-size=0x200000000

# 개별 실행 파일 이름 정의
TARGETS = merge_sort heap_sort insertion_sort bubble_sort selection_sort quick_sort auto_eval comb_sort auto_eval_adv tournament_sort

# 기본 규칙: 모든 실행 파일 생성
all: $(TARGETS)

# 개별 프로그램 컴파일 규칙
auto_eval: auto_eval.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

auto_eval.o: auto_eval.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

auto_eval_adv: auto_eval_adv.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

auto_eval_adv.o: auto_eval_adv.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

merge_sort: merge_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

merge_sort.o: merge_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

heap_sort: heap_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

heap_sort.o: heap_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

insertion_sort: insertion_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

insertion_sort.o: insertion_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

bubble_sort: bubble_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

bubble_sort.o: bubble_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

selection_sort: selection_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

selection_sort.o: selection_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

quick_sort: quick_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

quick_sort.o: quick_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

comb_sort: comb_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

comb_sort.o: comb_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

tournament_sort: tournament_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

tournament_sort.o: tournament_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 청소 규칙: 생성된 파일 삭제
.PHONY: clean
clean:
	rm -f $(TARGETS) *.o
