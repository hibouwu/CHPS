#!/bin/bash
# ============================================================================
# rendu.sh : creation de l'archive de rendu du TP Floyd-Warshall
# ============================================================================
# Usage, depuis le repertoire CODE :
#   bash rendu.sh
#
# Le script demande le nom et le prenom, cree un repertoire
#   NOM.PRENOM
# y copie les fichiers de rendu (sources C, C++ et CUDA, Makefile,
# REPONSES.md ; jamais d'executable ni de binaire), verifie le contenu
# de l'archive, puis produit
#   NOM.PRENOM.tar.gz
# dont il affiche la liste des fichiers. L'archive est ensuite
# envoyee par mail, en piece jointe, a adrien.roussel@cea.fr.
# ============================================================================

# --- identite ---------------------------------------------------------------
read -r -p "Nom : " nom
read -r -p "Prenom : " prenom

# Mise en forme : majuscules, accents convertis, seuls lettres, chiffres
# et tiret conserves (le nom de repertoire ne peut ainsi ni etre vide,
# ni contenir de separateur de chemin).
maj() {
    printf '%s' "$1" | iconv -f UTF-8 -t ASCII//TRANSLIT \
        | tr '[:lower:]' '[:upper:]' | tr -cd 'A-Z0-9-'
}
nom=$(maj "$nom")
prenom=$(maj "$prenom")
if [ -z "$nom" ] || [ -z "$prenom" ]; then
    echo "rendu.sh : nom ou prenom invalide (vide)." >&2
    exit 1
fi
ident="$nom.$prenom"

# --- le rendu n'a de sens qu'avec le fichier principal ----------------------
if [ ! -f fw_gpu.cu ]; then
    echo "rendu.sh : fw_gpu.cu est absent ; lancez le script depuis CODE." >&2
    exit 1
fi

# --- repertoire de rendu ----------------------------------------------------
rm -rf "$ident"
mkdir "$ident" || exit 1

# --- copie des sources uniquement : aucun executable ------------------------
shopt -s nullglob
for f in *.c *.h *.cpp *.cc *.cxx *.cu *.cuh; do
    cp -f "$f" "$ident/"
done
for f in Makefile REPONSES.md; do
    [ -f "$f" ] && cp -f "$f" "$ident/"
done

# --- archive ----------------------------------------------------------------
archive="$ident.tar.gz"
rm -f "$archive"
tar -czf "$archive" "$ident"

# --- controle : l'archive ne doit contenir que des sources ------------------
inattendus=$(tar -tzf "$archive" \
    | grep -vE "^$ident/?$" \
    | grep -vE "\.(c|h|cpp|cc|cxx|cu|cuh|md)$" \
    | grep -v "/Makefile$")
if [ -n "$inattendus" ]; then
    echo "rendu.sh : fichiers inattendus dans l'archive :" >&2
    printf '%s\n' "$inattendus" >&2
    rm -rf "$ident" "$archive"
    exit 1
fi

echo "Archive creee : $archive"
echo "Contenu :"
tar -tzf "$archive"
echo "Verifiez la liste ci-dessus, puis envoyez l'archive en piece"
echo "jointe par mail a adrien.roussel@cea.fr."
