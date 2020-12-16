# Suite bitonic

Lors du tri, on trie la première moitié de la suite considérée dans l'ordre croissant et la seconde
moitié de la suite dans l'ordre décroissant, et pour trier les sous-listes, on procède de même.

L'idée pour paralléliser ici est donc de faire trier la première moitié de la suite par un thread
et la seconde moitié par une second thread, et pour chaque sous-suite on parallélise de même.

La principale difficulté lors de la parallélisation de la suite bitonique est que l'algorithme étant
récursif, il faut éviter de lancer pendant les appels récursifs de la focntion trop de threads, ce qui
nuirait à la performance de la parallélisation.

Un possibilité est de limiter le nombre de threads en fonction de la profoneur de la récursion. Par exemple,
on peut décider de ne plus lancer de threads au troisième niveau de récurson de la suite, ce qui fera
que nous nous limiterons dans ce cas à 2^3=8 threads en tout.

La seule limitation de cette technique est que nous ne pouvons limiter le nombre maximal de thread
qu'à une puissance de deux.

Pour les tests, l'ordinateur utilisé possédait six coeurs physiques de calcul hyperthreadés.

Voici en fonction du nombre maximal de thread les performances  en parallèle :

Pour le tri de valeurs scalaires :

+=========================================================+
| # proc | Temps total calcul | Accélération | Efficacité |
|=========================================================|
|   1    |       0s62         |       1      |     100%   |
|--------+--------------------+--------------+------------|
|   2    |       0s32         |      1.94    |      97%   |
|--------+--------------------+--------------+------------|
|   4    |       0s20         |      3.1     |      78%   |
|--------+--------------------+--------------+------------|
|   8    |       0s16         |      3.9     |      49%   |
|--------+--------------------+--------------+------------|
|  16    |       0s14         |      4.43    |      28%   |
+=========================================================+

L'accélération se comporte bien jusqu'à quatre threads. A partir de huit, on observe un écroulement
des performances dû surement à plusieurs facteurs :

    1. Les premières récursions de la fonction de tri n'utilisent pas tous les threads et il faut faire
       un nombre de récursions de plus en plus en grand pour exploiter pleinement tous les threads demandés.
    2. Le nombre de thread est supérieur au nombre de coeurs physique
    3. L'accès à la mémoire commence aussi à ralentir l'efficacité de la parallélisation.

Pour le tri de vecteurs :

+=========================================================+
| # proc | Temps total calcul | Accélération | Efficacité |
|=========================================================|
|   1    |      22s27         |       1      |     100%   |
|--------+--------------------+--------------+------------|
|   2    |      13s91         |       1.6    |      80%   |
|--------+--------------------+--------------+------------|
|   4    |      11s12         |       2      |      50%   |
|--------+--------------------+--------------+------------|
|   8    |       9s72         |       2.3    |      29%   |
|--------+--------------------+--------------+------------|
|  16    |       9s31         |      2.39    |      15%   |
+=========================================================+

Contrairement au tri scalaire, on voit ici qu'à partir de quatre threads, la parallélisation n'est plus très efficace.
Si le premier point précédent est toujours valable, on voit ici que le fait de gérer des vecteurs nous fait sortir plus
facilement de la mémoire cache (à cause de la taille des vecteurs) et que le calcul de la norme + le tri presse encore
plus le goulot d'étranglement qu'est la mémoire. Ce qui explique cette dégradation pour quatre processus.

Afin de se convaincre que l'accès mémoire dégrade les performances, on a transformé la classe vecteur de sorte
que le calcul de la normne ne se fait qu'une seule fois. Le principale accès mémoire ne provient plus que de l'échange
des vecteurs (qui dans le cas des vecteurs ne correspond qu'à l'échange de leurs vecteurs adressant les tableaux).

On voit dans le tableau suivant que l'efficacité s'est amélioré (sans parler du temps de tri qui est divié par dix du fait qu'on ne recalcule plus plusieurs fois la norme d'un vecteur). Néanmoins, il reste un défaut dans notre algorithme qui provient du fait
que le calcul des normes des vecteurs à leurs premières comparaisons va dégrader l'accès cache du fait qu'on accède à leurs coefficients.

Pour le tri de vecteurs (avec stockage de la norme):

+=========================================================+
| # proc | Temps total calcul | Accélération | Efficacité |
|=========================================================|
|   1    |       1s57         |       1      |     100%   |
|--------+--------------------+--------------+------------|
|   2    |       1s01         |       1.55   |      78%   |
|--------+--------------------+--------------+------------|
|   4    |       0s6          |       2.6    |      65%   |
|--------+--------------------+--------------+------------|
|   8    |       0s54         |       2.9    |      36%   |
|--------+--------------------+--------------+------------|
|  16    |       0s53         |       3.0    |      19%   |
+=========================================================+

Si on précalcule les normes des vecteurs pour le tri, on voit effectivement qu'on améliore encore les performances
et on retrouve une dégradation similaire à celle observée avec les scalaires (avec une efficacité moindre toute fois
à cause du précalcul de la norme des vecteurs qui est parallélisée mais limitée par l'accès mémoire). Remarquons que curieusement, le temps de tri sur un seul thread est plus grand que pour la version précédente.

Pour le tri de vecteurs (avec pré-stockage de la norme):

+=========================================================+
| # proc | Temps total calcul | Accélération | Efficacité |
|=========================================================|
|   1    |       1s70         |       1      |     100%   |
|--------+--------------------+--------------+------------|
|   2    |       0.96         |       1.77   |      89%   |
|--------+--------------------+--------------+------------|
|   4    |       0s6          |       2.6    |      65%   |
|--------+--------------------+--------------+------------|
|   8    |       0s56         |       3.0    |      38%   |
|--------+--------------------+--------------+------------|
|  16    |       0s48         |       3.6    |      23%   |
+=========================================================+
