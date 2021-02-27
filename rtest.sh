clang -g -fsanitize=address world_init.c read_rt.c object_init.c  get_next_line.c libft.a

echo "============================================"
echo "==================invalid==================="
echo -e "============================================\n"

for i in {1..100}
do
	echo "file : $i.rt"
	./a.out rt/invalid/$i.rt
	if [ $? != 0 ]; then
		printf '\n\033[32m%s\033[m\n' '[OK]'
		echo -e "============================================\n"
	else
		printf '\n\033[31m%s\033[m\n' '[KO]'
		echo -e "============================================\n"
	fi
	FILE="rt/invalid/$i.rt"
	if [ ! -e $FILE ]; then
		break
	fi
done

echo "file : .rt"
./a.out rt/invalid/.rt 
if [ $? != 0 ]; then
	printf '\n\033[32m%s\033[m\n' '[OK]'
	echo -e "============================================\n"
else
	printf '\n\033[31m%s\033[m\n' '[KO]'
	echo -e "============================================\n"
fi

echo "file : a"
./a.out rt/invalid/a 
if [ $? != 0 ]; then
	printf '\n\033[32m%s\033[m\n' '[OK]'
	echo -e "============================================\n"
else
	printf '\n\033[31m%s\033[m\n' '[KO]'
	echo -e "============================================\n"
fi

echo -e "\n============================================"
echo "===================valid===================="
echo -e "============================================\n"

for i in {1..100}
do
	FILE="rt/valid/$i.rt"
	if [ ! -e $FILE ]; then
		break
	fi
	echo "file : $i.rt"
	./a.out rt/valid/$i.rt
	if [ $? != 0 ]; then
		printf '\n\033[31m%s\033[m\n' '[KO]'
		echo -e "============================================\n"
	else
		printf '\n\033[32m%s\033[m\n' '[OK]'
		echo -e "============================================\n"
	fi
done