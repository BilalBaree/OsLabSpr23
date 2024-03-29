Installation Guide for Raspberry Pi In QEMU on Kali/Debian Linux 



<p>1 : Install QEMU <br>
<code>$ sudo apt update </code> <br>
<code>$ sudo apt install qemu-system-arm qemu-kvm libvirt-clients libvirt-daemon-system bridge-utils virtinst libvirt-daemon virt-manager</code> <br> </p>

2 : Download Raspberry PI Buster Lite Image <br>
Download 2022-09-22-raspios-buster-armhf-lite.img.xz from : [Website](https://www.raspberrypi.com/software/operating-systems/) <br>
Direct Download : [Download](https://downloads.raspberrypi.org/raspios_oldstable_lite_armhf/images/raspios_oldstable_lite_armhf-2022-09-26/2022-09-22-raspios-buster-armhf-lite.img.xz) <br>

3 : Download kernel-qemu-4.19.50-buster and versatile-pb-buster.dtb <br>
Link : [website](https://github.com/dhruvvyas90/qemu-rpi-kernel) <br>

4 : Set up the VM in Virtual Manager <br>
Open Virtual Machine Manager with <br><code>$ sudo virt-manager</code> <br>Click Create new virtual machine. <br>
Step 1:

    Choose Import existing disk image.
    Under Architecture Options:
        Select Architechture: armv6l.
        Select Machine Type: versatilepb.
    Click Forward.

Step 2:

    Under Provide the existing storage path:
        Click Browse.
        Click Browse Local.
        Go to the downloaded OS image location and select the OS Image (.img or .qcow2).
    Under Choose the operating system you are installing: select Generic or unknown OS. Usage is not recommended.
    Click Forward.

Step 3:

    Input Memory: 256.
    Input CPU: 1.
    Click Forward.

Step 4:

    Rename VM if you like.
    Toggle Customize configuration before install ON.
    Choose Network selection: Virtual network 'default' : NAT.
    Click Finish.

Configuration screen:

    Go to CPUs tab:
        Select Model: arm1176.
        Click Apply.

    Go to Boot Options tab:
        Expand Direct kernel boot.
        Toggle Enable direct kernel boot ON.
        Input or browse Kernel path: /.../kernel-qemu-4.19.50-buster.
        Input or browse DTB path: /.../versatile-pb-buster.dtb.
        Input Kernel args: root=/dev/vda2 panic=1.
        Click Apply.

    Go to IDE Disk 1 tab:
        Select Disk Bus: VirtIO.
        Click Apply.

    Go to NIC tab:
        Select Device Model: virtio.
        Select Apply.

    Click Add Hardware:
        Go to Channel tab.
        Input Name: org.qemu.guest_agent.0
        Select Device Type: UNIX socket (unix).
        Click Finish.

    (Optional) Click Add Hardware:
        Go to RNG tab.
        Click Finish.

    Click Begin Installation.

    The VM will start and begin installation. Wait for it to finish, you'll be prompted to log in.

5 : Inside VM 

    Log in with the default credentials Login: pi and Password: raspberry.
    Run $ sudo raspi-config to configure the OS (hostname, password, ssh, language, keyboard layout, etc.).
    Run $ sudo apt install qemu-guest-agent to install QEMU guest agent and enable host control.
6 : ALL DONE!




