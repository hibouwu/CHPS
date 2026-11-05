#!/usr/bin/env bash

# 1. Vérification de la présence du fichier
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <fichier_sass.txt>"
    exit 1
fi

FILE_PATH="$1"

if [ ! -f "$FILE_PATH" ]; then
    echo "Erreur : Le fichier '$FILE_PATH' n'a pas été trouvé."
    exit 1
fi

# 2. Extraction des mnémoniques compatible avec toutes les versions d'AWK
RAW_DATA=$(awk '
/^[ \t]*\/\*[0-9a-fA-F]+\*\// {
    # On isole tout ce qui suit l adresse /*0008*/
    sub(/^[ \t]*\/\*[0-9a-fA-F]+\*\/[ \t]*/, "")
    
    # On retire le prédicat s il existe (@!P0, @P0)
    sub(/^@[!]*P[0-7][ \t]*/, "")
    
    # On extrait le premier mot (le mnémonique de l instruction)
    split($0, words, "[ \t\n;.]+")
    mnemonic = words[1]
    
    # On ne conserve que les mnémoniques valides
    if (mnemonic ~ /^[A-Z0-9]+$/ && mnemonic != "") {
        print mnemonic
    }
}' "$FILE_PATH")

if [ -z "$RAW_DATA" ]; then
    echo "## Répartition des Instructions SASS (Analyse Statique)"
    echo ""
    echo "**Nombre total d'instructions SASS dans le binaire :** \`0\`"
    exit 0
fi

# 3. Calcul du total d'instructions
TOTAL_INST=$(echo "$RAW_DATA" | wc -l | tr -d ' ')

# 4. Génération du rapport Markdown avec description
echo "## Répartition des Instructions SASS (Analyse Statique)"
echo ""
echo "**Nombre total d'instructions SASS dans le binaire :** \`$TOTAL_INST\`"
echo ""
echo "| Rang | Instruction SASS | Description | Nombre d'occurrences | Proportion |"
echo "| :---: | :--- | :--- | :---: | :---: |"

# Tri par fréquence et enrichissement avec la description via AWK
echo "$RAW_DATA" | sort | uniq -c | sort -nr | awk -v total="$TOTAL_INST" '
BEGIN {
    rank = 1
    # Dictionnaire des descriptions des instructions SASS CUDA
    desc["LDS"]     = "Load Shared Memory (Lecture mémoire partagée)"
    desc["STS"]     = "Store Shared Memory (Écriture mémoire partagée)"
    desc["LDG"]     = "Load Global Memory (Lecture mémoire globale)"
    desc["STG"]     = "Store Global Memory (Écriture mémoire globale)"
    desc["LDC"]     = "Load Constant Memory (Lecture mémoire constante)"
    desc["DFMA"]    = "Double Precision Fused Multiply-Add"
    desc["FFMA"]    = "Single Precision Fused Multiply-Add"
    desc["HMMA"]    = "Half Precision Matrix Multiply-Accumulate (Tensor Core)"
    desc["IMMA"]    = "Integer Matrix Multiply-Accumulate (Tensor Core)"
    desc["DMUL"]    = "Double Precision Multiply"
    desc["FMUL"]    = "Single Precision Multiply"
    desc["DADD"]    = "Double Precision Add"
    desc["FADD"]    = "Single Precision Add"
    desc["XMAD"]    = "Integer 16-bit Multiply-Add (Calcul d d indexation)"
    desc["IMAD"]    = "Integer 32-bit Multiply-Add"
    desc["IADD"]    = "Integer Addition"
    desc["IADD32I"] = "Integer Add 32-bit Immediate"
    desc["ISCADD"]  = "Scaled Integer Add (Multiplication par constante + addition)"
    desc["MOV"]     = "Register Move (Transfert entre registres)"
    desc["S2R"]     = "Special Register to Register (Lecture ID thread/bloc)"
    desc["LEA"]     = "Load Effective Address (Calcul d adresses)"
    desc["SHL"]     = "Shift Left (Décalage binaire à gauche)"
    desc["SHR"]     = "Shift Right (Décalage binaire à droite)"
    desc["LOP3"]    = "Logic Operation 3-input LUT"
    desc["LOP32I"]  = "Logic Operation 32-bit Immediate"
    desc["ISETP"]   = "Integer Set Predicate (Test de condition entière)"
    desc["FSETP"]   = "Float Set Predicate (Test de condition flottante)"
    desc["NOP"]     = "No Operation (Alignement / Délai d attente)"
    desc["BAR"]     = "Barrier Synchronization (Barrière de synchro du bloc)"
    desc["MEMBAR"]  = "Memory Barrier (Barrière mémoire)"
    desc["BRA"]     = "Branch (Saut / Contrôle de flux)"
    desc["JCAL"]    = "Jump Subroutine Call (Appel de fonction)"
    desc["EXIT"]    = "Program Exit (Fin d exécution du kernel)"
}
{
    count = $1
    instr = $2
    pct = (count / total) * 100
    
    # Récupération de la description ou valeur par défaut si absente du dictionnaire
    d = (instr in desc) ? desc[instr] : "Instruction de calcul / contrôle"
    
    printf("| %d | **%s** | %s | %d | %.2f%% |\n", rank, instr, d, count, pct)
    rank++
}'
