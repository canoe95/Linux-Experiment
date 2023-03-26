echo System time: `date "+%Y-%m-%d %H:%M:%S"`
echo Running time: `uptime -p`
echo Load average: `cat /proc/loadavg | awk '{print $1,$2,$3}'`
totalMem=`free -h | grep 内存 | awk '{print $2}'`
usedMem=`free -h | grep 内存 | awk '{print $3}'`
echo used memory: $usedMem / $totalMem
