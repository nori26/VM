clang -g -fsanitize=address world_init.c read_rt.c object_init.c  get_next_line.c libft.a

echo "============================================"
echo "==================invalid==================="
echo -e "============================================\n"

result=0
cases=0;
ko[0]=KO
k=1

for i in {1..100}
do
	echo "file : $i.rt"
	./a.out rt/invalid/$i.rt
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
	FILE="rt/invalid/$i.rt"
	if [ ! -e $FILE ]; then
		cases=$i
		break
	fi
done

echo "file : .rt"
./a.out rt/invalid/.rt 
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
./a.out rt/invalid/a 
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
	FILE="rt/valid/$i.rt"
	if [ ! -e $FILE ]; then
		break
	fi
	let cases++
	echo "file : $i.rt"
	./a.out rt/valid/$i.rt
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