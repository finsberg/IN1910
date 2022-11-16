ARG REPO_BRANCH="main"

# We choose ubuntu 22.04 as our base docker image
FROM ubuntu:22.04 as base

# Expose arg
ARG REPO_BRANCH

# Install pip and git with apt
RUN apt-get update && \
    apt-get install -y python3-pip git

# We upgrade pip and setuptools
# We remove the version of setuptools install via apt, as it is outdated
RUN python3 -m pip install pip setuptools --upgrade
RUN apt-get purge -y python3-setuptools


# We set the working directory to install docker dependencies
WORKDIR /tmp/

# Install the Python-module
RUN git clone --branch ${REPO_BRANCH} --single-branch https://github.com/finsberg/IN1910
RUN python3 -m pip install -r requirements.txt


# We remove the contents of the temporary directory to minimize the size of the image
RUN rm -rf /tmp
