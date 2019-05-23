# Check http://releases.llvm.org/download.html#8.0.0 for the latest available binaries
FROM conanio/clang8

USER root
RUN apt-get update

RUN apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash develop
RUN echo "develop   ALL=(ALL:ALL) ALL" >> /etc/sudoers


EXPOSE 2000
USER develop

RUN mkdir /home/develop/.conan
RUN mkdir /home/develop/src
RUN mkdir /home/develop/build

RUN chmod a+rwx /home/develop/build
RUN chmod a+rwx /home/develop/.conan

#VOLUME "/home/develop/cpputil"
WORKDIR "/home/develop/build"


# Start from a Bash prompt
#CMD [ "/bin/bash" ]

