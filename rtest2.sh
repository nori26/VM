echo_result(){
	if [$1]; then
		echo aaaa
	fi
}

echo $?
echo $result
echo_result test $?