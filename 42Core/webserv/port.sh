#!/bin/bash

# Vérifie si un port a été passé en argument
if [ -z "$1" ]; then
  echo "Usage: $0 <port>"
  exit 1
fi

PORT=$1

echo "Recherche des processus utilisant le port $PORT..."

# Trouve les processus utilisant le port
PIDS=$(sudo lsof -t -i :$PORT)

if [ -z "$PIDS" ]; then
  echo "Aucun processus trouvé sur le port $PORT."
  exit 0
fi

echo "Processus trouvés : $PIDS"

# Tuer les processus
for PID in $PIDS; do
  echo "Fermeture du processus PID=$PID..."
  sudo kill -9 $PID
done

echo "Vérification que le port $PORT est libéré..."

# Vérifie que le port est maintenant libéré
CHECK=$(sudo lsof -i :$PORT)
if [ -z "$CHECK" ]; then
  echo "Le port $PORT est désormais fermé."
else
  echo "Erreur : le port $PORT est toujours utilisé."
fi
