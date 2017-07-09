sum=`sha256sum $1 | cut -d ' ' -f 1`
for i in `seq 2 $2`; do
	sum=`echo $sum | sha256sum | cut -d ' ' -f 1`
done
echo $sum
