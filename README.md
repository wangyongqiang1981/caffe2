prepare on Ubuntu16.04 with K80x2

    install NVIDIA_driver
    install CUDA8.0
    install cuDNN6.0
    install Anaconda3
        conda update -n base conda
        add source.list (optional:China)

setup 
```
sudo apt-get update
sudo apt-get upgrade

conda create -n ai_caffe2 python=2.7
conda activate  ai_caffe2

conda install cmake ipython opencv git future protobuf hypothesis pydot
sudo apt-get install -y --no-install-recommends \
      build-essential \
      libgoogle-glog-dev \
      libgtest-dev \
      libiomp-dev \
      libleveldb-dev \
      liblmdb-dev \
      libopencv-dev \
      libopenmpi-dev \
      libsnappy-dev \
      libprotobuf-dev \
      openmpi-bin \
      openmpi-doc \
      protobuf-compiler \
      python-dev

sudo apt-get remove libprotobuf-dev
conda install protobuf

git clone --recursive https://github.com/caffe2/caffe2.git && cd caffe2
git submodule update --init
mkdir build && cd build

cmake -DCMAKE_INSTALL_PREFIX=/your-anaconda3-path/envs/ai_caffe2 -DUSE_NATIVE_ARCH=ON ..
sudo make install -j8

cd your-anaconda3-path
sudo chown robot:robot -R * 
#my user:group is robot

echo "export LD_LIBRARY_PATH="/home/robot/anaconda3/envs/ai_caffe2/:/home/robot/anaconda3/pkgs/cudatoolkit-8.0-3/lib" >> ~/.bashrc
. ~/bashrc
conda activate ai_caffe2

watch -n 0.1 nvidia-smi 
python -m caffe2.python.operator_test.relu_op_test
# Ran 1 test in 2.846s
```
