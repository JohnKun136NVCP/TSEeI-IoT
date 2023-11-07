#!/bin/bash
trap ' ' 2 20
clear
#Colors
red='\033[0;31m'
black='\033[0;30m'
green='\033[0;32m'
cyan='\033[0;36m'
yellow='\033[1;33m'
nc='\033[0m'
lblue='\033[1;34m'
lred='\033[1;31m'
lcyan='\033[1;36m'

directoryCodes="src/"

while : ;do
    echo -e "\033[5m${green} ___           ______   __   __                                   _____ ______  _______  _____  ____  "  
    echo -e "\033[5m${green}(   )    /\    \  ___) |  \ /  |                                 |  ___)\  ___)(   _   )(__  / (___ \   "
    echo -e "\033[5m${green} | |    /  \    \ \    |   v   | _    ___    ___    ___    ___   | |_    \ \    | | | |   / /    __) )"
    echo -e "\033[5m${green} | |   / /\ \    > >   | |\_/| || |  / _ \  / _ \  / _ \  / _ \  |  _)    > >   | | | |  (__ \  / __/ "
    echo -e "\033[5m${green} | |  / /__\ \  / /__  | |   | || | | |_) )| |_) )( (_) )| |_) ) | |___  / /__  | | | |  ___) )| |___ "
    echo -e "\033[5m${green}(___)/________\/_____) |_|   |_| \_)|  __/ |  __/  \___/ |  __/  |_____)/_____) |_| |_| (____/ |_____)"
    echo -e "\033[5m${green}                                   | |    | |           | |                                           "
    echo -e "\033[5m${green}                                   |_|    |_|           |_|                                           "
    cat src/imgascii/logo.txt
    echo -e "${yellow} IDS Mirror ESP32 ver. 1.0.0${nc}"
    echo -e "${lblue} Made by JohnKun136NVCP and Jose-MPM"
    echo
    echo -e "${cyan} Welcome $USER, choose an option please:${nc}"
    echo -e "${lred}[1]. Install packets (Wireshark and some dependences of python)"
    echo -e "${lred}[2]. Get IP from esp32"
    echo -e "${lred}[3]. Start IDS and start esp32 inspection"
    echo -e "${lred}[4]. Update database local"
    echo -e "${lred}[5]. Update from database local to remote database"
    echo -e "${lred}[6]. INFO"
    echo -e "${lred}[7]. Quit ${nc}${lblue}"
    read -p "==> " input
    case $input in
        "1")
            source "${directoryCodes}/installations.sh" ;;
        "2")
            source "python3 pyfiles/getsips.py"
            ;;
        "3")
            echo "Ok3"
            ;;
        "4")
            echo "OK4"
            ;;
        "5")
            echo "OK5"
            ;;
        "6")
            echo "OK5"
            ;;
        "7")
            echo "Quitting the menu..."
            exit 0
            ;;
        *)
            eval "$input" || clear
            echo "Invalid option"
            ;;
    esac
done

trap - 2 20
