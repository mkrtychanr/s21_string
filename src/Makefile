CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TST_LIBS = -lcheck
ifeq ($(shell uname), Linux)
	TST_LIBS += -lpthread -lrt -lsubunit -lm
endif
LIB_NAME = s21_string

SRCS=$(wildcard s21_*.c)

OBJS=$(SRCS:.c=.o)

all: clean test

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css

clang-format:
	clang-format -i *.c *.h tests/*.c tests/*.h

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf *.o

linter:
	python3 ../cpplint.py --extensions=c *.c *.h tests/*.c tests/*.h

# check - либа для работы тестов, $(LIB_NAME) - наша либа
test: clean $(LIB_NAME).a
	$(CC) $(FLAGS) check.c tests/*.c $(LIB_NAME).a $(TST_LIBS) -o test

main: $(LIB_NAME).a
	$(CC) $(FLAGS) main.c -L. -l$(LIB_NAME) $(TST_LIBS) -o Main

add_coverage_flag:
	$(eval FLAGS += --coverage)

gcov_report: add_coverage_flag test
	./test
	rm check*.gcda check*.gcno
	gcov -b -l -p -c s21_*.gcno
	gcovr -o gcov_report.html --html --html-details
