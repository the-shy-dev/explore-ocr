# explore-ocr

### 1.3 Compile or Download or the Paddle Inference Library

* There are 2 ways to obtain the Paddle inference library, described in detail below.

#### 1.3.1 Direct download and installation

[Paddle inference library official website](https://www.paddlepaddle.org.cn/inference/master/guides/install/download_lib.html#linux). You can review and select the appropriate version of the inference library on the official website.


* After downloading, use the following command to extract files.

```
tar -xf paddle_inference.tgz
```

Finally you will see the folder of `paddle_inference/` in the current path.

#### 1.3.2 Compile the inference source code
* If you want to get the latest Paddle inference library features, you can download the latest code from Paddle GitHub repository and compile the inference library from the source code. It is recommended to download the inference library with paddle version greater than or equal to 2.0.1.
* You can refer to [Paddle inference library] (https://www.paddlepaddle.org.cn/documentation/docs/en/advanced_guide/inference_deployment/inference/build_and_install_lib_en.html) to get the Paddle source code from GitHub, and then compile To generate the latest inference library. The method of using git to access the code is as follows.


```shell
git clone https://github.com/PaddlePaddle/Paddle.git
git checkout develop
```

* Enter the Paddle directory and run the following commands to compile the paddle inference library.

```shell
rm -rf build
mkdir build
cd build

cmake  .. \
    -DWITH_CONTRIB=OFF \
    -DWITH_MKL=ON \
    -DWITH_MKLDNN=ON  \
    -DWITH_TESTING=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DWITH_INFERENCE_API_TEST=OFF \
    -DON_INFER=ON \
    -DWITH_PYTHON=ON
make -j
make inference_lib_dist
```

For more compilation parameter options, please refer to the [document](https://www.paddlepaddle.org.cn/documentation/docs/zh/2.0/guides/05_inference_deployment/inference/build_and_install_lib_cn.html#congyuanmabianyi).


* After the compilation process, you can see the following files in the folder of `build/paddle_inference_install_dir/`.