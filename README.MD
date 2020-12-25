

[![Wazuh](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwazuh.com%2Fwp-content%2Fuploads%2F2018%2F12%2Fwazuh_web_img_blog-full.png&f=1&nofb=1)](https://wazuh.com/)
![Monty](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fi.ytimg.com%2Fvi%2F_X5erR9LKUs%2Fmaxresdefault.jpg&f=1&nofb=1)

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

# Usage
You can play with the executable with the following parameters:
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
$ docker run monty
```
If you want to play with some parameters do the following:
```sh
$ docker run -it wazuh ./monty --loops 5000000 --doors 100 --reveal 98 --threads 4
```

