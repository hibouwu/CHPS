#!/bin/bash
#SBATCH --job-name=mon_job       # Nom de la tâche
# #SBATCH --nodes=1                # Nombre de nœuds
#SBATCH --ntasks=1               # Nombre de tâches
# #SBATCH --cpus-per-task=4        # Nombre de processeurs par tâche
# #SBATCH --mem=4G                 # Mémoire par tâche
#SBATCH --time=00:10:00          # Temps limite (HH:MM:SS)
# #SBATCH --partition=nom_partition # Partition spécifique

# Chargez les modules nécessaires (facultatif, selon votre configuration)
# module load module1
# module load module2

# Commandes à exécuter sur chaque nœud
# (remplacez ces lignes par les commandes réelles de votre script)
echo "Hello, this is my Slurm job!"
echo "Running on host: $(hostname)"
echo "Current directory: $(pwd)"
sleep 120
echo "fin"
# Fin du script

