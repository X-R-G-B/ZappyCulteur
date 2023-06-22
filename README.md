# Zappy[Culteur]

## Table of Contents

- [Introduction](#Introduction)
- [Installation](#Installation)
- [Usage](#Usage)
- [Graphic Helper](#Graphic-Helper)
    - [FOOD](#FOOD)
    - [LINEMATE](#LINEMATE)
    - [DERAUMERE](#DERAUMERE)
    - [SIBUR](#SIBUR)
    - [MENDIANE](#MENDIANE)
    - [PHIRAS](#PHIRAS)
    - [THYSTAME](#THYSTAME)
- [Contributors](#Contributors)
- [Gource](#Gource)

## Introduction

<details open>
    <summary>in English</summary>

The Zappy (Culteur) is a game in the form of a board without edges (cyclic), where 'trantoriens' (the bees) will move in order to recover resources allowing them
to survive and evolve in the but to reach level 8 to win his team.
Trantorians have the ability to eject.

The aim is to make a game playable by AIs.

It is divided into 3 parts:
- Make an __**IA**__ that tries to __survive and evolve in a world__.
- Make a __**Server**__ that __manages the actions of AIs in the world__ and __sends data to the Graphic__.
- Make a __**Graphic**__ client to the Server that __displays the world__.

</details>

<details>
    <summary>en Français</summary>

Le Zappy(Culteur) est un jeu sous forme de plateau sans bords (cyclique), ou des 'trantoriens' (les abeilles) vont se déplacer afin de récupérer des ressources leur perméttants
de survivre et d'évoluer dans le but d'atteindre le niveau 8 pour faire gagner son équipe.
Les trantoriens ont la possibilité d'éjécter.

Le but est de faire un jeu jouable par des IA.

Il se découpe en 3 parties:
- Faire une __**IA**__ qui essaie de __survivre et évoluer dans un monde__
- Faire un __**Serveur**__ qui __gère les actions des IA dans le monde__ et __envoi des données au Graphique__
- Faire un client __**Graphique**__ au Serveur qui permet __d'afficher le monde__

</details>

## Installation

<details open>
    <summary>Docker</summary>

```sh
docker run -it --rm --name zappy -v "$PWD:/code" -w "/code" docker.io/epitechcontent/epitest-docker make
```

</details>

<details>
    <summary>OS</summary>

- you need to install **make** and **cmake**
```sh
# Arch-based
pacman -S make cmake
# Debian-based
apt install make cmake
# Fedora
dnf install make cmake
# Windows: https://www.technewstoday.com/install-and-use-make-in-windows/
```

- you need to install **SFML** (linux only)
```sh
# Arch-based
pacman -S sfml-dev
# Debian-based
apt install libsfml-dev
# Fedora
dnf install SFML-devel SFML
# Windows: it will be installed automatically
```

- you need to install **python** and **pip**
```sh
# Arch-based
pacman -S python python-pip
# Debian-based
apt install python3 pip
# Fedora
dnf install python pip
# Windows: available on microsoft store
```

- run the following command
```sh
make
```

</details>

## Usage

<details open>
    <summary>Docker</summary>

- The server (and initialize the docker container) *if you want a graphical interface, please follow the `2.`*
1. on one terminal:
```sh
docker run -it --network=host --rm --name zappy -v "$PWD:/code" -w "/code" docker.io/epitechcontent/epitest-docker
make
# ./zappy_server --help
./zappy_server -p 4042 -x 10 -y 20 -n abc -c 5 -f 50
```
2. ont one terminal (**only tested on linux**)
```bash
docker run -it --rm --name zappy -v "$PWD:/code" -v "/dev/dri/:/dev/dri/" -v "/tmp/.X11-unix/:/tmp/.X11-unix/" -v "$HOME/.Xauthority:/root/.Xauthority" --network=host  -w "/code" docker.io/epitechcontent/epitest-docker
make
# ./zappy_server --help
./zappy_server -p 4042 -x 10 -y 20 -n abc -c 5 -f 50
```

- The graphical user interface (*only if you followed step `2.`*):
```sh
docker exec -it -e "DISPLAY=$DISPLAY" zappy bash
dnf install -y mesa-dri-drivers
# ./zappy_gui --help
./zappy_gui -h 127.0.0.1 -p 4042
```

- The player (AI/Bot):
```sh
docker exec -it zappy bash
# ./zappy_ai --help
./zappy_ai -p 4042 -n abc
```

</details>

<details>
    <summary>OS</summary>

- on one terminal:
```sh
# ./zappy_server --help
./zappy_server -p 4042 -x 10 -y 20 -n abc -c 5 -f 50
```

- on another terminal:
```sh
# ./zappy_gui --help
./zappy_gui -h 127.0.0.1 -p 4042
```

- on another terminal:
```sh
# ./zappy_ai --help
./zappy_ai -p 4042 -n abc
```

</details>

## Graphic-Helper

### FOOD:
![honey](https://github.com/X-R-G-B/ZappyCulteur/assets/91657273/3763b0fd-0241-4ac0-9f7f-ad0bc69ca963)

### LINEMATE:
![rocks](https://github.com/X-R-G-B/ZappyCulteur/assets/91657273/463cb2c3-4e47-425c-8fe9-20c2df6af3a0)

### DERAUMERE:
![flower](https://github.com/X-R-G-B/ZappyCulteur/assets/91657273/598e9532-88db-4717-b454-011ef0860e5f)

### SIBUR:
![rose](https://github.com/X-R-G-B/ZappyCulteur/assets/91657273/35f6af23-b21e-4c9d-a083-f780a1116097)

### MENDIANE:
![hibiscus](https://github.com/X-R-G-B/ZappyCulteur/assets/91657273/23754955-b090-41a6-b22b-935b80871066)

### PHIRAS:
![camellia](https://github.com/X-R-G-B/ZappyCulteur/assets/91657273/0bed9ff3-663c-4033-a262-861d1c877b1e)

### THYSTAME:
![dahlia](https://github.com/X-R-G-B/ZappyCulteur/assets/91657273/7505394d-ae49-40eb-bd05-f27fd4f5d618)

## Contributors

| [<img src="https://github.com/Saverio976.png?size=85" width=85><br><sub>Saverio976</sub>](https://github.com/Saverio976) | [<img src="https://github.com/TTENSHII.png?size=85" width=85><br><sub>TTENSHII</sub>](https://github.com/TTENSHII) | [<img src="https://github.com/KitetsuK.png?size=85" width=85><br><sub>KitetsuK</sub>](https://github.com/KitetsuK) | [<img src="https://github.com/guillaumeAbel.png?size=85" width=85><br><sub>guillaumeAbel</sub>](https://github.com/guillaumeAbel) | [<img src="https://github.com/romainpanno.png?size=85" width=85><br><sub>romainpanno</sub>](https://github.com/romainpanno) | [<img src="https://github.com/StEgo2103.png?size=85" width=85><br><sub>StEgo2103</sub>](https://github.com/StEgo2103)
| :---: | :---: | :---: | :---: | :---: | :---: |

## Gource

![source](/bonus/assets/zappyculteur.mp4)
