# KaOS - An experimental and minimal operating system

## Building with Docker
For now, the easiest way is to build the `.iso` file with Docker. After installing docker, follow the steps;
```bash
docker build -t kaos .

# Optional: do this if you want to move .iso file in the container to your local machine
id=$(docker create image-name)
docker cp $id:/src/KaOS/kaos.iso - > ./kaos.iso
docker rm -v $id

# To work on the container and experiment
docker run -t -i kaos /bin/sh
```
