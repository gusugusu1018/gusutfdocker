# My Docker image of tensorflow

## Usage

```bash
# build image
make build

# run docker container
make run

# start docker container
make start

# start shell
make shell

# stop docker container
make stop

# erase docker container
make rm

# stop and erace docker container
make clean
```


## mnist test

```bash
cd workspace/mnist
./download_model.sh
./build_x86_64.sh
./main.out
```

If you want to crosscompile to raspi
```bash
./build_armhf.sh
scp main.out hoge@fugahoge:~/fuga/.
```
