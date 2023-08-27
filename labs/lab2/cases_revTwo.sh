# PLEASE CHANGE THIS NUMBER TO THE TOTAL NUMBER OF TEST CASES
#declare -i n=5
readonly n=5
# PLEASE CHANGE THIS NUMBER TO THE TOTAL NUMBER OF TEST CASES


cmd=lab1
if [ -f ${cmd} ]; then
    rm ${cmd}
fi

g++ -std=c++11 *.cpp -o ${cmd}

if [ ! -f ${cmd} ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi

# REMOVES THE EXTRANEOUS FILES
for casenum in `seq 1 1 $n`; do # START: 1, INCREMENT BY: 1, END AT: 3
    if [ -f T${casenum}.out ]; then
        rm T${casenum}.out
    fi
    if [ -f T${casenum}.stderr ]; then
        rm T${casenum}.stderr
    fi
    if [ -f T${casenum}.stdcout ]; then
        rm T${casenum}.stdcout
    fi
done

# ACTUAL TESTING PART
for casenum in `seq 1 1 $n`; do # START: 1, INCREMENT BY: 1, END AT: 3
	./${cmd} "input=inputT${casenum}.txt;output=outputT${casenum}.txt" 1>T${casenum}.stdcout 2>T${casenum}.stderr
# COMPARING ans#.txt TO output#.txt, PUTTING RESULT IN #.diff
	diff -iEBwu ansT${casenum}.txt outputT${casenum}.txt > T${casenum}.diff

	if [ $? -ne 0 ]; then   # FAILED IF THERE IS A DIFFERENCE BETWEEN THE ANSWER AND YOUR OUTPUT
    		echo -e "Test case T${casenum}    \033[1;91mFAILED.\033[0m"
	else
    		echo -e "Test case T${casenum}    \033[1;92mPASSED.\033[0m"
    		rm -f T${casenum}.diff
            rm -f T${casenum}.stderr
            rm -f T${casenum}.stdcout
	fi
done

if [ -f ${cmd} ]; then
    rm ${cmd}
fi