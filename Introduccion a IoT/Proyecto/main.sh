#!/bin/bash
trap ' ' 2 20
clear
# Reset
Color_Off='\033[0m'       # Text Reset

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

# Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White

# Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White

# High Intensity
IBlack='\033[0;90m'       # Black
IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
IBlue='\033[0;94m'        # Blue
IPurple='\033[0;95m'      # Purple
ICyan='\033[0;96m'        # Cyan
IWhite='\033[0;97m'       # White

# Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
BIPurple='\033[1;95m'     # Purple
BICyan='\033[1;96m'       # Cyan
BIWhite='\033[1;97m'      # White

# High Intensity backgrounds
On_IBlack='\033[0;100m'   # Black
On_IRed='\033[0;101m'     # Red
On_IGreen='\033[0;102m'   # Green
On_IYellow='\033[0;103m'  # Yellow
On_IBlue='\033[0;104m'    # Blue
On_IPurple='\033[0;105m'  # Purple
On_ICyan='\033[0;106m'    # Cyan
On_IWhite='\033[0;107m'   # White'

directoryCodes="src/"

while : ;do
    source "${directoryCodes}/info.sh"
    echo -e "${Cyan}\t\tWelcome $USER, choose an option please:${Color_Off}"
    echo -e "${IRed} [1]. Install packets (Wireshark and some dependences of python)"
    echo -e "${IRed} [2]. Get IP from esp32"
    echo -e "${IRed} [3]. Start IDS and start esp32 inspection"
    echo -e "${IRed} [4]. Update remote database (sudo administrator permissions)"
    echo -e "${IRed} [5]. Quit ${Color_Off}${IBlue}"
    read -p " ==> " input
    case $input in
        "1")
            source "${directoryCodes}/installations.sh" ;;
        "2")
            source "python3 pyfiles/getsips.py"
            ;;
        "3")
            read -p "Give the path of your, if you add one: " pathIP
            if [ -z "$pathIP"]
            then
                source "${directoryCodes}/idsinspection.sh"
            else
                source "${directoryCodes}/idsinspection.sh" "$pathIP"
            fi;;
        "4")
            echo "SUDO permissions -> Using openvpn to connect remote base"
            read -p "Path of your vpn: " vpnVar
            read -p "Your path of CSV: " csvPath
            read -p "User name or root (connect by SSH): " uSSHname
            read -p "Your IP from your server: "ipServerRemote
            source "$sudo {directoryCodes}/updatedbs.sh" "$vpnVar" "$csvPath" "$csvPath" "$uSSHname" "$ipServerRemote"
            ;;
        "5")
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