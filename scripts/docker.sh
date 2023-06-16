docker build -f Dockerfile.dev -t eoussama/truedrive_core_dev:0.0.2 ..
docker run -it --rm -v "$(pwd)":/app eoussama/truedrive_core_dev:0.0.2 /bin/sh