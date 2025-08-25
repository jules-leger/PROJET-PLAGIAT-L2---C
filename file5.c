#include <stdio.h>
#include <time.h>

int main() {
  // Obtenir l'heure actuelle
  time_t temps_actuel = time(NULL);
  struct tm *heure_locale = localtime(&temps_actuel);

  // Définir les limites de l'heure du jour (de 6h00 à 18h59)
  int debut_jour = 6;
  int fin_jour = 18;

  // Vérifier si l'heure actuelle se trouve dans la plage de l'heure du jour
  if (debut_jour <= heure_locale->tm_hour && heure_locale->tm_hour <= fin_jour) {
    // Afficher un soleil
    printf("\u2600");
  } else {
    // Afficher une lune
    printf("\u263D");
  }

  return 0;
}
