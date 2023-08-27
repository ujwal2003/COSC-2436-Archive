#Compile the code
# if the file densemult exits then remove it
if [ -f evalexpr ]; then
    rm evalexpr
fi
g++ -std=c++11 *.cpp -o evalexpr
# if the file densemult does not exit then exit the test
if [ ! -f evalexpr ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi
# clean
if [ -f *.out ]; then
    rm *.out
fi
if [ -f *.stderr ]; then
    rm *.stderr
fi
if [ -f *.stdcout ]; then
    rm *.stdcout
fi
#rm *.out *.stderr *.stdcout
# For test case 1
# input 1.txt and output 1.out
./evalexpr "input=input21.txt;output=output21.txt" 1>21.stdcout 2>21.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu ans21.txt output21.txt > 21.diff
# if diff returns nothing, it means you pass the test case (Your ourput file 1.out is correct)
if [ $? -ne 0 ]; then
    # display "test case 21 FAILED" to the screen. The word "FAILED" is highlighted in Red color
    echo -e "Test case 21    \033[1;91mFAILED.\033[0m"
else
    # display "test case 21 PASSED" to the screen. The word "PASSED" is highlighted in Green color
    echo -e "Test case 21    \033[1;92mPASSED.\033[0m"
    # remove the file 21.diff
    rm -f 21.diff
fi
# For test case 2
./evalexpr "input=input22.txt;output=output22.txt" 1>22.stdcout 2>22.stderr
diff -iEBwu ans22.txt output22.txt > 22.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 22    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 22    \033[1;92mPASSED.\033[0m"
    rm -f 22.diff
fi
# For test case 23
./evalexpr "input=input23.txt;output=output23.txt" 1>23.stdcout 2>23.stderr
diff -iEBwu ans23.txt output23.txt > 23.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 23    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 23    \033[1;92mPASSED.\033[0m"
    rm -f 23.diff
fi
# For test case 24
./evalexpr "input=input24.txt;output=output24.txt" 1>24.stdcout 2>24.stderr
diff -iEBwu ans24.txt output24.txt > 24.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 24    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 24    \033[1;92mPASSED.\033[0m"
    rm -f 24.diff
fi
# For test case 25
./evalexpr "input=input25.txt;output=output25.txt" 1>25.stdcout 2>25.stderr
diff -iEBwu ans25.txt output25.txt > 25.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 25    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 25    \033[1;92mPASSED.\033[0m"
    rm -f 25.diff
fi
# For test case 26
./evalexpr "input=input26.txt;output=output26.txt" 1>26.stdcout 2>26.stderr
diff -iEBwu ans26.txt output26.txt > 26.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 26    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 26    \033[1;92mPASSED.\033[0m"
    rm -f 26.diff
fi
# For test case 27
./evalexpr "input=input27.txt;output=output27.txt" 1>27.stdcout 2>27.stderr
diff -iEBwu ans27.txt output27.txt > 27.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 27    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 27    \033[1;92mPASSED.\033[0m"
    rm -f 27.diff
fi
# For test case 28
./evalexpr "input=input28.txt;output=output28.txt" 1>28.stdcout 2>28.stderr
diff -iEBwu ans28.txt output28.txt > 28.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 28    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 28    \033[1;92mPASSED.\033[0m"
    rm -f 28.diff
fi
# For test case 29
./evalexpr "input=input29.txt;output=output29.txt" 1>29.stdcout 2>29.stderr
diff -iEBwu ans29.txt output29.txt > 29.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 29    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 29    \033[1;92mPASSED.\033[0m"
    rm -f 29.diff
fi