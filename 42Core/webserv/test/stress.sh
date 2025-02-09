#!/bin/bash

# Define the ports to test
ports=(8080 8081 8082)

# Loop indefinitely
while true; do
    for port in "${ports[@]}"; do
        curl -s "http://localhost:$port" > /dev/null
        if [ $? -eq 0 ]; then
            echo "Port $port is up"
        else
            echo "Port $port is down"
        fi
    done
    for port in "${ports[@]}"; do
        curl -s "https://localhost:$port" > /dev/null
        if [ $? -eq 0 ]; then
            echo "Port $port is up"
        else
            echo "Port $port is down"
        fi
    done
    # sleep 1
done