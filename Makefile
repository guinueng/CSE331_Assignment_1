# 컴파일러 및 플래그 정의
CXX = g++
CXXFLAGS = -Wall -O2

# 개별 실행 파일 이름 정의
TARGETS = merge_sort heap_sort insertion_sort bubble_sort selection_sort quick_sort

# 기본 규칙: 모든 실행 파일 생성
all: $(TARGETS)

# 개별 프로그램 컴파일 규칙
merge_sort: merge_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

merge_sort.o: merge_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

heap_sort: heap_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

heap_sort.o: heap_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

insertion_sort: insertion_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

insertion_sort.o: insertion_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

bubble_sort: bubble_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

bubble_sort.o: bubble_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

selection_sort: selection_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

selection_sort.o: selection_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

quick_sort: quick_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

quick_sort.o: quick_sort.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 청소 규칙: 생성된 파일 삭제
.PHONY: clean
clean:
	rm -f $(TARGETS) *.o
