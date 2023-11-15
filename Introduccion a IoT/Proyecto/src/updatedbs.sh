#!/bin/bash
spinerFunction(){
    local i sp n
    chars="/-\|"
    n=${#chars}
    printf ' '
    while sleep 0.1; do
        printf "%s\b" "${chars:i++%n:1}"
    done
}
if [ ! -z $1 ] && [! -z $2 ] && [ ! -z $3 ] && [! -z $4] then;
    openvpn "$1" &> /dev/null &
    firstLine="$(head -1 $2)"
    if [ ! -d temcsv/ ];then
        mkdir temcsv
        cd temcsv/
        touch tem
    else
        cd temcsv/
        touch tem
    fi
    tail -n +2 "$2">tem
    sed -i 's/\"//g' tem
    IFC=""
    while read i; do
        tt="$(cut -d "," -f 1 <<<"$i")"
        ipsrc="$(cut -d "," -f 2 <<<"$i")"
        ipdst="$(cut -d "," -f 3 <<<"$i")"
        protocol="$(cut -d "," -f 4 <<<"$i")"
        length="$(cut -d "," -f 5 <<<"$i")"
        info="$(cut -d "," -f 6 <<<"$i")"
        printf "Saving remote data"
        spinerFunction &
ssh "$3"@"$4" &> /dev/null<< EOF
mariadb -u root -proot ids -e "INSERT INTO traffic (time, ipsrc, ipdst, protocol, packlen, info) VALUES ($tt, '$ipsrc', '$ipdst', '$protocol', $length, '$info')"

EOF
done<tem
kill "$!"
echo "Saved Data returning to main menu..."
cd ../..
sleep 3
else
    echo "ERROR! MAKE SURE TO BE LOGGIN AS ROOT OR ALL ENTRIES ARE RIGHT"
    