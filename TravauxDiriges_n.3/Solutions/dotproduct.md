# Produit scalaire parallélisé

La parallélisation du produit scalaire est relativement simple puisqu'il suffit de partager la boucle
sur la sommation en partie de mêmes tailles, le nombre de parties étant égale au nombre de threads demandés.

Voici le tableau obtenu des performances en parallèle :

+=========================================================+
| # proc | Temps total calcul | Accélération | Efficacité |
|=========================================================|
|   1    |       0.22         |       1      |     100%   |
|--------+--------------------+--------------+------------|
|   2    |       0.18         |       1.22   |      61%   |
|--------+--------------------+--------------+------------|
|   4    |       0s17         |       1.29   |      32%   |
|--------+--------------------+--------------+------------|
|   6    |       0s23         |       0.96   |      16%   |
+=========================================================+

on voit ici clairement le rôle de la mémoire dont l'accès limite les performances de l'algorithme
parallèle, voire même les pénalise dans le cas où l'on prend six threads. On est clairement Memory
Bound dans ce cas et une analyse du code nous le confirme puisque le nombre d'opérations effectuées
est deux fois moindre que le nombre de données utilisées.

