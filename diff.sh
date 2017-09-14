if [ $# -ne 1 ]
then
	echo "usage : ./diff.sh BINARY_FILE"
	exit
fi
diff <( ./ft_nm $1 ) <( nm $1 )
