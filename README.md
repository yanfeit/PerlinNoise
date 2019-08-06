# Perlin Noise

This note is about Perlin noise and accelerating Python codes using C dynamic library. My knowledge of Perlin noise mostly comes from [pvigier](https://github.com/pvigier/perlin-numpy)'s GitHub site, [Adrian](https://flafla2.github.io/2014/08/09/perlinnoise.html)'s blog, [Wikipedia](https://en.wikipedia.org/wiki/Perlin_noise), and this marvelous [post](https://gpfault.net/posts/perlin-noise.txt.html). Anyone who wants to learn Perlin noise is strongly recommended to take a look at those references. There are several ways to accelerate Python codes. I learn one way from this [post](https://zhuanlan.zhihu.com/p/76058539). 

My original idea is to study how to generate a smooth noise, not a white noise. Perlin noise is definitely a good choice. I like to use Python. However, Python does not have the speed to do this in a fast way. If multiples of for loops are unavoided, the performance of Python is horrible! One of the options to accelerate Python is taking the advantage of numpy, if one has the superior numpy skill like Pvigier did in this [post](https://pvigier.github.io/2018/06/13/perlin-noise-numpy.html). Building such skills require fluency about numpy. An alternative way is accerlateing Python by using C dynamic library. 

To build the C dynamic library, use the following in terminal.

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ mv ./lib/libperlinNoise.dylib ../python # Move library to the python folder.
```

This will generate a dynamics library libperlinNoise.dylib in the folder ./build/lib. 

