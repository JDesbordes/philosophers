# philosophers

<img src="https://user-images.githubusercontent.com/45235527/96753610-698e7080-13d0-11eb-9461-d3351c9208d7.png" width="250" height="200" />

<strong>Description</strong>

Ce projet est une introduction au bases du threading de processus, et comment travailler sur le même espace mémoire.
Vous apprendrez comment faire des threads.
Vous découvrirez les mutex, les semaphores, et la mémoire partagée.

<p align="center" width="100%">
  
<img src="https://user-images.githubusercontent.com/45235527/104717704-ff187280-5729-11eb-940e-f52e2ed31e46.gif" width="33%" height="33%" /> <img src="https://user-images.githubusercontent.com/45235527/104717692-f9229180-5729-11eb-9e58-edca3bea9a58.gif" width="33%" height="33%" /> <img src="https://user-images.githubusercontent.com/45235527/104717707-ffb10900-5729-11eb-86c0-8fb81f8d2147.gif" width="33%" height="33%" />

</p>


# Partie obligatoire

Vous devez faire 3 programmes respectant le même set de règles basiques :

- Ce projet doit êre codé en C. Tout crash, fuite mémoire, comportement indéterminé
ou erreur de norme rapporte 0 au projet.
- Un nombre de philosophes sont assis autour d’une table et font trois choses :
manger, penser et dormir.
- Lorsqu’ils mangent, ils ne peuvent pas penser ou dormir, lorsqu’ils dorment, ils
ne peuvent pas manger ou penser, et enfin, lorsqu’ils pensent, ils ne peuvent pas
manger ou dormir.
- La table est circulaire et a un large plat de spaghettis au centre.
- Il y a des fourchettes sur la table.
- Comme il n’est pas aisé de se servir et manger avec une seule fourchette, nous
assumerons qu’un philosophe doit manger avec deux fourchettes, une dans chaque
main.
- Les philosophes ne doivent jamais être affamés.
- Tous les philosophes ont besoin de manger.
- Les philosophes ne communiquent pas entre eux.
- Les philosophes ne savent pas lorsque l’un d’entre eux est sur le point de mourir.
- Dès qu’un philosophe a fini de manger, il pose ses fourchettes et se met à dormir.
- Quand un philosophe a fini de dormir, il se met a penser.
- La simulation s’arrête dès qu’un philosophe meurt.
- Tous les programmes auront les mêmes options : number_of_philosopher time_to_die
time_to_eat time_to_sleep [number_of_time_each_philosophers_must_eat]
- Each programs should have the same option : number_of_philosopher time_to_die
time_to_eat time_to_sleep [number_of_time_each_philosophers_must_eat]
  - number_of_philosopher : correspond au nombre de philosophes et au nombre
de fourchettes.
  - time_to_die : en millisecondes. Si un philosophe ne commence pas a manger
dans ’time_to_die’ millisecondes après avoir commencer son dernier repas ou
le début de la simulation, il meurt.
  - time_to_eat : en millisecondes. C’est le temps que prend un philosophe à
manger. Il garde les deux fourchette pendant ce temps.
  - time_to_sleep : en millisecondes. C’est le temps que prend un philosophe à
dormir.
  - number_of_time_each_philosophers_must_eat : Optionnel, si tous les philosophes mangent au moins ’number_of_time_each_philosophers_must_eat’
la simulation s’arrête. Si ce temps n’est pas spécifié, la simulation s’arrête dès
qu’un philosophe meurt.
- Chaque philosophe se verra assigné un nombre de 1 à ’number_of_philosopher’.
- Philosophe 1 est à coté de philosophe ’number_of_philosopher’. Tous les autres
philosophes sont N sont à coté de leur N + 1 et N - 1.
- Tout changement de statut d’un philosophe doit être écrit comme suit (X remplacant le numéro de philosophe et timestamp_in_ms le timestamp, en millisecondes)
  - timestamp_in_ms X has taken a fork
  - timestamp_in_ms X is eating
  - timestamp_in_ms X is sleeping
  - timestamp_in_ms X is thinking
  - timestamp_in_ms X died
- Le statut affiché ne doit pas être mélangé avec le statut d’un autre philosophe.
- Vous ne pouvez pas avoir plus de 10ms de retard entre la mort d’un philosophe et
l’affichage de sa mort.
- Les philosophes doivent éviter de mourir !


## Contraintes

![Sujet - Philo 1](https://user-images.githubusercontent.com/45235527/102659664-12134380-417a-11eb-9b55-7861a10e338d.PNG)

Dans cette version, les règles supplémentaires seront :

- Il y a une fourchette entre chaque philosophe, donc il y aura une fourchette à
gauche et a droite de chaque philosophe.
- Pour éviter aux philosophes d’accidentellement dupliquer des fourchettes, vous
devez protéger l’état des fourchettes à l’aide de mutex.
- Vous devez attacher chaque philosophe à un thread différent.


![Sujet - Philo 2](https://user-images.githubusercontent.com/45235527/102659873-69b1af00-417a-11eb-9b36-ed62e71d3654.PNG)

Dans cette version, les règles supplémentaires seront :

- Toutes les fourchettes sont au milieu de la table.
- Elles n’ont pas d’état spécifique en mémoire, mais le nombre de fourchettes disponibles est représenté par un semaphore
- Vous devez attacher chaque philosophe à un thread différent.


![Sujet - Philo 3](https://user-images.githubusercontent.com/45235527/102659659-10e21680-417a-11eb-9d14-6c2f3b05c205.PNG)

Dans cette version, les règles supplémentaires seront :

- Toutes les fourchettes sont au milieu de la table.
- Elles n’ont pas d’état spécifique en mémoire, mais le nombre de fourchettes disponibles est représenté par un semaphore
- Chaque philosophe est représenté par un processus différent. Le processus principal
ne devrait pas être un philosophe.

# Resultat 

<p align="center" width="100%">
   <img src="https://user-images.githubusercontent.com/45235527/104717704-ff187280-5729-11eb-940e-f52e2ed31e46.gif" width="60% height="50%" />
  
   <img src="https://user-images.githubusercontent.com/45235527/104717692-f9229180-5729-11eb-9e58-edca3bea9a58.gif" width="60%" height="50%" />
   
   <img src="https://user-images.githubusercontent.com/45235527/104717707-ffb10900-5729-11eb-86c0-8fb81f8d2147.gif" width="60%" height="50%" />
</p>
