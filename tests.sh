rm test1original.txt test2original.txt test3original.txt test4original.txt test5original.txt test6original.txt test7original.txt
rm test1.txt test2.txt test3.txt test4.txt test5.txt test6o.txt test7.txt

echo "Test 1 - ls -a >(One-comand)! -----------------------------"
ls > test1original.txt
echo $?
echo "Original:"
cat test1original.txt
echo "Test 2 - ls | grep a > test2.txt (two comands without infile)! -----------------------------"
ls | grep a > test2original.txt
echo $?
echo "Original:"
cat test2original.txt
echo "Test 3 - ls | grep a | grep t > test3.txt (tree comands)! -----------------------------"
ls | grep a | grep t > test3original.txt
echo $?
echo "Original:"
cat test3original.txt
echo "Test 4 - < text1.txt grep c | grep a | grep t > outfile(outfile e infile) -----------------------------"
< infile grep c | grep a | grep t > test4original.txt
echo $?
echo "Original:"
cat test4original.txt
echo "Test 5 - < text1.txt grep c | grep a | grep t >> test3.txt! (heredoc) -----------------------------"
echo "Test 5 - ls >> test5.txt -----------------------------"
ls >> test5original.txt
echo $?
echo "Original:"
cat test5original.txt
echo "Test 6 (built in env) - env | grep a >> test6.txt -----------------------------"
env | grep a >> test6original.txt
echo $?
echo "Original:"
cat test6original.txt
echo "Test 7 (built in pwd) - pwd | grep a >> test7.txt -----------------------------"
pwd | grep a >> test7original.txt
echo $?
echo "Original:"
cat test7original.txt
echo "Test 8 echo dasdasdsa -----------------------------"
echo dasdasdsa >> test8original.txt
echo $?
echo "Original:"
cat test8original.txt



