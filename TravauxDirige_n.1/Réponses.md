# Exercice à rendre

## Un hello World parallèle

Il est plus clair d'écrire dans des fichiers que de mettre le résultat dans le terminal car les résultats ne sont pas trié dans le terminal.

## Envoi bloquant et non bloquant

La première version est plus sûr car elle va attendre d'avoir libéré le buffer avant de passer à la suite tandis que le non-bloquant va lancer le reste du code dès l'execution du ISend, il peut donc y avoir deux fois le calcul avant qu'il attende.

On peut mettre le MPI_Wait en dessous du MPI_ISend pour le rendre sûr.

## Circulation d'un jeton dans un anneau

On remarque pas grand chose

## Calcul de pi par lancer de fléchettes

