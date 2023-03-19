#Function: monitor load average of cpu, and write to file
#Author:Mr.Yu
# create file
if [ -f cpu_monitor.txt ]
	then
	touch cpu_monitor.txt
fi

# modify file permission
if [ -w cpu_monitor.txt ]
	then
	chmod 755 cpu_monitor.txt
fi

# write cpu infomation
cat /proc/cpuinfo | grep "model name" > cpu_monitor.txt
cat /proc/cpuinfo | grep "cpu cores" >> cpu_monitor.txt

echo " " >> cpu_monitor.txt
echo Total data: >> cpu_monitor.txt
echo user nice system idle iowait irq softirq >> cpu_monitor.txt

#write cpu infomation every 2s
for ((i=0;i<=50;i++))
	do
	cat /proc/stat | grep 'cpu ' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}' >> cpu_monitor.txt
	sleep 2
done 
