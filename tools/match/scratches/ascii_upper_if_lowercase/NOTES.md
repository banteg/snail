# RstrASC

Exact at 7/7 instructions with no masked operands. It folds lowercase ASCII to
uppercase and leaves every other byte unchanged. Android and iOS preserve the
same `RstrASC(char)` entry in `RString.o`.
