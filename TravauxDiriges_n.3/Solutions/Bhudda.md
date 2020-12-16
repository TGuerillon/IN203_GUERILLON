# Résultat sur Bhudda

L'ordinateur sur lequel l'accélération a été calculé possède six coeurs de calculs physiques
hyperthreadés.

Le temps de sauvegarde de l'image étant négligeable, on ne s'intéresse qu'à la parallélisation
du calcul de l'ensemble de Bhudda.

Temps pris en parallèle :

+=========================================================+
| # proc | Temps total calcul | Accélération | Efficacité |
|=========================================================|
|   1    |       12s08        |       1      |     100%   |
|--------+--------------------+--------------+------------|
|   2    |       6s           |       2      |     100%   |
|--------+--------------------+--------------+------------|
|   4    |       3s6          |      3.4     |     85%    |
|--------+--------------------+--------------+------------|
|   6    |       2s36         |      5.1     |     85%    |
|--------+--------------------+--------------+------------|
|   8    |       2s           |      6       |     75%    |
|--------+--------------------+--------------+------------|
|  10    |       1s8          |      6.7     |     67%    |
|--------+--------------------+--------------+------------|
|  12    |       1s64         |      7.4     |     62%    |
+=========================================================+

On voit que l'accélération reste conséquente jusqu'à six threads (85% d'efficacité), bien qu'une
légère baisse de l'efficacité est observée à partir de quatre threads.

Au delà de six threads, les performances se dégradent, ce qui est attendu puisque la machine ne
possède que six coeurs physiques. Néanmoins, on peut observer tout de même un gain grâce à
l'hyperthreading puisque de 85% d'efficacité sur six threads, on passe à 62% sur douze threads !

Remarquons de plus que sur ce problème, l'accès mémoire ne joue aucun rôle, on est en CPU-Bound,
car on itère principalement sur une suite récursive dont les valeurs restent au niveau des
registres du CPU, ou au pire dans la mémoire cache L1.