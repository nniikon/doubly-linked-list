CFLAGS = -O0 -Wall -Waggressive-loop-optimizations 							   \
-Wmissing-declarations -Wcast-align -Wcast-qual 							   \
-Wchar-subscripts -Wconversion 												   \
-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security 			   \
-Wformat-signedness -Wformat=2 -Winline -Wlogical-op 						   \
-Wopenmp-simd -Wpacked -Wpointer-arith -Winit-self 							   \
-Wredundant-decls -Wshadow 													   \
-Wstrict-overflow=2 -Wsuggest-attribute=noreturn 							   \
-Wsuggest-final-methods -Wsuggest-final-types 								   \
-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code 	 	   \
-Wunused -Wvariadic-macros -Wno-nonnull 									   \
-Wno-missing-field-initializers -Wno-narrowing 								   \
-Wno-varargs -Wstack-protector -fcheck-new 									   \
-fstack-protector -fstrict-overflow -flto-odr-type-merging 					   \
-fno-omit-frame-pointer -Wstack-usage=8192 									   \
-fsanitize=address,bool,bounds,enum,float-cast-overflow,$\
float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,$\
object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,$\
undefined,unreachable,vla-bound,vptr

CFLAGS += -D DEBUG
CFLAGS += -D LOG

export CFLAGS

export BUILD_DIR = ${CURDIR}/build
export EXEC_NAME = list 

export GXX = g++
