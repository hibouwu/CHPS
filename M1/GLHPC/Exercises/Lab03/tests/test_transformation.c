#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include <stdio.h>
#include "unity.h"
#include "transformation.h"
#include <stdlib.h>
#include <stdint.h>

// Test de non-régression pour la rotation de 90 degrés dans le sens horaire
void test_rotate_90_clockwise_basic(void){
    printf("Testing 90-degree clockwise rotation...\n");
    // Créer une image de test 3x2 en niveaux de gris
    Image *img = create_image(3, 2, 1); // 3x2
    TEST_ASSERT_NOT_NULL(img);
    
    // Données de l'image originale:
    // 1 2 3
    // 4 5 6
    img->pixels[0][0] = 1; img->pixels[0][1] = 2; img->pixels[0][2] = 3;
    img->pixels[0][3] = 4; img->pixels[0][4] = 5; img->pixels[0][5] = 6;
    
    // Créer le nœud et exécuter la rotation
    Node node = {0};
    node.input = img;
    node.op = kRotate;
    
    rotate_image_90_clockwise(&node);
    
    // Vérifier que l'image de sortie existe et a les bonnes dimensions
    TEST_ASSERT_NOT_NULL(node.output);
    TEST_ASSERT_EQUAL(2, node.output->width);   // Largeur = ancienne hauteur
    TEST_ASSERT_EQUAL(3, node.output->height);  // Hauteur = ancienne largeur
    TEST_ASSERT_EQUAL(1, node.output->channels);
    
    // Vérifier le contenu après rotation 90° horaire:
    // Résultat attendu:
    // 4 1
    // 5 2  
    // 6 3
    TEST_ASSERT_EQUAL(4, node.output->pixels[0][0]); // Position (0,0)
    TEST_ASSERT_EQUAL(1, node.output->pixels[0][1]); // Position (1,0)
    TEST_ASSERT_EQUAL(5, node.output->pixels[0][2]); // Position (0,1)
    TEST_ASSERT_EQUAL(2, node.output->pixels[0][3]); // Position (1,1)
    TEST_ASSERT_EQUAL(6, node.output->pixels[0][4]); // Position (0,2)
    TEST_ASSERT_EQUAL(3, node.output->pixels[0][5]); // Position (1,2)
    
    // Libérer la mémoire
    free_image(img);
    free_image(node.output);
}

// Test de non-régression pour la taille d'image qui causait le crash original
void test_rotate_90_clockwise_original_crash_size(void){
    printf("Testing 90-degree clockwise rotation on original crash size...\n");
    // Tester avec une image RGB 259x194 (taille exacte qui causait l'erreur de segmentation)
    Image *img = create_image(259, 194, 3);
    TEST_ASSERT_NOT_NULL(img);
    
    Node node = {0};
    node.input = img;
    
    // Cet appel causait précédemment une erreur de segmentation, maintenant il devrait fonctionner
    rotate_image_90_clockwise(&node);
    
    // Vérifier que les dimensions de l'image de sortie sont correctes (éviter la confusion largeur/hauteur)
    TEST_ASSERT_NOT_NULL(node.output);
    TEST_ASSERT_EQUAL(194, node.output->width);   // Largeur = ancienne hauteur
    TEST_ASSERT_EQUAL(259, node.output->height);  // Hauteur = ancienne largeur
    TEST_ASSERT_EQUAL(3, node.output->channels);  // Nombre de canaux inchangé
    
    // Libérer la mémoire
    free_image(img);
    free_image(node.output);
}