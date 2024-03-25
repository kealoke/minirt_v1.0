#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <error_or_success_or_bonus>"
    exit 1
fi

if [ "$1" = "error" ]; then
    for error_file in rt_file/error/*; do
        echo "Processing error file: $error_file"
        ./miniRT "$error_file"
    done

elif [ "$1" = "success" ]; then
    for success_file in rt_file/success/*; do
        echo "Processing success file: $success_file"
        ./miniRT "$success_file"
    done

elif [ "$1" = "bonus" ]; then
    for bonus_file in rt_file/bonus/*; do
        echo "Processing bonus file: $bonus_file"
        ./miniRT "$bonus_file"
    done

else
    echo "Invalid argument. Please provide 'error' or 'success' or 'bonus'."
    exit 1
fi
