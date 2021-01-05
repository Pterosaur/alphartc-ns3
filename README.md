# webrtc-gcc-ns3

Simulation for webrtc cc algorithm on ns-3.32

### Setup Guide

#### Clone the repo

```sh
export WORK_DIR=$(pwd)
export GYM=$WORK_DIR/gym
git clone https://github.com/Pterosaur/alphartc-ns3.git gym
```

#### ns3.32 installation

```sh
cd $WORK_DIR
git clone https://gitlab.com/nsnam/ns-3-allinone.git
cd ns-3-allinone
./download.py -n ns-3.32
cd ns-3.32
export NS_DIR=$(pwd)
```
#### get AlphaRTC code

```sh
cd $GYM
git submodule init
git submodule update
cd AlphaRTC
export ALPHARTC_DIR=$(pwd)
```

#### Replace some source files from this repo 

```sh
cd $GYM
cp -rf src/* $ALPHARTC_DIR/
cp -rf ex-webrtc/test $ALPHARTC_DIR
cp -rf ex-webrtc $NS_DIR/src/
```

#### Compile libwebrtc.a 

```sh
cd $ALPHARTC_DIR
make sync host_workdir=$GYM docker_homedir=/app docker_workdir=/app/AlphaRTC
make lib
```

then we'll get `$ALPHARTC_DIR/out/m84/obj/libwebrtc.a`

<!--

#### Set the default c++ version in `$NS_DIR/wscript` or you can directly replace it with `global-script` in this repo.

```sh
cd $NS_DIR
vi wscript
```

```python
# Enable C++-11 support
env.append_value('CXXFLAGS', '-std=c++11')
   
# Enable C++-14 support
# Change to 
env.append_value('CXXFLAGS', '-std=c++14')
```

-->

#### Build ns project

```sh
cd $NS_DIR
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$ALPHARTC_DIR:$ALPHARTC_DIR/third_party/abseil-cpp
# CXXFLAGS="-Wno-error" ./waf configure --enable-static
./waf configure --enable-static --cxx-standard=c++14
./waf build
```

#### Copy the webrtc sratch script `scratch/webrtc_test/*` to `ns-3.26/scratch/`, 

```sh
cd $GYM
cp -r scratch $NS_DIR
```

#### Then you can run the script:

```shell
cd $NS_DIR
mkdir traces
./waf --run webrtc_test
```

You can see the results in `$NS_DIR/traces`. And you can compare the results with the plots in `./results/`

#### Customized estimator

You can set your own CC model to control the bitrate in `my_network_estimator.cc`

### Reference: 

1. download webrtc(m84):  [instruction](https://mediasoup.org/documentation/v3/libmediasoupclient/installation/)
2. Evaluate webrtc GCC congestion control on ns3: [link](https://blog.csdn.net/u010643777/article/details/107237315)


