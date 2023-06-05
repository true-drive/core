docker build -f Dockerfile.dev -t truedrive_core_dev ..
docker run -it --rm -v "$(pwd)":/app truedrive_core_dev /bin/sh