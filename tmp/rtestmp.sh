clang -g -fsanitize=address world_init.c read_rt.c object_init.c  get_next_line.c libft.a

echo "============================================"
echo "==================invalid==================="
echo -e "============================================\n"

result=0
cases=0;
ko[0]=KO
k=1
run=./a.out
path_ko=rt/invalid
path_ok=rt/valid

function print_result() {
	if [$1]

	else
}

for i in {1..100}
do
	echo "file : $i.rt" &
	if &? != 0
	if kill
	$run $path_ko/$i.rt
	if [ $? != 0 ]; then
		let result++
		printf '\n\033[32m%s\033[m\n' '[OK]'
		echo -e "============================================\n"
	else
		ko[k]=$i
		let k++
		printf '\n\033[31m%s\033[m\n' '[KO]'
		echo -e "============================================\n"
	fi
	FILE="$path_ko/$i.rt"
	if [ ! -e $FILE ]; then
		cases=$i
		break
	fi
done

echo "file : .rt"
$run $path_ko/.rt 
if [ $? != 0 ]; then
	let result++
	printf '\n\033[32m%s\033[m\n' '[OK]'
	echo -e "============================================\n"
else
	ko[k]=$i
	let k++
	printf '\n\033[31m%s\033[m\n' '[KO]'
	echo -e "============================================\n"
fi

let cases++

echo "file : a"
$run $path_ko/a 
if [ $? != 0 ]; then
	let result++
	printf '\n\033[32m%s\033[m\n' '[OK]'
	echo -e "============================================\n"
else
	ko[k]=$i
	let k++
	printf '\n\033[31m%s\033[m\n' '[KO]'
	echo -e "============================================\n"
fi

let cases++

echo -e "\n============================================"
echo "===================valid===================="
echo -e "============================================\n"

for i in {1..100}
do
	FILE="$path_ok/$i.rt"
	if [ ! -e $FILE ]; then
		break
	fi
	let cases++
	echo "file : $i.rt"
	$run $path_ok/$i.rt
	if [ $? == 0 ]; then
		let result++
		printf '\n\033[32m%s\033[m\n' '[OK]'
		echo -e "============================================\n"
	else
		ko[k]=$i
		let k++
		printf '\n\033[31m%s\033[m\n' '[KO]'
		echo -e "============================================\n"
	fi
done

echo OK $result / $cases
for i in "${ko[@]}"
do
	echo -n "$i "
done