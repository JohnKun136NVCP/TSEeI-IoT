#!/bin/bash
#trap ' ' 2 20
#colors
cyan='\033[0;36m'
lblue='\033[1;34m'
red='\033[0;31m'
function wiresharkFunction (){
  csvDataDirectory="csvdata"
  echo -e "${lblue}Make sure you all ready installed wireshark and tshark"
  read -p "Type name for wireshark catch file(without extensions): " wirefile
  sleep 0.5
  for _ in once; do
    if [ -d records/ ]
    then
        cd records/
        touch "$wirefile".pcap
        break
    else
        mkdir records
        cd records/
        touch "$wirefile".pcap
        break
    fi
  done
  echo "Showing interfaces for Wireshark. Choose your interface of network (WAN/LAN)"
  ifconfig -a
  read -p "Type the interface: " intNetwork
  clear
  echo -e "${red}WARNING!!\n Wireshark will execute soon\n when you finish your scanning, please save it as .csv file and quit id column"
  sleep 0.5
  for _ in once;do
    if [ -f "$csvDataDirectory" ]
    then
        echo -e "${lblue}Automatically, it will be created a directory (csvdata) if you want to save your files..."
        mkdir csvdata
        echo "Directory created"
        break
    else
        break
    fi
  done
  sleep 0.5
  tail -f -c 0 "$wirefile".pcap | wireshark -k -i "$intNetwork" -R "ip.addr == $1" -Y "ip.addr == $1" -w "$wirefile".pcap;
  echo "Data saved it"
}

function esp32Ids(){
    cd pyfiles/;source "python3 esp32listener.py"
}

echo -e "${cyan} Welcome to IDS Mirrow, please check, you save  EPSP32's IP address on file. If not it'll take default path (~/pyfiles/.ip/ip.txt)"
file=$1
file_default="pyfiles/.ip/ip.txt"
if [ -z "$file" ]
then
    echo "Taking default path..."
    sleep 1
    if [ -f "$file_default" ]
    then
        ip="$(cat "$file_default")"
        wiresharkFunction $ip
        #esp32Ids //Until esp32 pyfile will work
        cd ..
    else
        echo "First execute number 2 option from main.sh to get your IP"
        exit 1
    fi
else
    echo "Getting ip..."
    sleep 0.5
    if [ -f "$file" ]
    then
        ip="$(cat $file)"
        wiresharkFunction $ip
        #esp32Ids //Until esp32 pyfile will work
        cd ..
    else
        echo "Your path or file doesn't exist"
        echo "First execute number 2 option from main.sh to get your IP"
        exit 1
    fi  
fi
#trap - 2 20