#!/bin/bash
docker rm deel -f
pwd=`pwd`
if [ $# -ne 1 ]; then
	docker run --name deel --privileged -v $pwd/prgm:/root/prgm -d -p 8888:8888 sakiyamak/deel:latest /bin/bash -c "source /root/.pyenv/versions/anaconda3-4.2.0/bin//activate deel && /root/.pyenv/versions/anaconda3-4.2.0/bin//jupyter notebook --notebook-dir=~/prgm --ip='*' --port=8888 --no-browser"
else
	docker run --name deel --privileged -v $pwd/prgm:/root/prgm -it -p 8888:8888 sakiyamak/deel:latest
fi