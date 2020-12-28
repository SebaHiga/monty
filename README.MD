

![Monty](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fi.ytimg.com%2Fvi%2F_X5erR9LKUs%2Fmaxresdefault.jpg&f=1&nofb=1)
[![Wazuh](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwazuh.com%2Fwp-content%2Fuploads%2F2018%2F12%2Fwazuh_web_img_blog-full.png&f=1&nofb=1)](https://wazuh.com/)

# The Monty Hall problem
The monty hall problem is a famous paradox and mathematical game. It's based on the American television game show called "Let's make a deal".
>Suppose you're on a game show, and you're given the choice of three doors: Behind one door is a car; behind the others, goats. You pick a door, say No. 1, and the host, who knows what's behind the doors, opens another door, say No. 3, which has a goat. He then says to you, "Do you want to pick door No. 2?" Is it to your advantage to switch your choice? 
Marilyn vos Savant's "Ask Marilyn" column in Parade magazine in 1990

# This proyect summary
There are generalized formulas to solve the probability to win the Monty Hall's game. But in this case, the proyect uses multiples simulations to prove that the formula is right (it's obiously right, it was written by a guy waaay smarter!).

## Dependencies
    * GCC
    * CMake
    * Make
    * Docker (optional)

# Compile it!
Put the entire project on your pc and compile the code using CMake.
If you are not in a Linux machine, you might want to use Docker to build the image. In both cases open your terminal friend and go to the project's directory.
### Compiling
```sh
$ mkdir build && cd build
$ cmake .. && make
```
### Using docker
```sh
$ docker build -t monty .
```
# Load it! (with docker)

If the saved docker image is around here, you can load it using. It's only ~5MB!!
```sh
$ docker load < wazuh-monty.tar
```


# Usage
You can play with the executable with the following parameters:
- interactive [1/0] : Start interactive mode and play the game as you were in television!
- loops <N> : The amount of loops of simulations to do. The more, the better will be the precision but it will take more time.
- doors <N> : The amount of doors that the game has.
- reveal <N> : The amount of doors with goats to reveal after the player selects a door.
- threads <N> : The amount of threads to use (limited by 4). The more the faster!

### Usage example
```sh
$ ./monty --loops 20000 --doors 100 --reveal 40 --threads 2
```

# With Docker
With the docker image the parameters are already defined in the dockerfile. To execute it you can do:

```sh
$ docker run -it wazuh-monty ./monty --loops 5000000 --doors 100 --reveal 98 --threads 4
```
```sh
 __________ 	 __________ 	 __________ 	
||         |	||         |	|  __  __  |	
||         |	||         |	| |  ||  | |	
||    A    |	||         |	| |  ||  | |	
||___/_\___|	||         |	| |__||__| |	
|| ',. ..' |	||         |	|  __  __()|	
|| /.'^'.\ |	||)        |	| |  ||  | |	
||/'     '\|	||         |	| |  ||  | |	
||         |	||         |	| |  ||  | |	
||         |	||         |	| |  ||  | |	
||         |	||         |	| |__||__| |	
||_________|	||_________|	|__________|	
```
# Play it!

Play the Monty Hall game as you were in television with the flag **--interactive**.
Use the same other flags but you are limited to use up to 6 doors (unless you have ultra hyper wide monitor heh).

The game implements some host behaviours, pay atention!
* Normal: nothing special, it plays like in the television.
* Angelic Monty: It tries to save you by asking you to change doors.
* Monty Hell: The worst one. It **only** ask you to switch doors if you chose the correct one.

```sh
$ ./monty --interactive 1 --doors 3 --reveal 1
```

## Playing with docker
To play this game with docker just run the following command after builing the image.
```sh
$ docker run -it wazuh-monty
```
### With custom scenario:
```sh
$ docker run -it wazuh-monty ./monty --interactive 1 --doors 4 --reveal 1
```