#!/bin/bash
#SBATCH --job-name=test_mpi       # Nom du job
#SBATCH --partition=docker        # Nom de la partition (défini dans votre slurm.conf)
#SBATCH --nodes=2                 # Demande 2 noeuds (c1 et c2)
#SBATCH --ntasks=2                # Demande 2 tâches au total
#SBATCH --ntasks-per-node=1       # 1 tâche par noeud (pour forcer la répartition)
#SBATCH --output=res_%j.out       # Fichier de sortie standard (%j = ID du job)
#SBATCH --error=res_%j.err        # Fichier d'erreur

echo "=========================================="
echo "Job SLURM ID : $SLURM_JOB_ID"
echo "Date de début : $(date)"
echo "Exécuté sur le noeud maître : $(hostname)"
echo "Liste des noeuds alloués : $SLURM_JOB_NODELIST"
echo "=========================================="

echo ""
echo ">>> TEST 1 : Vérification simple des noeuds (srun hostname)"
# Doit retourner c1 et c2
srun hostname

echo ""
echo ">>> TEST 2 : Test MPI via Python (mpi4py)"
# Ce script Python va afficher le rang MPI et le nom de l'hôte
# Votre slurm.conf utilise MpiDefault=pmi2, donc srun devrait gérer la communication
srun python3 -c "from mpi4py import MPI; \
comm = MPI.COMM_WORLD; \
rank = comm.Get_rank(); \
size = comm.Get_size(); \
host = MPI.Get_processor_name(); \
print(f'MPI SUCCESS: Je suis le rang {rank} sur {size}, tournant sur le conteneur {host}')"

echo ""
echo "=========================================="
echo "Fin du job : $(date)"
