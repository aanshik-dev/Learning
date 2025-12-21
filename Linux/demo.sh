#!/bin/bash

system_info(){
   echo "=== System Information"
   echo "Hostname : $(hostname)"
   echo "Operating System : $(uname -s)"
   echo "User : $USER"
   echo "Current Directory : $PWD"
   echo "Date : $(date)"
}

system_info
