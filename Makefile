SANITIZER = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
DIFFERENT_FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=81920 -Wstack-usage=81920 -pie -fPIE -Werror=vla
DEBUG_SET = -DDEBUG -DTURN_ON_CANARIES -DTURN_ON_HASH
OBJECTS = o_files/main.o o_files/writeData.o o_files/writeHtmlFile.o o_files/insDelElem.o o_files/stackPushPop.o o_files/stackInitDestroy.o o_files/stackDump.o o_files/stackAssertFunction.o o_files/stackError.o o_files/countHash.o

all: init out

out: $(OBJECTS)
	g++ $(OBJECTS) -o out $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/main.o: cpp_files/main.cpp
	g++ -c cpp_files/main.cpp -o o_files/main.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/writeData.o: cpp_files/writeData.cpp
	g++ -c cpp_files/writeData.cpp -o o_files/writeData.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/writeHtmlFile.o: cpp_files/writeHtmlFile.cpp
	g++ -c cpp_files/writeHtmlFile.cpp -o o_files/writeHtmlFile.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/insDelElem.o: cpp_files/insDelElem.cpp
	g++ -c cpp_files/insDelElem.cpp -o o_files/insDelElem.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)









o_files/stackPushPop.o: workWithStack/cpp_files/stackPushPop.cpp
	g++ -c workWithStack/cpp_files/stackPushPop.cpp -o o_files/stackPushPop.o $(DEBUG_SET) $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/stackInitDestroy.o: workWithStack/cpp_files/stackInitDestroy.cpp
	g++ -c workWithStack/cpp_files/stackInitDestroy.cpp -o o_files/stackInitDestroy.o $(DEBUG_SET) $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/stackDump.o: workWithStack/cpp_files/stackDump.cpp
	g++ -c workWithStack/cpp_files/stackDump.cpp -o o_files/stackDump.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/stackAssertFunction.o: workWithStack/cpp_files/stackAssertFunction.cpp
	g++ -c workWithStack/cpp_files/stackAssertFunction.cpp -o o_files/stackAssertFunction.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/stackError.o: workWithStack/cpp_files/stackError.cpp
	g++ -c workWithStack/cpp_files/stackError.cpp -o o_files/stackError.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/countHash.o: workWithStack/cpp_files/countHash.cpp
	g++ -c workWithStack/cpp_files/countHash.cpp -o o_files/countHash.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

clean:
	rm -rf o_files/*.o out o_files

init:
	mkdir -p o_files