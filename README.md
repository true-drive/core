# True Drive Core

## Description
True Drive is a storage solution that allows you to encrypt any file to a noise video and upload it to YouTube. This way, you can store your files securely and access them from anywhere with an internet connection. You can also download and decrypt the noise videos back to your original files whenever you need them.

This repository houses the core functionality of True Drive which lies in the process of encrypting/decrypting files into a series of random pixels and sound waves.

## Usage

The program has two entry modes, encode and decode. Both can be run as follow

```sh
./truedrive [option] -i <input file> -o <output folder>
```

### Encoding
In order to encode a file into a noise video, say `input.txt`, run the following.

```sh
./truedrive encode -i input.txt -o /path/to/output
```

### Decoding
In order to encode a file into a noise video, say `input.txt`, run the following.

```sh
./truedrive decode -i input.mp4 -o /path/to/output
```