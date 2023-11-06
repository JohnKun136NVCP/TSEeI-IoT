#!/bin/bash
trap ' ' 2 20
    echo "Installing packets..."
    sleep 4
    echo "Please, this version only works on Debian based distributions..."
    sleep 4
    sudo add-apt-repository ppa:wireshark-dev/stable
    sudo apt-get update
    echo "Installing Wireshark..."
    echo "Select YES if any user's able to run wireshark without root permissions"
    echo "If it's necessary to reboot your computer, only run again the script"
    sleep 4
    sudo apt install wireshark
    echo "Packets installed..."
    sleep 4
    clear
trap - 2 20