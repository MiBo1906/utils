FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-20.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.21.5"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

RUN apt-get update && apt-get install -y \
    clang-tools \
    clang-format \
    clang-tidy \
    libgtest-dev \
    libgmock-dev \
    python3-pip 
    

RUN pip install -U pytest

COPY log4cplus-files.tar.gz /tmp
RUN cd /tmp && tar xvf log4cplus-files.tar.gz && cd log4cplus-install && cp -r include/* /usr/local/include && cp -r lib/* /usr/local/lib/ && rm -rf /tmp/log4cplus* && ldconfig


# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>
