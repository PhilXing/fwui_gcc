8be4df61-93ca-11d2-aa0d-00e098032b8c-OsIndications
sudo apt install efivar
chattr -i /sys/firmware/efi/efivars/
sudo printf "\x01\x00\x00\x00\x00" > /sys/firmware/efi/efivars/OsIndications-8be4df61-93ca-11d2-aa0d-00e098032b8c
OsIndications-8be4df61-93ca-11d2-aa0d-00e098032b8c

sudo efivar -w -n 8be4df61-93ca-11d2-aa0d-00e098032b8c-OsIndications -f new.txt



sudo apt install libefivar-dev

