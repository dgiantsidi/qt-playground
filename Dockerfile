# Use the official Ubuntu 18.04 LTS image as the base image
FROM ubuntu:18.04

# Update and upgrade the packages
RUN apt-get update && apt-get upgrade -y sudo

# Install any necessary packages
RUN apt-get install -y build-essential qt5-default qt5-doc qt5-doc-html qtbase5-doc-html

RUN useradd -ms /bin/bash myuser
RUN usermod -aG sudo myuser

WORKDIR /home/myuser/app
# Set the working directory

# Copy the contents of the current directory to the container's working directory
COPY . .
RUN chown -R myuser:myuser /home/myuser/app && chgrp myuser /home/myuser/app && chmod g+w /home/myuser/app
RUN echo '%sudo ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers
USER myuser



# Set the command to run when the container starts
# CMD ["cd examples/my_app && qmake"]

