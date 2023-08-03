#! /bin/bash
if [ $# -eq 0 ]
  then
    workspace=$(pwd)
else
  workspace=$1
fi

echo Home path at $HOME
echo Mounting $workspace at /build

username=$(whoami)
# user user and group IDs:
usr="--user $(id -u ${username}):$(id -g ${username})"
mountdirs="-v /etc/passwd:/etc/passwd:ro\
           -v /etc/shadow:/etc/shadow:ro\
           -v /etc/group:/etc/group:ro\
           -v /etc/resolv.conf:/etc/resolv.conf:ro\
           -v ${HOME}/.qnx/:${HOME}/.qnx/\
           -v /etc/hosts:/etc/hosts:ro\
           -v $workspace:/build"

options="-p 6379:6379"
options="-it --rm --entrypoint=/bin/bash"

# image=jfrog.chennai.visteon.com:8443/docker-local/qcom_platform_devenv:2021May07
# image=jfrog.chennai.visteon.com:8443/docker-local/qcom_platform_devenv:2021Jun14
image=jfrog.chennai.visteon.com:8443/docker-local/qcom_platform_devenv:2022Apr02

docker run ${options} ${usr} ${mountdirs} "${image}"

